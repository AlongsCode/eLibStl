#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "��������ֵ",
		/*explain*/ ("������ԭ�Ӳ�����ֵ��ͬ�ڶ���-1"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	}
};


EXTERN_C void Fn_atomic_decrement(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = InterlockedDecrement(reinterpret_cast<long*>(pArgInf->m_pInt));
}

FucInfo atomic_decrement = { {
		/*ccname*/  ("ԭ�ӵݼ�"),
		/*egname*/  (""),
		/*explain*/ ("���ؾ�ֵ,���������֤���ڶ��̻߳����¸ò�����ԭ�ӵģ������ᱻ�����̸߳���,�����԰�ȫ,�߳���ʹ��ԭ�Ӳ������Բ��üӻ����塣�����̲߳���ȫ�ֱ���ʱʹ�ã���ͬ��a=a-1"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_atomic_decrement ,"Fn_atomic_decrement" };
