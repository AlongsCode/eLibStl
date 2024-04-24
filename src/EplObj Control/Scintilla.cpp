#include"EcontrolHelp.h"
#include "Scintilla\Scintilla.h"
#include "Scintilla\SciLexer.h"
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
#pragma comment(lib,"msimg32.lib")


inline std::string WStrToUtf8(const std::wstring& pwsText)
{
	size_t npLength = pwsText.size();
	std::string memBuf;
	if (npLength > 0)
	{
		auto npBufLen = ::WideCharToMultiByte(CP_UTF8, 0, pwsText.c_str(), (INT)npLength, NULL, 0, NULL, NULL);
		memBuf.resize(npBufLen + 1);
		CHAR* psBuf = memBuf.data();
		npBufLen = ::WideCharToMultiByte(CP_UTF8, 0, pwsText.c_str(), (INT)npLength, psBuf, (INT)npBufLen, NULL, NULL);

		if (npBufLen > 0)  // ת���ɹ�?
		{
			psBuf[npBufLen] = '\0';
			return psBuf;
		}
	}
	return "";
}


#pragma warning(disable:4996)

#define SCID_SCINTILLA		20230523'01u
#define SCID_SCINTILLAPARENT	20230523'02u

#define ED_CUEBANNER_MAXLEN 260

ESTL_NAMESPACE_BEGIN
/*�𻨱༭��*/
#define DATA_VER_SCINTILLA_1	1
struct ESCINTILLADATA
{
	int iVer;				// �汾��
	DWORD dwReserved;		// ����

	COLORREF m_BackColour;//����ɫ
	COLORREF m_ForeColour;//ǰ��ɫ
	bool m_bSelectionBackColour;		// �Ƿ�ѡ�񱳾�ɫ
	COLORREF m_SelectionBackColour;		// ��ѡ�񱳾�ɫ
	bool m_bSelectionForeColour;		// �Ƿ�ѡ�񱳾�ɫ
	COLORREF m_SelectionForeColour;		// ��ѡ��ǰ��ɫ
	int  m_ScrollbarMode;//���������
	int  m_ScrollbarWigtht;//����������
	bool m_onlyread;//ֻ��
	int m_lexer;//�ʷ�������;
};
#pragma region Help
inline void show_warning_dialog(HWND parentWnd, LPCWSTR title, LPCWSTR content) {
	TASKDIALOGCONFIG config = { 0 };
	config.cbSize = sizeof(config);
	config.hwndParent = parentWnd;
	config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_USE_HICON_MAIN;
	config.pszWindowTitle = title;
	config.pszMainIcon = TD_WARNING_ICON;
	config.pszContent = content;
	config.pszMainInstruction = L"����";

	TaskDialogIndirect(&config, NULL, NULL, NULL);
}

static std::string ansi_to_utf8(const char* text)
{
	if (text == nullptr || *text == '\0')
		return "";
	int utf8Length = MultiByteToWideChar(CP_ACP, 0, text, -1, nullptr, 0);
	std::wstring wideText(utf8Length, L'\0');
	MultiByteToWideChar(CP_ACP, 0, text, -1, &wideText[0], utf8Length);
	int utf8Length2 = WideCharToMultiByte(CP_UTF8, 0, wideText.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string utf8Text(utf8Length2, '\0');
	WideCharToMultiByte(CP_UTF8, 0, wideText.c_str(), -1, &utf8Text[0], utf8Length2, nullptr, nullptr);
	return utf8Text;
}
static std::string utf8_to_ansi(const char* text)
{
	if (text == nullptr || *text == '\0')
		return "";
	int wideLength = MultiByteToWideChar(CP_UTF8, 0, text, -1, nullptr, 0);
	std::wstring wideText(wideLength, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, text, -1, &wideText[0], wideLength);

	int ansiLength = WideCharToMultiByte(CP_ACP, 0, wideText.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string ansiText(ansiLength, '\0');
	WideCharToMultiByte(CP_ACP, 0, wideText.c_str(), -1, &ansiText[0], ansiLength, nullptr, nullptr);
	return ansiText;
}
static std::string unicode_to_utf8(const wchar_t* text)
{
	if (text == nullptr || *text == L'\0')
		return "";
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, text, -1, nullptr, 0, nullptr, nullptr);
	std::string utf8Text(utf8Length + 1, '\0');
	WideCharToMultiByte(CP_UTF8, 0, text, -1, &utf8Text[0], utf8Length, nullptr, nullptr);
	return utf8Text;
}
std::wstring utf8_to_unicode(const char* utf8Text)
{
	if (utf8Text == nullptr || *utf8Text == L'\0')
		return L"";
	int unicodeLength = MultiByteToWideChar(CP_UTF8, 0, utf8Text, -1, nullptr, 0);
	std::wstring unicodeText(unicodeLength, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, utf8Text, -1, &unicodeText[0], unicodeLength);

	return unicodeText;
}
static PSTR unicode_to_utf8_p(const wchar_t* text)
{
	int utf8Length = WideCharToMultiByte(CP_UTF8, 0, text, -1, nullptr, 0, nullptr, nullptr);
	char* utf8Text = new char[utf8Length + 1];
	WideCharToMultiByte(CP_UTF8, 0, text, -1, utf8Text, utf8Length, nullptr, nullptr);
	utf8Text[utf8Length] = '\0';
	return utf8Text;
}

#pragma endregion
/*�ı����ݷ�ʽΪutf-8���ͻ����ı����淽ʽ����ϴ�*/
class CScintillaEditor :public elibstl::CCtrlBase
{

	SUBCLASS_MGR_DECL(CScintillaEditor)
private:
	ESCINTILLADATA m_Info{ 0 };
	static LRESULT CALLBACK ParentSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
	static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto p = (CScintillaEditor*)dwRefData;
		elibstl::SendToParentsHwnd(p->m_dwWinFormID, p->m_dwUnitID, uMsg, wParam, lParam);
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
public: /*C��ʹ��,utf-8*/
	void set_text(const char* text) {

		auto u8str = ansi_to_utf8(text);
		SendEditor(SCI_SETTEXT, 0, (sptr_t)u8str.data());
	}
	void set_text(const wchar_t* text) {

		auto u8str = unicode_to_utf8(text);
		SendEditor(SCI_SETTEXT, 0, (sptr_t)u8str.data());
	}
	unsigned char get_selalpha() {
		return static_cast<unsigned char>(::SendMessage(m_hWnd, SCI_GETSELALPHA, 0, 0));
	}
	CHAR* get_text() {
		int length = SendMessage(m_hWnd, SCI_GETLENGTH, 0, 0);
		std::string text(length, '\0');
		SendMessage(m_hWnd, SCI_GETTEXT, length + 1, (LPARAM)text.data());
		m_ansiStr = utf8_to_ansi(text.c_str());
		return m_ansiStr.data();
	}
	LPBYTE get_textW(size_t* size) {
		int length = SendMessage(m_hWnd, SCI_GETLENGTH, 0, 0);
		std::string text(length, '\0');
		SendMessage(m_hWnd, SCI_GETTEXT, length + 1, (LPARAM)text.data());
		m_wstr = utf8_to_unicode(text.c_str());
		*size = (m_wstr.size() + 1) * sizeof(wchar_t);
		return (LPBYTE)m_wstr.data();
	}
	/*�ù�����ģʽ*/
	void set_scrollbar_mode(int mode) {
		m_Info.m_ScrollbarMode = mode;
		switch (m_Info.m_ScrollbarMode)
		{
		case 0:

			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 0, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 0, 0);
			break;
		case 1:
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 0, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 1, 0);
			break;
		case 2:
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 1, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 0, 0);
			break;
		case 3:
			::SendMessage(m_hWnd, SCI_SETVSCROLLBAR, 1, 0);
			::SendMessage(m_hWnd, SCI_SETHSCROLLBAR, 1, 0);
			break;
		}
	}
	/*��ȡ������*/
	int get_scrollbar_mode() {
		int vertical = static_cast<int>(::SendMessage(m_hWnd, SCI_GETVSCROLLBAR, 0, 0));
		int horizontal = static_cast<int>(::SendMessage(m_hWnd, SCI_GETHSCROLLBAR, 0, 0));

		if (vertical && horizontal) {
			m_Info.m_ScrollbarMode = 3;  // ��ʾ��ֱ��ˮƽ������
		}
		else if (vertical) {
			m_Info.m_ScrollbarMode = 2;  // ��ʾ��ֱ������
		}
		else if (horizontal) {
			m_Info.m_ScrollbarMode = 1;  // ��ʾˮƽ������
		}
		else {
			m_Info.m_ScrollbarMode = 0;  // ���ع�����
		}
		return m_Info.m_ScrollbarMode;
	}


	/*�÷�񱳾�ɫ*/
	void set_background_color(COLORREF color) {
		m_Info.m_BackColour = color;
		SendEditor(SCI_STYLESETBACK, (uptr_t)STYLE_DEFAULT, (sptr_t)color);
		debug_put((INT)SendEditor(SCI_STYLEGETBACK, (uptr_t)STYLE_DEFAULT, (sptr_t)color));
	}
	/*ȡ��񱳾�ɫ*/
	COLORREF get_background_color() {
		if (m_bInDesignMode)
			return m_Info.m_BackColour;
		return SendEditor(SCI_STYLEGETBACK, (uptr_t)STYLE_DEFAULT);
	}
	/*�÷��ǰ��ɫ*/
	void set_foreground_color(COLORREF color) {
		m_Info.m_ForeColour = color;
		SendEditor(SCI_STYLESETFORE, STYLE_DEFAULT, m_Info.m_ForeColour);
	}
	/*ȡ���ǰ��ɫ*/
	COLORREF get_foreground_color() {
		if (m_bInDesignMode)
			return m_Info.m_ForeColour;
		return static_cast<COLORREF>(SendEditor(SCI_STYLEGETFORE, STYLE_DEFAULT, 0));
	}
	/*�Ƿ�����ѡ�б���ɫ*/
	void set_bselbackclor(bool bselbackclor) {
		m_Info.m_bSelectionBackColour = bselbackclor;
		::SendMessage(m_hWnd, SCI_SETSELBACK, m_Info.m_bSelectionBackColour, m_Info.m_SelectionBackColour);
	}
	/*�Ƿ�����ѡ�б���ɫ*/
	bool get_bselbackclor() const {
		return m_Info.m_bSelectionBackColour;
	}
	/*��ѡ�б���ɫ*/
	void set_selbackclor(COLORREF selbackclor) {
		m_Info.m_SelectionBackColour = selbackclor;
		::SendMessage(m_hWnd, SCI_SETSELBACK, m_Info.m_bSelectionBackColour, m_Info.m_SelectionBackColour);
	}
	/*�Ƿ�����ѡ��ǰ��ɫ*/
	void set_bselforeclor(bool bselforeclor) {
		m_Info.m_bSelectionForeColour = bselforeclor;
		::SendMessage(m_hWnd, SCI_SETSELFORE, m_Info.m_bSelectionForeColour, m_Info.m_SelectionForeColour);
	}
	bool get_bselforeclor() const {
		return m_Info.m_bSelectionForeColour;
	}
	/*��ѡ��ǰ��ɫ*/
	void set_selforeclor(COLORREF selbackclor) {
		m_Info.m_SelectionForeColour = selbackclor;
		::SendMessage(m_hWnd, SCI_SETSELFORE, m_Info.m_bSelectionForeColour, m_Info.m_SelectionForeColour);
	}
	/*�ù��������*/
	void set_scrollbar_wigth(int wigth) {
		if (wigth <= 0)
		{
			if (m_bInDesignMode)
			{
				TaskDialog(GetActiveWindow(), NULL, L"����", L"�����ô���1�Ŀ��", L"�����ģʽ������ʾ������ʧЧ", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
			}
			return;
		}
		m_Info.m_ScrollbarWigtht = wigth;
		::SendMessage(m_hWnd, SCI_SETSCROLLWIDTH, m_Info.m_ScrollbarWigtht, 0);
	}
	/*ȡ���������*/
	int get_scrollbar_wigth() {
		m_Info.m_ScrollbarWigtht = ::SendMessage(m_hWnd, SCI_GETSCROLLWIDTH, 0, 0);
		return m_Info.m_ScrollbarWigtht;
	}
	bool onlyread() {
		m_Info.m_onlyread = static_cast<bool>(SendEditor(SCI_GETREADONLY));
		return m_Info.m_onlyread;
	}
	void onlyread(bool open) {
		m_Info.m_onlyread = open;

		SendEditor(SCI_SETREADONLY, (uptr_t)m_Info.m_onlyread);
	}
	int get_lexer() {
		m_Info.m_lexer = SendEditor(SCI_GETLEXER);
		return m_Info.m_lexer;
	}
	void set_lexer_name(LPCWSTR str) {
		SendEditor(SCI_SETLEXERLANGUAGE, 0, (sptr_t)unicode_to_utf8(str).c_str());
	}
	LPBYTE get_lexer_name(INT* size) {
		sptr_t len = SendEditor(SCI_GETLEXERLANGUAGE) + 1;
		std::string str(len, 0);
		m_lexname.clear();
		if (SendEditor(SCI_GETLEXERLANGUAGE, 0, (sptr_t)str.data()) > 0) {
			m_lexname = utf8_to_unicode(str.c_str());
			*size = (m_lexname.size() + 1) * sizeof(wchar_t);
		}
		return (LPBYTE)m_lexname.data();
	}
	void set_lexer(int lexer) {
		if (lexer < 0 || lexer>130 || lexer == 29 || lexer == 30)
		{
			if (m_bInDesignMode)
			{
				TaskDialog(GetActiveWindow(), NULL, L"����", L"��������Ч�ʷ�������", L"�����ģʽ������ʾ������ʧЧ", TDCBF_OK_BUTTON, LPCWSTR(65529), 0);
			}
			return;
		}
		m_Info.m_lexer = lexer;
		SendEditor(SCI_SETLEXER, (uptr_t)m_Info.m_lexer);
	}
public:
	std::wstring m_wstr,m_lexname;
	std::string m_ansiStr;
	SciFnDirect m_fnDirect;
	sptr_t m_ptrDirect;
	sptr_t SendEditor(unsigned int iMessage, uptr_t wParam = 0, sptr_t lParam = 0)
	{
		return m_fnDirect(m_ptrDirect, iMessage, wParam, lParam);
	}
	CScintillaEditor(STD_ECTRL_CREATE_ARGS)
	{

		auto cbBaseData = InitBase0(pAllData, cbData, bInDesignMode, dwWinFormID, dwUnitID, nID, hParent);
		m_Info.iVer = DATA_VER_SCINTILLA_1;
		Scintilla_RegisterClasses(g_elibstl_hModule);
		m_hWnd = CreateWindowExW(0, L"Scintilla", NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
			x, y, cx, cy, hParent, (HMENU)nID, g_elibstl_hModule, NULL);
		SendMessage(m_hWnd, SCI_STYLESETFONT, 0, (LPARAM)"Consolas");

		m_fnDirect = (SciFnDirect)SendMessage(m_hWnd, SCI_GETDIRECTFUNCTION, 0, 0);
		m_ptrDirect = (sptr_t)SendMessage(m_hWnd, SCI_GETDIRECTPOINTER, 0, 0);
		if (pAllData)
		{
			BYTE* p = (BYTE*)pAllData + cbBaseData;
			memcpy(&m_Info, p, sizeof(ESCINTILLADATA));
		}
		else
		{
			/*�޹�����*/
			m_Info.m_BackColour = 16777215;
			m_Info.m_ScrollbarWigtht = get_scrollbar_wigth();
			m_Info.m_ScrollbarMode = get_scrollbar_mode();
		}



		set_background_color(m_Info.m_BackColour);
		set_foreground_color(m_Info.m_ForeColour);
		set_selbackclor(m_Info.m_SelectionBackColour);
		set_selforeclor(m_Info.m_SelectionForeColour);
		set_scrollbar_mode(m_Info.m_ScrollbarMode);
		set_scrollbar_wigth(m_Info.m_ScrollbarWigtht);
		onlyread(m_Info.m_onlyread);
		set_lexer(m_Info.m_lexer);

		m_SM.OnCtrlCreate(this);
		m_hParent = hParent;

		InitBase0(pAllData);
		FrameChanged();
	}




public:

	static HUNIT WINAPI ECreate(STD_EINTF_CREATE_ARGS)
	{
		auto p = new CScintillaEditor(STD_ECTRL_CREATE_REAL_ARGS);
		return elibstl::make_cwnd(p->GetHWND());
	}

	eStlInline HGLOBAL FlattenInfo() override
	{
		BYTE* p;
		SIZE_T cbBaseData;
		auto hGlobal = FlattenInfoBase0(sizeof(ESCINTILLADATA), &cbBaseData);
		if (!hGlobal)
			goto Fail;
		p = (BYTE*)GlobalLock(hGlobal);
		if (!p)
			goto Fail;
		// �ṹ
		p += cbBaseData;
		memcpy(p, &m_Info, sizeof(ESCINTILLADATA));

		GlobalUnlock(hGlobal);
	Fail:
		return hGlobal;
	}
	static HGLOBAL WINAPI EGetAlldata(HUNIT hUnit)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		return p->FlattenInfo();
	}

	static BOOL WINAPI EChange(HUNIT hUnit, INT nPropertyIndex, UNIT_PROPERTY_VALUE* pPropertyVaule, PSTR* ppszTipText)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// ����
			p->set_text(pPropertyVaule->m_szText);
			break;
		case 1:// ����W
			p->set_text((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		case 2://������ɫ
			p->set_background_color(pPropertyVaule->m_clr);
			break;
		case 3://ǰ����ɫ
			p->set_foreground_color(pPropertyVaule->m_clr);
			break;
		case 4://�Ƿ�����ѡ�񱳾���ɫ
			p->set_bselbackclor(pPropertyVaule->m_bool);
			break;
		case 5://ѡ�񱳾���ɫ
			p->set_selbackclor(pPropertyVaule->m_clr);
			break;
		case 6://�Ƿ�����ѡ��ǰ����ɫ
			p->set_bselforeclor(pPropertyVaule->m_bool);
			break;
		case 7://ѡ��ǰ����ɫ
			p->set_selforeclor(pPropertyVaule->m_clr);
			break;
		case 8://������ģʽ
			p->set_scrollbar_mode(pPropertyVaule->m_int);
			break;
		case 9://���������
			p->set_scrollbar_wigth(pPropertyVaule->m_int);
			break;
		case 10:/*ֻ��*/
			p->onlyread(pPropertyVaule->m_bool);
			break;
		case 11:/*�ʷ�������*/
			p->set_lexer(pPropertyVaule->m_int);
			break;
		case 12:/*�ʷ�������*/
			p->set_lexer_name((PCWSTR)pPropertyVaule->m_data.m_pData);
			break;
		}

		return FALSE;
	}
	static BOOL WINAPI EGetData(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));

		switch (nPropertyIndex)
		{
		case 0:// ����
			//p->GetTextA();
			pPropertyVaule->m_szText = p->get_text();
			break;
		case 1:// ����W
		{
			pPropertyVaule->m_data.m_pData = p->get_textW((size_t*) & pPropertyVaule->m_data.m_nDataSize);

		}break;
		case 2://������ɫ
			pPropertyVaule->m_clr = p->get_background_color();
			break;
		case 3://ǰ����ɫ
			pPropertyVaule->m_clr = p->get_foreground_color();
			break;
		case 4://�Ƿ�����ѡ�񱳾���ɫ
			pPropertyVaule->m_bool = p->get_bselbackclor();
			break;
		case 5://ѡ�񱳾���ɫ
			pPropertyVaule->m_clr = p->m_Info.m_SelectionBackColour;
			break;
		case 6://�Ƿ�����ѡ��ǰ����ɫ
			pPropertyVaule->m_bool = p->get_bselforeclor();
			break;
		case 7://�Ƿ�����ѡ��ǰ����ɫ
			pPropertyVaule->m_clr = p->m_Info.m_SelectionForeColour;
			break;
		case 8://������ģʽ
			pPropertyVaule->m_int = p->get_scrollbar_mode();
			break;
		case 9://���������
			pPropertyVaule->m_int = p->get_scrollbar_wigth();
			break;
		case 10:/*ֻ��*/
			pPropertyVaule->m_bool = p->onlyread();
			break;
		case 11:/*�ʷ�*/
			pPropertyVaule->m_int = p->get_lexer();
			break;
		case 12:/*�ʷ�����*/
			pPropertyVaule->m_data.m_pData = p->get_lexer_name(&pPropertyVaule->m_data.m_nDataSize);
			break;
		}


		return TRUE;
	}

	static BOOL WINAPI EInputW(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		//PWSTR psz;
		*pblModified = FALSE;
		//switch (nPropertyIndex)
		//{
		//case 1:// ����W
		//{
		//	if (elibstl::IntputBox(&psz, p->GetTextW()))
		//	{
		//		p->Set_TextW(psz);
		//		delete[] psz;
		//		*pblModified = TRUE;
		//	}
		//}
		//break;
		//}
		return FALSE;
	}
	static BOOL WINAPI EPropUpdateUI(HUNIT hUnit, INT nPropertyIndex)
	{
		auto p = m_CtrlSCInfo.at(elibstl::get_hwnd_from_hunit(hUnit));
		switch (nPropertyIndex)
		{
		case 5:// ������ɫ
			return p->m_Info.m_bSelectionBackColour;
		case 7:// ������ɫ
			return p->m_Info.m_bSelectionForeColour;
		case 9:// ���������ֵ
			return p->m_Info.m_ScrollbarMode != 0;
		}

		return TRUE;
	}
	static INT WINAPI ENotify(INT nMsg, DWORD dwParam1, DWORD dwParam2)
	{
		switch (nMsg)
		{
		case NU_GET_CREATE_SIZE_IN_DESIGNER:
		{
			*((int*)dwParam1) = 200;
			*((int*)dwParam2) = 50;
		}
		return TRUE;
		}
		return FALSE;
	}
};
SUBCLASS_MGR_INIT(CScintillaEditor, SCID_SCINTILLAPARENT, SCID_SCINTILLA)
ESTL_NAMESPACE_END





EXTERN_C PFN_INTERFACE WINAPI libstl_GetInterface_Scintilla(INT nInterfaceNO)
{
	switch (nInterfaceNO)
	{
	case ITF_CREATE_UNIT:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::ECreate;
	case ITF_NOTIFY_PROPERTY_CHANGED:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EChange;
	case ITF_GET_ALL_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EGetAlldata;
	case ITF_GET_PROPERTY_DATA:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EGetData;
	case ITF_DLG_INIT_CUSTOMIZE_DATA:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EInputW;
	case ITF_PROPERTY_UPDATE_UI:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::EPropUpdateUI;
	case ITF_GET_NOTIFY_RECEIVER:
		return (PFN_INTERFACE)elibstl::CScintillaEditor::ENotify;
	}
	return NULL;
}






static UNIT_PROPERTY s_Member_Scintilla[] =
{
	FIXED_WIN_UNIT_PROPERTY,
	//1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����

	/*000*/  {"����", "Text", "", UD_TEXT, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL},
	/*001*/  {"����W", "TextW", "", UD_CUSTOMIZE, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL},
	/*002*/	 {"Ĭ�ϱ�����ɫ", "BKClr", "", UD_COLOR, _PROP_OS(__OS_WIN) ,  NULL},
	/*003*/	 {"Ĭ��ǰ����ɫ", "FKClr", "", UD_COLOR, _PROP_OS(__OS_WIN) | UW_GROUP_LINE,  NULL},
	/*004*/	 {"���ñ�ѡ�б���ɫ", "Frame", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*005*/	 {"��ѡ�б���ɫ", "SelBKClr", "���õ�ǰ�༭����ѡ�������ı��ı���ɫ", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT| UW_GROUP_LINE ,  NULL},
	/*006*/	 {"���ñ�ѡ��ǰ��ɫ", "Frame", "", UD_BOOL, _PROP_OS(__OS_WIN),  NULL},
	/*007*/	 {"��ѡ��ǰ��ɫ", "SelBKClr", "", UD_COLOR, _PROP_OS(__OS_WIN) | UW_HAS_INDENT | UW_GROUP_LINE ,  NULL},
	/*008*/  { "������", "Scroll", "���ù�����ģʽ", UD_PICK_INT, _PROP_OS(OS_ALL), "��\0""���������\0""���������\0""�������������\0""\0" },
	/*009*/  {"���������ֵ", "TextBKClr", "Խ���������ԽС��ÿ���ƶ���Խ����Խ��", UD_INT, _PROP_OS(__OS_WIN) | UW_HAS_INDENT, NULL},
	/*010*/  { "ֻ��ģʽ", "ReadOnly", "ֻ��ģʽΪ���桱�Ǵ�����༭��ֻ�ܶ��������Ա༭��Ϊ���١�ʱ���Ա༭", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	/*011*/  { "�ʷ�������", "SETLEXER", "���ôʷ������������ôʷ���������ϵͳ���������ı������﷨�����Ĵ���", UD_PICK_INT, _PROP_OS(__OS_WIN) ,
	"����\0"
	"��\0"               // SCLEX_CONTAINER - 0
"Python\0"          // SCLEX_HTML - 1
"C++\0"             // SCLEX_PYTHON - 2
"HTML\0"            // SCLEX_CPP - 3
"XML\0"             // SCLEX_HTML - 4
"Perl\0"            // SCLEX_XML - 5
"SQL\0"             // SCLEX_PERL - 6
"VB\0"              // SCLEX_SQL - 7
"Properties\0"      // SCLEX_VB - 8
"ErrorList\0"       // SCLEX_PROPERTIES - 9
"Makefile\0"        // SCLEX_ERRORLIST - 10
"Batch\0"           // SCLEX_MAKEFILE - 11
"Xcode\0"           // SCLEX_BATCH - 12
"LaTeX\0"           // SCLEX_XCODE - 13
"Lua\0"             // SCLEX_LATEX - 14
"Diff\0"            // SCLEX_LUA - 15
"Conf\0"            // SCLEX_DIFF - 16
"Pascal\0"          // SCLEX_CONF - 17
"Ave\0"             // SCLEX_PASCAL - 18
"Ada\0"             // SCLEX_AVE - 19
"Lisp\0"            // SCLEX_ADA - 20
"Ruby\0"            // SCLEX_LISP - 21
"Eiffel\0"          // SCLEX_RUBY - 22
"EiffelKW\0"        // SCLEX_EIFFEL - 23
"Tcl\0"             // SCLEX_EIFFELKW - 24
"NNCRontab\0"       // SCLEX_TCL - 25
"Bullant\0"         // SCLEX_NNCRONTAB - 26
"VBScript\0"        // SCLEX_BULLANT - 27
"Baan\0"            // SCLEX_VBSCRIPT - 28
"��Ч\0"//29
"��Ч\0"//30
"Matlab\0"          // SCLEX_BAAN - 31
"Scriptol\0"        // SCLEX_MATLAB - 32
"ASM\0"             // SCLEX_SCRIPTOL - 33
"CPPNoCase\0"       // SCLEX_ASM - 34
"Fortran\0"         // SCLEX_CPPNOCASE - 35
"F77\0"             // SCLEX_FORTRAN - 36
"CSS\0"             // SCLEX_F77 - 37
"POV\0"             // SCLEX_CSS - 38
"LOUT\0"            // SCLEX_POV - 39
"EScript\0"         // SCLEX_LOUT - 40
"PS\0"              // SCLEX_ESCRIPT - 41
"NSIS\0"            // SCLEX_PS - 42
"MMIXAL\0"          // SCLEX_NSIS - 43
"CLW\0"             // SCLEX_MMIXAL - 44
"CLWNoCase\0"       // SCLEX_CLW - 45
"LOT\0"             // SCLEX_CLWNOCASE - 46
"YAML\0"            // SCLEX_LOT - 47
"TeX\0"             // SCLEX_YAML - 48
"MetaPost\0"        // SCLEX_TEX - 49
"PowerBASIC\0"      // SCLEX_METAPOST - 50
"Forth\0"           // SCLEX_POWERBASIC - 51
"Erlang\0"          // SCLEX_FORTH - 52
"Octave\0"          // SCLEX_ERLANG - 53
"MSSQL\0"           // SCLEX_OCTAVE - 54
"Verilog\0"         // SCLEX_MSSQL - 55
"Kix\0"             // SCLEX_VERILOG - 56
"Gui4Cli\0"         // SCLEX_KIX - 57
"Specman\0"         // SCLEX_GUI4CLI - 58
"AutoIt\0"          // SCLEX_SPECMAN - 59
"APDL\0"            // SCLEX_AU3 - 60
"Bash\0"            // SCLEX_APDL - 61
"ASN.1\0"           // SCLEX_BASH - 62
"VHDL\0"            // SCLEX_ASN1 - 63
"CAML\0"            // SCLEX_VHDL - 64
"BlitzBasic\0"      // SCLEX_CAML - 65
"PureBasic\0"       // SCLEX_BLITZBASIC - 66
"Haskell\0"         // SCLEX_PUREBASIC - 67
"PHPScript\0"       // SCLEX_HASKELL - 68
"TADS3\0"           // SCLEX_PHPSCRIPT - 69
"Rebol\0"           // SCLEX_TADS3 - 70
"Smalltalk\0"       // SCLEX_REBOL - 71
"Flagship\0"        // SCLEX_SMALLTALK - 72
"Csound\0"          // SCLEX_FLAGSHIP - 73
"FreeBASIC\0"       // SCLEX_CSOUND - 74
"InnoSetup\0"       // SCLEX_FREEBASIC - 75
"Opal\0"            // SCLEX_INNOSETUP - 76
"Spice\0"           // SCLEX_OPAL - 77
"D\0"               // SCLEX_SPICE - 78
"CMake\0"           // SCLEX_D - 79
"GAP\0"             // SCLEX_CMAKE - 80
"PL/M\0"            // SCLEX_GAP - 81
"Progress\0"        // SCLEX_PLM - 82
"Abaqus\0"          // SCLEX_PROGRESS - 83
"Asymptote\0"       // SCLEX_ABAQUS - 84
"R\0"               // SCLEX_ASYMPTOTE - 85
"Magik\0"           // SCLEX_R - 86
"PowerShell\0"      // SCLEX_MAGIK - 87
"MySQL\0"           // SCLEX_POWERSHELL - 88
"PO\0"              // SCLEX_MYSQL - 89
"TAL\0"             // SCLEX_PO - 90
"COBOL\0"           // SCLEX_TAL - 91
"TACL\0"            // SCLEX_COBOL - 92
"Sorcus\0"          // SCLEX_TACL - 93
"PowerPro\0"        // SCLEX_SORCUS - 94
"Nimrod\0"          // SCLEX_POWERPRO - 95
"SML\0"             // SCLEX_NIMROD - 96
"Markdown\0"        // SCLEX_SML - 97
"Txt2Tags\0"        // SCLEX_MARKDOWN - 98
"A68K\0"            // SCLEX_TXT2TAGS - 99
"Modula\0"          // SCLEX_A68K - 100
"CoffeeScript\0"    // SCLEX_MODULA - 101
"TCMD\0"            // SCLEX_COFFEESCRIPT - 102
"AVS\0"             // SCLEX_TCMD - 103
"ECL\0"             // SCLEX_AVS - 104
"OScript\0"         // SCLEX_ECL - 105
"VisualProlog\0"    // SCLEX_OSCRIPT - 106
"LiterateHaskell\0" // SCLEX_VISUALPROLOG - 107
"sttxt\0"           // SCLEX_LITERATEHASKELL - 108
"KVIrc\0"           // SCLEX_STTXT - 109
"Rust\0"            // SCLEX_KVIRC - 110
"DMAP\0"            // SCLEX_RUST - 111
"AS\0"              // SCLEX_DMAP - 112
"DMIS\0"            // SCLEX_AS - 113
"Registry\0"        // SCLEX_DMIS - 114
"BibTeX\0"          // SCLEX_REGISTRY - 115
"SREC\0"            // SCLEX_BIBTEX - 116
"IHEX\0"            // SCLEX_SREC - 117
"TEHEX\0"           // SCLEX_IHEX - 118
"JSON\0"            // SCLEX_TEHEX - 119
"EDIFACT\0"         // SCLEX_JSON - 120
"Indent\0"          // SCLEX_EDIFACT - 121
"Maxima\0"          // SCLEX_INDENT - 122
"Stata\0"           // SCLEX_MAXIMA - 123
"SAS\0"             // SCLEX_STATA - 124
"Nim\0"             // SCLEX_SAS - 125
"CIL\0"             // SCLEX_NIM - 126
"X12\0"             // SCLEX_CIL - 127
"DataFlex\0"        // SCLEX_X12 - 128
"Hollywood\0"       // SCLEX_DATAFLEX - 129
"Raku\0"            // SCLEX_HOLLYWOOD - 130
	"\0" },
	/*012*/	 { "�ʷ�����������", "Text", R"(���õ�ǰ����ʹ�õ����ôʷ�����������,��"�ʷ�������"���Բ�ͬ���Ǳ�����ʹ�ôʷ����������ı�������ѡ��)", UD_CUSTOMIZE, _PROP_OS(__OS_WIN) | UW_CANNOT_INIT, NULL },
	



	///*002*/{ "�հ��������ģʽ", "WhiteSpace", "���ÿհ��������ģʽ���հ�����ָ����Ŀո��ַ�����Tab�ַ�����ɵ��޿����ַ�����ʹ�õ����ո��ַ���ʹ�ü�ͷ���Tab�ַ�", UD_PICK_INT, _PROP_OS(OS_ALL), "��\0""�������\0""���ַ�ʹ�ú����\0""\0" },
	///*003*/{ "�հ�����ǰ����ɫ", "WhiteSpaceFore", "���ÿհ�����ǰ����ɫ", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*004*/{ "�հ����򱳾���ɫ", "WhiteSpaceBack", "���ÿհ�����ǰ����ɫ", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*005*/{ "�������", "CursorType", "�������", UD_PICK_INT, _PROP_OS(OS_ALL), "��ͨ\0""æ\0""\0" },
	///*006*/{ "�н�����־", "EolMode", "�����н�����־��ע��Macʹ��\\r��Unixʹ��\\n��DOS��WINDOWSʹ��\\r\\n", UD_PICK_INT, _PROP_OS(OS_ALL), "CRLFģʽ\0""CRģʽ\0""LFģʽ\0""\0" },
	///*007*/{ "��ʾ�н�����־", "ViewEol", "��ʾ�н�����־", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	///*008*/{ "ѡ���ı�ǰ��ɫ", "SelForeColor", "ѡ���ı����ı���ǰ��ɫ", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*009*/{ "ѡ���ı�����ɫ", "SelBackColor", "ѡ���ı����ı��ı���ɫ", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*010*/{ "�����ɫ", "CaretForeColor", "������ɫ", UD_COLOR, _PROP_OS(OS_ALL), NULL },
	///*011*/{ "�����������ɫģʽ", "CaretLineVisible", "�Ƿ�ʹ�ù�������еı�����ɫ", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	///*012*/{ "��������б�����ɫ", "CaretLineBackColor", "��������б�����ɫ���������������ɫģʽ��Ϊ��ʱ��Ч", UD_COLOR, _PROP_OS(OS_ALL) | UW_HAS_INDENT, NULL },
	///*013*/{ "�����˸���", "CaretPeriod", "�����˸�ļ������", UD_INT, _PROP_OS(OS_ALL), NULL },
	///*014*/{ "�����", "CaretWidth", "���Ŀ�ȣ���λΪ����", UD_PICK_INT, _PROP_OS(OS_ALL), " 0����\0"" 1����\0"" 2����\0"" 3����\0""\0" },
	///*015*/{ "����", "SetCodePage", "�����ַ�����", UD_PICK_INT, _PROP_OS(OS_ALL), "ANSI\0""UNICODE\0""\0" },
	///*016*/{ "��ʾ������", "SetIndentationGuides", "��ʾ�����򵼣���������������Ե��һ������", UD_BOOL, _PROP_OS(OS_ALL), NULL },
	///*017*/{ "�Զ�����", "SetWrapMode", "�Զ�����", UD_BOOL, _PROP_OS(OS_ALL), NULL },

};



ESTL_NAMESPACE_BEGIN
LIB_DATA_TYPE_INFO CtScintilla = {
	"�𻨱༭��",//��������
	"Scintilla",//Ӣ������
	"���ؼ���������Ըı����Ҫ���´����ؼ���Ӧ���������ʱȷ������ֵ",//˵��
	0,//��������
	0,//��ȫ�ֺ����ж�Ӧ������
	_DT_OS(__OS_WIN) | LDT_WIN_UNIT,//��־
	IDB_SCINTILLA,//��ԴID
	0,
	0,//�¼�
	ARRAYSIZE(s_Member_Scintilla),//������
	s_Member_Scintilla,//����ָ��
	libstl_GetInterface_Scintilla,//��������ӳ���
	NULL,//��Ա����
	NULL//��Ա��������
};
ESTL_NAMESPACE_END

