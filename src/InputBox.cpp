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
					break;
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
				WORD      pointsize = 8;
				WORD      weight = 0;
				BYTE      italic = 0;
				BYTE      charset = 0;
				WCHAR     typeface[13] = L"MS Shell Dlg";
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
				//������
				//WORD      extraCount;

			};
#pragma pack(pop) 
		public:
			/*��ӿؼ�*/
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
				auto lenth = (title.size() + 1) * sizeof(wchar_t);;
				auto dlg_template = reinterpret_cast<DLGITEMTEMPLATEEX*>(new char[gitem_size + lenth]{ 0 });
				dlg_template->cx = cx;
				dlg_template->cy = cy;
				dlg_template->x = x;
				dlg_template->y = y;
				dlg_template->helpID = 0;
				dlg_template->id = id;;
				dlg_template->style = style;
				dlg_template->must = 0xffff;//��ʾϵͳ�ؼ�
				dlg_template->windowClass = windowClass;

				if (!title.empty())
				{
					wcscpy_s(dlg_template->title, title.size() + 1, title.c_str());
				}

				m_pData.insert(m_pData.end(), reinterpret_cast<unsigned char*>(dlg_template), reinterpret_cast<unsigned char*>(dlg_template) + gitem_size + lenth);
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
				m_pData.insert(m_pData.begin(), reinterpret_cast<unsigned char*>(&Font), reinterpret_cast<unsigned char*>(&Font) + sizeof(Font));
				if (!title.empty())
				{
					m_pData.insert(m_pData.begin(), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(title.c_str())), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(title.c_str())) + (title.size() + 1) * sizeof(wchar_t));
				}
				else
				{
					const auto emptystr = L"";
					m_pData.insert(m_pData.begin(), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(emptystr)), const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(emptystr) + sizeof(wchar_t)));

				}
				m_pData.insert(m_pData.begin(), reinterpret_cast<unsigned char*>(&Head), reinterpret_cast<unsigned char*>(&Head) + sizeof(Head));

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





/*ת16�����ڴ��ı�*/
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


	auto prompt_str = elibstl::arg_to_wstring(pArgInf, 0);
	/*Ĭ��Ϊ��ǰ�����*/
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
		/*����ģʽ*/
		dwStyleEdit |= ES_PASSWORD;
	}
	else if (nType == 2)
	{
		/*����ģʽ*/
		dwStyleEdit |= ES_NUMBER;
	}

	/*��̬�Ի���ģ��,����һ��B����û��*/
	elibstl::inputbox::MyDlg Dlg;
	if (!prompt_str.empty())
	{
		/*��ť*/
		Dlg.Add(L"ȷ������(&O)", 1342242816, 63, 66 + MultiLineAdd, 55, 19, IDOK, 0x0080);
		Dlg.Add(L"ȡ��(&C)", 1342242816, 134, 66 + MultiLineAdd, 55, 19, IDCANCEL, 0x0080);
		/*����� */
		Dlg.Add(init_text, dwStyleEdit, 7, 45, 238, 12 + MultiLineAdd, 58570, 0x0081);
		/*��ʾ��*/
		Dlg.Add(prompt_str, 1342312448, 7, 7, 238, 35, 0, 0x0082);
		/*����*/
		Dlg.Create(0, 0, 252, 92 + MultiLineAdd, title, reinterpret_cast<HWND>(hParent));
	}
	else
	{	/*����ʾ�ı�,������Ҫ����һ��*/
			/*��ť*/
		Dlg.Add(L"ȷ������(&O)", 1342242816, 82, 30 + MultiLineAdd, 55, 19, IDOK, 0x0080);
		Dlg.Add(L"ȡ��(&C)", 1342242816, 151, 30 + MultiLineAdd, 55, 19, IDCANCEL, 0x0080);
		/////*����� */
		Dlg.Add(init_text, dwStyleEdit, 7, 7, 200, 12 + MultiLineAdd, 58570, 0x0081);
		///*����*/
		Dlg.Create(0, 0, 214, 56 + MultiLineAdd, title, reinterpret_cast<HWND>(hParent));

	}
	pRetData->m_bool = Dlg.MessageLoop(nType == 3);
	elibstl::wstring_to_arg(&pArgInf[3], Dlg.GetText());
}
static ARG_INFO s_Args_InputBox[] =
{
	{"��ʾ��Ϣ", "֧���������ͣ��Ƽ�utf16�ı�", 0, 0, DATA_TYPE::_SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"���ڱ���", "֧���������ͣ��Ƽ�utf16�ı�", 0, 0, DATA_TYPE::_SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"��ʼ�ı�", "֧���������ͣ��Ƽ�utf16�ı�", 0, 0, DATA_TYPE::_SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"����������ݵı���", "����ֵ��ָ���ı�������Ϊ��ֵ���ı��ͣ������Բ�ͬ����������ȡ����������", 0, 0, DATA_TYPE::_SDT_ALL, 0, AS_RECEIVE_VAR},
	{"���뷽ʽ", "����ֵ����Ϊ���³���ֵ�� 1 - �����ı�  2 - ��������  3 - ����С��  4 - ��������  �����ʡ�Ա�������Ĭ��Ϊ�������ı�����", 0, 0, DATA_TYPE::SDT_INT, 1, AS_HAS_DEFAULT_VALUE},
	{"������", "ָ�������ĸ����ڣ�������һ�������ڡ��������ݻ���һ�������ʹ��ھ���������ʡ�ԣ�Ĭ��Ϊ�ޡ�", 0, 0, DATA_TYPE::_SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"�Ƿ��������", "", 0, 0, DATA_TYPE::SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE},
};
FucInfo Fn_InputBox = { {
		/*ccname*/  "�����W",
		/*egname*/  "InputBoxW",
		/*explain*/ "��һ�Ի�������ʾ��ʾ���ȴ��û��������Ĳ����°�ť������û���ȷ������󣨰��¡�ȷ�����롱��ť��س������˳��������棬���򷵻ؼ١�",
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/ARRAYSIZE(s_Args_InputBox),
		/*arg lp*/  s_Args_InputBox },ESTLFNAME(libstl_InputBox) };