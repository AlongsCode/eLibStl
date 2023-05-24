#include"ElibHelp.h"
#include <random>
#undef max
static ARG_INFO Args[] =
{
	{
		/*name*/    "欲判断的值",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_Prime(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int x = pArgInf->m_int;
	if (x < 2) {
		// 小于 2 的数都不是素数
		pRetData->m_bool = false;
		return;
	}
	if (x == 2 || x == 3) {
		// 2 和 3 是素数
		pRetData->m_bool = true;
		return;
	}
	if (x % 2 == 0 || x % 3 == 0) {
		// 如果能够被 2 或 3 整除，则不是素数
		pRetData->m_bool = false;
		return;
	}
	// 从 5 开始枚举到 sqrt(x)，如果 x 能够被枚举到的数整除，则不是素数
	for (unsigned long long i = 5; i * i <= x; i += 6) {
		if (x % i == 0 || x % (i + 2) == 0) {
			pRetData->m_bool = false;
			return;
		}
	}
	// 如果没有被整除，则是素数
	pRetData->m_bool = true;
}

FucInfo prime = { {
		/*ccname*/  ("是否素数"),
		/*egname*/  (""),
		/*explain*/ ("判断是否为素数"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_Prime ,"Fn_Prime" };
