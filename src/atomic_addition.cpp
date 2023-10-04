#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		/*name*/    "欲操作的变量",
		/*explain*/ ("欲进行原子操作的值等同于对其运算"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_RECEIVE_VAR,
	},
	{
		/*name*/    "欲操作的值",
		/*explain*/ ("欲对变量进行原子运算的值,可为正负"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_atomic_addition(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = InterlockedExchangeAdd(reinterpret_cast<long*>(pArgInf->m_pInt), pArgInf[1].m_int);
}

FucInfo atomic_addition = { {
		/*ccname*/  ("原子运算"),
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
	} ,Fn_atomic_addition ,"Fn_atomic_addition" };
