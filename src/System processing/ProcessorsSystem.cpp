#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"
/*�����¼�*/
//void ProcessMessagesImproved() {
//    CWinThread* pWinThread = AfxGetThread();
//    if (pWinThread != nullptr) {
//        MSG msg;
//        while (::PeekMessageW(&msg, nullptr, 0, 0, PM_NOREMOVE) && msg.message != WM_QUIT) {
//            pWinThread->PumpMessage();
//        }
//    }
//}

EXTERN_C void fn_process_messages_improved(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	SYSTEM_INFO si;
	::GetSystemInfo(&si);
	pRetData->m_int = si.dwNumberOfProcessors;
}


FucInfo Fn_process_messages_improved = { {
		/*ccname*/  ("ȡCPU������"),
		/*egname*/  ("process_messages_improved"),
		/*explain*/ ("��ȡCPU������"),
		/*category*/6,
		/*state*/    NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,ESTLFNAME(fn_process_messages_improved)};