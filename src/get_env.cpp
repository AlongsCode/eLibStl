#include"ElibHelp.h"
using namespace std;



static ARG_INFO Args[] =
{
	{
		/*name*/    " 环境变量名称",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
wstring get_env(const wstring& env_name) {
	wchar_t* pBuf = new wchar_t[MAX_PATH];
	UINT nRet = GetEnvironmentVariableW(env_name.c_str(), pBuf, MAX_PATH);
	if (nRet > MAX_PATH)//缓冲区不够
	{
		delete[]pBuf;//释放再申请
		pBuf = new wchar_t[nRet];
		GetEnvironmentVariableW(env_name.c_str(), pBuf, nRet);
	}
	wstring Ret(pBuf);
	delete[]pBuf;
	return Ret;
}
EXTERN_C void Fn_get_env_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto env_name = elibkrnln::args_to_wsdata(pArgInf, 0);
	pRetData->m_pBin = elibkrnln::clone_textw(get_env(wstring(env_name)));
}

FucInfo get_env_W = { {
		/*ccname*/  ("读环境变量W"),
		/*egname*/  ("GetEnvW"),
		/*explain*/ ("返回文本，它关连于一个操作系统环境变量。成功时返回所取得的值，失败则返回空文本。"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_get_env_W ,"Fn_get_env_W" };
