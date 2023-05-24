#include"ElibHelp.h"
#include <random>
#undef max
static ARG_INFO Args[] =
{
	{
		/*name*/    "��ȡ���������Сֵ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "��ȡ����������ֵ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};


EXTERN_C void Fn_rndEx(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto min = elibstl::args_to_data<INT>(pArgInf, 0), max = elibstl::args_to_data<INT>(pArgInf, 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min.has_value() ? min.value() : 0, max.has_value() ? max.value() : std::numeric_limits<int>::max());
	pRetData->m_int = dis(gen);
}

FucInfo rnd_ex = { {
		/*ccname*/  ("ȡ�����Ex"),
		/*egname*/  (""),
		/*explain*/ ("��ָ��ȡ����������������������"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} ,Fn_rndEx ,"Fn_rndEx" };
