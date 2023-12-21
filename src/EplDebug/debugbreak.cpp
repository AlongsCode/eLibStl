//#include"ElibHelp.h"
//
//void  __stdcall fnDebugbreak() {
//	__asm int 3;
//}
//
//EXTERN_C void  fnDebugbreak(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
//{
//	OutputDebugStringA("* 程序执行被<<标准模板库>>的“断点”命令所中断 *");
//	fnDebugbreak();
//}
//
//
//FucInfo Fn_debugbreak = { {
//		/*ccname*/  ("断点"),
//		/*egname*/  ("debugbreak"),
//		/*explain*/ ("导致当前进程中发生断点异常。 这样，调用线程就可以向调试器发出信号来处理异常。若要在另一个进程中导致断点异常，请使用 DebugBreakProcess 函数。"),
//		/*category*/11,
//		/*state*/     CT_DISABLED_IN_RELEASE,
//		/*ret*/     _SDT_NULL,
//		/*reserved*/NULL,
//		/*level*/   LVL_HIGH,
//		/*bmp inx*/ 0,
//		/*bmp num*/ 0,
//		/*ArgCount*/0,
//		/*arg lp*/ 0
//	} ,ESTLFNAME(fnDebugbreak)};