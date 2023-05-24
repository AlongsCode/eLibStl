#include"ElibHelp.h"
#include"MiniCo/coroutine.h"

static LIB_DATA_TYPE_ELEMENT* m_hCoprocess = nullptr;
static LIB_DATA_TYPE_ELEMENT* m_hCoroutine = nullptr;
namespace elibstl {
	LIB_DATA_TYPE_INFO hCoprocessD = {
		  "Э�̾��", "hCoprocess", "Э��ӳ��Ķ���ID", NULL, NULL, NULL,NULL ,NULL , NULL,NULL , NULL, NULL, 0,nullptr ,
	};
	LIB_DATA_TYPE_INFO hCoroutine = {
		  "Э�̵�����", "hCoroutine", "����Э�̵����л�", NULL, NULL, NULL,NULL ,NULL , NULL,NULL , NULL, NULL, 0,nullptr ,
	};
}




namespace elibcoroutine {
	static void* create_coroutine(PFIBER_START_ROUTINE func, void* arg) {
		//�Ƚ��߳�ת��ΪЭ�̣���ֹ�߳���û��ת��Э��ʱ�л�Э��
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
	//��׼���ò��ˣ���ķ�����
	//#include <functional>
	//void* create_coroutine(void* func, void* arg) {
	//	std::function<void()> fn = std::bind((void(*)(void*))func, arg);
	//	auto pfn_fiber = [](void* pfn) -> void
	//	{
	//		std::function<void()>* fn = (std::function<void()>*)pfn;
	//		(*fn)();
	//	};
	//	void* coroutine_fiber = CreateFiber(0, (LPFIBER_START_ROUTINE)pfn_fiber, new std::function<void()>(fn));
	//	if (coroutine_fiber == nullptr) {
	//		return nullptr;
	//	}
	//	return coroutine_fiber;
	//}
}
static ARG_INFO createArgs[] =
{
	{
		/*name*/    "Э�̵�����",
		/*explain*/ ("�ɡ�����Э�̵����������ء�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::DTP_HCOROUTINE,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "�ӳ����ַ",
		/*explain*/ ("��ִ�е��ӳ���ָ��,����ԭ�ͱ���Ϊ��[�޷���ֵ] ����([������]Э�̵�����,[������]����)��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "����",
		/*explain*/ ("�����ӳ���Ĳ���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   NULL,
	}
};


EXTERN_C void Fn_create_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto pSchedule = reinterpret_cast<schedule*>(pArgInf->m_pCompoundData);
	auto Fun = reinterpret_cast<coroutine_func>(pArgInf[1].m_int);
	void* arg = reinterpret_cast<void*>(pArgInf[2].m_int);
	pRetData->m_pCompoundData = reinterpret_cast<void*>(coroutine_new(pSchedule, Fun, arg));
}
FucInfo create_coroutine = { {
		/*ccname*/  ("����Э��"),
		/*egname*/  ("create_coroutine"),
		/*explain*/ ("��ָ���������м���Э��,Э�����������̣߳�������Э�̾��.���������Ǻ���ִ�пɼ�¼������c��Ŀ纯����ת�����Ǹ���ȫ�ɿ���ͬһ����������ӵ�ж��Э�̣����ڵ������жԺ���Э�̽����л����л�֮���¼Э��ִ��λ�ã��´������Э��ʱ��Ȼ�Ӽ�¼λ��ִ�С�"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::DTP_HCOPROCESS ,
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
		/*name*/    "Э�̵�����",
		/*explain*/ ("�ɡ�����Э�̵����������ء�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::DTP_HCOROUTINE,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "Э�̾��",
		/*explain*/ ("�ɴ���Э�����ɵ�Э�̾��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::DTP_HCOPROCESS,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_switch_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto pSchedule = reinterpret_cast<schedule*>(pArgInf->m_pCompoundData);
	int ID = reinterpret_cast<int>(pArgInf[1].m_pCompoundData);
	coroutine_resume(pSchedule, ID);
}
FucInfo switch_coroutine = { {
		/*ccname*/  ("�ָ�Э��"),
		/*egname*/  ("coroutine_resume"),
		/*explain*/ ("�ָ�ָ�������Э�̡�"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/    DATA_TYPE::_SDT_NULL ,
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
		/*name*/    "Э�̵�����",
		/*explain*/ ("�ɴ���Э�̵��������ɵľ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::DTP_HCOROUTINE,
		/*default*/ 0,
		/*state*/   0,
	}
};

EXTERN_C void Fn_is_valid_hCoprocess(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	coroutine_yield(reinterpret_cast<schedule*>(pArgInf[0].m_pCompoundData));
}
FucInfo is_valid_hCoprocess = { {
		/*ccname*/  ("����Э��"),
		/*egname*/  ("coroutine_yield"),
		/*explain*/ ("�һ�ָ���������ĵ�ǰЭ�̡�"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_hCo_args,
	} ,Fn_is_valid_hCoprocess ,"Fn_is_valid_hCoprocess" };



EXTERN_C void Fn_delete_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto pSchedule = reinterpret_cast<schedule*>(pArgInf->m_pCompoundData);
	int ID = reinterpret_cast<int>(pArgInf[1].m_pCompoundData);
	pRetData->m_int = coroutine_status(pSchedule, ID);
}
FucInfo delete_coroutine = { {
		/*ccname*/  ("ȡЭ��״̬"),
		/*egname*/  ("coroutine_status"),
		/*explain*/ ("����ָ��Э�̵�������ָ��Э�̵�״̬��"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/  m_Args,
	} ,Fn_delete_coroutine ,"Fn_delete_coroutine" };


EXTERN_C void Fn_get_h_coroutine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pCompoundData = reinterpret_cast<void*>(coroutine_running(reinterpret_cast<schedule*>(pArgInf->m_pCompoundData)));
}

FucInfo get_h_coroutine = { {
		/*ccname*/  ("ȡ��ǰЭ�̾��"),
		/*egname*/  ("get_h_coroutine"),
		/*explain*/ ("����ָ���������������е�Э�̡�"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::DTP_HCOPROCESS ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  m_hCo_args,
	} ,Fn_get_h_coroutine ,"Fn_get_h_coroutine" };




EXTERN_C void Fn_coroutine_open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pCompoundData = coroutine_open();
}

FucInfo e_coroutine_open = { {
		/*ccname*/  ("����Э�̵�����"),
		/*egname*/  ("coroutine_open"),
		/*explain*/ ("����������һ���µ�Э�̵�������"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::DTP_HCOROUTINE ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_coroutine_open ,"Fn_coroutine_open" };



EXTERN_C void Fn_coroutine_close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	coroutine_close(reinterpret_cast<schedule*>(pArgInf->m_pCompoundData));
}

FucInfo e_coroutine_close = { {
		/*ccname*/  ("�ͷ�Э�̵�����"),
		/*egname*/  ("coroutine_close"),
		/*explain*/ ("�رղ��ͷ�Э�̵�������"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::_SDT_NULL ,
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
		/*name*/    "Э�̵�����ָ��",
		/*explain*/ ("���ݽ���Э�̵ĵ�����ָ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_hCoi2h(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pCompoundData = (reinterpret_cast<void*>(pArgInf->m_int));
}

FucInfo e_hCoi2h = { {
		/*ccname*/  ("ָ�뵽������"),
		/*egname*/  ("hCoi2h"),
		/*explain*/ ("��Э�̺��������ָ��תΪ��������"),
		/*category*/9,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::DTP_HCOROUTINE ,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ m_hCo_int_args,
	} ,Fn_hCoi2h ,"Fn_hCoi2h" };



