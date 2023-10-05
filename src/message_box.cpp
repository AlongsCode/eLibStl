#include"ElibHelp.h"


static ARG_INFO Args[] =
{
	{
		/*name*/    "提示信息",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_RECEIVE_ALL_TYPE_DATA,
	},
	{
		/*name*/    "按钮",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "窗口标题",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/    ArgMark::AS_RECEIVE_ALL_TYPE_DATA | ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "父窗口",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "留存时间",
		/*explain*/ ("指定时长后自动关闭，默认为不自动关闭,单位:毫秒"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};



EXTERN_C int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);

EXTERN_C void Fn_MessageBoxW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const auto text = elibstl::arg_to_wstring(pArgInf[0]);
	auto button = elibstl::args_to_data<INT>(pArgInf, 1);
	const auto title = elibstl::arg_to_wstring(pArgInf[2]);
	auto hpwnd = elibstl::args_to_data<INT>(pArgInf, 3);
	auto time = elibstl::args_to_data<INT>(pArgInf, 4);
	const HWND hOldFocusWnd = ::GetFocus();
	INT nResult;
	if (time.has_value() && time.value() >= 0) {
		nResult = ::MessageBoxTimeoutW(reinterpret_cast<HWND>(hpwnd.has_value() ? hpwnd.value() : 0), text.c_str(), title.c_str(), button.has_value() ? button.value() : 0, 0, time.value());
	}
	else
	{
		nResult = ::MessageBoxW(reinterpret_cast<HWND>(hpwnd.has_value() ? hpwnd.value() : 0), text.c_str(), title.c_str(), button.has_value() ? button.value() : 0);
	}

	if (hOldFocusWnd != NULL && ::IsWindow(hOldFocusWnd)) {
		::SetFocus(hOldFocusWnd);
	}
	pRetData->m_int = nResult - 1;
}

FucInfo message_box_w = { {
		/*ccname*/  ("信息框W"),
		/*egname*/  (""),
		/*explain*/ ("支持unicode的信息框,以及延迟时间"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/5,
		/*arg lp*/  &Args[0],
	} ,Fn_MessageBoxW ,"Fn_MessageBoxW" };
