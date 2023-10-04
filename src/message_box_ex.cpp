#include"ElibHelp.h"
#include<commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include"ElibHelp.h"
#include<commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

static ARG_INFO Args[] =
{
	{
		/*name*/    "提示信息",
		/*explain*/ ("以较小字体显示在主指令下方"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_RECEIVE_ALL_TYPE_DATA,
	},
	{
		/*name*/    "提示标题",
		/*explain*/ ("用于显示的主指令"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_RECEIVE_ALL_TYPE_DATA | ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "按钮",
		/*explain*/ ("可通过不同位或组合不同按钮，默认为确认,1.确定,2.是,4.否,8.取消(必须为此对话框指定此按钮，才能响应 alt-F4 和转义) 的典型取消操作。),16.重试,32.关闭"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "窗口标题",
		/*explain*/ ("窗口显示的标题"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_RECEIVE_ALL_TYPE_DATA | ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ ("父窗口句柄"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "图标",
		/*explain*/ ("默认为无图标,欲显示图标,默认为:正确,0.无,1.任务对话框中会显示一个非索引符号图标.2.由圆圈中的小写字母 i 组成的图标显示在任务对话框中。3.任务对话框中会显示一个安全防护图标。4.任务对话框中会显示感叹号图标。默认为1。5.正确，6.错误"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

static LIB_DATA_TYPE_ELEMENT s_TaskDialog_Button[] =
{
	 {SDT_INT, 0, "确定", "TDCBF_OK_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_OK_BUTTON},
	 {SDT_INT, 0, "是", "TDCBF_YES_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_YES_BUTTON},
	 {SDT_INT, 0, "否", "TDCBF_NO_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_NO_BUTTON},
	 {SDT_INT, 0, "取消", "TDCBF_CANCEL_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_CANCEL_BUTTON},
	 {SDT_INT, 0, "重试", "TDCBF_RETRY_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_RETRY_BUTTON},
	 {SDT_INT, 0, "关闭", "TDCBF_OK_CLOSE", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_CLOSE_BUTTON}
};
namespace elibstl {
	LIB_DATA_TYPE_INFO TaskDialog_Button_Type =
	{
		"高级信息框按钮",
		"TDCBF",
		"高级信息框按钮值",
		NULL,
		NULL,
		_DT_OS(__OS_WIN) | LDT_ENUM,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		sizeof(s_TaskDialog_Button) / sizeof(s_TaskDialog_Button[0]),
		s_TaskDialog_Button
	};
}

EXTERN_C void Fn_TaskDialogW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const PWSTR icon[] = { nullptr,TD_ERROR_ICON,TD_INFORMATION_ICON,TD_SHIELD_ICON,TD_WARNING_ICON , MAKEINTRESOURCEW(-8),MAKEINTRESOURCEW(-7) };
	const auto
		lpContent = elibstl::arg_to_wstring(pArgInf, 0),
		lpTitle = elibstl::arg_to_wstring(pArgInf, 1),
		lpWindowTitle = elibstl::arg_to_wstring(pArgInf, 3);
	auto hwndParent = elibstl::args_to_data<INT>(pArgInf, 4),
		standardButtons = elibstl::args_to_data<INT>(pArgInf, 2),
		inicon = elibstl::args_to_data<INT>(pArgInf, 5);
	PWSTR boxicon = nullptr;
	if (inicon.has_value() && inicon.value() > 0 && inicon.value() <= 6)
	{
		boxicon = icon[inicon.value()];
	}
	//if (standardButtons.has_value())
	//{

	//	switch (standardButtons.value())
	//	{
	//	case 1:
	//		setButton = TDCBF_YES_BUTTON;
	//		break;
	//	case 2:
	//		setButton = TDCBF_NO_BUTTON;
	//		break;
	//	case 3:
	//		setButton = TDCBF_CANCEL_BUTTON;
	//		break;
	//	case 4:
	//		setButton = TDCBF_RETRY_BUTTON;
	//		break;
	//	case 5:
	//		setButton = TDCBF_OK_BUTTON;
	//		break;
	//	default:
	//		setButton = TDCBF_OK_BUTTON;
	//		break;
	//	}
	//}
	int buttonPressed;
	TaskDialog(reinterpret_cast<HWND>(hwndParent.has_value() ? hwndParent.value() : 0), NULL, !lpWindowTitle.empty() ? lpWindowTitle.c_str() : L"提示", lpTitle.c_str(), lpContent.c_str(), standardButtons.has_value() ? standardButtons.value() : TDCBF_OK_BUTTON, boxicon, &buttonPressed);
	switch (buttonPressed) {
	case IDOK:
		pRetData->m_int = TDCBF_OK_BUTTON;
		break;
	case IDCANCEL:
		pRetData->m_int = TDCBF_CANCEL_BUTTON;
		break;
	case IDRETRY:
		pRetData->m_int = TDCBF_RETRY_BUTTON;
		break;
	case IDYES:
		pRetData->m_int = TDCBF_YES_BUTTON;
		break;
	case IDNO:
		pRetData->m_int = TDCBF_NO_BUTTON;
		break;
	case IDCLOSE:
		pRetData->m_int = TDCBF_CLOSE_BUTTON;
		break;
	default:
		pRetData->m_int = -1;
		break;
	}
}

FucInfo task_dialog_w = { {
		/*ccname*/  ("高级信息框"),
		/*egname*/  ("TaskDialog"),
		/*explain*/ ("函数调用失败返回-1,如果成功，返回枚举常量:高级信息框按钮::"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/6,
		/*arg lp*/  &Args[0],
	} ,Fn_TaskDialogW ,"Fn_TaskDialogW" };


