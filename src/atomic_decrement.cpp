#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲操作的值",
		/*explain*/ ("欲进行原子操作的值等同于对其-1"),
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
		/*ccname*/  ("原子递减"),
		/*egname*/  (""),
		/*explain*/ ("返回旧值,这个函数保证了在多线程环境下该操作是原子的，即不会被其它线程干扰,即绝对安全,线程中使用原子操作可以不用加互斥体。对于线程操作全局变量时使用，等同于a=a-1"),
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
