#include<windows.h>
#include<CommCtrl.h>
#include<Richedit.h>
#include <OleIdl.h>
#include <RichOle.h>
#include<string>
#include<vector>
#include <sstream>
#pragma comment (lib,"Crypt32.lib")
#include"elib\fnshare.h"


namespace elibstl {

	/*对应的16进制转为unicode*/
	inline std::wstring UmakeW(const std::wstring& str)
	{
		std::wstring wstr;

		std::wstring hexValue;
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] == L'\\' && str[i + 1] == L'u')
			{
				hexValue = str.substr(i + 2, 4);
				unsigned int unicodeValue = std::stoi(hexValue, nullptr, 16);
				wstr += static_cast<wchar_t>(unicodeValue);
				i += 5; // Skip the next 5 characters ('\uXXXX')
			}
			else
			{
				wstr += static_cast<wchar_t>(str[i]);
			}
		}

		return wstr;
	}

	inline std::vector<unsigned char> Base64ToString(const std::wstring& base64String)
	{
		DWORD binaryLength = 0;

		// 获取解码后的二进制数据长度
		if (::CryptStringToBinaryW(base64String.c_str(), base64String.length(),
			CRYPT_STRING_BASE64, nullptr, &binaryLength, nullptr, nullptr)) {
			std::vector<unsigned char> binaryData(binaryLength);

			// 将 Base64 编码的字符串解码为二进制数据
			if (::CryptStringToBinaryW(base64String.c_str(), base64String.length(),
				CRYPT_STRING_BASE64, binaryData.data(), &binaryLength, nullptr, nullptr)) {
				return binaryData;
			}
		}

		// 失败时返回空向量
		return std::vector<unsigned char>();
	}

	/*易语言调试框*/
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
				| ES_NOHIDESEL | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | EM_PASTESPECIAL;
			//dwStyle |= dwDefStyle;
			// 创建 RichEdit 控件
			m_hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, WindowName, dwDefStyle,
				x, y, width, height, parentWnd, NULL, GetModuleHandle(NULL), NULL);
			SendMessageW(m_hWnd, EM_SETOLECALLBACK, 0, (LPARAM)NULL);
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
		void AppendImage()
		{
			if (!m_isInit || m_hWnd == NULL)
				return;
			// 在富文本框中插入剪贴板中的图像
			SendMessageW(m_hWnd, WM_PASTE, 0, 0);

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
			SetWindowTextA(m_hDebugBox, "");
			ShowWindow(m_hDebugBox, SW_SHOW);
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
				if (text && wcslen(text))//继续判断
				{

					auto  is_img = [](const wchar_t* str1) {

						const wchar_t* img = L"* [elbbstl::image]";
						while (*str1 && *img && (*str1 == *img)) {


							++str1;
							++img;
						}

						return (*img == L'\0'); // 判断是否 str2 已经遍历结束
					};
					if (is_img(text))
					{
						auto img = Base64ToString(std::wstring(text).substr(sizeof("* [elbbstl::image]") - sizeof('\0')));
						now->m_hRicEdit.AppendText(L"* [图片:]");
						now->m_hRicEdit.AppendImage();

						now->m_hRicEdit.AppendText(L"\r\n");
					}
					else
						now->m_hRicEdit.AppendText(UmakeW(text).c_str());

				}


			}break;
			default:

				break;
			}
			return CallWindowProcW(now->m_WndOldProcDebugBox, hWnd, Msg, wParam, lParam);

		}
	};


	EDebugEdit* GetRichEdit() {
		/*用于延迟初始化,卸载时自动析构*/
		static EDebugEdit instance;
		return &instance;

	}

	void e_debugbox_init() {
		GetRichEdit();
	}
}