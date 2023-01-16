#include"ElibHelp.h"
#include<wininet.h>
#pragma comment(lib,"Wininet.lib")
EXTERN_C void Fn_is_connect_to_internet(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	DWORD flag;
	pRetData->m_bool = InternetGetConnectedState(&flag, 0);;
}

FucInfo is_connect_to_internet = { {
		/*ccname*/  ("是否已联网"),
		/*egname*/  ("is_connect_to_internet"),
		/*explain*/ ("判断计算机是否已经连接网络"),
		/*category*/7,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_is_connect_to_internet ,"Fn_is_connect_to_internet" };
