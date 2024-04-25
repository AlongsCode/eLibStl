#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"



// �����쳣������ָ��ԭ��
using  ExceptionHandlerFunction = bool(__stdcall*)(const char*);


#include <stdexcept>
#include <iostream>
#include <windows.h>

namespace {
    // Ĭ���쳣������
    bool  __stdcall  DefaultExceptionHandler(const char* errorMessage) {
        // �ڴ˴����Ĭ�ϵ��쳣�����߼��������������־��
		auto wstr= elibstl::A2W(errorMessage);
		std::wstring s = L"����δ������쳣,������ͣ����" ;
		
		put_errmsg(s.append(wstr));
		delete[]wstr;
        //std::cerr << "Default Exception Handler: " << errorMessage << std::endl;
        return false;  // ����false��ʾδ����
    };
    ExceptionHandlerFunction g_exceptionHandler{ DefaultExceptionHandler };
    // �쳣������ָ��
    //ExceptionHandlerFunction g_exceptionHandler{ DefaultExceptionHandler };
    //HANDLE g_Handler{ NULL };
    //// Vectored Exception Handler
    //LONG WINAPI VectoredExceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
    //    // ��ȡ�쳣ָ��
    //    PEXCEPTION_RECORD exceptionRecord = exceptionInfo->ExceptionRecord;

    //    // ��ȡ�쳣����
    //    DWORD exceptionCode = exceptionRecord->ExceptionCode;

    //    // ��ȡ�쳣��Ϣ
    //    std::string errorMessage = "Unknown Exception";
    //    if (exceptionCode == 0xC0000005) {
    //        errorMessage = "Access Violation";
    //    }
    //    else if (exceptionRecord->ExceptionInformation[0] == 0 && exceptionCode == EXCEPTION_ACCESS_VIOLATION) {
    //        errorMessage = "Access Violation (NULL Pointer)";
    //    }
    //    else if (exceptionCode == 0xE06D7363) {
    //        // C++�쳣
    //        errorMessage = "C++ Exception: " + std::string(reinterpret_cast<const char*>(exceptionRecord->ExceptionInformation[1]));
    //    }

    //    // �����쳣������
    //    bool handled = g_exceptionHandler(errorMessage.c_str());

    //    // ���� EXCEPTION_CONTINUE_SEARCH ��ʾ�������������쳣�������
    //    return handled ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_CONTINUE_SEARCH;
    //}
}
// ��װ Vectored Exception Handler
//void InstallVectoredExceptionHandler() {
//    // ע�� Vectored Exception Handler
//    AddVectoredExceptionHandler(1, VectoredExceptionHandler);
//}




// ע���쳣������-�ӿ�
void RegisterExceptionHandler(ExceptionHandlerFunction handler) {
    if (handler)
        g_exceptionHandler = handler;
    else
        ExceptionHandlerFunction g_exceptionHandler = DefaultExceptionHandler;
   // InstallVectoredExceptionHandler();
}

// �׳��쳣-�ӿ�
//bool ThrowException(const char* errorMessage) {
//    try {
//        // �����쳣������
//        bool handled = g_exceptionHandler(errorMessage);
//        if (!handled) {
//            // ����쳣δ�������׳�std::runtime_error�쳣
//            throw std::runtime_error(errorMessage);
//        }
//        return true;  // ����true��ʾ�쳣�ѱ�����
//    }
//    catch (...) {
//        // �쳣�����������׳��쳣������false��ʾδ����
//        __debugbreak();
//        return false;
//    }
//}

bool ThrowException(const char* errorMessage) {
        // �����쳣������
        bool handled = g_exceptionHandler(errorMessage);
        if (!handled) {
            // ����쳣δ�������׳�std::runtime_error�쳣
			MDATA_INF RetData{};

			__debugbreak();
			//elibstl::CallElibFunc("krnln.fne", "��ͣ", &RetData, 0, nullptr);
           // __debugbreak();
            return false;
        }
        return true;  // ����true��ʾ�쳣�ѱ�����
}

//void UnRegisterExcept() {
//    if (g_Handler)
//    {
//        RemoveVectoredExceptionHandler(g_Handler);
//    }
//
//}

// �Զ����쳣������
bool CustomExceptionHandler(const char* errorMessage) {
    // ����������Զ�����쳣�����߼���������ʾ����Ի����
    std::cerr << "Custom Exception Handler: " << errorMessage << std::endl;
    return false;  // ����true��ʾ�Ѵ����쳣
}

//int main() {
//    // ע���Զ����쳣������
//    RegisterExceptionHandler(CustomExceptionHandler);
//
//    // ��װ Vectored Exception Handler
//
//
//    try {
//        // �׳��쳣
//        if (ThrowException("����!")) {
//            std::cout << "Exception handled." << std::endl;
//        }
//        else {
//            std::cerr << "Exception not handled." << std::endl;
//        }
//    }
//    catch (const std::exception& e) {
//        // �����ﴦ��δ���쳣������������쳣
//        std::cerr << "Unhandled Exception: " << e.what() << std::endl;
//    }
//
//    return 0;
//}




/*.�汾 2
.֧�ֿ� libstl

.�ӳ��� _��ť1_������

�׳��쳣 (��a��)

�����쳣 (��a��, &����)


.�ӳ��� ����


*/

static ARG_INFO Args[] =
{
	{
	/*name*/	"�쳣ֵ",
	/*explain*/	"�쳣��ʶ",
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_TEXT,
	/*default*/	0,
	/*state*/	ArgMark::AS_NONE,
		},
			{
		/*name*/	"�ص�����",
		/*explain*/	"����Ϊ�߼�����ֻ��һ���ı��Ͳ����ĺ���,������������쳣�Ѿ�������,�������ͣ����",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_SUB_PTR,
		/*default*/	0,
		/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY ,
			},
};



EXTERN_C void efn_catch_ception(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	//auto str = elibstl::args_to_sdata(pArgInf, 0);
	RegisterExceptionHandler(static_cast<ExceptionHandlerFunction>(pArgInf->m_pCompoundData));

}

FucInfo Fn_catch_ception = { {
		/*ccname*/  ("ע���쳣������"),
		/*egname*/  ("catch_ception"),
		/*explain*/ ("�����������̵߳���һ��!!!"),
		/*category*/11,
		/*state*/    CT_IS_HIDED,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args+1,
	} ,efn_catch_ception ,"efn_catch_ception" };




EXTERN_C void efn_throw_ception(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto str = elibstl::args_to_sdata(pArgInf, 0);
	pRetData->m_bool = ThrowException(str.empty() ? "δ�����쳣ֵ" : str.data());  

}

FucInfo Fn_throw_ception = { {
		/*ccname*/  ("�׳��쳣"),
		/*egname*/  ("throw_ception"),
		/*explain*/ ("�׳�ָ���쳣"),
		/*category*/11,
		/*state*/   CT_IS_HIDED,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,efn_throw_ception ,"efn_throw_ception" };

