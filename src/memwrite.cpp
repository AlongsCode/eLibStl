#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"��д���ڴ������",
		"",
		0,
		0,
		DATA_TYPE::_SDT_ALL,
		0,
		NULL,
	},
	{
		"�ڴ�����ָ��",
		"",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		NULL,
	},
	{
		"�ڴ�����ָ��",
		"",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		AS_DEFAULT_VALUE_IS_EMPTY,
	}

};

EXTERN_C void Fn_e_WriteMem(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	unsigned char* pData = nullptr;
	size_t dwLen;
	if (pArgInf[0].is_dt_flag())//������
	{
		pArgInf[0].remove_dt_flag(); //ȥ�������־
		if (pArgInf[0].m_dtDataType == DATA_TYPE::SDT_BYTE)//�ֽ�����
		{
			pData = elibstl::get_array_element_inf<unsigned char*>(pArgInf[0].m_pAryData, &dwLen);
			if (dwLen == 0)
				return;
		}
		else
			return;
	}
	else
	{
		if (pArgInf[0].m_dtDataType == DATA_TYPE::SDT_TEXT)
		{
			if (pArgInf[0].m_pText == NULL)
				return;

			dwLen = strlen(pArgInf[0].m_pText);
			if (dwLen == 0)
				return;
			dwLen++;
			pData = (LPBYTE)pArgInf[0].m_pText;

		}
		else if (pArgInf[0].m_dtDataType == DATA_TYPE::SDT_BIN)
		{
			if (pArgInf[0].m_pBin == NULL)
				return;

			LPINT p = (LPINT)pArgInf[0].m_pBin;
			dwLen = p[1];
			p += 2;
			pData = (LPBYTE)p;


		}
		else {

			dwLen = elibstl::get_esys_datatype_size(pArgInf[0].m_dtDataType);
			if (dwLen == 0)//��֧�ֵ���������
				return;
			pData = (unsigned char*)&pArgInf[0].m_int;
		}

	}
	if (pArgInf[2].m_dtDataType != DATA_TYPE::_SDT_NULL && pArgInf[2].m_int > 0)
	{
		if (static_cast<size_t>(pArgInf[2].m_int) < dwLen)
			dwLen = pArgInf[2].m_int;
	}
	memcpy(pArgInf[1].m_pCompoundData, pData, dwLen);
}

FucInfo e_WriteMem = { {
		/*ccname*/  ("д���ڴ�"),
		/*egname*/  ("writemem"),
		/*explain*/ ("�˴��������ڴ治����������ide�����ü���,��ȫ�ɳ���Ա����,�������ͷš�"),
		/*category*/15,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args) / sizeof(Args[0]),
		/*arg lp*/  Args,
	} ,Fn_e_WriteMem ,"Fn_e_WriteMem" };
