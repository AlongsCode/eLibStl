#include"ElibHelp.h"
#include<iostream>
#pragma warning(disable:4018)


EXTERN_C void Fn_clearConsole(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::system("cls");
}

FucInfo clearConsole = { {
		/*ccname*/  ("Çå¿Õ¿ØÖÆÌ¨"),
		/*egname*/  ("clearConsole"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/  NULL,
		/*ret*/    DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_clearConsole ,"Fn_clearConsole" };
