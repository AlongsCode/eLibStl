#include"EcontrolHelp.h"

#pragma warning(disable:4996)

#define SCID_UPDOWN			20230507'01u
#define SCID_UPDOWNPARENT	20230507'02u

ESTL_NAMESPACE_BEGIN
// ������
/*
* �汾1���ݲ���
*/
#define DATA_VER_UPDOWN_1 1
struct EUPDOWNDATA
{
	int iVer;				// �汾��
	DWORD dwReserved;		// ����

	int iDirection;			// ����
	int iMin;				// ��Сλ��
	int iMax;				// ���λ��
	int iPos;				// λ��
	BOOL bAutoBuddy;		// �Զ�ѡ����
	int iBuddyAlign;		// ��鴰�ڶ�λ��ʽ
	int iValueBase;			// ��ֵ����
	BOOL bHousands;			// �Ƿ����ǧ�ַ�
	BOOL bArrowKeys;		// �Ƿ������¼�ͷ����
	BOOL bHotTrack;			// �Ƿ��ȵ����
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
#pragma warning(disable:26454)// �������
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
		SetPos(m_Info.iPos);// ��֪��Ϊʲô�������˻�鴰��֮�����������
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
		// �ṹ
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(EUPDOWNDATA));
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CUpDown(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// ����
			p->SetDirection(pPropertyVaule->m_int);
			return TRUE;
		case 1:// ��Сλ��
			p->SetMin(pPropertyVaule->m_int);
			break;
		case 2:// ���λ��
			p->SetMax(pPropertyVaule->m_int);
			break;
		case 3:// λ��
			p->SetPos(pPropertyVaule->m_int);
			break;
		case 4:// �Զ�ѡ���鴰��
			p->SetAutoBuddy(pPropertyVaule->m_bool);
			return TRUE;
		case 5:// ��鴰��
			p->SetBuddy((HWND)pPropertyVaule->m_int);
			break;
		case 6:// ��鴰�ڶ�λ��ʽ
			p->SetBuddyAlign(pPropertyVaule->m_int);
			return TRUE;
		case 7:// ��ֵ����
			p->SetBase(pPropertyVaule->m_int);
			break;
		case 8:// �Ƿ����ǧ�ַ�
			p->SetHousands(pPropertyVaule->m_bool);
			return TRUE;
		case 9:// �Ƿ������¼�ͷ����
			p->SetArrowKeys(pPropertyVaule->m_bool);
			return TRUE;
		case 10:// �Ƿ��ȵ����
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
		case 0:// ����
			pPropertyVaule->m_int = p->GetDirection();
			break;
		case 1:// ��Сλ��
			p->GetRange(&pPropertyVaule->m_int);
			break;
		case 2:// ���λ��
			p->GetRange(NULL, &pPropertyVaule->m_int);
			break;
		case 3:// λ��
			pPropertyVaule->m_int = p->GetPos();
			break;
		case 4:// �Զ�ѡ���鴰��
			pPropertyVaule->m_bool = p->GetAutoBuddy();
			break;
		case 5:// ��鴰��
			pPropertyVaule->m_int = (int)p->GetBuddy();
			break;
		case 6:// ��鴰�ڶ�λ��ʽ
			pPropertyVaule->m_int = p->GetBuddyAlign();
			break;
		case 7:// ��ֵ����
			pPropertyVaule->m_int = p->GetBase();
			break;
		case 8:// �Ƿ����ǧ�ַ�
			pPropertyVaule->m_bool = p->GetHousands();
			break;
		case 9:// �Ƿ������¼�ͷ����
			pPropertyVaule->m_bool = p->GetArrowKeys();
			break;
		case 10:// �Ƿ��ȵ����
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
	{"��ǰλ��", "", 0, DATA_TYPE::SDT_INT},
	{"����ı��ֵ", "", 0, DATA_TYPE::SDT_INT},
};
static EVENT_INFO2 s_Event_UpDown[] =
{
	/*000*/ {"����ť������", "������ť������ʱ����������������λ�ø��ģ����ؼٽ�ֹλ�ø���", _EVENT_OS(OS_ALL) | EV_IS_VER2,
			ARRAYSIZE(s_Event_Arg), s_Event_Arg, DATA_TYPE::SDT_BOOL},
};

static UNIT_PROPERTY s_Member_UpDown[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	/*000*/  {"����", "Direction", "�����Ըı��ؼ������´�������鴰����Ҫ�������ã�����У�", UD_PICK_INT, _PROP_OS(OS_ALL),  "����\0""����\0""\0"},
	/*001*/  {"��Сλ��", "Min", "", UD_INT, _PROP_OS(OS_ALL), NULL},
	/*002*/  {"���λ��", "Max", "", UD_INT, _PROP_OS(OS_ALL), NULL},
	/*003*/  {"λ��", "Pos", "�������˻�鴰�ڣ������������֮��ʹ�ô��븳ֵ", UD_INT, _PROP_OS(OS_ALL), NULL},
	/*004*/  {"�Զ�ѡ���鴰��", "AutoBuddy", "�Ƿ��Զ�ѡ�������Z��֮�ϵĵ�һ������Ϊ��鴰�ڡ������Ըı��ؼ������´�������鴰����Ҫ�������ã�����У�", UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*005*/  {"��鴰��", "BuddyWindow", "������λ�ý���ӳ�ڻ�鴰�ڵı�����", UD_INT, _PROP_OS(OS_ALL) | UW_CANNOT_INIT, NULL},
	/*006*/  {"��鴰�ڶ�λ��ʽ", "BuddyAlign", "�����Ըı��ؼ������´�������鴰����Ҫ�������ã�����У�", UD_PICK_INT, _PROP_OS(OS_ALL), "��\0""���\0""�ұ�\0""\0"},
	/*007*/  {"��ֵ����", "Base", "", UD_PICK_INT, _PROP_OS(OS_ALL), "ʮ����\0""ʮ������\0""\0"},
	/*008*/  {"�Ƿ����ǧ�ַ�", "Housands", "�����Ըı��ؼ������´�������鴰����Ҫ�������ã�����У�", UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*009*/  {"�Ƿ������¼�ͷ������", "ArrowKeys", "�����Ըı��ؼ������´�������鴰����Ҫ�������ã�����У�", UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*010*/  {"�Ƿ��ȵ����", "HotTrack", "�����Ըı��ؼ������´�������鴰����Ҫ�������ã�����У�", UD_BOOL, _PROP_OS(OS_ALL), NULL},
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
		/*name*/    "����",
		/*explain*/ "���밴��С�����˳������",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA,
	},
	{
		/*name*/    "����",
		/*explain*/ "��Ա�����������һ��ͬ���ҳ�Ա��һһ��Ӧ",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_ARRAY_DATA,
	}
};
FucInfo Fn_UpDownSetAccel = { {
		/*ccname*/  "�ü��ٶ�",
		/*egname*/  "SetAccel",
		/*explain*/ "���ð�ס����ť�󾭹�ָ�������������",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     DATA_TYPE::SDT_BOOL,
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
	elibstl::efree(*pArgInf[2].m_ppAryData);
	elibstl::efree(*pArgInf[3].m_ppAryData);

	int cAccel = SendMessageW(hWnd, UDM_GETACCEL, 0, NULL);
	if (!cAccel)
	{
		*pArgInf[2].m_ppAryData = NULL;
		*pArgInf[3].m_ppAryData = NULL;
		pRetData->m_int = 0;
		return;
	}
	int cNeedAccel;
	if (pArgInf[1].m_dtDataType == DATA_TYPE::_SDT_NULL)
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
		/*name*/    "���ٶ�����",
		/*explain*/ "���ò���Ϊ�ջ�С�ڵ���0�����ʵ�ʼ��ٶ��������򷵻����м��ٶȡ�",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������������",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR_ARRAY,
	},
	{
		/*name*/    "������������",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR_ARRAY,
	}
};
FucInfo Fn_UpDownGetAccel = { {
		/*ccname*/  "ȡ���ٶ�",
		/*egname*/  "GetAccel",
		/*explain*/ "���ؿؼ�ʵ��ӵ�еļ��ٶ�����",
		/*category*/-1,
		/*state*/   0,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_ArgsGetAccel),
		/*arg lp*/  s_ArgsGetAccel,
	} , libstl_UpDown_GetAccel ,"libstl_UpDown_GetAccel" };

ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO UpDown = {
	"������Ex",//��������
	"UpDown",//Ӣ������
	"���ؼ���������Ըı����Ҫ���´����ؼ���Ӧ���������ʱȷ������ֵ",//˵��
	ARRAYSIZE(s_Cmd_UpDown),//��������
	s_Cmd_UpDown,//��ȫ�ֺ����ж�Ӧ������
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//��־
	IDB_UPDOWN_EX,//��ԴID
	ARRAYSIZE(s_Event_UpDown),
	s_Event_UpDown,//�¼�
	ARRAYSIZE(s_Member_UpDown),//������
	s_Member_UpDown,//����ָ��
	libstl_GetInterface_UpDown,//��������ӳ���
	NULL,//��Ա����
	NULL//��Ա��������
};
ESTL_NAMESPACE_END