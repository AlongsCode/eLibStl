#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"
/*捕获*/
typedef void (*ExecuteFunction)(void);
void catchException(const char* exceptionValue, ExecuteFunction executeFunction) {
	/*try {
	* 使用什么机制可以捕获呢?
		throw exceptionValue;
	}*/
	/*catch ( exception) {}*/

}
/*抛出*/
void throwException(const char* exceptionValue) {
	/*易里如何让此消息一直延栈向上传递*/
}


/*.版本 2
.支持库 libstl

.子程序 _按钮1_被单击

抛出异常 (“a”)

捕获异常 (“a”, &测试)


.子程序 测试


*/

static ARG_INFO Args[] =
{
		{
		/*name*/	"异常值",
		/*explain*/	"异常标识",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
			},
				{
					/*name*/	"回调函数",
					/*explain*/	"必须为空参无返回值函数",
					/*bmp inx*/	0,
					/*bmp num*/	0,
					/*type*/	DATA_TYPE::SDT_SUB_PTR,
					/*default*/	0,
					/*state*/	0,
						},
};



EXTERN_C void efn_catch_ception(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto str = elibstl::args_to_sdata(pArgInf, 0);
	catchException(str.empty() ? "未定义异常值" : str.data(), reinterpret_cast<ExecuteFunction>(pArgInf[1].m_dwSubCodeAdr));

}

FucInfo g_catch_ception = { {
		/*ccname*/  ("捕获异常"),
		/*egname*/  ("catch_ception"),
		/*explain*/ ("抛出指定异常"),
		/*category*/11,
		/*state*/     NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,efn_catch_ception ,"efn_catch_ception" };




EXTERN_C void efn_throw_ception(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto str = elibstl::args_to_sdata(pArgInf, 0);
	throwException(str.empty() ? "未定义异常值" : str.data());

}

FucInfo g_throw_ception = { {
		/*ccname*/  ("抛出异常"),
		/*egname*/  ("throw_ception"),
		/*explain*/ ("抛出指定异常"),
		/*category*/11,
		/*state*/     NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,efn_throw_ception ,"efn_throw_ception" };