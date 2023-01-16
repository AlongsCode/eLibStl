#include <shlobj.h>
#include"ElibHelp.h"

// 获取文件夹路径
/*此参数表示要获取的特殊文件夹的类型。
值为1时表示获取我的文档文件夹路径；
值为2时表示获取我的收藏夹路径；
值为3时表示获取桌面文件夹路径；
值为4时表示获取字体文件夹路径；
值为5时表示获取开始菜单文件夹路径；
值为6时表示获取程序文件夹路径；
值为7时表示获取启动文件夹路径；
值为8时表示获取应用程序数据文件夹路径；
值为9时表示获取Windows文件夹路径；
值为10时表示获取系统文件夹路径；
值为11时表示获取临时文件夹路径。*/
static LPBYTE GetSpecialFolderPath(DWORD Type) {
	wchar_t path[MAX_PATH + 1] = { 0 };
	BOOL IsSucceeded = FALSE;
	if (Type >= 1 && Type <= 8) {
		IsSucceeded = SHGetSpecialFolderPathW(NULL, path, (Type == 1 ? CSIDL_PERSONAL : Type == 2 ? CSIDL_FAVORITES : Type == 3 ? CSIDL_DESKTOPDIRECTORY :
			Type == 4 ? CSIDL_FONTS : Type == 5 ? CSIDL_STARTMENU : Type == 6 ? CSIDL_PROGRAMS : Type == 7 ? CSIDL_STARTUP : CSIDL_APPDATA), FALSE);
	}
	else if (Type == 9) {
		IsSucceeded = (GetWindowsDirectoryW(path, MAX_PATH) > 0);
	}
	else if (Type == 10) {
		IsSucceeded = (GetSystemDirectoryW(path, MAX_PATH) > 0);
	}
	else {
		if (Type != 11) {
			return 0;
		}
		IsSucceeded = (GetTempPathW(MAX_PATH, path) > 0);
	}
	LPBYTE Ret = nullptr;
	if (IsSucceeded) {
		size_t lenth = wcslen(path);
		if (lenth > 0 && path[lenth - 1] != L'\\') {
			path[lenth] = L'\\';
			path[lenth + 1] = L'\0';
		}
		Ret = elibstl::clone_textw(path);
	}
	return Ret;
};

EXTERN_C void shell_get_special_folder_path_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	//参数必不为空
	pRetData->m_pBin = GetSpecialFolderPath(pArgInf->m_int);
}


static ARG_INFO Args[] =
{

	{
		/*name*/    "欲获取目录类型",
		/*explain*/ ("。本参数指定欲获取目录的类型，可以为以下常量值之一： 1: #我的文档;  2: #我的收藏夹;  3: #系统桌面;  4: #系统字体;  5: #开始菜单组;  6: #程序菜单组;  7: #启动菜单组;  8: #程序数据目录;  9: #Windows安装目录;  10: #Windows系统目录;  11: #临时文件目录。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

FucInfo get_special_folder_path_W = { {
		/*ccname*/  ("取特定目录W"),
		/*egname*/  ("GetSpecialFolderPathW"),
		/*explain*/ ("本命令返回指定的Windows系统特定目录，所返回目录名以“\\”符号结束，如失败返回空文本。"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,shell_get_special_folder_path_W ,"shell_get_special_folder_path_W" };