#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "文本",
		/*explain*/ ("欲转换Unicode的文本"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};



EXTERN_C void efn_trim_leading_zeros(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring result = elibstl::args_to_wsdata(pArgInf, 0).data();
	auto pos = result.find_first_not_of(L'0'); // 找到第一个非零字符的位置
	if (pos != std::wstring::npos)
	{
		result.erase(0, pos); // 删除左侧无用的零
	}
	// 如果存在小数点，则删除结尾的零和小数点
	if (auto pos_dot = result.find_last_of(L'.'); pos_dot != std::wstring::npos)
	{
		// 找到最后一个非零数字的位置
		auto pos_nonzero = result.find_last_not_of(L'0');
		// 如果最后一个非零数字位于小数点之前，则将小数点一起删除
		if (pos_nonzero < pos_dot)
		{
			result.erase(pos_dot, std::wstring::npos);
		}
		// 如果最后一个非零数字位于小数点之后，则仅删除结尾的零字符
		else
		{
			result.erase(pos_nonzero + 1, std::wstring::npos);
		}
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}

FucInfo g_trim_leading_zeros = { {
		/*ccname*/  ("删数值文本左侧无效零W"),
		/*egname*/  ("trim_leading_zeros"),
		/*explain*/ ("删数值文本左侧无效零"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,efn_trim_leading_zeros ,"efn_trim_leading_zeros" };