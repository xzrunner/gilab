#ifndef EXE_FILEPATH
#error "You must define EXE_FILEPATH macro before include this file"
#endif

// object

#define NODES_GROUP_NAME Object

#define PARM_NODE_CLASS Mesh
#define PARM_NODE_NAME mesh
#include EXE_FILEPATH

#define PARM_NODE_CLASS Material
#define PARM_NODE_NAME material
#include EXE_FILEPATH

#undef NODES_GROUP_NAME

// operator

#define NODES_GROUP_NAME Operator

#define PARM_NODE_CLASS Transform
#define PARM_NODE_NAME transform
#include EXE_FILEPATH

#undef NODES_GROUP_NAME

// render

#define NODES_GROUP_NAME Render

#define PARM_NODE_CLASS Draw
#define PARM_NODE_NAME draw
#include EXE_FILEPATH

#undef NODES_GROUP_NAME

// tool

#define NODES_GROUP_NAME Tool

#define PARM_NODE_CLASS Scene
#define PARM_NODE_NAME scene
#include EXE_FILEPATH

#undef NODES_GROUP_NAME
