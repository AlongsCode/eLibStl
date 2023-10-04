#include"ElibHelp.h"


static ARG_INFO Args[] =
{
		{
			"子程序指针或子程序地址",
			"提示：在子程序名称前加“&”即可得到该子程序的“子程序指针”，如“&子程序1”就是“子程序1”的子程序指针；子程序地址可通过本库中的“取子程序地址()”命令获取，“到整数(&子程序1)”返回的也是子程序1的执行地址，也可通过Windows系统API函数“GetProcAddress()”获取，或由外部程序传入。",
			0,
			0,
			_SDT_ALL,
			0,
			ArgMark::AS_NONE,
		},
		{
				"返回值",
				"本参数用于接收子程序被调用后的返回值；如果该子程序没有返回值或不需要接收返回值，请省略本参数。，提供本参数时，请务必提供准确的数据类型，否则所得结果可能不正确。",
				0,
				0,
				_SDT_ALL,
				0,
				ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_VAR,
		},{
			"参数",
			"本参数值将作为参数传入被调用子程序。如果相应子程序没有参数，请省略本参数；如果相应子程序有多个参数，请重复提供本参数。请务必提供准确的参数类型和参数个数，否则后果不可预知。",
			0,
			0,
			_SDT_ALL,
			0,
			ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
		}
};

#pragma region Old
//
//
//
//
//
//
//inline void CallFunction_GetValue(PMDATA_INF pMData, int& HiValue, int& LowValue, int& bytes)
//{
//	HiValue = LowValue = 0;
//	if (pMData->m_dtDataType == _SDT_NULL) return;
//	bytes = 4;
//
//	switch (pMData->m_dtDataType)
//	{
//	case SDT_INT:
//		LowValue = (int)pMData->m_int; break;
//	case SDT_SHORT:
//		LowValue = (int)pMData->m_short; bytes = 2; break;
//	case SDT_BYTE:
//		LowValue = (int)pMData->m_byte; bytes = 1; break;
//	case SDT_INT64:
//	{
//		LowValue = *(reinterpret_cast<INT*>(&pMData->m_int64));
//		HiValue = *(reinterpret_cast<INT*>(&pMData->m_int64) + 1);
//		bytes = 8;
//		break;
//	}
//	case SDT_FLOAT:
//		//LowValue = (int)pMData->m_float;  //这样肯定是不行的
//	{
//		//注意float转int的处理方式(通过ST0寄存器中转一下), 参考了VC编译器生成的汇编代码
//		float f = pMData->m_float;
//		int i = 0;
//		__asm fld f;
//		__asm fst i;
//		LowValue = (int)i;
//		bytes = 4;
//		break;
//	}
//	case SDT_DOUBLE:
//	case SDT_DATE_TIME:
//	{
//		LowValue = *(reinterpret_cast<INT*>(&pMData->m_double));
//		HiValue = *(reinterpret_cast<INT*>(&pMData->m_double) + 1);
//		bytes = 8;
//		break;
//	}
//	case SDT_BOOL:
//		LowValue = (int)(pMData->m_bool ? 1 : 0); bytes = 4; break;
//	case SDT_TEXT:
//		LowValue = (int)(DWORD)pMData->m_pText; break;
//	case SDT_BIN:
//	{
//		if (pMData->m_pBin == NULL) //! 字节集为空的情况!
//		{
//			LowValue = (int)0; break;
//		}
//		LowValue = reinterpret_cast<DWORD>(reinterpret_cast<LPBYTE>(pMData->m_pBin) + 2 * sizeof(INT));
//		break;
//	}
//	case SDT_SUB_PTR:
//		LowValue = (int)((DWORD)pMData->m_dwSubCodeAdr); break;
//	case _SDT_NULL:
//		LowValue = (int)0; break;
//	case SDT_STATMENT:
//		//todo: 执行子语句并取其值
//		LowValue = (int)0; //!!!
//		break;
//	default: LowValue = (int)pMData->m_int; break;
//	}
//}
////将寄存器EAX或ST0中的值写入pMData
//inline void CallFunction_GetReturnedValue(PMDATA_INF pMData, int eaxValue, int edxValue, double stValue)
//{
//	if (pMData->m_dtDataType == _SDT_NULL) return;
//
//	switch (pMData->m_dtDataType)
//	{
//	case SDT_INT: case SDT_SHORT: case SDT_BYTE:
//		*(pMData->m_pInt) = eaxValue;
//		break;
//	case SDT_INT64:
//	{
//		//EAX在低位, EDX在高位, 组成double
//		int temp[2];
//		temp[0] = eaxValue; temp[1] = edxValue;
//		*(pMData->m_pInt64) = *(INT64*)temp;
//		break;
//	}
//	case SDT_FLOAT:
//		//根据VC编译器生成的代码，返回的浮点数(float,double)应该在ST0中；看来易编译器与其不同。
//		//*(pMData->m_pFloat) = (float)stValue; 
//	{
//		float f = 0;
//		__asm fld eaxValue;
//		__asm fst f;
//		*(pMData->m_pFloat) = f;
//	}
//	break;
//	case SDT_DOUBLE:
//	case SDT_DATE_TIME:
//		//根据VC编译器生成的代码，返回的浮点数(float,double)应该在ST0中；看来易编译器与其不同。
//		//*(pMData->m_pDouble) = stValue;
//	{
//		//EAX在低位, EDX在高位, 组成double
//		int temp[2];
//		temp[0] = eaxValue; temp[1] = edxValue;
//		*(pMData->m_pDouble) = *(double*)temp;
//	}
//	break;
//	case SDT_BOOL:
//		*(pMData->m_pBool) = (eaxValue != 0);
//		break;
//	case SDT_TEXT:
//		*(pMData->m_ppText) = elibstl::clone_text((char*)eaxValue);
//		break;
//	case SDT_BIN:
//		//pMData->m_pBin = CloneBinData((LPBYTE)intValue, n); //? 无法知道字节集长度!
//		break;
//	case SDT_SUB_PTR:
//		break;
//	case _SDT_NULL:
//		break;
//	case SDT_STATMENT:
//		break;
//
//	default:
//		break;
//	}
//}
//static BOOL Global_CallFunction(PMDATA_INF pFuncMData, INT nArgCount)
//{
//
//	//取被调用子程序的执行地址(pFunc)
//	int pFunc = NULL; //pArgInf[0].m_dwSubCodeAdr;
//	int temp = 0;
//	CallFunction_GetValue(pFuncMData, temp, pFunc, temp);
//	if (pFunc == 0) return FALSE;
//
//	//返回值
//	PMDATA_INF pReturnMData = &pFuncMData[2];
//	//参数
//	PMDATA_INF pParamsMData = &pFuncMData[3];
//
//	//参数依次反序压栈
//	int  HiValue = 0, LowValue = 0;
//	int bytes = 0;
//	int byteValue = 0;
//	int shortValue = 0;
//	if (!(pParamsMData[0].m_dtDataType == _SDT_NULL && nArgCount <= 1)) //第一个参数被省略表示没有参数
//	{
//		for (int i = nArgCount - 1; i >= 0; i--) //反序压栈
//		{
//			CallFunction_GetValue(&pParamsMData[i], HiValue, LowValue, bytes); //函数调用会影响参数栈吗?
//
//			//经查看VC编译器生成的汇编代码，参数压栈总是以4字节为单位
//			byteValue = (int)(byte)LowValue; shortValue = (int)(short)LowValue;
//
//			//如果是8字节数值的话,先高位入栈,后低位入栈
//			if (bytes == 8)
//			{
//				__asm PUSH HiValue;
//				__asm PUSH LowValue;
//			}
//			else if (bytes == 4)
//				__asm PUSH LowValue;
//			else if (bytes == 2)
//				__asm PUSH shortValue;
//			else if (bytes == 1)
//				__asm PUSH byteValue;
//
//		}
//	}
//
//	//调用子程序
//	__asm CALL pFunc;
//	int eaxValue = 0, edxValue = 0;
//	double stValue = 0.0;
//	__asm mov eaxValue, eax;
//	__asm mov edxValue, edx;
//	__asm fst stValue; //! 取ST0寄存器中存储的浮点数值(float,double)
//
//	if (pReturnMData->m_dtDataType != _SDT_NULL)
//		CallFunction_GetReturnedValue(pReturnMData, eaxValue, edxValue, stValue);
//
//	return TRUE;
//
//
//
//}


EXTERN_C void Fn_CallEfun(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {

	if (pArgInf->m_dtDataType != SDT_INT && pArgInf->m_dtDataType != SDT_SUB_PTR)
	{
		pRetData->m_bool = FALSE;
	}
	//4字节32位依次压入
	std::uint32_t
		pEfun = pArgInf[0].m_uint;



	//从后往前
	for (int i = nArgCount - 1; i > 1; i--)
	{
		std::uint32_t arg = 0;
		switch (pArgInf[i].m_dtDataType)	//	判断参数类型
		{
			//32位以下
		case SDT_BYTE:
		case SDT_SHORT:
		case SDT_INT:
		case SDT_BOOL:
		case SDT_SUB_PTR:
		case SDT_TEXT:
			arg = pArgInf[i].m_dwSubCodeAdr;
			break;
		case SDT_FLOAT:
			arg = pArgInf[i].m_uint;
			break;
		case SDT_DOUBLE:
		case SDT_DATE_TIME:
			arg = *(reinterpret_cast<std::uint32_t*>(&pArgInf[i].m_date) + 1);	//	高32位
			_asm
			{
				push arg	//	参数压栈
			}
			arg = *(reinterpret_cast<std::uint32_t*>(&pArgInf[i].m_date));//	低32位
			break;
		case SDT_INT64:
			arg = *(reinterpret_cast<std::uint32_t*>(&pArgInf[i].m_int64) + 1);	//高32位
			_asm
			{
				push arg	//	参数压栈
			}
			arg = *(reinterpret_cast<std::uint32_t*>(&pArgInf[i].m_int64));	//	低32位
			break;

		case SDT_BIN:
			//易语言IDE禁止被取地址的子程序存在字节集参数但是，因为指针获取方式不一定通过易语言的代码，所以还是加上了
			if (pArgInf[i].m_pBin == NULL) //!防止为空访问到垃圾内存
			{
				arg = 0; break;
			}
			arg = reinterpret_cast<std::uint32_t>(pArgInf[i].m_pBin + 2 * sizeof(INT));
			break;
		}
		_asm
		{
			push arg
		}

	}
	//执行函数
	std::uint32_t lpart, hpart;
	_asm
	{
		call pEfun
		mov lpart, eax
		mov hpart, edx
	}

	switch (pArgInf[1].m_dtDataType)
	{

	case SDT_BYTE:
		if (pArgInf[1].m_pByte)
			*pArgInf[1].m_pByte = static_cast <std::uint8_t>(lpart);
		break;

	case SDT_SHORT:
		if (pArgInf[1].m_pShort)
			*pArgInf[1].m_pShort = static_cast <std::uint16_t>(lpart);
		break;

	case SDT_INT:
		if (pArgInf[1].m_pInt)
			*reinterpret_cast<unsigned int*>(pArgInf[1].m_pInt) = lpart;
		break;

	case SDT_INT64:
		if (pArgInf[1].m_pInt64)
		{
			LARGE_INTEGER temp;
			temp.HighPart = hpart;
			temp.LowPart = lpart;
			*pArgInf[1].m_pInt64 = *reinterpret_cast<long long*>(&temp);
		}
		break;

	case SDT_FLOAT:
		if (pArgInf[1].m_pFloat) {
			*pArgInf[1].m_pFloat = *reinterpret_cast<float*>(&lpart);
		}
		break;

	case SDT_DOUBLE:
	case SDT_DATE_TIME:
		if (pArgInf[1].m_pDate)
		{
			std::uint32_t temp[2] = { lpart ,hpart };
			*(pArgInf[1].m_pDate) = *reinterpret_cast<double*>(temp);
		}
		break;
	case SDT_BOOL:
		if (pArgInf[1].m_pBool)
			*pArgInf[1].m_pBool = static_cast<int>(lpart);
		break;


	case SDT_TEXT:
		if (pArgInf[1].m_ppText)
		{
			elibstl::efree(*(pArgInf[1].m_ppText));
			*(pArgInf[1].m_ppText) =
				elibstl::clone_text(reinterpret_cast<char*>(lpart));
		}
		break;


	case SDT_BIN:
		//易语言IDE禁止被取地址的子程序存在字节集参数但是，因为指针获取方式不一定通过易语言的代码，所以还是加上了
		if (pArgInf[1].m_ppBin)
		{
			elibstl::efree(*(pArgInf[1].m_ppBin));
			*(pArgInf[1].m_ppBin) = elibstl::clone_bin(
				reinterpret_cast<unsigned char*>(lpart), *(reinterpret_cast<std::uint32_t*>(lpart) - 1));
		}
		break;

	case SDT_SUB_PTR:
		if (pArgInf[1].m_pdwSubCodeAdr)
			*pArgInf[1].m_pdwSubCodeAdr = lpart;
		break;
	}

	pRetData->m_bool = TRUE;


}



#pragma endregion







#pragma region new
//inline  void* _GetPointerByIndex(void* pBase, int index)
//{
//	return (void*)((INT)pBase + index * sizeof(INT));
//}
//
//inline  INT _GetIntByIndex(void* pBase, INT index)
//{
//	return *((INT*)_GetPointerByIndex(pBase, index));
//}
//inline void CallFunction_GetValue(PMDATA_INF pMData, int& HiValue, int& LowValue, int& bytes)
//{
//	HiValue = LowValue = 0;
//	if (pMData->m_dtDataType == _SDT_NULL) return;
//	bytes = 4;
//	switch (pMData->m_dtDataType)
//	{
//	case SDT_INT:
//		LowValue = (int)pMData->m_int; break;
//	case SDT_SHORT:
//		LowValue = (int)pMData->m_short; bytes = 2; break;
//	case SDT_BYTE:
//		LowValue = (int)pMData->m_byte; bytes = 1; break;
//	case SDT_INT64:
//	{
//		LowValue = (int)_GetIntByIndex(&(pMData->m_int64), 0);
//		HiValue = (int)_GetIntByIndex(&(pMData->m_int64), 1);
//		bytes = 8;
//		break;
//	}
//	case SDT_FLOAT:
//	{
//		float f = pMData->m_float;
//		int i = 0;
//		__asm fld f;
//		__asm fst i;
//		LowValue = (int)i;
//		bytes = 4;
//		break;
//	}
//	case SDT_DOUBLE:
//	case SDT_DATE_TIME:
//	{
//		LowValue = (int)_GetIntByIndex(&(pMData->m_double), 0);
//		HiValue = (int)_GetIntByIndex(&(pMData->m_double), 1);
//		bytes = 8;
//		break;
//	}
//	case SDT_BOOL:
//		LowValue = (int)(pMData->m_bool ? 1 : 0); bytes = 4; break;
//	case SDT_TEXT:
//		LowValue = (int)(DWORD)pMData->m_pText; break;
//	case SDT_BIN:
//	{
//		if (pMData->m_pBin == NULL) //! 字节集为空的情况!
//		{
//			LowValue = (int)0; break;
//		}
//		LowValue = (int)(DWORD)(LPBYTE)_GetPointerByIndex(pMData->m_pBin, 2);
//		break;
//	}
//	case SDT_SUB_PTR:
//		LowValue = (int)((DWORD)pMData->m_dwSubCodeAdr); break;
//	case _SDT_NULL:
//		LowValue = (int)0; break;
//	case SDT_STATMENT:
//		//todo: 执行子语句并取其值
//		LowValue = (int)0; //!!!
//		break;
//	default: LowValue = (int)pMData->m_int; break;
//	}
//}
//
////将寄存器EAX或ST0中的值写入pMData
//inline void CallFunction_GetReturnedValue(PMDATA_INF pMData, int eaxValue, int edxValue, double stValue)
//{
//	if (pMData->m_dtDataType == _SDT_NULL) return;
//
//	switch (pMData->m_dtDataType)
//	{
//	case SDT_INT: case SDT_SHORT: case SDT_BYTE:
//		*(pMData->m_pInt) = eaxValue;
//		break;
//	case SDT_INT64:
//	{
//		//EAX在低位, EDX在高位, 组成double
//		int temp[2];
//		temp[0] = eaxValue; temp[1] = edxValue;
//		*(pMData->m_pInt64) = *(INT64*)temp;
//		break;
//	}
//	case SDT_FLOAT:
//		//根据VC编译器生成的代码，返回的浮点数(float,double)应该在ST0中；看来易编译器与其不同。
//		//*(pMData->m_pFloat) = (float)stValue; 
//	{
//		float f = 0;
//		__asm fld eaxValue;
//		__asm fst f;
//		*pMData->m_pFloat = f;
//		debug_put(f);
//	}
//	break;
//	case SDT_DOUBLE:
//	case SDT_DATE_TIME:
//		//根据VC编译器生成的代码，返回的浮点数(float,double)应该在ST0中；看来易编译器与其不同。
//		//*(pMData->m_pDouble) = stValue;
//	{
//		//EAX在低位, EDX在高位, 组成double
//		int temp[2];
//		temp[0] = eaxValue; temp[1] = edxValue;
//		*(pMData->m_pDouble) = *(double*)temp;
//	}
//	break;
//	case SDT_BOOL:
//		*(pMData->m_pBool) = (eaxValue != 0);
//		break;
//	case SDT_TEXT:
//		*(pMData->m_ppText) = elibstl::clone_text((char*)eaxValue);
//		break;
//	case SDT_BIN:
//
//		break;
//	case SDT_SUB_PTR:
//		break;
//	case _SDT_NULL:
//		break;
//	case SDT_STATMENT:
//		break;
//
//	default:
//		break;
//	}
//}
//inline BOOL Global_CallFunction(PMDATA_INF pFuncMData, INT nArgCount)
//{
//
//	//取被调用子程序的执行地址(pFunc)
//	int pFunc = NULL; //pArgInf[0].m_dwSubCodeAdr;
//	int temp = 0;
//	CallFunction_GetValue(pFuncMData, temp, pFunc, temp);
//	if (pFunc == 0) return FALSE;
//
//	//返回值
//	PMDATA_INF pReturnMData = &pFuncMData[1];
//	//参数
//	PMDATA_INF pParamsMData = &pFuncMData[2];
//
//	//参数依次反序压栈
//	int  HiValue = 0, LowValue = 0;
//	int bytes = 0;
//	int byteValue = 0;
//	int shortValue = 0;
//	if (!(pParamsMData[0].m_dtDataType == _SDT_NULL && nArgCount <= 1)) //第一个参数被省略表示没有参数
//	{
//		for (int i = nArgCount - 1; i >= 0; i--) //反序压栈
//		{
//			CallFunction_GetValue(&pParamsMData[i], HiValue, LowValue, bytes); //函数调用会影响参数栈吗?
//
//			//经查看VC编译器生成的汇编代码，参数压栈总是以4字节为单位
//			byteValue = (int)(byte)LowValue; shortValue = (int)(short)LowValue;
//
//			//如果是8字节数值的话,先高位入栈,后低位入栈
//			if (bytes == 8)
//			{
//				__asm PUSH HiValue;
//				__asm PUSH LowValue;
//			}
//			else if (bytes == 4)
//				__asm PUSH LowValue;
//			else if (bytes == 2)
//				__asm PUSH shortValue;
//			else if (bytes == 1)
//				__asm PUSH byteValue;
//
//		}
//	}
//
//	//调用子程序
//	__asm CALL pFunc;
//
//	//取被调用子程序的返回值 (须在CALL之后立刻读取)
//	int eaxValue = 0, edxValue = 0;
//	double stValue = 0.0;
//	__asm mov eaxValue, eax;
//	__asm mov edxValue, edx;
//	__asm fst stValue; //! 取ST0寄存器中存储的浮点数值(float,double)
//
//	if (pReturnMData->m_dtDataType != _SDT_NULL)
//		CallFunction_GetReturnedValue(pReturnMData, eaxValue, edxValue, stValue);
//
//	return TRUE;
//
//
//
//}
//
//
//
//
//EXTERN_C void Fn_CallEfun(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
//
//	BOOL bOK = Global_CallFunction(pArgInf, nArgCount - 2);
//	if (pRetData)
//	{
//		pRetData->m_bool = bOK;
//	}
//}


#pragma endregion





FucInfo e_CallEfun = { {
		/*ccname*/  ("调用函数"),
		/*egname*/  ("e_call"),
		/*explain*/ ("同易语言的调用子程序"),
		/*category*/12,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  &Args[0],
	} ,Fn_CallEfun ,"Fn_CallEfun" };

