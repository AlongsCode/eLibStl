#include"ElibHelp.h"
static ARG_INFO Args[] =
{
	{
		/*name*/    "��ת�����ֽڼ�",
		/*explain*/ ("��ת�����ֽڼ�"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

template <typename T>
inline std::basic_string<T> byte_array_to_string(const std::vector<unsigned char>& byte_vector) {
	if (byte_vector.empty()) {
		return std::basic_string<T>();
	}

	const size_t length = byte_vector.size();
	std::vector<T> buffer(length * 4 + sizeof("{}"));

	size_t buffer_index = 0;
	buffer[buffer_index++] = '{';

	for (const auto byte : byte_vector) {
		auto hundreds = byte / 100;
		auto tens = byte % 100 / 10;
		auto ones = byte % 10;

		if (hundreds > 0) {
			buffer[buffer_index++] = hundreds + T('0');
			buffer[buffer_index++] = tens + T('0');
		}
		else if (tens > 0) {
			buffer[buffer_index++] = tens + T('0');
		}
		buffer[buffer_index++] = ones + T('0');
		buffer[buffer_index++] = ',';
	}
	buffer[buffer_index - 1] = '}';

	return std::basic_string<T>(buffer.data(), buffer_index);
}



EXTERN_C void efn_byte_array_to_wstring(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	auto bin = elibstl::arg_to_vdata(pArgInf, 0);
	if (!bin.empty()) {
		pRetData->m_pBin = elibstl::clone_textw(byte_array_to_string<wchar_t>(bin));
	}
}

FucInfo g_byte_array_to_wstring = { {
		/*ccname*/  ("�ֽڼ���ʮ�����ı�W"),
		/*egname*/  ("byte_array_to_wstring"),
		/*explain*/ ("���ֽڼ�ת��Ϊ�ı���ʽ,����\"����\"����"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,efn_byte_array_to_wstring ,"efn_byte_array_to_wstring" };
EXTERN_C void efn_byte_array_to_string(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	auto bin = elibstl::arg_to_vdata(pArgInf, 0);
	if (!bin.empty()) {
		pRetData->m_pText = elibstl::clone_text(byte_array_to_string<char>(bin));
	}
}
FucInfo g_byte_array_to_string = { {
		/*ccname*/  ("�ֽڼ���ʮ�����ı�A"),
		/*egname*/  ("byte_array_to_string"),
		/*explain*/ ("���ֽڼ�ת��Ϊ�ı���ʽ,����\"����\"����"),
		/*category*/2,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_TEXT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,efn_byte_array_to_string ,"efn_byte_array_to_string" };

