#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "�ı�",
		/*explain*/ ("��ת��Unicode���ı�"),
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
	auto pos = result.find_first_not_of(L'0'); // �ҵ���һ�������ַ���λ��
	if (pos != std::wstring::npos)
	{
		result.erase(0, pos); // ɾ��������õ���
	}
	// �������С���㣬��ɾ����β�����С����
	if (auto pos_dot = result.find_last_of(L'.'); pos_dot != std::wstring::npos)
	{
		// �ҵ����һ���������ֵ�λ��
		auto pos_nonzero = result.find_last_not_of(L'0');
		// ������һ����������λ��С����֮ǰ����С����һ��ɾ��
		if (pos_nonzero < pos_dot)
		{
			result.erase(pos_dot, std::wstring::npos);
		}
		// ������һ����������λ��С����֮�����ɾ����β�����ַ�
		else
		{
			result.erase(pos_nonzero + 1, std::wstring::npos);
		}
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}

FucInfo g_trim_leading_zeros = { {
		/*ccname*/  ("ɾ��ֵ�ı������Ч��W"),
		/*egname*/  ("trim_leading_zeros"),
		/*explain*/ ("ɾ��ֵ�ı������Ч��"),
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