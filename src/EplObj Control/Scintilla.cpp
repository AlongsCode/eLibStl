#include"EcontrolHelp.h"

#include "Scintilla\Scintilla.h"
#include "Scintilla\ILexer.h"



#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
#pragma comment(lib,"msimg32.lib")
//#ifdef _WIN32
//#ifdef _DEBUG
//#pragma comment(lib,"openlib\\scintilla\\scintilladb.lib")
//#else
//#pragma comment(lib,"openlib\\scintilla\\scintilla.lib")
//#endif
//#endif 



ESTL_NAMESPACE_BEGIN

class CScintillaEditor :public elibstl::CCtrlBaseSimple {
public:
	CScintillaEditor(STD_ECTRL_CREATE_ARGS) {
		Scintilla_RegisterClasses(g_elibstl_hModule);
		m_hWnd = CreateWindowExW(0, L"Scintilla", NULL, WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			x, y, cx, cy, hParent, (HMENU)nID, g_elibstl_hModule, NULL);

		// 设置 Scintilla 控件的样式和语法高亮
		SendMessage(m_hWnd, SCI_STYLESETFONT, 0, (LPARAM)"Consolas");
		//SendMessage(m_hwndScintilla, SCI_SETLEXER, SCLEX_CPP, 0);
	}

	void SetText(const std::string& text) {
		SendMessage(m_hWnd, SCI_SETTEXT, 0, (LPARAM)text.c_str());
	}

	std::string GetText() const {
		int length = SendMessage(m_hWnd, SCI_GETLENGTH, 0, 0);
		std::string text(length, '\0');
		SendMessage(m_hWnd, SCI_GETTEXT, length + 1, (LPARAM)text.data());
		return text;
	}

	void Show() {
		ShowWindow(m_hWnd, SW_SHOW);
	}

	void SetSize(int width, int height) {
		SetWindowPos(m_hWnd, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	}
private:


public:/*易语言接口*/
	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CScintillaEditor(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}
};

ESTL_NAMESPACE_END



EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_Scintilla(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)nullptr;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)nullptr;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)nullptr;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)nullptr;
	}
	return NULL;
}


ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtScintilla = {
	"火花编辑框",//中文名称
	"Scintilla",//英文名称
	"本控件有诸多属性改变后需要重新创建控件，应尽量在设计时确定属性值",//说明
	0,//命令数量
	0,//在全局函数中对应的索引
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//标志
	IDB_UPDOWN_EX,//资源ID
	0,
	0,//事件
	0,//属性数
	0,//属性指针
	libstl_GetInterface_Scintilla,//组件交互子程序
	NULL,//成员数量
	NULL//成员数据数组
};
ESTL_NAMESPACE_END