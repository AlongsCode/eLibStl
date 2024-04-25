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
	//���Բ���,��Ϊ����ֱ�Ӷ�ȡ,���Կ���ֱ�Ӹ�ֵ
	bool  m_bCreateprompt{};//����ʱ��ʾ
	bool  m_bFileMustExist{};//�ļ��������
	bool  m_bOverrideprompt{};//�ļ�������ʾ
	bool  m_bPathMustExist{};//Ŀ¼�������
	bool  noChangeDir{};// ���ı�Ŀ¼
	bool m_SelectedFiles{};//��ѡ
	UINT m_dwDefFilter{};//��ʼ����������
	std::wstring m_strDefext;//Ĭ���ļ���׺
	std::wstring m_strFilter;//������
	std::wstring m_fileNamae;//Ĭ�Ϸ����ļ���
	std::wstring m_title;//����
	std::wstring m_strDefdir;//��ʼĿ¼
private:
	OPENFILENAMEW m_ofn{};//�Ի���ṹ��
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

		for (auto& c : m_strFilter) {//���������
			if (c == L'|')
				c = L'\0';
		}

		while (pParentWnd != nullptr) {//�����㴰��
			auto tempParent = ::GetParent(pParentWnd);
			if (tempParent == nullptr)
				break;
			pParentWnd = tempParent;
		}
		m_ofn.lStructSize = sizeof(m_ofn);
		m_ofn.lpstrDefExt = m_strDefext.c_str(); //Ĭ���ļ���׺
		m_ofn.lpstrFilter = m_strFilter.data();//������
		m_ofn.lpstrFile = m_szFileName.data();
		m_ofn.nMaxFile = static_cast<DWORD>(m_szFileName.size());
		m_ofn.lpstrFileTitle = m_szFileTitle.data();
		m_ofn.nMaxFileTitle = static_cast<DWORD>(m_szFileTitle.size());
		m_ofn.nFilterIndex = m_strFilter.empty() ? 0 : (m_dwDefFilter < 0 ? 0 : m_dwDefFilter + 1);//Ĭ�Ϲ���������
		m_ofn.lpstrTitle = m_title.data();//����
		m_ofn.lpstrInitialDir = m_strDefdir.data();//Ĭ��Ŀ¼
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
			//���������
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

		for (auto& c : m_strFilter) {//���������
			if (c == L'|')
				c = L'\0';
		}

		while (pParentWnd != nullptr) {//�����㴰��
			auto tempParent = ::GetParent(pParentWnd);
			if (tempParent == nullptr)
				break;
			pParentWnd = tempParent;
		}
		m_ofn.lStructSize = sizeof(m_ofn);
		m_ofn.lpstrDefExt = m_strDefext.c_str(); //Ĭ���ļ���׺
		m_ofn.lpstrFilter = m_strFilter.data();//������
		m_ofn.lpstrFile = m_szFileName.data();
		m_ofn.nMaxFile = static_cast<DWORD>(m_szFileName.size());
		m_ofn.lpstrFileTitle = m_szFileTitle.data();
		m_ofn.nMaxFileTitle = static_cast<DWORD>(m_szFileTitle.size());
		m_ofn.nFilterIndex = m_strFilter.empty() ? 0 : (m_dwDefFilter < 0 ? 0 : m_dwDefFilter + 1);//Ĭ�Ϲ���������
		m_ofn.lpstrTitle = m_title.data();//����
		m_ofn.lpstrInitialDir = m_strDefdir.data();//Ĭ��Ŀ¼
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
			//���������
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
