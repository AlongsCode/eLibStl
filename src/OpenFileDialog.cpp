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

static ARG_INFO Args[] =
{
	{
		/*name*/    "标题",
		/*explain*/ ("指定文件打开对话框的标题，如果被省略，则默认为“请输入欲打开的文件："),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "过滤器",
		/*explain*/ ("过滤器文本由单个或多个成对的文本串组成，每对文本串的第一个描述显示形式，如：“文本文件（*.txt）”；第二个指定实际的过滤匹配符，如：“*.txt”，所有各文本串之间用“|”号隔开。如果被省略，则默认没有过滤器"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "初始过滤器",
		/*explain*/ ("可以被省略。如果上一参数提供了有效的过滤器文本，则本参数用作指定初始的过滤器，0为第一个过滤器。如果被省略，则默认值为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "初始目录",
		/*explain*/ ("可以被省略。指定当打开对话框时所自动跳转到的目录，如果被省略，则默认为当前目录。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_TEXT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "不改变目录",
		/*explain*/ ("可以被省略。指定在对话框关闭后是否自动返回到进入对话框前的文件目录，如果被省略，则默认值为假。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ ("可以被省略。指定对话框的父窗口,可以是一个\"窗口\"类型数据或者一个整数型窗口句柄.如果被省略,默认为无."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "对话框类型",
		/*explain*/ ("0为打开，1为保存，默认为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};


static std::string OpenFileDialog(const char* title, const char* filter, int initFilter, const char* initDir, bool noChangeDir, HWND parentWnd, int openMode)
{
	std::string fileName;
	CHAR szFile[MAX_PATH] = { 0 };
	OPENFILENAMEA ofn = { sizeof(ofn) };
	ofn.hwndOwner = parentWnd;
	ofn.lpstrTitle = title;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = initFilter;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrInitialDir = initDir;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	if (noChangeDir) ofn.Flags |= OFN_NOCHANGEDIR;
	if (openMode == 1) ofn.Flags |= OFN_OVERWRITEPROMPT;
	if (GetOpenFileNameA(&ofn))
	{
		fileName = szFile;
	}
	return fileName;
}
EXTERN_C void Fn_Open_File_Dialog_A(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto title = elibstl::args_to_sdata(pArgInf, 0), filter = elibstl::args_to_sdata(pArgInf, 1), initDir = elibstl::args_to_sdata(pArgInf, 3);
	int initFilter = elibstl::args_to_data<int>(pArgInf, 2).value_or(0), openMode = elibstl::args_to_data<int>(pArgInf, 6).value_or(0);
	bool noChangeDir = elibstl::args_to_data<BOOL>(pArgInf, 4).value_or(false);
	HWND parentWnd = reinterpret_cast<HWND> (elibstl::args_to_data<INT>(pArgInf, 5).value_or(0));
	pRetData->m_pText = elibstl::clone_text(OpenFileDialog(title.data(), filter.data(), initFilter, initDir.data(), noChangeDir, parentWnd, openMode));
}

FucInfo e_Open_File_Dialog_A = { {
		/*ccname*/  ("文件选择夹"),
		/*egname*/  (""),
		/*explain*/ ("显示一个文件打开对话框，允许用户选择或输入所需要打开的已存在文件，或保存文件，返回用户所选择或输入后的结果文本。如果用户未输入或按“取消”按钮退出，则返回一个空文本"),
		/*category*/6,
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
		/*state*/    AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "过滤器",
		/*explain*/ ("过滤器文本由单个或多个成对的文本串组成，每对文本串的第一个描述显示形式，如：“文本文件（*.txt）”；第二个指定实际的过滤匹配符，如：“*.txt”，所有各文本串之间用“|”号隔开。如果被省略，则默认没有过滤器"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/  AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "初始过滤器",
		/*explain*/ ("可以被省略。如果上一参数提供了有效的过滤器文本，则本参数用作指定初始的过滤器，0为第一个过滤器。如果被省略，则默认值为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "初始目录",
		/*explain*/ ("可以被省略。指定当打开对话框时所自动跳转到的目录，如果被省略，则默认为当前目录。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY ,
	},
	{
		/*name*/    "不改变目录",
		/*explain*/ ("可以被省略。指定在对话框关闭后是否自动返回到进入对话框前的文件目录，如果被省略，则默认值为假。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ ("可以被省略。指定对话框的父窗口,可以是一个\"窗口\"类型数据或者一个整数型窗口句柄.如果被省略,默认为无."),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "对话框类型",
		/*explain*/ ("0为打开，1为保存，默认为0"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};



static std::wstring OpenFileDialogW(const wchar_t* title, const wchar_t* filter, int initFilter, const wchar_t* initDir, bool noChangeDir, HWND parentWnd, int openMode)
{
	std::wstring fileName;
	WCHAR szFile[MAX_PATH] = { 0 };
	OPENFILENAMEW ofn = { sizeof(ofn) };
	ofn.hwndOwner = parentWnd;
	ofn.lpstrTitle = title;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = initFilter;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrInitialDir = initDir;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	if (noChangeDir) ofn.Flags |= OFN_NOCHANGEDIR;
	if (openMode == 1) ofn.Flags |= OFN_OVERWRITEPROMPT;
	if (GetOpenFileNameW(&ofn))
	{
		fileName = szFile;
	}
	return fileName;
}
EXTERN_C void Fn_Open_File_Dialog_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto title = elibstl::args_to_wsdata(pArgInf, 0), filter = elibstl::args_to_wsdata(pArgInf, 1), initDir = elibstl::args_to_wsdata(pArgInf, 3);
	int initFilter = elibstl::args_to_data<int>(pArgInf, 2).value_or(0), openMode = elibstl::args_to_data<int>(pArgInf, 6).value_or(0);
	bool noChangeDir = elibstl::args_to_data<BOOL>(pArgInf, 4).value_or(false);
	HWND parentWnd = reinterpret_cast<HWND> (elibstl::args_to_data<INT>(pArgInf, 5).value_or(0));
	pRetData->m_pBin = elibstl::clone_textw(OpenFileDialogW(std::wstring(title).c_str(), std::wstring(filter).data(), initFilter, std::wstring(initDir).data(), noChangeDir, parentWnd, openMode));
}

FucInfo e_Open_File_Dialog_W = { {
		/*ccname*/  ("文件选择夹W"),
		/*egname*/  (""),
		/*explain*/ ("显示一个文件打开对话框，允许用户选择或输入所需要打开的已存在文件，或保存文件，返回用户所选择或输入后的结果文本。如果用户未输入或按“取消”按钮退出，则返回一个空文本"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_Open_File_Dialog_W ,"Fn_Open_File_Dialog_W" };