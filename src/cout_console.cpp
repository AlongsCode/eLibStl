#include"ElibHelp.h"
#include<iostream>
#pragma warning(disable:4018)
static ARG_INFO Args[] =
{
	{
		/*name*/    "�������",
		/*explain*/ ("�������ṩ��������������豸������Ϊ���³���ֵ֮һ�� 1��#��׼����豸�� 2��#��׼�����豸�����ʡ�Ա�������Ĭ��Ϊ��#��׼����豸��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},{
		/*name*/    "����ı�",
		/*explain*/ ("������ֻ��Ϊunicode�ֽڼ����������Ϊ�ı��Ұ������У����ڸ���֮���ûس��� (�����ַ�W (13)��)�����з� (�����ַ�W (10)��) ��س����з������ (�������ַ�W (13) + �ַ�W (10)"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_coutW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto direction = elibstl::args_to_data<INT>(pArgInf, 0);
	int directionin = 1;
	if (direction.has_value() && direction.value() == 2)
	{
		directionin = 2;
	}

	// ��������ǿ��ַ���ʹ�� std::wcout ���
	for (size_t i = 1; i < nArgCount; i++)
	{
		std::wstring_view text = elibstl::args_to_wsdata(pArgInf, i);
		if (directionin == 2) {
			std::wcerr << std::wstring(text);
		}
		else {
			std::wcout << std::wstring(text);
		}
	}
}

FucInfo cout_w = { {
		/*ccname*/  ("��׼���W"),
		/*egname*/  ("coutW"),
		/*explain*/ (""),
		/*category*/5,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/    DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  Args,
	} ,Fn_coutW ,"Fn_coutW" };
