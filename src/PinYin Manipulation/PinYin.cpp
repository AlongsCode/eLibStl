#include"ElibHelp.h"
#include"TransPingYin.h"/*拼音字典*/
#include <unordered_map>
#include <sstream>
#include <mutex>
namespace elibstl {
	/*这里为什么不拆分几个cpp是因为没必要了，几百K的字典都打包了，还差这点obj的体积?*/
	//extern const unsigned char g_pPinYinData[];

	class Pinyin {
	public:
		using PinyinMap = std::unordered_map<std::wstring, std::vector<std::wstring>>;
		static PinyinMap pinyinMap;
		static std::mutex pinyinMapMutex;  // 互斥锁用于保护 pinyinMap 的写入操作

		/*取拼音*/
		static std::wstring get_py(const std::wstring& hanzi, size_t index) {
			if (hanzi.empty() || !iswalpha(hanzi[0])) {
				// 如果输入为空或首字符不是汉字，则返回0
				return L"";
			}

			// 判断是否初始化了
			if (pinyinMap.empty()) {
				// 如果映射表还未初始化，则返回空字符串
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}

			auto it = pinyinMap.find(hanzi.substr(0, 1));
			/*易中索引减1*/
			if (it != pinyinMap.end() && index >= 1 && index <= it->second.size()) {
				return it->second[index - 1];
			}

			return L""; // 返回空字符串表示未找到对应的拼音
		}
		/*取拼音数目*/
		static size_t get_py_count(const std::wstring& hanzi) {
			if (hanzi.empty()) {
				// 如果输入为空或首字符不是汉字，则返回空
				return 0;
			}

			// 使用你的拼音映射表来获取对应汉字的拼音列表
			std::vector<std::wstring> pinyinList = get_all_py(hanzi.substr(0, 1));

			// 返回拼音列表的大小即为发音数目
			return pinyinList.size();
		}

		/*取所有拼音*/
		static std::vector<std::wstring> get_all_py(const std::wstring& hanzi) {
			// 判断是否初始化了
			if (pinyinMap.empty()) {
				// 如果映射表还未初始化，则返回空字符串
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

		/*取声母*/
		static std::wstring get_py_sm(const std::wstring& hanzi, size_t index) {
			if (hanzi.empty()) {
				return L"";
			}
			// 判断是否初始化了
			if (pinyinMap.empty()) {
				// 如果映射表还未初始化，则返回空字符串
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}

			auto it = pinyinMap.find(hanzi);
			if (it != pinyinMap.end() && index >= 1 && index <= it->second.size()) {
				const std::wstring& pinyin = it->second[index - 1];
				if (pinyin.size() < 1) {
					return L""; // 没有声母
				}
				// 获取声母部分
				std::wstring sm;
				if (pinyin.substr(0, 2) == L"zh" || pinyin.substr(0, 2) == L"ch" || pinyin.substr(0, 2) == L"sh") {
					sm = pinyin.substr(0, 2);
				}
				else {
					sm = pinyin.substr(0, 1);
				}
				return sm;
			}

			return L""; // 返回空文本表示无效的汉字或索引
		}

		/*取韵母*/
		static std::wstring get_py_ym(const std::wstring& hanzi, size_t index) {
			if (hanzi.empty()) {
				return L"";
			}
			// 判断是否初始化了
			if (pinyinMap.empty()) {
				// 如果映射表还未初始化，则返回空字符串
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}

			auto it = pinyinMap.find(hanzi);
			if (it != pinyinMap.end() && index >= 1 && index <= it->second.size()) {
				const std::wstring& pinyin = it->second[index - 1];
				auto sm_size = get_py_sm(hanzi, index).size();
				if (pinyin.size() < sm_size)/*小于声母的长度一定没有声母*/
				{
					return L"";
				}
				return pinyin.substr(sm_size); // 提取从索引 声母之后的第一个字符开始的子字符串作为韵母部分

			}

			return L""; // 返回空文本表示无效的汉字或索引
		}

		/*比较拼音*/
		static bool comp_py(const std::wstring& text1, const std::wstring& text2, bool supportSouthern = true, bool fuzzyComparison = false) {
			if (text1.empty() || text2.empty())
			{
				return false;
			}
			if (pinyinMap.empty()) {
				// 如果映射表还未初始化，则返回空字符串
				buildPinyinMap(reinterpret_cast<const wchar_t*>(elibstl::g_pPinYinData));
			}


			// 获取文本的拼音列表
			std::vector<std::wstring> pinyinList1 = GetPinyinList(text1, pinyinMap, supportSouthern);
			std::vector<std::wstring> pinyinList2 = GetPinyinList(text2, pinyinMap, supportSouthern);

			if (fuzzyComparison) {
				// 模糊比较
				for (const auto& pinyin : pinyinList1) {
					if (StartsWith(pinyinList2, pinyin)) {
						return true;
					}
				}
			}
			else {
				// 精确比较
				return (pinyinList1 == pinyinList2);
			}

			return false;
		}
		/*输入字比较*/
		static bool comp_py_code(const std::wstring& pinyinInput, const std::wstring& normalText, bool supportSouthernAccent, int pinyinInputCategory) {
			// 处理首拼及全拼类别
			if (pinyinInputCategory != ':' && pinyinInputCategory != ';') {
				// 检查是否匹配全拼
				if (normalText.find(pinyinInput) != std::wstring::npos) {
					return true;
				}

				// 检查是否匹配首拼
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

			// 处理双拼类别
			if (pinyinInputCategory == ':') {
				std::wstring doublePinyin;
				size_t inputLength = pinyinInput.length();
				size_t textLength = normalText.length();

				// 双拼匹配逻辑
				if (inputLength % 2 == 0 && inputLength <= textLength) {
					bool match = true;
					for (size_t i = 0; i < inputLength; i += 2) {
						wchar_t ch1 = std::tolower(pinyinInput[i]);
						wchar_t ch2 = std::tolower(pinyinInput[i + 1]);

						// 检查是否匹配双拼
						if (i + 1 < textLength && normalText[i] == ch1 && normalText[i + 1] == ch2) {
							continue;
						}

						// 如果不匹配，则标记为不匹配并结束循环
						match = false;
						break;
					}
					if (match) {
						return true;
					}
				}
			}

			// 处理自动判别类别
			if (pinyinInputCategory != ':' && pinyinInputCategory != ';') {
				// 检查是否匹配全拼
				if (normalText.find(pinyinInput) != std::wstring::npos) {
					return true;
				}

				// 检查是否匹配首拼
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
						// 支持南方音，将相近的发音视为相同
						for (const auto& pinyin : characterPinyinList) {
							pinyinList.push_back(AdjustPinyin(pinyin));
						}
					}
					else {
						// 不支持南方音，保留原始发音
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
			/*主要是nl不分，zzh不分,iue不分*/
			std::wstring adjustedPinyin = pinyin;

			if (adjustedPinyin.length() > 0) {
				// 处理南方音的发音调整
				if (adjustedPinyin[0] == L'n') {
					// 将 n 转换为 l
					adjustedPinyin[0] = L'l';
				}
				else if (adjustedPinyin[0] == L'z') {
					// 将 z 转换为 zh
					adjustedPinyin[0] = L'z';
					adjustedPinyin.insert(1, L"h");
				}
				else if (adjustedPinyin[0] == L'i' && adjustedPinyin.length() > 1 && adjustedPinyin[1] == L'e') {
					// 将 ie 转换为 ue
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
		/*有效性不会验证，因为全部来自字典*/
		//static std::wstring GetInitial(const std::wstring& pinyin) {
		//	if (pinyin.empty()) {
		//		return L"";
		//	}
		//	wchar_t ch = std::tolower(pinyin[0]); // 将拼音的首字母转换为小写
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
		//	return L""; // 返回空文本表示无效的拼音
		//}


		static void buildPinyinMap(const wchar_t* data) {
			if (!pinyinMap.empty()) {
				// 如果映射表已经初始化过，则直接返回
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

					// 移除换行符
					pinyin.erase(std::remove(pinyin.begin(), pinyin.end(), L'\n'), pinyin.end());
					pinyin.erase(std::remove(pinyin.begin(), pinyin.end(), L'\r'), pinyin.end());

					// 解析拼音字符串，按逗号分隔多个拼音
					std::vector<std::wstring> pinyinList;
					size_t startPos = 0;
					size_t commaPos = pinyin.find(L",", startPos);
					while (commaPos != std::wstring::npos) {
						std::wstring singlePinyin = pinyin.substr(startPos, commaPos - startPos);
						pinyinList.push_back(singlePinyin);

						startPos = commaPos + 1;
						commaPos = pinyin.find(L",", startPos);
					}

					// 处理最后一个拼音
					std::wstring lastPinyin = pinyin.substr(startPos);
					pinyinList.push_back(lastPinyin);

					// 将汉字及对应的拼音列表插入映射表中
					pinyinMap[hanzi] = pinyinList;
				}
			}
		}



	};

	// 拼音的全局变量定义
	Pinyin::PinyinMap Pinyin::pinyinMap;
	std::mutex Pinyin::pinyinMapMutex;
}






static ARG_INFO Args1[] =
{
	{
		"欲取其拼音编码的汉字",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个成员数目为 0 的空文本数组",
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
		/*ccname*/  ("取所有发音W"),
		/*egname*/  ("get_all_py"),
		/*explain*/ ("返回包含指定汉字所有拼音编码的文本数组（支持多音字）。返回的数组结果可以用“复制数组”命令保存到同类型数组变量。本命令为初级命令。"),
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
		"欲取其拼音的汉",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个成员数目为 0 的空文本数组",
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
		/*ccname*/  ("取发音数目W"),
		/*egname*/  ("get_py_count"),
		/*explain*/ ("返回指定汉字的发音数目。"),
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
		"欲取其拼音编码的汉字",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个空文本。",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},
	{
		"欲取拼音编码的索引",
		"只取用文本首部的第一个汉字，如果该文本首部不为国标汉字，命令将返回一个空文本。",
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
		/*ccname*/  ("取拼音W"),
		/*egname*/  ("get_py_count"),
		/*explain*/ ("返回包含指定汉字的指定拼音编码的文本。如果该指定拼音编码不存在，将返回空文本。目前仅支持国标汉字。多音字的第一个发音为常用音。同易完全相同"),
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
		/*ccname*/  ("取声母W"),
		/*egname*/  ("get_py_sm"),
		/*explain*/ ("返回包含指定汉字的指定拼音编码的文本。如果该指定拼音编码不存在，将返回空文本。目前仅支持国标汉字。多音字的第一个发音为常用音。同易完全相同"),
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
		/*ccname*/  ("取韵母W"),
		/*egname*/  ("get_py_ym"),
		/*explain*/ ("返回包含指定汉字指定拼音编码的韵母部分文本。如果指定拼音编码不存在或该汉字此发音无声母，将返回空文本。"),
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
		"待比较文本一",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},{
		"待比较文本二",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},
	{
		"是否支持南方音",
		"初始值为“真”。为真则支持南方音。如果支持南方音，比较时将认为所有相近的发音都相同。如： n 和 l、 z 和 zh、 ie 和 ue 等等",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		1,
		AS_HAS_DEFAULT_VALUE,
	},
	{
		"是否为模糊比较",
		"本参数为真时，当待比较文本一的发音在待比较文本二的首部被包容时即认为比较通过。如果被省略，默认值为假。",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		0,
		AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo g_comp_py = { {
		/*ccname*/  ("发音比较W"),
		/*egname*/  ("comp_py"),
		/*explain*/ ("比较两段文本的发音，如果发音相同返回真，否则返回假。对于文本中的非国标汉字部分，将仅进行简单的值比较。"),
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
		"待比较文本一",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},{
		"待比较文本二",
		"",
		0,
		0,
		DATA_TYPE::SDT_BIN,
		0,
		NULL,
	},
	{
		"是否支持南方音",
		"初始值为“真”。为真则支持南方音。如果支持南方音，比较时将认为所有相近的发音都相同。如： n 和 l、 z 和 zh、 ie 和 ue 等等",
		0,
		0,
		DATA_TYPE::SDT_BOOL,
		1,
		AS_HAS_DEFAULT_VALUE,
	},
	{
		"拼音输入字类别",
		"可以被省略。参数值可以为以下常量之一： 1、#首拼及全拼； 2、#双拼； 3、#自动判别。 如果省略本参数，默认为“#自动判别",
		0,
		0,
		DATA_TYPE::SDT_INT,
		0,
		AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
FucInfo g_comp_py_code = { {
		/*ccname*/  ("输入字比较W"),
		/*egname*/  ("comp_py_code"),
		/*explain*/ ("比较两段文本的发音，如果发音相同返回真，否则返回假。对于文本中的非国标汉字部分，将仅进行简单的值比较。"),
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