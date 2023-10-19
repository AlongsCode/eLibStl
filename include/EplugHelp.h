#include "ElibHelp.h"

#define PlugInfoMake(plugname,name, description,funcptr) void funcptr(); namespace elibstl{ PlugInfo plugname{ funcptr,name"\0" description "\0",sizeof(name"\0" description "\0")};};



namespace elibstl::ideplug {
	/*IDE功能*/
	class idefunc {
	public:
		inline constexpr static DWORD nop_arg[] = {0,0};
		/*获取当前行的所有文本*/
		static std::string get_this_text() {
			GET_PRG_TEXT_PARAM arg = { -1,-1,nullptr,0,0,0 };
			GET_PRG_TEXT_PARAM* pArg[] = { &arg,nullptr };
			NotifySys(NES_RUN_FUNC, FN_GET_PRG_TEXT, reinterpret_cast<DWORD>(pArg));
			if (arg.m_nBufSize == 0)
				return {};
			std::string ret(arg.m_nBufSize, '\0');
			arg.m_pBuf = ret.data();
			NotifySys(NES_RUN_FUNC, FN_GET_PRG_TEXT, reinterpret_cast<DWORD>(pArg));
			return ret;
		}

		/*替换IDE文本*/
		static bool replace_text(const std::string& oldtext, const std::string& newtext) {
			REPLACE_ALL2_PARAM arg = { oldtext.data(),newtext.data(),true };
			REPLACE_ALL2_PARAM* pArg[] = { &arg,nullptr };
			return NotifySys(NES_RUN_FUNC, FN_REPLACE_ALL2, reinterpret_cast<DWORD>(pArg));
		}
		/*替换当前行*/
		static bool replace_text(const std::string& newtext, BOOL isPrecompile = TRUE) {
			const void* pArg[] = {
				newtext.data(),
				&isPrecompile };
			return NotifySys(NES_RUN_FUNC, FN_SET_AND_COMPILE_PRG_ITEM_TEXT, reinterpret_cast<DWORD>(pArg));
		}
		/*移到顶部*/
		static bool move_to_top() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_TOP, reinterpret_cast<const DWORD>(nop_arg));
		}
		static bool move_to_bottom() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_BOTTOM, reinterpret_cast<const DWORD>(nop_arg));
		}
		/*上移一行*/
		static bool up_cursor() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_UP, reinterpret_cast<const DWORD>(nop_arg));
		}
		/*下移一行*/
		static bool down_cursor() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_DOWN, reinterpret_cast<const DWORD>(nop_arg));
		}
		/*取当前行号*/
		static auto get_cursor_row() {
			DWORD ret = 0;
			DWORD arg[] = { reinterpret_cast<DWORD>(&ret),0 };
			NotifySys(NES_RUN_FUNC, FN_GET_CARET_ROW_INDEX, reinterpret_cast<const DWORD>(arg));
			return ret;
		}
		/*取当前列号*/
		static auto get_cursor_col() {
			DWORD ret = 0;
			DWORD arg[] = { reinterpret_cast<DWORD>(&ret),0 };
			NotifySys(NES_RUN_FUNC, FN_GET_CARET_COL_INDEX, reinterpret_cast<const DWORD>(arg));
			return ret;
		}
	};
	class IdeMessageBox {
	public:
		static auto Show(const wchar_t* text, const wchar_t* title = L"ElibStl", UINT type = MB_OK) {
			HWND hWnd = (HWND)elibstl::NotifySys(NES_GET_MAIN_HWND, 0, 0);
			::MessageBoxW(hWnd, text, title, type);
		}

	};
}



