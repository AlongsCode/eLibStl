#include <sstream>  
#include <iomanip>
#include"ElibHelp.h"



static ARG_INFO Args[] =
{
		{
		/*name*/	"Ҫ�ȴ���ʱ��(����)",
		/*explain*/	"��ʾ��1000�������1�롣",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_INT64,
		/*default*/	0,
		/*state*/	0,
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
		/*ccname*/  ("�ӳ�Ex"),
		/*egname*/  ("delay"),
		/*explain*/ ("ͬ�ӳٵĸ߾��Ȱ�"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_e_delay ,"Fn_e_delay" };

