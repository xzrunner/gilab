#include "gilab/GILab.h"
#include "gilab/PinCallback.h"
#include "gilab/Node.h"
#include "gilab/RegistNodes.h"
#include "gilab/ReflectPropTypes.h"

#include <blueprint/node/Commentary.h>

#include <gigraph/GIGraph.h>

namespace bp
{
extern void regist_sm_rttr();
extern void regist_pt0_rttr();
}

namespace gilab
{

CU_SINGLETON_DEFINITION(GILab);

GILab::GILab()
{
    gigraph::GIGraph::Instance();

    RegistRTTR();

	Init();
	InitNodes();

    InitPinCallback();
}

void GILab::RegistRTTR()
{
    bp::regist_sm_rttr();
    bp::regist_pt0_rttr();

    prop_types_regist_rttr();
    nodes_regist_rttr();
}

void GILab::Init()
{
	//bp::NodeBuilder::Callback cb;
	//cb.on_created = [](bp::Node& node, std::vector<n0::SceneNodePtr>& nodes) {
	//	NodeBuilder::CreateDefaultInputs(nodes, node);
	//};
	//cb.on_connecting = [](bp::Pin& from, bp::Pin& to) {
	//	NodeHelper::RemoveDefaultNode(to);
	//};
	//cb.on_connected = [](bp::Pin& from, bp::Pin& to) {
 //       TypeDeduction::DeduceConn(from, to);
	//};
 //   cb.on_disconnected = [](bp::Pin& from, bp::Pin& to) {
 //       TypeDeduction::DeduceNode(from.GetParent());
 //       TypeDeduction::DeduceNode(to.GetParent());
 //   };
	//bp::NodeBuilder::Instance()->RegistCB(cb);
}

void GILab::InitNodes()
{
    const int bp_count = 1;

	auto list = rttr::type::get<Node>().get_derived_classes();
	m_nodes.reserve(bp_count + list.size());

    m_nodes.push_back(std::make_shared<bp::node::Commentary>());

	for (auto& t : list)
	{
		auto obj = t.create();
		assert(obj.is_valid());
		auto node = obj.get_value<bp::NodePtr>();
		assert(node);
		m_nodes.push_back(node);
	}
}

}