#include<vector>
//#include<filesystem>
#include"ElibHelp.h"
using namespace std;
inline int MyStrcmp(const wchar_t* szSource, const wchar_t* szDest)
{
	if (szSource == NULL)  szSource = L"";
	if (szDest == NULL)  szDest = L"";

	int nResult = 0;
	while (!(nResult = (int)(*szSource - *szDest)) && *szDest)
	{
		szSource++;
		szDest++;
	}

	return nResult;
}
static wstring get_complete_path(const wstring& filename, const wstring& path)
{
	// 取当前目录
	wstring strCurrentDir;
	if (path.empty())
	{
		//strCurrentDir = std::filesystem::current_path().wstring();
		const intptr_t BUF_SIZE = 1024;
		wchar_t CurrentDirBuf[BUF_SIZE] = { 0 };

		::GetCurrentDirectoryW(BUF_SIZE, CurrentDirBuf);
		strCurrentDir = CurrentDirBuf;

	}
	else
	{
		strCurrentDir = path;
	}

	// 按'/'或'\\'分割
	vector<wstring> tokens;

	wstring strPath = strCurrentDir;
	strPath += L"/";
	strPath += filename;
	const wchar_t* szPrevToken = strPath.c_str();
	for (const wchar_t* p = szPrevToken; *p; ++p)
	{
		if (*p == L'\\' || *p == L'/')
		{
			tokens.push_back(wstring(szPrevToken, p - szPrevToken));
			szPrevToken = p + 1;
		}
	}
	if (*szPrevToken)
	{
		tokens.push_back(szPrevToken);
	}

	// 处理 "." 和 ".."
	vector<wstring>  tempArray;
	for (size_t n = 0; n < tokens.size(); ++n)
	{
		wstring szTok = tokens[n];
		if (szTok.empty()) {
			continue;
		}
		else if (MyStrcmp(L".", szTok.c_str()) == 0) {
			continue;
		}
		else if (MyStrcmp(L"..", szTok.c_str()) == 0)
		{
			size_t nTempArrayCount = tempArray.size();
			if (nTempArrayCount > 1)
			{
				tempArray.pop_back();
			}
		}
		else
		{
			tempArray.push_back(szTok);
		}
	}
	// 生成最终文本
	size_t nCount = tempArray.size();
	wstring strReturn;
	for (size_t n2 = 0; n2 < nCount; ++n2)
	{
		strReturn += tempArray[n2];
		if (n2 != nCount - 1)
		{
			strReturn += L"/";
		}
	}
	return strReturn;
}



static ARG_INFO Args[] =
{
	{
		/*name*/    "文件名",
		/*explain*/ ("欲组合的文件名"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "路径名",
		/*explain*/ ("欲组合的路径名，默认为当前目录"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_get_complete_path_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	auto filename = elibstl::args_to_wsdata(pArgInf, 0);
	auto path = elibstl::args_to_wsdata(pArgInf, 1);
	pRetData->m_pBin = elibstl::clone_textw(get_complete_path(wstring(filename), wstring(path)));
}

FucInfo get_complete_path_W = { {
		/*ccname*/  ("取完整路径W"),
		/*egname*/  ("GetCompletePathW"),
		/*explain*/ ("获取文件的完整路径，也就是合并文件名和路径，会自动匹配\"\\\""),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_get_complete_path_W ,"Fn_get_complete_path_W" };
