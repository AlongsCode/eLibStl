#pragma once
#include<string>
#include <vector>
#include <cstring>
#include <cstdlib>

#include"EcontrolHelp.h"


#ifdef _WIN32
namespace elibstl {



	class CFile{
		HANDLE m_hFile{ INVALID_HANDLE_VALUE };
	public:
		~CFile() {
			Close();
		}
		BOOL Open(const std::wstring_view& filename,int openmode,int sharemod) {
			Close(); // 首先关闭已经打开的当前文件
			if (filename.empty())
				return FALSE;
			 DWORD dwAccess = 0;
			 DWORD dwCreateFlag = 0;
			 switch (openmode)
			 {
			 case 1:  dwCreateFlag = OPEN_EXISTING;  dwAccess = GENERIC_READ;  break;
			 case 2:  dwCreateFlag = OPEN_EXISTING;  dwAccess = GENERIC_WRITE;  break;
			 case 3:  dwCreateFlag = OPEN_EXISTING;  dwAccess = (GENERIC_READ | GENERIC_WRITE);  break;
			 case 4:  dwCreateFlag = CREATE_ALWAYS;  dwAccess = GENERIC_WRITE;  break;
			 case 5:  dwCreateFlag = OPEN_ALWAYS;  dwAccess = GENERIC_WRITE;  break;
			 case 6:  dwCreateFlag = OPEN_ALWAYS;  dwAccess = (GENERIC_READ | GENERIC_WRITE);  break;
			 default:  return FALSE;
			 }
			 DWORD dwShareMode = 0;
			 switch (sharemod)
			 {
			 case 1:  dwShareMode = (FILE_SHARE_WRITE | FILE_SHARE_READ);  break;
			 case 2:  dwShareMode = FILE_SHARE_WRITE;  break;
			 case 3:  dwShareMode = FILE_SHARE_READ;  break;
			 case 4:  dwShareMode = 0;  break;
			 default:  return FALSE;
			 }
			 SECURITY_ATTRIBUTES sa;
			 sa.nLength = sizeof(sa);
			 sa.lpSecurityDescriptor = NULL;
			 sa.bInheritHandle = TRUE;
			 m_hFile = ::CreateFileW(filename.data(), dwAccess, dwShareMode, &sa, dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
			 if (m_hFile == INVALID_HANDLE_VALUE)
				     return FALSE;
			 return TRUE;
		}
		void Close() {
			if (m_hFile != INVALID_HANDLE_VALUE )
			{
				::CloseHandle(m_hFile);
				m_hFile = INVALID_HANDLE_VALUE;
			}
		}
		BOOL Lock(INT64 position, INT64 size, INT time) {

			if (m_hFile == INVALID_HANDLE_VALUE || size <= 0)
				return FALSE;
			const DWORD dwBeginTickCount = GetTickCount();
			while (TRUE)
			{
				if (::LockFile(GetFileHandle(), (DWORD)position, (DWORD)(position >> 32), (DWORD)size, (DWORD)(size >> 32)))
					return TRUE;
				const DWORD dwLastError = ::GetLastError();
				if ((dwLastError != ERROR_SHARING_VIOLATION && dwLastError != ERROR_LOCK_VIOLATION) ||
					time == 0 || (time > 0 && GetTickCount() - dwBeginTickCount > (DWORD)time))
					break;
				Sleep(20 + (INT)(randint() % 20));
			}
			return FALSE;
		}
		BOOL Unlock(INT64 position, INT64 size) {
			return ::UnlockFile(m_hFile, (DWORD)position, (DWORD)(position >> 32), (DWORD)size, (DWORD)(size >> 32));
		}
		void FSeek(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf) {
			BOOL bRet = FALSE;
			DWORD dwMoveMethod;
			switch (pArgInf[1].m_int)
			{
			case 2://#文件尾
				dwMoveMethod = FILE_END;
				break;
			case 3://#现行位置
				dwMoveMethod = FILE_CURRENT;
				break;
			default://#文件首
				dwMoveMethod = FILE_BEGIN;
			}
			LARGE_INTEGER dis;
			dis.QuadPart = (ULONGLONG)pArgInf[2].m_int64;
			bRet = ::SetFilePointerEx(m_hFile, dis, NULL, (DWORD)dwMoveMethod);
			pRetData->m_bool = bRet;

		}
		BOOL SeekToBegin() {
			return (::SetFilePointer(m_hFile, 0, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER);
		}
		BOOL SeekToEnd() {
			return (::SetFilePointer(m_hFile, 0, NULL, FILE_END) != INVALID_SET_FILE_POINTER);
		}
		BOOL WriteBin(INT nArgCount, PMDATA_INF pArgInf) {
			DWORD dwNumOfByteRead;
			auto bRet = TRUE;
			for (INT i = 1; i < nArgCount; i++)
			{
				LPBYTE pData = pArgInf[i].m_pBin + 2 * sizeof(INT);
				INT nLen = pArgInf[i].m_pInt[1];
				if (WriteFile(m_hFile, pData, nLen, &dwNumOfByteRead, NULL) == FALSE)
				{
					bRet = FALSE;
					break;
				}
			}
			return bRet;
		}
		BOOL  MoveWrOff(int 基准移动位置, INT64 移动距离) {

			LARGE_INTEGER dis;
			dis.QuadPart = (ULONGLONG)移动距离;
			return ::SetFilePointerEx(m_hFile, dis, NULL, (DWORD)基准移动位置);
		}
		BOOL MoveToBegin() {
			return (::SetFilePointer(m_hFile, 0, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER);
		}
		BOOL MoveToEnd() {
			return (::SetFilePointer(m_hFile, 0, NULL, FILE_END) != INVALID_SET_FILE_POINTER);
		}
		LPBYTE ReadBin(size_t 欲读入数据的尺寸) {
			std::vector<unsigned char> mem;
			const HANDLE hFile = GetFileHandle();
			if (m_hFile != INVALID_HANDLE_VALUE && 欲读入数据的尺寸 > 0)
			{
				DWORD dwRead = 0;

				mem.resize(欲读入数据的尺寸);
				if (::ReadFile(hFile, mem.data(), 欲读入数据的尺寸, &dwRead, NULL))
					mem.resize(dwRead);
				else
					::SetFilePointer(hFile, 0, NULL, FILE_END);
			}
			return elibstl::clone_bin(mem.data(), mem.size());
		}
		BOOL WriteBin(const elibstl::classhelp::span<unsigned char>& 欲写出的字节集数据) {
			return WriteData(欲写出的字节集数据.data(), 欲写出的字节集数据.size());
		}
		auto GetOffst() {
			return (m_hFile == INVALID_HANDLE_VALUE) ? -1 : MoveAndGetFilePos(FILE_CURRENT);
		}

		INT64 GetCurrentPos()const {
			return MoveAndGetFilePos(FILE_CURRENT);
		}
		auto GetCurrent()const {
			return (m_hFile == INVALID_HANDLE_VALUE ? -1 : GetCurrentPos());

		}
		BOOL SetCurrentPos(INT64 n64CurrentPos)
		{
			if (m_hFile == INVALID_HANDLE_VALUE)
				return FALSE;
			LARGE_INTEGER pos;
			pos.QuadPart = (ULONGLONG)n64CurrentPos;
			return ::SetFilePointerEx(m_hFile, pos, NULL, FILE_BEGIN);
		}

		INT64 MoveAndGetFilePos(DWORD dwMoveMethod)const
		{
			if (m_hFile == INVALID_HANDLE_VALUE)
				return 0;
			LARGE_INTEGER dis, current_pos;
			dis.QuadPart = current_pos.QuadPart = 0;
			return (::SetFilePointerEx(m_hFile, dis, &current_pos, dwMoveMethod) ? (INT64)current_pos.QuadPart : -1);
		}
		/*Unicode*/
		LPBYTE ReadText(INT wannasize) {
			std::wstring ret;
			if (m_hFile != INVALID_HANDLE_VALUE && wannasize != 0)
			{
				BOOL blpSuceeded = FALSE;
				do
				{
					const INT64 n64CurrentPos = GetCurrentPos();
					if (n64CurrentPos < 0)
						break;
					INT npReadSize;
					if (wannasize < 0)
					{
						const INT64 n64FileSize = MoveAndGetFilePos(FILE_END);
						if (n64FileSize < 0)
							break;
						npReadSize = (INT)(n64FileSize - n64CurrentPos);
						SetCurrentPos( n64CurrentPos);
					}
					else
					{
						npReadSize = wannasize * sizeof(WCHAR);
					}

					std::vector<unsigned char> mem;
					DWORD dwRead = 0;
					mem.resize(npReadSize);
					if (::ReadFile(m_hFile, mem.data(), (DWORD)npReadSize, &dwRead, NULL) == FALSE)
						break;
					mem.resize(dwRead);
					mem.push_back(0);
					mem.push_back(0);

					const WCHAR* psBegin = (const WCHAR*)mem.data();
					if (n64CurrentPos == 0 && (WORD)*psBegin == 0xFEFF)  // 为文件首部MS的Unicode文本文件起始标志?
						psBegin++;  // 将其跳过
					const WCHAR* ps = psBegin;
					while (*ps != '\0' && *ps != 0x1A)
						ps++;
					ret = std::wstring(psBegin, ps - psBegin);
					const DWORD dwOffset = (DWORD)((const BYTE*)(ps + 1) - mem.data());
					blpSuceeded = SetCurrentPos(n64CurrentPos + (INT64)min(dwOffset, dwRead));
				} while (FALSE);

				if (blpSuceeded == FALSE)
					::SetFilePointer(m_hFile, 0, NULL, FILE_END);
			}
			return clone_textw(ret);

		}
		BOOL WriteText(INT nArgCount, PMDATA_INF pArgInf) {
			auto bRet = TRUE;
			for (INT i = 1; i < nArgCount; i++)
			{
				auto pData = elibstl::arg_to_wstring(pArgInf, i);
				const auto dwTextSize = (DWORD)(pData.size() * sizeof(WCHAR));
				DWORD dwWritten = 0;
				if (pData.size() > 0)
				{
					if (!::WriteFile(m_hFile, pData.c_str(), dwTextSize, &dwWritten, NULL) || dwWritten != dwTextSize) {
						bRet = FALSE;
						break;
					}
				}	
			}
			return bRet;
		}
		INT64 GetSize()const {
			LARGE_INTEGER fileSize;
			if (m_hFile == INVALID_HANDLE_VALUE)
				return -1;
			if (::GetFileSizeEx(m_hFile, &fileSize) == FALSE) {
				return -1;
			}
			return fileSize.QuadPart;
		}

		INT64 MoveToEndAndGetFileSize() {
			return MoveAndGetFilePos(FILE_END); 
		}
		auto ReadLineW()->std::wstring {
			LARGE_INTEGER 
				orgLoc{ 0 }, /*原始位置*/
				newLoc{ 0 }, /*用于储存新位置*/
				nTLen{ 0 };/*用于记录读取总长度*/
			if (SetFilePointerEx(m_hFile, orgLoc, &newLoc, FILE_CURRENT) == 0) {
				// 文件指针位置获取失败，移动到文件末尾并返回空字符串
				SetFilePointerEx(m_hFile, orgLoc, &newLoc, FILE_END);
				return {};
			}
			auto nLen = GetSize() - orgLoc.QuadPart;/*剩余长度*/
			constexpr auto once_max = 4096;/*定义单次读取长度*/
			constexpr auto once_wchar_max = once_max / sizeof(wchar_t);/*定义单词读取wchar_t字符长度*/
			
			std::wstring line;
			DWORD dwNumOfByteRead;
			BOOL bFoundNewline = FALSE;

		
			for (long long i = 0; i < nLen; i += once_max)
			{
				std::wstring tmp(once_wchar_max, L'\0');
				const auto needsize = static_cast<DWORD>(min(nLen - i, static_cast<long long>(4096)));
				auto nRet = ReadFile(m_hFile, tmp.data(), needsize, &dwNumOfByteRead, 0);/*一定不会大于4096,所以可以用ReadFile读*/;
				if (nRet == FALSE)
				{
					SetFilePointer(m_hFile, 0, NULL, FILE_END);
					break;
				}
				bool bFind{ false };/*用于记录是否匹配到换行符*/
				DWORD j = 0;/*用于记录这段字符中的索引位置*/
				for (const auto& ch : tmp )/*遍历这段字符*/
				{
					if (ch == L'\0')
					{
						bFind = true;/*匹配到结束符*/
						dwNumOfByteRead = j * sizeof(wchar_t);
						newLoc.QuadPart = orgLoc.QuadPart + nTLen.QuadPart + j * sizeof(wchar_t);	/*计算新位置:旧位置+先前长度+本次字符长度*/;
						SetFilePointerEx(m_hFile, newLoc, nullptr, FILE_BEGIN);/*设置新位置*/
						break;
					}
					else if (ch == L'\n')
					{
						
						bFind = true;/*匹配到换行符*/
						dwNumOfByteRead = j;
						newLoc.QuadPart = orgLoc.QuadPart + nTLen.QuadPart + (j + 1) * sizeof(wchar_t);/*相对于结束符,这段代码需要跳到下一行行首所以+1个字符*/
						SetFilePointerEx(m_hFile, newLoc, nullptr, FILE_BEGIN); /*设置新位置*/
						break;
					}
					else if (ch == L'\r') {
						
						bFind = true;/*匹配到回车*/
						if (j + 1 == dwNumOfByteRead)/*如果回车是最后一个字符*/
						{
							wchar_t szNewline{ L'\0' };
							
							nRet = ReadFile(m_hFile, &szNewline, sizeof(szNewline), &dwNumOfByteRead, 0);//再读两个字节，看看是不是\r\n组合
							if (nRet == FALSE || szNewline != L'\n')
							{
								//不是\r\n组合，把读写位置放到\r后面
								newLoc.QuadPart = orgLoc.QuadPart + nTLen.QuadPart + (j + 1) * sizeof(wchar_t);
								SetFilePointerEx(m_hFile, newLoc, nullptr, FILE_BEGIN); /*设置新位置*/
							}
						}
						else if (tmp[j + 1] == L'\n')/*不是最后一个字符,且回车后为换行,此位置不用at，是因为一定不会越界*/
						{
							
							newLoc.QuadPart = orgLoc.QuadPart + nTLen.QuadPart + (j + 2) * sizeof(wchar_t);
							SetFilePointerEx(m_hFile, newLoc, nullptr, FILE_BEGIN); /*设置新位置*/
						}
						else/*不是最后一个字符,且回车后不为换行*/
						{
							// 找到 '\r' 后面不是 '\n'，截断当前行并更新文件指针位置
							newLoc.QuadPart = orgLoc.QuadPart + nTLen.QuadPart + (j + 1) * sizeof(wchar_t);
							SetFilePointerEx(m_hFile, newLoc, nullptr, FILE_BEGIN); /*设置新位置*/
						}
						dwNumOfByteRead = j;
						break;
					}
					j++;
					
				}
				
				tmp.resize(dwNumOfByteRead);
				nTLen.QuadPart += dwNumOfByteRead;
				line += tmp;
				if (bFind || dwNumOfByteRead != 4096)//如果找到了换行符或者读取的长度不等于4096，如果实际长度不足也会改变dwNumOfByteRead,则跳出循环
					break;

			}

			return line;
		}

		BOOL isOpen() const{
			return m_hFile != INVALID_HANDLE_VALUE;
		}
		BOOL WriteLine(INT nArgCount, PMDATA_INF pArgInf) {
			BOOL bRet = FALSE;
			DWORD dwNumOfByteRead;
			bRet = TRUE;
			for (INT i = 1; i < nArgCount; i++)
			{
				auto pData = elibstl::arg_to_wstring(pArgInf, i);
				if (pData.empty())
				{
					WriteFile(m_hFile, L"\r\n", 4, &dwNumOfByteRead, NULL);
					continue;
				}
				auto nLen = pData.size() * sizeof(wchar_t);
				if (nLen > 0)
				{
					if (WriteFile(m_hFile, pData.data(), nLen, &dwNumOfByteRead, NULL))
						WriteFile(m_hFile, L"\r\n", 4, &dwNumOfByteRead, NULL);
					else
						bRet = FALSE;
				}
				if (bRet == FALSE)
					break;

			}
			return bRet;
		}
		BOOL RemoveData(INT64 size) {
			if (m_hFile == INVALID_HANDLE_VALUE || size <= 0)
				return FALSE;
			LARGE_INTEGER orgLoc, newLoc;
			orgLoc.QuadPart = 0;
			newLoc.QuadPart = 0;

			if (SetFilePointerEx(m_hFile, orgLoc, &newLoc, FILE_CURRENT) == 0)
				return FALSE;

			auto bRet = TRUE;
			DWORD dwNumOfByteRead;
			LARGE_INTEGER fileSize;
			if (GetFileSizeEx(m_hFile, &fileSize) == FALSE)
				return FALSE;

			LARGE_INTEGER nBkLen;
			nBkLen.QuadPart = fileSize.QuadPart - orgLoc.QuadPart - size;
			LPBYTE pBkData = NULL;
			if (nBkLen.QuadPart > 0)  // 有残余数据
			{
				
				pBkData = new BYTE[static_cast<size_t>(nBkLen.QuadPart)];
				LARGE_INTEGER nLen;
				nLen.QuadPart = size;
				if (SetFilePointerEx(m_hFile, nLen, NULL, FILE_CURRENT) == 0)  // 后移到
				{
					delete[] pBkData;
					return FALSE;
				}
				if (ReadFile(m_hFile, pBkData, static_cast<DWORD>(nBkLen.QuadPart), &dwNumOfByteRead, 0) == FALSE)
				{
					delete[] pBkData;
					return FALSE;
				}
				if (SetFilePointerEx(m_hFile, orgLoc, NULL, FILE_BEGIN) == 0)  // 恢复原位置
				{
					delete[] pBkData;
					return FALSE;
				}
				if (WriteFile(m_hFile, pBkData, static_cast<DWORD>(nBkLen.QuadPart), &dwNumOfByteRead, NULL))
				{
					if (FlushFileBuffers(m_hFile) == FALSE)
						bRet = FALSE;
				}
				else
					bRet = FALSE;
				delete[] pBkData;
			}
			if (bRet)
				SetEndOfFile(m_hFile);
			return bRet;
		}
		BOOL InsertStr(INT nArgCount, PMDATA_INF pArgInf) {
			if (m_hFile == INVALID_HANDLE_VALUE) {
				// 文件句柄无效
				return FALSE;
			}

			LARGE_INTEGER orgLoc, newLoc;
			orgLoc.QuadPart = 0;
			newLoc.QuadPart = 0;

			// 将文件指针移动到当前位置
			if (SetFilePointerEx(m_hFile, orgLoc, &newLoc, FILE_CURRENT) == 0) {
				// 文件指针移动失败
				return FALSE;
			}

			auto bRet = TRUE;
			DWORD dwNumOfBytesWritten;
			LARGE_INTEGER fileSize;

			// 获取文件当前大小
			if (GetFileSizeEx(m_hFile, &fileSize) == FALSE) {
				// 获取文件大小失败
				return FALSE;
			}

			// 计算要保留的数据长度
			LARGE_INTEGER nBkLen;
			nBkLen.QuadPart = fileSize.QuadPart - orgLoc.QuadPart;
			LPBYTE pBkData = nullptr;

			if (nBkLen.QuadPart > 0) {
				// 有残余数据，读取并保存
				pBkData = new BYTE[static_cast<size_t>(nBkLen.QuadPart)];
				if (!ReadFile(m_hFile, pBkData, static_cast<DWORD>(nBkLen.QuadPart), &dwNumOfBytesWritten, nullptr)) {
					// 读取残余数据失败，释放内存并返回
					delete[] pBkData;
					return FALSE;
				}
				// 恢复原文件指针位置
				SetFilePointerEx(m_hFile, orgLoc, nullptr, FILE_BEGIN);
			}

			for (INT i = 1; i < nArgCount; i++) {
				auto dataToInsert = elibstl::arg_to_wstring(pArgInf, i);
				if (dataToInsert.empty()) {
					continue;  // 跳过空数据
				}

				INT dataLength = dataToInsert.size() * sizeof(wchar_t);

				if (dataLength > 0) {
					// 插入数据到文件
					bRet = WriteFile(m_hFile, dataToInsert.data(), dataLength, &dwNumOfBytesWritten, nullptr);
				}

				if (bRet == FALSE) {
					break;  // 写入数据失败，退出循环
				}
			}

			if (bRet && pBkData) {
				// 插入数据后，恢复原文件位置，写回残余数据
				if (SetFilePointerEx(m_hFile, orgLoc, &newLoc, FILE_CURRENT) == 0) {
					// 恢复原文件位置失败
					return FALSE;
				}

				if (!WriteFile(m_hFile, pBkData, static_cast<DWORD>(nBkLen.QuadPart), &dwNumOfBytesWritten, nullptr)) {
					// 写回残余数据失败
					bRet = FALSE;
				}
				// 恢复原文件位置
				SetFilePointerEx(m_hFile, orgLoc, nullptr, FILE_BEGIN);
			}

			if (pBkData) {
				delete[] pBkData;
			}

			return bRet;
		}

	private: 
		inline static BOOL s_blpSrand = FALSE;
		INT randint()
		{
			if (s_blpSrand == FALSE)
			{
				s_blpSrand = TRUE;
				srand(::GetTickCount());
			}

			return rand();
		}
		HANDLE GetFileHandle()const
		{
			return m_hFile;
		}
		/*从易语言写入不了大于DWORD长度的内存,他申请不了*/
		BOOL WriteData(const void* pData, const int npDataSize)
		{
			if (pData == nullptr || npDataSize == 0)
				return FALSE;
			if (m_hFile == INVALID_HANDLE_VALUE)
				return FALSE;
			DWORD dwWritten = 0;
			return (npDataSize == 0 || (::WriteFile(m_hFile, pData, (DWORD)npDataSize, &dwWritten, NULL) && dwWritten == (DWORD)npDataSize));
		}
	

	};


}


#endif // _WIN32

//构造
EXTERN_C void fn_CFile_structure(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	self = new elibstl::CFile;
}
//构造
FucInfo Fn_CFile_structure = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/  _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_CONSTURCT_CMD,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,ESTLFNAME(fn_CFile_structure) };
//复制
static ARG_INFO s_CopyArgs[] =
{
	{
		/*name*/    "拷贝",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/   DTP_CFILE,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
EXTERN_C void fn_CFile_copy(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	const auto& rht = elibstl::classhelp::get_other<elibstl::CFile>(pArgInf);
	self = new elibstl::CFile{ *rht };
}
FucInfo Fn_CFile_copy = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_COPY_CMD,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_CopyArgs,
	} ,ESTLFNAME(fn_CFile_copy)};

//析构
EXTERN_C void fn_CFile_des(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	if (self)
	{
		self->elibstl::CFile::~CFile();
		operator delete(self);
	}
	self = nullptr;
}
FucInfo Fn_CFile_destruct = { {
		/*ccname*/  "",
		/*egname*/  "",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/    _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_FREE_CMD,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/  NULL,
	} ,ESTLFNAME(fn_CFile_des) };


static ARG_INFO s_OpenArgs[] =
{
	{
		/*name*/    "文件名",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "打开方式",
		/*explain*/ "1、#读入：从指定文件读入数据，如果该文件不存在则失败；2、#写出：写出数据到指定文件，如果该文件不存在则失败；3、#读写：从文件中读入数据或者写出数据到文件，如果该文件不存在则失败 4、#重写：写出数据到指定文件。如果该文件不存在则先创建一个新文件，如果已经存在就先清除其中的所有数据；5、#改写：写出数据到指定文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开；6、#改读：从文件中读入数据或者写出数据到文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
		/*name*/    "共享模式",
		/*explain*/ "1、#无限制：允许其它进程任意读写此文件；2、#禁止读：禁止其它进程读此文件；3、#禁止写：禁止其它进程写此文件；4、#禁止读写：禁止其它进程读写此文件。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
EXTERN_C void fn_CFile_Open(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	int openmode = 3, sharemode = 1;
	if (pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_int>=1 && pArgInf[2].m_int <= 6)
	{//#读写
		openmode = pArgInf[2].m_int;
	}
	if (pArgInf[3].m_dtDataType != _SDT_NULL && pArgInf[3].m_int >= 1 && pArgInf[3].m_int <= 3) {
		sharemode= pArgInf[3].m_int;
	}
	auto file = elibstl::args_to_wsdata(pArgInf,1);
	pRetData->m_bool=self->Open(file, openmode, sharemode);
}
FucInfo Fn_CFile_Open = { {
		/*ccname*/  "打开",
		/*egname*/  "打开一个普通文件，以对文件进行输入或输出。成功返回真，失败返回假。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/ s_OpenArgs,
	} ,ESTLFNAME(fn_CFile_Open)  };
EXTERN_C void fn_CFile_Close(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	 self->Close();
}

FucInfo Fn_CFile_Close = { {
		/*ccname*/  "关闭",
		/*egname*/  "关闭文件",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ _SDT_NULL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ 0,
	} ,ESTLFNAME(fn_CFile_Close) };
static ARG_INFO s_LockArgs[] =
{
	{
		/*name*/    "欲加锁或解锁的位置",
		/*explain*/ "位置值从 0 开始。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT64,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "欲加锁或解锁的长度",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT64,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "加锁重试时间",
		/*explain*/ "本参数指定加锁失败后反复进行重试的毫秒数。如果被省略，默认为 0 ，即一旦失败立即返回。如果参数值提供为 -1 ，则反复进行重试，直到加锁成功为止。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_DEFAULT_VALUE_IS_EMPTY,
	}
};
EXTERN_C void fn_CFile_Lock(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	auto time = elibstl::args_to_data<int>(pArgInf, 3).value_or(0);
	pRetData->m_bool = self->Lock(pArgInf[1].m_int64, pArgInf[2].m_int64, time);
}
FucInfo Fn_CFile_Lock = { {
		/*ccname*/  "锁住",
		/*egname*/  " 在有若干个进程访问同一个文件的环境中，使用本命令拒绝其它用户对被打开文件中的某个区域进行读写访问。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/3,
		/*arg lp*/ s_LockArgs,
	} ,ESTLFNAME(fn_CFile_Lock) };


static ARG_INFO s_UnLockArgs[] =
{
	{
		/*name*/    "欲加锁或解锁的位置",
		/*explain*/ "位置值从 0 开始。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT64,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "欲加锁或解锁的长度",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT64,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_UnLock(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool = self->Unlock(pArgInf[1].m_int64, pArgInf[2].m_int64);
}
FucInfo Fn_CFile_UnLock = { {
		/*ccname*/  "解锁",
		/*egname*/  "解除由“锁住文件”命令对文件所进行的锁定。成功返回真，失败返回假。注意：本命令调用时所提供的参数值必须与调用“锁住文件”命令时所提供的参数值完全一致。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/ s_UnLockArgs,
	} ,ESTLFNAME(fn_CFile_UnLock) };


static ARG_INFO s_FSeekArgs[] =
{
	{
		/*name*/    "起始移动位置",
		/*explain*/ "参数值指定从文件中开始移动的位置。可以为以下常量之一：1、#文件首； 2、#文件尾； 3、#现行位置。如果本参数被省略，默认值为“#文件首”。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	},
	{
		/*name*/    "移动距离",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT64,
		/*default*/ 0,
		/*state*/  ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_FSeek(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	self->FSeek(pRetData, nArgCount, pArgInf);
}
FucInfo Fn_CFile_FSeek = { {
		/*ccname*/  "移动读写位置",
		/*egname*/  "在被打开的文件中，设置下一个读或写操作的位置。成功返回真，失败返回假。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/2,
		/*arg lp*/ s_FSeekArgs,
	} ,ESTLFNAME(fn_CFile_FSeek) };

EXTERN_C void fn_CFile_SeekToBegin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	self->SeekToBegin();
}
FucInfo Fn_CFile_SeekToBegin = { {
		/*ccname*/  "移到文件首",
		/*egname*/  "在被打开的文件中，设置下一个读或写操作的位置到文件首。成功返回真，失败返回假。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ nullptr,
	} ,ESTLFNAME(fn_CFile_SeekToBegin) };

EXTERN_C void fn_CFile_SeekToEnd(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	self->SeekToEnd();
}
FucInfo Fn_CFile_SeekToEnd = { {
		/*ccname*/  "移到文件尾",
		/*egname*/  "在被打开的文件中，设置下一个读或写操作的位置到文件首。成功返回真，失败返回假。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ nullptr,
	} ,ESTLFNAME(fn_CFile_SeekToEnd) };





static ARG_INFO s_ReadBinArgs[] =
{
	{
		/*name*/    "欲读入数据的尺寸",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_ReadBin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_pBin = self->ReadBin(pArgInf[1].m_int);
}
FucInfo Fn_CFile_ReadBin = { {
		/*ccname*/  "读入字节集",
		/*egname*/  "从文件中当前读写位置读取并返回一段字节集数据,实际读入长度(即所返回字节集的尺寸)可能会小于欲读入长度.如果读入失败,将返回一个空字节集并且自动将当前文件读写位置移到文件尾部.",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_ReadBinArgs,
	} ,ESTLFNAME(fn_CFile_ReadBin) };

static ARG_INFO s_WriteBinArgs[] =
{
	{
		/*name*/    "欲写入的数据",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_WriteBin(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool = self->WriteBin(nArgCount,pArgInf);
}
FucInfo Fn_CFile_WriteBin = { {
		/*ccname*/  "写出字节集",
		/*egname*/  "本命令用作写出一段或数段字节集数据到文件中当前读写位置处。成功返回真，失败返回假。",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG  ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_WriteBinArgs,
	} ,ESTLFNAME(fn_CFile_WriteBin) };

static ARG_INFO s_ReadTextArgs[] =
{
	{
		/*name*/    "欲读入文本的尺寸",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT,
		/*default*/ -1,
		/*state*/   ArgMark::AS_HAS_DEFAULT_VALUE,
	}
};
EXTERN_C void fn_CFile_ReadText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_pBin = self->ReadText(pArgInf[1].m_int);
}
FucInfo Fn_CFile_ReadText = { {
		/*ccname*/  "读入文本W",
		/*egname*/  " 从文件中当前读写位置读取并返回一段文本数据,实际读入长度(即返回文本的尺寸)可能会小于欲读入长度.如果该数据中存在字符值0或26(文本结束标志),将仅返回该字符之前的数据(后续读写将跳过该字符).如果读入失败,将返回一个空文本并且自动将当前文件读写位置移到文件尾部.注意: 文本文件的编码格式必须为Unicode(即UTF - 16).",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_ReadTextArgs,
	} ,ESTLFNAME(fn_CFile_ReadText) };

static ARG_INFO s_WriteTextArgs[] =
{
	{
		/*name*/    "欲写入的UTF16文本数据,如为非文本数据则自动转换为文本",
		/*explain*/ "",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_WriteText(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool= self->WriteText(nArgCount, pArgInf);
}
FucInfo Fn_CFile_WriteText = { {
		/*ccname*/  "写出文本W",
		/*egname*/  "本命令用作写出一段或数段文本数据到文件中当前读写位置处。成功返回真，失败返回假。注意: 文本文件的编码格式必须为Unicode(即UTF - 16).",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_WriteTextArgs,
	} ,ESTLFNAME(fn_CFile_WriteText) };

EXTERN_C void fn_CFile_ReadLine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_pBin = elibstl::clone_textw(self->ReadLineW());
}

FucInfo Fn_CFile_ReadLine = { {
		/*ccname*/  "读入一行W",
		/*egname*/  "本命令用作从文件中当前读写位置读取并返回一行文本数据，行末的回车及换行符将被抛弃。注意: 文本文件的编码格式必须为Unicode(即UTF - 16).",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   _CMD_OS(__OS_WIN) ,
		/*ret*/ SDT_BIN,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ nullptr,
	} ,ESTLFNAME(fn_CFile_ReadLine) };


static ARG_INFO s_WriteLineArgs[] =
{
	{
		/*name*/    "欲写入的文本行数据",
		/*explain*/ "参数值如果不为文本类型数据，将自动进行转换，如果无法转换（即数据类型为字节集、子程序指针、库或用户自定义数据类型），则不写出此数据。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_WriteLine(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool = self->WriteLine(nArgCount, pArgInf);
}
FucInfo Fn_CFile_WriteLine = { {
		/*ccname*/  "写文本行W",
		/*egname*/  "本命令用作写出一行或多行文本数据到文件中当前读写位置处，每行的尾部将被自动加上回车及换行符。注意: 文本文件的编码格式必须为Unicode(即UTF - 16).",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_WriteLineArgs,
	} ,ESTLFNAME(fn_CFile_WriteLine) };

EXTERN_C void fn_CFile_isOpen(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool = self->isOpen();
}
FucInfo Fn_CFile_isOpen = { {
		/*ccname*/  "是否已打开",
		/*egname*/  "用来判断是否已经打开文本文件",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   0 ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ nullptr,
	} ,ESTLFNAME(fn_CFile_isOpen) };

EXTERN_C void fn_CFile_GetCurrent(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_int64 = self->GetCurrent();
}
FucInfo Fn_CFile_GetCurrent = { {
		/*ccname*/  "取当前读写位置",
		/*egname*/  "获取当前读写位置,失败返回-1",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   0 ,
		/*ret*/ SDT_INT64,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ nullptr,
	} ,ESTLFNAME(fn_CFile_GetCurrent) };

EXTERN_C void fn_CFile_GetSize(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_int64 = self->GetSize();
}
FucInfo Fn_CFile_GetSize = { {
		/*ccname*/  "取文件大小",
		/*egname*/  "获取当前文件占用磁盘大小,失败返回-1，单位:(字节)",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   0 ,
		/*ret*/ SDT_INT64,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/0,
		/*arg lp*/ nullptr,
	} ,ESTLFNAME(fn_CFile_GetSize) };

static ARG_INFO s_RemoveDataArgs[] =
{
	{
		/*name*/    "欲删除的字节",
		/*explain*/ "是INT64没错,但是易申请不了这么大内存,心里有数就行哈",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_INT64,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_RemoveData(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool = self->RemoveData(pArgInf[1].m_int64);
}
FucInfo Fn_CFile_RemoveData = { {
		/*ccname*/  "删除数据",
		/*egname*/  R"(本命令用作在文件中当前读写位置处删除一段字节数据，文件后面的数据顺序前移。该文件被打开时必须给予"#读写"或"#改读"权限。注意: 文本文件的编码格式必须为Unicode(即UTF - 16).)",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   NULL ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_RemoveDataArgs,
	} ,ESTLFNAME(fn_CFile_RemoveData) };
static ARG_INFO s_InsertStrArgs[] =
{
	{
		/*name*/    "欲插入的文本",
		/*explain*/ "参数值如果不为文本类型数据，将自动进行转换，如果无法转换（即数据类型为字节集、子程序指针、库或用户自定义数据类型），则不写出此数据。",
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    _SDT_ALL,
		/*default*/ 0,
		/*state*/   ArgMark::AS_NONE,
	}
};
EXTERN_C void fn_CFile_InsertStr(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto& self = elibstl::classhelp::get_this<elibstl::CFile>(pArgInf);
	pRetData->m_bool = self->InsertStr(nArgCount, pArgInf);
}
FucInfo Fn_CFile_InsertStr = { {
		/*ccname*/  "插入文本W",
		/*egname*/ R"( 本命令用作插入一段或数段文本数据到文件中当前读写位置处。该文件被打开时必须给予"#读写"或"#改读"权限。成功返回真，失败返回假。注意: 文本文件的编码格式必须为Unicode(即UTF - 16).)",
		/*explain*/ NULL,
		/*category*/ -1,
		/*state*/   CT_ALLOW_APPEND_NEW_ARG ,
		/*ret*/ SDT_BOOL,
		/*reserved*/0,
		/*level*/   LVL_SIMPLE,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ s_InsertStrArgs,
	} ,ESTLFNAME(fn_CFile_InsertStr) };

static INT s_dtCmdIndexcommobj_memfile_ex[] = { 318,319 ,320 ,321,322,323,324,326,327,328,329,330,331,332,333,334,335,336,337,338,339};

namespace elibstl {


	LIB_DATA_TYPE_INFO Obj_DiskFile =
	{
		"文件读写",
		"DiskFile",
		"文件读写",
		sizeof(s_dtCmdIndexcommobj_memfile_ex) / sizeof(s_dtCmdIndexcommobj_memfile_ex[0]),
		 s_dtCmdIndexcommobj_memfile_ex,
		_DT_OS(__OS_WIN),
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		0
	};
}