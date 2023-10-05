#include"ElibHelp.h"
//#include <filesystem>
static void prevent_duplicate_execution(const std::wstring& identifier, int(WINAPI* callback)())
{
	if (OpenEventW(EVENT_ALL_ACCESS, false, identifier.c_str())) {

		if (callback) {
			callback();
		}

		exit(0);
	}
	CreateEventW(NULL, false, false, identifier.c_str());
}
static ARG_INFO Args[] =
{
	{
		/*name*/    "标识",
		/*explain*/ ("设置程序运行时的唯一标识，默认为当前进程名"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "子程序",
		/*explain*/ ("如果重复运行时执行的子程序，函数原型为无返回值和参数的子程序,默认为空"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_SUB_PTR,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
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
EXTERN_C void Fn_prevent_duplicate_execution_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto in_bs = elibstl::args_to_wsdata(pArgInf, 0);
	std::wstring bs = in_bs.empty() ? get_exe_name() : std::wstring(in_bs);
	auto sub = elibstl::args_to_data<DWORD>(pArgInf, 1);
	int(WINAPI * subProgram)();
	subProgram = (int(WINAPI*)())(sub.has_value() ? sub.value() : 0);
	prevent_duplicate_execution(bs, subProgram);
}

FucInfo prevent_duplicate_execution_W = { {
		/*ccname*/  ("禁止程序重复运行W"),
		/*egname*/  ("prevent_duplicate_execution_W"),
		/*explain*/ ("本命令防止同样标识的进程重复运行。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_prevent_duplicate_execution_W ,"Fn_prevent_duplicate_execution_W" };

