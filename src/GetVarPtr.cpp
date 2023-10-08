#include"ElibHelp.h"








static ARG_INFO Args[] =
{
		{
			"欲获取其地址的变量",
			"",
			0,
			0,
			_SDT_ALL,
			0,
			ArgMark::AS_RECEIVE_VAR_OR_ARRAY,
		}
};
EXTERN_C void libstl_fn_get_var_ptr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
	*pRetData = *pArgInf;
}

EXTERN_C void libstl_fn_get_var_data_ptr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
	auto primitive_type = pArgInf->ret_type_noflag();
	/*是数组*/
	if (pArgInf->is_dt_flag()) {
		/*不使用绑定,避免性能消耗*/
		auto get_arr_p = [](void* pAryData)->void* {
			if (pAryData == nullptr) return nullptr;
			auto pn_data = static_cast<int*>(pAryData);
			int count = *pn_data++; //获取维数
			size_t nElementCount = 1; //数组元素数量
			for (auto it = pn_data; it != pn_data + count; ++it)
			{
				nElementCount *= *it;
			}
			return reinterpret_cast<void*>(pn_data + count);
			};
		pRetData->m_pAryData = get_arr_p(*pArgInf->m_ppAryData);
	}
	else if (primitive_type == SDT_TEXT)/*常规变量*/
	{
		auto pText = *pArgInf->m_ppText;
		pRetData->m_int = reinterpret_cast<uintptr_t>((pText == nullptr || strlen(pText) == 0) ? nullptr : pText);
	}
	else if (primitive_type == SDT_BIN) {
		auto pData = elibstl::classhelp::eplarg::get_bin(*pArgInf->m_ppBin);
		if (pData.size() > 0)
			pRetData->m_int = reinterpret_cast<uintptr_t>(pData.data());
	}
	else
		*pRetData = *pArgInf;

}
FucInfo Fn_GetVarPtr = { {
		/*ccname*/  ("取变量指针"),
		/*egname*/  ("GetVarPtr"),
		/*explain*/ ("返回指定变量的内存地址（在内联汇编代码中可以在执行本命令后立即检查EAX寄存器获得），如欲修改该地址处内容（尤其是文本型、字节集型或复合数据类型变量），请谨慎操作，否则很可能造成内存垃圾或程序崩溃。本命令为高级命令。"),
		/*category*/12,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,ESTLFNAME(libstl_fn_get_var_ptr) };

FucInfo Fn_GetVarDataPtr = { {
		/*ccname*/  ("取变量数据指针"),
		/*egname*/  ("GetVarDataPtr"),
		/*explain*/ ("取指定变量中数据的内存地址。返回值为0表示没有取到变量地址。对文本型或字节集型变量而言，如果其长度为0，将返回0；对数组变量而言，如果其成员数为0，也将返回0。对于文本型或字节集型变量，返回值为文本数据或字节集数据的地址。其它情况下，本命令与“取变量地址”具有相同的返回值。注意：一旦变量超出其作用域范围，或文本型/字节集型变量被重新赋值，或数组变量被重新赋值，先前取到的变量地址将变成无效地址，再对该地址进行读写操作很有可能导致程序崩溃。本命令为高级命令。"),
		/*category*/12,
		/*state*/   0,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,ESTLFNAME(libstl_fn_get_var_data_ptr) };