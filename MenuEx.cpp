#include "include/EcontrolHelp.h"
#include "include/elib/krnllib.h"

class CMenu
{
public:
	HMENU m_hMenu;
};


static int s_Cmd_MenuEx[] = { 0 };





EXTERN_C void libstl_MenuEx_Constructor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& p = elibstl::args_to_obj<CMenu>(pArgInf);
	p = new CMenu;
}
FucInfo Fn_MenuConstructor = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   CT_IS_OBJ_CONSTURCT_CMD,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},libstl_MenuEx_Constructor,"libstl_MenuEx_Constructor" };

EXTERN_C void libstl_MenuEx_Destructor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& p = elibstl::args_to_obj<CMenu>(pArgInf);
	if (p)
	{
		delete p;
		//self->~eMideaPlay();
		//operator delete(p);
	}
	p = NULL;
}
FucInfo Fn_MenuDestructor = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   CT_IS_OBJ_FREE_CMD,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},libstl_MenuEx_Destructor,"libstl_MenuEx_Destructor" };

EXTERN_C void libstl_MenuEx_Copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

}
FucInfo Fn_MenuCopy = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   CT_IS_OBJ_COPY_CMD,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},libstl_MenuEx_Copy,"libstl_MenuEx_Copy" };



ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO ClMenu =
{
	"²Ëµ¥Ex",
	"MenuEx",
	"",
	ARRAYSIZE(s_Cmd_MenuEx),
	s_Cmd_MenuEx,
	_DT_OS(__OS_WIN),
	0,
	0,
	NULL,
	0,
	NULL,
	NULL,
	0,
	NULL
};
ESTL_NAMESPACE_END