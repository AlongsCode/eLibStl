#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"�ڴ�ָ��",
		"",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	},
	{
		"��������",
		"ͨ���Զ�����������ʵ�ֵĴ���",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	}
};
EXTERN_C void Fn_e_ptrToData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_int < 0) { put_errmsg(L"��������һ������ָ��?!"); return; }
	if (auto& p = reinterpret_cast<void*&>(pArgInf->m_int);  p)
	{
		pRetData->m_pCompoundData = p;
		pRetData->m_dtDataType = static_cast<DATA_TYPE>(pArgInf[1].m_int);
	}
}

FucInfo Fn_ptrToData = { {
		/*ccname*/  ("ָ�뵽�Զ�����������"),
		/*egname*/  ("ptrToData"),
		/*explain*/ ("�Կ����ķ�ʽ���ݱ�������ȷ��������Ч"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     _SDT_ALL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Args),
		/*arg lp*/  Args,
	} ,Fn_e_ptrToData ,"Fn_e_ptrToData" };
