#include"ElibHelp.h"

using namespace std;


inline double GetCpuUsage()
{
	static unsigned long long last_idle_time = 0;
	static unsigned long long last_kernel_time = 0;
	static unsigned long long last_user_time = 0;

	unsigned long long sys_idle_time, sys_kernel_time, sys_user_time;
	if (!GetSystemTimes((FILETIME*)&sys_idle_time, (FILETIME*)&sys_kernel_time, (FILETIME*)&sys_user_time))
	{
		return -1;
	}

	unsigned long long idle_time = sys_idle_time - last_idle_time;
	unsigned long long kernel_time = sys_kernel_time - last_kernel_time;
	unsigned long long user_time = sys_user_time - last_user_time;
	unsigned long long total_time = kernel_time + user_time;

	last_idle_time = sys_idle_time;
	last_kernel_time = sys_kernel_time;
	last_user_time = sys_user_time;

	return 100.0 * (total_time - idle_time) / total_time;
}

EXTERN_C void Fn_get_cpu_usges(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	pRetData->m_double = GetCpuUsage();
}


FucInfo get_cpu_usges = { {
		/*ccname*/  ("取CPU占用率Ex"),
		/*egname*/  ("get_cpu_usges"),
		/*explain*/ ("获取CPU当前使用率,精确度更高"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_DOUBLE ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_cpu_usges ,"Fn_get_cpu_usges" };