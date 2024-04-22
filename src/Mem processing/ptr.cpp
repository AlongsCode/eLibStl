#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"Ŀ���ڴ�ռ�ָ��",
		R"(ָ���������Ƶ���Ŀ���ڴ�ռ��ַָ��,����ȷ���Ӹ�ָ���ַ
��ʼ�ĳߴ�Ϊ"���������ݳߴ�"���ڴ�ռ��д.)",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	},
	{
		"��Դ�ڴ�ռ�ָ��",
		R"(ָ������������Դ���ݵ��ڴ�ռ��ַָ��,����ȷ���Ӹ�ָ���ַ
��ʼ�ĳߴ�Ϊ"���������ݳߴ�"���ڴ�ռ�ɶ�.)",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	},
	{
		"���������ݳߴ�",
		R"(�ṩ����������Դ���ݵĳߴ�,������ڵ���0.)",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_e_memmove(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf[0].m_int < 0) { put_errmsg(L"��������һ������ָ��?!"); return; }
	if (pArgInf[1].m_int < 0) { put_errmsg(L"��������һ������ָ��?!"); return; }
	if (pArgInf[2].m_int < 0) { put_errmsg(L"�ṩ����������Դ���ݵĳߴ�,������ڵ���0!"); return; }
	memmove(reinterpret_cast<void*>(pArgInf[0].m_int), reinterpret_cast<void*>(pArgInf[1].m_int), pArgInf[2].m_int);
}

FucInfo Fn_memmove = { {
		/*ccname*/  ("�ڴ��ƶ�"),
		/*egname*/  ("memmove"),
		/*explain*/ (R"(��һ����ָ�����ݸ��Ƶ�ָ����ָ����ڴ�ռ�.
��"�ڴ渴��"������ͬ����: ���Ƶ���Դ��Ŀ�Ŀռ��ַ�����໥�ص�.)"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Args),
		/*arg lp*/  Args,
	} ,Fn_e_memmove ,"Fn_e_memmove" };
