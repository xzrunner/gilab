#include "gilab/Evaluator.h"

#include <gigraph/typedef.h>
#include <gigraph/Evaluator.h>
#include <gigraph/Component.h>

namespace gilab
{

Evaluator::Evaluator()
{
}

void Evaluator::Rebuild(const std::vector<bp::NodePtr>& nodes, 
	                    const bp::BackendGraph<gigraph::ParamType>& eval,
                        const std::shared_ptr<dag::Context>& ctx)
{
	std::vector<gigraph::CompPtr> comps;
    for (auto& node : nodes)
    {
        auto back_node = eval.QueryBackNode(*node);
        if (!back_node) {
            continue;
        }
        assert(back_node);
        auto comp = std::static_pointer_cast<gigraph::Component>(back_node);
        comps.push_back(comp);
    }

    gigraph::Evaluator back_eval;
    back_eval.Rebuild(comps, ctx);
}

}