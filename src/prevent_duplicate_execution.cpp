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
		/*name*/    "��ʶ",
		/*explain*/ ("���ó�������ʱ��Ψһ��ʶ��Ĭ��Ϊ��ǰ������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�ӳ���",
		/*explain*/ ("����ظ�����ʱִ�е��ӳ��򣬺���ԭ��Ϊ�޷���ֵ�Ͳ������ӳ���,Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_SUB_PTR,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
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
		/*ccname*/  ("��ֹ�����ظ�����W"),
		/*egname*/  ("prevent_duplicate_execution_W"),
		/*explain*/ ("�������ֹͬ����ʶ�Ľ����ظ����С�"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_prevent_duplicate_execution_W ,"Fn_prevent_duplicate_execution_W" };

