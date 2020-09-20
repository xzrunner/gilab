#pragma once

#include <blueprint/typedef.h>
#include <blueprint/BackendGraph.h>

#include <gigraph/ParamType.h>

#include <boost/noncopyable.hpp>

#include <vector>

namespace gilab
{

class Evaluator : boost::noncopyable
{
public:
    Evaluator();

    void Rebuild(const std::vector<bp::NodePtr>& nodes,
        const bp::BackendGraph<gigraph::ParamType>& eval);

}; // Evaluator

}