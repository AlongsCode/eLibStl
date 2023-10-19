#include"EplugHelp.h"
#include <regex>
/*****************************************
Unicode预编译
旨在将L()函数转为unicode字节集代码
减少运行时的转换,从而提高代码运行效率
*****************************************/


struct FuncInfo {
    std::string arg_str;
    bool arg_hasEnd;
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

/*将提取出来的字符,转为utf16字节集*/
inline auto ansi2unicodebyte(const FuncInfo& funinfo) -> std::string {
    if (funinfo.arg_str.empty())/*如果是空字符串*/
        return "{  }";
    std::wstring wstr;
    int widesize = MultiByteToWideChar(CP_ACP, 0, funinfo.arg_str.c_str(), -1, NULL, 0);
    if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
        return "{  }";
    if (widesize == 0)
        return "{  }";

    //返回没释放内存，啥比了
    wchar_t* resultstring = new wchar_t[widesize];
    int convresult = MultiByteToWideChar(CP_ACP, 0, funinfo.arg_str.c_str(), -1, resultstring, widesize);

    if (convresult == widesize)
    {
        wstr = resultstring;
    }
    delete[] resultstring;
    std::vector<unsigned char> ret = std::vector<unsigned char>(reinterpret_cast<const unsigned char*>(wstr.data()), reinterpret_cast<const unsigned char*>(wstr.data() + wstr.size()));
    if (funinfo.arg_hasEnd)/*存在结束符*/
    {
        /*添加L'\0',两字节,内存字节集表示为{0,0}*/
        ret.push_back(0);
        ret.push_back(0);
    }
    return  byte_array_to_string<char>(ret);

}

inline std::string ReplaceLstr(const std::string& input) {
    std::string result = input;

    // 使用正则表达式匹配L字符串及其内容

    //std::regex pattern(R"(L\s*\(\s*“([^”]*)”\s*,\s*(真|假)?\s*\))"); //服了,ansi中的“似乎和"编"冲突,更换捕获组,找半天没找到BUG
    std::regex pattern(R"(L\s*\(\s*“(.*?)”\s*,\s*(真|假)?\s*\))");
    std::smatch match;

    while (std::regex_search(result, match, pattern)) {
        if (match.size() == 3) {
            FuncInfo info;
            info.arg_str = match[1];
            if (match[2] == "真") {
                info.arg_hasEnd = true;
            }
            else if (match[2] == "假") {
                info.arg_hasEnd = false;
            }
            else {
                info.arg_hasEnd = true;  // 默认值
            }

            // 获取内存字节集表示
            std::string replacement = ansi2unicodebyte(info);

            // 替换原始字符串中的匹配部分
            result = std::regex_replace(result, pattern, replacement, std::regex_constants::format_first_only);
        }
    }

    return result;
}


static void L() {
    /*移动到首部*/
    using namespace elibstl::ideplug;
    idefunc::move_to_bottom();
    auto end = idefunc::get_cursor_row();
    idefunc::move_to_top();
    for (DWORD i = 0; i < end; i++)
    {
        idefunc::down_cursor();
        auto oldtext = idefunc::get_this_text();
        idefunc::replace_text(ReplaceLstr(oldtext));
        debug_put(oldtext);
    }
    IdeMessageBox::Show(L"本页宽字符预编译完成");
};

PlugInfoMake(
    Plug_UnicodeBase,
    "宽字符->预编译该页",
    "在IDE中将宽字符转换为{}字节集,用以较少运行时执行从而提升效率",
    L
);