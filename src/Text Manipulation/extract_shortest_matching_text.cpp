#include"ElibHelp.h"
#include <algorithm>


inline void extract_shortest_matching_text(std::vector<LPBYTE>& aryText, const std::wstring& wanna, const std::wstring& left_str, const std::wstring& right_str)
{

	size_t start_place = 0;

	if (left_str.empty() || right_str.empty()) {
		return; // �����߻��ұߵ��ַ���Ϊ�գ���ֱ�ӷ��ؿյĽ��
	}

	while (start_place != std::wstring::npos) {

		start_place = wanna.find(left_str, start_place);
		if (start_place == std::wstring::npos) {
			break; // ����Ҳ�����ߵ��ַ����������ѭ��
		}

		start_place += left_str.length();
		size_t end_place = wanna.find(right_str, start_place);

		if (end_place != std::wstring::npos) {

			aryText.push_back(elibstl::clone_textw(wanna.substr(start_place, end_place - start_place)));
			start_place = end_place + right_str.length();
		}
	}
};

inline void  extract_shortest_matching_text(std::vector<LPBYTE>& aryText, const std::wstring& wanna, const std::wstring& left_str, const std::wstring& right_str, const size_t& count)
{

	size_t start_place = 0;

	if (left_str.empty() || right_str.empty()) {
		return; // �����߻��ұߵ��ַ���Ϊ�գ���ֱ�ӷ��ؿյĽ��
	}

	while (start_place != std::wstring::npos) {
		if (aryText.size() >= count) {
			break;
		}

		start_place = wanna.find(left_str, start_place);
		if (start_place == std::wstring::npos) {
			break; // ����Ҳ�����ߵ��ַ����������ѭ��
		}

		start_place += left_str.length();
		size_t end_place = wanna.find(right_str, start_place);

		if (end_place != std::wstring::npos) {
			aryText.push_back(elibstl::clone_textw(wanna.substr(start_place, end_place - start_place)));
			start_place = end_place + right_str.length();
		}
	}
}

static ARG_INFO WArgs[] =
{
	{
		/*name*/    "��ȡ���ı�",
		/*explain*/ ("�������ֵ��һ������Ϊ����ı����򷵻�һ�������飬��û���κγ�Ա������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "����ı�",
		/*explain*/ ("����1:���ƥ����ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/    NULL,
	},
	{
		/*name*/    "�ұ��ı�",
		/*explain*/ ("����2:�ұ�ƥ����ı�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	},
	{
		/*name*/    "����ȡ����",
		/*explain*/ ("-1��Ϊ��ʱ������"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   AS_DEFAULT_VALUE_IS_EMPTY,
	}
};

EXTERN_C void efn_extract_shortest_matching_text(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	std::wstring
		text = elibstl::args_to_wsdata(pArgInf, 0).data(),
		left = elibstl::args_to_wsdata(pArgInf, 1).data(),
		right = elibstl::args_to_wsdata(pArgInf, 2).data();
	size_t size = static_cast<size_t>(elibstl::args_to_data<INT>(pArgInf, 3).value_or(-1));
	std::vector<LPBYTE> ret;

	if (size == static_cast<size_t>(-1))
	{

		extract_shortest_matching_text(ret, text, left, right);
	}
	else
	{
		extract_shortest_matching_text(ret, text, left, right, size);
	}


	pRetData->m_pAryData = elibstl::create_array<LPBYTE>(ret.data(), ret.size());

}

FucInfo g_extract_shortest_matching_text = { {
		/*ccname*/  ("ȡ�м��ı�W"),
		/*egname*/  ("extract_shortest_matching_text"),
		/*explain*/ ("��ȡ�ı��м��кܴ�����,ͨ��ǰ��(����)�ı���ȡ���������ƥ��Ҫ����м��ı������ƾ���ģ���\"�ı�_ȡ�м�\""),
		/*category*/2,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/4,
		/*arg lp*/  &WArgs[0],
	} ,efn_extract_shortest_matching_text ,"efn_extract_shortest_matching_text" };



