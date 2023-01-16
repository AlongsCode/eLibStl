#include"ElibHelp.h"

static bool remove_dir(const std::wstring& path) {
	if (path.empty())
		return FALSE;
	size_t nLen = path.size();
	if (nLen == 0)//防止删除当前目录的根目录"\*"
		return FALSE;
	if (nLen == 1 && path == L"\\")//防止删除当前目录的根目录"\*"
		return FALSE;
	return RemoveDirectoryW(path.c_str());//删除空目录
}

static ARG_INFO Args[] =
{
	{
		/*name*/    "目录路径",
		/*explain*/ ("欲删除的路径"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_remove_dir_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto filename = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_bool = remove_dir(std::wstring(filename));
}

FucInfo remove_dir_W = { {
		/*ccname*/  ("删除目录W"),
		/*egname*/  ("remove_dirW"),
		/*explain*/ ("删除指定目录。成功返回真，失败返回假。"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_remove_dir_W ,"Fn_remove_dir_W" };

