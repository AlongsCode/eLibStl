#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"
/*����*/
typedef void (*ExecuteFunction)(void);
void catchException(const char* exceptionValue, ExecuteFunction executeFunction) {
	/*try {
	* ʹ��ʲô���ƿ��Բ�����?
		throw exceptionValue;
	}*/
	/*catch ( exception) {}*/

}
/*�׳�*/
void throwException(const char* exceptionValue) {
	/*��������ô���Ϣһֱ��ջ���ϴ���*/
}


/*.�汾 2
.֧�ֿ� libstl

.�ӳ��� _��ť1_������

�׳��쳣 (��a��)

�����쳣 (��a��, &����)


.�ӳ��� ����


*/

static ARG_INFO Args[] =
{
		{
		/*name*/	"�쳣ֵ",
		/*explain*/	"�쳣��ʶ",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_TEXT,
		/*default*/	0,
		/*state*/	0,
			},
				{
					/*name*/	"�ص�����",
					/*explain*/	"����Ϊ�ղ��޷���ֵ����",
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
	catchException(str.empty() ? "δ�����쳣ֵ" : str.data(), reinterpret_cast<ExecuteFunction>(pArgInf[1].m_dwSubCodeAdr));

}

FucInfo g_catch_ception = { {
		/*ccname*/  ("�����쳣"),
		/*egname*/  ("catch_ception"),
		/*explain*/ ("�׳�ָ���쳣"),
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
	throwException(str.empty() ? "δ�����쳣ֵ" : str.data());

}

FucInfo g_throw_ception = { {
		/*ccname*/  ("�׳��쳣"),
		/*egname*/  ("throw_ception"),
		/*explain*/ ("�׳�ָ���쳣"),
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