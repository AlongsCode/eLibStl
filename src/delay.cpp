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
		/*ccname*/  ("界面延迟"),
		/*egname*/  ("delay"),
		/*explain*/ ("同延迟的高精度版"),
		/*category*/11,
		/*state*/    NULL,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_e_delay ,"Fn_e_delay" };

