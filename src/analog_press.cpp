#include"ElibHelp.h"
static ARG_INFO SimulateKeyArg[] =
{
	  { "�����ֵ", "����Ϊ��ֵ��������ansi unicode����",0 , 0,  DATA_TYPE::_SDT_ALL, NULL, NULL },
};

static BYTE MyVkKeyScanExA(MDATA_INF pArgInf) {
	HKL hKl = GetKeyboardLayout(0);
	BYTE ret = 0;
	//�ı���
	if (pArgInf.m_dtDataType == DATA_TYPE::SDT_TEXT) {
		if (strlen(pArgInf.m_pText) > 0)
		{
			ret = static_cast<BYTE>(VkKeyScanExA(pArgInf.m_pText[0], hKl));
		}
	}//���ַ�
	else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BIN) {
		std::wstring Ebin = std::wstring(elibstl::args_to_wsdata(&pArgInf, 0));
		if (!Ebin.empty()) {
			ret = static_cast<BYTE>(VkKeyScanExW(Ebin[0], hKl));
		}
	}
	else {//�ֽڡ�������������
		ret = pArgInf.m_byte;
	}
	return ret;
}


EXTERN_C void Fn_analog_press(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	BYTE a = 0;
	//ȡ��ֵ
	if (pArgInf[0].m_dtDataType) {

		a = MyVkKeyScanExA(pArgInf[0]);
	}
	keybd_event(a, 0, 0, 0);
}
EXTERN_C void Fn_analog_up(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	BYTE a = 0;
	//ȡ��ֵ
	if (pArgInf[0].m_dtDataType) {

		a = MyVkKeyScanExA(pArgInf[0]);
	}
	keybd_event(a, 0, KEYEVENTF_KEYUP, 0);
}
FucInfo analog_press = { {
		/*ccname*/  ("ģ�ⰴ��"),
		/*egname*/  (""),
		/*explain*/ ("�����ڶ��λ��Ҫͬʱ����ʱ��ģ�ⰴ���޷�ģ��������ʹ��"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  SimulateKeyArg,
	} ,Fn_analog_press ,"Fn_analog_press" };


FucInfo analog_up = { {
		/*ccname*/  ("ģ�ⵯ��"),
		/*egname*/  (""),
		/*explain*/ ("�����ڶ��λ��Ҫͬʱ����ʱ��ģ�ⰴ���޷�ģ��������ʹ��"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  SimulateKeyArg,
	} ,Fn_analog_up ,"Fn_analog_up" };