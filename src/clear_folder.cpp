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
		/*name*/    "�ļ���",
		/*explain*/ ("��������ļ���"),
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
		/*ccname*/  ("���Ŀ¼W"),
		/*egname*/  (""),
		/*explain*/ ("��ָ��Ŀ¼�����е��ļ���գ����������ļ���ϵͳ�ļ����ļ��е�,ʹ���������֮ǰ����ȷ�����˽��Լ��ڲ�������ʲô�ļ�"),
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

