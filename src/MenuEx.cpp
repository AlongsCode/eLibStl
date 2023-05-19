#include "EcontrolHelp.h"

class CMenu
{
public:
	HMENU m_hMenu = NULL;
	BOOL m_bDeleteMenu = FALSE;

	std::vector<HBITMAP> m_HbmNeedDelete{};// 菜单被销毁时位图不会被删除，还需要额外维护

	CMenu()
	{

	}

	~CMenu()
	{
		if (m_bDeleteMenu)
			DestroyMenu(m_hMenu);
		for (HBITMAP hbm : m_HbmNeedDelete)
			DeleteObject(hbm);
	}
};


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
		/*arg lp*/  NULL,},ESTLFNAME(libstl_MenuEx_Constructor) };

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
		/*arg lp*/  NULL,},ESTLFNAME(libstl_MenuEx_Destructor) };

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
		/*arg lp*/  NULL,},ESTLFNAME(libstl_MenuEx_Copy) };

EXTERN_C void libstl_MenuEx_Attach(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	p->m_hMenu = (HMENU)pArgInf[1].m_int;
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
		/*arg lp*/  s_Args_Attach},ESTLFNAME(libstl_MenuEx_Attach) };

EXTERN_C void libstl_MenuEx_Detach(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	pRetData->m_int = (int)p->m_hMenu;
	p->m_hMenu = NULL;
}
FucInfo Fn_MenuDetach = { {
		/*ccname*/  "拆离句柄",
		/*egname*/  "Detach",
		/*explain*/ "拆离对象持有的菜单，返回菜单句柄。",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_Detach) };

EXTERN_C void libstl_MenuEx_SetDelFlag(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	p->m_bDeleteMenu = pArgInf[1].m_bool;
}
static ARG_INFO s_Args_SetDelFlag[] =
{
	{"对象析构时是否销毁菜单", "", 0, 0, SDT_BOOL, 0, NULL}
};
FucInfo Fn_MenuSetDelFlag = { {
		/*ccname*/  "置回收标志",
		/*egname*/  "SetDelFlag",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   0,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetDelFlag),
		/*arg lp*/  s_Args_SetDelFlag},ESTLFNAME(libstl_MenuEx_SetDelFlag) };

EXTERN_C void libstl_MenuEx_InsertItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STRING | MIIM_STATE;
	mii.dwTypeData = (PWSTR)elibstl::args_to_pszw(pArgInf, 1);
	mii.fState = pArgInf[4].m_int;
	if (pArgInf[5].m_dtDataType != _SDT_NULL)
	{
		mii.fMask |= MIIM_ID;
		mii.wID = pArgInf[5].m_int;
	}

	if (pArgInf[6].m_dtDataType != _SDT_NULL || !pArgInf[7].m_int)
	{
		mii.fMask |= MIIM_SUBMENU;
		mii.hSubMenu = (HMENU)pArgInf[6].m_int;
	}

	if (pArgInf[7].m_dtDataType != _SDT_NULL)
	{
		mii.fMask |= MIIM_DATA;
		mii.dwItemData = pArgInf[7].m_int;
	}

	if (pArgInf[8].m_dtDataType != _SDT_NULL)
	{
		mii.fMask |= MIIM_BITMAP;
		if (pArgInf[8].m_dtDataType == SDT_INT)
			mii.hbmpItem = (HBITMAP)pArgInf[8].m_int;
		else if (pArgInf[8].m_dtDataType == SDT_BIN)
		{
			HBITMAP hbm = elibstl::make_hbm_gp(
				elibstl::get_array_data_base(pArgInf[8].m_pBin),
				elibstl::get_array_count(pArgInf[8].m_pBin));
			if (!hbm)
			{
				pRetData->m_bool = FALSE;
				return;
			}
			mii.hbmpItem = hbm;
		}
		else
		{
			pRetData->m_bool = FALSE;
			return;
		}
	}

	int iPos;
	BOOL bIndex;
	if (pArgInf[2].m_dtDataType == _SDT_NULL)
	{
		iPos = GetMenuItemCount(p->m_hMenu);
		bIndex = TRUE;
	}
	else if (pArgInf[2].m_int < 0 && pArgInf[3].m_bool)
	{
		iPos = GetMenuItemCount(p->m_hMenu);
		bIndex = TRUE;
	}
	else
	{
		iPos = pArgInf[2].m_int;
		bIndex = pArgInf[3].m_bool;
	}

	pRetData->m_bool = InsertMenuItemW(p->m_hMenu, iPos, bIndex, &mii);
}
static ARG_INFO s_Args_InsertItem[] =
{
	{"标题", "", 0, 0, SDT_BIN, 0, 0},
	{"插入位置", "以下两种情况下将插入到菜单末尾：1)该参数为空；2)参数三为真且该参数为负数", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"状态", "#菜单项状态_ 常量，使用 位或() 命令组合状态", 0, 0, SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"ID", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"子菜单句柄", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"自定义数值", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"位图句柄", "指定一个位图句柄或图片字节集或 #菜单预设位图_ 常量。"
			"注意：1)有大量图片需要被复用时不应传递字节集，这会导致性能问题；"
			"2)若本参数传递了字节集，则菜单Ex对象的生命周期必须持续到菜单被销毁之后，因为本对象内部维护位图句柄。", 0, 0, _SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
};
FucInfo Fn_MenuInsertItem = { {
		/*ccname*/  "插入项目",
		/*egname*/  "InsertItem",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_InsertItem),
		/*arg lp*/  s_Args_InsertItem},ESTLFNAME(libstl_MenuEx_InsertItem) };

EXTERN_C void libstl_MenuEx_CreatePopupMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	HMENU hMenu = CreatePopupMenu();
	if(pArgInf[1].m_bool)
	{
		if (p->m_bDeleteMenu)
			DestroyMenu(p->m_hMenu);
		p->m_hMenu = hMenu;
	}
	pRetData->m_int = (int)hMenu;
}
static ARG_INFO s_Args_CreatePopupMenu[] =
{
	{"是否依附", "", 0, 0, SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE}
};
FucInfo Fn_MenuCreatePopupMenu = { {
		/*ccname*/  "创建弹出式菜单",
		/*egname*/  "CreatePopupMenu",
		/*explain*/ "创建一个弹出式菜单，成功返回菜单句柄，失败返回0",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_CreatePopupMenu),
		/*arg lp*/  s_Args_CreatePopupMenu},ESTLFNAME(libstl_MenuEx_CreatePopupMenu) };

EXTERN_C void libstl_MenuEx_GetCurrentMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	pRetData->m_int = (int)p->m_hMenu;
	p->m_hMenu = NULL;
}
FucInfo Fn_MenuGetCurrentMenu = { {
		/*ccname*/  "取当前菜单句柄",
		/*egname*/  "GetCurrentMenu",
		/*explain*/ "返回菜单句柄",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_GetCurrentMenu) };

EXTERN_C void libstl_MenuEx_DeleteItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	DeleteMenu(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_int ? MF_BYPOSITION : MF_BYCOMMAND);
}
static ARG_INFO s_Args_DeleteItem[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuDeleteItem = { {
		/*ccname*/  "插入项目",
		/*egname*/  "DeleteItem",
		/*explain*/ "成功返回真，失败返回假",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_DeleteItem),
		/*arg lp*/  s_Args_DeleteItem},ESTLFNAME(libstl_MenuEx_DeleteItem) };

EXTERN_C void libstl_MenuEx_GetCount(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	pRetData->m_int = GetMenuItemCount(p->m_hMenu);
}
FucInfo Fn_MenuGetCount = { {
		/*ccname*/  "取项目数",
		/*egname*/  "GetCount",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_GetCount) };

EXTERN_C void libstl_MenuEx_GetCaption(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = NULL;
	mii.cch = 0;
	GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
	if (!mii.cch)
	{
		pRetData->m_pBin = NULL;
		return;
	}
	pRetData->m_pBin = elibstl::malloc_wstring(mii.cch);
	mii.dwTypeData = (PWSTR)(pRetData->m_pBin + 8);
	mii.cch++;
	GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
}
static ARG_INFO s_Args_GetCaption[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetCaption = { {
		/*ccname*/  "取标题",
		/*egname*/  "GetCaption",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetCaption),
		/*arg lp*/  s_Args_GetCaption},ESTLFNAME(libstl_MenuEx_GetCaption) };

EXTERN_C void libstl_MenuEx_SetCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	CheckMenuItem(p->m_hMenu, pArgInf[1].m_int,
		(pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND) |
		(pArgInf[3].m_bool ? MF_CHECKED : MF_UNCHECKED));
}
static ARG_INFO s_Args_SetCheck[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"是否选中", "", 0, 0, SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuSetCheck = { {
		/*ccname*/  "置选中状态",
		/*egname*/  "SetCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetCheck),
		/*arg lp*/  s_Args_SetCheck},ESTLFNAME(libstl_MenuEx_SetCheck) };

EXTERN_C void libstl_MenuEx_GetCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	pRetData->m_bool = elibstl::IsBitExist(
		GetMenuState(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND),
		MF_CHECKED);
}
static ARG_INFO s_Args_GetCheck[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"是否选中", "", 0, 0, SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuGetCheck = { {
		/*ccname*/  "取选中状态",
		/*egname*/  "GetCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetCheck),
		/*arg lp*/  s_Args_GetCheck},ESTLFNAME(libstl_MenuEx_GetCheck) };

EXTERN_C void libstl_MenuEx_SetRadioCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	if (pArgInf[5].m_bool)
		pRetData->m_bool = CheckMenuRadioItem(p->m_hMenu, pArgInf[2].m_int, pArgInf[3].m_int, pArgInf[1].m_int,
			(pArgInf[4].m_bool ? MF_BYPOSITION : MF_BYCOMMAND));
	else
	{
		MENUITEMINFOW mii;
		mii.cbSize = sizeof(mii);
		mii.fMask = MIIM_STATE | MIIM_FTYPE;
		GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
		mii.fState &= (~MFS_DEFAULT);
		mii.fType &= (~MFT_RADIOCHECK);
		pRetData->m_bool = SetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
	}
}
static ARG_INFO s_Args_SetRadioCheck[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"互斥范围起始位置", "", 0, 0, SDT_INT, 0, 0},
	{"互斥范围结束位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"是否选中", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuSetRadioCheck = { {
		/*ccname*/  "置单选状态",
		/*egname*/  "SetRadioCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetRadioCheck),
		/*arg lp*/  s_Args_SetRadioCheck},ESTLFNAME(libstl_MenuEx_SetRadioCheck) };

EXTERN_C void libstl_MenuEx_GetRadioCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_FTYPE;
	GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);

	pRetData->m_bool =
		elibstl::IsBitExist(
			GetMenuState(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND),
			MF_CHECKED) &&
		elibstl::IsBitExist(mii.fType, MFT_RADIOCHECK);
}
static ARG_INFO s_Args_GetRadioCheck[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetRadioCheck = { {
		/*ccname*/  "取单选状态",
		/*egname*/  "GetRadioCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetRadioCheck),
		/*arg lp*/  s_Args_GetRadioCheck},ESTLFNAME(libstl_MenuEx_GetRadioCheck) };

EXTERN_C void libstl_MenuEx_SetDefault(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STATE;
	GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
	if (pArgInf[3].m_bool)
		mii.fState |= MFS_DEFAULT;
	else
		mii.fState &= (~MFS_DEFAULT);
	pRetData->m_bool = SetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
}
static ARG_INFO s_Args_SetDefault[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"是否默认", "", 0, 0, SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuSetDefault = { {
		/*ccname*/  "置默认状态",
		/*egname*/  "SetDefault",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetDefault),
		/*arg lp*/  s_Args_SetDefault},ESTLFNAME(libstl_MenuEx_SetDefault) };

EXTERN_C void libstl_MenuEx_GetDefault(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STATE;
	GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
	pRetData->m_bool = elibstl::IsBitExist(mii.fState, MFS_DEFAULT);
}
static ARG_INFO s_Args_GetDefault[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetDefault = { {
		/*ccname*/  "取默认状态",
		/*egname*/  "GetDefault",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetDefault),
		/*arg lp*/  s_Args_GetDefault},ESTLFNAME(libstl_MenuEx_GetDefault) };

EXTERN_C void libstl_MenuEx_SetDisable(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	pRetData->m_bool = EnableMenuItem(p->m_hMenu, pArgInf[1].m_int,
		(pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND) |
		(pArgInf[3].m_bool ? (pArgInf[4].m_bool ? MF_GRAYED : MF_DISABLED) : MF_ENABLED));
}
static ARG_INFO s_Args_SetDisable[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"是否禁止", "", 0, 0, SDT_BOOL, 0, 0},
	{"是否灰色", "若此参数为假，则仅禁用项目，而不改变项目的外观，仅当 是否禁止 参数为真时有效", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuSetDisable = { {
		/*ccname*/  "置禁止状态",
		/*egname*/  "SetDisable",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetDisable),
		/*arg lp*/  s_Args_SetDisable},ESTLFNAME(libstl_MenuEx_SetDisable) };

EXTERN_C void libstl_MenuEx_GetDisable(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<CMenu>(pArgInf);

	UINT uState = GetMenuState(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND);
	if (elibstl::IsBitExist(uState, MFS_GRAYED))
		pRetData->m_int = 2;
	else if (elibstl::IsBitExist(uState, MFS_DISABLED))
		pRetData->m_int = 1;
	else
		pRetData->m_int = 0;
}
static ARG_INFO s_Args_GetDisable[] =
{
	{"位置", "", 0, 0, SDT_INT, 0, 0},
	{"位置是否为索引", "", 0, 0, SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetDisable = { {
		/*ccname*/  "取禁止状态",
		/*egname*/  "GetDisable",
		/*explain*/ "返回值定义：0 - 常规  1 - 禁用  2 - 禁用且灰色",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetDisable),
		/*arg lp*/  s_Args_GetDisable},ESTLFNAME(libstl_MenuEx_GetDisable) };














static int s_Cmd_MenuEx[] = { 196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215 };
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