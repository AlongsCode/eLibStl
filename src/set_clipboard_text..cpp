#include"ElibHelp.h"
#pragma warning(disable:4996)

static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("需置入剪辑板的uncidoe文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};

EXTERN_C void Fn_SetClipBoardTextW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const std::wstring_view& text = elibstl::args_to_wsdata(pArgInf, 0);
	if (text.empty()) {
		pRetData->m_bool = false;
		return;
	}

	if (!OpenClipboard(NULL)) {
		pRetData->m_bool = false;
		return;
	}
	EmptyClipboard();

	HGLOBAL hClip = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(wchar_t));
	if (hClip == NULL) {
		CloseClipboard();
		pRetData->m_bool = false;
		return;
	}

	LPVOID pClip = GlobalLock(hClip);
	if (pClip == NULL) {
		CloseClipboard();
		GlobalFree(hClip);
		pRetData->m_bool = false;
		return;
	}

	wcscpy((wchar_t*)pClip, std::wstring(text).c_str());
	GlobalUnlock(hClip);
	SetClipboardData(CF_UNICODETEXT, hClip);
	CloseClipboard();

	pRetData->m_bool = true;
}

FucInfo set_clip_board_text_w = { {
		/*ccname*/  ("置剪辑板文本W"),
		/*egname*/  (""),
		/*explain*/ (""),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_SetClipBoardTextW ,"Fn_SetClipBoardTextW" };
