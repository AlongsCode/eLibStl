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
		/*type*/	SDT_INT64,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE,
			}
};








namespace {
	void ProcessMessagesImproved() {
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE) && msg.message != WM_QUIT) {
			if (GetMessage(&msg, nullptr, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

}

EXTERN_C void Fn_e_delay(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (pArgInf[0].m_int64 <= 0) return;
	const auto hTimer = ::CreateWaitableTimerW(NULL, FALSE, NULL);
	if (hTimer == NULL)  return;
	LARGE_INTEGER liDueTime{};
	liDueTime.QuadPart = static_cast<std::uint64_t>(-10000) * static_cast<std::uint64_t>(pArgInf[0].m_int64);
	if (::SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE))
	{
		while (true)
		{
			const auto dwResult = ::MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLEVENTS);
			if (dwResult == WAIT_FAILED || dwResult == WAIT_OBJECT_0)
				break;
			ProcessMessagesImproved();
		}
	}
	::CloseHandle(hTimer);
}

FucInfo _e_delay = { {
		/*ccname*/  ("�����ӳ�"),
		/*egname*/  ("delay"),
		/*explain*/ ("ͬ�ӳٵĸ߾��Ȱ�"),
		/*category*/6,
		/*state*/    NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_e_delay ,"Fn_e_delay" };

