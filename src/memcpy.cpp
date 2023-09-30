


#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"目标内存",
		"",
		0,
		0,
		SDT_INT,
		0,
		NULL,
	},
	{
		"待复制的内存",
		"",
		0,
		0,
		SDT_INT,
		0,
		NULL,
	},
	{
		"内存长度",
		"请确保内存安全",
		0,
		0,
		SDT_INT,
		0,
		NULL,
	},/*{
		"是否报错?",
		"对于不安全的内存操作进行报错，之后退出程序.否则出错后会安全处理后导致函数无效!建议在调试时为真方便调试和定位所处位置,编译后为假!",
		0,
		0,
		SDT_BOOL,
		0,
		AS_HAS_DEFAULT_VALUE,
	}*/

};

EXTERN_C void Fn_e_memcpy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
	BOOL dbg = elibstl::is_debug();

	// 检查参数是否有效
	for (int i = 0; i < 3; ++i) {
		if (pArgInf[i].m_int <= 0) {
			if (!dbg) {
				return;
			}
			const wchar_t* errorMsg = nullptr;
			switch (i) {
			case 0:
				errorMsg = L"你想要将内存复制到一个负指针/空指针吗?!";
				break;
			case 1:
				errorMsg = L"你想要将负指针/空指针的内存复制?!";
				break;
			case 2:
				errorMsg = L"您正在复制负长度/零长度的内存?!";
				break;
			}
			put_errmsg(errorMsg);
			return;
		}
	}
	
	auto destination = elibstl::args_to_data_noop<char*>(pArgInf, 0);
	auto source = elibstl::args_to_data_noop<char*>(pArgInf, 1);
	auto count = elibstl::args_to_data_noop<size_t>(pArgInf, 2);

	std::copy(source, source + count, destination);
}
FucInfo e_memcpy = { {
		/*ccname*/  ("内存复制"),
		/*egname*/  ("memcpy"),
		/*explain*/ ("复制内存"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  Args,
	} ,Fn_e_memcpy ,"Fn_e_memcpy" };
