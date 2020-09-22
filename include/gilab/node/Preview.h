#pragma once

#include "gilab/Node.h"

#include <blueprint/Pin.h>

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

    RTTR_ENABLE(Node)

}; // Preview

}
}