#include"ElibHelp.h"
#pragma warning(disable:6031)

static ARG_INFO Args[] =
{
	{
		/*name*/    "标题",
		/*explain*/ ("欲设置的控制台标题"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_SetConsoleTitleW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::wstring_view& text = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_bool = SetConsoleTitleW(std::wstring(text).c_str());
}

FucInfo set_console_title = { {
		/*ccname*/  ("置控制台标题W"),
		/*egname*/  ("SetConsoleTitleW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_SetConsoleTitleW ,"Fn_SetConsoleTitleW" };
