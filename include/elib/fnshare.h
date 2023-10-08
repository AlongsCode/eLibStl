#include "lib2.h"
typedef INT(cdecl* PFN_ON_SYS_NOTIFY) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
#ifndef _private
#define _private  //称识为只私有
#endif
#include<shlwapi.h>
#include<string_view>
#include<stdexcept>
#include<optional>
#include<vector>
#include<string>
#include<map>
#include <cmath>
namespace elibstl
{
	/*易库通信,调用易库命令等*/





	struct ebin
	{
#pragma warning(disable:4200)
		std::uint32_t m_check;//恒为1
		size_t m_size;//长度
		std::uint8_t m_data[0];//字节集指针
		ebin() {
			m_check = 1;
			m_size = 0;
		}
	};

	inline auto& args_to_ebin(PMDATA_INF pArgInf, size_t index) {
		return *reinterpret_cast<ebin*>(pArgInf[index].m_pBin);
	}


	INT WINAPI ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);
	// 向易语言ide发送消息
	INT WINAPI NotifySys(INT nMsg, DWORD dwParam1, DWORD dwParam2);
	//改自白喵的代码
	template <typename T>
	auto& args_to_obj(PMDATA_INF pArgInf)
	{
		return reinterpret_cast<T*&>(pArgInf[0].m_ppCompoundData[0]);
	}
	template <typename T>
	auto args_to_obj_noref(PMDATA_INF pArgInf)
	{
		return reinterpret_cast<T*>(pArgInf[0].m_ppCompoundData[0]);
	}



	inline auto ErrorMsgBox(const std::wstring& filePath, const std::wstring& msg) {
#ifdef _WIN32
		//std::wstring fileName = std::filesystem::path(filePath).filename();
		std::wstring fileName = PathFindFileNameW(filePath.c_str());/*路径不会为空*/
		std::wstring error_msg = L"出现运行时异常,已被支持库拦截(编译后不会出现该提示，但同样会处理异常操作,防止重大错误引起崩溃!)\n出错文件：" + fileName + L"\n错误信息:" + msg;
		int result = ::MessageBoxW(0, error_msg.c_str(), L"出现重大错误", MB_OK | MB_ICONERROR);
#endif
	}
#define put_errmsg(x) elibstl::ErrorMsgBox(__FILEW__,x)

	template <typename T>
	std::optional<T> args_to_data(PMDATA_INF pArgInf, size_t index)
	{
		if (!(std::is_same<T, BYTE>::value ||
			std::is_same<T, SHORT>::value ||
			std::is_same<T, INT>::value ||
			std::is_same<T, INT64>::value ||
			std::is_same<T, FLOAT>::value ||
			std::is_same<T, DOUBLE>::value ||
			std::is_same<T, DATE>::value ||
			std::is_same<T, BOOL>::value ||
			std::is_same<T, char*>::value ||
			std::is_same<T, LPBYTE>::value ||
			std::is_same<T, DWORD>::value ||
			std::is_same<T, STATMENT_CALL_DATA>::value ||
			std::is_same<T, MUNIT>::value ||
			std::is_same<T, void*>::value ||
			std::is_same<T, BYTE*>::value ||
			std::is_same<T, SHORT*>::value ||
			std::is_same<T, INT*>::value ||
			std::is_same<T, INT64*>::value ||
			std::is_same<T, FLOAT*>::value ||
			std::is_same<T, DOUBLE*>::value ||
			std::is_same<T, DATE*>::value))
		{
			throw std::invalid_argument("Invalid template argument type.");
		}
		if (pArgInf[index].m_dtDataType == _SDT_NULL)
		{
			return {};
		}
#pragma warning (push)
#pragma warning (disable:4302)// “从void*到T截断”
		return reinterpret_cast<T>(pArgInf[index].m_pCompoundData);
#pragma warning (pop)
	}

	template <typename T>
	const T& args_to_data_noop(PMDATA_INF pArgInf, size_t index)
	{
#pragma warning (push)
#pragma warning (disable:4302)// “从void*到T截断”
		return reinterpret_cast<T&>(pArgInf[index].m_pCompoundData);
#pragma warning (pop)
	}
	inline std::vector<unsigned char> arg_to_vdata(PMDATA_INF pArgInf, int index) {
		if (pArgInf[index].m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t)) >= 2) {
			//无需对原始指针操作的情况下映射为string_view
			return  std::vector<unsigned char>(pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2, pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2 + *reinterpret_cast<std::uint32_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t)));
		}
		else {
			return  std::vector<unsigned char>();
		}
	}
	inline
		std::vector<unsigned char> arg_to_vdata(LPBYTE bin) {
		if (!bin)
		{
			return  std::vector<unsigned char>();
		}
		size_t lenth = *reinterpret_cast<std::uint32_t*>(bin + sizeof(std::uint32_t));
		LPBYTE pbuffer = (bin + sizeof(std::uint32_t) * 2);
		if (lenth)
		{
			return std::vector<unsigned char>(pbuffer, pbuffer + lenth);
		}
		return  std::vector<unsigned char>();
	};
	inline auto args_to_sdata(PMDATA_INF pArgInf, int index)
	{

		if (pArgInf[index].m_dtDataType == SDT_TEXT && pArgInf[index].m_pText && *pArgInf[index].m_pText != '\0') {
			//无需对原始指针操作的情况下映射为string_view
			return std::string_view(pArgInf[index].m_pText);
		}
		else {

			return std::string_view("");
		}
	}
	inline auto args_to_wsdata(PMDATA_INF pArgInf, int index)
	{
		if (pArgInf[index].m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t)) >= 2 && *reinterpret_cast<wchar_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2) != L'\0') {
			//无需对原始指针操作的情况下映射为string_view
			return std::wstring_view(reinterpret_cast<wchar_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2));
		}
		else {
			return std::wstring_view();
		}
	}
	inline PCWSTR args_to_pszw(PMDATA_INF pArgInf, int idx)
	{
		if (pArgInf[idx].m_dtDataType == _SDT_NULL)
			return NULL;
		else if (reinterpret_cast<INT*>(pArgInf[idx].m_pBin + sizeof(INT))[0])
			return reinterpret_cast<PCWSTR>(pArgInf[idx].m_pBin + 8);
		else
			return NULL;
	}
	inline HBITMAP make_hbm(LPBYTE pData, size_t nSize) {
		return	(HBITMAP)NotifySys(NAS_GET_HBITMAP, (DWORD)pData, nSize);
	}
	inline HUNIT make_cwnd(HWND hWnd) {
		return NotifySys(NAS_CREATE_CWND_OBJECT_FROM_HWND, (DWORD)hWnd, 0);
	}
	inline HWND get_hwnd_from_hunit(HUNIT hUnit) {
		return ((HWND)NotifySys(NAS_GET_HWND_OF_CWND_OBJECT, (INT)hUnit, 0));
	}
	template <typename T>
	inline T get_obj_from_hunit(HUNIT hUnit) {
		return reinterpret_cast<T>(GetWindowLongPtrW((HWND)NotifySys(NAS_GET_HWND_OF_CWND_OBJECT, (INT)hUnit, 0), GWL_USERDATA));
	}
	inline void* GetWndPtr(PMDATA_INF pInf)
	{
		return (void*)NotifySys(NRS_GET_AND_CHECK_UNIT_PTR, pInf->m_unit.m_dwFormID,
			pInf->m_unit.m_dwUnitID);
	}
	inline HWND get_hwnd_from_arg(PMDATA_INF pArgInfo) {
		return ((HWND)NotifySys(NAS_GET_HWND_OF_CWND_OBJECT, (INT)GetWndPtr(pArgInfo), 0));
	}

	inline BOOL is_debug()
	{
		return NotifySys(NRS_GET_PRG_TYPE, 0, 0) == PT_DEBUG_RUN_VER;
	}

	// 从易语言里申请内存, 单位为字节
	// 函数命名不要与CRT冲突！
	inline void* ealloc(int size)
	{
		void* pMem = (void*)NotifySys(NRS_MALLOC, size, 0);
		memset(pMem, 0, size);
		return (void*)pMem;
	}

	inline void efree(void* p)
	{
		NotifySys(NRS_MFREE, reinterpret_cast<DWORD>(p), 0);
	}


	inline char* clone_text(char* ps)
	{
		if (ps == nullptr || *ps == '\0')
			return nullptr;
		std::string_view s(ps);
		const INT nTextLen = s.length();
		char* pd = static_cast<char*>(ealloc(nTextLen + 1));
		std::copy(s.begin(), s.end(), pd);
		pd[nTextLen] = '\0';
		return pd;
	}
	inline char* clone_text(const std::string& s)
	{
		const INT nTextLen = s.length();
		char* pd = static_cast<char*>(ealloc(nTextLen + 1));
		std::copy(s.begin(), s.end(), pd);
		pd[nTextLen] = '\0';
		return pd;
	}


	inline char* clone_text(const std::wstring& s)
	{
		const INT nTextLen = s.length();
		const INT nAnsiLen = WideCharToMultiByte(CP_ACP, 0, s.data(), nTextLen, nullptr, 0, nullptr, nullptr);
		char* pd = static_cast<char*>(ealloc(nAnsiLen + 1));
		WideCharToMultiByte(CP_ACP, 0, s.data(), nTextLen, pd, nAnsiLen + 1, nullptr, nullptr);
		return pd;
	}
	inline char* clone_text(char* ps, INT nTextLen)
	{
		if (nTextLen <= 0)
			return nullptr;
		char* pd = static_cast<char*>(ealloc(nTextLen + 1));
		//空指针检查在这
		std::copy(ps, ps + nTextLen, pd);
		pd[nTextLen] = '\0';
		return pd;
	}
	// 拷贝字节集, 生成易语言格式的字节集,1维数组
	inline LPBYTE clone_bin(LPBYTE pData, INT nDataSize)
	{
		if (nDataSize == 0)
			return nullptr;

		LPBYTE pd = static_cast<LPBYTE>(ealloc(sizeof(std::uint32_t) * 2 + nDataSize));
		std::copy(pData, pData + nDataSize, pd + sizeof(std::uint32_t) * 2);
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(std::uint32_t)) = nDataSize;
		return pd;
	}
	inline LPBYTE clone_textw(const std::wstring& s, bool bTerminator = true)
	{
		if (s.empty())
			return nullptr;
		const INT nLen = (s.length() + (bTerminator ? 1 : 0)) * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(ealloc(nLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, s.data(), s.length() * sizeof(wchar_t));
		return pd;
	}
	inline LPBYTE clone_textw(const std::wstring_view& s, bool bTerminator = true)
	{
		if (s.empty())
			return nullptr;
		const INT nLen = (s.length() + (bTerminator ? 1 : 0)) * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(ealloc(nLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, s.data(), s.length() * sizeof(wchar_t));
		return pd;
	}
	inline LPBYTE clone_textw(LPCWSTR ps, bool bTerminator = true)
	{
		if (ps == nullptr || *ps == L'\0')
			return nullptr;
		const INT nTextLen = static_cast<INT>(wcslen(ps) + (bTerminator ? 1 : 0));
		const INT nWideLen = nTextLen * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(ealloc(nWideLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nWideLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, ps, wcslen(ps) * sizeof(wchar_t));
		return pd;
	}
	inline LPBYTE clone_textw(LPCWSTR ps, INT nTextLen, bool bTerminator = true)
	{
		if (ps == nullptr || *ps == '\0' || nTextLen == 0)
			return nullptr;
		const INT nWideLen = (nTextLen + (bTerminator ? 1 : 0)) * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(ealloc(nWideLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nWideLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, ps, nTextLen * sizeof(wchar_t));
		return pd;
	}


#pragma region arr



	template <typename T>
	inline std::vector<T> get_vector_from_array(const void* pAryData, const size_t arrCount) {
		return std::vector<T>(static_cast<const T*>(pAryData), static_cast<const T*>(pAryData) + arrCount);
	}

	inline std::vector<std::string_view> get_vector_from_array(LPSTR* pAryData, const size_t arrCount) {
		std::vector<std::string_view> result;
		result.reserve(arrCount);
		for (size_t i = 0; i < arrCount; ++i) {
			if (pAryData[i])result.emplace_back(pAryData[i]);

		}
		return result;
	}
	template <typename T>
	inline T get_array_element_inf(void* pAryData, int* pnElementCount)
	{
		if (pnElementCount != nullptr) *pnElementCount = 0;
		if (pAryData == nullptr) return nullptr;

		auto pn_data = static_cast<int*>(pAryData);
		int count = *pn_data++; //获取维数

		int nElementCount = 1; //数组元素数量
		for (auto it = pn_data; it != pn_data + count; ++it)
		{
			nElementCount *= *it;
		}

		if (pnElementCount != nullptr)
			*pnElementCount = nElementCount;
		return reinterpret_cast<T>(pn_data + count);
	}
	template <typename T>
	inline T get_array_element_inf(void* pAryData, size_t* pnElementCount)
	{
		if (pnElementCount != nullptr) *pnElementCount = 0;
		if (pAryData == nullptr) return nullptr;

		auto pn_data = static_cast<int*>(pAryData);
		int count = *pn_data++; //获取维数

		size_t nElementCount = 1; //数组元素数量
		for (auto it = pn_data; it != pn_data + count; ++it)
		{
			nElementCount *= *it;
		}

		if (pnElementCount != nullptr)
			*pnElementCount = nElementCount;
		return reinterpret_cast<T>(pn_data + count);
	}
	template <typename T>
	inline std::vector <T> get_array_element_inf(PMDATA_INF pAryData)
	{

		if (pAryData == nullptr) return std::vector <T>();
		if ((pAryData->m_dtDataType & DT_IS_ARY) == 0) {
			auto data = args_to_data<T>(pAryData, 0);
			return  data.has_value() ? std::vector <T>(data.value()) : std::vector <T>();
		}
		auto pn_data = static_cast<int*>(pAryData->m_pAryData);
		int count = *pn_data++; //获取维数
		int nElementCount = 1; //数组元素数量
		for (auto it = pn_data; it != pn_data + count; ++it)
		{
			nElementCount *= *it;
		}
		return  get_vector_from_array<T>(pn_data + count, nElementCount);
	}

	inline std::vector <std::string_view> get_array_element_inf(PMDATA_INF pAryData)
	{

		if (pAryData == nullptr) return {};
		if ((pAryData->m_dtDataType & DT_IS_ARY) == 0) return  std::vector <std::string_view>{args_to_sdata(pAryData, 0)};

		auto pn_data = static_cast<int*>(pAryData->m_pAryData);
		int count = *pn_data++; //获取维数
		int nElementCount = 1; //数组元素数量
		for (auto it = pn_data; it != pn_data + count; ++it)
		{
			nElementCount *= *it;
		}
		return  get_vector_from_array(reinterpret_cast<LPSTR*>(pn_data + count), nElementCount);
	}
	template <typename T>
	LPBYTE malloc_array(int nCount)
	{
		const auto p = static_cast<LPBYTE>(ealloc(sizeof(T) * nCount + 8));
		*reinterpret_cast<LPINT>(p) = 1;
		*reinterpret_cast<LPINT>(p + 4) = nCount;
		return p;
	}
	inline LPBYTE malloc_wstring(int cch)
	{
		int cb = sizeof(WCHAR) * (cch + 1);
		const auto p = static_cast<LPBYTE>(ealloc(cb + 8));
		*reinterpret_cast<LPINT>(p) = 1;
		*reinterpret_cast<LPINT>(p + 4) = cb;
		return p;
	}
	inline void* empty_array() {
		const auto p = static_cast<LPBYTE>(ealloc(sizeof(int) * 2));
		*reinterpret_cast<LPINT>(p) = 1;
		*reinterpret_cast<LPINT>(p + 4) = 0;
		return p;
	}
	//获取多数组维数
	inline int get_array_dimension(LPVOID n_pAryData) {
		return static_cast<int*>(n_pAryData)[0];
	}
	//获取多数组对应维的成员数，指针和维索引
	inline int get_array_count(void* pBase, INT dimension = 1)
	{
		return reinterpret_cast<INT*>(static_cast<char*>(pBase) + dimension * sizeof(INT))[0];
	}

	inline BYTE* get_array_data_base(void* pBase, int iDimension = 1)
	{
		if (pBase)
			return reinterpret_cast<BYTE*>(static_cast<BYTE*>(pBase) + (iDimension + 1) * sizeof(INT));
		else
			return NULL;
	}
	template <typename T>
	void* create_array(void* data, size_t size)
	{
		if (size <= 0)
			return empty_array();
		if (!data)
			return empty_array();
		const auto p = reinterpret_cast<size_t*>(malloc_array<T>(size));
		memcpy(p + 2, data, sizeof(T) * size);
		return p;
	}
	template <typename T>
	void* create_array(const std::vector<T>& data) {

		return create_array<T>(data.data(), data.size());

	}
	inline void* create_text_array(const std::vector<std::wstring>& data)
	{
		if (data.empty())
			return empty_array();

		const auto p = reinterpret_cast<size_t*>(malloc_array<LPBYTE>(data.size()));
		std::vector<LPBYTE> ewstr(data.size());
		size_t i = 0;
		for (const auto& now : data)
		{
			ewstr[i] = clone_textw(now);
			i++;
		}
		memcpy(p + 2, ewstr.data(), sizeof(LPBYTE) * ewstr.size());
		return p;
	}







	/*参数类辅助函数*/

//是否为数组
	inline bool is_array(const MDATA_INF& pArgInf) {
		return	(pArgInf.m_dtDataType & DT_IS_ARY) == DT_IS_ARY;
	}
	//移除数组标志
	inline void remove_array_flags(PMDATA_INF pArgInf) {
		pArgInf->remove_dt_flag();
	}
	// 添加数组标志
	inline void add_array_flags(PMDATA_INF pArgInf) {
		pArgInf->add_dt_flag();
	}
	//取基础类型长度
	inline size_t get_esys_datatype_size(DATA_TYPE pArgInf)
	{
		static  const std::map<DATA_TYPE, size_t> dataSizes = {
			{SDT_BYTE, sizeof(BYTE)},
			{SDT_SHORT, sizeof(SHORT)},
			{SDT_BOOL, sizeof(BOOL)},
			{SDT_INT, sizeof(INT)},
			{SDT_FLOAT, sizeof(FLOAT)},
			{SDT_SUB_PTR, sizeof(DWORD)},
			{SDT_TEXT, sizeof(DWORD)},
			{SDT_BIN, sizeof(DWORD)},
			{SDT_INT64, sizeof(INT64)},
			{SDT_DOUBLE, sizeof(DOUBLE)},
			{SDT_DATE_TIME, sizeof(DATE)}
		};
		auto iter = dataSizes.find(pArgInf);
		if (iter != dataSizes.end()) {
			return iter->second;
		}
		return 0u;
	}
	/*请确保不为空*/
	inline bool wstring_to_arg(PMDATA_INF pArgInf, const std::wstring& str) {

		switch (pArgInf->m_dtDataType)
		{
		case SDT_TEXT:
			efree(*pArgInf->m_ppText);
			*pArgInf->m_ppText = clone_text(str);
			break;
		case SDT_BIN:
			efree(*pArgInf->m_ppBin);
			*pArgInf->m_ppBin = clone_textw(str);
			break;
		case SDT_BYTE:
			*pArgInf->m_pByte = (BYTE)_wtoi(str.c_str());
			break;
		case SDT_SHORT:
			*pArgInf->m_pShort = (SHORT)_wtoi(str.c_str());
			break;
		case SDT_INT:
			*pArgInf->m_pInt = _wtoi(str.c_str());
			break;
		case SDT_INT64:
			*pArgInf->m_pInt64 = _wtoi64(str.c_str());
			break;
		case SDT_FLOAT:
			*pArgInf->m_pFloat = (FLOAT)_wtof(str.c_str());
			break;
		case SDT_DOUBLE:
			*pArgInf->m_pDouble = _wtof(str.c_str());
			break;
		default:
			return false;
		}
		return true;
	}

	//参数到文本,此代码会将易基本类型格式化为文本例如整形105会变为"105"
	inline std::wstring arg_to_wstring(MDATA_INF pArgInf) {

		if (is_array(pArgInf))//是数组
		{
			remove_array_flags(&pArgInf); //去除数组标志

			auto szData = get_esys_datatype_size(pArgInf.m_dtDataType);

			wchar_t* ret = nullptr;

			if (szData != 0) {
				auto array_to_string = [](void* pArry, size_t szData) -> wchar_t* {
					size_t dwSize;

					auto pText = elibstl::get_array_element_inf<wchar_t*>(pArry, &dwSize);

					if (dwSize == 0)
						return nullptr;

					//最大肯能存在的unicode字符数
					auto nMax = (dwSize * szData) / sizeof(wchar_t);

					size_t nLen = 0;

					while (nLen < nMax && pText[nLen] != L'\0')
						nLen++;


					if (nLen == 0)
						return nullptr;

					wchar_t* pNewText = reinterpret_cast<wchar_t*>(elibstl::ealloc((nLen + 1) * sizeof(wchar_t)));

					memcpy(pNewText, pText, nLen * sizeof(wchar_t));

					pNewText[nLen] = L'\0';

					return pNewText;
				};
				ret = array_to_string(pArgInf.m_pAryData, szData);
			}
			//无论是否转换成功都将添加回数组标志
			//pArgInf.add_array_flags();非拷贝取消

			if (ret)
				return ret;
			else
				return {};
		}
		else
		{
			std::wstring str;

			if (pArgInf.m_dtDataType == SDT_TEXT) {
				if (pArgInf.m_pText && *pArgInf.m_pText != '\0') {
					int widesize = MultiByteToWideChar(CP_ACP, 0, pArgInf.m_pText, -1, NULL, 0);
					if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
					{
						return {};
					}
					if (widesize == 0)
					{
						return {};
					}
					wchar_t* resultstring = new wchar_t[widesize];
					int convresult = MultiByteToWideChar(CP_ACP, 0, pArgInf.m_pText, -1, resultstring, widesize);
					if (convresult != widesize)
					{
						return {};
					}
					str = resultstring;
					delete[] resultstring;
				}
			}
			//整数值类型
			else if (pArgInf.m_dtDataType == SDT_BYTE || pArgInf.m_dtDataType == SDT_SHORT || pArgInf.m_dtDataType == SDT_INT ||
				pArgInf.m_dtDataType == SDT_SUB_PTR) {
				intptr_t nVal = 0;
				if (pArgInf.m_dtDataType == SDT_BYTE)
					nVal = pArgInf.m_byte;
				else if (pArgInf.m_dtDataType == SDT_SHORT)
					nVal = pArgInf.m_short;
				else if (pArgInf.m_dtDataType == SDT_INT)
					nVal = pArgInf.m_int;
				else if (pArgInf.m_dtDataType == SDT_SUB_PTR)
					nVal = pArgInf.m_int;
				return  std::to_wstring(nVal);
			}
			else if (pArgInf.m_dtDataType == SDT_INT64) {
				return  std::to_wstring(pArgInf.m_int64);
			}
			else if (pArgInf.m_dtDataType == SDT_FLOAT) {
				str = std::to_wstring(pArgInf.m_float);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();
			}
			else if (pArgInf.m_dtDataType == SDT_DOUBLE) {
				str = std::to_wstring(pArgInf.m_double);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();

			}
			else if (pArgInf.m_dtDataType == SDT_BOOL) {
				if (pArgInf.m_bool)
					return  L"真";
				else
					return  L"假";

			}
			else if (pArgInf.m_dtDataType == SDT_BIN) {//如果为字节集直接返回就可
				if (pArgInf.m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t)) >= 2 && *reinterpret_cast<wchar_t*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2) != L'\0') {
					//无需对原始指针操作的情况下映射为string_view
					return std::wstring(reinterpret_cast<wchar_t*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2), *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t));
				}
			}
			else if (pArgInf.m_dtDataType == SDT_DATE_TIME) {

				wchar_t temp[MAX_PATH]{ 0 };
				SYSTEMTIME st = { 0 };
				VariantTimeToSystemTime(pArgInf.m_double, &st);
				wchar_t strFormat[128]{ 0 };
				wcscpy_s(strFormat, L"%d年%d月%d日");
				//格式化时间部分
				wchar_t strFormatTime[128]{ 0 };
				if (st.wSecond)
					wcscpy_s(strFormatTime, L"%d时%d分%d秒");
				else if (st.wMinute && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%d时%d分");
				else if (st.wHour && st.wMinute == 0 && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%d时");
				else
					strFormatTime[0] = L'\0';
				wcscat_s(strFormat, strFormatTime);
				wsprintfW(temp, strFormat, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				return temp;

			}
			return str;
		}

	}

	inline std::wstring arg_to_wstring(PMDATA_INF ArgInf, size_t index) {
		auto pArgInf = ArgInf[index];
		if (is_array(pArgInf))//是数组
		{
			remove_array_flags(&pArgInf); //去除数组标志

			auto szData = get_esys_datatype_size(pArgInf.m_dtDataType);

			wchar_t* ret = nullptr;

			if (szData != 0) {
				auto array_to_string = [](void* pArry, size_t szData) -> wchar_t* {
					size_t dwSize;

					auto pText = elibstl::get_array_element_inf<wchar_t*>(pArry, &dwSize);

					if (dwSize == 0)
						return nullptr;

					//最大肯能存在的unicode字符数
					auto nMax = (dwSize * szData) / sizeof(wchar_t);

					size_t nLen = 0;

					while (nLen < nMax && pText[nLen] != L'\0')
						nLen++;


					if (nLen == 0)
						return nullptr;

					wchar_t* pNewText = reinterpret_cast<wchar_t*>(elibstl::ealloc((nLen + 1) * sizeof(wchar_t)));

					memcpy(pNewText, pText, nLen * sizeof(wchar_t));

					pNewText[nLen] = L'\0';

					return pNewText;
				};
				ret = array_to_string(pArgInf.m_pAryData, szData);
			}
			//无论是否转换成功都将添加回数组标志
			//pArgInf.add_array_flags();非拷贝取消

			if (ret)
				return ret;
			else
				return {};
		}
		else
		{
			std::wstring str;

			if (pArgInf.m_dtDataType == SDT_TEXT) {
				if (pArgInf.m_pText && *pArgInf.m_pText != '\0') {
					int widesize = MultiByteToWideChar(CP_ACP, 0, pArgInf.m_pText, -1, NULL, 0);
					if (GetLastError() == ERROR_NO_UNICODE_TRANSLATION)
					{
						return {};
					}
					if (widesize == 0)
					{
						return {};
					}
					wchar_t* resultstring = new wchar_t[widesize];
					int convresult = MultiByteToWideChar(CP_ACP, 0, pArgInf.m_pText, -1, resultstring, widesize);
					if (convresult != widesize)
					{
						return {};
					}
					str = resultstring;
					delete[] resultstring;
				}
			}
			//整数值类型
			else if (pArgInf.m_dtDataType == SDT_BYTE || pArgInf.m_dtDataType == SDT_SHORT || pArgInf.m_dtDataType == SDT_INT ||
				pArgInf.m_dtDataType == SDT_SUB_PTR) {
				intptr_t nVal = 0;
				if (pArgInf.m_dtDataType == SDT_BYTE)
					nVal = pArgInf.m_byte;
				else if (pArgInf.m_dtDataType == SDT_SHORT)
					nVal = pArgInf.m_short;
				else if (pArgInf.m_dtDataType == SDT_INT)
					nVal = pArgInf.m_int;
				else if (pArgInf.m_dtDataType == SDT_SUB_PTR)
					nVal = pArgInf.m_int;
				return  std::to_wstring(nVal);
			}
			else if (pArgInf.m_dtDataType == SDT_INT64) {
				return  std::to_wstring(pArgInf.m_int64);
			}
			else if (pArgInf.m_dtDataType == SDT_FLOAT) {
				str = std::to_wstring(pArgInf.m_float);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();
			}
			else if (pArgInf.m_dtDataType == SDT_DOUBLE) {
				str = std::to_wstring(pArgInf.m_double);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();

			}
			else if (pArgInf.m_dtDataType == SDT_BOOL) {
				if (pArgInf.m_bool)
					return  L"真";
				else
					return  L"假";

			}
			else if (pArgInf.m_dtDataType == SDT_BIN) {//如果为字节集直接返回就可
				if (!pArgInf.m_pBin)return {};
	
				auto p = reinterpret_cast<char*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2);
				auto size = *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t));
				if (!p || size <= 2 || *reinterpret_cast<wchar_t*>(p) == L'\0')return {};
				/*为了保证安全任何情况下都要进行构造*/
				std::vector<char> ret(p, p + size);
				ret.push_back(0); ret.push_back(0);
				return reinterpret_cast<wchar_t*>(ret.data());
				/*if (size <= 2 || *reinterpret_cast<wchar_t*>(p) == L'\0')return {};
				auto maxsize = static_cast<size_t>(std::ceil(size / 2.0f));
				std::wstring ret(L'0', maxsize);
				memcpy(&ret[0], p, size);
				
				if (ret.back() != L'0')
					ret.push_back(L'\0');
				return ret;*/
			}
			else if (pArgInf.m_dtDataType == SDT_DATE_TIME) {

				wchar_t temp[MAX_PATH]{ 0 };
				SYSTEMTIME st = { 0 };
				VariantTimeToSystemTime(pArgInf.m_double, &st);
				wchar_t strFormat[128]{ 0 };
				wcscpy_s(strFormat, L"%d年%d月%d日");
				//格式化时间部分
				wchar_t strFormatTime[128]{ 0 };
				if (st.wSecond)
					wcscpy_s(strFormatTime, L"%d时%d分%d秒");
				else if (st.wMinute && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%d时%d分");
				else if (st.wHour && st.wMinute == 0 && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%d时");
				else
					strFormatTime[0] = L'\0';
				wcscat_s(strFormat, strFormatTime);
				wsprintfW(temp, strFormat, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				return temp;

			}
			return str;
		}

	}

#pragma endregion
}

namespace elibstl::classhelp {
	/*对象*/
	template <typename T>
	auto& get_this(PMDATA_INF pArgInf)
	{
		return reinterpret_cast<T*&>(pArgInf[0].m_ppCompoundData[0]);
	}
	/*其他对象*/
	template <typename T>
	auto& get_other(PMDATA_INF pArgInf)
	{
		return reinterpret_cast<T*&>(pArgInf[1].m_ppCompoundData[0]);
	}
#ifndef _SPAN_
	template<typename T>
	class span {
	public:
		span() = default;
		span(T* ptr, size_t size) : ptr_(ptr), size_(size) {}

		T* data() const { return ptr_; }
		size_t size() const { return size_; }

	private:
		T* ptr_{ nullptr };
		size_t size_{ 0 };
	};
#endif
	class eplarg
	{
		PMDATA_INF m_pArgInf{ nullptr };
		size_t m_size;
	public:
		eplarg(PMDATA_INF pArgInf, size_t size) :m_pArgInf(pArgInf), m_size(size) {};
		auto get_bin(size_t index) -> span<unsigned char> {
			if (index >= m_size)
				return {};
			auto bin = m_pArgInf[index].m_pBin;
			if (!bin)
				return  {};
			size_t lenth = *reinterpret_cast<std::uint32_t*>(bin + sizeof(std::uint32_t));
			auto pbuffer = (bin + sizeof(std::uint32_t) * 2);
			if (lenth > 0)
				return span<unsigned char>(pbuffer, lenth);
			return  {};
		}

	private:
	public:
		static 	
			auto get_bin(PMDATA_INF pArgInf, size_t index) -> span<unsigned char> {
			auto bin = pArgInf[index].m_pBin;
			if (!bin)
				return  {};
			size_t lenth = *reinterpret_cast<std::uint32_t*>(bin + sizeof(std::uint32_t));
			auto pbuffer = (bin + sizeof(std::uint32_t) * 2);
			if (lenth > 0)
				return span<unsigned char>(pbuffer, lenth);
			return  {};
		}
		static
			auto get_bin(MDATA_INF pArgInf) -> span<unsigned char> {
			auto bin = pArgInf.m_pBin;
			if (!bin)
				return  {};
			size_t lenth = *reinterpret_cast<std::uint32_t*>(bin + sizeof(std::uint32_t));
			auto pbuffer = (bin + sizeof(std::uint32_t) * 2);
			if (lenth > 0)
				return span<unsigned char>(pbuffer, lenth);
			return  {};
		}
		static
			auto get_bin(LPBYTE bin) -> span<unsigned char> {
			if (!bin)
				return  {};
			size_t lenth = *reinterpret_cast<std::uint32_t*>(bin + sizeof(std::uint32_t));
			auto pbuffer = (bin + sizeof(std::uint32_t) * 2);
			if (lenth > 0)
				return span<unsigned char>(pbuffer, lenth);
			return  {};
		}
	};



}