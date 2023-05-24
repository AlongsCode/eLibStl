#include"ElibHelp.h"

EXTERN_C void Fn_to_string(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf->m_dtDataType == DATA_TYPE::SDT_BIN) {
		pRetData->m_pBin = pArgInf->m_pBin;
		return;
	}
	pRetData->m_pBin = elibstl::clone_textw(elibstl::arg_to_wstring(*pArgInf)), static_cast<bool>(elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE));
}



static ARG_INFO Args[] =
{
	{
		/*name*/    "��ת��������",
		/*explain*/ ("��ת��������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA,
	},{
		/*name*/    "�Ƿ����������",
		/*explain*/ ("Ĭ�ϰ���������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

FucInfo   eto_wstring = { {
		/*ccname*/  ("���ı�W"),
		/*egname*/  ("to_wstring"),
		/*explain*/ ("ת��ָ������Ϊ�ı���"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} , Fn_to_string ,"Fn_to_string" };

