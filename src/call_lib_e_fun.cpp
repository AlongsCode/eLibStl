#include"ElibHelp.h"


static ARG_INFO Args[] =
{
		{
			"易库",
			"例如:krnln.fne、krnln.fnr、lib\\krnln.fne等,如未找到则自动寻找",
			0,
			0,
			DATA_TYPE::SDT_TEXT,
			0,
			NULL,
		},
		{
				"函数名",
				"所需调用的易库函数、请不要调用包含参考型变量的函数",
				0,
				0,
				DATA_TYPE::_SDT_ALL,
				0,
				NULL,
		},	{
				"返回值",
				"请确保使用规范",
				0,
				0,
				DATA_TYPE::_SDT_ALL,
				0,
				AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
		},
		{
			"参数",
			"本参数值将作为参数传入被调用子程序。如果相应子程序没有参数，请省略本参数；如果相应子程序有多个参数，请重复提供本参数。请务必提供准确的参数类型和参数个数，否则后果不可预知。",
			0,
			0,
			DATA_TYPE::_SDT_ALL,
			0,
			AS_DEFAULT_VALUE_IS_EMPTY,
		}
};



EXTERN_C void Fn_e_eLibCallEfun(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {

	pRetData->m_bool = elibstl::CallElibFunc(elibstl::args_to_sdata(pArgInf, 0).data(), elibstl::args_to_sdata(pArgInf, 1).data(), pArgInf + 2, nArgCount - 3, pArgInf + 3);
}
FucInfo e_eLibCallEfun = { {
		/*ccname*/  ("调用易库函数"),
		/*egname*/  ("elib_call"),
		/*explain*/ ("动态调用易语言支持库函数"),
		/*category*/12,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &Args[0],
	} ,Fn_e_eLibCallEfun ,"Fn_e_eLibCallEfun" };

