#define NOMINMAX 
#include <stdexcept>
#include <iostream>
#include"ElibHelp.h"
#include <bit> 
static ARG_INFO Args[]
{
		{
		/*name*/	"窗口句柄",
		/*explain*/	"提供欲捕获其显示内容的窗口句柄,如果为0则为捕获屏幕显示内容.",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_INT,
		/*default*/	0,
		/*state*/	ArgMark::AS_HAS_DEFAULT_VALUE,
		},
		{
			/*name*/	"横坐标",
			/*explain*/	R"()",
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	ArgMark::AS_HAS_DEFAULT_VALUE,
},
{
	/*name*/	"纵坐标",
	/*explain*/	R"()",
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	ArgMark::AS_HAS_DEFAULT_VALUE,
}
};





EXTERN_C void fn_get_pixel(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	const auto hwnd = reinterpret_cast<HWND>(pArgInf[0].m_int);
	const auto hDC = ::GetDC(hwnd);
	const auto clr = ::GetPixel(hDC, pArgInf[1].m_int, pArgInf[2].m_int);
	::ReleaseDC(hwnd, hDC);
	pRetData->m_int = clr;
}


FucInfo Fn_get_pixel = { {
		/*ccname*/  ("取坐标颜色"),
		/*egname*/  ("get_pixel"),
		/*explain*/ ("返回指定区域上所指定位置处的颜色值"),
		/*category*/6,
		/*state*/    NULL,
		/*ret*/     SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		ESTLARG(Args)
	} ,ESTLFNAME(fn_get_pixel) };