#include"ElibHelp.h"



static ARG_INFO Args[] =
{
	{
		/*name*/    "�ļ�·��",
		/*explain*/ ("��ɾ�����ļ���·��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_remove_file_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto filename = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_bool = DeleteFileW(std::wstring(filename).c_str());
}

FucInfo remove_file_W = { {
		/*ccname*/  ("ɾ���ļ�W"),
		/*egname*/  ("remove_fileW"),
		/*explain*/ ("ɾ��ָ���ļ����ɹ������棬ʧ�ܷ��ؼ١�"),
		/*category*/4,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_remove_file_W ,"Fn_remove_file_W" };

