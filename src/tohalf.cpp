#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ ("��ת����ǵ��ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};
EXTERN_C void Fn_tohalfW(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring_view
		text = elibstl::args_to_wsdata(pArgInf, 0);
	if (text.empty())
		return;

	std::wstring result;
	result.reserve(text.size());

	for (auto it = text.begin(); it != text.end(); ++it)
	{
		const size_t upChar = (size_t)*it;

		if (upChar == 0x3000)
		{
			result += L' ';
		}
		else if (upChar >= 65281 && upChar <= 65374)
		{
			result += (wchar_t)(upChar - 65248);
		}
		else
		{
			result += *it;
		}
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}
FucInfo   to_half_w = { {
		/*ccname*/  ("�����W"),
		/*egname*/  ("tohalfW"),
		/*explain*/ ("ת��ָ���ı�Ϊȫ�ǡ�"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} , Fn_tohalfW ,"Fn_tohalfW" };

