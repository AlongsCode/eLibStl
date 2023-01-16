#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲赋值的变量",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	},
	{
		/*name*/    "值",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_atomic_exchange(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = InterlockedExchange(reinterpret_cast<long*>(pArgInf->m_pInt), pArgInf[1].m_int);
}

FucInfo atomic_exchange = { {
		/*ccname*/  ("原子赋值"),
		/*egname*/  (""),
		/*explain*/ ("返回旧值,这个函数保证了在多线程环境下该操作是原子的，即不会被其它线程干扰,即绝对安全,线程中使用原子操作可以不用加互斥体。对于线程操作全局变量时使用。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_atomic_exchange ,"Fn_atomic_exchange" };
