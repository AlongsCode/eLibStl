#include"ElibHelp.h"

static bool remove_dir(const std::wstring& path) {
	if (path.empty())
		return FALSE;
	size_t nLen = path.size();
	if (nLen == 0)//��ֹɾ����ǰĿ¼�ĸ�Ŀ¼"\*"
		return FALSE;
	if (nLen == 1 && path == L"\\")//��ֹɾ����ǰĿ¼�ĸ�Ŀ¼"\*"
		return FALSE;
	return RemoveDirectoryW(path.c_str());//ɾ����Ŀ¼
}

static ARG_INFO Args[] =
{
	{
		/*name*/    "Ŀ¼·��",
		/*explain*/ ("��ɾ����·��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
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
		/*ccname*/  ("ɾ��Ŀ¼W"),
		/*egname*/  ("remove_dirW"),
		/*explain*/ ("ɾ��ָ��Ŀ¼���ɹ������棬ʧ�ܷ��ؼ١�"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_remove_dir_W ,"Fn_remove_dir_W" };

