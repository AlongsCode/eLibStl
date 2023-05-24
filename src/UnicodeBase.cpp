#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ ("��ת��Unicode���ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   NULL,
	},{
		/*name*/    "�Ƿ����������",
		/*explain*/ ("Ĭ�ϰ���������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
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
	//����û�ͷ��ڴ棬ɶ����
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
		/*explain*/ ("���ı�תΪunicode�ı�"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_L ,"Fn_L" };