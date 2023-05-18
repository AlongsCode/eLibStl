#include "EcontrolHelp.h"

class CMenu
{
public:
	HMENU m_hMenu = NULL;
	BOOL m_bDeleteMenu = FALSE;
};


static int s_Cmd_MenuEx[] = { 196,197,198,199 };
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
		/*state*/   CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED,
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
		p->~CMenu();
		operator delete(p);
	}
	p = NULL;
}
FucInfo Fn_MenuDestructor = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   CT_IS_OBJ_FREE_CMD | CT_IS_HIDED,
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
		/*state*/   CT_IS_OBJ_COPY_CMD | CT_IS_HIDED,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},libstl_MenuEx_Copy,"libstl_MenuEx_Copy" };

EXTERN_C void libstl_MenuEx_Attach(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

}
static ARG_INFO s_Args_Attach[] =
{
	{"菜单句柄", "", 0, 0, SDT_INT, 0, NULL}
};
FucInfo Fn_MenuAttach = { {
		/*ccname*/  "依附句柄",
		/*egname*/  "Attach",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   0,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_Attach),
		/*arg lp*/  s_Args_Attach},libstl_MenuEx_Attach,"libstl_MenuEx_Attach" };

EXTERN_C void libstl_MenuEx_Insert(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);


	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);


	InsertMenuItemW(p->m_hMenu, pArgInf[2].m_int, pArgInf[3].m_bool,)


}
static ARG_INFO s_Args_Insert[] =
{
	{"标题", "", 0, 0, SDT_BIN, 0, 0},
	{"插入位置", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"插入位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"状态", "", 0, 0, SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"ID", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"子菜单句柄", "", 0, 0, SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"自定义数值", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
};
FucInfo Fn_MenuInsert = { {
		/*ccname*/  "依附句柄",
		/*egname*/  "Insert",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   0,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_Insert),
		/*arg lp*/  s_Args_Insert},libstl_MenuEx_Insert,"libstl_MenuEx_Insert" };



ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO ClMenu =
{
	"菜单Ex",
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