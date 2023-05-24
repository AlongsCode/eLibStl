#include"ElibHelp.h"
using namespace std;



static ARG_INFO Args[] =
{
	{
		/*name*/    " ������������",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
wstring get_env(const wstring& env_name) {
	wchar_t* pBuf = new wchar_t[MAX_PATH];
	UINT nRet = GetEnvironmentVariableW(env_name.c_str(), pBuf, MAX_PATH);
	if (nRet > MAX_PATH)//����������
	{
		delete[]pBuf;//�ͷ�������
		pBuf = new wchar_t[nRet];
		GetEnvironmentVariableW(env_name.c_str(), pBuf, nRet);
	}
	wstring Ret(pBuf);
	delete[]pBuf;
	return Ret;
}
EXTERN_C void Fn_get_env_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto env_name = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_pBin = elibstl::clone_textw(get_env(wstring(env_name)));
}

FucInfo get_env_W = { {
		/*ccname*/  ("����������W"),
		/*egname*/  ("GetEnvW"),
		/*explain*/ ("�����ı�����������һ������ϵͳ�����������ɹ�ʱ������ȡ�õ�ֵ��ʧ���򷵻ؿ��ı���"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_get_env_W ,"Fn_get_env_W" };
