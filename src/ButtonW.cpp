#include"EcontrolHelp.h"
#pragma warning(disable:4996)
using namespace std;
#define PARBUTTONPROC L"Buntton_ParentOldProc"




static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK WndCProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//后紧随图片，图片后直到数据结束为窗口标题
typedef struct _EButtonExDATA
{
	//横向对齐方式
	INT m_transverse;
	//纵向对齐方式
	INT m_portrait;
	//字体数据
	EFONTDATA m_font_data;
	//图片长度
	DWORD m_pic_lenth;
	_EButtonExDATA()
	{
		memset(this, 0, sizeof(_EButtonExDATA));
	}
	LPBYTE get_pic(DWORD* size) {
		*size = 0;
		if (m_pic_lenth <= 0)
		{
			return 0;
		}
		*size = m_pic_lenth;
		return reinterpret_cast<LPBYTE>(this) + sizeof(_EButtonExDATA);
	};
	DWORD get_size_with_pic() {
		return sizeof(_EButtonExDATA) + m_pic_lenth;
	}
	wchar_t* get_text() {
		return reinterpret_cast<wchar_t*>(reinterpret_cast<LPBYTE>(this) + sizeof(_EButtonExDATA) + m_pic_lenth);
	}
} EBUTTONDATA, * PEBUTTONDATA;//后面紧跟图片的数据，数据长度为piclenth

class eButtonEx
{
public:
	eButtonEx(
		LPVOID data,
		size_t lenth,
		DWORD dwStyle,
		int x,
		int y,
		int cx,
		int cy,
		HWND hParent,
		UINT nId,
		BOOL blInDesignMode,
		DWORD dwWinFormID,
		DWORD dwUnitID
	) :m_hParentWnd(NULL),
		m_hWnd(NULL),
		m_oldProc(NULL),
		m_blInDesignMode(blInDesignMode),
		m_dwWinFormID(dwWinFormID),
		m_dwUnitID(dwUnitID),
		m_TextA(NULL),
		m_transverse(1),
		m_portrait(1),
		m_hBitmap(NULL),
		m_TextW(NULL),
		m_ColdProc(NULL)

	{
		//操作的是组件容器
		m_hParentWnd = CreateWindowExW(0, L"Static", 0, dwStyle | WS_VISIBLE | WS_CHILDWINDOW | WS_CLIPSIBLINGS, x, y, cx, cy, hParent, (HMENU)nId, GetModuleHandle(0), 0);
		//窗口风格
		dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_MULTILINE | BS_PUSHBUTTON | WS_CLIPSIBLINGS | dwStyle;
		//创建按钮
		if (data)
		{
			wstring Title = L"按钮";
			PEBUTTONDATA base = reinterpret_cast<PEBUTTONDATA>(data);


			if (lenth - base->get_size_with_pic() > 0)//如果标题不为空
			{
				Title = wstring(base->get_text(), (lenth - base->get_size_with_pic()) / 2);
			}
			m_hWnd = CreateWindowExW(0, WC_BUTTON, Title.c_str(), dwStyle, 0, 0, cx, cy, m_hParentWnd, (HMENU)nId, GetModuleHandle(0), 0);
			if (base->m_font_data.m_hFont)//字体有效
			{
				SetFont(base->m_font_data.m_data);
			}
			SetButtonTextTransverse(base->m_transverse);
			SetButtonTextPortrait(base->m_portrait);
			DWORD picsize = 0;
			LPBYTE pic = base->get_pic(&picsize);
			if (picsize > 0 && pic)
			{
				SetButtonPicture(pic, picsize);
			}
		}
		else {
			m_hWnd = CreateWindowExW(0, WC_BUTTON, L"按钮W", dwStyle, 0, 0, cx, cy, m_hParentWnd, (HMENU)nId, GetModuleHandle(0), 0);
			strcpy_s(m_Fontdata.m_data.lfFaceName, "SimSun");
			m_Fontdata.m_data.lfHeight = 13;
			m_Fontdata.m_hFont = CreateFontIndirectA(&m_Fontdata.m_data);
			SendMessageW(m_hWnd, WM_SETFONT, (WPARAM)m_Fontdata.m_hFont, 1);
			//DeleteObject(temp_hFont);
		}


		//子类化容器
		SetWindowLongPtrW(m_hParentWnd, GWLP_USERDATA, (LONG_PTR)this);
		//记录原始回调
		m_oldProc = (WNDPROC)SetWindowLongW(m_hParentWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

		//子类化组件
		SetWindowLongPtrW(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
		//记录原始回调
		m_ColdProc = (WNDPROC)SetWindowLongW(m_hWnd, GWLP_WNDPROC, (LONG_PTR)WndCProc);

	}
	EBUTTONDATA GetBaseData() const {
		EBUTTONDATA temp;
		temp.m_font_data = m_Fontdata;
		temp.m_pic_lenth = m_picdata.size();
		temp.m_portrait = m_portrait;
		temp.m_transverse = m_transverse;
		return temp;
	}
	WNDPROC GetOldProc() const {
		if (!m_hParentWnd)
		{
			return 0;
		}
		if (m_oldProc <= 0)
		{
			return 0;
		}
		return m_oldProc;
	}
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
	HWND GetChild()const {
		if (!m_hParentWnd)
		{
			return 0;
		}
		return m_hWnd;
	}
	BOOL isDesign()const {
		return m_blInDesignMode;
	}
	BOOL SetPos(int width, int height) {//容器被改变时请调用此函数
		return SetWindowPos(m_hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	}
	HWND GetHwnd()const {
		return m_hParentWnd;
	}
	void OnClick() {
		EVENT_NOTIFY2 event(m_dwWinFormID, m_dwUnitID, 0);
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
	}
	void OnKEYDOWN_UP(UINT MSG, WPARAM wparam, int mod) {

		EVENT_NOTIFY2 event(m_dwWinFormID, m_dwUnitID, 247 - MSG);
		event.m_nArgCount = 2;
		event.m_arg[0].m_inf.m_int = wparam;
		event.m_arg[1].m_inf.m_int = mod;
		elibstl::NotifySys(NRS_EVENT_NOTIFY2, (DWORD) & event, 0);
	}

	//内部使用的
	void SetText(const wchar_t* text)
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}

		SetWindowTextW(m_hWnd, text);
	}
	void SetText(const char* text)
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}

		SetWindowTextA(m_hWnd, text);
	}
	std::wstring GetText() const
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return std::wstring();
		}
		int length = GetWindowTextLengthW(m_hWnd);
		std::vector<wchar_t> buffer(length + 1);
		GetWindowTextW(m_hWnd, buffer.data(), buffer.size());
		return std::wstring(buffer.data());
	}
	//给易使用的
	void SetButtonTextTransverse(INT transverse)
	{
		if (transverse >= 0 && transverse <= 2)
		{
			m_transverse = transverse;
			DWORD style = transverse == 0 ? BS_LEFT : transverse == 1 ? BS_CENTER : BS_RIGHT;
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, (GetWindowLongPtrW(m_hWnd, GWL_STYLE) & ~(BS_LEFT | BS_CENTER | BS_RIGHT)) | style);
		}

	}
	INT GetButtonTextTransverse() {
		return m_transverse;

	}
	INT GetButtonTextPortrait() {
		return m_portrait;

	}
	void SetButtonTextPortrait(INT portrait)
	{
		if (portrait >= 0 && portrait <= 2)
		{
			m_portrait = portrait;
			DWORD style = portrait == 0 ? BS_TOP : portrait == 1 ? BS_VCENTER : BS_BOTTOM;
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, (GetWindowLongPtrW(m_hWnd, GWLP_STYLE) & ~(BS_TOP | BS_VCENTER | BS_BOTTOM)) | style);
		}
	}
	char* GetTextAtoE()
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		if (m_TextA)
		{
			delete[]m_TextA;
			m_TextA = NULL;
		}
		int length = GetWindowTextLengthA(m_hWnd);
		m_TextA = new char[length + 1]{ 0 };
		GetWindowTextA(m_hWnd, m_TextA, length);
		return m_TextA;
	}
	wchar_t* GetTextWtoE()
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		if (m_TextA)
		{
			delete[]m_TextA;
			m_TextA = NULL;
		}
		int length = GetWindowTextLengthW(m_hWnd);
		m_TextW = new wchar_t[length + 1]{ 0 };
		GetWindowTextW(m_hWnd, m_TextW, length);
		return m_TextW;
	}
	~eButtonEx() {
		//释放资源
		delete_data();
		//销毁按钮
		destroy_button();
		//交还WNDPROC
		if (m_hParentWnd)
		{
			::SetWindowLongW(m_hParentWnd, GWLP_WNDPROC, (LONG_PTR)m_oldProc);
		}
		m_hParentWnd = NULL;
		//再被销毁→
	}
	void SetFont(LOGFONTA Font)
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}
		if (m_Fontdata.m_hFont) {//存在句柄则销毁

			DeleteObject(m_Fontdata.m_hFont);
			m_Fontdata.m_hFont = NULL;
		}
		memcpy(&m_Fontdata.m_data, &Font, sizeof(LOGFONTA));
		m_Fontdata.m_hFont = CreateFontIndirectA(&Font);
		SendMessageW(m_hWnd, WM_SETFONT, (WPARAM)m_Fontdata.m_hFont, 1);
	}
	LOGFONTA* GetFont()
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		if (!m_Fontdata.m_hFont) {//存在句柄则销毁

			return 0;
		}
		return &m_Fontdata.m_data;
	}

	void SetButtonPicture(LPBYTE pData, DWORD nSize)
	{
		if (!m_hParentWnd || !m_hWnd)
		{
			return;
		}
		if (!m_picdata.empty())
		{
			m_picdata = {};
		}
		if (m_hBitmap)
		{
			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
		}

		if (pData != NULL && nSize != 0)
		{
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) | BS_BITMAP);
			m_hBitmap = elibstl::make_hbit(pData, nSize);
			if (m_hBitmap)
			{
				SendMessageW(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
				BITMAP bmp;
				GetObject(m_hBitmap, sizeof(BITMAP), &bmp);
				m_picdata.resize(nSize);
				memcpy(m_picdata.data(), pData, nSize);
				/*if (!m_picdata.empty())
				{
					out_pBuffer = new unsigned char[m_picdata.size()];
					memcpy(out_pBuffer, m_picdata.data(), m_picdata.size());
				}*/
			}
		}
		else
		{
			SetWindowLongPtrW(m_hWnd, GWL_STYLE, GetWindowLongPtrW(m_hWnd, GWL_STYLE) & ~BS_BITMAP);
			int length = GetWindowTextLengthW(m_hWnd);
			std::vector<wchar_t> buffer(length + 1);
			GetWindowTextW(m_hWnd, buffer.data(), buffer.size());
			SendMessageW(m_hWnd, WM_SETTEXT, 0, (LPARAM)buffer.data());
		}
	}
	vector<unsigned char>* GetButtonPicture() {
		if (!m_hParentWnd || !m_hWnd)
		{
			return 0;
		}
		if (m_picdata.empty())
		{
			return 0;
		}
		if (!m_hBitmap)
		{
			return 0;
		}
		return &m_picdata;
	}

private:
	void delete_data() {
		if (m_TextA)
		{
			delete[]m_TextA;
			m_TextA = NULL;
		}
		if (m_TextW)
		{
			delete[]m_TextW;
			m_TextW = NULL;
		}
		if (m_Fontdata.m_hFont) {//字体创建过便销毁

			DeleteObject(m_Fontdata.m_hFont);
			m_Fontdata.m_hFont = NULL;
		}
		if (m_hBitmap) {//图片

			DeleteObject(m_hBitmap);
			m_hBitmap = NULL;
		}
	}
	void destroy_button() {
		if (m_hWnd)
		{
			::DestroyWindow(m_hWnd);
			m_hWnd = NULL;
		}
	}

private:
	//需要保存的数据
	//标题
	HBITMAP m_hBitmap;
	vector<unsigned char> m_picdata;
	wchar_t* m_TextW;
	char* m_TextA;
	INT m_transverse, m_portrait;
	EFONTDATA m_Fontdata;
	//易里用来区分组件的标识
	DWORD m_dwWinFormID, m_dwUnitID;
	HWND m_hParentWnd,//容器句柄
		m_hWnd;//按钮句柄
	WNDPROC m_oldProc, m_ColdProc;
	BOOL m_blInDesignMode;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	eButtonEx* pButton = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	if (!pButton)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	WNDPROC oldproc = pButton->GetOldProc();
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
		pButton->SetPos(width, height);
		break;
	}
	case WM_COMMAND:
		//按钮单击事件
		if (HIWORD(wParam) == BN_CLICKED) {
			if (reinterpret_cast<HWND>(lParam) == pButton->GetChild()) {
				pButton->OnClick();
			}
		}
		break;
	case WM_DESTROY:
		pButton->~eButtonEx();
		break;
	default:
		break;
	}
	return oldproc(hWnd, message, wParam, lParam);
};

static LRESULT CALLBACK WndCProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	eButtonEx* pButton = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	if (!pButton)
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	WNDPROC oldproc = pButton->GetCOldProc();
	if (oldproc == NULL)
	{
		oldproc = DefWindowProc;
	}

	bool is_continue = SendToParentsHwnd(pButton->GetID(), pButton->GetUID(), uMsg, wParam, lParam);
	if (!is_continue)
	{
		return 0;
	}
	return oldproc(hWnd, uMsg, wParam, lParam);
};



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
	eButtonEx* Button = new eButtonEx(pAllPropertyData, nAllPropertyDataSize, dwStyle, x, y, cx, cy, hParentWnd, uID, blInDesignMode, dwWinFormID, dwUnitID);
	return elibstl::make_cwnd(Button->GetHwnd());
}


static BOOL WINAPI Change(HUNIT hUnit, INT nPropertyIndex,  // 被修改的属性索引
	UNIT_PROPERTY_VALUE* pPropertyVaule, // 用作修改的相应属性数据
	LPTSTR* ppszTipText) {  //目前尚未使用
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
	eButtonEx* Button = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);;

	switch (nPropertyIndex)
	{
	case 0: {
		LPBYTE pData = pPropertyVaule->m_data.m_pData;
		DWORD nSize = pPropertyVaule->m_data.m_nDataSize;
		Button->SetButtonPicture(pData, nSize);
		break;
	}
	case 1:
		Button->SetText(pPropertyVaule->m_szText);
		break;
	case 2:
		Button->SetButtonTextTransverse(pPropertyVaule->m_int);
		break;
	case 3:
		Button->SetButtonTextPortrait(pPropertyVaule->m_int);
		break;
	case 4: {
		LOGFONTA* Font = (LOGFONTA*)pPropertyVaule->m_int;
		Button->SetFont(*Font);
	}
		  break;
	case 5:
	{
		if (pPropertyVaule->m_data.m_pData && pPropertyVaule->m_data.m_nDataSize)
		{
			std::vector<unsigned char> wcs(pPropertyVaule->m_data.m_pData, pPropertyVaule->m_data.m_pData + pPropertyVaule->m_data.m_nDataSize);
			std::wstring wstr;
			wstr.append((wchar_t*)wcs.data(), wcs.size() / sizeof(wchar_t));
			Button->SetText(wstr.c_str());
		}
		return FALSE;
	}
	default:
		break;
	}
	return 1;
}

static HGLOBAL WINAPI GetAlldata(HUNIT hUnit)
{
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);

	eButtonEx* Button = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);;
	//获取基础数据
	EBUTTONDATA temp = Button->GetBaseData();
	//获取标题
	wstring temp_title = Button->GetText();
	//获取图片数据
	vector<unsigned char>* temp_pic = nullptr;
	if (temp.m_pic_lenth > 0)
	{
		temp_pic = Button->GetButtonPicture();
	}
	//再次验证
	if (!temp_pic)
	{
		temp.m_pic_lenth = 0;
	}
	//基础数据+图片长度+文本长度
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, sizeof(EBUTTONDATA) + temp.m_pic_lenth + temp_title.size() * sizeof(wchar_t));
	if (hGlobal)
	{
		PVOID pGlobal = ::GlobalLock(hGlobal);
		if (pGlobal)
		{
			memcpy(pGlobal, &temp, sizeof(EBUTTONDATA));
			if (temp.m_pic_lenth != 0 && temp_pic)
			{
				memcpy((LPBYTE)pGlobal + sizeof(EBUTTONDATA), temp_pic->data(), temp_pic->size());
			}
			if (temp_title.size() > 0)
			{
				memcpy((LPBYTE)pGlobal + sizeof(EBUTTONDATA) + temp.m_pic_lenth, temp_title.c_str(), temp_title.size() * sizeof(wchar_t));
			}
			::GlobalUnlock(hGlobal);
		}
	}
	return hGlobal;
}

static BOOL WINAPI GetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
{
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
	eButtonEx* Button = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);;
	if (!Button)
	{
		return 0;
	}
	switch (nPropertyIndex)
	{
	case 0:
	{
		vector<unsigned char>* data = Button->GetButtonPicture();
		if (data && data->size() != 0)
		{
			pPropertyVaule->m_data.m_nDataSize = data->size();
			pPropertyVaule->m_data.m_pData = data->data();
		}
		return FALSE;
	}
	case 1:
	{
		pPropertyVaule->m_szText = Button->GetTextAtoE();
		return FALSE;
	}
	case 2:
	{
		pPropertyVaule->m_int = Button->GetButtonTextTransverse();
		return FALSE;
	}
	case 3:
	{
		pPropertyVaule->m_int = Button->GetButtonTextPortrait();
		return FALSE;
	}
	case 4:
	{
		LOGFONTA* Font = Button->GetFont();
		if (Font)
		{
			pPropertyVaule->m_data.m_pData = (LPBYTE)Font;
			pPropertyVaule->m_data.m_nDataSize = sizeof(LOGFONTA);
		}
		return FALSE;
	}
	case 5:
	{
		wchar_t* wText = Button->GetTextWtoE();
		if (wText)
		{
			pPropertyVaule->m_data.m_pData = (LPBYTE)wText;
			pPropertyVaule->m_data.m_nDataSize = wcslen(wText);
		}
		return FALSE;
	}
	default:
		return false;
	}
	return true;
}
static BOOL WINAPI InputW(HUNIT hUnit, INT nPropertyIndex,
	BOOL* pblModified, LPVOID pResultExtraData)
{
	HWND hWnd = elibstl::get_hwnd_from_hunit(hUnit);
	eButtonEx* Button = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);;
	if (nPropertyIndex == 5)
	{
		Button->SetText(MyInputBox(Button->GetText()).c_str());
		*pblModified = true;
	}
	return *pblModified;
}

EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_ButtonW(INT nInterfaceNO)
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
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
	{
		return (PFN_INTERFACE)InputW;
	}
	default:
		return NULL;
	}
	return NULL;
}

static EVENT_INFO2 s_event[] =
{
	/*000*/ {"按钮被单击", "当按钮被单击时触发", _EVENT_OS(OS_ALL) | EV_IS_VER2, 0, 0, _SDT_NULL},
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
	/*000*/ {"图片", "PIC", "", UD_PIC, _PROP_OS(__OS_WIN), NULL},
	/*002*/ {"标题", "Titile", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_TEXT, _PROP_OS(__OS_WIN), NULL},
	/*003*/ {"横向对齐方式", "", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "左边\0""局中\0""右边\0""\0"},
	/*004*/ {"纵向对齐方式", "", "", UD_PICK_INT, _PROP_OS(__OS_WIN), "上边\0""局中\0""下边\0""\0"},
	/*005*/ {"字体", "Font", "用作在运行时提供浏览器的当前标题文本", UD_FONT, _PROP_OS(__OS_WIN) , NULL},
	/*000*/ {"标题W", "PIC", "按钮标题在设置时支持最大259个字符，代码运行过程中没有限制", UD_CUSTOMIZE, _PROP_OS(__OS_WIN), NULL},
};

static INT s_cmd[] = { 120 };
namespace elibstl {


	LIB_DATA_TYPE_INFO buttonw = {
		"按钮W",//中文名称
		"ButtonW",//英文名称
		"unicode按钮",//说明
		sizeof(s_cmd) / sizeof(INT),//命令数量
		s_cmd,//在全局函数中对应的索引
		_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
		103,//资源ID
		sizeof(s_event) / sizeof(s_event[0]),
		s_event,
		sizeof(s_member) / sizeof(s_member[0]),//属性数
		s_member,//属性指针
		libstl_GetInterface_ButtonW,//组件交互子程序
		NULL,//成员数量
		NULL//成员数据数组
	};



}
EXTERN_C void Fn_EButtonW_GetHwnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND hWnd = elibstl::get_hwnd_from_arg(pArgInf);
	eButtonEx* Button = (eButtonEx*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);

	pRetData->m_int = reinterpret_cast<INT>(Button->GetChild());
}


FucInfo EButtonW_GetHwnd = { {
		/*ccname*/  ("取组件句柄"),
		/*egname*/  ("GetHwnd"),
		/*explain*/ ("取窗口句柄获取的为容器句柄,此命令为取出组件的句柄。"),
		/*category*/-1,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} , Fn_EButtonW_GetHwnd ,"Fn_EButtonW_GetHwnd" };