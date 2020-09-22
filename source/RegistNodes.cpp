#include "gilab/RegistNodes.h"
#include "gilab/node/Preview.h"

#include <ee0/ReflectPropTypes.h>

#include <js/RTTR.h>

#define REGIST_NODE_RTTI(type, name, prop)                        \
	rttr::registration::class_<gilab::node::type>("gilab::"#name) \
		.constructor<>()                                          \
		prop                                                      \
	;

#define PROP
#define REGIST_NODE_RTTI_DEFAULT(type, name) REGIST_NODE_RTTI(type, name, PROP)

RTTR_REGISTRATION
{

// base

rttr::registration::class_<gilab::Node>("gilab::node")
.property("name", &gilab::Node::GetName, &gilab::Node::SetName)
(
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Name"))
)
;

#define EXE_FILEPATH "gilab/node_rttr_gen.h"
#define SKIP_FILE_NODE
#include "gilab/node_regist_cfg.h"
#undef SKIP_FILE_NODE
#undef EXE_FILEPATH

// renderlab
REGIST_NODE_RTTI_DEFAULT(Preview, preview)

}

namespace gilab
{

void nodes_regist_rttr()
{
}

}