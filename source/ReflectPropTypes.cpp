#include "gilab/ReflectPropTypes.h"

#include <unirender/Device.h>

#include <rttr/registration.h>

#define REGIST_ENUM_ITEM(type, name, label) \
    rttr::value(name, type),                \
    rttr::metadata(type, label)             \


RTTR_REGISTRATION
{

rttr::registration::enumeration<ur::Device::TextureSamplerType>("ur_tex_sampler")
(
    REGIST_ENUM_ITEM(ur::Device::TextureSamplerType::NearestClamp,   "nearest_clamp",  "NearestClamp"),
    REGIST_ENUM_ITEM(ur::Device::TextureSamplerType::LinearClamp,    "linear_clamp",   "LinearClamp"),
    REGIST_ENUM_ITEM(ur::Device::TextureSamplerType::NearestRepeat,  "nearest_repeat", "NearestRepeat"),
    REGIST_ENUM_ITEM(ur::Device::TextureSamplerType::LinearRepeat,   "linear_repeat",  "LinearRepeat")
);

}

namespace gilab
{

void prop_types_regist_rttr()
{
}

}