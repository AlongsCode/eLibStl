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
		/*ccname*/  ("�򿪿���̨"),
		/*egname*/  ("openconsole"),
		/*explain*/ ("�������ڳ����н�����תΪ����̨������������ͬʱ�������̨Ҳ���ǿ���̨�ǳ�Ϊ���������̣߳��رտ���̨Ҳ���ǹرճ���,�������Ҫ����̨�������������̣���ʹ��\"�������̨()\""),
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
