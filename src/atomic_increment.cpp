#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "��������ֵ",
		/*explain*/ ("������ԭ�Ӳ�����ֵ��ͬ�ڶ���+1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	}
};


EXTERN_C void Fn_atomic_increment(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = InterlockedIncrement(reinterpret_cast<long*>(pArgInf->m_pInt));
}

FucInfo atomic_increment = { {
		/*ccname*/  ("ԭ�ӵ���"),
		/*egname*/  (""),
		/*explain*/ ("���ؾ�ֵ,���������֤���ڶ��̻߳����¸ò�����ԭ�ӵģ������ᱻ�����̸߳���,�����԰�ȫ,�߳���ʹ��ԭ�Ӳ������Բ��üӻ����塣�����̲߳���ȫ�ֱ���ʱʹ�ã���ͬ��a=a+1"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_atomic_increment ,"Fn_atomic_increment" };
