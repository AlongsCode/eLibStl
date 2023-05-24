//#include <fstream> 
//#include <filesystem>
#include"ElibHelp.h"
//���ˣ������ñ�׼�⣬����������һ��create_directories������
#pragma warning(disable:4996)
static bool CreatedirectoryNp(const std::wstring& path) {

	SECURITY_ATTRIBUTES SecAttrib;
	SecAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
	SecAttrib.lpSecurityDescriptor = NULL;
	SecAttrib.bInheritHandle = FALSE;

	return CreateDirectoryW(path.c_str(), &SecAttrib);//����Ŀ¼
}
static inline std::wstring RemoveEndPathChar(const std::wstring& szPath, const std::wstring& strBuf)
{

	if (szPath.empty() || szPath[1] == L'\0')  // Ϊ�ջ���ֻ��1���ַ�?
		return szPath;

	size_t npLength = szPath.size();

	while (szPath[npLength - 1] == L'\\')  // ��·���ַ�����?
	{
		if (szPath[npLength - 2] == ':')  // ����ɾ�������������·���ַ�
			break;
		return std::wstring(szPath, npLength - 1);
	}
	return szPath;
}
static bool Createdirectory(std::wstring szOSDirectoryName)
{

	if (szOSDirectoryName.empty())
		return FALSE;

	// ȥ����Ŀ¼β����·����
	std::wstring strBuf;
	szOSDirectoryName = RemoveEndPathChar(szOSDirectoryName, strBuf);
	if (szOSDirectoryName[0] == L'\0' ||  // Ϊ"\"?
		(szOSDirectoryName[1] == ':' && szOSDirectoryName[2] == L'\0') ||  // Ϊ����'c:"?
		::CreateDirectoryW(szOSDirectoryName.c_str(), NULL))
	{
		return TRUE;
	}

	const DWORD dwError = ::GetLastError();
	if (dwError == ERROR_ALREADY_EXISTS)  // �Ѿ������򷵻���
		return TRUE;

	// ��Windowsƽ̨���Զ������м�Ŀ¼
	if (dwError == ERROR_PATH_NOT_FOUND)  // �м�Ŀ¼������?
	{
		WCHAR* wstr = new WCHAR[szOSDirectoryName.size() + 1];
		wcscpy(wstr, szOSDirectoryName.c_str());
		const WCHAR* ps = wcsrchr(wstr, L'\\');  // Ѱ����һ��Ŀ¼
		if (ps != NULL && ps[1] == L'\0')  // ���ҵ���OS_PATH_CHARλ��Ŀ¼��β?
		{
			ps--;
			while (ps >= wstr && *ps != L'\\')
				ps--;
			if (ps < wstr)
				ps = NULL;
		}

		if (ps != NULL)  // �ҵ�����һ��Ŀ¼?
		{
			std::wstring str(wstr, ps - wstr);

			if (Createdirectory(str.c_str())) { // ��һ��Ŀ¼�����ɹ�?
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
		/*name*/    "·��",
		/*explain*/ ("��������·��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	},
	{
		/*name*/    "�Ƿ�ǿ�ƴ���",
		/*explain*/ ("Ϊ��ʱ�����ָ��Ŀ¼δ���ڸ�Ŀ¼����ᴴ����Ŀ¼�󴴽�ָ��Ŀ¼������ָ��·���ĸ�·��������ʱ���ؼ٣�Ĭ��Ϊ��"),
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
		/*ccname*/  ("����Ŀ¼W"),
		/*egname*/  ("MkDirW"),
		/*explain*/ ("����һ���µ�Ŀ¼���ɹ������棬ʧ�ܷ��ؼ١�"),
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

