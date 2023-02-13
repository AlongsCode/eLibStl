#include"EcontrolHelp.h"
#include<Richedit.h>
#pragma warning(disable:4996)
//static INT s_cmd[] = { 0 };

static EVENT_ARG_INFO2  s_event_arg = { "按钮值", "如果按下的是调节器的向上箭头按钮，参数值为 1，否则为 -1", 0, SDT_INT };



static EVENT_INFO2 s_event[] =
{
	/*000*/ {"调节钮被按下", "当调节钮被按下时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 1, &s_event_arg, _SDT_NULL},
};
static UNIT_PROPERTY s_member[] =
{
	// FIXED_WIN_UNIT_PROPERTY,    // 必须加上此宏, 或者直接展开, 这里就展开
	//1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束

	/*000*/ {"左边", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*001*/ {"顶边", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*002*/ {"宽度", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*003*/ {"高度", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
	/*004*/ {"标记", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
	/*005*/ {"可视", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*006*/ {"禁止", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
	/*007*/ {"鼠标指针", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},

	// 以上属性是易语言需要的默认属性, 每个组件都必须有, 但是可以手动隐藏
	// 以下属性是组件自身带的, 这些不是强制需要的
	// 这些属性在易语言的回调里是从0开始的, 所以, 这些序号也从0开始
	/*000*/  {"自动模式","SpinMod", "自动调节器不再接受回调函数,他由系统控制。对于绑定组件的文本进行数值'+','-' 操作",  UD_BOOL, _PROP_OS(__OS_WIN), NULL},
	/*001*/  {"调节器下限", "SpinMin", "设置调节器下限", UD_INT, _PROP_OS(OS_ALL) | UW_HAS_INDENT, NULL},
	/*002*/  {"调节器上限", "SpinMax", "设置调节器上限", UD_INT, _PROP_OS(OS_ALL) | UW_HAS_INDENT, NULL},
	/*003*/  {"方向", "SpinDirection", "设置调节器方向", UD_PICK_INT, _PROP_OS(OS_ALL),  "纵向\0""横向\0""\0"},
	/*004*/  {"绑定组件", "BindHwnd", "欲绑定的可编辑文本组件或对话框句柄", UD_INT, _PROP_OS(OS_ALL) | UW_CANNOT_INIT, NULL},
};


typedef struct _EBinWindowData
{
	HWND m_hWnd;
	RECT m_Rect;
	_EBinWindowData() {
		memset(this, 0, sizeof(*this));
	}
}BINDWINDOWDATA, * LPBINDWINDOWDATA;

typedef struct _eUpDowndata {
	bool m_Auto;
	int m_min;
	int m_max;
	bool m_IsHorizontal;
	BINDWINDOWDATA m_win_data;
	_eUpDowndata() {
		memset(this, 0, sizeof(*this));
	}
}EUODOWNDATA, * LPEUODOWNDATA;

class eUpDown
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		eUpDown* pEUpDown = (eUpDown*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
		if (!pEUpDown)
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		WNDPROC oldproc = pEUpDown->GetOldProc();
		if (oldproc == NULL)
		{
			oldproc = DefWindowProc;
		}

		switch (message)
		{
		case WM_SIZE://容器窗口被改变时改变按钮大小
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			pEUpDown->SetPos(width, height);
			break;
		}
		case WM_NOTIFY: {
			LPNMHDR lpnmhdr = (LPNMHDR)lParam;
			// 检查消息类型
			switch (lpnmhdr->code)
			{
			case UDN_DELTAPOS:
			{
				//接受到调节器按下
				NMUPDOWN nID = *(NMUPDOWN*)lParam;
				pEUpDown->OnDeltaPos(nID.iDelta);
				//这里你可以通过 nID 来知道是哪一个按下
				break;
			}
			}
			//return TRUE;
			break;
		}
		case WM_DESTROY: {

			pEUpDown->~eUpDown();
			return FALSE;
		}
		default:
			break;
		}
		return oldproc(hWnd, message, wParam, lParam);
	};
	static LRESULT CALLBACK WndCProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		eUpDown* pEUpDown = (eUpDown*)GetWindowLongPtrW(hWnd, GWL_USERDATA);
		if (!pEUpDown)
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		WNDPROC oldproc = pEUpDown->GetCOldProc();
		if (oldproc == NULL)
		{
			oldproc = DefWindowProc;
		}

		bool is_continue = elibstl::SendToParentsHwnd(pEUpDown->GetID(), pEUpDown->GetUID(), uMsg, wParam, lParam);
		if (!is_continue)
		{
			return 0;
		}
		return oldproc(hWnd, uMsg, wParam, lParam);
	};
private:
	//容器句柄，和调节器句柄
	HWND m_hWnd, m_hParentWnd;
	//容器旧过程
	WNDPROC m_oldProc, m_ColdProc;;
	//绑定窗口的数据
	BINDWINDOWDATA m_BindWinow;
	INT m_dwWinFormID, m_dwUnitID;
public:
	~eUpDown() {
		if (m_hWnd)
		{
			::DestroyWindow(m_hWnd);
			m_hWnd = nullptr;
		}
		if (m_hParentWnd)
		{
			::SetWindowLongW(m_hParentWnd, GWL_WNDPROC, (LONG_PTR)m_oldProc);
			::DestroyWindow(m_hParentWnd);
		}

	}
	eUpDown(
		LPBYTE pAllPropertyData,
		INT nAllPropertyDataSize,
		DWORD dwStyle,
		int x,
		int y,
		int cx,
		int cy,
		HWND hParent,
		UINT nId,
		DWORD dwWinFormID,
		DWORD dwUnitID
	) :
		m_BindWinow({}),
		m_hWnd(nullptr),
		m_hParentWnd(nullptr),
		m_oldProc(nullptr),
		m_dwWinFormID(dwWinFormID), m_dwUnitID(dwUnitID),
		m_ColdProc(NULL)
	{

		//创建容器
		m_hParentWnd = CreateWindowExW(0, L"Static", 0, dwStyle | WS_VISIBLE | WS_CHILDWINDOW | WS_CLIPSIBLINGS, x, y, cx, cy, hParent, (HMENU)nId, GetModuleHandle(0), 0);
		//创建调节器

		dwStyle |= WS_CHILD | UDS_ARROWKEYS | WS_VISIBLE;
		BOOL HasData = FALSE;
		if (pAllPropertyData && nAllPropertyDataSize == sizeof(EUODOWNDATA))
		{
			HasData = TRUE;
			LPEUODOWNDATA nData = reinterpret_cast<LPEUODOWNDATA>(pAllPropertyData);
			if (nData->m_IsHorizontal)
			{
				dwStyle |= UDS_HORZ;
			}
			if (nData->m_Auto)
			{
				dwStyle |= UDS_SETBUDDYINT;
			}

		}
		m_hWnd = CreateWindowExW(0,
			UPDOWN_CLASS,
			L"",
			dwStyle,
			0,
			0,
			0,
			0,
			m_hParentWnd,
			(HMENU)nId,
			GetModuleHandle(0),
			NULL
		);

		if (HasData)
		{
			LPEUODOWNDATA nData = reinterpret_cast<LPEUODOWNDATA>(pAllPropertyData);
			SetUpDownMax(nData->m_max);
			SetUpDownMin(nData->m_min);
			SetUpDownAuto(nData->m_Auto);
			if (nData->m_win_data.m_hWnd)
			{
				BindHwnd(nData->m_win_data.m_hWnd);
			}
		}
		else
		{
			SetUpDownMax(100);
			SetUpDownMin(0);

		}
		//绑定容器句柄和对象
		SetWindowLongPtrW(m_hParentWnd, GWL_USERDATA, (LONG_PTR)this);
		//绑定容器回调函数
		m_oldProc = (WNDPROC)SetWindowLongW(m_hParentWnd, GWL_WNDPROC, (LONG_PTR)WndProc);
		//子类化组件
		SetWindowLongPtrW(m_hWnd, GWL_USERDATA, (LONG_PTR)this);
		//记录原始回调
		m_ColdProc = (WNDPROC)SetWindowLongW(m_hWnd, GWL_WNDPROC, (LONG_PTR)WndCProc);
		SetPos(cx, cy);

	}
public:
	DWORD GetID() const {

		return m_dwWinFormID;
	}
	DWORD GetUID() const {

		return m_dwUnitID;
	}
	WNDPROC GetCOldProc() const {
		if (!m_hWnd)
		{
			return 0;
		}
		if (m_ColdProc <= 0)
		{
			return 0;
		}
		return m_ColdProc;
	}
	//按下回调
	void OnDeltaPos(int nID)
	{
		EVENT_NOTIFY event(m_dwWinFormID, m_dwUnitID, 0);
		event.m_nArgCount = 1;  // 一个参数。  
		event.m_nArgValue[0] = nID;
		elibstl::NotifySys(NRS_EVENT_NOTIFY, (DWORD) & event, 0);


	}
	//设置自动,自动和绑定窗口必须同时，否则不会执行
	void SetUpDownAuto(bool nIsAuto) {
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}
		DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
		if (nIsAuto)
		{
			dwStyle |= UDS_SETBUDDYINT;
		}
		else
		{
			dwStyle &= ~UDS_SETBUDDYINT;
		}
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
	}
	//取自动
	bool GetUpDownAuto() {
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
		return (dwStyle & UDS_SETBUDDYINT) != 0;

	}
	//容器大小被改变时请调用此函数
	BOOL SetPos(int width, int height) {
		if (!m_hWnd || !m_hParentWnd)
		{
			return FALSE;
		}
		return SetWindowPos(m_hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	}
	//取容器句柄
	HWND GetContainerHwnd() {
		return m_hParentWnd;
	}
	//取调节器句柄
	HWND GetUpDownHwnd() {
		if (!m_hParentWnd)
		{
			return 0;
		}
		return m_hWnd;
	}
	//取窗口原过程
	WNDPROC GetOldProc() {
		if (!m_hParentWnd)
		{
			return nullptr;
		}
		if (m_oldProc < 0)
		{
			return nullptr;
		}
		return m_oldProc;
	}
	//取调节器上限
	int GetUpDownMax() {
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		int nMax;
		SendMessageW(m_hWnd, UDM_GETRANGE32, NULL, reinterpret_cast<LPARAM>(&nMax));
		return nMax;
	}
	//取调节器下限
	int GetUpDownMin() {
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		int nMin;
		SendMessageW(m_hWnd, UDM_GETRANGE32, reinterpret_cast<WPARAM>(&nMin), NULL);
		return nMin;
	}
	//置调节器上限
	bool SetUpDownMax(int nMax) {
		if (!m_hParentWnd || !m_hWnd)
		{
			return false;
		}
		return SendMessageW(m_hWnd, UDM_SETRANGE32, GetUpDownMin(), nMax);
	}
	//置调节器下限
	bool SetUpDownMin(int nMin) {
		if (!m_hParentWnd || !m_hWnd)
		{
			return false;
		}
		return SendMessageW(m_hWnd, UDM_SETRANGE32, nMin, GetUpDownMax());
	}
	//设置调节器横向
	void SetDirection(bool isHorizontal)
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}
		DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
		if (isHorizontal)
			dwStyle |= UDS_HORZ;
		else
			dwStyle &= ~UDS_HORZ;
		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		RECT rect = { 0,0,100,100 };
		InvalidateRect(m_hWnd, &rect, TRUE);
	}
	//取调节器是否横向
	bool IsHorizontal()
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return false;
		}
		DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
		return (dwStyle & UDS_HORZ) != 0;
	}
	//绑定窗口
	void BindHwnd(HWND nContorl) {
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}
		if (nContorl == 0)//如果输入为0则取消绑定
		{
			memset(&m_BindWinow, 0, sizeof(_EBinWindowData));
			SendMessage(m_hWnd, UDM_SETBUDDY, 0, 0);
		}
		if (!IsWindow(nContorl))
		{
			return;
		}
		m_BindWinow.m_hWnd = nContorl;
		GetWindowRect(m_hWnd, &m_BindWinow.m_Rect);
		SendMessage(m_hWnd, UDM_SETBUDDY, reinterpret_cast <WPARAM>(m_BindWinow.m_hWnd), 0);
	}
	//取绑定的窗口
	HWND GetBindHwnd() {
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		return m_BindWinow.m_hWnd;
	}
	//取绑定的窗口数据
	BINDWINDOWDATA GetBindHwndData() {
		if (!m_hParentWnd || !m_hWnd)
		{
			return {};
		}
		return m_BindWinow;
	}
};


#pragma region 易语言接口函数

#pragma endregion

static BOOL WINAPI Change(HUNIT hUnit, INT nPropertyIndex,  // 被修改的属性索引
	UNIT_PROPERTY_VALUE* pPropertyVaule, // 用作修改的相应属性数据
	LPTSTR* ppszTipText) {  //目前尚未使用


	eUpDown* pEupDown = elibstl::get_obj_from_hunit<eUpDown*>(hUnit);
	if (!pEupDown)
	{
		return false;
	}
	switch (nPropertyIndex)
	{
	case 0:
		pEupDown->SetUpDownAuto(pPropertyVaule->m_bool);
		return TRUE;
	case 1:
		pEupDown->SetUpDownMin(pPropertyVaule->m_int);
		return TRUE;
	case 2:
		pEupDown->SetUpDownMax(pPropertyVaule->m_int);
		return TRUE;
	case 3:
		pEupDown->SetDirection(pPropertyVaule->m_int);
		return TRUE;
	case 4:
	{
		pEupDown->BindHwnd(reinterpret_cast<HWND>(pPropertyVaule->m_int));
		return TRUE;
	}
	default:

		break;
	}
	return FALSE;
}
static BOOL WINAPI GetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
{
	eUpDown* pEupDown = elibstl::get_obj_from_hunit<eUpDown*>(hUnit);
	if (!pEupDown)
	{
		return false;
	}
	switch (nPropertyIndex)
	{
	case 0:
	{
		pPropertyVaule->m_bool = pEupDown->GetUpDownAuto();
		break;
	}
	case 1:
		pPropertyVaule->m_int = pEupDown->GetUpDownMin();

		break;
	case 2:
		pPropertyVaule->m_int = pEupDown->GetUpDownMax();
		break;
	case 3:
	{
		pPropertyVaule->m_int = pEupDown->IsHorizontal();
		break;
	}
	case 4:
	{
		pPropertyVaule->m_int = reinterpret_cast<INT>(pEupDown->GetBindHwnd());
		break;
	}

	default:

		return false;
	}
	return false;
}
static HGLOBAL WINAPI GetAlldata(HUNIT hUnit)
{
	eUpDown* pEupDown = elibstl::get_obj_from_hunit<eUpDown*>(hUnit);
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, sizeof(EUODOWNDATA));
	EUODOWNDATA temp;
	temp.m_Auto = pEupDown->GetUpDownAuto();
	temp.m_IsHorizontal = pEupDown->IsHorizontal();
	temp.m_max = pEupDown->GetUpDownMax();
	temp.m_min = pEupDown->GetUpDownMin();
	temp.m_win_data = pEupDown->GetBindHwndData();
	if (hGlobal)
	{
		PVOID pGlobal = ::GlobalLock(hGlobal);
		if (pGlobal)
		{
			memcpy(pGlobal, &temp, sizeof(EUODOWNDATA));
			::GlobalUnlock(hGlobal);
		}
	}
	return  hGlobal;
}
static HUNIT WINAPI Create(
	LPBYTE pAllPropertyData,            //   指向本窗口单元的已有属性数据, 由本窗口单元的ITF_GET_PROPERTY_DATA接口产生, 如果没有数据则为NULL
	INT nAllPropertyDataSize,           //   提供pAllPropertyData所指向数据的尺寸, 如果没有则为0
	DWORD dwStyle,                      //   预先设置的窗口风格
	HWND hParentWnd,                    //   父窗口句柄
	UINT uID,                           //   在父窗口中的ID
	HMENU hMenu,                        //   未使用
	INT x, INT y, INT cx, INT cy,       //   指定位置及尺寸
	DWORD dwWinFormID, DWORD dwUnitID,  //   本窗口单元所在窗口及本身的ID, 用作通知到系统
	HWND hDesignWnd,                    //   如果blInDesignMode为真, 则hDesignWnd提供所设计窗口的窗口句柄
	BOOL blInDesignMode                 //   说明是否被易语言IDE调用以进行可视化设计, 运行时为假
)
{
	eUpDown* pUpDown = new eUpDown(pAllPropertyData, nAllPropertyDataSize, dwStyle, x, y, cx, cy, hParentWnd, uID, dwWinFormID, dwUnitID);
	return elibstl::make_cwnd(pUpDown->GetContainerHwnd());
}
static INT WINAPI DefSize(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	switch (nMsg)
	{
	case NU_GET_CREATE_SIZE_IN_DESIGNER:
	{
		*((int*)dwParam1) = 17;
		*((int*)dwParam2) = 110;
	}
	return TRUE;
	}
	return FALSE;
}


EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_UpDown(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
	{
		// 创建组件
		return (PFN_INTERFACE)Create;
	}
	case ITF_NOTIFY_PROPERTY_CHANGED:
	{
		// 通知某属性数据被用户修改
		return (PFN_INTERFACE)Change;
	}
	case ITF_GET_ALL_PROPERTY_DATA:
	{
		// 取全部属性数据
		return (PFN_INTERFACE)GetAlldata;
	}
	case ITF_GET_PROPERTY_DATA:
	{
		// 取某属性数据
		return (PFN_INTERFACE)GetData;
	}
	case ITF_GET_NOTIFY_RECEIVER:
	{
		// 取组件的附加通知接收者(PFN_ON_NOTIFY_UNIT)
		return (PFN_INTERFACE)DefSize;
	}
	default:
		return NULL;
	}
	return NULL;
}




static INT s_cmd[] = { 121 };


namespace elibstl {

	LIB_DATA_TYPE_INFO UpDown = {
		"调节器",//中文名称
		"UpDown",//英文名称
		"类似编辑的调节器，具有更多的功能和拓展性",//说明
		sizeof(s_cmd) / sizeof(INT),//命令数量
		s_cmd,//在全局函数中对应的索引
		_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
		IDB_UPDOWN_EX,//资源ID
		sizeof(s_event) / sizeof(s_event[0]),
		s_event,//事件
		sizeof(s_member) / sizeof(s_member[0]),//属性数
		s_member,//属性指针
		libstl_GetInterface_UpDown,//组件交互子程序
		NULL,//成员数量
		NULL//成员数据数组
	};
}


EXTERN_C void Fn_EUpDown_GetHwnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eUpDown* pEUpDown = (eUpDown*)GetWindowLongPtrW(hWnd, GWL_USERDATA);

	pRetData->m_int = reinterpret_cast<INT>(pEUpDown->GetUpDownHwnd());
}


FucInfo EUpDown_GetHwnd = { {
		/*ccname*/  ("取组件句柄"),
		/*egname*/  ("GetHwnd"),
		/*explain*/ ("取窗口句柄获取的为容器句柄,此命令为取出调节器组件的句柄。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_EUpDown_GetHwnd ,"Fn_EUpDown_GetHwnd" };


