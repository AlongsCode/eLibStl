#include"ElibHelp.h"
#include <algorithm>

static ARG_INFO Args[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ ("��ת��ȫ�ǵ��ı�"),
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
		result.reserve(s.size());//���ַ�win��2��linux3Ϊ�̶���������ǰ���룬��ֹÿ��ƴ��ʱ�����ڴ�,string����������Ϊ����Ϊ���ַ�
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
		/*ccname*/  ("��ȫ��W"),
		/*egname*/  ("tofullW"),
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
	} , Fn_tofullW ,"Fn_tofullW" };

