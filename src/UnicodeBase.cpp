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
		/*state*/   ArgMark::AS_NONE,
	},{
		/*name*/    "是否包含结束符",
		/*explain*/ ("默认包含结束符"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};



EXTERN_C void Fn_L(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, pArgInf->m_pText, -1, NULL, 0);
	if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
	{
		pRetData->m_pBin = nullptr;
		return;
	}
	if (widesize == 0)
	{
		pRetData->m_pBin = nullptr;
		return;
	}
	//返回没释放内存，啥比了
	wchar_t* resultstring = new wchar_t[widesize];
	int convresult = MultiByteToWideChar(CP_ACP, 0, pArgInf->m_pText, -1, resultstring, widesize);
	LPBYTE ret = nullptr;
	if (convresult == widesize)
	{
		ret = elibstl::clone_textw(resultstring, static_cast<bool>(elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE)));
	}
	delete[] resultstring;
	pRetData->m_pBin = ret;
}

FucInfo L = { {
		/*ccname*/  ("L"),
		/*egname*/  ("L"),
		/*explain*/ ("将文本转为unicode文本"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_L ,"Fn_L" };