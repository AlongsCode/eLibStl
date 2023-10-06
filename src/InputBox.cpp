#include "ElibHelp.h"


namespace elibstl {
	namespace inputbox {
		class MyDlg
		{
			struct DlgData
			{
				std::wstring m_text;
				bool m_bRet = false;

			};
			static BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				switch (uMsg)
				{
				case WM_INITDIALOG:
					::SetWindowLongPtrW(hDlg, GWL_USERDATA, lParam);
					SetFocus(GetDlgItem(hDlg, 58570));
					return FALSE;
				case WM_COMMAND:
				{
					INT nID = wParam & 0xffff;
					if (nID == IDCANCEL)
						DestroyWindow(hDlg);
					else if (nID == IDOK) {

						auto pDlgData = reinterpret_cast<DlgData*>(::GetWindowLongPtrW(hDlg, GWL_USERDATA));
						auto hEdit = GetDlgItem(hDlg, 58570);
						INT nLen = ::GetWindowTextLengthW(hEdit);
						if (nLen > 0)
						{
							WCHAR* pText = new WCHAR[nLen + 1]{ 0 };
							GetWindowTextW(hEdit, pText, nLen + 1);
							pDlgData->m_text = pText;
							delete[]pText;
						}
						pDlgData->m_bRet = true;
						DestroyWindow(hDlg);
					}
				}
				break;
				case WM_CLOSE:
					DestroyWindow(hDlg);
					break;
				case WM_DESTROY:
					PostMessage(hDlg, WM_QUIT, 0, 0);
					break;
				default:
					return FALSE;

				}
				return TRUE;
			}

#pragma pack(push, 1)  
#pragma warning(disable:4200)
			struct DLGTEMPLATEEX // Already defined in Win SDK
			{
				WORD        dlgVer;    // must be 0x0001
				WORD        signature; // must be 0xFFFF
				DWORD       helpID;
				DWORD       exStyle;
				DWORD       style;
				WORD        cDlgItems;
				short       x;
				short       y;
				short       cx;
				short       cy;
				short menu;
				short windowClass;
				WCHAR     title[];

			};
			//#if (style & (DS_SETFONT|DS_SHELLFONT))
			struct FONTDLG
			{
				WORD      pointsize = 9;
				WORD      weight = 0;
				BYTE      italic = 0;
				BYTE      charset = 0;
				WCHAR     typeface[19] = L"Microsoft YaHei UI";
			};
			struct DLGITEMTEMPLATEEX
			{
				DWORD       helpID;
				DWORD       exStyle;
				DWORD       style;
				short       x;
				short       y;
				short       cx;
				short       cy;
				DWORD       id;
				WORD must;
				WORD windowClass;
				WCHAR title[];
				//其后跟随
				//WORD      extraCount;

			};
#pragma pack(pop) 
		public:
			/*添加控件*/
			inline void Add(const std::wstring& title,
				DWORD style,
				short       x,
				short       y,
				short       cx,
				short       cy,
				DWORD       id,
				WORD windowClass
			) {
				constexpr size_t  gitem_size = sizeof(DLGITEMTEMPLATEEX) + sizeof(WORD);
				auto lenth = (title.size() + 1) * sizeof(wchar_t);
				size_t cbTotal = lenth + gitem_size;
				if (cbTotal % 4)
					cbTotal += 2;
				auto dlg_template = reinterpret_cast<DLGITEMTEMPLATEEX*>(new char[cbTotal]{ 0 });
				dlg_template->cx = cx;
				dlg_template->cy = cy;
				dlg_template->x = x;
				dlg_template->y = y;
				dlg_template->helpID = 0;
				dlg_template->id = id;;
				dlg_template->style = style;
				dlg_template->must = 0xffff;//表示系统控件
				dlg_template->windowClass = windowClass;

				if (!title.empty())
				{
					wcscpy_s(dlg_template->title, title.size() + 1, title.c_str());
				}

				m_pData.insert(m_pData.end(), 
					reinterpret_cast<unsigned char*>(dlg_template), 
					reinterpret_cast<unsigned char*>(dlg_template) + cbTotal);
				delete[]reinterpret_cast<char*>(dlg_template);
				m_Count++;
			}
			inline HWND Create(short x, short y, short cx, short cy, const std::wstring title, HWND hParent) {
				DLGTEMPLATEEX Head;
				Head.dlgVer = 0x0001;
				Head.signature = 0xFFFF;
				Head.helpID = 0;
				Head.cDlgItems = m_Count;
				Head.cx = cx;
				Head.cy = cy;
				Head.x = x;
				Head.y = y;
				Head.menu = 0;
				Head.style = 2160593096;
				Head.exStyle = 0;
				Head.windowClass = 0;
				FONTDLG Font{  };
				m_pData.insert(m_pData.begin(), 
					reinterpret_cast<unsigned char*>(&Font), 
					reinterpret_cast<unsigned char*>(&Font) + sizeof(Font));
				if (title.size() % 2)
					m_pData.insert(m_pData.begin() + sizeof(Font), { 0,0 });
				if (!title.empty())
				{
					m_pData.insert(m_pData.begin(), 
						const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(title.c_str())), 
						const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(title.c_str())) + (title.size() + 1) * sizeof(wchar_t));
				}
				else
				{
					const auto emptystr = L"";
					m_pData.insert(m_pData.begin(), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(emptystr)), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(emptystr) + sizeof(wchar_t)));

				}
				m_pData.insert(m_pData.begin(), 
					reinterpret_cast<unsigned char*>(&Head), 
					reinterpret_cast<unsigned char*>(&Head) + sizeof(Head));

				m_hDlg = CreateDialogIndirectParamW(g_elibstl_hModule, (DLGTEMPLATE*)m_pData.data(), hParent, DlgProc, reinterpret_cast<LPARAM>(&m_DlgData));

				return m_hDlg;
			}
			bool MessageLoop(bool nType) const {
				if (m_hDlg) {
					ShowWindow(m_hDlg, SW_SHOW);
					UpdateWindow(m_hDlg);
					MSG msg;
					while (GetMessage(&msg, NULL, 0, 0)) {
						if (msg.hwnd == GetDlgItem(m_hDlg, 58570) && msg.message == WM_CHAR) {
							if (msg.wParam == 13)
								::SendMessage(m_hDlg, WM_COMMAND, IDOK, 0);
							else if (nType) {
								if (!(msg.wParam == '-' || (msg.wParam >= '0' && msg.wParam <= '9') || msg.wParam == '.'))
									continue;
							}

						}
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				return m_DlgData.m_bRet;
			}

			const std::wstring& GetText() const {
				return m_DlgData.m_text;
			}
		private:
			DlgData  m_DlgData{};
			HWND m_hDlg = NULL;
			WORD m_Count = 0;
			std::vector<unsigned char> m_pData;
		};
	}
}





/*转16进制内存文本*/
/*#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

typedef unsigned char BYTE;

std::string makedatamem(BYTE* data, size_t size) {
	std::ostringstream oss;
	oss << "{\n";

	for (size_t i = 0; i < size; ++i) {
		if (i % 16 == 0) {
			oss << "    ";
		}

		oss << "0x" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(data[i]);

		if (i != size - 1) {
			oss << ",";
		}

		if ((i + 1) % 16 == 0 && i != size - 1) {
			oss << "\n";
		} else {
			oss << " ";
		}
	}

	oss << "};";

	return oss.str();
}*/



EXTERN_C void libstl_InputBox(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{


	auto prompt_str =elibstl::arg_to_wstring(pArgInf, 0);
	/*默认为当前活动窗口*/
	auto hParent = elibstl::args_to_data<INT>(pArgInf, 5).value_or(reinterpret_cast<INT>(GetActiveWindow()));
	auto title = elibstl::arg_to_wstring(pArgInf, 1);
	auto init_text = elibstl::arg_to_wstring(pArgInf, 2);
	auto nType = elibstl::args_to_data<INT>(pArgInf, 4).value_or(1);
	short MultiLineAdd = (elibstl::args_to_data<BOOL>(pArgInf, 6).value_or(FALSE)) ? 12 : 0;
	if (nType < 1 || nType>5)
		nType = 1;

	DWORD dwStyleEdit = 1350631552;
	if (MultiLineAdd == 12)
	{
		dwStyleEdit &= ~ES_AUTOHSCROLL;
		dwStyleEdit |= (ES_MULTILINE | ES_AUTOVSCROLL);
	}
	if (nType == 4)
	{
		/*密码模式*/
		dwStyleEdit |= ES_PASSWORD;
	}
	else if (nType == 2)
	{
		/*数字模式*/
		dwStyleEdit |= ES_NUMBER;
	}

	/*动态对话框模板,网上一点B资料没有*/
	elibstl::inputbox::MyDlg Dlg;
	if (!prompt_str.empty())
	{
		/*按钮*/
		Dlg.Add(L"确认输入(&O)", 1342242816, 63, 66 + MultiLineAdd, 55, 19, IDOK, 0x0080);
		Dlg.Add(L"取消(&C)", 1342242816, 134, 66 + MultiLineAdd, 55, 19, IDCANCEL, 0x0080);
		/*输入框 */
		
		debug_put(init_text, prompt_str);
		Dlg.Add(init_text, dwStyleEdit, 7, 45, 238, 12 + MultiLineAdd, 58570, 0x0081);
		/*提示框*/
		Dlg.Add(prompt_str, 1342312448, 7, 7, 238, 35, 0, 0x0082);
		/*创建*/
		Dlg.Create(0, 0, 252, 92 + MultiLineAdd, title, reinterpret_cast<HWND>(hParent));
	}
	else
	{	/*无提示文本,窗口需要调整一下*/
			/*按钮*/
		Dlg.Add(L"确认输入(&O)", 1342242816, 82, 30 + MultiLineAdd, 55, 19, IDOK, 0x0080);
		Dlg.Add(L"取消(&C)", 1342242816, 151, 30 + MultiLineAdd, 55, 19, IDCANCEL, 0x0080);
		/////*输入框 */
		Dlg.Add(init_text, dwStyleEdit, 7, 7, 200, 12 + MultiLineAdd, 58570, 0x0081);
		/*创建*/
		Dlg.Create(0, 0, 214, 56 + MultiLineAdd, title, reinterpret_cast<HWND>(hParent));

	}
	pRetData->m_bool = Dlg.MessageLoop(nType == 3);
	elibstl::wstring_to_arg(&pArgInf[3], Dlg.GetText());
}
static ARG_INFO s_Args_InputBox[] =
{
	{"提示信息", "支持任意类型，推荐utf16文本", 0, 0, _SDT_ALL, 0, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY},
	{"窗口标题", "支持任意类型，推荐utf16文本", 0, 0, _SDT_ALL, 0, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY},
	{"初始文本", "支持任意类型，推荐utf16文本", 0, 0, _SDT_ALL, 0, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY},
	{"存放输入内容的变量", "参数值所指定的变量可以为数值或文本型，用于以不同的数据类型取回输入内容", 0, 0, _SDT_ALL, 0, ArgMark::AS_RECEIVE_VAR},
	{"输入方式", "参数值可以为以下常量值： 1 - 输入文本  2 - 输入整数  3 - 输入小数  4 - 输入密码  。如果省略本参数，默认为“输入文本”。", 0, 0, SDT_INT, 1, ArgMark::AS_HAS_DEFAULT_VALUE},
	{"父窗口", "指定输入框的父窗口，可以是一个“窗口”类型数据或者一个整数型窗口句柄。如果被省略，默认为无。", 0, 0, _SDT_ALL, 0, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY},
	{"是否多行输入", "", 0, 0, SDT_BOOL, FALSE, ArgMark::AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_InputBox = { {
		/*ccname*/  "输入框W",
		/*egname*/  "InputBoxW",
		/*explain*/ "在一对话框中显示提示，等待用户输入正文并按下按钮。如果用户在确认输入后（按下“确认输入”按钮或回车键）退出，返回真，否则返回假。",
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_InputBox),
		/*arg lp*/  s_Args_InputBox },ESTLFNAME(libstl_InputBox) };