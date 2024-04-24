#include "ElibHelp.h"

#define PlugInfoMake(plugname,name, description,funcptr) void funcptr(); namespace elibstl{ PlugInfo plugname{ funcptr,name"\0" description "\0",sizeof(name"\0" description "\0")};};



namespace elibstl::ideplug {
	/*IDE����*/
	class idefunc {
	public:
		inline constexpr static DWORD nop_arg[] = {0,0};
		/*��ȡ��ǰ�е������ı�*/
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

		/*�滻IDE�ı�*/
		static bool replace_text(const std::string& oldtext, const std::string& newtext) {
			REPLACE_ALL2_PARAM arg = { oldtext.data(),newtext.data(),true };
			REPLACE_ALL2_PARAM* pArg[] = { &arg,nullptr };
			return NotifySys(NES_RUN_FUNC, FN_REPLACE_ALL2, reinterpret_cast<DWORD>(pArg));
		}
		/*�滻��ǰ��*/
		static bool replace_text(const std::string& newtext, BOOL isPrecompile = TRUE) {
			const void* pArg[] = {
				newtext.data(),
				&isPrecompile };
			return NotifySys(NES_RUN_FUNC, FN_SET_AND_COMPILE_PRG_ITEM_TEXT, reinterpret_cast<DWORD>(pArg));
		}
		/*�Ƶ�����*/
		static bool move_to_top() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_TOP, reinterpret_cast<const DWORD>(nop_arg));
		}
		static bool move_to_bottom() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_BOTTOM, reinterpret_cast<const DWORD>(nop_arg));
		}
		/*����һ��*/
		static bool up_cursor() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_UP, reinterpret_cast<const DWORD>(nop_arg));
		}
		/*����һ��*/
		static bool down_cursor() {
			return NotifySys(NES_RUN_FUNC, FN_MOVE_DOWN, reinterpret_cast<const DWORD>(nop_arg));
		}
		/*ȡ��ǰ�к�*/
		static auto get_cursor_row() {
			DWORD ret = 0;
			DWORD arg[] = { reinterpret_cast<DWORD>(&ret),0 };
			NotifySys(NES_RUN_FUNC, FN_GET_CARET_ROW_INDEX, reinterpret_cast<const DWORD>(arg));
			return ret;
		}
		/*ȡ��ǰ�к�*/
		static auto get_cursor_col() {
			DWORD ret = 0;
			DWORD arg[] = { reinterpret_cast<DWORD>(&ret),0 };
			NotifySys(NES_RUN_FUNC, FN_GET_CARET_COL_INDEX, reinterpret_cast<const DWORD>(arg));
			return ret;
		}
		static auto get_main_wnd() {
			static HWND hWnd{ nullptr };
			if (hWnd == nullptr)
				hWnd = reinterpret_cast<HWND>(elibstl::NotifySys(NES_GET_MAIN_HWND, 0, 0));
			return hWnd;
		}
		static auto get_currcet_dir() {
			char buffer[MAX_PATH]{};
			reinterpret_cast<HWND>(elibstl::NotifySys(NAS_GET_VER, 1, (DWORD)buffer));
			return std::string(buffer);
		}
	};
	class IdeMessageBox {
	public:
		static auto Show(const wchar_t* text, const wchar_t* title = L"ElibStl", UINT type = MB_OK) {
			static HWND hWnd{ NULL };
			if (hWnd == NULL)
				hWnd = reinterpret_cast<HWND>(elibstl::NotifySys(NES_GET_MAIN_HWND, 0, 0));
			::MessageBoxW(hWnd, text, title, type);
		}
	};
}



