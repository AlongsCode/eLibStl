#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"目的内存空间指针",
		R"(指向所欲复制到的目的内存空间地址指针,必须确保从该指针地址
开始的尺寸为"欲复制数据尺寸"的内存空间可写.)",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	},
	{
		"来源内存空间指针",
		R"(指向所欲复制来源数据的内存空间地址指针,必须确保从该指针地址
开始的尺寸为"欲复制数据尺寸"的内存空间可读.)",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	},
	{
		"欲复制数据尺寸",
		R"(提供所欲复制来源数据的尺寸,必须大于等于0.)",
		0,
		0,
		SDT_INT,
		0,
		ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_e_memmove(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf[0].m_int < 0) { put_errmsg(L"您传入了一个负数指针?!"); return; }
	if (pArgInf[1].m_int < 0) { put_errmsg(L"您传入了一个负数指针?!"); return; }
	if (pArgInf[2].m_int < 0) { put_errmsg(L"提供所欲复制来源数据的尺寸,必须大于等于0!"); return; }
	memmove(reinterpret_cast<void*>(pArgInf[0].m_int), reinterpret_cast<void*>(pArgInf[1].m_int), pArgInf[2].m_int);
}

FucInfo Fn_memmove = { {
		/*ccname*/  ("内存移动"),
		/*egname*/  ("memmove"),
		/*explain*/ (R"(将一段所指定数据复制到指针所指向的内存空间.
与"内存复制"方法不同的是: 复制的来源和目的空间地址可以相互重叠.)"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Args),
		/*arg lp*/  Args,
	} ,Fn_e_memmove ,"Fn_e_memmove" };
