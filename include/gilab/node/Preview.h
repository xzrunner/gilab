#pragma once

#include "gilab/Node.h"

#include <blueprint/Pin.h>

#include <unirender/Device.h>

namespace gilab
{
namespace node
{

class Preview : public Node
{
public:
    Preview()
        : Node("Preview")
    {
        m_all_input.push_back(std::make_shared<bp::Pin>(
            true, 0, bp::PIN_ANY_VAR, "in", *this
        ));

        Layout();

        SetGroup("Tool");
    }

    const sm::bvec4& GetColorMask() const { return m_color_mask; }
    void SetColorMask(const sm::bvec4& mask) { m_color_mask = mask; }

    auto GetSamplerType() const { return m_sampler_type; }
    void SetSamplerType(ur::Device::TextureSamplerType sampler_type) { m_sampler_type = sampler_type; }

private:
    sm::bvec4 m_color_mask = sm::bvec4(true, true, true, true);

    ur::Device::TextureSamplerType m_sampler_type = ur::Device::TextureSamplerType::LinearClamp;

    RTTR_ENABLE(Node)

}; // Preview

}
}