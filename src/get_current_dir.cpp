#include"ElibHelp.h"
//#include<filesystem>

std::wstring get_current_path() {

	std::wstring Path;
	wchar_t szModule[MAX_PATH];
	if (GetModuleFileNameW(NULL, szModule, MAX_PATH)) {
		Path = szModule;
		Path = Path.substr(0, Path.find_last_of(L"\\"));

	}
	return Path;

}

EXTERN_C void Fn_current_path_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	//标准库不给用，恶心
	//pRetData->m_pBin = elibkrnln::clone_textw(std::filesystem::current_path().wstring());
	pRetData->m_pBin = elibstl::clone_textw(get_current_path());

}

FucInfo current_path_W = { {
		/*ccname*/  ("取运行目录W"),
		/*egname*/  ("current_pathW"),
		/*explain*/ ("取当前被执行的易程序文件所处的目录。"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_current_path_W ,"Fn_current_path_W" };

