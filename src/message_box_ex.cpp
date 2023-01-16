#include"ElibHelp.h"
#include<commctrl.h>
#pragma comment(lib, "comctl32.lib")


static ARG_INFO Args[] =
{
	{
		/*name*/    "提示信息",
		/*explain*/ ("以较小字体显示在主指令下方"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	},
	{
		/*name*/    "提示标题",
		/*explain*/ ("用于显示的主指令"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "按钮",
		/*explain*/ ("可通过不同位或组合不同按钮，默认为确认,1.确定,2.是,4.否,8.取消(必须为此对话框指定此按钮，才能响应 alt-F4 和转义) 的典型取消操作。),16.重试,32.关闭"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "窗口标题",
		/*explain*/ ("窗口显示的标题"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ ("父窗口句柄"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "图标",
		/*explain*/ ("欲显示图标,默认为:正确,0.无,1.任务对话框中会显示一个非索引符号图标.2.由圆圈中的小写字母 i 组成的图标显示在任务对话框中。3.任务对话框中会显示一个安全防护图标。4.任务对话框中会显示感叹号图标。默认为1。5.正确，6.错误"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};


EXTERN_C void Fn_TaskDialogW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const PWSTR icon[] = { nullptr,TD_ERROR_ICON,TD_INFORMATION_ICON,TD_SHIELD_ICON,TD_WARNING_ICON , MAKEINTRESOURCEW(-8),MAKEINTRESOURCEW(-7) };
	const std::wstring_view&
		lpContent = elibkrnln::args_to_wsdata(pArgInf, 0),
		lpTitle = elibkrnln::args_to_wsdata(pArgInf, 1),
		lpWindowTitle = elibkrnln::args_to_wsdata(pArgInf, 3);
	auto hwndParent = elibkrnln::args_to_data<INT>(pArgInf, 4),
		standardButtons = elibkrnln::args_to_data<INT>(pArgInf, 2),
		inicon = elibkrnln::args_to_data<INT>(pArgInf, 5);
	PWSTR boxicon = MAKEINTRESOURCEW(-8);
	if (inicon.has_value() && inicon.value() > 0 && inicon.value() <= 6)
	{
		boxicon = icon[inicon.value()];
	}

	int buttonPressed;
	TaskDialog(reinterpret_cast<HWND>(hwndParent.has_value() ? hwndParent.value() : 0), NULL, !lpWindowTitle.empty() ? std::wstring(lpWindowTitle).c_str() : L"提示", std::wstring(lpTitle).c_str(), std::wstring(lpContent).c_str(), standardButtons.has_value() ? standardButtons.value() : TDCBF_OK_BUTTON, boxicon, &buttonPressed);
	pRetData->m_int = buttonPressed;
}

FucInfo task_dialog_w = { {
		/*ccname*/  ("高级信息框W"),
		/*egname*/  ("TaskDialog"),
		/*explain*/ ("0.函数调用失败,1.已选择“确定”按钮。2.已选择“取消”按钮，按 Alt-F4，已按下转义，或者用户单击关闭窗口按钮。4.已选择“重试”按钮。6.已选择“是”按钮。7.未选择任何按钮。"),
		/*category*/3,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/6,
		/*arg lp*/  &Args[0],
	} ,Fn_TaskDialogW ,"Fn_TaskDialogW" };
