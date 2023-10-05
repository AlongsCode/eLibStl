#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲转换半角的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};




EXTERN_C void Fn_tohalfW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto text = elibstl::args_to_wsdata(pArgInf, 0);
	if (text.empty())
		return;

	std::wstring result;
	result.reserve(text.size());

	for (const auto& it: text)
	{
		auto upChar = static_cast<int>(it);

		if (upChar == 0x3000)
		{
			result.push_back(L' ');
		}
		else if (upChar >= 65281 && upChar <= 65374)
		{
			result.push_back(static_cast<wchar_t>(upChar - 65248));
		}
		else
		{
			result.push_back(it);
		}
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}
FucInfo   to_half_w = { {
		/*ccname*/  ("到半角W"),
		/*egname*/  ("tohalfW"),
		/*explain*/ ("转换指定文本为全角。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_tohalfW ,"Fn_tohalfW" };

