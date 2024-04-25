#ifndef CFILEDLG_H
#define CFILEDLG_H
#include"ElibHelp.h"
#include <windows.h>
#include <string>
#include <array>
#include <vector>
#include <tchar.h>
class CFileDlg {
public:
	//属性部分,因为都是直接读取,所以可以直接赋值
	bool  m_bCreateprompt{};//创建时提示
	bool  m_bFileMustExist{};//文件必须存在
	bool  m_bOverrideprompt{};//文件覆盖提示
	bool  m_bPathMustExist{};//目录必须存在
	bool  noChangeDir{};// 不改变目录
	bool m_SelectedFiles{};//多选
	UINT m_dwDefFilter{};//初始过滤器索引
	std::wstring m_strDefext;//默认文件后缀
	std::wstring m_strFilter;//过滤器
	std::wstring m_fileNamae;//默认返回文件名
	std::wstring m_title;//标题
	std::wstring m_strDefdir;//初始目录
private:
	OPENFILENAMEW m_ofn{};//对话框结构体
	std::array<wchar_t, 64> m_szFileTitle{};
	std::array<wchar_t, MAX_PATH>m_szFileName{};
public:
	BOOL Open(HWND pParentWnd = nullptr) {
		m_ofn.Flags = OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_EXPLORER;
		if (m_bCreateprompt)  m_ofn.Flags |= OFN_CREATEPROMPT;
		if (m_bFileMustExist)  m_ofn.Flags |= OFN_FILEMUSTEXIST;
		if (m_bOverrideprompt)  m_ofn.Flags |= OFN_OVERWRITEPROMPT;
		if (m_bPathMustExist)  m_ofn.Flags |= OFN_PATHMUSTEXIST;
		if (noChangeDir)  m_ofn.Flags |= OFN_NOCHANGEDIR;
		if (m_SelectedFiles) m_ofn.Flags |= OFN_ALLOWMULTISELECT;

		if (!m_fileNamae.empty())
			std::copy(m_fileNamae.begin(), m_fileNamae.end(), m_szFileName.begin());

		for (auto& c : m_strFilter) {//处理过滤器
			if (c == L'|')
				c = L'\0';
		}

		while (pParentWnd != nullptr) {//处理顶层窗口
			auto tempParent = ::GetParent(pParentWnd);
			if (tempParent == nullptr)
				break;
			pParentWnd = tempParent;
		}
		m_ofn.lStructSize = sizeof(m_ofn);
		m_ofn.lpstrDefExt = m_strDefext.c_str(); //默认文件后缀
		m_ofn.lpstrFilter = m_strFilter.data();//过滤器
		m_ofn.lpstrFile = m_szFileName.data();
		m_ofn.nMaxFile = static_cast<DWORD>(m_szFileName.size());
		m_ofn.lpstrFileTitle = m_szFileTitle.data();
		m_ofn.nMaxFileTitle = static_cast<DWORD>(m_szFileTitle.size());
		m_ofn.nFilterIndex = m_strFilter.empty() ? 0 : (m_dwDefFilter < 0 ? 0 : m_dwDefFilter + 1);//默认过滤器索引
		m_ofn.lpstrTitle = m_title.data();//标题
		m_ofn.lpstrInitialDir = m_strDefdir.data();//默认目录
		m_ofn.hwndOwner = pParentWnd;

		BOOL bEnableParent = FALSE;
		HWND hWndFocus = ::GetFocus();
		if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
		{
			bEnableParent = TRUE;
			::EnableWindow(m_ofn.hwndOwner, FALSE);
		}
		BOOL nResult = ::GetOpenFileNameW(&m_ofn);
		if (bEnableParent)
			::EnableWindow(m_ofn.hwndOwner, TRUE);
		if (::IsWindow(hWndFocus))
			::SetFocus(hWndFocus);

		if (nResult)
		{
			//记忆过滤器
			m_dwDefFilter = (0 > m_ofn.nFilterIndex - 1) ? 0 : (m_ofn.nFilterIndex - 1);
			return TRUE;
		}
		return FALSE;
	}
	BOOL Save(HWND pParentWnd = nullptr)
	{
		m_ofn.Flags = OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_EXPLORER;
		if (m_bCreateprompt)  m_ofn.Flags |= OFN_CREATEPROMPT;
		if (m_bFileMustExist)  m_ofn.Flags |= OFN_FILEMUSTEXIST;
		if (m_bOverrideprompt)  m_ofn.Flags |= OFN_OVERWRITEPROMPT;
		if (m_bPathMustExist)  m_ofn.Flags |= OFN_PATHMUSTEXIST;
		if (noChangeDir)  m_ofn.Flags |= OFN_NOCHANGEDIR;
		if (m_SelectedFiles) m_ofn.Flags |= OFN_ALLOWMULTISELECT;

		if (!m_fileNamae.empty())
			wcscpy_s(m_szFileName.data(), static_cast<INT>(m_fileNamae.size()), m_fileNamae.data());

		for (auto& c : m_strFilter) {//处理过滤器
			if (c == L'|')
				c = L'\0';
		}

		while (pParentWnd != nullptr) {//处理顶层窗口
			auto tempParent = ::GetParent(pParentWnd);
			if (tempParent == nullptr)
				break;
			pParentWnd = tempParent;
		}
		m_ofn.lStructSize = sizeof(m_ofn);
		m_ofn.lpstrDefExt = m_strDefext.c_str(); //默认文件后缀
		m_ofn.lpstrFilter = m_strFilter.data();//过滤器
		m_ofn.lpstrFile = m_szFileName.data();
		m_ofn.nMaxFile = static_cast<DWORD>(m_szFileName.size());
		m_ofn.lpstrFileTitle = m_szFileTitle.data();
		m_ofn.nMaxFileTitle = static_cast<DWORD>(m_szFileTitle.size());
		m_ofn.nFilterIndex = m_strFilter.empty() ? 0 : (m_dwDefFilter < 0 ? 0 : m_dwDefFilter + 1);//默认过滤器索引
		m_ofn.lpstrTitle = m_title.data();//标题
		m_ofn.lpstrInitialDir = m_strDefdir.data();//默认目录
		m_ofn.hwndOwner = pParentWnd;

		BOOL bEnableParent = FALSE;
		HWND hWndFocus = ::GetFocus();
		if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
		{
			bEnableParent = TRUE;
			::EnableWindow(m_ofn.hwndOwner, FALSE);
		}
		BOOL nResult = ::GetSaveFileNameW(&m_ofn);
		if (bEnableParent)
			::EnableWindow(m_ofn.hwndOwner, TRUE);
		if (::IsWindow(hWndFocus))
			::SetFocus(hWndFocus);

		if (nResult)
		{
			//记忆过滤器
			m_dwDefFilter = (0 > m_ofn.nFilterIndex - 1) ? 0 : (m_ofn.nFilterIndex - 1);
			return TRUE;
		}
		return FALSE;

	}


	std::wstring GetFullName() const {
		return m_szFileName.data();
	}

	std::wstring GetName() const {
		return  m_szFileTitle.data();
	}
	std::vector<LPBYTE> GetAllPathName() {
		int pos = 0;
		std::vector<LPBYTE> ret;
		do {
			auto temp = std::wstring(GetNextPathName(pos).data());
			if (!temp.empty())
				ret.push_back(elibstl::clone_textw(temp));

		} while (pos != -1);
		return ret;
	}

private:
	std::wstring GetNextPathName(int& pos) const
	{
		int maxFileSize = static_cast<int>(m_ofn.nMaxFile);
		int bufferSize = (260 < maxFileSize - pos) ? 260 : (maxFileSize - pos);
		std::wstring fileNames(m_ofn.lpstrFile + pos, m_ofn.lpstrFile + pos + bufferSize);
		size_t index = 0;
		if (pos == 0)
		{
			index = fileNames.find(L'\0');

			if (index == std::wstring::npos || (fileNames.at(++index) == L'\0'))
			{
				pos = -1;
				return m_ofn.lpstrFile;
			}
		}
		std::wstring pathName = m_ofn.lpstrFile;
		std::wstring fileName = m_ofn.lpstrFile + pos + index;

		int fileLength = lstrlenW(fileName.data());
		if (fileNames.at(index + fileLength + 1) == L'\0')
			pos = -1;
		else
			pos = pos + static_cast<UINT>(index) + fileLength + 1;

		if (!pathName.empty())
		{
			int pathLength = static_cast<int>(pathName.size());
			TCHAR termination = pathName.at(pathLength - 1);

			if (termination == L'\\')
				return pathName + fileName;

		}
		return pathName + L'\\' + fileName;
	}
};

#endif
