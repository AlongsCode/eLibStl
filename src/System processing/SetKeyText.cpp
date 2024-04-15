#include"ElibHelp.h"
namespace {
	static ARG_INFO Arg[] =
	{
		  { "�����ļ���", "ָ�������ļ������ƣ�ͨ����.ini��Ϊ�ļ�����׺��",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "������", "������д�������������ڵ����ơ�",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "����������", "����ֵָ����д��������������е����ơ��������ֵ��ʡ�ԣ���ɾ��ָ���ڼ����µ����������",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY },
		  { "��д��ֵ", "����ֵָ����д�뵽ָ���������е��ı����������ֵ��ʡ�ԣ���ɾ����ָ�������",0 , 0,  _SDT_ALL, NULL,  ArgMark::AS_DEFAULT_VALUE_IS_EMPTY },
	};
}

EXTERN_C void fn_SetKeyTextW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool= WritePrivateProfileStringW(elibstl::arg_to_wstring(pArgInf, 1).data(), elibstl::arg_to_wstring(pArgInf, 2).data(), elibstl::arg_to_wstring(pArgInf, 3).data(), elibstl::arg_to_wstring(pArgInf, 0).data());
}


FucInfo Fn_SetKeyTextW = { {
		/*ccname*/  ("д������W"),
		/*egname*/  ("SetKeyTextW"),
		/*explain*/ (" ��ָ���ı�����д��ָ���������л���ɾ��ָ�����������ڣ����ָ�������ļ������ڣ������Զ��������ɹ������棬ʧ�ܷ��ؼ١�"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Arg),
		/*arg lp*/  Arg,
	} ,fn_SetKeyTextW ,"fn_SetKeyTextW" };








//ϵͳ���� - ��������
/*
	���ø�ʽ�� ���ı��͡� �������� ���ı��� �����ļ������ı��� �����ƣ��ı��� ���������ƣ����ı��� Ĭ���ı��ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
	Ӣ�����ƣ�GetKeyText
	��ȡָ�������ļ���ָ����Ŀ���ı����ݡ�������Ϊ�������
	����<1>������Ϊ�������ļ�����������Ϊ���ı��ͣ�text������ָ�������ļ������ƣ�ͨ����.ini��Ϊ�ļ�����׺��
	����<2>������Ϊ�������ơ�������Ϊ���ı��ͣ�text���������������������������ڵ����ơ�
	����<3>������Ϊ�����������ơ�������Ϊ���ı��ͣ�text����������ֵָ��������������������е����ơ�
	����<4>������Ϊ��Ĭ���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ָ����������ڣ������ش�Ĭ���ı������ָ������������ұ�������ʡ�ԣ������ؿ��ı���
*/
namespace {
	static ARG_INFO Arg2[] =
	{ 
		  { "�����ļ���", "ָ�������ļ������ƣ�ͨ����.ini��Ϊ�ļ�����׺��",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "������", "������д�������������ڵ����ơ�",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "����������", "����ֵָ����д��������������е����ơ��������ֵ��ʡ�ԣ���ɾ��ָ���ڼ����µ����������",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_NONE },
		  { "Ĭ���ı�", "���ָ����������ڣ������ش�Ĭ���ı������ָ������������ұ�������ʡ�ԣ������ؿ��ı���",0 , 0,  _SDT_ALL, NULL, ArgMark::AS_DEFAULT_VALUE_IS_EMPTY },

	};
}
EXTERN_C void fn_GetKeyText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	LPWSTR pBuff = NULL;
	INT nLen = 1024;
	do
	{
		pBuff = new wchar_t[nLen] {};
		INT nRet = GetPrivateProfileStringW(elibstl::arg_to_wstring(pArgInf, 1).data(), elibstl::arg_to_wstring(pArgInf, 2).data(), elibstl::arg_to_wstring(pArgInf, 3).data(), pBuff, nLen, elibstl::arg_to_wstring(pArgInf, 0).data());
		if (nRet < nLen - 1)
			break;
		nLen = nRet + 1024;
		delete[] pBuff;
	} while (1);

	LPBYTE pText = NULL;
	nLen = wcslen(pBuff);
	if (nLen)
	{
		pText = elibstl::clone_textw(pBuff);
	}
	delete[] pBuff;
	pRetData->m_pBin = pText;
}




FucInfo Fn_GetKeyTextW = { {
		/*ccname*/  ("��������W"),
		/*egname*/  ("GetKeyTextW"),
		/*explain*/ ("��ȡָ�������ļ���ָ����Ŀ���ı����ݡ�"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/std::size(Arg2),
		/*arg lp*/  Arg2,
	} ,fn_GetKeyText ,"fn_GetKeyText" };