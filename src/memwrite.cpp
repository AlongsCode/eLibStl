//#include"ElibHelp.h"
//
//static ARG_INFO Args[] =
//{
//	{
//			"申请长度",
//			"",
//			0,
//			0,
//			SDT_INT,
//			0,
//			NULL,
//		} ,{
//			"是否初始化为零",
//			"",
//			0,
//			0,
//			SDT_BOOL,
//			0,
//			AS_DEFAULT_VALUE_IS_EMPTY,
//		}
//
//};
//EXTERN_C void Fn_e_malloc(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
//{
//	LPBYTE pData;
//	DWORD dwLen;
//	if ((pArgInf[0].m_dtDataType & DT_IS_ARY) == DT_IS_ARY)//是数组
//	{
//		pArgInf[0].m_dtDataType &= ~DT_IS_ARY; //去除数组标志
//		if (pArgInf[0].m_dtDataType == SDT_BYTE)//字节数组
//		{
//
//			pData = (LPBYTE)elibstl::get_array_count(pArgInf[0].m_pAryData, dwLen);
//			if (dwLen == 0)
//				return;
//		}
//		else
//			return;
//	}
//	else
//	{
//		if (pArgInf[0].m_dtDataType == SDT_TEXT)
//		{
//			if (pArgInf[0].m_pText == NULL)
//				return;
//
//			dwLen = strlen(pArgInf[0].m_pText);
//			if (dwLen == 0)
//				return;
//			dwLen++;
//			pData = (LPBYTE)pArgInf[0].m_pText;
//
//		}
//		else if (pArgInf[0].m_dtDataType == SDT_BIN)
//		{
//			if (pArgInf[0].m_pBin == NULL)
//				return;
//
//			LPINT p = (LPINT)pArgInf[0].m_pBin;
//			dwLen = p[1];
//			p += 2;
//			pData = (LPBYTE)p;
//
//
//		}
//		else {
//
//			dwLen = GetSysDataTypeDataSize(pArgInf[0].m_dtDataType);
//			if (dwLen == 0)//不支持的数据类型
//				return;
//			pData = (LPBYTE)&pArgInf[0].m_int;
//		}
//
//	}
//
//	FucInfo e_malloc = { {
//			/*ccname*/  ("内存申请"),
//			/*egname*/  ("malloc"),
//			/*explain*/ ("此代码申请内存不经过易语言ide的引用计数,完全由程序员管理,需自行释放。"),
//			/*category*/15,
//			/*state*/   NULL,
//			/*ret*/     SDT_INT,
//			/*reserved*/NULL,
//			/*level*/   LVL_HIGH,
//			/*bmp inx*/ 0,
//			/*bmp num*/ 0,
//			/*ArgCount*/2,
//			/*arg lp*/  Args,
//		} ,Fn_e_malloc ,"Fn_e_malloc" };
