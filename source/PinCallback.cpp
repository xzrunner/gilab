#include "gilab/PinCallback.h"
#include "gilab/PinType.h"

#include <painting0/Color.h>
#include <blueprint/Pin.h>

#include <string>
#include <set>

namespace
{

const pt0::Color COL_DEFAULT   = pt0::Color(255, 255, 255);

const pt0::Color COL_MESHES    = pt0::Color(132, 228, 231);
const pt0::Color COL_MATERIAL  = pt0::Color(132, 228, 131);
const pt0::Color COL_TEXTURE   = pt0::Color(132, 128, 231);

std::string get_desc_func(const std::string& name, int type)
{
    std::string ret = name;
    switch (type)
    {
    case gilab::PIN_MESHES:
        ret += "(M)";
        break;
    case gilab::PIN_MATERIAL:
        ret += "(Mat)";
        break;
    case gilab::PIN_TEXTURE:
        ret += "(T)";
        break;
    }
    return ret;
}

const pt0::Color& get_color_func(int type)
{
    switch (type)
    {
    case gilab::PIN_MESHES:
        return COL_MESHES;
    case gilab::PIN_MATERIAL:
        return COL_MATERIAL;
    case gilab::PIN_TEXTURE:
        return COL_TEXTURE;
    default:
        return COL_DEFAULT;
    }
}

bool can_type_cast_func(int type_from, int type_to)
{
    if (type_from == type_to) {
        return true;
    }
    if (type_from == bp::PIN_ANY_VAR ||
        type_to == bp::PIN_ANY_VAR) {
        return true;
    }

    return false;
}

}

namespace gilab
{

void InitPinCallback()
{
    bp::Pin::SetExtendFuncs({
        get_desc_func,
        get_color_func,
        can_type_cast_func
    });
}

}