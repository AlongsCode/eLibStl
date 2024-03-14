#include"intrin.h"
#include"ElibHelp.h"




#ifndef CFILEDLG_H
#define CFILEDLG_H
#include <windows.h>
#include <array>
#include <vector>
#include <tchar.h>
class CFileDlg {
public:
	//属性部分,因为都是直接读取,所以可以直接赋值
	bool  m_bCreateprompt{};//创建时提示
	bool  m_bFileMustExist{};//文件必须存在
	bool  m_bOverrideprompt{};//文件覆盖提示
	bool  m_bPathMustExist{};//目录必须存在
	bool  noChangeDir{};// 不改变目录
	bool m_SelectedFiles{};//多选
	UINT m_dwDefFilter{};//初始过滤器索引
	std::wstring m_strDefext;//默认文件后缀
	std::wstring m_strFilter;//过滤器
	std::wstring m_fileNamae;//默认返回文件名
	std::wstring m_title;//标题
	std::wstring m_strDefdir;//初始目录
private:
	OPENFILENAMEW m_ofn{};//对话框结构体
	std::array<wchar_t, 64> m_szFileTitle{};
	std::array<wchar_t, MAX_PATH>m_szFileName{};
public:
	BOOL Open(HWND pParentWnd = nullptr) {
		m_ofn.Flags = OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_EXPLORER;
		if (m_bCreateprompt)  m_ofn.Flags |= OFN_CREATEPROMPT;
		if (m_bFileMustExist)  m_ofn.Flags |= OFN_FILEMUSTEXIST;
		if (m_bOverrideprompt)  m_ofn.Flags |= OFN_OVERWRITEPROMPT;
		if (m_bPathMustExist)  m_ofn.Flags |= OFN_PATHMUSTEXIST;
		if (noChangeDir)  m_ofn.Flags |= OFN_NOCHANGEDIR;
		if (m_SelectedFiles) m_ofn.Flags |= OFN_ALLOWMULTISELECT;

		if (!m_fileNamae.empty())
			wcscpy_s(m_szFileName.data(), static_cast<INT>(m_fileNamae.size()), m_fileNamae.data());

		for (auto& c : m_strFilter) {//处理过滤器
			if (c == L'|')
				c = L'\0';
		}

		while (pParentWnd != nullptr) {//处理顶层窗口
			auto tempParent = ::GetParent(pParentWnd);
			if (tempParent == nullptr)
				break;
			pParentWnd = tempParent;
		}
		m_ofn.lStructSize = sizeof(m_ofn);
		m_ofn.lpstrDefExt = m_strDefext.c_str(); //默认文件后缀
		m_ofn.lpstrFilter = m_strFilter.data();//过滤器
		m_ofn.lpstrFile = m_szFileName.data();
		m_ofn.nMaxFile = static_cast<DWORD>(m_szFileName.size());
		m_ofn.lpstrFileTitle = m_szFileTitle.data();
		m_ofn.nMaxFileTitle = static_cast<DWORD>(m_szFileTitle.size());
		m_ofn.nFilterIndex = m_strFilter.empty() ? 0 : (m_dwDefFilter < 0 ? 0 : m_dwDefFilter + 1);//默认过滤器索引
		m_ofn.lpstrTitle = m_title.data();//标题
		m_ofn.lpstrInitialDir = m_strDefdir.data();//默认目录
		m_ofn.hwndOwner = pParentWnd;

		BOOL bEnableParent = FALSE;
		HWND hWndFocus = ::GetFocus();
		if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
		{
			bEnableParent = TRUE;
			::EnableWindow(m_ofn.hwndOwner, FALSE);
		}
		BOOL nResult = ::GetOpenFileNameW(&m_ofn);
		if (bEnableParent)
			::EnableWindow(m_ofn.hwndOwner, TRUE);
		if (::IsWindow(hWndFocus))
			::SetFocus(hWndFocus);

		if (nResult)
		{
			//记忆过滤器
			m_dwDefFilter = (0 > m_ofn.nFilterIndex - 1) ? 0 : (m_ofn.nFilterIndex - 1);
			return TRUE;
		}
		return FALSE;
	}
	BOOL Save(HWND pParentWnd = nullptr)
	{
		m_ofn.Flags = OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_EXPLORER;
		if (m_bCreateprompt)  m_ofn.Flags |= OFN_CREATEPROMPT;
		if (m_bFileMustExist)  m_ofn.Flags |= OFN_FILEMUSTEXIST;
		if (m_bOverrideprompt)  m_ofn.Flags |= OFN_OVERWRITEPROMPT;
		if (m_bPathMustExist)  m_ofn.Flags |= OFN_PATHMUSTEXIST;
		if (noChangeDir)  m_ofn.Flags |= OFN_NOCHANGEDIR;
		if (m_SelectedFiles) m_ofn.Flags |= OFN_ALLOWMULTISELECT;

		if (!m_fileNamae.empty())
			wcscpy_s(m_szFileName.data(), static_cast<INT>(m_fileNamae.size()), m_fileNamae.data());

		for (auto& c : m_strFilter) {//处理过滤器
			if (c == L'|')
				c = L'\0';
		}

		while (pParentWnd != nullptr) {//处理顶层窗口
			auto tempParent = ::GetParent(pParentWnd);
			if (tempParent == nullptr)
				break;
			pParentWnd = tempParent;
		}
		m_ofn.lStructSize = sizeof(m_ofn);
		m_ofn.lpstrDefExt = m_strDefext.c_str(); //默认文件后缀
		m_ofn.lpstrFilter = m_strFilter.data();//过滤器
		m_ofn.lpstrFile = m_szFileName.data();
		m_ofn.nMaxFile = static_cast<DWORD>(m_szFileName.size());
		m_ofn.lpstrFileTitle = m_szFileTitle.data();
		m_ofn.nMaxFileTitle = static_cast<DWORD>(m_szFileTitle.size());
		m_ofn.nFilterIndex = m_strFilter.empty() ? 0 : (m_dwDefFilter < 0 ? 0 : m_dwDefFilter + 1);//默认过滤器索引
		m_ofn.lpstrTitle = m_title.data();//标题
		m_ofn.lpstrInitialDir = m_strDefdir.data();//默认目录
		m_ofn.hwndOwner = pParentWnd;

		BOOL bEnableParent = FALSE;
		HWND hWndFocus = ::GetFocus();
		if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
		{
			bEnableParent = TRUE;
			::EnableWindow(m_ofn.hwndOwner, FALSE);
		}
		BOOL nResult = ::GetSaveFileNameW(&m_ofn);
		if (bEnableParent)
			::EnableWindow(m_ofn.hwndOwner, TRUE);
		if (::IsWindow(hWndFocus))
			::SetFocus(hWndFocus);

		if (nResult)
		{
			//记忆过滤器
			m_dwDefFilter = (0 > m_ofn.nFilterIndex - 1) ? 0 : (m_ofn.nFilterIndex - 1);
			return TRUE;
		}
		return FALSE;

	}


	std::wstring GetFullName() const {
		return m_szFileName.data();
	}

	std::wstring GetName() const {
		return  m_szFileTitle.data();
	}
	std::vector<LPBYTE> GetAllPathName() {
		int pos = 0;
		std::vector<LPBYTE> ret;
		do {
			auto temp = std::wstring(GetNextPathName(pos).data());
			if (!temp.empty())
				ret.push_back(elibstl::clone_textw(temp));
			
		} while (pos != -1);
		return ret;
	}

private:
	std::wstring GetNextPathName(int& pos) const
	{
		int maxFileSize = static_cast<int>(m_ofn.nMaxFile);
		int bufferSize = (260 < maxFileSize - pos) ? 260 : (maxFileSize - pos);
		std::wstring fileNames(m_ofn.lpstrFile + pos, m_ofn.lpstrFile + pos + bufferSize);
		size_t index = 0;
		if (pos == 0)
		{
			index = fileNames.find(L'\0');

			if (index == std::wstring::npos || (fileNames.at(++index) == L'\0'))
			{
				pos = -1;
				return m_ofn.lpstrFile;
			}
		}
		std::wstring pathName = m_ofn.lpstrFile;
		std::wstring fileName = m_ofn.lpstrFile + pos + index;

		int fileLength = lstrlenW(fileName.data());
		if (fileNames.at(index + fileLength + 1) == L'\0')
			pos = -1;
		else
			pos = pos + static_cast<UINT>(index) + fileLength + 1;

		if (!pathName.empty())
		{
			int pathLength = static_cast<int>(pathName.size());
			TCHAR termination = pathName.at(pathLength - 1);

			if (termination == L'\\')
				return pathName + fileName;

		}
		return pathName + L'\\' + fileName;
	}
};

#endif









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
		/*name*/    "标题",
		/*explain*/ ("指定文件打开对话框的标题，如果被省略，则默认为“请输入欲打开的文件："),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "过滤器",
		/*explain*/ ("过滤器文本由单个或多个成对的文本串组成，每对文本串的第一个描述显示形式，如：“文本文件（*.txt）”；第二个指定实际的过滤匹配符，如：“*.txt”，所有各文本串之间用“|”号隔开。如果被省略，则默认没有过滤器"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/  ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "初始过滤器",
		/*explain*/ ("可以被省略。如果上一参数提供了有效的过滤器文本，则本参数用作指定初始的过滤器，0为第一个过滤器。如果被省略，则默认值为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "初始目录",
		/*explain*/ ("可以被省略。指定当打开对话框时所自动跳转到的目录，如果被省略，则默认为当前目录。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "不改变目录",
		/*explain*/ ("可以被省略。指定在对话框关闭后是否自动返回到进入对话框前的文件目录，如果被省略，则默认值为假。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ ("可以被省略。指定对话框的父窗口,可以是一个\"窗口\"类型数据或者一个整数型窗口句柄.如果被省略,默认为无."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},

	{
		/*name*/    "对话框类型",
		/*explain*/ ("0为打开，1为保存，默认为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "创建时提示",
		/*explain*/ ("可以被省略。创建时是否提示.默认为真"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "覆盖时提示",
		/*explain*/ ("可以被省略。创建时是否提示.默认为真"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "默认文件后缀",
		/*explain*/ ("保存文件时，默认文件后缀"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "是否启用旧式风格",
		/*explain*/ ("是否启用旧式对话框风格,默认为假"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
	,{
		/*name*/    "默认文件名",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
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
	//非保存模式文件必须存在，且为文件增加默认后缀

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
		/*ccname*/  ("文件对话框"),
		/*egname*/  (""),
		/*explain*/ ("显示一个文件打开对话框，允许用户选择或输入所需要打开的已存在文件，或保存文件，返回用户所选择或输入后的结果文本。如果用户未输入或按“取消”按钮退出，则返回一个空文本"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     SDT_TEXT,
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
		/*name*/    "标题",
		/*explain*/ ("指定文件打开对话框的标题，如果被省略，则默认为“请输入欲打开的文件："),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "过滤器",
		/*explain*/ ("过滤器文本由单个或多个成对的文本串组成，每对文本串的第一个描述显示形式，如：“文本文件（*.txt）”；第二个指定实际的过滤匹配符，如：“*.txt”，所有各文本串之间用“|”号隔开。如果被省略，则默认没有过滤器"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "初始过滤器",
		/*explain*/ ("可以被省略。如果上一参数提供了有效的过滤器文本，则本参数用作指定初始的过滤器，0为第一个过滤器。如果被省略，则默认值为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "初始目录",
		/*explain*/ ("可以被省略。指定当打开对话框时所自动跳转到的目录，如果被省略，则默认为当前目录。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "不改变目录",
		/*explain*/ ("可以被省略。指定在对话框关闭后是否自动返回到进入对话框前的文件目录，如果被省略，则默认值为假。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ ("可以被省略。指定对话框的父窗口,可以是一个\"窗口\"类型数据或者一个整数型窗口句柄.如果被省略,默认为无."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "对话框类型",
		/*explain*/ ("0为打开，1为保存，默认为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "创建时提示",
		/*explain*/ ("可以被省略。创建时是否提示.默认为真"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "覆盖时提示",
		/*explain*/ ("可以被省略。创建时是否提示.默认为真"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "默认文件后缀",
		/*explain*/ ("保存文件时，默认文件后缀"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "保存时目录必须存在",
		/*explain*/ ("保存时目录不存在则不会创建"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
	,{
		/*name*/    "默认文件名",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}, {
		/*name*/    "保存时文件必须存在",
		/*explain*/ ("保存时文件不存在则不会创建"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

static std::wstring OpenFileDialogW(
	const wchar_t* title, 
	const wchar_t* filter, 
	int initFilter, 
	const wchar_t* initDir, 
	bool noChangeDir, 
	HWND parentWnd, 
	int openMode,
	bool bCreateprompt,
	bool bOverrideprompt,
	const wchar_t* deflutext,
	bool bPathMustExist,
	const wchar_t* defaultFileName,
	bool bFileMustExist
) {
	CFileDlg dlg;
	dlg.m_bFileMustExist = bFileMustExist;
	dlg.m_SelectedFiles = true;
	dlg.m_bCreateprompt = bCreateprompt;
	dlg.m_bOverrideprompt = bOverrideprompt;
	dlg.m_strDefext = deflutext;
	dlg.m_strDefdir = initDir;
	dlg.m_fileNamae = defaultFileName;
	dlg.m_strFilter = filter;
	dlg.m_dwDefFilter = initFilter;
	dlg.noChangeDir = noChangeDir;
	dlg.m_bPathMustExist = bPathMustExist;
	dlg.m_title = title;
	if (openMode == 0)
		dlg.Open(parentWnd);
	else
		dlg.Save(parentWnd);
	return dlg.GetFullName();
}


EXTERN_C void Fn_Open_File_Dialog_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto title = elibstl::args_to_wsdata(pArgInf, 0), filter = elibstl::args_to_wsdata(pArgInf, 1), initDir = elibstl::args_to_wsdata(pArgInf, 3), deflutext = elibstl::args_to_wsdata(pArgInf, 9), deflufilename = elibstl::args_to_wsdata(pArgInf, 11);;
	int initFilter = elibstl::args_to_data<int>(pArgInf, 2).value_or(0), openMode = elibstl::args_to_data<int>(pArgInf, 6).value_or(0);
	bool noChangeDir = elibstl::args_to_data<BOOL>(pArgInf, 4).value_or(false), bCreateprompt = elibstl::args_to_data<BOOL>(pArgInf, 7).value_or(true), bOverrideprompt = elibstl::args_to_data<BOOL>(pArgInf, 8).value_or(true),
		bOldStyle = elibstl::args_to_data<BOOL>(pArgInf, 10).value_or(false),fileMustExist= elibstl::args_to_data<BOOL>(pArgInf, 12).value_or(false);
	HWND parentWnd = reinterpret_cast<HWND> (elibstl::args_to_data<INT>(pArgInf, 5).value_or(0));
	pRetData->m_pBin = elibstl::clone_textw(OpenFileDialogW(std::wstring(title).c_str(), std::wstring(filter).data(), initFilter, std::wstring(initDir).data(), noChangeDir, parentWnd, openMode, bCreateprompt,
		bOverrideprompt,
		std::wstring(deflutext).data(),
		bOldStyle, std::wstring(deflufilename).data(), fileMustExist));
}

FucInfo e_Open_File_Dialog_W = { {
		/*ccname*/  ("文件对话框W"),
		/*egname*/  (""),
		/*explain*/ ("显示一个文件打开对话框，允许用户选择或输入所需要打开的已存在文件，或保存文件，返回用户所选择或输入后的结果文本。如果用户未输入或按“取消”按钮退出，则返回一个空文本"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(WArgs) / sizeof(WArgs[0]),
		/*arg lp*/  WArgs,
	} ,Fn_Open_File_Dialog_W ,"Fn_Open_File_Dialog_W" };










































static std::vector<LPBYTE> OpenFileManyDialogW(
	const wchar_t* title,
	const wchar_t* filter,
	int initFilter,
	const wchar_t* initDir,
	bool noChangeDir,
	HWND parentWnd,
	int openMode,
	bool bCreateprompt,
	bool bOverrideprompt,
	const wchar_t* deflutext,
	bool bPathMustExist,
	const wchar_t* defaultFileName,
	bool bFileMustExist
) {
	CFileDlg dlg;
	dlg.m_bFileMustExist = bFileMustExist;
	dlg.m_SelectedFiles = true;
	dlg.m_bCreateprompt = bCreateprompt;
	dlg.m_bOverrideprompt = bOverrideprompt;
	dlg.m_strDefext = deflutext;
	dlg.m_strDefdir = initDir;
	dlg.m_fileNamae = defaultFileName;
	dlg.m_strFilter = filter;
	dlg.m_dwDefFilter = initFilter;
	dlg.noChangeDir = noChangeDir;
	dlg.m_bPathMustExist = bPathMustExist;
	dlg.m_title = title;
	if (openMode == 0)
		dlg.Open(parentWnd);
	else
		dlg.Save(parentWnd);
	return dlg.GetAllPathName();
}


EXTERN_C void fn_OpenFileManyDialog_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto title = elibstl::args_to_wsdata(pArgInf, 0), filter = elibstl::args_to_wsdata(pArgInf, 1), initDir = elibstl::args_to_wsdata(pArgInf, 3), deflutext = elibstl::args_to_wsdata(pArgInf, 9), deflufilename = elibstl::args_to_wsdata(pArgInf, 11);;
	int initFilter = elibstl::args_to_data<int>(pArgInf, 2).value_or(0), openMode = elibstl::args_to_data<int>(pArgInf, 6).value_or(0);
	bool noChangeDir = elibstl::args_to_data<BOOL>(pArgInf, 4).value_or(false), bCreateprompt = elibstl::args_to_data<BOOL>(pArgInf, 7).value_or(true), bOverrideprompt = elibstl::args_to_data<BOOL>(pArgInf, 8).value_or(true),
		bOldStyle = elibstl::args_to_data<BOOL>(pArgInf, 10).value_or(false), fileMustExist = elibstl::args_to_data<BOOL>(pArgInf, 12).value_or(false);;
	HWND parentWnd = reinterpret_cast<HWND> (elibstl::args_to_data<INT>(pArgInf, 5).value_or(0));


	auto ret = OpenFileManyDialogW(std::wstring(title).c_str(), std::wstring(filter).data(), initFilter, std::wstring(initDir).data(), noChangeDir, parentWnd, openMode, bCreateprompt,
		bOverrideprompt,
		std::wstring(deflutext).data(),
		bOldStyle, std::wstring(deflufilename).data(),fileMustExist);
	elibstl::create_array<LPBYTE>(ret.data(), ret.size());
	pRetData->m_pAryData = elibstl::create_array<LPBYTE>(ret.data(), ret.size());
}

FucInfo Fn_eStl_FileManyDialogW = { {
		/*ccname*/  ("多文件对话框W"),
		/*egname*/  (""),
		/*explain*/ ("显示一个文件对话框，允许用户选择或输入所需要打开的已存在文件，或保存文件，返回用户所选择或输入后的结果文本数组。如果用户未输入或按“取消”按钮退出，则返回一个空数组"),
		/*category*/13,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(WArgs) / sizeof(WArgs[0]),
		/*arg lp*/  WArgs,
	} ,fn_OpenFileManyDialog_W ,"fn_OpenFileManyDialog_W" };