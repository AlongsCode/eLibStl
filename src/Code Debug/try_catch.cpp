#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"



// 定义异常处理函数指针原型
using  ExceptionHandlerFunction = bool(__stdcall*)(const char*);


#include <stdexcept>
#include <iostream>
#include <windows.h>

namespace {
    // 默认异常处理函数
    bool  __stdcall  DefaultExceptionHandler(const char* errorMessage) {
        // 在此处添加默认的异常处理逻辑，例如输出到日志等
		std::string s = "* 出现未处理的异常,即将暂停程序" ;
		OutputDebugStringA(s.append(errorMessage).c_str());
        //std::cerr << "Default Exception Handler: " << errorMessage << std::endl;
        return false;  // 返回false表示未处理
    };
    ExceptionHandlerFunction g_exceptionHandler{ DefaultExceptionHandler };
    // 异常处理函数指针
    //ExceptionHandlerFunction g_exceptionHandler{ DefaultExceptionHandler };
    //HANDLE g_Handler{ NULL };
    //// Vectored Exception Handler
    //LONG WINAPI VectoredExceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
    //    // 获取异常指针
    //    PEXCEPTION_RECORD exceptionRecord = exceptionInfo->ExceptionRecord;

    //    // 获取异常代码
    //    DWORD exceptionCode = exceptionRecord->ExceptionCode;

    //    // 获取异常消息
    //    std::string errorMessage = "Unknown Exception";
    //    if (exceptionCode == 0xC0000005) {
    //        errorMessage = "Access Violation";
    //    }
    //    else if (exceptionRecord->ExceptionInformation[0] == 0 && exceptionCode == EXCEPTION_ACCESS_VIOLATION) {
    //        errorMessage = "Access Violation (NULL Pointer)";
    //    }
    //    else if (exceptionCode == 0xE06D7363) {
    //        // C++异常
    //        errorMessage = "C++ Exception: " + std::string(reinterpret_cast<const char*>(exceptionRecord->ExceptionInformation[1]));
    //    }

    //    // 调用异常处理函数
    //    bool handled = g_exceptionHandler(errorMessage.c_str());

    //    // 返回 EXCEPTION_CONTINUE_SEARCH 表示继续搜索其他异常处理程序
    //    return handled ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_CONTINUE_SEARCH;
    //}
}
// 安装 Vectored Exception Handler
//void InstallVectoredExceptionHandler() {
//    // 注册 Vectored Exception Handler
//    AddVectoredExceptionHandler(1, VectoredExceptionHandler);
//}




// 注册异常处理函数-接口
void RegisterExceptionHandler(ExceptionHandlerFunction handler) {
    if (handler)
        g_exceptionHandler = handler;
    else
        ExceptionHandlerFunction g_exceptionHandler = DefaultExceptionHandler;
   // InstallVectoredExceptionHandler();
}

// 抛出异常-接口
//bool ThrowException(const char* errorMessage) {
//    try {
//        // 调用异常处理函数
//        bool handled = g_exceptionHandler(errorMessage);
//        if (!handled) {
//            // 如果异常未被处理，抛出std::runtime_error异常
//            throw std::runtime_error(errorMessage);
//        }
//        return true;  // 返回true表示异常已被处理
//    }
//    catch (...) {
//        // 异常处理函数本身抛出异常，返回false表示未处理
//        __debugbreak();
//        return false;
//    }
//}

bool ThrowException(const char* errorMessage) {
        // 调用异常处理函数
        bool handled = g_exceptionHandler(errorMessage);
        if (!handled) {
            // 如果异常未被处理，抛出std::runtime_error异常
			MDATA_INF RetData{};
			__debugbreak();
			//elibstl::CallElibFunc("krnln.fne", "暂停", &RetData, 0, nullptr);
           // __debugbreak();
            return false;
        }
        return true;  // 返回true表示异常已被处理
}

//void UnRegisterExcept() {
//    if (g_Handler)
//    {
//        RemoveVectoredExceptionHandler(g_Handler);
//    }
//
//}

// 自定义异常处理函数
bool CustomExceptionHandler(const char* errorMessage) {
    // 在这里添加自定义的异常处理逻辑，例如显示错误对话框等
    std::cerr << "Custom Exception Handler: " << errorMessage << std::endl;
    return false;  // 返回true表示已处理异常
}

//int main() {
//    // 注册自定义异常处理函数
//    RegisterExceptionHandler(CustomExceptionHandler);
//
//    // 安装 Vectored Exception Handler
//
//
//    try {
//        // 抛出异常
//        if (ThrowException("测试!")) {
//            std::cout << "Exception handled." << std::endl;
//        }
//        else {
//            std::cerr << "Exception not handled." << std::endl;
//        }
//    }
//    catch (const std::exception& e) {
//        // 在这里处理未被异常处理函数处理的异常
//        std::cerr << "Unhandled Exception: " << e.what() << std::endl;
//    }
//
//    return 0;
//}




/*.版本 2
.支持库 libstl

.子程序 _按钮1_被单击

抛出异常 (“a”)

捕获异常 (“a”, &测试)


.子程序 测试


*/

static ARG_INFO Args[] =
{
	{
	/*name*/	"异常值",
	/*explain*/	"异常标识",
	/*bmp inx*/	0,
	/*bmp num*/	0,
	/*type*/	SDT_TEXT,
	/*default*/	0,
	/*state*/	ArgMark::AS_NONE,
		},
			{
		/*name*/	"回调函数",
		/*explain*/	"必须为逻辑型且只有一个文本型参数的函数,返回真则代表异常已经被处理,否则会暂停程序",
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
		/*ccname*/  ("注册异常处理函数"),
		/*egname*/  ("catch_ception"),
		/*explain*/ ("仅允许在主线程调用一次!!!"),
		/*category*/11,
		/*state*/     NULL,
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
	pRetData->m_bool = ThrowException(str.empty() ? "未定义异常值" : str.data());  

}

FucInfo Fn_throw_ception = { {
		/*ccname*/  ("抛出异常"),
		/*egname*/  ("throw_ception"),
		/*explain*/ ("抛出指定异常"),
		/*category*/11,
		/*state*/     NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,efn_throw_ception ,"efn_throw_ception" };