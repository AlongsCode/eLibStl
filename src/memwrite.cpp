#include"ElibHelp.h"

static ARG_INFO Args[] =
{
	{
		"欲写到内存的数据",
		"",
		0,
		0,
		DATA_TYPE::_SDT_ALL,
		0,
		NULL,
	},
	{
		"内存区域指针",
		"",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		NULL,
	},
	{
		"内存区域指针",
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
	if (pArgInf[0].is_dt_flag())//是数组
	{
		pArgInf[0].remove_dt_flag(); //去除数组标志
		if (pArgInf[0].m_dtDataType == DATA_TYPE::SDT_BYTE)//字节数组
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
			if (dwLen == 0)//不支持的数据类型
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
		/*ccname*/  ("写入内存"),
		/*egname*/  ("writemem"),
		/*explain*/ ("此代码申请内存不经过易语言ide的引用计数,完全由程序员管理,需自行释放。"),
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
