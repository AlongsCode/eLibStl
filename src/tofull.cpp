#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲转换全角的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_tofullW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		s = elibstl::args_to_wsdata(pArgInf, 0);
	std::wstring result;
	if (!s.empty()) {
		result.reserve(s.size());//宽字符win下2，linux3为固定，可以提前申请，防止每次拼接时申请内存,string不可以是因为汉字为两字符
		for (const auto& c : s)
		{
			if (c == ' ')
			{
				result += (wchar_t)0x3000;
			}
			else if (c >= 33 && c <= 126)
			{
				result += (wchar_t)(c + 65248);
			}
			else
			{
				result += c;
			}
		}
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}
FucInfo   to_full_w = { {
		/*ccname*/  ("到全角W"),
		/*egname*/  ("tofullW"),
		/*explain*/ ("转换指定文本为全角。"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_tofullW ,"Fn_tofullW" };

