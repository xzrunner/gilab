#pragma once

#include "gilab/Node.h"

#include <gigraph/component/Mesh.h>

namespace gilab
{

void nodes_regist_rttr();

namespace node
{

#define EXE_FILEPATH "gilab/node_def_gen.h"
#include "gilab/node_regist_cfg.h"
#undef EXE_FILEPATH

}

}