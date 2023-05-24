#include"ElibHelp.h"


static ARG_INFO Args[] =
{
	{
		/*name*/    "��ʾ��Ϣ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA,
	},
	{
		/*name*/    "��ť",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "���ڱ���",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "����ʱ��",
		/*explain*/ ("ָ��ʱ�����Զ��رգ�Ĭ��Ϊ���Զ��ر�,��λ:����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
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
		/*ccname*/  ("��Ϣ��W"),
		/*egname*/  (""),
		/*explain*/ ("֧��unicode����Ϣ��,�Լ��ӳ�ʱ��"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/5,
		/*arg lp*/  &Args[0],
	} ,Fn_MessageBoxW ,"Fn_MessageBoxW" };
