#include"ElibHelp.h"
EXTERN_C void Fn_LoadWindows(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto parent_pCwnd = pArgInf[1].m_dtDataType == DATA_TYPE::_SDT_NULL ? nullptr : reinterpret_cast<void*>(elibstl::NotifySys(NRS_GET_UNIT_PTR, pArgInf[1].m_uint, 0));
	struct 
	{
		HUNIT m_uint{ 0 };
		void* m_pCwnd{ nullptr };
		BOOL m_bModal{ TRUE };
	}windata{ pArgInf->m_uint ,parent_pCwnd , pArgInf[2].m_bool };
	if (!elibstl::NotifySys(2005, reinterpret_cast<size_t>(&windata), 0))
		pRetData->m_bool = TRUE;

}


static ARG_INFO Args[] =
{
	{
		/*name*/    "窗口",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/     DATA_TYPE::KRNLN_WIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE
	},
	{
		/*name*/    "父窗口",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::KRNLN_WIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY
	},
	{
		/*name*/    "模态载入",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BOOL,
		/*default*/ TRUE,
		/*state*/   ArgMark::AS_HAS_DEFAULT_VALUE
	}
};
FucInfo e_load_windows = { {
		/*ccname*/  ("载入窗口"),
		/*egname*/  ("LoadWindows"),
		/*explain*/ ("载入窗口"),
		/*category*/10,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/  Args,
	} ,Fn_LoadWindows ,"Fn_LoadWindows" };
