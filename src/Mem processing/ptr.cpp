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
		ArgMark::AS_NONE,
	},
	{
		"数据类型",
		"通过自定义数据类型实现的代码",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	}
};
EXTERN_C void Fn_e_ptrToData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_int < 0) { put_errmsg(L"您传入了一个负数指针?!"); return; }
	if (auto& p = reinterpret_cast<void*&>(pArgInf->m_int);  p)
	{
		pRetData->m_pCompoundData = p;
		pRetData->m_dtDataType = static_cast<DATA_TYPE>(pArgInf[1].m_int);
	}
}

FucInfo Fn_ptrToData = { {
		/*ccname*/  ("指针到自定义数据类型"),
		/*egname*/  ("ptrToData"),
		/*explain*/ ("以拷贝的方式传递变量。请确保数据有效"),
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
