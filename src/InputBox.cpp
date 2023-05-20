#include "ElibHelp.h"

EXTERN_C void libstl_InputBox(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

}
static ARG_INFO s_Args_InputBox[] =
{
	{"提示信息", "", 0, 0, SDT_BIN, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"窗口标题", "", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"初始文本", "", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"存放输入内容的变量", "参数值所指定的变量可以为数值或文本型，用于以不同的数据类型取回输入内容", 0, 0, _SDT_ALL, 0, AS_RECEIVE_VAR},
	{"输入方式", "参数值可以为以下常量值： 1 - 输入文本  2 - 输入整数  3 - 输入小数  4 - 输入密码。如果省略本参数，默认为“输入文本”。", 0, 0, SDT_INT, 1, AS_HAS_DEFAULT_VALUE},
	{"父窗口", "指定输入框的父窗口，可以是一个“窗口”类型数据或者一个整数型窗口句柄。如果被省略，默认为无。", 0, 0, _SDT_ALL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	{"是否多行输入", "", 0, 0, SDT_BOOL, FALSE, AS_HAS_DEFAULT_VALUE},
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