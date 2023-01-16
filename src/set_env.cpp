#include"ElibHelp.h"
using namespace std;



static ARG_INFO Args[] =
{
	{
		/*name*/    " 环境变量名称",
		/*explain*/ ("欲组合的文件名"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "欲写入内容",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_set_env_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto env_name = elibstl::args_to_wsdata(pArgInf, 0);
	auto env_val = elibstl::args_to_wsdata(pArgInf, 1);
	pRetData->m_bool = SetEnvironmentVariableW(wstring(env_name).c_str(), wstring(env_val).c_str()) == TRUE;
}


FucInfo set_env_W = { {
		/*ccname*/  ("写环境变量W"),
		/*egname*/  ("SetEnvW"),
		/*explain*/ ("修改或建立指定的操作系统环境变量。成功返回真，失败返回假。"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_set_env_W ,"Fn_set_env_W" };
