#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲转换Unicode的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};



EXTERN_C void Fn_L(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, pArgInf->m_pText, -1, NULL, 0);
	if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		pRetData->m_pBin = 0;
		return;
	}
	if (widesize == 0)
	{
		pRetData->m_pBin = 0;
		return;
	}
	//返回没释放内存，啥比了
	wchar_t* resultstring = new wchar_t[widesize];
	int convresult = MultiByteToWideChar(CP_ACP, 0, pArgInf->m_pText, -1, resultstring, widesize);
	if (convresult != widesize)
	{
		pRetData->m_pBin = 0;
		delete[] resultstring;
		return;
	}
	LPBYTE ret = elibstl::clone_textw(resultstring);
	delete[] resultstring;
	pRetData->m_pBin = ret;
}

FucInfo L = { {
		/*ccname*/  ("L"),
		/*egname*/  (""),
		/*explain*/ ("uncidoe文本"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_L ,"Fn_L" };
