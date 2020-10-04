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

void Node::InitProps(const std::string& name)
{
    rttr::type t = rttr::type::get_by_name("gigraph::" + name);
    if (!t.is_valid()) {
        return;
    }

    rttr::variant var = t.create();
    assert(var.is_valid());
    auto back_node = var.get_value<std::shared_ptr<gigraph::ParamType>>();
    auto back_props = t.get_properties();
    auto front_props = get_type().get_properties();
    for (auto& back_prop : back_props)
    {
        for (auto& front_prop : front_props) {
            if (back_prop.get_name() == front_prop.get_name()) {
                front_prop.set_value(*this, back_prop.get_value(var));
                break;
            }
        }
    }
}

}