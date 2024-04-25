//#include <fstream>  
#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲读入的文件",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_readfileA(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	//const std::string_view& filename = elibstl::args_to_sdata(pArgInf, 0);
	//std::ifstream file(std::string(filename), std::ios::binary);
	//LPBYTE data;
	//// 如果文件打开成功
	//if (file) {
	//	// 获取文件长度
	//	file.seekg(0, std::ios::end);
	//	size_t length = static_cast<size_t>(file.tellg());
	//	// 重置文件指针到文件开头
	//	file.seekg(0, std::ios::beg);
	//	data = new BYTE[length];
	//	file.read(reinterpret_cast<char*>(data), length);
	//	if (data && length > 0)
	//	{
	//		pRetData->m_pBin = elibstl::clone_bin(data, length);
	//		delete[]data;
	//	}

	//}
	//// 关闭文件
	//file.close();

}

FucInfo read_file_a = { {
		/*ccname*/  ("读入文件A"),
		/*egname*/  (""),
		/*explain*/ ("将文件以二进制方式读入内存"),
		/*category*/4,
		/*state*/   CT_IS_HIDED,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_readfileA ,"Fn_readfileA" };











static ARG_INFO WArgs[] =
{
	{
		/*name*/    "欲读入的文件",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_readfileW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::wstring_view& filename = elibstl::args_to_wsdata(pArgInf, 0);
	HANDLE hFile = CreateFile(filename.data(),
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	LPBYTE pData = NULL;

	if (hFile != INVALID_HANDLE_VALUE)
	{

		DWORD dwNumOfByteRead;
		INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
		pData = (LPBYTE)elibstl::ealloc(nLen + 2 * sizeof(INT));
		*(LPINT)pData = 1;
		*(LPINT)(pData + sizeof(INT)) = nLen;
		INT nRet = ReadFile(hFile, pData + 2 * sizeof(INT), nLen, &dwNumOfByteRead, 0);
		CloseHandle(hFile);
	}
	pRetData->m_pBin = pData;
}

FucInfo read_file_w = { {
		/*ccname*/  ("读入文件W"),
		/*egname*/  (""),
		/*explain*/ ("将文件以二进制方式读入内存"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &WArgs[0],
	} ,Fn_readfileW ,"Fn_readfileW" };
