#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "�������ı���",
		/*explain*/ ("������ԭ�Ӳ�����ֵ��ͬ�ڶ�������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	},
	{
		/*name*/    "��������ֵ",
		/*explain*/ ("���Ա�������ԭ�������ֵ,��Ϊ����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_atomic_addition(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = InterlockedExchangeAdd(reinterpret_cast<long*>(pArgInf->m_pInt), pArgInf[1].m_int);
}

FucInfo atomic_addition = { {
		/*ccname*/  ("ԭ������"),
		/*egname*/  (""),
		/*explain*/ ("���ؾ�ֵ,���������֤���ڶ��̻߳����¸ò�����ԭ�ӵģ������ᱻ�����̸߳���,�����԰�ȫ,�߳���ʹ��ԭ�Ӳ������Բ��üӻ����塣�����̲߳���ȫ�ֱ���ʱʹ�á�"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_atomic_addition ,"Fn_atomic_addition" };
