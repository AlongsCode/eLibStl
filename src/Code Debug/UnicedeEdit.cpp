#include<windows.h>
#include<CommCtrl.h>
#include<Richedit.h>
#include<string>
#include<vector>
#include"elib\fnshare.h"
namespace elibstl {
	/*易语言调试框*/
	HBITMAP make_hbm_gp(BYTE* pData, SIZE_T cbPic);
	class RichEdit
	{
	public:
		void Create(HWND parentWnd, const WCHAR* WindowName, int x, int y, int width, int height, DWORD dwStyle)
		{
			if (!m_isInit)
			{
				return;

			}
			/*| ES_AUTOHSCROLL| WS_HSCROLL*/
			DWORD dwDefStyle = ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | WS_TABSTOP
				| ES_NOHIDESEL | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
			dwStyle |= dwDefStyle;

			// 创建 RichEdit 控件
			m_hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, WindowName, dwStyle,
				x, y, width, height, parentWnd, NULL, GetModuleHandle(NULL), NULL);
			if (!m_hWnd)
			{
				OutputDebugStringW(std::to_wstring(GetLastError()).c_str());
			}
		}
		RichEdit() {
			/*载入 2.0
				NOTE:  MSFTEDIT.DLL only registers MSFTEDIT_CLASS.
				*/
			HMODULE hRichEditDLL = LoadLibraryW(L"MSFTEDIT.DLL");
			if (hRichEditDLL != NULL)
			{
				m_isInit = true;
			}
		}
		~RichEdit()
		{
			if (m_hWnd != NULL)
			{
				if (IsWindow(m_hWnd)) {
					/*防止已经被销毁*/
					DestroyWindow(m_hWnd);
				};

				m_hWnd = NULL;
			}
		}
		void SetText(const wchar_t* text)  const
		{
			SendMessageW(m_hWnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(text));
		}
		/*移动*/
		void Move(int left, int top, int width, int height) const
		{
			MoveWindow(m_hWnd, left, top, width, height, TRUE);
		}
		/*获取文本*/
		std::wstring GetText()  const
		{
			int length = GetWindowTextLengthW(m_hWnd) + 1;
			std::wstring buffer(length, L'\0');
			GetWindowTextW(m_hWnd, &buffer[0], length);
			return buffer;
		}
		/*清空文本*/
		void ClearText()  const
		{
			SetWindowTextW(m_hWnd, L"");
		}
		/*追加文本*/
		void AppendText(const wchar_t* text) const
		{
			int length = GetWindowTextLengthW(m_hWnd);
			SendMessageW(m_hWnd, EM_SETSEL, length, length);
			SendMessageW(m_hWnd, EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(text));
		}
		/*添加图片*/
		void AppendImage(HBITMAP hBitmap)   const
		{
			// 将图片数据转换为富文本格式
			FORMATETC format;
			format.cfFormat = CF_BITMAP;
			format.ptd = NULL;
			format.dwAspect = DVASPECT_CONTENT;
			format.lindex = -1;
			format.tymed = TYMED_GDI;

			STGMEDIUM stg;
			stg.tymed = TYMED_GDI;
			stg.hBitmap = hBitmap;
			stg.pUnkForRelease = NULL;

			// 将图片数据插入到富文本框中
			SendMessage(m_hWnd, EM_SETEDITSTYLE, SES_EMULATESYSEDIT, SES_EMULATESYSEDIT);
			SendMessage(m_hWnd, EM_SETSEL, -1, -1);
			SendMessage(m_hWnd, EM_SETEDITSTYLE, SES_EMULATESYSEDIT, 0);
			SendMessage(m_hWnd, EM_REPLACESEL, TRUE, (LPARAM)&stg);
		}
		void AppendImage(const std::vector<unsigned char>& pPicData) const
		{
			// 将图像数据创建为 HBITMAP
			HBITMAP hBitmap = elibstl::make_hbm_gp(const_cast<unsigned char*>(pPicData.data()), pPicData.size());

			if (hBitmap != NULL)
			{
				// 调用 AppendImage 方法输出图片
				AppendImage(hBitmap);

				// 释放 HBITMAP
				DeleteObject(hBitmap);
			}
		}
		void AppendImage(unsigned char* pPicData, size_t cbSize) const
		{
			// 将图像数据创建为 HBITMAP
			HBITMAP hBitmap = elibstl::make_hbm_gp(pPicData, cbSize);
			if (hBitmap != NULL)
			{
				// 调用 AppendImage 方法输出图片
				AppendImage(hBitmap);

				// 释放 HBITMAP
				DeleteObject(hBitmap);
			}
		}
	private:
		/*置选中区域格式*/
		bool SetSelectionCharacterFormat(const CHARFORMAT2W& format)   const
		{
			CHARFORMAT2W cf;
			cf.cbSize = sizeof(CHARFORMAT2W);
			cf.dwMask = CFM_FACE | CFM_EFFECTS | CFM_SIZE | CFM_OFFSET | CFM_COLOR | CFM_CHARSET;
			auto len = lstrlenW(format.szFaceName);
			if (len > LF_FACESIZE - 1)
			{
				len = LF_FACESIZE - 1;
			}
			wcsncpy_s(cf.szFaceName, format.szFaceName, len);
			cf.szFaceName[len] = L'\0';
			cf.dwEffects = format.dwEffects & ~CFE_AUTOCOLOR;
			cf.yHeight = format.yHeight;
			cf.yOffset = format.yOffset;
			cf.crTextColor = format.crTextColor;
			cf.bCharSet = format.bCharSet;
			cf.bPitchAndFamily = format.bPitchAndFamily;
			return SendMessageW(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, reinterpret_cast<LPARAM>(&cf)) != 0;
		}
		/*置选中区域*/
		bool SetSelection(int startPosition, int endPosition)   const
		{
			CHARRANGE range;
			range.cpMin = startPosition;
			range.cpMax = endPosition;
			return SendMessageW(m_hWnd, EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&range)) != 0;
		}
		HWND m_hWnd = NULL;
		bool m_isInit = false;
	};



	class EDebugEdit
	{
	public:
		RichEdit m_hRicEdit{};
		/*易语言IDE句柄*/
		HWND m_hEplIDE = NULL;
		/*选择卡句柄主要是用于控制切换是的隐藏和显示*/
		HWND m_hTab = NULL;;
		/*选择夹句柄*/
		HWND m_hTabControl = NULL;
		/*调试框句柄*/
		HWND m_hDebugBox = NULL;
		/*是否初始化成功*/
		bool m_isCreate = false;

		/*************************以下为回调*************************/
		/*原选项卡回调，销毁需还原*/
		WNDPROC m_WndOldProcTab = nullptr;
		/*原选择夹回调，销毁需还原*/
		WNDPROC m_WndOldProcTabControl = nullptr;
		/*原调试框回调，销毁需还原*/
		WNDPROC m_WndOldProcDebugBox = nullptr;


	public:
		EDebugEdit() {
			/*初始化失败*/
			m_isCreate = GetEplDebugOutputWindow();
			if (!m_isCreate) {
				return;
			};
			GetOldDataAndMakeNewWnd();
			SubDebugBoxClass();
		};
		~EDebugEdit() {
			/*交还原过程*/
			ReturnOldProc();

		};

	private:
		void GetOldDataAndMakeNewWnd() {
			/*获取原数据*/
			/*原始风格*/
			auto dwStyle = GetWindowLongPtrW(m_hDebugBox, GWL_STYLE);
			/*窗口类名*/
			wchar_t szClassName[MAX_PATH + 1]{ 0 };
			GetClassNameW(m_hDebugBox, szClassName, MAX_PATH);
			/*字体*/
			auto hFontA = SendMessageW(m_hDebugBox, WM_GETFONT, 0, 0);
			/*窗口位置*/
			RECT  rect;
			GetWindowRect(m_hDebugBox, &rect);
			/*取客户取坐标*/
			POINT point = { rect.left ,rect.top };
			ScreenToClient(m_hTabControl, &point);
			/*取原内容*/
			int WindowNameW_len = GetWindowTextLengthW(m_hDebugBox);
			std::wstring WindowNameW(WindowNameW_len, L'\0');
			GetWindowTextW(m_hDebugBox, &WindowNameW[0], WindowNameW_len + 1);

			m_hRicEdit.Create(m_hTabControl, WindowNameW.c_str(), point.x, point.y, rect.right - rect.left, rect.bottom - rect.top, dwStyle);

		}
		/*交还原过程*/
		void ReturnOldProc() {
			if (m_WndOldProcTab)
			{
				SetWindowLongPtrW(m_hTab, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_WndOldProcTab));
				m_WndOldProcTab = nullptr;
			}

			if (m_WndOldProcTabControl)
			{
				SetWindowLongPtrW(m_hTabControl, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_WndOldProcTabControl));
				m_WndOldProcTabControl = nullptr;
			}

			if (m_WndOldProcDebugBox)
			{
				SetWindowLongPtrW(m_hDebugBox, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_WndOldProcDebugBox));
				m_WndOldProcDebugBox = nullptr;
			}
		}

		/*获取易语言IDE窗口句柄*/
		HWND GetEplIDEWindowHandle()
		{
			if (m_hEplIDE)
				return m_hEplIDE;

			auto hProcessID = GetCurrentProcessId();
			if (hProcessID == NULL)
				return NULL;
			struct EFINDWND
			{
				DWORD m_hProcessID;
				HWND m_RetWnd;
				EFINDWND(DWORD hProcessID, HWND RetWnd) {
					m_hProcessID = hProcessID;
					m_RetWnd = RetWnd;
				}
			};
			EFINDWND eFindWindow(hProcessID, NULL);
			if (EnumWindows(&EnumWindowsProc_ENewFrame, reinterpret_cast<LPARAM> (&eFindWindow))) {
				return NULL;
			}
			return eFindWindow.m_RetWnd;
		}
		/*获取易语言调试输出窗口句柄*/
		bool GetEplDebugOutputWindow() {

			m_hEplIDE = GetEplIDEWindowHandle();
			if (m_hEplIDE == NULL)
			{
				return false;
			}
			auto Temp_hWnd = FindWindowExW(m_hEplIDE, 0, L"AfxControlBar42s", L"状态夹");
			if (Temp_hWnd == NULL)
			{
				return NULL;
			}
			Temp_hWnd = GetDlgItem(Temp_hWnd, 130);
			if (Temp_hWnd == NULL)
			{
				return false;
			}
			m_hTab = FindWindowExW(Temp_hWnd, 0, L"#32770", NULL);
			if (m_hTab == NULL)
			{
				return false;
			}
			/*寻找选择夹*/
			m_hTabControl = FindWindowExW(m_hTab, 0, L"SysTabControl32", NULL);
			if (m_hTabControl == NULL)
			{
				return false;
			}
			/*原调试输出框*/
			m_hDebugBox = GetDlgItem(m_hTabControl, 1011);
			return true;

		}
		/*子类化,获取数据等*/
		void SubDebugBoxClass() {
			/*选择夹绑定对象*/
			SetWindowLongPtrW(m_hTab, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
			/*子类化选择卡,用于控制选择夹的切换*/
			m_WndOldProcTab = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(m_hTab, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProcTab)));

			/*原调试框绑定对象*/
			SetWindowLongPtrW(m_hDebugBox, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
			/*子类化原调试框*/
			m_WndOldProcDebugBox = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(m_hDebugBox, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProcDebugBox)));


		}


	private:
		/*枚举易窗口*/
		static BOOL CALLBACK EnumWindowsProc_ENewFrame(HWND hwnd, LPARAM lParam) {
			struct EFINDWND
			{
				DWORD m_hProcessID;
				HWND m_RetWnd;
			};
			EFINDWND* data = reinterpret_cast<EFINDWND*>(lParam);
			DWORD dwProcessID = NULL;
			GetWindowThreadProcessId(hwnd, &dwProcessID);
			WCHAR szClassName[MAX_PATH + 1]{ 0 };
			GetClassNameW(hwnd, szClassName, MAX_PATH);

			if (dwProcessID == data->m_hProcessID && wcscmp(szClassName, L"ENewFrame") == 0) {
				data->m_RetWnd = hwnd;
				return FALSE;
			}
			else
				return TRUE;
		}
		/*选择夹回调*/
		static LRESULT CALLBACK WndProcTab(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
			auto now = reinterpret_cast<EDebugEdit*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (!now)
				return DefWindowProcW(hWnd, Msg, wParam, lParam);
			ShowWindow(now->m_hDebugBox, SW_HIDE);
			return CallWindowProcW(now->m_WndOldProcTab, hWnd, Msg, wParam, lParam);

		}

		/*原调试框回调*/
		static LRESULT CALLBACK WndProcDebugBox(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
			auto now = reinterpret_cast<EDebugEdit*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

			if (!now)
				return DefWindowProcW(hWnd, Msg, wParam, lParam);
			switch (Msg)
			{
			case WM_WINDOWPOSCHANGED: {

				WINDOWPOS* windowPos = reinterpret_cast<WINDOWPOS*>(lParam);
				//检查是否改变
				if ((windowPos->flags & SWP_NOSIZE) == 0 || (windowPos->flags & SWP_NOMOVE) == 0)
				{
					now->m_hRicEdit.Move(windowPos->x, windowPos->y, windowPos->cx, windowPos->cy);
				}

			}break;
			case EM_REPLACESEL: {
				if (lParam == NULL)
					break;
				auto text = reinterpret_cast<const WCHAR*>(lParam);
				if (text && wcslen(text))
				{
					now->m_hRicEdit.AppendText(text);
				}


			}break;
			default:

				break;
			}
			return CallWindowProcW(now->m_WndOldProcDebugBox, hWnd, Msg, wParam, lParam);

		}
	};


	static EDebugEdit& GetRichEdit() {
		/*用于延迟初始化*/
		static EDebugEdit instance;
		return instance;

	}
	/*输出图片*/
	void e_debugbox_putimg(unsigned char* pPicData, size_t cbSize) {
		auto pbox = GetRichEdit();;
		//
		/*置图片*/
		pbox.m_hRicEdit.AppendImage(pPicData, cbSize);

	}
	void e_debugbox_init() {
		GetRichEdit();
	}
}