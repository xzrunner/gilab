#include "gilab/Node.h"
#include "gilab/RenderAdapter.h"

#include <blueprint/Pin.h>
#include <blueprint/BackendAdapter.h>

#include <dag/Node.h>
#include <gigraph/Component.h>

namespace gilab
{

Node::Node(const std::string& title)
    : bp::Node(title)
{
}

Node::~Node() = default;

void Node::InitPins(const std::string& name)
{
	auto back2front = [](const dag::Node<gigraph::ParamType>::Port& back) -> bp::PinDesc
	{
        bp::PinDesc front;

        front.type = RenderAdapter::TypeBackToFront(back.var.type);
        //const_cast<gigraph::Component::Port&>(back).var.full_name = back.var.type.name;
        front.name = back.var.full_name;

        return front;
	};

    bp::BackendAdapter<gigraph::ParamType>
        trans("gigraph", back2front);
    trans.InitNodePins(*this, name);
}

}