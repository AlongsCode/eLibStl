#include"ElibHelp.h"
static LIB_DATA_TYPE_ELEMENT* m_hCoprocess;
namespace libkrnln {
	LIB_DATA_TYPE_INFO hCoprocessD = {
		  "协程句柄", "hCoprocess", "协程映射的对象，可用协程句柄是否有效来判断", NULL, NULL, NULL,NULL ,NULL , NULL,NULL , NULL, NULL, 0,m_hCoprocess ,
	};
}
#define DTP_HCOPROCESS   MAKELONG (5, 0) 
namespace elibcoroutine {
	static void* create_coroutine(PFIBER_START_ROUTINE func, void* arg) {
		//先将线程转换为协程，防止线程在没有转换协程时切换协程
		ConvertThreadToFiber(NULL);;
		if (IsBadCodePtr((FARPROC)func)) {
			return NULL;
		}
		void* coroutine_fiber = CreateFiber(0, func, arg);
		if (coroutine_fiber == NULL) {
			return NULL;
		}
		return coroutine_fiber;
	}
	//标准库用不了，妈的烦死了
	//#include <functional>
	//void* create_coroutine(void* func, void* arg) {
	//	std::function<void()> fn = std::bind((void(*)(void*))func, arg);
	//	auto pfn_fiber = [](void* pfn) -> void
	//	{
	//		std::function<void()>* fn = (std::function<void()>*)pfn;
	//		(*fn)();
	//	};
	//	void* coroutine_fiber = CreateFiber(0, (LPFIBER_START_ROUTINE)pfn_fiber, new std::function<void()>(fn));
	//	if (coroutine_fiber == NULL) {
	//		return NULL;
	//	}
	//	return coroutine_fiber;
	//}
}
static ARG_INFO createArgs[] =
{
	{
		/*name*/    "子程序指针",
		/*explain*/ ("欲执行的子程序指针"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_SUB_PTR,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "参数",
		/*explain*/ ("传入子程序的参数"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void Fn_create_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	PFIBER_START_ROUTINE    Fun = reinterpret_cast<PFIBER_START_ROUTINE>(pArgInf[0].m_dwSubCodeAdr);
	auto arg = elibkrnln::args_to_data<INT>(pArgInf, 1);
	void* hCoprocess = elibcoroutine::create_coroutine(Fun, reinterpret_cast<void*>((arg.has_value() ? arg.value() : 0)));
	if (hCoprocess)
	{
		pRetData->m_pCompoundData = hCoprocess;
	}
}
FucInfo create_coroutine = { {
		/*ccname*/  ("创建协程"),
		/*egname*/  ("create_coroutine"),
		/*explain*/ ("返回协程句柄，可通过 \"协程句柄是否有效()\"来判断协程是否创建成功,协程是轻量级线程，他的优势是函数执行可记录，类似c里的跨函数跳转，但是更安全可靠，同一个线程可拥有多个协程，每条线程可跳转不同协程，跳转之后记录协程执行位置，下次跳入此协程时仍然从记录位置执行。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DTP_HCOPROCESS ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  &createArgs[0],
	} ,Fn_create_coroutine ,"Fn_create_coroutine" };

static ARG_INFO m_Args[] =
{
	{
		/*name*/    "协程句柄",
		/*explain*/ ("由创建协程生成的协程句柄"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DTP_HCOPROCESS,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_switch_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	void* hCoprocess = pArgInf[0].m_pCompoundData;
	if (!hCoprocess) return;
	SwitchToFiber(hCoprocess);
}
FucInfo switch_coroutine = { {
		/*ccname*/  ("切换协程"),
		/*egname*/  ("switch_coroutine"),
		/*explain*/ ("切换当前线程至指定协程"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     NULL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_Args,
	} ,Fn_switch_coroutine ,"Fn_switch_coroutine" };


EXTERN_C void Fn_is_valid_hCoprocess(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = pArgInf[0].m_pCompoundData != nullptr;
}
FucInfo is_valid_hCoprocess = { {
		/*ccname*/  ("协程句柄是否有效"),
		/*egname*/  ("is_valid_hCoprocess"),
		/*explain*/ ("用来判断协程是否创建或者销毁成功"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_Args,
	} ,Fn_is_valid_hCoprocess ,"Fn_is_valid_hCoprocess" };

static ARG_INFO m_delete_Args[] =
{
	{
		/*name*/    "协程句柄",
		/*explain*/ ("由创建协程生成的协程句柄"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DTP_HCOPROCESS,
		/*default*/ 0,
		/*state*/   AS_RECEIVE_VAR,
	}
};

EXTERN_C void Fn_delete_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	LPVOID* hCoprocess = pArgInf[0].m_ppCompoundData;
	if (!*hCoprocess) return;
	DeleteFiber(*hCoprocess);
	*hCoprocess = nullptr;
}
FucInfo delete_coroutine = { {
		/*ccname*/  ("销毁协程"),
		/*egname*/  ("delete_coroutine"),
		/*explain*/ ("销毁指定协程,可通过 \"协程句柄是否有效()\"来判断协程是否销毁成功"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     NULL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_Args,
	} ,Fn_delete_coroutine ,"Fn_delete_coroutine" };


EXTERN_C void Fn_get_h_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	void* ret = ConvertThreadToFiber(NULL);;
	if (!ret)
	{
		ret = GetCurrentFiber();
	}

	pRetData->m_pCompoundData = ret;
}

FucInfo get_h_coroutine = { {
		/*ccname*/  ("取当前函数协程句柄"),
		/*egname*/  ("get_h_coroutine"),
		/*explain*/ ("获取当前函数所在协程的句柄,用于指定协程之间的切换,可通过 \"协程句柄是否有效()\"来判断是否获取成功"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DTP_HCOPROCESS ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_get_h_coroutine ,"Fn_get_h_coroutine" };

