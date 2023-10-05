#include <sstream>  
#include <iomanip>
#include"ElibHelp.h"



static ARG_INFO Args[] =
{
		{
		/*name*/	"要等待的时间(毫秒)",
		/*explain*/	"提示：1000毫秒等于1秒。",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT64,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE,
			}
};








EXTERN_C void Fn_e_delay(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf[0].m_int <= 0) return;
	auto iEnd = ::GetTickCount64() + pArgInf[0].m_int64;
	while (1)
	{
		elibstl::NotifySys(NRS_DO_EVENTS, 0, 0);
		elibstl::NotifySys(NRS_DO_EVENTS, 0, 0);
		if (::GetTickCount64() > iEnd) break;

		elibstl::NotifySys(NRS_DO_EVENTS, 0, 0);
		elibstl::NotifySys(NRS_DO_EVENTS, 0, 0);
	}


}

FucInfo _e_delay = { {
		/*ccname*/  ("延迟Ex"),
		/*egname*/  ("delay"),
		/*explain*/ ("同延迟的高精度版"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_e_delay ,"Fn_e_delay" };

