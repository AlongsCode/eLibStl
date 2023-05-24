#include"intrin.h"
#include"ElibHelp.h"
//static std::vector<std::string> OpenManyFileDialog(const char* title, const char* filter, int initFilter, const char* initDir, bool noChangeDir, HWND parentWnd, int openMode)
//{
//	std::vector<std::string> fileNames;
//	std::vector<char> szFile(MAX_PATH * 200, 0);
//	OPENFILENAMEA ofn = { sizeof(ofn) };
//	ofn.hwndOwner = parentWnd;
//	ofn.lpstrTitle = title;
//	ofn.lpstrFilter = filter;
//	ofn.nFilterIndex = initFilter;
//	ofn.lpstrFile = szFile.data();
//	ofn.nMaxFile = static_cast<DWORD>(szFile.size());
//	ofn.lpstrInitialDir = initDir;
//	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
//	if (noChangeDir) ofn.Flags |= OFN_NOCHANGEDIR;
//	if (openMode == 1) ofn.Flags |= OFN_OVERWRITEPROMPT;
//	if (GetOpenFileNameA(&ofn))
//	{
//		char* p = szFile.data() + strlen(szFile.data()) + 1;
//		while (*p)
//		{
//			std::string szFileName(szFile.data());
//			szFileName += '\\';
//			szFileName += p;
//			fileNames.push_back(szFileName);
//			p += strlen(p) + 1;
//		}
//	}
//	return fileNames;
//}







static  std::vector<std::wstring> split_text(const std::wstring& text, const  wchar_t* str) {
	std::vector<std::wstring> ret;
	if (str == nullptr || *str == L'\0' || text == L"")
	{
		ret.push_back((text));
		return ret;
	}
	size_t start = 0, index = text.find_first_of(str, 0);
	while (index != text.npos)
	{
		if (start != index)
			ret.push_back((text.substr(start, index - start)));
		start = index + 1;
		index = text.find_first_of(str, start);
	}
	if (text.substr(start) != L"")
	{
		ret.push_back((text.substr(start)));
	}
	return ret;
}


static  std::vector<std::string> split_text(const std::string& text, const  char* str) {
	std::vector<std::string> ret;
	if (str == nullptr || *str == '\0' || text == "")
	{
		ret.push_back((text));
		return ret;
	}
	size_t start = 0, index = text.find_first_of(str, 0);
	while (index != text.npos)
	{
		if (start != index)
			ret.push_back((text.substr(start, index - start)));
		start = index + 1;
		index = text.find_first_of(str, start);
	}
	if (text.substr(start) != "")
	{
		ret.push_back((text.substr(start)));
	}
	return ret;
}




static ARG_INFO Args[] =
{
	{
		/*name*/    "����",
		/*explain*/ ("ָ���ļ��򿪶Ի���ı��⣬�����ʡ�ԣ���Ĭ��Ϊ�����������򿪵��ļ���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������",
		/*explain*/ ("�������ı��ɵ��������ɶԵ��ı�����ɣ�ÿ���ı����ĵ�һ��������ʾ��ʽ���磺���ı��ļ���*.txt�������ڶ���ָ��ʵ�ʵĹ���ƥ������磺��*.txt�������и��ı���֮���á�|���Ÿ����������ʡ�ԣ���Ĭ��û�й�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "��ʼ������",
		/*explain*/ ("���Ա�ʡ�ԡ������һ�����ṩ����Ч�Ĺ������ı����򱾲�������ָ����ʼ�Ĺ�������0Ϊ��һ���������������ʡ�ԣ���Ĭ��ֵΪ0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "��ʼĿ¼",
		/*explain*/ ("���Ա�ʡ�ԡ�ָ�����򿪶Ի���ʱ���Զ���ת����Ŀ¼�������ʡ�ԣ���Ĭ��Ϊ��ǰĿ¼��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "���ı�Ŀ¼",
		/*explain*/ ("���Ա�ʡ�ԡ�ָ���ڶԻ���رպ��Ƿ��Զ����ص�����Ի���ǰ���ļ�Ŀ¼�������ʡ�ԣ���Ĭ��ֵΪ�١�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������",
		/*explain*/ ("���Ա�ʡ�ԡ�ָ���Ի���ĸ�����,������һ��\"����\"�������ݻ���һ�������ʹ��ھ��.�����ʡ��,Ĭ��Ϊ��."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},

	{
		/*name*/    "�Ի�������",
		/*explain*/ ("0Ϊ�򿪣�1Ϊ���棬Ĭ��Ϊ0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "����ʱ��ʾ",
		/*explain*/ ("���Ա�ʡ�ԡ�����ʱ�Ƿ���ʾ.Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "����ʱ��ʾ",
		/*explain*/ ("���Ա�ʡ�ԡ�����ʱ�Ƿ���ʾ.Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "Ĭ���ļ���׺",
		/*explain*/ ("�����ļ�ʱ��Ĭ���ļ���׺"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "�Ƿ����þ�ʽ���",
		/*explain*/ ("�Ƿ����þ�ʽ�Ի�����,Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	}
	,{
		/*name*/    "Ĭ���ļ���",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_TEXT,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	}
};


static std::string OpenFileDialog(const char* title,
	const char* filter,
	int initFilter,
	const char* initDir,
	bool noChangeDir,
	HWND parentWnd,
	int openMode,
	bool bCreateprompt,
	bool bOverrideprompt,
	const char* deflutext,
	bool bOldStyle,
	const char* defaultFileName)
{
	std::string fileName;
	CHAR szFile[MAX_PATH] = { 0 };
	if (defaultFileName && *defaultFileName != '\0')
	{
		strcpy_s(szFile, MAX_PATH, ("\\" + std::string(defaultFileName)).c_str());
	}


	auto filterarry = split_text(filter, "|");
	std::vector<char> all_filter;
	for (size_t i = 0; i < filterarry.size(); i++)
	{
		if (i + 1 == filterarry.size()) {
			auto temp = std::vector<char>(filterarry[i].c_str(), filterarry[i].c_str() + filterarry[i].size());

			all_filter.insert(all_filter.end(), temp.begin(), temp.end());
			all_filter.push_back('\0');
			all_filter.push_back('\0');
		}
		else {
			auto temp = std::vector<char>(filterarry[i].c_str(), filterarry[i].c_str() + filterarry[i].size());
			all_filter.insert(all_filter.end(), temp.begin(), temp.end());
			all_filter.push_back('\0');
		}
	}
	OPENFILENAMEA ofn = { sizeof(ofn) };
	if (!all_filter.empty())
	{
		ofn.lpstrFilter = all_filter.data();
	}
	ofn.hwndOwner = parentWnd;
	ofn.lpstrTitle = title;
	ofn.nFilterIndex = initFilter;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrInitialDir = initDir;
	DWORD dwFlags = OFN_HIDEREADONLY;
	if (bCreateprompt)  dwFlags |= OFN_CREATEPROMPT;
	if (noChangeDir) dwFlags |= OFN_NOCHANGEDIR;
	if (bOverrideprompt)  dwFlags |= OFN_OVERWRITEPROMPT;
	if (bOldStyle) dwFlags |= OFN_EXPLORER;
	//�Ǳ���ģʽ�ļ�������ڣ���Ϊ�ļ�����Ĭ�Ϻ�׺

	if (openMode != 1) {
		dwFlags |= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;;
		ofn.Flags = dwFlags;
		if (GetOpenFileNameA(&ofn))
		{
			fileName = szFile;
		}
	}
	else {
		ofn.lpstrDefExt = deflutext;
		ofn.Flags = dwFlags;
		if (GetSaveFileNameA(&ofn))
		{
			fileName = szFile;
		}
	}


	return fileName;
}
EXTERN_C void Fn_Open_File_Dialog_A(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto title = elibstl::args_to_sdata(pArgInf, 0), filter = elibstl::args_to_sdata(pArgInf, 1), initDir = elibstl::args_to_sdata(pArgInf, 3), deflutext = elibstl::args_to_sdata(pArgInf, 9), deflufilename = elibstl::args_to_sdata(pArgInf, 11);;;
	int initFilter = elibstl::args_to_data<int>(pArgInf, 2).value_or(0), openMode = elibstl::args_to_data<int>(pArgInf, 6).value_or(0);
	bool noChangeDir = elibstl::args_to_data<BOOL>(pArgInf, 4).value_or(false), bCreateprompt = elibstl::args_to_data<BOOL>(pArgInf, 7).value_or(true), bOverrideprompt = elibstl::args_to_data<BOOL>(pArgInf, 8).value_or(true),
		bOldStyle = elibstl::args_to_data<BOOL>(pArgInf, 10).value_or(false);
	HWND parentWnd = reinterpret_cast<HWND> (elibstl::args_to_data<INT>(pArgInf, 5).value_or(0));
	pRetData->m_pText = elibstl::clone_text(OpenFileDialog(title.data(), filter.data(), initFilter, initDir.data(), noChangeDir, parentWnd, openMode, bCreateprompt,
		bOverrideprompt,
		deflutext.data(),
		bOldStyle, deflufilename.data()));
}

FucInfo e_Open_File_Dialog_A = { {
		/*ccname*/  ("�ļ��Ի���"),
		/*egname*/  (""),
		/*explain*/ ("��ʾһ���ļ��򿪶Ի��������û�ѡ�����������Ҫ�򿪵��Ѵ����ļ����򱣴��ļ��������û���ѡ��������Ľ���ı�������û�δ����򰴡�ȡ������ť�˳����򷵻�һ�����ı�"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_TEXT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_Open_File_Dialog_A ,"Fn_Open_File_Dialog_A" };






static ARG_INFO WArgs[] =
{
	{
		/*name*/    "����",
		/*explain*/ ("ָ���ļ��򿪶Ի���ı��⣬�����ʡ�ԣ���Ĭ��Ϊ�����������򿪵��ļ���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������",
		/*explain*/ ("�������ı��ɵ��������ɶԵ��ı�����ɣ�ÿ���ı����ĵ�һ��������ʾ��ʽ���磺���ı��ļ���*.txt�������ڶ���ָ��ʵ�ʵĹ���ƥ������磺��*.txt�������и��ı���֮���á�|���Ÿ����������ʡ�ԣ���Ĭ��û�й�����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "��ʼ������",
		/*explain*/ ("���Ա�ʡ�ԡ������һ�����ṩ����Ч�Ĺ������ı����򱾲�������ָ����ʼ�Ĺ�������0Ϊ��һ���������������ʡ�ԣ���Ĭ��ֵΪ0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "��ʼĿ¼",
		/*explain*/ ("���Ա�ʡ�ԡ�ָ�����򿪶Ի���ʱ���Զ���ת����Ŀ¼�������ʡ�ԣ���Ĭ��Ϊ��ǰĿ¼��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "���ı�Ŀ¼",
		/*explain*/ ("���Ա�ʡ�ԡ�ָ���ڶԻ���رպ��Ƿ��Զ����ص�����Ի���ǰ���ļ�Ŀ¼�������ʡ�ԣ���Ĭ��ֵΪ�١�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������",
		/*explain*/ ("���Ա�ʡ�ԡ�ָ���Ի���ĸ�����,������һ��\"����\"�������ݻ���һ�������ʹ��ھ��.�����ʡ��,Ĭ��Ϊ��."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "�Ի�������",
		/*explain*/ ("0Ϊ�򿪣�1Ϊ���棬Ĭ��Ϊ0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "����ʱ��ʾ",
		/*explain*/ ("���Ա�ʡ�ԡ�����ʱ�Ƿ���ʾ.Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "����ʱ��ʾ",
		/*explain*/ ("���Ա�ʡ�ԡ�����ʱ�Ƿ���ʾ.Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "Ĭ���ļ���׺",
		/*explain*/ ("�����ļ�ʱ��Ĭ���ļ���׺"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "�Ƿ����þ�ʽ���",
		/*explain*/ ("�Ƿ����þ�ʽ�Ի�����,Ĭ��Ϊ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	}
	,{
		/*name*/    "Ĭ���ļ���",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

static std::wstring OpenFileDialogW(const wchar_t* title, const wchar_t* filter, int initFilter, const wchar_t* initDir, bool noChangeDir, HWND parentWnd, int openMode,
	bool bCreateprompt,
	bool bOverrideprompt,
	const wchar_t* deflutext,
	bool bOldStyle,
	const wchar_t* defaultFileName) {
	std::wstring fileName;
	WCHAR szFile[MAX_PATH] = { 0 };
	if (defaultFileName && *defaultFileName != L'\0')
	{
		wcscpy_s(szFile, MAX_PATH, (L"\\" + std::wstring(defaultFileName)).c_str());
	}

	auto filterarry = split_text(filter, L"|");
	std::vector<wchar_t> all_filter;
	for (size_t i = 0; i < filterarry.size(); i++)
	{
		if (i + 1 == filterarry.size()) {
			auto temp = std::vector<wchar_t>(filterarry[i].c_str(), filterarry[i].c_str() + filterarry[i].size());

			all_filter.insert(all_filter.end(), temp.begin(), temp.end());
			all_filter.push_back(L'\0');
			all_filter.push_back(L'\0');
		}
		else {
			auto temp = std::vector<wchar_t>(filterarry[i].c_str(), filterarry[i].c_str() + filterarry[i].size());
			all_filter.insert(all_filter.end(), temp.begin(), temp.end());
			all_filter.push_back(L'\0');
		}
	}
	OPENFILENAMEW ofn = { sizeof(ofn) };
	if (!all_filter.empty())
	{
		ofn.lpstrFilter = all_filter.data();
	}
	ofn.hwndOwner = parentWnd;
	ofn.lpstrTitle = title;

	ofn.nFilterIndex = initFilter;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrInitialDir = initDir;
	DWORD dwFlags = OFN_HIDEREADONLY;
	if (bCreateprompt)  dwFlags |= OFN_CREATEPROMPT;
	if (noChangeDir) dwFlags |= OFN_NOCHANGEDIR;
	if (bOverrideprompt)  dwFlags |= OFN_OVERWRITEPROMPT;
	if (bOldStyle) dwFlags |= OFN_EXPLORER;
	//�Ǳ���ģʽ�ļ�������ڣ���Ϊ�ļ�����Ĭ�Ϻ�׺

	if (openMode != 1) {
		dwFlags |= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;;
		ofn.Flags = dwFlags;
		if (GetOpenFileNameW(&ofn))
		{
			fileName = szFile;
		}
	}
	else {
		ofn.lpstrDefExt = deflutext;
		ofn.Flags = dwFlags;
		if (GetSaveFileNameW(&ofn))
		{
			fileName = szFile;
		}
	}


	return fileName;
}


EXTERN_C void Fn_Open_File_Dialog_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto title = elibstl::args_to_wsdata(pArgInf, 0), filter = elibstl::args_to_wsdata(pArgInf, 1), initDir = elibstl::args_to_wsdata(pArgInf, 3), deflutext = elibstl::args_to_wsdata(pArgInf, 9), deflufilename = elibstl::args_to_wsdata(pArgInf, 11);;
	int initFilter = elibstl::args_to_data<int>(pArgInf, 2).value_or(0), openMode = elibstl::args_to_data<int>(pArgInf, 6).value_or(0);
	bool noChangeDir = elibstl::args_to_data<BOOL>(pArgInf, 4).value_or(false), bCreateprompt = elibstl::args_to_data<BOOL>(pArgInf, 7).value_or(true), bOverrideprompt = elibstl::args_to_data<BOOL>(pArgInf, 8).value_or(true),
		bOldStyle = elibstl::args_to_data<BOOL>(pArgInf, 10).value_or(false);
	HWND parentWnd = reinterpret_cast<HWND> (elibstl::args_to_data<INT>(pArgInf, 5).value_or(0));
	pRetData->m_pBin = elibstl::clone_textw(OpenFileDialogW(std::wstring(title).c_str(), std::wstring(filter).data(), initFilter, std::wstring(initDir).data(), noChangeDir, parentWnd, openMode, bCreateprompt,
		bOverrideprompt,
		std::wstring(deflutext).data(),
		bOldStyle, std::wstring(deflufilename).data()));
}

FucInfo e_Open_File_Dialog_W = { {
		/*ccname*/  ("�ļ��Ի���W"),
		/*egname*/  (""),
		/*explain*/ ("��ʾһ���ļ��򿪶Ի��������û�ѡ�����������Ҫ�򿪵��Ѵ����ļ����򱣴��ļ��������û���ѡ��������Ľ���ı�������û�δ����򰴡�ȡ������ť�˳����򷵻�һ�����ı�"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(WArgs) / sizeof(WArgs[0]),
		/*arg lp*/  WArgs,
	} ,Fn_Open_File_Dialog_W ,"Fn_Open_File_Dialog_W" };