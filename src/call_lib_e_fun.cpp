#include"ElibHelp.h"


static ARG_INFO Args[] =
{
		{
			"�׿�",
			"����:krnln.fne��krnln.fnr��lib\\krnln.fne��,��δ�ҵ����Զ�Ѱ��",
			0,
			0,
			DATA_TYPE::SDT_TEXT,
			0,
			NULL,
		},
		{
				"������",
				"������õ��׿⺯�����벻Ҫ���ð����ο��ͱ����ĺ���",
				0,
				0,
				DATA_TYPE::_SDT_ALL,
				0,
				NULL,
		},	{
				"����ֵ",
				"��ȷ��ʹ�ù淶",
				0,
				0,
				DATA_TYPE::_SDT_ALL,
				0,
				AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY,
		},
		{
			"����",
			"������ֵ����Ϊ�������뱻�����ӳ��������Ӧ�ӳ���û�в�������ʡ�Ա������������Ӧ�ӳ����ж�����������ظ��ṩ��������������ṩ׼ȷ�Ĳ������ͺͲ�������������������Ԥ֪��",
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
		/*ccname*/  ("�����׿⺯��"),
		/*egname*/  ("elib_call"),
		/*explain*/ ("��̬����������֧�ֿ⺯��"),
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

