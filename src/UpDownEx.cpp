#include"EcontrolHelp.h"

#pragma warning(disable:4996)

#define SCID_UPDOWN			20230507'01u
#define SCID_UPDOWNPARENT	20230507'02u

ESTL_NAMESPACE_BEGIN
// 调节器
/*
* 版本1数据布局
*/
#define DATA_VER_UPDOWN_1 1
struct EUPDOWNDATA
{
	int iVer;				// 版本号
	DWORD dwReserved;		// 保留

	int iDirection;			// 方向
	int iMin;				// 最小位置
	int iMax;				// 最大位置
	int iPos;				// 位置
	BOOL bAutoBuddy;		// 自动选择伙伴
	int iBuddyAlign;		// 伙伴窗口定位方式
	int iValueBase;			// 数值进制
	BOOL bHousands;			// 是否插入千分符
	BOOL bArrowKeys;		// 是否由上下箭头控制
	BOOL bHotTrack;			// 是否热点跟踪
};

class CUpDown :public elibstl::CCtrlBaseSimple
{
	SUBCLASS_MGR_DECL(CUpDown)
private:
	EUPDOWNDATA m_Info{};

	eStlInline BOOL OnDeltaPos(int iPos, int iDelta)
	{
		EVENT_NOTIFY Event(m_dwWinFormID, m_dwUnitID, 0);
		Event.m_nArgCount = 2;
		Event.m_nArgValue[0] = iPos;
		Event.m_nArgValue[1] = iDelta;
		elibstl::NotifySys(NRS_EVENT_NOTIFY, (DWORD)&Event, 0);
		return (BOOL)Event.m_nRetVal || !Event.m_blHasRetVal;
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_NOTIFY:
		{
#pragma warning(push)
#pragma warning(disable:26454)// 算术溢出
			if (((NMHDR*)lParam)->code == UDN_DELTAPOS)
			{
				auto pnmud = (NMUPDOWN*)lParam;
				if (m_CtrlSCInfo.count(pnmud->hdr.hwndFrom))
					return !(m_CtrlSCInfo[pnmud->hdr.hwndFrom]->OnDeltaPos(pnmud->iPos, pnmud->iDelta));
			}
#pragma warning(pop)
		}
		break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CUpDown*)dwRefData;
		switch (uMsg)
		{
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CUpDown() = delete;
	CUpDown(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);

		if (pAllData)
		{
			memcpy(&m_Info, (BYTE*)pAllData + cbBaseData, sizeof(EUPDOWNDATA));
		}
		else
		{
			m_Info.bHousands = TRUE;
			m_Info.iMax = 100;
		}
		m_Info.iVer = DATA_VER_UPDOWN_1;

		DWORD dwUDStyle = UDS_SETBUDDYINT |
			elibstl::MultiSelect<DWORD>(m_Info.iBuddyAlign, 0, UDS_ALIGNLEFT | WS_VISIBLE, UDS_ALIGNRIGHT | WS_VISIBLE);
		if (m_Info.bAutoBuddy)
			dwUDStyle |= UDS_AUTOBUDDY;
		if (m_Info.iDirection)
			dwUDStyle |= UDS_HORZ;
		if (m_Info.bArrowKeys)
			dwUDStyle |= UDS_ARROWKEYS;
		if (m_Info.bHotTrack)
			dwUDStyle |= UDS_HOTTRACK;

		m_hWnd = CreateWindowExW(0, UPDOWN_CLASSW, NULL, WS_CLIPSIBLINGS | WS_CHILD | dwUDStyle,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;
		// SetDirection(m_Info.iDirection);
		SetMin(m_Info.iMin);
		SetMax(m_Info.iMax);
		SetAutoBuddy(m_Info.bAutoBuddy);
		// SetBuddyAlign(m_Info.iBuddyAlign);
		SetBase(m_Info.iValueBase);
		SetHousands(m_Info.bHousands);
		// SetArrowKeys(m_Info.bArrowKeys);
		// SetHotTrack(m_Info.bHotTrack);
		SetPos(m_Info.iPos);// 不知道为什么，设置了伙伴窗口之后这个不管用
	}

	eStlInline void SetDirection(int iDirection)
	{
		m_Info.iDirection = iDirection;
	}

	eStlInline int GetDirection()const
	{
		if (m_bInDesignMode)
			return m_Info.iDirection;
		else
			return (int)elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), UDS_HORZ);
	}

	eStlInline void SetMin(int iMin)
	{
		m_Info.iMin = iMin;
		int iMax;
		SendMessageW(m_hWnd, UDM_GETRANGE32, NULL, (LPARAM)&iMax);
		SendMessageW(m_hWnd, UDM_SETRANGE32, iMin, iMax);
	}

	eStlInline void SetMax(int iMax)
	{
		m_Info.iMax = iMax;
		int iMin;
		SendMessageW(m_hWnd, UDM_GETRANGE32, (WPARAM)&iMin, NULL);
		SendMessageW(m_hWnd, UDM_SETRANGE32, iMin, iMax);
	}

	eStlInline void GetRange(int* piMin = NULL, int* piMax = NULL)
	{
		if (m_bInDesignMode)
		{
			if (piMin)
				*piMin = m_Info.iMin;
			if (piMax)
				*piMax = m_Info.iMax;
		}
		else
			SendMessageW(m_hWnd, UDM_GETRANGE32, (WPARAM)piMin, (LPARAM)piMax);
	}

	eStlInline void SetPos(int iPos)
	{
		m_Info.iPos = iPos;
		SendMessageW(m_hWnd, UDM_SETPOS, 0, iPos);
	}

	eStlInline int GetPos()
	{
		if (m_bInDesignMode)
			return m_Info.iPos;
		else
			return SendMessageW(m_hWnd, UDM_GETPOS32, 0, NULL);
	}

	eStlInline void SetAutoBuddy(BOOL bAutoBuddy)
	{
		m_Info.bAutoBuddy = bAutoBuddy;
	}

	eStlInline BOOL GetAutoBuddy() const
	{
		if (m_bInDesignMode)
			return m_Info.bAutoBuddy;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), UDS_AUTOBUDDY);
	}

	eStlInline void SetBuddy(HWND hBuddy)
	{
		SendMessageW(m_hWnd, UDM_SETBUDDY, (WPARAM)hBuddy, 0);
	}

	eStlInline HWND GetBuddy()const
	{
		return (HWND)SendMessageW(m_hWnd, UDM_GETBUDDY, 0, 0);
	}

	eStlInline void SetBuddyAlign(int iAlign)
	{
		m_Info.iBuddyAlign = iAlign;
		elibstl::ModifyWindowStyle(
			m_hWnd,
			elibstl::MultiSelect<DWORD>(iAlign, 0, UDS_ALIGNLEFT, UDS_ALIGNRIGHT),
			UDS_ALIGNLEFT | UDS_ALIGNRIGHT);
	}

	eStlInline int GetBuddyAlign()
	{
		if (m_bInDesignMode)
			return m_Info.iBuddyAlign;
		else
		{
			int i = MultiSelectWndStyle(m_hWnd, UDS_ALIGNLEFT, UDS_ALIGNRIGHT);
			if (i >= 0)
				return i + 1;
			else
				return 0;
		}
	}

	eStlInline void SetBase(int iBase)
	{
		m_Info.iValueBase = iBase;
		SendMessageW(m_hWnd, UDM_SETBASE, (iBase ? 16 : 10), 0);
	}

	eStlInline int GetBase()
	{
		if (m_bInDesignMode)
			return m_Info.iValueBase;
		else
			return (int)(SendMessageW(m_hWnd, UDM_GETBASE, 0, 0) == 16);
	}

	eStlInline void SetHousands(BOOL bHousands)
	{
		m_Info.bHousands = bHousands;
		elibstl::ModifyWindowStyle(m_hWnd, (bHousands ? 0 : UDS_NOTHOUSANDS), UDS_NOTHOUSANDS);
	}

	eStlInline BOOL GetHousands()
	{
		if (m_bInDesignMode)
			return m_Info.bHousands;
		else
			return !elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), UDS_NOTHOUSANDS);
	}

	eStlInline void SetArrowKeys(BOOL bArrowKeys)
	{
		m_Info.bArrowKeys = bArrowKeys;
	}

	eStlInline BOOL GetArrowKeys()
	{
		if (m_bInDesignMode)
			return m_Info.bArrowKeys;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), UDS_ARROWKEYS);
	}

	eStlInline void SetHotTrack(BOOL bHotTrack)
	{
		m_Info.bHotTrack = bHotTrack;
	}

	eStlInline BOOL GetHotTrack()
	{
		if (m_bInDesignMode)
			return m_Info.bHotTrack;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), UDS_HOTTRACK);
	}

	HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(EUPDOWNDATA), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// 结构
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(EUPDOWNDATA));
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto pButton = new CUpDown(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(pButton->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 方向
			p->SetDirection(pPropertyVaule->m_int);
			return TRUE;
		case 1:// 最小位置
			p->SetMin(pPropertyVaule->m_int);
			break;
		case 2:// 最大位置
			p->SetMax(pPropertyVaule->m_int);
			break;
		case 3:// 位置
			p->SetPos(pPropertyVaule->m_int);
			break;
		case 4:// 自动选择伙伴窗口
			p->SetAutoBuddy(pPropertyVaule->m_bool);
			return TRUE;
		case 5:// 伙伴窗口
			p->SetBuddy((HWND)pPropertyVaule->m_int);
			break;
		case 6:// 伙伴窗口定位方式
			p->SetBuddyAlign(pPropertyVaule->m_int);
			return TRUE;
		case 7:// 数值进制
			p->SetBase(pPropertyVaule->m_int);
			break;
		case 8:// 是否插入千分符
			p->SetHousands(pPropertyVaule->m_bool);
			return TRUE;
		case 9:// 是否由上下箭头控制
			p->SetArrowKeys(pPropertyVaule->m_bool);
			return TRUE;
		case 10:// 是否热点跟踪
			p->SetHotTrack(pPropertyVaule->m_bool);
			return TRUE;
		}

		return FALSE;
	}

	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}

	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// 方向
			pPropertyVaule->m_int = p->GetDirection();
			break;
		case 1:// 最小位置
			p->GetRange(&pPropertyVaule->m_int);
			break;
		case 2:// 最大位置
			p->GetRange(NULL, &pPropertyVaule->m_int);
			break;
		case 3:// 位置
			pPropertyVaule->m_int = p->GetPos();
			break;
		case 4:// 自动选择伙伴窗口
			pPropertyVaule->m_bool = p->GetAutoBuddy();
			break;
		case 5:// 伙伴窗口
			pPropertyVaule->m_int = (int)p->GetBuddy();
			break;
		case 6:// 伙伴窗口定位方式
			pPropertyVaule->m_int = p->GetBuddyAlign();
			break;
		case 7:// 数值进制
			pPropertyVaule->m_int = p->GetBase();
			break;
		case 8:// 是否插入千分符
			pPropertyVaule->m_bool = p->GetHousands();
			break;
		case 9:// 是否由上下箭头控制
			pPropertyVaule->m_bool = p->GetArrowKeys();
			break;
		case 10:// 是否热点跟踪
			pPropertyVaule->m_bool = p->GetHotTrack();
			break;
		}

		return TRUE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 18;
			*((int*)dwParam2) = 80;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CUpDown, SCID_UPDOWNPARENT, SCID_UPDOWN)
ESTL_NAMESPACE_END

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_UpDown(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CUpDown::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CUpDown::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CUpDown::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CUpDown::EGetData;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CUpDown::ENotify;
	}
	return NULL;
}

static EVENT_ARG_INFO2 s_Event_Arg[] =
{
	{"当前位置", "", 0, SDT_INT},
	{"建议改变的值", "", 0, SDT_INT},
};
static EVENT_INFO2 s_Event_UpDown[] =
{
	/*000*/ {"调节钮被按下", "当调节钮被按下时触发。返回真允许位置更改，返回假禁止位置更改", _EVENT_OS(OS_ALL) | EV_IS_VER2,
			ARRAYSIZE(s_Event_Arg), s_Event_Arg, SDT_BOOL},
};

static UNIT_PROPERTY s_Member_UpDown[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/  {"方向", "Direction", "该属性改变后控件将重新创建，伙伴窗口需要重新设置（如果有）", UD_PICK_INT, _PROP_OS(OS_ALL),  "纵向\0""横向\0""\0"},
	/*001*/  {"最小位置", "Min", "", UD_INT, _PROP_OS(OS_ALL), NULL},
	/*002*/  {"最大位置", "Max", "", UD_INT, _PROP_OS(OS_ALL), NULL},
	/*003*/  {"位置", "Pos", "若设置了伙伴窗口，则必须在设置之后使用代码赋值", UD_INT, _PROP_OS(OS_ALL), NULL},
	/*004*/  {"自动选择伙伴窗口", "AutoBuddy", "是否自动选择调节器Z序之上的第一个窗口为伙伴窗口。该属性改变后控件将重新创建，伙伴窗口需要重新设置（如果有）", UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*005*/  {"伙伴窗口", "BuddyWindow", "调节器位置将反映在伙伴窗口的标题上", UD_INT, _PROP_OS(OS_ALL) | UW_CANNOT_INIT, NULL},
	/*006*/  {"伙伴窗口定位方式", "BuddyAlign", "该属性改变后控件将重新创建，伙伴窗口需要重新设置（如果有）", UD_PICK_INT, _PROP_OS(OS_ALL), "无\0""左边\0""右边\0""\0"},
	/*007*/  {"数值进制", "Base", "", UD_PICK_INT, _PROP_OS(OS_ALL), "十进制\0""十六进制\0""\0"},
	/*008*/  {"是否插入千分符", "Housands", "该属性改变后控件将重新创建，伙伴窗口需要重新设置（如果有）", UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*009*/  {"是否由上下箭头键控制", "ArrowKeys", "该属性改变后控件将重新创建，伙伴窗口需要重新设置（如果有）", UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*010*/  {"是否热点跟踪", "HotTrack", "该属性改变后控件将重新创建，伙伴窗口需要重新设置（如果有）", UD_BOOL, _PROP_OS(OS_ALL), NULL},
};


static INT s_Cmd_UpDown[] = { 121,181 };
EXTERN_C void libstl_UpDown_SetAccel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	int cAccel = elibstl::get_array_count(pArgInf[1].m_pAryData);
	if (cAccel != elibstl::get_array_count(pArgInf[2].m_pAryData))
	{
		pRetData->m_bool = FALSE;
		return;
	}

	if (cAccel)
	{
		int* pSec = (int*)elibstl::get_array_data_base(pArgInf[1].m_pAryData);
		int* pInc = (int*)elibstl::get_array_data_base(pArgInf[2].m_pAryData);
		auto puda = new UDACCEL[cAccel];
		for (int i = 0; i < cAccel; ++i)
		{
			puda[i].nSec = pSec[i];
			puda[i].nInc = pInc[i];
		}
		pRetData->m_bool = (BOOL)SendMessageW(hWnd, UDM_SETACCEL, cAccel, (LPARAM)puda);
		delete[] puda;
	}
	else
	{
		pRetData->m_bool = (BOOL)SendMessageW(hWnd, UDM_SETACCEL, 0, 0);
	}
}
static ARG_INFO s_ArgsSetAccel[] =
{
	{
		/*name*/    "秒数",
		/*explain*/ "必须按从小到大的顺序排列",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA,
	},
	{
		/*name*/    "增量",
		/*explain*/ "成员数必须与参数一相同，且成员须一一对应",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA,
	}
};
FucInfo Fn_UpDownSetAccel = { {
		/*ccname*/  "置加速度",
		/*egname*/  "SetAccel",
		/*explain*/ "设置按住调节钮后经过指定秒数后的增量",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsSetAccel),
		/*arg lp*/  s_ArgsSetAccel,
	} , libstl_UpDown_SetAccel ,"libstl_UpDown_SetAccel" };

EXTERN_C void libstl_UpDown_GetAccel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	elibstl::free(*pArgInf[2].m_ppAryData);
	elibstl::free(*pArgInf[3].m_ppAryData);

	int cAccel = SendMessageW(hWnd, UDM_GETACCEL, 0, NULL);
	if (!cAccel)
	{
		*pArgInf[2].m_ppAryData = NULL;
		*pArgInf[3].m_ppAryData = NULL;
		pRetData->m_int = 0;
		return;
	}
	int cNeedAccel;
	if (pArgInf[1].m_dtDataType == _SDT_NULL)
		cNeedAccel = cAccel;
	else if (pArgInf[1].m_int <= 0 || pArgInf[1].m_int > cAccel)
		cNeedAccel = cAccel;
	else
		cNeedAccel = pArgInf[1].m_int;

	*pArgInf[2].m_ppAryData = elibstl::malloc_array<int>(cNeedAccel);
	*pArgInf[3].m_ppAryData = elibstl::malloc_array<int>(cNeedAccel);
	int* pSec = (int*)elibstl::get_array_data_base(*pArgInf[2].m_ppAryData);
	int* pInc = (int*)elibstl::get_array_data_base(*pArgInf[3].m_ppAryData);
	auto puda = new UDACCEL[cNeedAccel];
	SendMessageW(hWnd, UDM_GETACCEL, cAccel, (LPARAM)puda);
	for (int i = 0; i < cNeedAccel; ++i)
	{
		pSec[i] = puda[i].nSec;
		pInc[i] = puda[i].nInc;
	}
	delete[] puda;
	pRetData->m_int = cAccel;
}
static ARG_INFO s_ArgsGetAccel[] =
{
	{
		/*name*/    "加速度数量",
		/*explain*/ "若该参数为空或小于等于0或大于实际加速度数量，则返回所有加速度。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "接收秒数变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR_ARRAY,
	},
	{
		/*name*/    "接收增量变量",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR_ARRAY,
	}
};
FucInfo Fn_UpDownGetAccel = { {
		/*ccname*/  "取加速度",
		/*egname*/  "GetAccel",
		/*explain*/ "返回控件实际拥有的加速度数量",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetAccel),
		/*arg lp*/  s_ArgsGetAccel,
	} , libstl_UpDown_GetAccel ,"libstl_UpDown_GetAccel" };

ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO UpDown = {
	"调节器Ex",//中文名称
	"UpDown",//英文名称
	"本控件有诸多属性改变后需要重新创建控件，应尽量在设计时确定属性值",//说明
	ARRAYSIZE(s_Cmd_UpDown),//命令数量
	s_Cmd_UpDown,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_UPDOWN_EX,//资源ID
	ARRAYSIZE(s_Event_UpDown),
	s_Event_UpDown,//事件
	ARRAYSIZE(s_Member_UpDown),//属性数
	s_Member_UpDown,//属性指针
	libstl_GetInterface_UpDown,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END