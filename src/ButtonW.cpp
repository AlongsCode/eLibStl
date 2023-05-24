/*
* 2023.5.7
* FIXME����ť��ͼ���б���ع���û�з�װ
*/
#include"EcontrolHelp.h"

#pragma warning(disable:4996)

#define SCID_PUSHBTN		20230425'01u
#define SCID_PUSHBTNPARENT	20230425'02u
#define SCID_CHECKBTN		20230425'03u
#define SCID_CHECKBTNPARENT	20230425'04u
#define SCID_CMDLINK		20230425'05u
#define SCID_CMDLINKPARENT	20230425'06u

#define BTN_COMM_PROP \
	/*000*/{ "ͼƬ", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL}, \
	/*001*/{ "�Ƿ�ͬʱ��ʾͼƬ���ı�", "IsShowPicAndText", "�޷�Ԥ������Ҫͨ�������6.0", UD_BOOL, _PROP_OS(__OS_WIN), NULL }, \
	/*002*/{ "����", "Text", "��ť����������ʱ֧�����259���ַ����������й�����û������", UD_TEXT, _PROP_OS(__OS_WIN), NULL }, \
	/*003*/{ "����W", "TextW", "��ť����������ʱ֧�����259���ַ����������й�����û������", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL }, \
	/*004*/{ "������뷽ʽ", "AlignH", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "���\0""����\0""�ұ�\0""\0" }, \
	/*005*/{ "������뷽ʽ", "AlignV", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "�ϱ�\0""����\0""�±�\0""\0" }, \
	/*006*/{ "����", "Font", "", UD_FONT, _PROP_OS(__OS_WIN) , NULL }

#define BTN_COMM_GETPROP \
	case 0:/*ͼƬ*/ \
		pPropertyVaule->m_data.m_pData = p->GetPic(&pPropertyVaule->m_data.m_nDataSize); \
		break; \
	case 1:/*�Ƿ�ͬʱ��ʾͼƬ���ı�*/ \
		pPropertyVaule->m_bool = p->GetTextImageShowing(); \
		break; \
	case 2:/*����*/ \
		pPropertyVaule->m_szText = p->GetTextA(); \
		break; \
	case 3:/*����W*/ \
		pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize); \
		break; \
	case 4:/*�������*/ \
		pPropertyVaule->m_int = p->GetAlign(TRUE); \
		break; \
	case 5:/*�������*/ \
		pPropertyVaule->m_int = p->GetAlign(FALSE); \
		break; \
	case 6:/*����*/ \
		pPropertyVaule->m_data.m_pData = p->GetFont(); \
		pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA); \
		break;

#define BTN_COMM_SETPROP \
	case 0:/*ͼƬ*/ \
		p->SetPicBtn(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize); \
		break; \
	case 1:/*�Ƿ�ͬʱ��ʾͼƬ���ı�*/ \
		p->SetTextImageShowing(pPropertyVaule->m_bool); \
		break; \
	case 2:/*����*/ \
		p->SetTextA(pPropertyVaule->m_szText); \
		break; \
	case 3:/*����W*/ \
		p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData); \
		break; \
	case 4:/*�������*/ \
		p->SetAlign(TRUE, pPropertyVaule->m_int); \
		break; \
	case 5:/*�������*/ \
		p->SetAlign(FALSE, pPropertyVaule->m_int); \
		break; \
	case 6:/*����*/ \
		p->SetFont((LOGFONTA*)pPropertyVaule->m_int); \
		break;

ESTL_NAMESPACE_BEGIN
// ��������
/*
* �汾1���ݲ��֣�
* EBUTTONDATA�ṹ
* ͼƬ
* �ı�
*/
#define DATA_VER_BTN_1	1
struct EBUTTONDATA
{
	int iVer;				// �汾��
	DWORD dwReserved;		// ����

	int algH;				// �������
	int algV;				// �������
	BOOL bShowTextAndImage;	// �Ƿ�ͬʱ��ʾͼƬ���ı�
};

// ��ͨ��ť
/*
* �汾1���ݲ��֣�
* EBUTTONDATA_PUSHBTN�ṹ
*/
#define DATA_VER_BTN_PUSHBTN_1	1
struct EBUTTONDATA_PUSHBTN
{
	int iVer;				// �汾

	int iType;				// ����
	int iDef;				// �Ƿ�Ĭ��
};

// ѡ��򣨵�ѡ����ѡ����̬��ѡ��
/*
* �汾1���ݲ��֣�
* EBUTTONDATA_CHECKBTN�ṹ
*/
#define DATA_VER_BTN_CHECKBTN_1	1
struct EBUTTONDATA_CHECKBTN
{
	int iVer;				// �汾

	int iType;				// ����
	int iCheckState;		// ѡ��״̬
	BOOL bPushLike;			// ��ť��ʽ
	BOOL bFlat;				// ƽ��
	BOOL bLeftText;			// �������
};

// ��������
/*
* �汾1���ݲ��֣�
* EBUTTONDATA_CMDLINK�ṹ
* ע���ı�
*/
#define DATA_VER_BTN_CMDLINK_1	1
struct EBUTTONDATA_CMDLINK
{
	int iVer;				// �汾

	int cchNote;			// ע���ı����ȣ������ڱ�����Ϣ
	BOOL bShieldIcon;		// �Ƿ����ͼ��
	int iDef;				// Ĭ��
};

// ��ť���ࡣ
// ����ֱ��ʵ��������
class CButton :public elibstl::CCtrlBase
{
protected:
	EBUTTONDATA m_Info{};

	eStlInline SIZE_T InitBase(LPVOID pAllData, int cbData, BOOL bInDesignMode, DWORD dwWinFormID, DWORD dwUnitID)
	{
		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(EBUTTONDATA));
		}

		m_Info.iVer = DATA_VER_BTN_1;

		if (pAllData)
			return sizeof(EBUTTONDATA) + cbBaseData;
		else
			return 0;
	}

	eStlInline void InitBase(PCVOID pAllData)
	{
		InitBase0(pAllData);
		if (pAllData)
		{
			SetAlign(TRUE, m_Info.algH);
			SetAlign(FALSE, m_Info.algV);
			SetTextImageShowing(m_Info.bShowTextAndImage);
		}
		else
		{
			m_Info.algH = 1;
			m_Info.algV = 1;
		}

		if (m_hbmPic)
		{
			if (!m_bInDesignMode)
				if (m_Info.bShowTextAndImage)
					SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
				else
					SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
			else
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
			SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hbmPic);
		}
		else
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
	}
public:
	CButton() {}

	virtual ~CButton() {}

	/// <summary>
	/// ��ͼƬ�ı�ͬʱ��ʾ
	/// </summary>
	/// <param name="bShowTextAndImage">�Ƿ�ͬʱ��ʾ</param>
	void SetTextImageShowing(BOOL bShowTextAndImage)
	{
		m_Info.bShowTextAndImage = bShowTextAndImage;
		if (!m_bInDesignMode)
		{
			DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE);
			if (bShowTextAndImage)
				dwStyle &= (~(BS_BITMAP));
			else if (m_pPicData && m_Info0.cbPic)
				dwStyle |= BS_BITMAP;
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
		}
	}

	/// <summary>
	/// ȡͼƬ�ı�ͬʱ��ʾ
	/// </summary>
	/// <returns>�Ƿ�ͬʱ��ʾ</returns>
	eStlInline BOOL GetTextImageShowing() const
	{
		return m_Info.bShowTextAndImage;
	}

	/// <summary>
	/// �ö���
	/// </summary>
	/// <param name="bHAlign">�Ƿ�ˮƽ����</param>
	/// <param name="iAlign">���룬�μ����Զ���</param>
	void SetAlign(BOOL bHAlign, int iAlign)
	{
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE);
		if (bHAlign)
		{
			dwStyle &= (~(BS_LEFT | BS_CENTER | BS_RIGHT));
			m_Info.algH = iAlign;
			switch (iAlign)
			{
			case 0: dwStyle |= BS_LEFT; break;
			case 1: dwStyle |= BS_CENTER; break;
			case 2: dwStyle |= BS_RIGHT; break;
			}
		}
		else
		{
			dwStyle &= (~(BS_TOP | BS_VCENTER | BS_BOTTOM));
			m_Info.algV = iAlign;
			switch (iAlign)
			{
			case 0: dwStyle |= BS_TOP; break;
			case 1: dwStyle |= BS_VCENTER; break;
			case 2: dwStyle |= BS_BOTTOM; break;
			}
		}
		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
		Redraw();
	}

	/// <summary>
	/// ȡ����
	/// </summary>
	/// <param name="bHAlign">�Ƿ�ˮƽ����</param>
	/// <returns>���룬�μ����Զ���</returns>
	eStlInline int GetAlign(BOOL bHAlign) const
	{
		if (m_bInDesignMode)
			if (bHAlign)
				return m_Info.algH;
			else
				return m_Info.algV;
		else
			if (bHAlign)
				return MultiSelectWndStyle(m_hWnd, BS_LEFT, BS_CENTER, BS_RIGHT);
			else
				return MultiSelectWndStyle(m_hWnd, BS_TOP, BS_VCENTER, BS_BOTTOM);
	}

	/// <summary>
	/// ��ͼƬ��
	/// �ض��ڰ�ť����Ӧʹ�û��෽��
	/// </summary>
	/// <param name="pPic">ͼƬ�ֽ���ָ��</param>
	/// <param name="cbSize">�ֽ�������</param>
	/// <returns></returns>
	eStlInline void SetPicBtn(void* pPic, int cbSize)
	{
		if (cbSize)
			if (m_Info.bShowTextAndImage)
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));
			else
				SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
		else
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & (~BS_BITMAP));

		SetPic(pPic, cbSize);
		SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hbmPic);
	}

	/// <summary>
	/// ƽ�滯�������ݡ�
	/// ��չ����Ӧ����󸽼�
	/// </summary>
	/// <returns></returns>
	eStlInline HGLOBAL FlattenInfoBase(SIZE_T cbExtra = 0u, SIZE_T* pcbBaseData = NULL)
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(EBUTTONDATA) + cbExtra, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		memcpy(p + cbBaseData, &m_Info, sizeof(EBUTTONDATA));
		GlobalUnlock(hGlobal);
		*pcbBaseData = cbBaseData + sizeof(EBUTTONDATA);
		return hGlobal;
	Fail:
		*pcbBaseData = 0;
		return hGlobal;
	}
};

// ��ͨ��ť
class CPushButton :public CButton
{
	SUBCLASS_MGR_DECL(CPushButton)
private:
	EBUTTONDATA_PUSHBTN m_InfoEx{};

	/// <summary>
	/// ������
	/// </summary>
	eStlInline void OnClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	/// <summary>
	/// ������ͷ������
	/// </summary>
	eStlInline void OnDropDownClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 1);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_NOTIFY:
		{
			auto p = (NMHDR*)lParam;
#pragma warning(push)
#pragma warning(disable:26454)// �������
			if (p->code == BCN_DROPDOWN)
				if (m_CtrlSCInfo.count(p->hwndFrom))
					m_CtrlSCInfo[p->hwndFrom]->OnDropDownClick();
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
		auto p = (CPushButton*)dwRefData;
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

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CPushButton() = delete;
	CPushButton(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_PUSHBTN));
		else
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"��ťW");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}
		m_InfoEx.iVer = DATA_VER_BTN_PUSHBTN_1;

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		InitBase(pAllData);
		SetDef(m_InfoEx.iDef);
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		Redraw();
	}

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="iType">���ͣ��μ����Զ���</param>
	void SetType(int iType)
	{
		m_InfoEx.iType = iType;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE)
			& (~(BS_PUSHBUTTON | BS_SPLITBUTTON | BS_DEFPUSHBUTTON | BS_DEFSPLITBUTTON));

		switch (iType)
		{
		case 0:
			dwStyle |= (m_InfoEx.iDef ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON);
			break;
		case 1:
			if (!m_bInDesignMode)
				dwStyle |= (m_InfoEx.iDef ? BS_DEFSPLITBUTTON : BS_SPLITBUTTON);
			break;
		}

		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
		Redraw();
	}

	/// <summary>
	/// ȡ����
	/// </summary>
	/// <returns>���ͣ��μ����Զ���</returns>
	eStlInline int GetType() const
	{
		return m_InfoEx.iType;
	}

	/// <summary>
	/// ���Ƿ�Ĭ��
	/// </summary>
	/// <param name="iDef">�Ƿ�Ĭ�ϣ��μ����Զ���</param>
	void SetDef(int iDef)
	{
		m_InfoEx.iDef = iDef;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE)
			& (~(BS_DEFPUSHBUTTON | BS_DEFSPLITBUTTON | BS_PUSHBUTTON | BS_SPLITBUTTON));
		if (iDef)
			if (m_InfoEx.iType)
				dwStyle |= BS_DEFSPLITBUTTON;
			else
				dwStyle |= BS_DEFPUSHBUTTON;
		else
			if (m_InfoEx.iType)
				dwStyle |= BS_SPLITBUTTON;
			else
				dwStyle |= BS_PUSHBUTTON;

		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
	}

	/// <summary>
	/// ȡ�Ƿ�Ĭ��
	/// </summary>
	/// <returns>�Ƿ�Ĭ�ϣ��μ����Զ���</returns>
	eStlInline int GetDef() const
	{
		return m_InfoEx.iDef;
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase(sizeof(EBUTTONDATA_PUSHBTN), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		memcpy(p + cbBaseData, &m_InfoEx, sizeof(EBUTTONDATA_PUSHBTN));
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CPushButton(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
			BTN_COMM_SETPROP

		case 7:// Ĭ��
			p->SetDef(pPropertyVaule->m_int);
			break;

		case 8:// ����
			p->SetType(pPropertyVaule->m_int);
			break;
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
			BTN_COMM_GETPROP

		case 7:// Ĭ��
			pPropertyVaule->m_int = p->GetDef();
			break;

		case 8:// ����
			pPropertyVaule->m_int = p->GetType();
			break;
		}

		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		*pblModified = FALSE;
		if (nPropertyIndex == 3)
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		return FALSE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 80;
			*((int*)dwParam2) = 32;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CPushButton, SCID_PUSHBTNPARENT, SCID_PUSHBTN)

// ѡ���
class CCheckButton :public CButton
{
	SUBCLASS_MGR_DECL(CCheckButton)
private:
	EBUTTONDATA_CHECKBTN m_InfoEx{};

	/// <summary>
	/// ������
	/// </summary>
	eStlInline void OnClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CCheckButton*)dwRefData;
		switch (uMsg)
		{
		case WM_DESTROY:
			m_SM.OnCtrlDestroy(p);
			delete p;
			return DefSubclassProc(hWnd, uMsg, wParam, lParam);

		case WM_NCCALCSIZE:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);

		case WM_SHOWWINDOW:
			CHECK_PARENT_CHANGE;
			break;
		}

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CCheckButton() = delete;
	CCheckButton(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);
		if (!m_pszTextW)
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"ѡ���W");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_CHECKBTN));
		else
			m_Info.algH = 0;
		m_InfoEx.iVer = DATA_VER_BTN_CHECKBTN_1;

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		InitBase(pAllData);
		SetType(m_InfoEx.iType);
		SetCheckState(m_InfoEx.iCheckState);
		SetPushLike(m_InfoEx.bPushLike);
		SetFlat(m_InfoEx.bFlat);
		SetLeftText(m_InfoEx.bLeftText);
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		Redraw();
	}

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="iType">����</param>
	void SetType(int iType)
	{
		m_InfoEx.iType = iType;
		elibstl::ModifyWindowStyle(
			m_hWnd,
			elibstl::MultiSelect<DWORD>(iType, BS_AUTORADIOBUTTON, BS_AUTOCHECKBOX, BS_AUTO3STATE),
			BS_AUTORADIOBUTTON | BS_AUTOCHECKBOX | BS_AUTO3STATE);
		Redraw();
	}

	/// <summary>
	/// ȡ����
	/// </summary>
	int GetType()
	{
		if (m_bInDesignMode)
			return m_InfoEx.iType;
		else
		{
			auto i = MultiSelectWndStyle(m_hWnd,
				BS_AUTORADIOBUTTON | BS_RADIOBUTTON, BS_AUTOCHECKBOX | BS_CHECKBOX, BS_AUTO3STATE | BS_3STATE);
			if (i < 0)
				i = 0;
			return i;
		}
	}

	/// <summary>
	/// �ü���״̬
	/// </summary>
	/// <param name="iState">״̬</param>
	eStlInline void SetCheckState(int iState)
	{
		m_InfoEx.iCheckState = iState;
		SendMessageW(m_hWnd, BM_SETCHECK, elibstl::MultiSelect<DWORD>(iState, BST_UNCHECKED, BST_CHECKED, BST_INDETERMINATE), 0);
	}

	/// <summary>
	/// ȡ����״̬
	/// </summary>
	int GetCheckState()
	{
		if (m_bInDesignMode)
			return m_InfoEx.iCheckState;
		else
		{
			int i = MultiSelectEqual(SendMessageW(m_hWnd, BM_GETCHECK, 0, 0), BST_UNCHECKED, BST_CHECKED, BST_INDETERMINATE);
			if (i < 0)
				i = 0;
			return i;
		}
	}

	/// <summary>
	/// �ð�ť��ʽ
	/// </summary>
	/// <param name="bPushLike">�Ƿ�Ϊ��ť��ʽ</param>
	eStlInline void SetPushLike(BOOL bPushLike)
	{
		m_InfoEx.bPushLike = bPushLike;
		elibstl::ModifyWindowStyle(m_hWnd, bPushLike ? BS_PUSHLIKE : 0, BS_PUSHLIKE);
		Redraw();
	}

	/// <summary>
	/// ȡ��ť��ʽ
	/// </summary>
	/// <returns></returns>
	eStlInline BOOL GetPushLike()
	{
		if (m_bInDesignMode)
			return m_InfoEx.bPushLike;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), BS_PUSHLIKE);
	}

	/// <summary>
	/// ��ƽ����ʽ
	/// </summary>
	/// <param name="bFlat">�Ƿ�Ϊƽ����ʽ</param>
	eStlInline void SetFlat(BOOL bFlat)
	{
		m_InfoEx.bFlat = bFlat;
		elibstl::ModifyWindowStyle(m_hWnd, bFlat ? BS_FLAT : 0, BS_FLAT);
		Redraw();
	}

	/// <summary>
	/// ȡƽ����ʽ
	/// </summary>
	eStlInline BOOL GetFlat()
	{
		if (m_bInDesignMode)
			return m_InfoEx.bFlat;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), BS_FLAT);
	}

	/// <summary>
	/// ���ı�����
	/// </summary>
	/// <param name="bLeftText">�Ƿ��ı�����</param>
	eStlInline void SetLeftText(BOOL bLeftText)
	{
		m_InfoEx.bLeftText = bLeftText;
		elibstl::ModifyWindowStyle(m_hWnd, bLeftText ? BS_LEFTTEXT : 0, BS_LEFTTEXT);
		Redraw();
	}

	/// <summary>
	/// ȡ�ı�����
	/// </summary>
	/// <returns></returns>
	eStlInline BOOL GetLeftText()
	{
		if (m_bInDesignMode)
			return m_InfoEx.bLeftText;
		else
			return elibstl::IsBitExist(GetWindowLongPtrW(m_hWnd, GWL_STYLE), BS_LEFTTEXT);
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase(sizeof(EBUTTONDATA_CHECKBTN), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		memcpy(p + cbBaseData, &m_InfoEx, sizeof(EBUTTONDATA_CHECKBTN));
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CCheckButton(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
			BTN_COMM_SETPROP

		case 7:// ����
			p->SetType(pPropertyVaule->m_int);
			break;

		case 8:// ѡ��
			p->SetCheckState(pPropertyVaule->m_int);
			break;

		case 9:// ��ť��ʽ
			p->SetPushLike(pPropertyVaule->m_bool);
			break;

		case 10:// ƽ��
			p->SetFlat(pPropertyVaule->m_bool);
			break;

		case 11:// �������
			p->SetLeftText(pPropertyVaule->m_bool);
			break;

		case 12:// �߿�
			p->SetFrame(pPropertyVaule->m_int);
			break;
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
			BTN_COMM_GETPROP

		case 7:// ����
			pPropertyVaule->m_int = p->GetType();
			break;

		case 8:// ѡ��
			pPropertyVaule->m_int = p->GetCheckState();
			break;

		case 9:// ��ť��ʽ
			pPropertyVaule->m_bool = p->GetPushLike();
			break;

		case 10:// ƽ��
			pPropertyVaule->m_bool = p->GetFlat();
			break;

		case 11:// �������
			pPropertyVaule->m_bool = p->GetLeftText();
			break;

		case 12:// �߿�
			pPropertyVaule->m_int = p->GetFrame();
			break;
		}
		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		*pblModified = FALSE;
		if (nPropertyIndex == 3)
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		return FALSE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 80;
			*((int*)dwParam2) = 24;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CCheckButton, SCID_CHECKBTNPARENT, SCID_CHECKBTN)

// ��������
class CCommandLink :public CButton
{
	SUBCLASS_MGR_DECL(CCommandLink)
private:
	EBUTTONDATA_CMDLINK m_InfoEx{};
	PWSTR m_pszNote;// ע���ı�

	/// <summary>
	/// ������
	/// </summary>
	eStlInline void OnClick()
	{
		EVENT_NOTIFY2 evt(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&evt, 0);
	}

	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		{
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED)
				if (m_CtrlSCInfo.count((HWND)lParam))
					m_CtrlSCInfo[(HWND)lParam]->OnClick();
			break;

		case WM_DESTROY:
			m_SM.OnParentDestroy(hWnd);
			break;
		}

		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CCommandLink*)dwRefData;
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

		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public:
	CCommandLink() = delete;
	CCommandLink(STD_ECTRL_CREATE_ARGS)
	{
		auto cbBaseData = InitBase(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID);
		if (!m_pszTextW)
		{
			elibstl::DupStringForNewDeleteW(m_pszTextW, L"��������");
			m_pszTextA = elibstl::W2A(m_pszTextW);
		}

		if (pAllData)
			memcpy(&m_InfoEx, (BYTE*)pAllData + cbBaseData, sizeof(EBUTTONDATA_CMDLINK));
		m_InfoEx.iVer = DATA_VER_BTN_CHECKBTN_1;
		m_pszNote = NULL;
		if (m_InfoEx.cchNote)
		{
			elibstl::DupStringForNewDeleteW(m_pszNote,
				(PCWSTR)((BYTE*)pAllData + cbBaseData + sizeof(EBUTTONDATA_CMDLINK)), m_InfoEx.cchNote);
		}

		m_hWnd = CreateWindowExW(0, WC_BUTTONW, m_pszTextW, WS_CHILD | WS_CLIPSIBLINGS |
			(m_bInDesignMode ? BS_PUSHBUTTON : BS_COMMANDLINK),
			x, y, cx, cy, hParent, (HMENU)nID, NULL, NULL);
		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		SendMessageW(m_hWnd, WM_SETREDRAW, FALSE, 0);
		InitBase(pAllData);
		SetShieldIcon(m_InfoEx.bShieldIcon);
		SetNote(m_pszNote);
		SendMessageW(m_hWnd, WM_SETREDRAW, TRUE, 0);
		Redraw();
	}

	~CCommandLink()
	{
		delete[] m_pszNote;
	}

	/// <summary>
	/// ��ע���ı�
	/// </summary>
	/// <param name="pszText">�ı�ָ��</param>
	/// <returns>�ɹ�����TRUE��ʧ�ܷ���FALSE</returns>
	eStlInline BOOL SetNote(PCWSTR pszText)
	{
		if (m_bInDesignMode)
		{
			if (pszText)
				elibstl::DupStringForNewDeleteW(m_pszNote, pszText);
			else
			{
				delete[] m_pszNote;
				m_pszNote = NULL;
			}
			return TRUE;
		}
		else
			return SendMessageW(m_hWnd, BCM_SETNOTE, 0, (LPARAM)pszText);
	}

	/// <summary>
	/// ��ע���ı���
	/// �������������ڴ�
	/// </summary>
	/// <param name="pszText">�ı�ָ�룬������new/delete[]����</param>
	/// <returns>�ɹ�����TRUE��ʧ�ܷ���FALSE</returns>
	eStlInline BOOL SetNoteNoCopy(PWSTR pszText)
	{
		if (m_bInDesignMode)
		{
			delete[] m_pszNote;
			m_pszNote = pszText;
			return TRUE;
		}
		else
			return SendMessageW(m_hWnd, BCM_SETNOTE, 0, (LPARAM)pszText);
	}

	/// <summary>
	/// ȡע���ı���
	/// ���ص��ı�Ϊ�����ڲ����У������ͷ�
	/// </summary>
	/// <returns>�ı�ָ��</returns>
	PWSTR GetNote()
	{
		if (!m_bInDesignMode)
		{
			int cch = SendMessageW(m_hWnd, BCM_GETNOTELENGTH, 0, 0);
			delete[] m_pszNote;
			if (cch)
			{
				m_pszNote = new WCHAR[cch + 1];
				SendMessageW(m_hWnd, BCM_GETNOTE, cch + 1, (LPARAM)m_pszNote);
			}
			else
				m_pszNote = NULL;
		}

		return m_pszNote;
	}

	/// <summary>
	/// �ö���ͼ��
	/// </summary>
	/// <param name="bShieldIcon">�Ƿ�Ϊ����ͼ��</param>
	eStlInline void SetShieldIcon(BOOL bShieldIcon)
	{
		m_InfoEx.bShieldIcon = bShieldIcon;
		SendMessageW(m_hWnd, BCM_SETSHIELD, 0, bShieldIcon);
	}

	/// <summary>
	/// ȡ����ͼ��
	/// </summary>
	/// <returns></returns>
	eStlInline BOOL GetShieldIcon()
	{
		return m_InfoEx.bShieldIcon;// �������ֻ���ò���ȡ.....�Ѽ�¼��ֵ���ػ�ȥ��
	}

	/// <summary>
	/// ���Ƿ�Ĭ��
	/// </summary>
	/// <param name="iDef">�Ƿ�Ĭ�ϣ��μ����Զ���</param>
	void SetDef(int iDef)
	{
		m_InfoEx.iDef = iDef;
		DWORD dwStyle = GetWindowLongPtrW(m_hWnd, GWL_STYLE)
			& (~(BS_DEFPUSHBUTTON | BS_PUSHBUTTON | BS_DEFCOMMANDLINK | BS_COMMANDLINK));
		if (iDef)
			dwStyle |= (m_bInDesignMode ? BS_DEFPUSHBUTTON : BS_DEFCOMMANDLINK);
		else
			dwStyle |= (m_bInDesignMode ? BS_PUSHBUTTON : BS_COMMANDLINK);

		SetWindowLongPtrW(m_hWnd, GWL_STYLE, dwStyle);
	}

	/// <summary>
	/// ȡ�Ƿ�Ĭ��
	/// </summary>
	/// <returns>�Ƿ�Ĭ�ϣ��μ����Զ���</returns>
	eStlInline int GetDef() const
	{
		return m_InfoEx.iDef;
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		SIZE_T cbData = sizeof(EBUTTONDATA_CMDLINK);
		if (GetNote())
		{
			m_InfoEx.cchNote = wcslen(m_pszNote);
			cbData += (m_InfoEx.cchNote * sizeof(WCHAR));
		}
		else
			m_InfoEx.cchNote = 0;
		auto hGlobal = FlattenInfoBase(cbData, &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// �ṹ
		p += cbBaseData;
		memcpy(p, &m_InfoEx, sizeof(EBUTTONDATA_CMDLINK));
		// ע���ı�
		p += sizeof(EBUTTONDATA_CMDLINK);
		if (m_pszNote)
			memcpy(p, m_pszNote, m_InfoEx.cchNote * sizeof(WCHAR));
		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CCommandLink(STD_ECTRL_CREATE_REAL_ARGS);
		if (p->GetHWND())
			return elibstl::make_cwnd(p->GetHWND());
		else
		{
			delete p;
			return NULL;
		}
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, LPTSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:/*ͼƬ*/
			p->SetPicBtn(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_nDataSize);
			break;
		case 1:/*����*/
			p->SetTextA(pPropertyVaule->m_szText);
			break;
		case 2:/*����W*/
			p->SetTextW((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 3:// ע���ı�
			p->SetNote((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 4:// �Ƿ����ͼ��
			p->SetShieldIcon(pPropertyVaule->m_bool);
			break;
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
		case 0:/*ͼƬ*/
			pPropertyVaule->m_data.m_pData = p->GetPic(&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 1:/*����*/
			pPropertyVaule->m_szText = p->GetTextA();
			break;
		case 2:/*����W*/
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetTextW((SIZE_T*)&pPropertyVaule->m_data.m_nDataSize);
			break;
		case 3:// ע���ı�
			pPropertyVaule->m_data.m_pData = (BYTE*)p->GetNote();
			break;
		case 4:// �Ƿ����ͼ��
			pPropertyVaule->m_bool = p->GetShieldIcon();
			break;
		}
		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		*pblModified = FALSE;
		switch (nPropertyIndex)
		{
		case 2:// ����W
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetTextW()))
			{
				p->SetTextNoCopyW(psz);
				*pblModified = TRUE;
			}
		}
		return FALSE;

		case 3:// ע���ı�
		{
			PWSTR psz;
			if (elibstl::IntputBox(&psz, p->GetNote()))
			{
				p->SetNoteNoCopy(psz);
				*pblModified = TRUE;
			}
		}
		return FALSE;
		}
		return FALSE;
	}

	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 200;
			*((int*)dwParam2) = 80;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CCommandLink, SCID_CMDLINKPARENT, SCID_CMDLINK)
ESTL_NAMESPACE_END
/////////////////////////////��ͨ��ť
static EVENT_INFO2 s_Event_PushBtn[] =
{
	/*000*/ {"��ť������", "����ť������ʱ����", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
	/*001*/ {"������ͷ������", "��������ͷ������ʱ����", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
};
static UNIT_PROPERTY s_Member_PushBtn[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	BTN_COMM_PROP,
	/*007*/ {"Ĭ��", "Def", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "ͨ��\0""Ĭ��\0""\0"},
	/*008*/ {"����", "Type", "�޷�Ԥ������������Ҫ���嵥��ָ��Comctl6.0", UD_PICK_INT, _PROP_OS(__OS_WIN), "��ͨ��ť\0""��ְ�ť\0""\0"},
};
///////////////////////////////ѡ���
static EVENT_INFO2 s_Event_CheckBtn[] =
{
	/*000*/ {"������", "��ѡ��򱻵���ʱ����", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
};
static UNIT_PROPERTY s_Member_CheckBtn[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	BTN_COMM_PROP,
	/*007*/ {"����", "Type", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "��ѡ��\0""��ѡ��\0""��̬��ѡ��\0""\0"},
	/*008*/ {"ѡ��", "CheckState", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "δѡ��\0""ѡ��\0""��ѡ��\0""\0"},
	/*009*/ {"��ť��ʽ", "IsBtnLike", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*010*/ {"ƽ��", "IsFlat", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*011*/ {"�������", "IsTextLeft", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*012*/ {"�߿�", "Frame", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "�ޱ߿�\0""����ʽ\0""͹��ʽ\0""ǳ����ʽ\0""����ʽ\0""���߱߿�ʽ\0""\0"},
};
/////////////////////////////��������
static EVENT_INFO2 s_Event_CmdLink[] =
{
	/*000*/ {"������", "����ť������ʱ����", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, DATA_TYPE::_SDT_NULL},
};
static UNIT_PROPERTY s_Member_CmdLink[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	/*000*/ {"ͼƬ", "Picture", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*001*/ {"����","Text","",UD_TEXT,_PROP_OS(__OS_WIN),NULL },
	/*002*/ {"����W","TextW","",UD_CUSTOMIZE,_PROP_OS(__OS_WIN),NULL },
	/*003*/ {"ע���ı�","Note","",UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
	/*004*/ {"�Ƿ�Ϊ����ͼ��", "IsShieldIcon", "", UD_BOOL, _PROP_OS(__OS_WIN), NULL },
};
/////////////////////////////����
static int s_Cmd_PushBtn[] = { 120 };

EXTERN_C void libstl_Button_GetIdealSize(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	SIZE size{ *pArgInf[1].m_pInt,0 };
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	if (!hWnd)
		goto Fail;
	if (!SendMessageW(hWnd, BCM_GETIDEALSIZE, 0, (LPARAM)&size))
		goto Fail;
	*pArgInf[1].m_pInt = size.cx;
	*pArgInf[2].m_pInt = size.cy;
	pRetData->m_bool = TRUE;
	return;
Fail:
	pRetData->m_bool = FALSE;
	return;
}

static ARG_INFO s_Args_GetIdealSize[] =
{
	{
		/*name*/    "���",
		/*explain*/ "���ܿ�ȵı�����������ǰ������Ϊ0���������ֵָ��Ϊ��ť�Ŀ�ȣ����Դ�ֵΪ��׼��������߶�",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	},
	{
		/*name*/    "�߶�",
		/*explain*/ "���ܸ߶ȵı���",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	}
};

FucInfo Fn_BtnGetIdealSize = { {
		/*ccname*/  ("ȡ����ߴ�"),
		/*egname*/  ("GetIdealSize"),
		/*explain*/ ("ȡ��ť����ߴ硣��������Ҫ���嵥��ָ��Comctl6.0"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_GetIdealSize),
		/*arg lp*/  s_Args_GetIdealSize,
	} ,libstl_Button_GetIdealSize ,"libstl_Button_GetIdealSize" };
/////////////////////////////ȡ�ӿ�
EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_ButtonW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CPushButton::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CPushButton::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CPushButton::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CPushButton::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CPushButton::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CPushButton::ENotify;
	}
	return NULL;
}

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_CheckButtonW(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CCheckButton::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CCheckButton::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCheckButton::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCheckButton::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CCheckButton::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CCheckButton::ENotify;
	}
	return NULL;
}

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_CommandLink(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CCommandLink::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CCommandLink::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCommandLink::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CCommandLink::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CCommandLink::EInputW;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CCommandLink::ENotify;
	}
	return NULL;
}
/////////////////////////////���Ͷ���
ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtButtonW =
{
	"��ťW",				//��������
	"ButtonW",			//Ӣ������
	"Unicode��ť",		//˵��
	ARRAYSIZE(s_Cmd_PushBtn),
	s_Cmd_PushBtn,
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	IDB_BUTTON_W,				//��ԴID
	ARRAYSIZE(s_Event_PushBtn),
	s_Event_PushBtn,
	ARRAYSIZE(s_Member_PushBtn),
	s_Member_PushBtn,
	libstl_GetInterface_ButtonW,
	0,					//��Ա����
	NULL				//��Ա��������
};

LIB_DATA_TYPE_INFO CtCheckButtonW =
{
	"ѡ���W",			//��������
	"CheckButtonW",		//Ӣ������
	"Unicodeѡ��򣨵�ѡ����ѡ����̬��ѡ��",//˵��
	0,					//��������
	0,					//��ȫ�ֺ����ж�Ӧ������
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	IDB_CHECKBUTTON_W,				//��ԴID
	ARRAYSIZE(s_Event_CheckBtn),
	s_Event_CheckBtn,
	ARRAYSIZE(s_Member_CheckBtn),
	s_Member_CheckBtn,
	libstl_GetInterface_CheckButtonW,
	0,					//��Ա����
	NULL				//��Ա��������
};

LIB_DATA_TYPE_INFO CtCommandLink =
{
	"�������Ӱ�ť",		//��������
	"CommandLink",		//Ӣ������
	"�������Ӱ�ť",		//˵��
	0,					//��������
	0,					//��ȫ�ֺ����ж�Ӧ������
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,
	IDB_COMLINKBUTTON_W,				//��ԴID
	ARRAYSIZE(s_Event_CmdLink),
	s_Event_CmdLink,
	ARRAYSIZE(s_Member_CmdLink),
	s_Member_CmdLink,
	libstl_GetInterface_CommandLink,
	0,					//��Ա����
	NULL				//��Ա��������
};
ESTL_NAMESPACE_END