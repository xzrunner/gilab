#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_NODE_CLASS
#error "You must define PARM_NODE_CLASS macro before include this file"
#endif

#ifndef PARM_NODE_NAME
#error "You must define PARM_NODE_NAME macro before include this file"
#endif

#ifndef PARM_FILEPATH
#define PARM_FILEPATH gigraph/component/##PARM_NODE_CLASS##.parm.h
#endif

#ifndef PARM_NODE_BASE
#define PARM_NODE_BASE Node
#endif // PARM_NODE_BASE

class PARM_NODE_CLASS : public PARM_NODE_BASE
{
public:
	PARM_NODE_CLASS(const std::string& title = XSTR(PARM_NODE_CLASS))
        : PARM_NODE_BASE(title)
	{
        InitPins(XSTR(PARM_NODE_NAME));
        InitProps(XSTR(PARM_NODE_NAME));
#ifdef ENABLE_PREVIEW
        SetPreview(true);
#else
        //SetPreview(false);
#endif // ENABLE_PREVIEW

#ifdef NODES_GROUP_NAME
        SetGroup(XSTR(NODES_GROUP_NAME));
#endif // NODES_GROUP_NAME
	}

#define PARAM_INFO(id, type, name, member, default_val) \
    type member = type##default_val;
#ifndef NO_PARM_FILEPATH
#include XSTR(PARM_FILEPATH)
#endif // NO_PARM_FILEPATH
#undef  PARAM_INFO

	RTTR_ENABLE(PARM_NODE_BASE)
};

#undef PARM_NODE_CLASS
#undef PARM_NODE_NAME
#undef PARM_NODE_BASE

#undef NO_PARM_FILEPATH
#undef ENABLE_PREVIEW