#include"ElibHelp.h"




EXTERN_C void Fn_GetClipBoardTextW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) {
		return;
	}

	if (!OpenClipboard(NULL)) {
		return;
	}

	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
	if (hClipboardData == NULL) {
		CloseClipboard();
		return;
	}

	LPCWSTR pClipboardData = (LPCWSTR)GlobalLock(hClipboardData);
	if (pClipboardData == NULL) {
		CloseClipboard();
		return;
	}

	std::wstring text(pClipboardData);
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	pRetData->m_pBin = elibstl::clone_textw(text);
}

FucInfo get_clip_board_text_w = { {
		/*ccname*/  ("È¡¼ô¼­°åÎÄ±¾W"),
		/*egname*/  (""),
		/*explain*/ (""),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  0,
	} ,Fn_GetClipBoardTextW ,"Fn_GetClipBoardTextW" };
