#include "gilab/NodePreview.h"
#include "gilab/Node.h"
#include "gilab/RegistNodes.h"
#include "gilab/PinType.h"
#include "gilab/Evaluator.h"
#include "gilab/node/Preview.h"

#include <blueprint/NodeHelper.h>

#include <SM_Matrix2D.h>
#include <unirender/Device.h>
#include <unirender/Context.h>
#include <unirender/Framebuffer.h>
#include <unirender/Texture.h>
#include <unirender/TextureDescription.h>
#include <unirender/ShaderProgram.h>
#include <unirender/Factory.h>
#include <unirender/ClearState.h>
#include <unirender/TextureSampler.h>
#include <painting0/ModelMatUpdater.h>
#include <painting2/Blackboard.h>
#include <painting2/RenderContext.h>
#include <painting2/RenderTarget.h>
#include <painting2/RenderSystem.h>
#include <painting2/RenderTargetCtx.h>
#include <painting2/RenderTargetMgr.h>
#include <painting2/WindowContext.h>
#include <painting2/WindowCtxRegion.h>
#include <painting2/Shader.h>
#include <painting2/ViewMatUpdater.h>
#include <painting2/ProjectMatUpdater.h>
#include <node2/RenderSystem.h>
#include <renderpipeline/RenderMgr.h>
#include <renderpipeline/IRenderer.h>
#include <gigraph/Param.h>
#include <gigraph/ParamImpl.h>

namespace
{

const size_t TEX_SIZE = 1024;

}

namespace gilab
{

void NodePreview::Draw(const ur::Device& dev, ur::Context& ctx, const bp::Node& node, 
                       const n2::RenderParams& rp, const bp::BackendGraph<gigraph::ParamType>& eval)
{
    auto fbo = pt2::RenderTargetMgr::Instance()->Fetch(dev);

    rp::RenderMgr::Instance()->Flush(dev, ctx);

    ctx.SetFramebuffer(fbo);
    Clear(ctx);

    int x, y, w, h;
    ctx.GetViewport(x, y, w, h);
    ctx.SetViewport(0, 0, TEX_SIZE, TEX_SIZE);
    bool succ = DrawToRT(dev, ctx, node, eval);
    ctx.SetViewport(x, y, w, h);
    ctx.SetFramebuffer(nullptr);

    if (succ) {
        auto tex = pt2::RenderTargetMgr::Instance()->GetBindedTex(fbo);
        assert(tex);
        DrawFromRT(dev, ctx, node, rp, tex);
    }

    pt2::RenderTargetMgr::Instance()->Return(fbo);

    auto default_sampler = dev.GetTextureSampler(ur::Device::TextureSamplerType::LinearClamp);
    default_sampler->Bind(0);
}

bool NodePreview::DrawToRT(const ur::Device& dev, ur::Context& ctx, const bp::Node& node, 
                           const bp::BackendGraph<gigraph::ParamType>& eval)
{
    bool ret = false;

    auto renderer = rp::RenderMgr::Instance()->GetRenderer(rp::RenderType::SPRITE);
    auto shader = renderer->GetAllShaders()[0];

    std::shared_ptr<pt0::ModelMatUpdater::Snapshot>   model_snap = nullptr;
    std::shared_ptr<pt2::ViewMatUpdater::Snapshot>    view_snap  = nullptr;
    std::shared_ptr<pt2::ProjectMatUpdater::Snapshot> proj_snap  = nullptr;

    auto model_updater = shader->QueryUniformUpdater(ur::GetUpdaterTypeID<pt0::ModelMatUpdater>());
    if (model_updater)
    {
        auto updater = std::static_pointer_cast<pt0::ModelMatUpdater>(model_updater);
        model_snap = std::make_shared<pt0::ModelMatUpdater::Snapshot>(*updater);
        updater->Update(sm::mat4());
    }
    auto view_updater = shader->QueryUniformUpdater(ur::GetUpdaterTypeID<pt2::ViewMatUpdater>());
    if (view_updater)
    {
        auto updater = std::static_pointer_cast<pt2::ViewMatUpdater>(view_updater);
        view_snap = std::make_shared<pt2::ViewMatUpdater::Snapshot>(*updater);
        updater->Update(sm::vec2(0, 0), 1.0f);
    }
    auto proj_updater = shader->QueryUniformUpdater(ur::GetUpdaterTypeID<pt2::ProjectMatUpdater>());
    if (proj_updater)
    {
        auto updater = std::static_pointer_cast<pt2::ProjectMatUpdater>(proj_updater);
        proj_snap = std::make_shared<pt2::ProjectMatUpdater::Snapshot>(*updater);
        updater->Update(TEX_SIZE, TEX_SIZE);
    }

    auto type = node.get_type();
    if (type == rttr::type::get<node::Preview>())
    {
        auto& conns = node.GetAllInput()[0]->GetConnecting();
        if (!conns.empty())
        {
            assert(conns.size() == 1);
            auto f_pin = conns[0]->GetFrom();
            switch (f_pin->GetOldType())
            {
            case PIN_TEXTURE:
            {
                auto back_node = eval.QueryBackNode(f_pin->GetParent());
                if (back_node) 
                {
                    auto param = std::static_pointer_cast<gigraph::Component>(back_node)->GetValue(f_pin->GetPosIdx());
                    if (param)
                    {
                        assert(param->Type() == gigraph::ParamType::Texture);
                        auto tex = std::static_pointer_cast<gigraph::TextureParam>(param)->GetTexture();
                        if (tex)
                        {
                            auto& preview_node = static_cast<const node::Preview&>(node);

                            auto sampler = dev.GetTextureSampler(preview_node.GetSamplerType());
                            sampler->Bind(0);

                            sm::Matrix2D mat;
                            mat.Scale(static_cast<float>(TEX_SIZE), static_cast<float>(TEX_SIZE));

                            auto rs = ur::DefaultRenderState2D();

                            rs.blending.enabled = false;

                            auto& color_mask = preview_node.GetColorMask();
                            rs.color_mask.r = color_mask.x;
                            rs.color_mask.g = color_mask.y;
                            rs.color_mask.b = color_mask.z;
                            rs.color_mask.a = color_mask.w;

                            pt2::RenderSystem::DrawTexture(dev, ctx, rs, tex->GetWidth(), tex->GetHeight(), tex, sm::rect(1, 1), mat);

                            ret = true;
                        }
                    }
                }
            }
                break;
            }
        }
    }

    rp::RenderMgr::Instance()->Flush(dev, ctx);

    if (model_snap) {
        model_snap->Restore();
    }
    if (view_snap) {
        view_snap->Restore();
    }
    if (proj_snap) {
        proj_snap->Restore();
    }

    return ret;
}

void NodePreview::DrawFromRT(const ur::Device& dev, ur::Context& ctx, const bp::Node& node, 
                             const n2::RenderParams& rp, const ur::TexturePtr& tex)
{
    auto mt4 = sm::mat4(bp::NodeHelper::CalcPreviewMat(node, rp.GetMatrix()));
    const auto scale = mt4.GetScale();
    const float hw = scale.x * 0.5f;
    const float hh = scale.y * 0.5f;
    const auto pos = mt4.GetTranslate();
    const float vertices[] = {
        pos.x - hw, pos.y - hh,
        pos.x + hw, pos.y - hh,
        pos.x + hw, pos.y + hh,
        pos.x - hw, pos.y + hh,
    };
    const float texcoords[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };

    auto rs = ur::DefaultRenderState2D();
    rs.blending.enabled = false;

    pt2::RenderSystem::DrawTexQuad(dev, ctx, rs, vertices, texcoords, tex, 0xffffffff);
}

void NodePreview::Clear(ur::Context& ctx)
{
    ur::ClearState clear;
    clear.buffers = ur::ClearBuffers::ColorBuffer;
    clear.color.FromRGBA(0);
    ctx.Clear(clear);
}

}