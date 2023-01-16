#include"ElibHelp.h"
#pragma warning(disable:6031)
#pragma warning(disable:4996)


EXTERN_C void Fn_free_console(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	FreeConsole();
}

FucInfo free_console = { {
		/*ccname*/  ("分离控制台"),
		/*egname*/  ("free_console"),
		/*explain*/ ("将控制台与进程分离，其后此进程中任何操作操作都无法控制控制台"),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_free_console ,"Fn_free_console" };
