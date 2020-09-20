#pragma once

#include <dag/Node.h>
#include <gigraph/Param.h>

namespace bp { class Node; }
namespace ur { class Device; }

namespace gilab
{

class RenderAdapter
{
public:
    static int TypeBackToFront(gigraph::ParamType type);

    static void Front2Back(const ur::Device& dev, const bp::Node& front, 
        dag::Node<gigraph::ParamType>& back, const std::string& dir);

}; // RenderAdapter

}