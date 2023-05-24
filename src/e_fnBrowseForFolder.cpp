#include"ElibHelp.h"
#include <shlobj.h>
static ARG_INFO Args[] =
{
	{"����", "�������ṩ��ʾ�ڶԻ����ϲ��ı����ı�", 0, 0, DATA_TYPE::SDT_TEXT, 0, NULL},
	{ "�Ƿ�����ļ�", "������ָ���Ƿ����������ͬʱ�г��ļ����������ʡ�ԣ�Ĭ��ֵΪ��", 0, 0, DATA_TYPE::SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY },
	{ "������", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY },
};
static char* BrowseForFolder(const std::string_view& Title, BOOL IsDisplayFile, HWND hWndParent) {
	BROWSEINFOA bi = { 0 };
	CHAR pszPath[MAX_PATH];
	bi.pszDisplayName = pszPath;
	bi.lpszTitle = Title.data();
	bi.ulFlags = BIF_EDITBOX;
	char* ret = nullptr;
	if (IsDisplayFile)//�Ƿ���ʾ�ļ�
	{
		bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
	}
	HWND hWnd = IsWindow(hWndParent) != 0 ? hWndParent : GetActiveWindow();//�������Ƿ���Ч
	bi.hwndOwner = IsWindow(hWnd) != 0 ? hWnd : nullptr;//ȡ��ǰ���̻����
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
	{"����", "�������ṩ��ʾ�ڶԻ����ϲ��ı����ı�", 0, 0, DATA_TYPE::SDT_BIN, 0, NULL},
	{ "�Ƿ�����ļ�", "������ָ���Ƿ����������ͬʱ�г��ļ����������ʡ�ԣ�Ĭ��ֵΪ��", 0, 0, DATA_TYPE::SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY },
	{ "������", "", 0, 0, DATA_TYPE::SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY },
};
static unsigned char* BrowseForFolderW(const std::wstring_view& Title, BOOL IsDisplayFile, HWND hWndParent) {
	BROWSEINFOW bi = { 0 };
	WCHAR pszPath[MAX_PATH];
	bi.pszDisplayName = pszPath;
	bi.lpszTitle = Title.data();
	bi.ulFlags = BIF_EDITBOX;
	unsigned char* ret = nullptr;
	if (IsDisplayFile)//�Ƿ���ʾ�ļ�
	{
		bi.ulFlags |= BIF_BROWSEINCLUDEFILES;
	}
	HWND hWnd = IsWindow(hWndParent) != 0 ? hWndParent : GetActiveWindow();//�������Ƿ���Ч
	bi.hwndOwner = IsWindow(hWnd) != 0 ? hWnd : nullptr;//ȡ��ǰ���̻����
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
		/*ccname*/  ("����ļ��Ի���"),
		/*egname*/  (""),
		/*explain*/ ("��һ���Ի������ϵͳ�д��ڵ������ļ��У����ر�ѡ���ļ��е�·���������δѡ���κ��ļ��У��򷵻ؿ��ı�"),
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
		/*ccname*/  ("����ļ��Ի���W"),
		/*egname*/  (""),
		/*explain*/ ("��һ���Ի������ϵͳ�д��ڵ������ļ��У����ر�ѡ���ļ��е�·���������δѡ���κ��ļ��У��򷵻ؿ��ı�"),
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