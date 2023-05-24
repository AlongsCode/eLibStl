#include "EcontrolHelp.h"

#define SCID_MENU 20230520'01u

ESTL_NAMESPACE_BEGIN
typedef int(__stdcall* MENU_EVENT_PROC)(int iID);
enum MENU_EVENT_RET
{
	SKIPDEF = 0,
	DODEF = 1
};
class CMenu
{
private:
	static LRESULT CALLBACK MenuWndSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CMenu*)dwRefData;
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == 0 && lParam == 0 && p->m_pProc)
			{
				if (p->m_pProc(LOWORD(wParam)) == SKIPDEF)
					return 0;
			}
			break;

		case WM_DESTROY:
			p->RemoveEventReceiver();
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	HMENU m_hMenu = NULL;
	BOOL m_bDeleteMenu = TRUE;
	BOOL m_bCopyed = FALSE;

	std::vector<HBITMAP> m_HbmNeedDelete{};// �˵�������ʱλͼ���ᱻɾ��������Ҫ����ά��
	MENU_EVENT_PROC m_pProc = NULL;
	HWND m_hWnd = NULL;

	CMenu()
	{

	}

	~CMenu()
	{
		if (m_bCopyed)
			return;
		RemoveEventReceiver();
		if (m_bDeleteMenu)
			DestroyMenu(m_hMenu);
		for (HBITMAP hbm : m_HbmNeedDelete)
			DeleteObject(hbm);
	}

	eStlInline BOOL IsHbmError()
	{
		return !m_bCopyed && !m_bDeleteMenu && m_HbmNeedDelete.size();
	}

	eStlInline void Attach(HMENU hMenu)
	{
		if (IsHbmError())
			elibstl::NotifySys(NRS_RUNTIME_ERR, (DWORD)"�˵�Ex�������˵�ʱ������ǰά����λͼ��������ڲ˵���ɾ��֮ǰ�ͷ�", 0);
		this->~CMenu();
		m_hMenu = hMenu;
	}

	void RemoveEventReceiver()
	{
		if (!m_hWnd)
			return;
		RemoveWindowSubclass(m_hWnd, MenuWndSubclassProc, SCID_MENU);
		m_hWnd = NULL;
		m_pProc = NULL;
	}

	BOOL SetEventReceiver(HWND hWnd, MENU_EVENT_PROC pProc)
	{
		if (!pProc)
		{
			RemoveEventReceiver();
			return TRUE;
		}

		if (m_hWnd && m_hWnd != hWnd)
			RemoveWindowSubclass(m_hWnd, MenuWndSubclassProc, SCID_MENU);

		SetWindowSubclass(hWnd, MenuWndSubclassProc, SCID_MENU, (DWORD_PTR)this);
		m_hWnd = hWnd;
		m_pProc = pProc;
		return FALSE;
	}
};
ESTL_NAMESPACE_END


EXTERN_C void libstl_MenuEx_Constructor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& p = elibstl::args_to_obj<elibstl::CMenu>(pArgInf);
	p = new elibstl::CMenu;
}
FucInfo Fn_MenuConstructor = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED,
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},ESTLFNAME(libstl_MenuEx_Constructor) };

EXTERN_C void libstl_MenuEx_Destructor(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& p = elibstl::args_to_obj<elibstl::CMenu>(pArgInf);
	if (p)
	{
		if (p->IsHbmError())
			elibstl::NotifySys(NRS_RUNTIME_ERR, (DWORD)"�˵�Ex����������ʱ������ǰά����λͼ��������ڲ˵���ɾ��֮ǰ�ͷ�", 0);
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
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},ESTLFNAME(libstl_MenuEx_Destructor) };

EXTERN_C void libstl_MenuEx_Copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& pA = elibstl::args_to_obj<elibstl::CMenu>(pArgInf);
	pA = new elibstl::CMenu;
	auto pB = (elibstl::CMenu*)*pArgInf[1].m_ppCompoundData;
	*pA = *pB;
	pA->m_bCopyed = TRUE;
}
FucInfo Fn_MenuCopy = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   CT_IS_OBJ_COPY_CMD | CT_IS_HIDED,
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,},ESTLFNAME(libstl_MenuEx_Copy) };

EXTERN_C void libstl_MenuEx_Attach(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	p->Attach((HMENU)pArgInf[1].m_int);
}
static ARG_INFO s_Args_Attach[] =
{
	{"�˵����", "", 0, 0, DATA_TYPE::SDT_INT, 0, NULL}
};
FucInfo Fn_MenuAttach = { {
		/*ccname*/  "�������",
		/*egname*/  "Attach",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_Attach),
		/*arg lp*/  s_Args_Attach},ESTLFNAME(libstl_MenuEx_Attach) };

EXTERN_C void libstl_MenuEx_Detach(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	if (p->IsHbmError())
		elibstl::NotifySys(NRS_RUNTIME_ERR, (DWORD)"�˵�Ex������˵�ʱ������ǰά����λͼ��������ڲ˵���ɾ��֮ǰ�ͷ�", 0);
	pRetData->m_int = (int)p->m_hMenu;
	p->m_hMenu = NULL;
	p->~CMenu();
	p->m_bCopyed = FALSE;
	p->m_hWnd = NULL;
	p->m_pProc = NULL;
	p->m_HbmNeedDelete.clear();
}
FucInfo Fn_MenuDetach = { {
		/*ccname*/  "������",
		/*egname*/  "Detach",
		/*explain*/ "���������еĲ˵������ز˵������",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_Detach) };

EXTERN_C void libstl_MenuEx_SetDelFlag(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	p->m_bDeleteMenu = pArgInf[1].m_bool;
}
static ARG_INFO s_Args_SetDelFlag[] =
{
	{"��������ʱ�Ƿ����ٲ˵�", "", 0, 0, DATA_TYPE::SDT_BOOL, 0, NULL}
};
FucInfo Fn_MenuSetDelFlag = { {
		/*ccname*/  "�û��ձ�־",
		/*egname*/  "SetDelFlag",
		/*explain*/ NULL,
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetDelFlag),
		/*arg lp*/  s_Args_SetDelFlag},ESTLFNAME(libstl_MenuEx_SetDelFlag) };

EXTERN_C void libstl_MenuEx_InsertItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	int iPos;
	BOOL bIndex;
	if (pArgInf[2].m_dtDataType == DATA_TYPE::_SDT_NULL)
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

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = 0;
	mii.fType = 0;
	if (pArgInf[5].m_dtDataType != DATA_TYPE::_SDT_NULL)// ID
	{
		mii.fMask |= MIIM_ID;
		mii.wID = (UINT)pArgInf[5].m_int;
	}

	if (pArgInf[7].m_dtDataType != DATA_TYPE::_SDT_NULL)// �Զ�����ֵ
	{
		mii.fMask |= MIIM_DATA;
		mii.dwItemData = pArgInf[7].m_int;
	}

	if (pArgInf[10].m_int)// ����
	{
		mii.fMask |= MIIM_FTYPE;
		if (pArgInf[10].m_int == 1)
			mii.fType |= MFT_MENUBREAK;
		else
			mii.fType |= MFT_MENUBARBREAK;
	}

	if (pArgInf[9].m_bool)// �ָ���
	{
		mii.fMask |= MIIM_FTYPE;
		mii.fType |= MFT_SEPARATOR;

		pRetData->m_bool = InsertMenuItemW(p->m_hMenu, iPos, bIndex, &mii);
		return;
	}

	mii.fMask |= (MIIM_STRING | MIIM_STATE);
	mii.dwTypeData = const_cast<PWSTR>(elibstl::args_to_pszw(pArgInf, 1));
	mii.fState = pArgInf[4].m_int;

	if (pArgInf[6].m_dtDataType != DATA_TYPE::_SDT_NULL || pArgInf[7].m_int)// �Ӳ˵�
	{
		mii.fMask |= MIIM_SUBMENU;
		mii.hSubMenu = (HMENU)pArgInf[6].m_int;
	}

	if (pArgInf[8].m_dtDataType != DATA_TYPE::_SDT_NULL)// λͼ
	{
		mii.fMask |= MIIM_BITMAP;
		if (pArgInf[8].m_dtDataType == DATA_TYPE::SDT_INT)
			mii.hbmpItem = (HBITMAP)pArgInf[8].m_int;
		else if (pArgInf[8].m_dtDataType == DATA_TYPE::SDT_BIN)
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
			p->m_HbmNeedDelete.push_back(hbm);
		}
		else
		{
			pRetData->m_bool = FALSE;
			return;
		}
	}

	pRetData->m_bool = InsertMenuItemW(p->m_hMenu, iPos, bIndex, &mii);
}
static ARG_INFO s_Args_InsertItem[] =
{
	{"����", "", 0, 0, DATA_TYPE::SDT_BIN, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"����λ��", "������������½����뵽�˵�ĩβ��1)�ò���Ϊ�գ�2)������Ϊ���Ҹò���Ϊ����", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"״̬", "#�˵���״̬_ ������ʹ�� λ��() �������״̬", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"ID", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"�Ӳ˵����", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"�Զ�����ֵ", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"λͼ���", "ָ��һ��λͼ�����ͼƬ�ֽڼ��� #�˵�Ԥ��λͼ_ ������"
			"ע�⣺1)�д���ͼƬ��Ҫ������ʱ��Ӧ�����ֽڼ�����ᵼ���������⣻"
			"2)���������������ֽڼ�����˵�Ex������������ڱ���������˵�������֮����Ϊ�������ڲ�ά��λͼ�����", 0, 0, DATA_TYPE::_SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"�Ƿ�Ϊ�ָ���", "", 0, 0, DATA_TYPE::SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE},
	{"����ѡ��", "0 - ����  1 - ����һ��  2 - ����һ�в�ʹ�����߷ָ�", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuInsertItem = { {
		/*ccname*/  "������Ŀ",
		/*egname*/  "InsertItem",
		/*explain*/ "�ɹ������棬ʧ�ܷ��ؼ�",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_InsertItem),
		/*arg lp*/  s_Args_InsertItem},ESTLFNAME(libstl_MenuEx_InsertItem) };

EXTERN_C void libstl_MenuEx_CreatePopupMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	HMENU hMenu = CreatePopupMenu();
	if (pArgInf[1].m_bool)
		p->Attach(hMenu);
	pRetData->m_int = (int)hMenu;
}
static ARG_INFO s_Args_CreatePopupMenu[] =
{
	{"�Ƿ�����", "", 0, 0, DATA_TYPE::SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE}
};
FucInfo Fn_MenuCreatePopupMenu = { {
		/*ccname*/  "��������ʽ�˵�",
		/*egname*/  "CreatePopupMenu",
		/*explain*/ "����һ������ʽ�˵����ɹ����ز˵������ʧ�ܷ���0",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_CreatePopupMenu),
		/*arg lp*/  s_Args_CreatePopupMenu},ESTLFNAME(libstl_MenuEx_CreatePopupMenu) };

EXTERN_C void libstl_MenuEx_GetCurrentMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	pRetData->m_int = (int)p->m_hMenu;
	p->m_hMenu = NULL;
}
FucInfo Fn_MenuGetCurrentMenu = { {
		/*ccname*/  "ȡ��ǰ�˵����",
		/*egname*/  "GetCurrentMenu",
		/*explain*/ "���ز˵����",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_GetCurrentMenu) };

EXTERN_C void libstl_MenuEx_DeleteItem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	DeleteMenu(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_int ? MF_BYPOSITION : MF_BYCOMMAND);
}
static ARG_INFO s_Args_DeleteItem[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuDeleteItem = { {
		/*ccname*/  "������Ŀ",
		/*egname*/  "DeleteItem",
		/*explain*/ "�ɹ������棬ʧ�ܷ��ؼ�",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_DeleteItem),
		/*arg lp*/  s_Args_DeleteItem},ESTLFNAME(libstl_MenuEx_DeleteItem) };

EXTERN_C void libstl_MenuEx_GetCount(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	pRetData->m_int = GetMenuItemCount(p->m_hMenu);
}
FucInfo Fn_MenuGetCount = { {
		/*ccname*/  "ȡ��Ŀ��",
		/*egname*/  "GetCount",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_GetCount) };

EXTERN_C void libstl_MenuEx_GetCaption(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

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
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetCaption = { {
		/*ccname*/  "ȡ����",
		/*egname*/  "GetCaption",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetCaption),
		/*arg lp*/  s_Args_GetCaption},ESTLFNAME(libstl_MenuEx_GetCaption) };

EXTERN_C void libstl_MenuEx_SetCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	CheckMenuItem(p->m_hMenu, pArgInf[1].m_int,
		(pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND) |
		(pArgInf[3].m_bool ? MF_CHECKED : MF_UNCHECKED));
}
static ARG_INFO s_Args_SetCheck[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"�Ƿ�ѡ��", "", 0, 0, DATA_TYPE::SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuSetCheck = { {
		/*ccname*/  "��ѡ��״̬",
		/*egname*/  "SetCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetCheck),
		/*arg lp*/  s_Args_SetCheck},ESTLFNAME(libstl_MenuEx_SetCheck) };

EXTERN_C void libstl_MenuEx_GetCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	pRetData->m_bool = elibstl::IsBitExist(
		GetMenuState(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND),
		MF_CHECKED);
}
static ARG_INFO s_Args_GetCheck[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"�Ƿ�ѡ��", "", 0, 0, DATA_TYPE::SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuGetCheck = { {
		/*ccname*/  "ȡѡ��״̬",
		/*egname*/  "GetCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetCheck),
		/*arg lp*/  s_Args_GetCheck},ESTLFNAME(libstl_MenuEx_GetCheck) };

EXTERN_C void libstl_MenuEx_SetRadioCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

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
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"���ⷶΧ��ʼλ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"���ⷶΧ����λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"�Ƿ�ѡ��", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuSetRadioCheck = { {
		/*ccname*/  "�õ�ѡ״̬",
		/*egname*/  "SetRadioCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetRadioCheck),
		/*arg lp*/  s_Args_SetRadioCheck},ESTLFNAME(libstl_MenuEx_SetRadioCheck) };

EXTERN_C void libstl_MenuEx_GetRadioCheck(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

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
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetRadioCheck = { {
		/*ccname*/  "ȡ��ѡ״̬",
		/*egname*/  "GetRadioCheck",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetRadioCheck),
		/*arg lp*/  s_Args_GetRadioCheck},ESTLFNAME(libstl_MenuEx_GetRadioCheck) };

EXTERN_C void libstl_MenuEx_SetDefault(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

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
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"�Ƿ�Ĭ��", "", 0, 0, DATA_TYPE::SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuSetDefault = { {
		/*ccname*/  "��Ĭ��״̬",
		/*egname*/  "SetDefault",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetDefault),
		/*arg lp*/  s_Args_SetDefault},ESTLFNAME(libstl_MenuEx_SetDefault) };

EXTERN_C void libstl_MenuEx_GetDefault(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STATE;
	GetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
	pRetData->m_bool = elibstl::IsBitExist(mii.fState, MFS_DEFAULT);
}
static ARG_INFO s_Args_GetDefault[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetDefault = { {
		/*ccname*/  "ȡĬ��״̬",
		/*egname*/  "GetDefault",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetDefault),
		/*arg lp*/  s_Args_GetDefault},ESTLFNAME(libstl_MenuEx_GetDefault) };

EXTERN_C void libstl_MenuEx_SetDisable(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	pRetData->m_bool = EnableMenuItem(p->m_hMenu, pArgInf[1].m_int,
		(pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND) |
		(pArgInf[3].m_bool ? (pArgInf[4].m_bool ? MF_GRAYED : MF_DISABLED) : MF_ENABLED));
}
static ARG_INFO s_Args_SetDisable[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"�Ƿ��ֹ", "", 0, 0, DATA_TYPE::SDT_BOOL, 0, 0},
	{"�Ƿ��ɫ", "���˲���Ϊ�٣����������Ŀ�������ı���Ŀ����ۣ����� �Ƿ��ֹ ����Ϊ��ʱ��Ч", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuSetDisable = { {
		/*ccname*/  "�ý�ֹ״̬",
		/*egname*/  "SetDisable",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetDisable),
		/*arg lp*/  s_Args_SetDisable},ESTLFNAME(libstl_MenuEx_SetDisable) };

EXTERN_C void libstl_MenuEx_GetDisable(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

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
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetDisable = { {
		/*ccname*/  "ȡ��ֹ״̬",
		/*egname*/  "GetDisable",
		/*explain*/ "����ֵ���壺0 - ����  1 - ����  2 - �����һ�ɫ",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetDisable),
		/*arg lp*/  s_Args_GetDisable},ESTLFNAME(libstl_MenuEx_GetDisable) };

EXTERN_C void libstl_MenuEx_SetHilite(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	pRetData->m_bool = HiliteMenuItem((HWND)pArgInf[3].m_int, p->m_hMenu, pArgInf[1].m_int,
		(pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND) |
		(pArgInf[4].m_bool ? MF_HILITE : MF_UNHILITE));
}
static ARG_INFO s_Args_SetHilite[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"���ھ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"�Ƿ����", "", 0, 0, DATA_TYPE::SDT_BOOL, 0, 0},
};
FucInfo Fn_MenuSetHilite = { {
		/*ccname*/  "�ø���״̬",
		/*egname*/  "SetHilite",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetHilite),
		/*arg lp*/  s_Args_SetHilite},ESTLFNAME(libstl_MenuEx_SetHilite) };

EXTERN_C void libstl_MenuEx_GetHilite(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	UINT uState = GetMenuState(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool ? MF_BYPOSITION : MF_BYCOMMAND);
	pRetData->m_bool = elibstl::IsBitExist(uState, MFS_HILITE);
}
static ARG_INFO s_Args_GetHilite[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuGetHilite = { {
		/*ccname*/  "ȡ����״̬",
		/*egname*/  "GetHilite",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetHilite),
		/*arg lp*/  s_Args_GetHilite},ESTLFNAME(libstl_MenuEx_GetHilite) };

EXTERN_C void libstl_MenuEx_TrackPopupMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	if (!pArgInf[3].m_int)
	{
		pRetData->m_int = 0;
		return;
	}

	UINT uFlags = 0;
	switch (pArgInf[4].m_int)// ˮƽ����
	{
	case 0:uFlags |= TPM_LEFTALIGN; break;
	case 1:uFlags |= TPM_CENTERALIGN; break;
	case 2:uFlags |= TPM_RIGHTALIGN; break;
	}

	switch (pArgInf[5].m_int)// ��ֱ����
	{
	case 0:uFlags |= TPM_TOPALIGN; break;
	case 1:uFlags |= TPM_VCENTERALIGN; break;
	case 2:uFlags |= TPM_BOTTOMALIGN; break;
	}

	switch (pArgInf[6].m_int)// ֪ͨѡ��
	{
	case 0:break;
	case 1:uFlags |= TPM_NONOTIFY; break;
	case 2:uFlags |= TPM_RETURNCMD; break;
	case 3:uFlags |= TPM_NONOTIFY | TPM_RETURNCMD; break;
	}

	// ����ѡ��
	UINT uAnFlags = (UINT)pArgInf[7].m_int;
	if (uAnFlags == 0xFFFFFFFF)
		uFlags |= TPM_NOANIMATION;
	else
	{
		if (elibstl::IsBitExist(uAnFlags, 1))
			uFlags |= TPM_VERPOSANIMATION;
		if (elibstl::IsBitExist(uAnFlags, 2))
			uFlags |= TPM_VERNEGANIMATION;
		if (elibstl::IsBitExist(uAnFlags, 4))
			uFlags |= TPM_HORPOSANIMATION;
		if (elibstl::IsBitExist(uAnFlags, 8))
			uFlags |= TPM_HORNEGANIMATION;
	}

	pRetData->m_int = TrackPopupMenu(p->m_hMenu, uFlags, pArgInf[1].m_int, pArgInf[2].m_int, 0, (HWND)pArgInf[3].m_int, NULL);
}
static ARG_INFO s_Args_TrackPopupMenu[] =
{
	{"����λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"����λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"���ھ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"ˮƽ����", "0 - ��  1 - ����  2 - ��", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"��ֱ����", "0 - ��  1 - ����  2 - ��", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"֪ͨѡ��", "0 - ����  1 - ��֪ͨ������  2 - ����ѡ����ĿID  3 - ��֪ͨ�������ҷ���ѡ����ĿID", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"����ѡ��", "0 - ����  -1 - ��ֹ����  1 - ���ϵ���  2 - ���µ���  4 - ������  8 - ���ҵ���ʹ�� λ��() �������������", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
	{"��갴��ѡ��", "0 - ���Ҽ���ѡ��  1 - �����ѡ��", 0, 0, DATA_TYPE::SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_MenuTrackPopupMenu = { {
		/*ccname*/  "��������ʽ�˵�",
		/*egname*/  "TrackPopupMenu",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_TrackPopupMenu),
		/*arg lp*/  s_Args_TrackPopupMenu},ESTLFNAME(libstl_MenuEx_TrackPopupMenu) };

EXTERN_C void libstl_MenuEx_SetCaption(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	MENUITEMINFOW mii;
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STRING;
	mii.dwTypeData = const_cast<PWSTR>(elibstl::args_to_pszw(pArgInf, 3));

	SetMenuItemInfoW(p->m_hMenu, pArgInf[1].m_int, pArgInf[2].m_bool, &mii);
}
static ARG_INFO s_Args_SetCaption[] =
{
	{"λ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"λ���Ƿ�Ϊ����", "", 0, 0, DATA_TYPE::SDT_BOOL, TRUE, AS_HAS_DEFAULT_VALUE},
	{"����", "", 0, 0, DATA_TYPE::SDT_BIN, 0, 0},
};
FucInfo Fn_MenuSetCaption = { {
		/*ccname*/  "�ñ���",
		/*egname*/  "SetCaption",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetCaption),
		/*arg lp*/  s_Args_SetCaption},ESTLFNAME(libstl_MenuEx_SetCaption) };

EXTERN_C void libstl_MenuEx_CreateMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	HMENU hMenu = CreateMenu();
	if (pArgInf[1].m_bool)
		p->Attach(hMenu);
	pRetData->m_int = (int)hMenu;
}
static ARG_INFO s_Args_CreateMenu[] =
{
	{"�Ƿ�����", "", 0, 0, DATA_TYPE::SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE}
};
FucInfo Fn_MenuCreateMenu = { {
		/*ccname*/  "����ˮƽ�˵�",
		/*egname*/  "CreateMenu",
		/*explain*/ "����һ��ˮƽ�˵����ɹ����ز˵������ʧ�ܷ���0",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_CreateMenu),
		/*arg lp*/  s_Args_CreateMenu},ESTLFNAME(libstl_MenuEx_CreateMenu) };

EXTERN_C void libstl_MenuEx_SetMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	pRetData->m_bool = SetMenu((HWND)pArgInf[1].m_int, p->m_hMenu);
}
static ARG_INFO s_Args_SetMenu[] =
{
	{"���ھ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0}
};
FucInfo Fn_MenuSetMenu = { {
		/*ccname*/  "�ô��ڲ˵�",
		/*egname*/  "SetMenu",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetMenu),
		/*arg lp*/  s_Args_SetMenu},ESTLFNAME(libstl_MenuEx_SetMenu) };

EXTERN_C void libstl_MenuEx_GetMenu(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	HMENU hMenu = GetMenu((HWND)pArgInf[1].m_int);
	if (pArgInf[2].m_bool)
		p->Attach(hMenu);
	pRetData->m_int = (int)hMenu;
}
static ARG_INFO s_Args_GetMenu[] =
{
	{"���ھ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"�Ƿ�����", "", 0, 0, DATA_TYPE::SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE}
};
FucInfo Fn_MenuGetMenu = { {
		/*ccname*/  "�ô��ڲ˵�",
		/*egname*/  "GetMenu",
		/*explain*/ "���ز˵����",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetMenu),
		/*arg lp*/  s_Args_GetMenu},ESTLFNAME(libstl_MenuEx_GetMenu) };

EXTERN_C void libstl_MenuEx_Reset(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	p->~CMenu();
	p->m_hMenu = NULL;
	p->m_bCopyed = FALSE;
	p->m_hWnd = NULL;
	p->m_pProc = NULL;
	p->m_HbmNeedDelete.clear();
}
FucInfo Fn_MenuReset = { {
		/*ccname*/  "����",
		/*egname*/  "Reset",
		/*explain*/ "��������Ϊ��ʼ״̬������������ı���ձ�־���ڲ�ά����λͼ����Ϥ��ɾ��",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::SDT_INT,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL},ESTLFNAME(libstl_MenuEx_Reset) };

EXTERN_C void libstl_MenuEx_SetEventReceiver(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto p = elibstl::args_to_obj_noref<elibstl::CMenu>(pArgInf);

	if (pArgInf[2].m_dtDataType != DATA_TYPE::SDT_INT && pArgInf[2].m_dtDataType != DATA_TYPE::SDT_SUB_PTR)
	{
		pRetData->m_bool = FALSE;
		return;
	}
	pRetData->m_bool = p->SetEventReceiver((HWND)pArgInf[1].m_int, (elibstl::MENU_EVENT_PROC)pArgInf[2].m_int);
}
static ARG_INFO s_Args_SetEventReceiver[] =
{
	{"���ھ��", "", 0, 0, DATA_TYPE::SDT_INT, 0, 0},
	{"�¼������ӳ���", "ֻ�ܽ��������ͺ��ӳ���ָ���ͣ��ӳ��򷵻�ֵΪ�����ͣ���һ�������Ͳ�����"
			"�ò���Ϊ�˵�ID������0����Ĭ�ϴ�������1ִ��Ĭ�ϴ���", 0, 0, DATA_TYPE::_SDT_ALL, 0, 0}
};
FucInfo Fn_MenuSetEventReceiver = { {
		/*ccname*/  "���¼�������",
		/*egname*/  "SetEventReceiver",
		/*explain*/ "",
		/*category*/-1,
		/*state*/   0,
		/*ret*/		DATA_TYPE::_SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_SetEventReceiver),
		/*arg lp*/  s_Args_SetEventReceiver},ESTLFNAME(libstl_MenuEx_SetEventReceiver) };




static int s_Cmd_MenuEx[] = { 196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,
	220,221,222,223,224,225 };
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO ClMenu =
{
	"�˵�Ex",
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