#pragma once

#include <blueprint/typedef.h>
#include <blueprint/BackendGraph.h>

#include <gigraph/ParamType.h>

#include <boost/noncopyable.hpp>

#include <vector>

namespace gigraph { class Component; }

namespace gilab
{

class RenderContext;

class Evaluator : boost::noncopyable
{
public:
    Evaluator();

    void Rebuild(const std::vector<bp::NodePtr>& nodes,
        const bp::BackendGraph<gigraph::ParamType>& eval,
        const std::shared_ptr<dag::Context>& ctx);

    void Draw(const std::shared_ptr<dag::Context>& ctx) const;

private:
    std::shared_ptr<gigraph::Component> m_draw_node = nullptr;

}; // Evaluator

}