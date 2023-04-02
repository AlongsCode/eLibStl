#include "lib2.h"
typedef INT(cdecl* PFN_ON_SYS_NOTIFY) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
#ifndef _private
#define _private  //称识为只私有
#endif
#include<string_view>
#include<stdexcept>
#include<optional>
#include<vector>
#include<string>
namespace elibstl
{
	/*易库通信,调用易库命令等*/










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
	std::optional<T> args_to_data(PMDATA_INF pArgInf, int index)
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
		return reinterpret_cast<T>(pArgInf[index].m_pCompoundData);
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
			return std::wstring_view(reinterpret_cast<wchar_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2), *reinterpret_cast<std::uint32_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t));
		}
		else {
			return std::wstring_view();
		}
	}

	inline HBITMAP make_hbit(LPBYTE pData, size_t nSize) {
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

	inline BOOL is_debug(char* szErrText)
	{
		return NotifySys(NRS_GET_PRG_TYPE, reinterpret_cast<DWORD>(szErrText), 0) == PT_DEBUG_RUN_VER;
	}

	// 从易语言里申请内存, 单位为字节
	inline void* malloc(int size)
	{
		void* pMem = (void*)NotifySys(NRS_MALLOC, size, 0);
		memset(pMem, 0, size);
		return (void*)pMem;
	}

	inline void free(void* p)
	{
		NotifySys(NRS_MFREE, reinterpret_cast<DWORD>(p), 0);
	}


	inline char* clone_text(char* ps)
	{
		if (ps == nullptr || *ps == '\0')
			return nullptr;
		std::string_view s(ps);
		const INT nTextLen = s.length();
		char* pd = static_cast<char*>(malloc(nTextLen + 1));
		std::copy(s.begin(), s.end(), pd);
		pd[nTextLen] = '\0';
		return pd;
	}
	inline char* clone_text(const std::string& s)
	{
		const INT nTextLen = s.length();
		char* pd = static_cast<char*>(malloc(nTextLen + 1));
		std::copy(s.begin(), s.end(), pd);
		pd[nTextLen] = '\0';
		return pd;
	}


	inline char* clone_text(const std::wstring& s)
	{
		const INT nTextLen = s.length();
		const INT nAnsiLen = WideCharToMultiByte(CP_ACP, 0, s.data(), nTextLen, nullptr, 0, nullptr, nullptr);
		char* pd = static_cast<char*>(malloc(nAnsiLen + 1));
		WideCharToMultiByte(CP_ACP, 0, s.data(), nTextLen, pd, nAnsiLen + 1, nullptr, nullptr);
		return pd;
	}
	inline char* clone_text(char* ps, INT nTextLen)
	{
		if (nTextLen <= 0)
			return nullptr;
		char* pd = static_cast<char*>(malloc(nTextLen + 1));
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

		LPBYTE pd = static_cast<LPBYTE>(malloc(sizeof(std::uint32_t) * 2 + nDataSize));
		std::copy(pData, pData + nDataSize, pd + sizeof(std::uint32_t) * 2);
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(std::uint32_t)) = nDataSize;
		return pd;
	}
	inline LPBYTE clone_textw(const std::wstring& s)
	{
		const INT nLen = s.length() * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(malloc(nLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, s.data(), nLen);
		return pd;
	}
	inline LPBYTE clone_textw(LPCWSTR ps)
	{
		if (ps == nullptr || *ps == '\0')
			return nullptr;
		const INT nTextLen = static_cast<INT>(wcslen(ps));
		const INT nWideLen = nTextLen * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(malloc(nWideLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nWideLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, ps, nWideLen);
		return pd;
	}
	inline LPBYTE clone_textw(LPCWSTR ps, INT nTextLen)
	{
		if (ps == nullptr || *ps == '\0' || nTextLen == 0)
			return nullptr;
		const INT nWideLen = nTextLen * sizeof(wchar_t);
		LPBYTE pd = static_cast<LPBYTE>(malloc(nWideLen + sizeof(uint32_t) * 2));
		*reinterpret_cast<std::uint32_t*>(pd) = 1;
		*reinterpret_cast<std::uint32_t*>(pd + sizeof(uint32_t)) = nWideLen;
		std::memcpy(pd + sizeof(uint32_t) * 2, ps, nWideLen);
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
		const auto p = static_cast<LPBYTE>(malloc(sizeof(T) * nCount + 8));
		*reinterpret_cast<LPINT>(p) = 1;
		*reinterpret_cast<LPINT>(p + 4) = nCount;
		return p;
	}

	inline void* empty_array() {
		const auto p = static_cast<LPBYTE>(malloc(sizeof(int) * 2));
		*reinterpret_cast<LPINT>(p) = 1;
		*reinterpret_cast<LPINT>(p + 4) = 0;
		return p;
	}
	//获取多数组维数
	inline int get_array_dimension(LPVOID n_pAryData) {
		return static_cast<int*>(n_pAryData)[0];
	}
	//获取多数组对应维的成员数，指针和维索引
	inline int get_array_count(void* pBase, INT dimension)
	{
		return reinterpret_cast<INT*>(static_cast<char*>(pBase) + dimension * sizeof(INT))[0];
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
#pragma endregion
}