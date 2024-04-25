#pragma warning(disable:4996)
#include <fstream>  
#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "��д����ļ�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "��д�������",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}

};


EXTERN_C void Fn_writefileA(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::string_view& filename = elibstl::args_to_sdata(pArgInf, 0);
	//std::vector<unsigned char> data = ebin2v(pArgInf->m_pBin);
	if (filename.empty() || pArgInf[1].m_pBin == nullptr || *reinterpret_cast<DWORD*>(pArgInf[1].m_pBin + sizeof(DWORD)) == 0) {
		pRetData->m_bool = false;
		return;
	}

	FILE* out = fopen(std::string(filename).c_str(), "wb");
	if (out == NULL) {
		pRetData->m_bool = false;
		return;
	}
	const bool blpSucceeded = (fwrite(pArgInf[1].m_pBin + sizeof(DWORD) * 2, 1, *reinterpret_cast<DWORD*>(pArgInf[1].m_pBin + sizeof(DWORD)), out) == *reinterpret_cast<DWORD*>(pArgInf[1].m_pBin + sizeof(DWORD)));
	fclose(out);
	pRetData->m_bool = blpSucceeded;

}

FucInfo write_file_a = { {
		/*ccname*/  ("д���ļ�A"),
		/*egname*/  (""),
		/*explain*/ ("���������ڴ�����д���ļ�"),
		/*category*/4,
		/*state*/   CT_IS_HIDED,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_writefileA ,"Fn_writefileA" };











static ARG_INFO WArgs[] =
{
	{
		/*name*/    "��д����ļ�",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	},
	{
		/*name*/    "��д�������",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}

};


EXTERN_C void Fn_writefileW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::wstring_view& filename = elibstl::args_to_wsdata(pArgInf, 0);
	//std::vector<unsigned char> data = ebin2v(pArgInf->m_pBin);
	if (filename.empty() || pArgInf[1].m_pBin == nullptr || *reinterpret_cast<DWORD*>(pArgInf[1].m_pBin + sizeof(DWORD)) == 0) {
		pRetData->m_bool = false;
		return;
	}

	FILE* out = _wfopen(std::wstring(filename).c_str(), L"wb");
	if (out == NULL) {
		pRetData->m_bool = false;
		return;
	}
	const bool blpSucceeded = (fwrite(pArgInf[1].m_pBin + sizeof(DWORD) * 2, 1, *reinterpret_cast<DWORD*>(pArgInf[1].m_pBin + sizeof(DWORD)), out) == *reinterpret_cast<DWORD*>(pArgInf[1].m_pBin + sizeof(DWORD)));
	fclose(out);
	pRetData->m_bool = blpSucceeded;
}

FucInfo write_file_w = { {
		/*ccname*/  ("д���ļ�W"),
		/*egname*/  (""),
		/*explain*/ ("���������ڴ�����д���ļ�"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &WArgs[0],
	} ,Fn_writefileW ,"Fn_writefileW" };
