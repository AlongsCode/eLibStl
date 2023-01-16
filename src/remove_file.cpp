#include"ElibHelp.h"



static ARG_INFO Args[] =
{
	{
		/*name*/    "文件路径",
		/*explain*/ ("欲删除的文件的路径"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_remove_file_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto filename = elibkrnln::args_to_wsdata(pArgInf, 0);
	pRetData->m_bool = DeleteFileW(std::wstring(filename).c_str());
}

FucInfo remove_file_W = { {
		/*ccname*/  ("删除文件W"),
		/*egname*/  ("remove_fileW"),
		/*explain*/ ("删除指定文件。成功返回真，失败返回假。"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_remove_file_W ,"Fn_remove_file_W" };

