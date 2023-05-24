#include"ElibHelp.h"
using namespace std;



static ARG_INFO Args[] =
{
	{
		/*name*/    " ������������",
		/*explain*/ ("����ϵ��ļ���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "��д������",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
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
		/*ccname*/  ("д��������W"),
		/*egname*/  ("SetEnvW"),
		/*explain*/ ("�޸Ļ���ָ���Ĳ���ϵͳ�����������ɹ������棬ʧ�ܷ��ؼ١�"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_set_env_W ,"Fn_set_env_W" };
