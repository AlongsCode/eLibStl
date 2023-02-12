#include"ElibHelp.h"
static ARG_INFO SimulateKeyArg[] =
{
	  { "虚拟键值", "可以为键值，键名等ansi unicode均可",0 , 0,  _SDT_ALL, NULL, NULL },
};

static BYTE MyVkKeyScanExA(MDATA_INF pArgInf) {
	HKL hKl = GetKeyboardLayout(0);
	BYTE ret = 0;
	//文本型
	if (pArgInf.m_dtDataType == SDT_TEXT) {
		if (strlen(pArgInf.m_pText) > 0)
		{
			ret = static_cast<BYTE>(VkKeyScanExA(pArgInf.m_pText[0], hKl));
		}
	}//宽字符
	else if (pArgInf.m_dtDataType == SDT_BIN) {
		std::wstring Ebin = std::wstring(elibstl::args_to_wsdata(&pArgInf, 0));
		if (!Ebin.empty()) {
			ret = static_cast<BYTE>(VkKeyScanExW(Ebin[0], hKl));
		}
	}
	else {//字节、整数、短整数
		ret = pArgInf.m_byte;
	}
	return ret;
}


EXTERN_C void Fn_analog_press(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	BYTE a = 0;
	//取键值
	if (pArgInf[0].m_dtDataType) {

		a = MyVkKeyScanExA(pArgInf[0]);
	}
	keybd_event(a, 0, 0, 0);
}
EXTERN_C void Fn_analog_up(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	BYTE a = 0;
	//取键值
	if (pArgInf[0].m_dtDataType) {

		a = MyVkKeyScanExA(pArgInf[0]);
	}
	keybd_event(a, 0, KEYEVENTF_KEYUP, 0);
}
FucInfo analog_press = { {
		/*ccname*/  ("模拟按下"),
		/*egname*/  (""),
		/*explain*/ ("对于在多键位需要同时按下时，模拟按键无法模拟的情况下使用"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  SimulateKeyArg,
	} ,Fn_analog_press ,"Fn_analog_press" };


FucInfo analog_up = { {
		/*ccname*/  ("模拟弹起"),
		/*egname*/  (""),
		/*explain*/ ("对于在多键位需要同时按下时，模拟按键无法模拟的情况下使用"),
		/*category*/6,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  SimulateKeyArg,
	} ,Fn_analog_up ,"Fn_analog_up" };