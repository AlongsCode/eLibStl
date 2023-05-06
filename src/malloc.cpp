#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
			"申请长度",
			"",
			0,
			0,
			SDT_INT,
			0,
			NULL,
		} ,{
			"是否初始化为零",
			"",
			0,
			0,
			SDT_BOOL,
			0,
			AS_DEFAULT_VALUE_IS_EMPTY,
		}

};
EXTERN_C void Fn_e_malloc(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = 0;
	auto p = std::malloc(pArgInf[0].m_int);
	if (!p)
	{
		return;
	}
	if (pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_bool)
	{
		std::memset(p, 0, pArgInf[0].m_int);
	}
	pRetData->m_int = reinterpret_cast<size_t>(p);
}

FucInfo e_malloc = { {
		/*ccname*/  ("内存申请"),
		/*egname*/  ("malloc"),
		/*explain*/ ("此代码申请内存不经过易语言ide的引用计数,完全由程序员管理,需自行释放。"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_e_malloc ,"Fn_e_malloc" };
