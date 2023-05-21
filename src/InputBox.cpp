#include "ElibHelp.h"


/*转16进制内存文本*/
/*#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

typedef unsigned char BYTE;

std::string makedatamem(BYTE* data, size_t size) {
	std::ostringstream oss;
	oss << "BYTE Data[] = {\n";

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

//216偏移为编辑框风格
BYTE InputBoxDialogTemplate[] = {
	0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x08, 0xC8, 0x80,
	0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7, 0x8B,
	0x93, 0x8F, 0x65, 0x51, 0x87, 0x65, 0x2C, 0x67, 0x1A, 0xFF, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x4D, 0x00, 0x53, 0x00, 0x20, 0x00, 0x53, 0x00, 0x68, 0x00, 0x65, 0x00, 0x6C, 0x00,
	0x6C, 0x00, 0x20, 0x00, 0x44, 0x00, 0x6C, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x50, 0x07, 0x00, 0x07, 0x00, 0xEE, 0x00, 0x23, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x00, 0x4B, 0x6D, 0xD5, 0x8B, 0x00, 0x4E, 0x0B, 0x4E,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x50,
	0x3F, 0x00, 0x42, 0x00, 0x37, 0x00, 0x13, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00,
	0x6E, 0x78, 0xA4, 0x8B, 0x93, 0x8F, 0x65, 0x51, 0x28, 0x00, 0x26, 0x00, 0x4F, 0x00, 0x29, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x50,
	0x86, 0x00, 0x42, 0x00, 0x37, 0x00, 0x13, 0x00, 0x02, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00,
	0xD6, 0x53, 0x88, 0x6D, 0x28, 0x00, 0x26, 0x00, 0x43, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x81, 0x50, 0x07, 0x00, 0x2D, 0x00,
	0xEE, 0x00, 0x0C, 0x00, 0x3B, 0x87, 0x00, 0x00, 0xFF, 0xFF, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00 };

//82偏移为编辑框风格
BYTE InputBoxDialogTemplateWithOutPrompt[] = {
	0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x08, 0xC8, 0x80,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7, 0x8B,
	0x93, 0x8F, 0x65, 0x51, 0x1A, 0xFF, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x00,
	0x53, 0x00, 0x20, 0x00, 0x53, 0x00, 0x68, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x20, 0x00,
	0x44, 0x00, 0x6C, 0x00, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x81, 0x50, 0x07, 0x00, 0x07, 0x00, 0xC8, 0x00, 0x0C, 0x00, 0x3B, 0x87, 0x00, 0x00,
	0xFF, 0xFF, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x01, 0x50, 0x52, 0x00, 0x1E, 0x00, 0x37, 0x00, 0x13, 0x00, 0x01, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0x80, 0x00, 0x6E, 0x78, 0xA4, 0x8B, 0x93, 0x8F, 0x65, 0x51, 0x28, 0x00, 0x26, 0x00,
	0x4F, 0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x50, 0x97, 0x00, 0x1E, 0x00, 0x37, 0x00, 0x13, 0x00, 0x02, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0x80, 0x00, 0xD6, 0x53, 0x88, 0x6D, 0x28, 0x00, 0x26, 0x00, 0x43, 0x00, 0x29, 0x00,
	0x00, 0x00, 0x00, 0x00 };

EXTERN_C void libstl_InputBox(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
#pragma region 动态赋值

	//	/*以下为控件*/
	///*提示框*/
	//	std::wstring prompt_title = L"提示信息";
	//	WORD prompt_check = 0xffff; //表示系统注册控件
	//	WORD prompt_class = 0x0082; //静态
	//	auto prompt_size = (prompt_title.size() + 1) * sizeof(WCHAR) + sizeof(WORD) * 2 + sizeof(DLGITEMTEMPLATE);
	//
	//	DLGITEMTEMPLATE* prompt_box = reinterpret_cast<DLGITEMTEMPLATE*>(new char[prompt_size] {});
	//	prompt_box->cx = 238;
	//	prompt_box->cy = 35;
	//	prompt_box->dwExtendedStyle = 0;
	//	prompt_box->id = 65535;
	//	prompt_box->style = 1342312448;
	//	prompt_box->x = 7;
	//	prompt_box->y = 7;
	//
	//	auto pbegin_prompt = reinterpret_cast<WORD*>(prompt_box + 1);
	//	*pbegin_prompt++ = prompt_check;
	//	*pbegin_prompt++ = prompt_class;
	//
	//	wcscpy_s(reinterpret_cast<WCHAR*>(pbegin_prompt), prompt_title.size() + 1, prompt_title.c_str());
	//	/*按钮*/
	//	std::wstring confirm_title = L"确认输入(&O)";
	//	WORD confirm_check = 0xffff; //表示系统注册控件
	//	WORD confirm_class = 0x0080; //静态
	//	auto confirm_size = (confirm_title.size() + 1) * sizeof(WCHAR) + sizeof(WORD) * 2 + sizeof(DLGITEMTEMPLATE);
	//
	//	DLGITEMTEMPLATE* confirm_box = reinterpret_cast<DLGITEMTEMPLATE*>(new char[confirm_size] {});
	//	confirm_box->cx = 238;
	//	confirm_box->cy = 35;
	//	confirm_box->dwExtendedStyle = 4;
	//	confirm_box->id = IDOK;
	//	confirm_box->style = 1342242816;
	//	confirm_box->x = 7;
	//	confirm_box->y = 7;
	//	auto confirm_prompt = reinterpret_cast<WORD*>(confirm_box + 1);
	//	*confirm_prompt++ = confirm_check;
	//	*confirm_prompt++ = confirm_class;
	//	wcscpy_s(reinterpret_cast<WCHAR*>(confirm_prompt), confirm_title.size() + 1, confirm_title.c_str());
	//
	//	// 对话框模板数据
	//	const WCHAR* dlgCaption = L"请输入:";
	//	const WCHAR* dlgFontName = L"MS Shell Dlg";
	//
	//	// 计算对话框模板的大小
	//	const int dlgCaptionLen = lstrlenW(dlgCaption) + 1;
	//	const int dlgTemplateSize =
	//		sizeof(DLGTEMPLATE) //对话框标头
	//		+ (sizeof(WORD) * 2) //菜单和默认窗口(都为0)
	//		+ (dlgCaptionLen * sizeof(WCHAR)) //标题
	//		+ sizeof(WORD) //字体大小
	//		+ (lstrlenW(dlgFontName) + 1) * sizeof(WCHAR) //字体名称
	//		+ prompt_size//提示框
	//		+ confirm_size
	//		;
	//
	//	// 创建对话框模板
	//	DLGTEMPLATE* pDlgTemplate = reinterpret_cast<DLGTEMPLATE*>(new char[dlgTemplateSize] {});
	//	auto pbegin = reinterpret_cast<char*>(pDlgTemplate);
	//
	//	DLGITEMTEMPLATE* A = (DLGITEMTEMPLATE*)BMInputBoxDialogTemplateData;
	//
	//
	//	// 填充对话框模板
	//	pDlgTemplate->style = 4294901761;
	//	pDlgTemplate->cdit = 1;
	//	pDlgTemplate->x = 0;
	//	pDlgTemplate->y = 0;
	//	pDlgTemplate->cx = 252;
	//	pDlgTemplate->cy = 92;
	//
	//	// 设置标题
	//	WCHAR* pCaption = reinterpret_cast<WCHAR*>(pbegin + sizeof(DLGTEMPLATE) + (sizeof(WORD) * 2));
	//	wcscpy_s(pCaption, dlgCaptionLen, dlgCaption);
	//
	//	// 设置字体信息
	//	WORD* pWord = reinterpret_cast<WORD*>(pbegin + sizeof(DLGTEMPLATE) + (sizeof(WORD) * 2) + dlgCaptionLen * sizeof(WCHAR));
	//	*pWord = 8;
	//	wcscpy_s(reinterpret_cast<LPWSTR>(pWord + 1), lstrlenW(dlgFontName) + 1, dlgFontName);
	//	auto controlbegin = reinterpret_cast<BYTE*>(reinterpret_cast<LPWSTR>(pWord + 1) + lstrlenW(dlgFontName) + 1);
	//	memcpy(controlbegin, prompt_box, prompt_size);
	//	controlbegin += prompt_size;
	//	memcpy(controlbegin, confirm_box, confirm_size);
#pragma endregion




	/*.版本 2
.支持库 libstl

.子程序 __启动窗口_创建完毕
.局部变量 A, 文本型


输入框W (“”, “”, “”,A , 1, )

*/

	auto prompt_str = elibstl::arg_to_wstring(pArgInf, 0);

	/*默认为当前活动窗口*/
	auto hParent = elibstl::args_to_data<INT>(pArgInf, 5).value_or(reinterpret_cast<INT>(GetActiveWindow()));

	auto title = elibstl::arg_to_wstring(pArgInf, 1);

	auto init_text = elibstl::arg_to_wstring(pArgInf, 2);

	auto nType = elibstl::args_to_data<INT>(pArgInf, 4).value_or(1);

	if (nType < 1 || nType>4)
		nType = 1;


	if (nType)
	{
		/*密码模式*/
		InputBoxDialogTemplate[216] = 0xA0;//ES_PASSWORD
	}

	HWND hDlg = CreateDialogIndirectParam(::GetModuleHandle(NULL), (LPCDLGTEMPLATE)InputBoxDialogTemplate, (HWND)hParent, 0, 0);
	SetWindowTextW(hDlg, title.c_str());
	/*获取提示框*/
	auto hPrompt = GetDlgItem(hDlg, -1);
	SetWindowTextW(hPrompt, prompt_str.c_str());
	/*获取编辑框*/
	auto hEdit = GetDlgItem(hDlg, 34619);
	SetWindowTextW(hPrompt, init_text.c_str());

	if (hDlg) {
		ShowWindow(hDlg, SW_SHOW);
		UpdateWindow(hDlg);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


}
static ARG_INFO s_Args_InputBox[] =
{
	{"提示信息", "支持任意类型，推荐utf16文本", 0, 0, _SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"窗口标题", "支持任意类型，推荐utf16文本", 0, 0, _SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"初始文本", "支持任意类型，推荐utf16文本", 0, 0, _SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"存放输入内容的变量", "参数值所指定的变量可以为数值或文本型，用于以不同的数据类型取回输入内容", 0, 0, _SDT_ALL, 0, AS_RECEIVE_VAR},
	{"输入方式", "参数值可以为以下常量值： 1 - 输入文本  2 - 输入整数  3 - 输入小数  4 - 输入密码。如果省略本参数，默认为“输入文本”。", 0, 0, SDT_INT, 1, AS_HAS_DEFAULT_VALUE},
	{"父窗口", "指定输入框的父窗口，可以是一个“窗口”类型数据或者一个整数型窗口句柄。如果被省略，默认为无。", 0, 0, _SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	//{"是否多行输入", "", 0, 0, SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE},
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