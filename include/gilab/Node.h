#pragma once

#include <blueprint/Node.h>

namespace gilab
{

class Node : public bp::Node
{
public:
    Node(const std::string& title);
    virtual ~Node();

protected:
    void InitPins(const std::string& name);
    void InitProps(const std::string& name);

    RTTR_ENABLE(bp::Node)

}; // Node

}