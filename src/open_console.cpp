#include"ElibHelp.h"
#pragma warning(disable:6031)
#pragma warning(disable:4996)


EXTERN_C void Fn_openconsole(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		pRetData->m_bool = true;
		return;
	}
	else {
		pRetData->m_bool = false;
		return;
	}
}

FucInfo open_console = { {
		/*ccname*/  ("打开控制台"),
		/*egname*/  ("openconsole"),
		/*explain*/ ("用作窗口程序中将程序转为控制台程序，生命周期同时跟随控制台也就是控制台是成为你程序的主线程，关闭控制台也就是关闭程序,如果你想要控制台程序脱离程序进程，请使用\"分离控制台()\""),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_openconsole ,"Fn_openconsole" };
