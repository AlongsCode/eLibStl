#include"ElibHelp.h"
#pragma warning(disable:6031)
#pragma warning(disable:4996)


EXTERN_C void Fn_free_console(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = FreeConsole();
}

FucInfo free_console = { {
		/*ccname*/  ("�������̨"),
		/*egname*/  ("free_console"),
		/*explain*/ ("������̨����̷��룬���˽������κβ����������޷����ƿ���̨"),
		/*category*/5,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_free_console ,"Fn_free_console" };
