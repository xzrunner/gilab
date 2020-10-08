#include "gilab//RenderAdapter.h"
#include "gilab/PinType.h"

#include <blueprint/Pin.h>

#include <gigraph/ParamType.h>

namespace
{

std::vector<std::pair<int, gigraph::ParamType>> PAIR_TYPES = 
{
	{ bp::PIN_ANY_VAR,     gigraph::ParamType::Any },

	{ gilab::PIN_STRING,   gigraph::ParamType::String },

	{ gilab::PIN_MESHES,   gigraph::ParamType::Meshes },
	{ gilab::PIN_MATERIAL, gigraph::ParamType::Material },

	{ gilab::PIN_TEXTURE,  gigraph::ParamType::Texture },
	{ gilab::PIN_SHADER,   gigraph::ParamType::Shader },
};

}

namespace gilab
{

int RenderAdapter::TypeBackToFront(gigraph::ParamType type)
{
    int ret = -1;

	for (auto& pair : PAIR_TYPES) {
		if (pair.second == type) {
			ret = pair.first;
			break;
		}
	}
	assert(ret >= 0);

    return ret;
}

void RenderAdapter::Front2Back(const ur::Device& dev, const bp::Node& front, dag::Node<gigraph::ParamType>& back, const std::string& dir)
{
}

}