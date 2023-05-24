#include <fstream>  
#include"ElibHelp.h"

static bool ClearFolder(const std::wstring& folderPath)
{
	std::wstring searchPath = folderPath + L"\\*.*";
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	do
	{
		std::wstring currentPath = folderPath + L"\\" + findData.cFileName;

		// ignore "." and ".."
		if (wcscmp(findData.cFileName, L".") && wcscmp(findData.cFileName, L".."))
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// recursively clear subfolder
				ClearFolder(currentPath);
				RemoveDirectoryW(currentPath.c_str());
			}
			else
			{
				// delete file
				DeleteFileW(currentPath.c_str());
			}
		}
	} while (FindNextFileW(hFind, &findData));

	FindClose(hFind);
	return true;
}


static ARG_INFO Args[] =
{
	{
		/*name*/    "文件夹",
		/*explain*/ ("欲清除的文件夹"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_clear_folder_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto filename = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_bool = ClearFolder(std::wstring(filename));
}

FucInfo clear_folder_W = { {
		/*ccname*/  ("清空目录W"),
		/*egname*/  (""),
		/*explain*/ ("将指定目录下所有的文件清空，包括隐藏文件、系统文件和文件夹等,使用这个函数之前，请确保你了解自己在操作的是什么文件"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_clear_folder_W ,"Fn_clear_folder_W" };

