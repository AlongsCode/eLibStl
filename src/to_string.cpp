#include"ElibHelp.h"
static void* GetAryElementInf(void* pAryData, DWORD& AryElementCount)
{
	LPINT pnData;
	INT nArys;
	UINT nElementCount;

	pnData = (LPINT)pAryData;

	nArys = *pnData; //取得维数。
	pnData += 1;

	// 计算成员数目。
	nElementCount = 1;
	while (nArys > 0)
	{
		nElementCount *= pnData[0];
		pnData++;
		nArys--;
	}

	AryElementCount = nElementCount;
	return pnData;
}
static wchar_t* ArryToString(void* pArry, DWORD szData)
{
	DWORD dwSize;
	wchar_t* pText = (wchar_t*)GetAryElementInf(pArry, dwSize);
	if (dwSize == 0)
		return NULL;
	INT nMax = dwSize * szData;
	INT i;
	for (i = 0; i < nMax; i++)
	{
		if (pText[i] == L'\0')
			break;
	}
	UINT nLen = i;

	if (nLen == 0)return NULL;
	wchar_t* pNewText = reinterpret_cast<wchar_t*>(elibstl::malloc((nLen + 1) * sizeof(wchar_t)));
	memcpy(pNewText, pText, nLen * sizeof(wchar_t));
	pNewText[nLen] = L'\0';
	return pNewText;

}
//inline void LTrimZeroChr(std::wstring& result)
//{
//
//	auto pos = result.find_first_not_of(L'0'); // 找到第一个非零字符的位置
//	if (pos != std::wstring::npos)
//	{
//		result.erase(0, pos); // 删除左侧无用的零
//	}
//	// 如果存在小数点，则删除结尾的零和小数点
//	if (auto pos_dot = result.find_last_of(L'.'); pos_dot != std::wstring::npos)
//	{
//		// 找到最后一个非零数字的位置
//		auto pos_nonzero = result.find_last_not_of(L'0');
//		// 如果最后一个非零数字位于小数点之前，则将小数点一起删除
//		if (pos_nonzero < pos_dot)
//		{
//			result.erase(pos_dot, std::wstring::npos);
//		}
//		// 如果最后一个非零数字位于小数点之后，则仅删除结尾的零字符
//		else
//		{
//			result.erase(pos_nonzero + 1, std::wstring::npos);
//		}
//	}
//
//}


inline void LTrimZeroChr(wchar_t* str)
{
	wchar_t* z = NULL;
	wchar_t* p = NULL;

	// 找小数点
	for (; *str; str++)
	{
		if (*str == L'.')
		{
			p = str++;
			break;
		}
	}

	//
	if (p) //存在小数点
	{
		for (; *str; str++)
		{
			if (*str == L'0')
			{
				if (!z)
				{
					z = str;
				}
			}
			else
			{
				z = NULL;
			}
		}

		//
		if (z)
		{
			if (z == p + 1) // 以小数点结尾则删除小数点
			{
				*p = L'\0';
			}
			else
			{
				*z = L'\0';
			}
		}
	}
}

EXTERN_C void Fn_to_string(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	LPBYTE pText = NULL;
	auto ArgInf = *pArgInf;
	if ((ArgInf.m_dtDataType & DT_IS_ARY) == DT_IS_ARY)//是数组
	{
		ArgInf.m_dtDataType &= ~DT_IS_ARY; //去除数组标志
		DWORD szData = 0;
		switch (ArgInf.m_dtDataType)
		{
		case SDT_BYTE:
			szData = sizeof(BYTE);
			break;
		case SDT_SHORT:
			szData = sizeof(SHORT);
			break;
		case SDT_INT64:
			szData = sizeof(INT64);
			break;
		case SDT_INT:
		case SDT_SUB_PTR:
			szData = sizeof(DWORD);
			break;
		}
		if (szData)
			pText = elibstl::clone_textw(ArryToString(ArgInf.m_pAryData, szData), static_cast<bool>(elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE)));
	}
	else
	{
		wchar_t str[MAX_PATH]{ 0 };
		int nLen = 0;
		wchar_t* pSrc = NULL;

		switch (ArgInf.m_dtDataType)
		{
		case SDT_TEXT:
			nLen = strlen(ArgInf.m_pText);
			if (nLen) {
				pSrc = elibstl::A2W(ArgInf.m_pText);
				pText = elibstl::clone_textw(pSrc, static_cast<bool>(elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE)));
				delete[]pSrc;
				pSrc = nullptr;
				nLen = 0;
			}
			break;
		case SDT_BYTE:
		{
			INT nVal = ArgInf.m_byte;
			wsprintf(str, L"%d", nVal);
			nLen = wcslen(str);
			pSrc = str;
		}
		break;
		case SDT_SHORT:
		{
			INT nVal = ArgInf.m_short;
			wsprintf(str, L"%d", nVal);
			nLen = wcslen(str);
			pSrc = str;
		}
		break;
		case SDT_INT:
		case SDT_SUB_PTR:
			wsprintf(str, L"%d", ArgInf.m_int);
			nLen = wcslen(str);
			pSrc = str;
			break;
		case SDT_INT64:
			wsprintf(str, L"%I64d", ArgInf.m_int64);
			nLen = wcslen(str);
			pSrc = str;
			break;
		case SDT_FLOAT:
			wsprintf(str, L"%f", ArgInf.m_float);
			LTrimZeroChr(str);
			nLen = wcslen(str);
			pSrc = str;
			break;
		case SDT_DOUBLE:
			wsprintf(str, L"%.13g", ArgInf.m_double);
			LTrimZeroChr(str);
			nLen = wcslen(str);
			pSrc = str;
			break;
		case SDT_BOOL:
			if (ArgInf.m_bool)
				wcscpy(str, L"真");
			else
				wcscpy(str, L"假");
			nLen = wcslen(str);
			pSrc = str;
			break;
		case SDT_BIN:
			pText = ArgInf.m_pBin;
			break;
		case SDT_DATE_TIME:
			auto DateTimeFormat = [](LPWSTR strValue, DATE dtDt, BOOL bOnlyDatePart)
			{
				SYSTEMTIME st = { 0 };
				VariantTimeToSystemTime(dtDt, &st);

				wchar_t strFormat[128]{ 0 };
				wcscpy_s(strFormat, L"%d年%d月%d日");


				//格式化时间部分
				wchar_t strFormatTime[128]{ 0 };

				if (st.wSecond)
					wcscpy_s(strFormatTime, L"%d时%d分%d秒");
				else if (st.wMinute && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%d时%d分");
				else if (st.wHour && st.wMinute == 0 && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%d时");
				else
					strFormatTime[0] = 0;

				if (bOnlyDatePart == FALSE)
					wcscat_s(strFormat, strFormatTime);

				wsprintf(strValue, strFormat, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			};
			DateTimeFormat(str, ArgInf.m_double, FALSE);
			nLen = wcslen(str);
			if (nLen)
				pSrc = str;
			break;
		}
		if (pSrc && nLen)
		{
			pText = elibstl::clone_textw(pSrc, nLen, static_cast<bool>(elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE)));
		}

	}
	pRetData->m_pBin = pText;
}



static ARG_INFO Args[] =
{
	{
		/*name*/    "欲转换的数据",
		/*explain*/ ("欲转换的数据"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA,
	},{
		/*name*/    "是否包含结束符",
		/*explain*/ ("默认包含结束符"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BOOL,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

FucInfo   eto_wstring = { {
		/*ccname*/  ("到文本W"),
		/*egname*/  ("to_wstring"),
		/*explain*/ ("转换指定数据为文本。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &Args[0],
	} , Fn_to_string ,"Fn_to_string" };

