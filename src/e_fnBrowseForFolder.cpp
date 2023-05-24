#include"ElibHelp.h"
#include <shlobj.h>
static ARG_INFO Args[] =
{
	{"标题", "本参数提供显示在对话框上部的标题文本", 0, 0, DATA_TYPE::SDT_TEXT, 0, NULL},
	{ "是否包含文件", "本参数指定是否在浏览框中同时列出文件名。如果被省略，默认值为假", 0, 0, DATA_TYPE::SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY },
	{ "父窗口", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY },
};
static char* BrowseForFolder(const std::string_view& Title, BOOL IsDisplayFile, HWND hWndParent) {
	BROWSEINFOA bi = { 0 };
	CHAR pszPath[MAX_PATH];
	bi.pszDisplayName = pszPath;
	bi.lpszTitle = Title.data();
	bi.ulFlags = BIF_EDITBOX;
	char* ret = nullptr;
	if (IsDisplayFile)//是否显示文件
	{
		bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
	}
	HWND hWnd = IsWindow(hWndParent) != 0 ? hWndParent : GetActiveWindow();//父窗口是否有效
	bi.hwndOwner = IsWindow(hWnd) != 0 ? hWnd : nullptr;//取当前进程活动窗口
	if (LPITEMIDLIST pil = SHBrowseForFolderA(&bi))
	{
		if (SHGetPathFromIDListA(pil, pszPath)) {
			ret = elibstl::clone_text(pszPath);
		}
		IMalloc* ppMalloc;
		if (SHGetMalloc(&ppMalloc) >= 0)
		{
			ppMalloc->Free(pil);
			ppMalloc->Release();
		}
	}
	return ret;
}

EXTERN_C void Fn_BrowseForFolder_A(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto IsDisplayFile = elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(0);
	auto hWndP = reinterpret_cast<HWND>(elibstl::args_to_data<INT>(pArgInf, 2).value_or(0));
	pRetData->m_pText = BrowseForFolder(elibstl::args_to_sdata(pArgInf, 0), IsDisplayFile, hWndP);

}




static ARG_INFO WArgs[] =
{
	{"标题", "本参数提供显示在对话框上部的标题文本", 0, 0, DATA_TYPE::SDT_BIN, 0, NULL},
	{ "是否包含文件", "本参数指定是否在浏览框中同时列出文件名。如果被省略，默认值为假", 0, 0, DATA_TYPE::SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY },
	{ "父窗口", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY },
};
static unsigned char* BrowseForFolderW(const std::wstring_view& Title, BOOL IsDisplayFile, HWND hWndParent) {
	BROWSEINFOW bi = { 0 };
	WCHAR pszPath[MAX_PATH];
	bi.pszDisplayName = pszPath;
	bi.lpszTitle = Title.data();
	bi.ulFlags = BIF_EDITBOX;
	unsigned char* ret = nullptr;
	if (IsDisplayFile)//是否显示文件
	{
		bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
	}
	HWND hWnd = IsWindow(hWndParent) != 0 ? hWndParent : GetActiveWindow();//父窗口是否有效
	bi.hwndOwner = IsWindow(hWnd) != 0 ? hWnd : nullptr;//取当前进程活动窗口
	if (LPITEMIDLIST pil = SHBrowseForFolderW(&bi))
	{
		if (SHGetPathFromIDListW(pil, pszPath)) {
			ret = elibstl::clone_textw(pszPath);
		}
		IMalloc* ppMalloc;
		if (SHGetMalloc(&ppMalloc) >= 0)
		{
			ppMalloc->Free(pil);
			ppMalloc->Release();
		}
	}
	return ret;
}

EXTERN_C void Fn_BrowseForFolder_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto IsDisplayFile = elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(0);
	auto hWndP = reinterpret_cast<HWND>(elibstl::args_to_data<INT>(pArgInf, 2).value_or(0));
	pRetData->m_pBin = BrowseForFolderW(std::wstring(elibstl::args_to_wsdata(pArgInf, 0)), IsDisplayFile, hWndP);

}

FucInfo e_BrowseForFolder_A = { {
		/*ccname*/  ("浏览文件对话框"),
		/*egname*/  (""),
		/*explain*/ ("打开一个对话框，浏览系统中存在的所有文件夹，返回被选定文件夹的路径名，如果未选中任何文件夹，则返回空文本"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_TEXT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_BrowseForFolder_A ,"Fn_BrowseForFolder_A" };


FucInfo e_BrowseForFolder_W = { {
		/*ccname*/  ("浏览文件对话框W"),
		/*egname*/  (""),
		/*explain*/ ("打开一个对话框，浏览系统中存在的所有文件夹，返回被选定文件夹的路径名，如果未选中任何文件夹，则返回空文本"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(WArgs) / sizeof(WArgs[0]),
		/*arg lp*/  WArgs,
	} ,Fn_BrowseForFolder_W ,"Fn_BrowseForFolder_W" };