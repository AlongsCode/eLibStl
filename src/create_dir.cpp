//#include <fstream> 
//#include <filesystem>
#include"ElibHelp.h"
//服了，不能用标准库，操死了命名一个create_directories的事情
#pragma warning(disable:4996)
static bool CreatedirectoryNp(const std::wstring& path) {

	SECURITY_ATTRIBUTES SecAttrib;
	SecAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
	SecAttrib.lpSecurityDescriptor = NULL;
	SecAttrib.bInheritHandle = FALSE;

	return CreateDirectoryW(path.c_str(), &SecAttrib);//创建目录
}
static inline std::wstring RemoveEndPathChar(const std::wstring& szPath, const std::wstring& strBuf)
{

	if (szPath.empty() || szPath[1] == L'\0')  // 为空或者只有1个字符?
		return szPath;

	size_t npLength = szPath.size();

	while (szPath[npLength - 1] == L'\\')  // 以路径字符结束?
	{
		if (szPath[npLength - 2] == ':')  // 避免删除驱动器符后的路径字符
			break;
		return std::wstring(szPath, npLength - 1);
	}
	return szPath;
}
static bool Createdirectory(std::wstring szOSDirectoryName)
{

	if (szOSDirectoryName.empty())
		return FALSE;

	// 去除掉目录尾部的路径符
	std::wstring strBuf;
	szOSDirectoryName = RemoveEndPathChar(szOSDirectoryName, strBuf);
	if (szOSDirectoryName[0] == L'\0' ||  // 为"\"?
		(szOSDirectoryName[1] == ':' && szOSDirectoryName[2] == L'\0') ||  // 为类似'c:"?
		::CreateDirectoryW(szOSDirectoryName.c_str(), NULL))
	{
		return TRUE;
	}

	const DWORD dwError = ::GetLastError();
	if (dwError == ERROR_ALREADY_EXISTS)  // 已经存在则返回真
		return TRUE;

	// 在Windows平台下自动创建中间目录
	if (dwError == ERROR_PATH_NOT_FOUND)  // 中间目录不存在?
	{
		WCHAR* wstr = new WCHAR[szOSDirectoryName.size() + 1];
		wcscpy(wstr, szOSDirectoryName.c_str());
		const WCHAR* ps = wcsrchr(wstr, L'\\');  // 寻找上一级目录
		if (ps != NULL && ps[1] == L'\0')  // 所找到的OS_PATH_CHAR位于目录结尾?
		{
			ps--;
			while (ps >= wstr && *ps != L'\\')
				ps--;
			if (ps < wstr)
				ps = NULL;
		}

		if (ps != NULL)  // 找到了上一级目录?
		{
			std::wstring str(wstr, ps - wstr);

			if (Createdirectory(str.c_str())) { // 上一级目录创建成功?
				delete[]wstr;
				return ::CreateDirectoryW(szOSDirectoryName.c_str(), NULL);
			}
		}
		delete[]wstr;
	}
	return FALSE;
}

static bool create_dir(const std::wstring& path, bool force) {
	/*std::filesystem::path p(path);
	if (!force)
	{
		if (!std::filesystem::exists(p.parent_path())) {
			return false;
		}
	}
	return std::filesystem::create_directories(path);*/

	if (force)
	{
		return Createdirectory(path);
	}
	return CreatedirectoryNp(path);
}

static ARG_INFO Args[] =
{
	{
		/*name*/    "路径",
		/*explain*/ ("欲创建的路径"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	},
	{
		/*name*/    "是否强制创建",
		/*explain*/ ("为真时，如果指定目录未存在父目录，则会创建父目录后创建指定目录，否则指定路径的父路径不存在时返回假，默认为假"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};


EXTERN_C void Fn_create_dir_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto filename = elibstl::args_to_wsdata(pArgInf, 0);
	auto force = elibstl::args_to_data<BOOL>(pArgInf, 1);
	pRetData->m_bool = create_dir(std::wstring(filename), force.has_value() ? force.value() : FALSE);
}

FucInfo create_dir_W = { {
		/*ccname*/  ("创建目录W"),
		/*egname*/  ("MkDirW"),
		/*explain*/ ("创建一个新的目录。成功返回真，失败返回假。"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_create_dir_W ,"Fn_create_dir_W" };

