#include"ElibHelp.h"
#include"MiniCo/coroutine.h"

//static LIB_DATA_TYPE_ELEMENT* m_hCoprocess = nullptr;
//static LIB_DATA_TYPE_ELEMENT* m_hCoroutine = nullptr;
namespace elibstl {
	LIB_DATA_TYPE_INFO hCoprocessD = {
		  "协程句柄", "hCoprocess", "协程映射的对象ID", NULL, NULL, LDT_IS_HIDED,NULL ,NULL , NULL,NULL , NULL, NULL, 0,nullptr ,
	};
	LIB_DATA_TYPE_INFO hCoroutine = {
		  "协程调度器", "hCoroutine", "用于协程调度切换", NULL, NULL, LDT_IS_HIDED,NULL ,NULL , NULL,NULL , NULL, NULL, 0,nullptr ,
	};
}

static ARG_INFO createArgs[] =
{
	{
		/*name*/    "协程调度器句柄",
		/*explain*/ ("由“创建协程调度器”返回。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	},
	{
		/*name*/    "子程序地址",
		/*explain*/ ("欲执行的子程序指针,函数原型必须为“[无返回值] 函数([整数型]协程调度器,[整数型]参数)”"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_SUB_PTR,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "参数",
		/*explain*/ ("传入子程序的参数"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_create_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto pSchedule = reinterpret_cast<schedule*>(pArgInf->m_int);
	auto Fun = reinterpret_cast<coroutine_func>(pArgInf[1].m_pdwSubCodeAdr);
	void* arg = reinterpret_cast<void*>(pArgInf[2].m_int);
	pRetData->m_int = coroutine_new(pSchedule, Fun, arg);
}
FucInfo create_coroutine = { {
		/*ccname*/  ("加入协程"),
		/*egname*/  ("create_coroutine"),
		/*explain*/ ("在指定调度器中加入协程并返回协程ID,协程是轻量级线程，并返回协程句柄.他的优势是函数执行可记录，类似c里的跨函数跳转，但是更安全可靠，同一个调度器可拥有多个协程，可在调度器中对函数协程进行切换，切换之后记录协程执行位置，下次切入此协程时仍然从记录位置执行。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     SDT_INT ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  &createArgs[0],
	} ,Fn_create_coroutine ,"Fn_create_coroutine" };

static ARG_INFO m_Args[] =
{
	{
		/*name*/    "协程调度器句柄",
		/*explain*/ ("由“创建协程调度器”返回。"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "协程ID",
		/*explain*/ ("由创建协程生成的协程句柄"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_switch_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto pSchedule = reinterpret_cast<schedule*>(pArgInf->m_int);
	coroutine_resume(pSchedule, pArgInf[1].m_int);
}
FucInfo switch_coroutine = { {
		/*ccname*/  ("恢复协程"),
		/*egname*/  ("coroutine_resume"),
		/*explain*/ ("恢复指定ID的协程。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  m_Args,
	} ,Fn_switch_coroutine ,"Fn_switch_coroutine" };



static ARG_INFO m_hCo_args[] =
{
	{
		/*name*/    "协程调度器句柄",
		/*explain*/ ("由创建协程调度器生成的句柄"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_is_valid_hCoprocess(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	coroutine_yield(reinterpret_cast<schedule*>(pArgInf->m_int));
}
FucInfo is_valid_hCoprocess = { {
		/*ccname*/  ("挂起协程"),
		/*egname*/  ("coroutine_yield"),
		/*explain*/ ("挂机指定调度器的当前正在执行的协程。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_hCo_args,
	} ,Fn_is_valid_hCoprocess ,"Fn_is_valid_hCoprocess" };



EXTERN_C void Fn_delete_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto pSchedule = reinterpret_cast<schedule*>(pArgInf->m_int);
	pRetData->m_int = coroutine_status(pSchedule, pArgInf[1].m_int);
}
FucInfo delete_coroutine = { {
		/*ccname*/  ("取协程状态"),
		/*egname*/  ("coroutine_status"),
		/*explain*/ ("返回指定协程调度器的指定协程的状态。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DTP_COROUTINE ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  m_Args,
	} ,Fn_delete_coroutine ,"Fn_delete_coroutine" };


EXTERN_C void Fn_get_h_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = coroutine_running(reinterpret_cast<schedule*>(pArgInf->m_int));
}

FucInfo get_h_coroutine = { {
		/*ccname*/  ("取当前执行协程ID"),
		/*egname*/  ("get_h_coroutine"),
		/*explain*/ ("返回指定调度器正在运行的协程ID。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     SDT_INT ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_hCo_args,
	} ,Fn_get_h_coroutine ,"Fn_get_h_coroutine" };


/*创建协程调度器*/
EXTERN_C void Fn_coroutine_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = reinterpret_cast<std::uintptr_t> (coroutine_open());
}
FucInfo e_coroutine_open = { {
		/*ccname*/  ("创建协程调度器"),
		/*egname*/  ("coroutine_open"),
		/*explain*/ ("创建并返回一个新的协程调度器句柄。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     SDT_INT ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_coroutine_open ,"Fn_coroutine_open" };


/*销毁协程调度器*/
EXTERN_C void Fn_coroutine_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	coroutine_close(reinterpret_cast<schedule*>(pArgInf->m_int));
}
FucInfo e_coroutine_close = { {
		/*ccname*/  ("销毁协程调度器"),
		/*egname*/  ("coroutine_close"),
		/*explain*/ ("关闭并释放协程调度器。"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     _SDT_NULL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_hCo_args,
	} ,Fn_coroutine_close ,"Fn_coroutine_close" };


static ARG_INFO m_hCo_int_args[] =
{
	{
		/*name*/    "协程调度器指针",
		/*explain*/ ("传递进入协程的调度器指针"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};


EXTERN_C void Fn_hCoi2h(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pCompoundData = (reinterpret_cast<void*>(pArgInf->m_int));
}

FucInfo e_hCoi2h = { {
		/*ccname*/  ("指针到调度器"),
		/*egname*/  ("hCoi2h"),
		/*explain*/ ("将协程函数传入的指针转为调度器。"),
		/*category*/9,
		/*state*/   CT_IS_HIDED,
		/*ret*/     SDT_INT ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ m_hCo_int_args,
	} ,Fn_hCoi2h ,"Fn_hCoi2h" };



static LIB_DATA_TYPE_ELEMENT s_Enum[] =
{
	 {SDT_INT, 0, "结束", "COROUTINE_DEAD", NULL, LES_HAS_DEFAULT_VALUE, COROUTINE_DEAD},
	 {SDT_INT, 0, "就绪", "COROUTINE_READY", NULL, LES_HAS_DEFAULT_VALUE, COROUTINE_READY},
	 {SDT_INT, 0, "运行中", "COROUTINE_RUNNING", NULL, LES_HAS_DEFAULT_VALUE,COROUTINE_RUNNING},
	 {SDT_INT, 0, "被挂起", "COROUTINE_SUSPEND", NULL, LES_HAS_DEFAULT_VALUE, COROUTINE_SUSPEND},
};
namespace elibstl {
	LIB_DATA_TYPE_INFO COROUTINE_Type =
	{
		"协程状态",
		"COROUTINE",
		"当前协程运行状态",
		NULL,
		NULL,
		_DT_OS(__OS_WIN) | LDT_ENUM,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		sizeof(s_Enum) / sizeof(s_Enum[0]),
		s_Enum
	};
}