#include"ElibHelp.h"
#include"TransPingYin.h"/*ƴ���ֵ�*/
#include <unordered_map>
#include <sstream>
#include <mutex>
namespace elibstl {
	/*����Ϊʲô����ּ���cpp����Ϊû��Ҫ�ˣ�����K���ֵ䶼����ˣ��������obj�����?*/
	//extern const unsigned char g_pPinYinData[];

	class Pinyin {
	public:
		using PinyinMap = std::unordered_map<std::wstring, std::vector<std::wstring>>;
		static PinyinMap pinyinMap;
		static std::mutex pinyinMapMutex;  // ���������ڱ��� pinyinMap ��д�����

		/*ȡƴ��*/
		static std::wstring get_py(const std::wstring& hanzi, size_t index) {
			if (hanzi.empty() || !iswalpha(hanzi[0])) {
				// �������Ϊ�ջ����ַ����Ǻ��֣��򷵻�0
				return L"";
			}

			// �ж��Ƿ��ʼ����
			if (pinyinMap.empty()) {
				// ���ӳ���δ��ʼ�����򷵻ؿ��ַ���
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}

			auto it = pinyinMap.find(hanzi.substr(0, 1));
			/*����������1*/
			if (it != pinyinMap.end() && index >= 1 && index <= it->second.size()) {
				return it->second[index - 1];
			}

			return L""; // ���ؿ��ַ�����ʾδ�ҵ���Ӧ��ƴ��
		}
		/*ȡƴ����Ŀ*/
		static size_t get_py_count(const std::wstring& hanzi) {
			if (hanzi.empty()) {
				// �������Ϊ�ջ����ַ����Ǻ��֣��򷵻ؿ�
				return 0;
			}

			// ʹ�����ƴ��ӳ�������ȡ��Ӧ���ֵ�ƴ���б�
			std::vector<std::wstring> pinyinList = get_all_py(hanzi.substr(0, 1));

			// ����ƴ���б�Ĵ�С��Ϊ������Ŀ
			return pinyinList.size();
		}

		/*ȡ����ƴ��*/
		static std::vector<std::wstring> get_all_py(const std::wstring& hanzi) {
			// �ж��Ƿ��ʼ����
			if (pinyinMap.empty()) {
				// ���ӳ���δ��ʼ�����򷵻ؿ��ַ���
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}
			std::vector<std::wstring> pinyinList;

			if (!hanzi.empty()) {
				auto it = pinyinMap.find(hanzi.substr(0, 1));
				if (it != pinyinMap.end()) {
					pinyinList = it->second;
				}
			}

			return pinyinList;
		}

		/*ȡ��ĸ*/
		static std::wstring get_py_sm(const std::wstring& hanzi, size_t index) {
			if (hanzi.empty()) {
				return L"";
			}
			// �ж��Ƿ��ʼ����
			if (pinyinMap.empty()) {
				// ���ӳ���δ��ʼ�����򷵻ؿ��ַ���
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}

			auto it = pinyinMap.find(hanzi);
			if (it != pinyinMap.end() && index >= 1 && index <= it->second.size()) {
				const std::wstring& pinyin = it->second[index - 1];
				if (pinyin.size() < 1) {
					return L""; // û����ĸ
				}
				// ��ȡ��ĸ����
				std::wstring sm;
				if (pinyin.substr(0, 2) == L"zh" || pinyin.substr(0, 2) == L"ch" || pinyin.substr(0, 2) == L"sh") {
					sm = pinyin.substr(0, 2);
				}
				else {
					sm = pinyin.substr(0, 1);
				}
				return sm;
			}

			return L""; // ���ؿ��ı���ʾ��Ч�ĺ��ֻ�����
		}

		/*ȡ��ĸ*/
		static std::wstring get_py_ym(const std::wstring& hanzi, size_t index) {
			if (hanzi.empty()) {
				return L"";
			}
			// �ж��Ƿ��ʼ����
			if (pinyinMap.empty()) {
				// ���ӳ���δ��ʼ�����򷵻ؿ��ַ���
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}

			auto it = pinyinMap.find(hanzi);
			if (it != pinyinMap.end() && index >= 1 && index <= it->second.size()) {
				const std::wstring& pinyin = it->second[index - 1];
				auto sm_size = get_py_sm(hanzi, index).size();
				if (pinyin.size() < sm_size)/*С����ĸ�ĳ���һ��û����ĸ*/
				{
					return L"";
				}
				return pinyin.substr(sm_size); // ��ȡ������ ��ĸ֮��ĵ�һ���ַ���ʼ�����ַ�����Ϊ��ĸ����

			}

			return L""; // ���ؿ��ı���ʾ��Ч�ĺ��ֻ�����
		}

		/*�Ƚ�ƴ��*/
		static bool comp_py(const std::wstring& text1, const std::wstring& text2, bool supportSouthern = true, bool fuzzyComparison = false) {
			if (text1.empty() || text2.empty())
			{
				return false;
			}
			if (pinyinMap.empty()) {
				// ���ӳ���δ��ʼ�����򷵻ؿ��ַ���
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}


			// ��ȡ�ı���ƴ���б�
			std::vector<std::wstring> pinyinList1 = GetPinyinList(text1, pinyinMap, supportSouthern);
			std::vector<std::wstring> pinyinList2 = GetPinyinList(text2, pinyinMap, supportSouthern);

			if (fuzzyComparison) {
				// ģ���Ƚ�
				for (const auto& pinyin : pinyinList1) {
					if (StartsWith(pinyinList2, pinyin)) {
						return true;
					}
				}
			}
			else {
				// ��ȷ�Ƚ�
				return (pinyinList1 == pinyinList2);
			}

			return false;
		}
		/*�����ֱȽ�*/
		static bool comp_py_code(const std::wstring& pinyinInput, const std::wstring& normalText, bool supportSouthernAccent, int pinyinInputCategory) {
			// ������ƴ��ȫƴ���
			if (pinyinInputCategory != ':' && pinyinInputCategory != ';') {
				// ����Ƿ�ƥ��ȫƴ
				if (normalText.find(pinyinInput) != std::wstring::npos) {
					return true;
				}

				// ����Ƿ�ƥ����ƴ
				std::wstring firstPinyin;
				for (wchar_t ch : pinyinInput) {
					if (std::isupper(ch)) {
						firstPinyin += std::tolower(ch);
					}
				}
				if (normalText.find(firstPinyin) != std::wstring::npos) {
					return true;
				}
			}

			// ����˫ƴ���
			if (pinyinInputCategory == ':') {
				std::wstring doublePinyin;
				size_t inputLength = pinyinInput.length();
				size_t textLength = normalText.length();

				// ˫ƴƥ���߼�
				if (inputLength % 2 == 0 && inputLength <= textLength) {
					bool match = true;
					for (size_t i = 0; i < inputLength; i += 2) {
						wchar_t ch1 = std::tolower(pinyinInput[i]);
						wchar_t ch2 = std::tolower(pinyinInput[i + 1]);

						// ����Ƿ�ƥ��˫ƴ
						if (i + 1 < textLength && normalText[i] == ch1 && normalText[i + 1] == ch2) {
							continue;
						}

						// �����ƥ�䣬����Ϊ��ƥ�䲢����ѭ��
						match = false;
						break;
					}
					if (match) {
						return true;
					}
				}
			}

			// �����Զ��б����
			if (pinyinInputCategory != ':' && pinyinInputCategory != ';') {
				// ����Ƿ�ƥ��ȫƴ
				if (normalText.find(pinyinInput) != std::wstring::npos) {
					return true;
				}

				// ����Ƿ�ƥ����ƴ
				std::wstring firstPinyin;
				for (wchar_t ch : pinyinInput) {
					if (std::isupper(ch)) {
						firstPinyin += std::tolower(ch);
					}
				}
				if (normalText.find(firstPinyin) != std::wstring::npos) {
					return true;
				}
			}

			return false;
		}
	private:

		static std::vector<std::wstring> GetPinyinList(const std::wstring& text, const PinyinMap& pinyinMap, bool supportSouthern) {
			std::vector<std::wstring> pinyinList;

			for (const auto& character : text) {
				std::wstring hanzi(1, character);
				auto it = pinyinMap.find(hanzi);
				if (it != pinyinMap.end()) {
					const std::vector<std::wstring>& characterPinyinList = it->second;
					if (supportSouthern) {
						// ֧���Ϸ�����������ķ�����Ϊ��ͬ
						for (const auto& pinyin : characterPinyinList) {
							pinyinList.push_back(AdjustPinyin(pinyin));
						}
					}
					else {
						// ��֧���Ϸ���������ԭʼ����
						pinyinList.insert(pinyinList.end(), characterPinyinList.begin(), characterPinyinList.end());
					}
				}
			}

			return pinyinList;
		}

		static bool StartsWith(const std::vector<std::wstring>& pinyinList, const std::wstring& targetPinyin) {
			for (const auto& pinyin : pinyinList) {
				if (pinyin.compare(0, targetPinyin.length(), targetPinyin) == 0) {
					return true;
				}
			}
			return false;
		}

		static std::wstring AdjustPinyin(const std::wstring& pinyin) {
			/*��Ҫ��nl���֣�zzh����,iue����*/
			std::wstring adjustedPinyin = pinyin;

			if (adjustedPinyin.length() > 0) {
				// �����Ϸ����ķ�������
				if (adjustedPinyin[0] == L'n') {
					// �� n ת��Ϊ l
					adjustedPinyin[0] = L'l';
				}
				else if (adjustedPinyin[0] == L'z') {
					// �� z ת��Ϊ zh
					adjustedPinyin[0] = L'z';
					adjustedPinyin.insert(1, L"h");
				}
				else if (adjustedPinyin[0] == L'i' && adjustedPinyin.length() > 1 && adjustedPinyin[1] == L'e') {
					// �� ie ת��Ϊ ue
					adjustedPinyin[0] = L'u';
					adjustedPinyin[1] = L'e';
				}
			}

			return adjustedPinyin;
		}
		/*static std::wstring GetInitial(const std::wstring& pinyin) {
			static const std::wstring initials = L"bpmfdtnlgkhjqxrzcsyw";

			if (pinyin.empty()) {
				return L"";
			}

			wchar_t firstChar = pinyin[0];
			if (initials.find(firstChar) != std::wstring::npos) {
				return std::wstring(1, firstChar);
			}
			else if (firstChar == L'w') {
				if (pinyin.size() >= 2 && pinyin[1] == L'v') {
					return L"w";
				}
				else {
					return L"";
				}
			}
			else if (firstChar == L'y') {
				if (pinyin.size() >= 2 && pinyin[1] == L'u') {
					return L"y";
				}
				else {
					return L"";
				}
			}
			else {
				return L"";
			}
		}*/
		/*��Ч�Բ�����֤����Ϊȫ�������ֵ�*/
		//static std::wstring GetInitial(const std::wstring& pinyin) {
		//	if (pinyin.empty()) {
		//		return L"";
		//	}
		//	wchar_t ch = std::tolower(pinyin[0]); // ��ƴ��������ĸת��ΪСд
		//	switch (ch) {
		//	case L'b':
		//	case L'p':
		//	case L'm':
		//	case L'f':
		//	case L'd':
		//	case L't':
		//	case L'n':
		//	case L'l':
		//	case L'g':
		//	case L'k':
		//	case L'h':
		//	case L'j':
		//	case L'q':
		//	case L'x':
		//	case L'r':
		//	case L'z':
		//	case L'c':
		//	case L's':
		//		return std::wstring(1, ch);
		//	case L'y':
		//		if (pinyin.size() >= 2) {
		//			wchar_t ch2 = std::tolower(pinyin[1]);
		//			if (ch2 == L'i' || ch2 == L'a' || ch2 == L'u') {
		//				return L"y";
		//			}
		//		}
		//		break;
		//	case L'w':
		//		if (pinyin.size() >= 2) {
		//			wchar_t ch2 = std::tolower(pinyin[1]);
		//			if (ch2 == L'a' || ch2 == L'o') {
		//				return L"w";
		//			}
		//		}
		//		break;
		//	}
		//	return L""; // ���ؿ��ı���ʾ��Ч��ƴ��
		//}


		static void buildPinyinMap(const wchar_t* data) {
			if (!pinyinMap.empty()) {
				// ���ӳ����Ѿ���ʼ��������ֱ�ӷ���
				return;
			}

			std::wistringstream iss(data);
			std::wstring line;
			while (std::getline(iss, line)) {
				std::wstring hanzi;
				std::wstring pinyin;

				size_t delimiterPos = line.find(L":");
				if (delimiterPos != std::wstring::npos) {
					hanzi = line.substr(0, delimiterPos);

					pinyin = line.substr(delimiterPos + 1);

					// �Ƴ����з�
					pinyin.erase(std::remove(pinyin.begin(), pinyin.end(), L'\n'), pinyin.end());
					pinyin.erase(std::remove(pinyin.begin(), pinyin.end(), L'\r'), pinyin.end());

					// ����ƴ���ַ����������ŷָ����ƴ��
					std::vector<std::wstring> pinyinList;
					size_t startPos = 0;
					size_t commaPos = pinyin.find(L",", startPos);
					while (commaPos != std::wstring::npos) {
						std::wstring singlePinyin = pinyin.substr(startPos, commaPos - startPos);
						pinyinList.push_back(singlePinyin);

						startPos = commaPos + 1;
						commaPos = pinyin.find(L",", startPos);
					}

					// �������һ��ƴ��
					std::wstring lastPinyin = pinyin.substr(startPos);
					pinyinList.push_back(lastPinyin);

					// �����ּ���Ӧ��ƴ���б����ӳ�����
					pinyinMap[hanzi] = pinyinList;
				}
			}
		}



	};

	// ƴ����ȫ�ֱ�������
	Pinyin::PinyinMap Pinyin::pinyinMap;
	std::mutex Pinyin::pinyinMapMutex;
}






static ARG_INFO Args1[] =
{
	{
		"��ȡ��ƴ������ĺ���",
		"ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ����Ա��ĿΪ 0 �Ŀ��ı�����",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	}
};
EXTERN_C void efn_get_all_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pAryData = elibstl::create_text_array(elibstl::Pinyin::get_all_py(elibstl::args_to_wsdata(pArgInf, 0).data()));
}

FucInfo g_get_all_py = { {
		/*ccname*/  ("ȡ���з���W"),
		/*egname*/  ("get_all_py"),
		/*explain*/ ("���ذ���ָ����������ƴ��������ı����飨֧�ֶ����֣������ص������������á��������顱����浽ͬ�������������������Ϊ�������"),
		/*category*/16,
		/*state*/   CT_RETRUN_ARY_TYPE_DATA,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args1) / sizeof(Args1[0]),
		/*arg lp*/  Args1,
	} ,efn_get_all_py ,"efn_get_all_py" };



static ARG_INFO Args2[] =
{
	{
		"��ȡ��ƴ���ĺ�",
		"ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ����Ա��ĿΪ 0 �Ŀ��ı�����",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	}
};
EXTERN_C void efn_get_py_count(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = elibstl::Pinyin::get_py_count(elibstl::args_to_wsdata(pArgInf, 0).data());
}

FucInfo g_get_py_count = { {
		/*ccname*/  ("ȡ������ĿW"),
		/*egname*/  ("get_py_count"),
		/*explain*/ ("����ָ�����ֵķ�����Ŀ��"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args2) / sizeof(Args2[0]),
		/*arg lp*/  Args2,
	} ,efn_get_py_count ,"efn_get_py_count" };


static ARG_INFO Args3[] =
{
	{
		"��ȡ��ƴ������ĺ���",
		"ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ�����ı���",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},
	{
		"��ȡƴ�����������",
		"ֻȡ���ı��ײ��ĵ�һ�����֣�������ı��ײ���Ϊ���꺺�֣��������һ�����ı���",
		0,
		0,
		DATA_TYPE::SDT_INT,
		1,
		AS_HAS_DEFAULT_VALUE,
	}
};
EXTERN_C void efn_get_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pBin = elibstl::clone_textw(elibstl::Pinyin::get_py(elibstl::args_to_wsdata(pArgInf, 0).data(), elibstl::args_to_data<INT>(pArgInf, 1).value_or(1)));
}

FucInfo g_get_py = { {
		/*ccname*/  ("ȡƴ��W"),
		/*egname*/  ("get_py_count"),
		/*explain*/ ("���ذ���ָ�����ֵ�ָ��ƴ��������ı��������ָ��ƴ�����벻���ڣ������ؿ��ı���Ŀǰ��֧�ֹ��꺺�֡������ֵĵ�һ������Ϊ��������ͬ����ȫ��ͬ"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/    DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args3) / sizeof(Args3[0]),
		/*arg lp*/  Args3,
	} ,efn_get_py ,"efn_get_py" };



EXTERN_C void efn_get_py_sm(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pBin = elibstl::clone_textw(elibstl::Pinyin::get_py_sm(elibstl::args_to_wsdata(pArgInf, 0).data(), elibstl::args_to_data<INT>(pArgInf, 1).value_or(1)));
}

FucInfo g_get_py_sm = { {
		/*ccname*/  ("ȡ��ĸW"),
		/*egname*/  ("get_py_sm"),
		/*explain*/ ("���ذ���ָ�����ֵ�ָ��ƴ��������ı��������ָ��ƴ�����벻���ڣ������ؿ��ı���Ŀǰ��֧�ֹ��꺺�֡������ֵĵ�һ������Ϊ��������ͬ����ȫ��ͬ"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args3) / sizeof(Args3[0]),
		/*arg lp*/  Args3,
	} ,efn_get_py_sm ,"efn_get_py_sm" };



EXTERN_C void efn_get_py_ym(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_pBin = elibstl::clone_textw(elibstl::Pinyin::get_py_sm(elibstl::args_to_wsdata(pArgInf, 0).data(), elibstl::args_to_data<INT>(pArgInf, 1).value_or(1)));
}

FucInfo g_get_py_ym = { {
		/*ccname*/  ("ȡ��ĸW"),
		/*egname*/  ("get_py_ym"),
		/*explain*/ ("���ذ���ָ������ָ��ƴ���������ĸ�����ı������ָ��ƴ�����벻���ڻ�ú��ִ˷�������ĸ�������ؿ��ı���"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_INT,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args3) / sizeof(Args3[0]),
		/*arg lp*/  Args3,
	} ,efn_get_py_ym ,"efn_get_py_ym" };




EXTERN_C void efn_comp_py(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = elibstl::Pinyin::comp_py(elibstl::args_to_wsdata(pArgInf, 0).data(), elibstl::args_to_wsdata(pArgInf, 1).data(), elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(FALSE), elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(TRUE));
}
static ARG_INFO Args4[] =
{
	{
		"���Ƚ��ı�һ",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},{
		"���Ƚ��ı���",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},
	{
		"�Ƿ�֧���Ϸ���",
		"��ʼֵΪ���桱��Ϊ����֧���Ϸ��������֧���Ϸ������Ƚ�ʱ����Ϊ��������ķ�������ͬ���磺 n �� l�� z �� zh�� ie �� ue �ȵ�",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		1,
		AS_HAS_DEFAULT_VALUE,
	},
	{
		"�Ƿ�Ϊģ���Ƚ�",
		"������Ϊ��ʱ�������Ƚ��ı�һ�ķ����ڴ��Ƚ��ı������ײ�������ʱ����Ϊ�Ƚ�ͨ���������ʡ�ԣ�Ĭ��ֵΪ�١�",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		0,
		AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo g_comp_py = { {
		/*ccname*/  ("�����Ƚ�W"),
		/*egname*/  ("comp_py"),
		/*explain*/ ("�Ƚ������ı��ķ��������������ͬ�����棬���򷵻ؼ١������ı��еķǹ��꺺�ֲ��֣��������м򵥵�ֵ�Ƚϡ�"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args4) / sizeof(Args4[0]),
		/*arg lp*/  Args4,
	} ,efn_comp_py ,"efn_comp_py" };





EXTERN_C void efn_comp_py_code(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = elibstl::Pinyin::comp_py_code(elibstl::args_to_wsdata(pArgInf, 0).data(), elibstl::args_to_wsdata(pArgInf, 1).data(), elibstl::args_to_data<BOOL>(pArgInf, 1).value_or(FALSE), elibstl::args_to_data<INT>(pArgInf, 1).value_or(3));
}
static ARG_INFO Args5[] =
{
	{
		"���Ƚ��ı�һ",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},{
		"���Ƚ��ı���",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},
	{
		"�Ƿ�֧���Ϸ���",
		"��ʼֵΪ���桱��Ϊ����֧���Ϸ��������֧���Ϸ������Ƚ�ʱ����Ϊ��������ķ�������ͬ���磺 n �� l�� z �� zh�� ie �� ue �ȵ�",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		1,
		AS_HAS_DEFAULT_VALUE,
	},
	{
		"ƴ�����������",
		"���Ա�ʡ�ԡ�����ֵ����Ϊ���³���֮һ�� 1��#��ƴ��ȫƴ�� 2��#˫ƴ�� 3��#�Զ��б� ���ʡ�Ա�������Ĭ��Ϊ��#�Զ��б�",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo g_comp_py_code = { {
		/*ccname*/  ("�����ֱȽ�W"),
		/*egname*/  ("comp_py_code"),
		/*explain*/ ("�Ƚ������ı��ķ��������������ͬ�����棬���򷵻ؼ١������ı��еķǹ��꺺�ֲ��֣��������м򵥵�ֵ�Ƚϡ�"),
		/*category*/16,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/sizeof(Args5) / sizeof(Args5[0]),
		/*arg lp*/  Args5,
	} ,efn_comp_py_code ,"efn_comp_py_code" };