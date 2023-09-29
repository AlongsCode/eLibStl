#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"内存指针",
		"",
		0,
		0,
		SDT_INT,
		0,
		AS_RECEIVE_VAR,
	}
};
EXTERN_C void Fn_e_free(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (*pArgInf->m_pInt < 0) { put_errmsg(L"您正在释放一个负数指针?!"); return; }
	if (auto& p = reinterpret_cast<void*&>(*pArgInf->m_pInt);  p)
	{
		try {
			// 尝试释放内存
			operator delete(p);
		}
		catch (...) {
			put_errmsg(L"内存释放失败!");
			return;
		}
		p = nullptr;
	}
}

FucInfo e_free = { {
		/*ccname*/  ("内存释放"),
		/*egname*/  ("free"),
		/*explain*/ ("释放所申请的内存。"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_e_free ,"Fn_e_free" };
