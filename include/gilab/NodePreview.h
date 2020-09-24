#pragma once

#include <blueprint/BackendGraph.h>

#include <SM_Vector.h>
#include <unirender/typedef.h>
#include <unirender/Device.h>
#include <gigraph/ParamType.h>

namespace ur { class Context; }
namespace n2 { class RenderParams; }
namespace bp { class Node; }

namespace gilab
{

class Evaluator;

class NodePreview
{
public:
    static void Draw(const ur::Device& dev, ur::Context& ctx, const bp::Node& node, 
        const n2::RenderParams& rp, const bp::BackendGraph<gigraph::ParamType>& eval);

private:
    static bool DrawToRT(const ur::Device& dev, ur::Context& ctx, const bp::Node& node, 
        const bp::BackendGraph<gigraph::ParamType>& eval);
    static void DrawFromRT(const ur::Device& dev, ur::Context& ctx,
        const bp::Node& node, const n2::RenderParams& rp, const ur::TexturePtr& tex);

    static void Clear(ur::Context& ctx);

}; // NodePreview

}