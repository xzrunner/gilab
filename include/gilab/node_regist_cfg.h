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

#define PARM_NODE_CLASS Shader
#define PARM_NODE_NAME shader
#include EXE_FILEPATH

#undef NODES_GROUP_NAME

// tool

#define NODES_GROUP_NAME Tool

#define PARM_NODE_CLASS Scene
#define PARM_NODE_NAME scene
#include EXE_FILEPATH

#define PARM_NODE_CLASS String
#define PARM_NODE_NAME string
#define PARM_CODE_EDIT
#include EXE_FILEPATH

#undef NODES_GROUP_NAME

// pathtrace

#define NODES_GROUP_NAME PathTrace

#define NO_PARM_FILEPATH
#define PARM_NODE_CLASS BRDF
#define PARM_NODE_NAME brdf
#define PARM_NODE_BASE String
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_CLASS Glass
#define PARM_NODE_NAME glass
#define PARM_NODE_BASE String
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_CLASS PathTrace
#define PARM_NODE_NAME pathtrace
#define PARM_NODE_BASE String
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_CLASS Vertex
#define PARM_NODE_NAME vertex
#define PARM_NODE_BASE String
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_CLASS Progressive
#define PARM_NODE_NAME progressive
#define PARM_NODE_BASE String
#include EXE_FILEPATH

#undef NODES_GROUP_NAME
