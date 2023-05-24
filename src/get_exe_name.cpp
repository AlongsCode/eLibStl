//#include <filesystem>
#include"ElibHelp.h"
static std::wstring get_exe_name()
{
	//std::error_code ec;
	////����ʹ�ñ�׼���ȡ
	//std::filesystem::path exec_path = std::filesystem::read_symlink(L"/proc/self/exe", ec);
	//if (ec)
	//{
		//if (ec.value() == ENOENT)//������?
		//{
		//	return {};
		//}
		//else//����ʹ��winapi��ȡ
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
	pRetData->m_pBin = elibstl::clone_textw(get_exe_name());
}

FucInfo get_exe_name_W = { {
		/*ccname*/  ("ȡִ���ļ���W"),
		/*egname*/  ("get_exe_nameW"),
		/*explain*/ ("ȡ��ǰ��ִ�е��׳����ļ������ơ�"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_exe_name_W ,"Fn_get_exe_name_W" };

