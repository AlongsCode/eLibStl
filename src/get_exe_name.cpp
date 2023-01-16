//#include <filesystem>
#include"ElibHelp.h"
static std::wstring get_exe_name()
{
	//std::error_code ec;
	////尝试使用标准库获取
	//std::filesystem::path exec_path = std::filesystem::read_symlink(L"/proc/self/exe", ec);
	//if (ec)
	//{
		//if (ec.value() == ENOENT)//不存在?
		//{
		//	return {};
		//}
		//else//尝试使用winapi获取
		//{
	std::wstring Path = L"";
	wchar_t szModule[MAX_PATH + 1] = { 0 };
	szModule[0] = L'\0';
	if (::GetModuleFileNameW(NULL, szModule, MAX_PATH)) {

		Path = szModule;
		Path = Path.substr(1 + Path.find_last_of(L"\\"));

	}
	return Path;
	/*}
}
return exec_path.filename().wstring();*/
}


EXTERN_C void Fn_get_exe_name_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pBin = elibkrnln::clone_textw(get_exe_name());
}

FucInfo get_exe_name_W = { {
		/*ccname*/  ("取执行文件名W"),
		/*egname*/  ("get_exe_nameW"),
		/*explain*/ ("取当前被执行的易程序文件的名称。"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_exe_name_W ,"Fn_get_exe_name_W" };

