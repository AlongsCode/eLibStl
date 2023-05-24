#include"ElibHelp.h"
#include<commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include"ElibHelp.h"
#include<commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

static ARG_INFO Args[] =
{
	{
		/*name*/    "��ʾ��Ϣ",
		/*explain*/ ("�Խ�С������ʾ����ָ���·�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA,
	},
	{
		/*name*/    "��ʾ����",
		/*explain*/ ("������ʾ����ָ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "��ť",
		/*explain*/ ("��ͨ����ͬλ����ϲ�ͬ��ť��Ĭ��Ϊȷ��,1.ȷ��,2.��,4.��,8.ȡ��(����Ϊ�˶Ի���ָ���˰�ť��������Ӧ alt-F4 ��ת��) �ĵ���ȡ��������),16.����,32.�ر�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "���ڱ���",
		/*explain*/ ("������ʾ�ı���"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::_SDT_ALL,
		/*default*/ 0,
		/*state*/    AS_RECEIVE_ALL_TYPE_DATA | AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "������",
		/*explain*/ ("�����ھ��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "ͼ��",
		/*explain*/ ("Ĭ��Ϊ��ͼ��,����ʾͼ��,Ĭ��Ϊ:��ȷ,0.��,1.����Ի����л���ʾһ������������ͼ��.2.��ԲȦ�е�Сд��ĸ i ��ɵ�ͼ����ʾ������Ի����С�3.����Ի����л���ʾһ����ȫ����ͼ�ꡣ4.����Ի����л���ʾ��̾��ͼ�ꡣĬ��Ϊ1��5.��ȷ��6.����"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

static LIB_DATA_TYPE_ELEMENT s_TaskDialog_Button[] =
{
	 {DATA_TYPE::SDT_INT, 0, "ȷ��", "TDCBF_OK_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_OK_BUTTON},
	 {DATA_TYPE::SDT_INT, 0, "��", "TDCBF_YES_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_YES_BUTTON},
	 {DATA_TYPE::SDT_INT, 0, "��", "TDCBF_NO_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_NO_BUTTON},
	 {DATA_TYPE::SDT_INT, 0, "ȡ��", "TDCBF_CANCEL_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_CANCEL_BUTTON},
	 {DATA_TYPE::SDT_INT, 0, "����", "TDCBF_RETRY_BUTTON", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_RETRY_BUTTON},
	 {DATA_TYPE::SDT_INT, 0, "�ر�", "TDCBF_OK_CLOSE", NULL, LES_HAS_DEFAULT_VALUE, (INT)TDCBF_CLOSE_BUTTON}
};
namespace elibstl {
	LIB_DATA_TYPE_INFO TaskDialog_Button_Type =
	{
		"�߼���Ϣ��ť",
		"TDCBF",
		"�߼���Ϣ��ťֵ",
		NULL,
		NULL,
		_DT_OS(__OS_WIN) | LDT_ENUM,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		sizeof(s_TaskDialog_Button) / sizeof(s_TaskDialog_Button[0]),
		s_TaskDialog_Button
	};
}

EXTERN_C void Fn_TaskDialogW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const PWSTR icon[] = { nullptr,TD_ERROR_ICON,TD_INFORMATION_ICON,TD_SHIELD_ICON,TD_WARNING_ICON , MAKEINTRESOURCEW(-8),MAKEINTRESOURCEW(-7) };
	const auto
		lpContent = elibstl::arg_to_wstring(pArgInf, 0),
		lpTitle = elibstl::arg_to_wstring(pArgInf, 1),
		lpWindowTitle = elibstl::arg_to_wstring(pArgInf, 3);
	auto hwndParent = elibstl::args_to_data<INT>(pArgInf, 4),
		standardButtons = elibstl::args_to_data<INT>(pArgInf, 2),
		inicon = elibstl::args_to_data<INT>(pArgInf, 5);
	PWSTR boxicon = nullptr;
	if (inicon.has_value() && inicon.value() > 0 && inicon.value() <= 6)
	{
		boxicon = icon[inicon.value()];
	}
	//if (standardButtons.has_value())
	//{

	//	switch (standardButtons.value())
	//	{
	//	case 1:
	//		setButton = TDCBF_YES_BUTTON;
	//		break;
	//	case 2:
	//		setButton = TDCBF_NO_BUTTON;
	//		break;
	//	case 3:
	//		setButton = TDCBF_CANCEL_BUTTON;
	//		break;
	//	case 4:
	//		setButton = TDCBF_RETRY_BUTTON;
	//		break;
	//	case 5:
	//		setButton = TDCBF_OK_BUTTON;
	//		break;
	//	default:
	//		setButton = TDCBF_OK_BUTTON;
	//		break;
	//	}
	//}
	int buttonPressed;
	TaskDialog(reinterpret_cast<HWND>(hwndParent.has_value() ? hwndParent.value() : 0), NULL, !lpWindowTitle.empty() ? lpWindowTitle.c_str() : L"��ʾ", lpTitle.c_str(), lpContent.c_str(), standardButtons.has_value() ? standardButtons.value() : TDCBF_OK_BUTTON, boxicon, &buttonPressed);
	switch (buttonPressed) {
	case IDOK:
		pRetData->m_int = TDCBF_OK_BUTTON;
		break;
	case IDCANCEL:
		pRetData->m_int = TDCBF_CANCEL_BUTTON;
		break;
	case IDRETRY:
		pRetData->m_int = TDCBF_RETRY_BUTTON;
		break;
	case IDYES:
		pRetData->m_int = TDCBF_YES_BUTTON;
		break;
	case IDNO:
		pRetData->m_int = TDCBF_NO_BUTTON;
		break;
	case IDCLOSE:
		pRetData->m_int = TDCBF_CLOSE_BUTTON;
		break;
	default:
		pRetData->m_int = -1;
		break;
	}
}

FucInfo task_dialog_w = { {
		/*ccname*/  ("�߼���Ϣ��"),
		/*egname*/  ("TaskDialog"),
		/*explain*/ ("��������ʧ�ܷ���-1,����ɹ�������ö�ٳ���:�߼���Ϣ��ť::"),
		/*category*/13,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/6,
		/*arg lp*/  &Args[0],
	} ,Fn_TaskDialogW ,"Fn_TaskDialogW" };


