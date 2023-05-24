#include "lib2.h"
typedef INT(cdecl* PFN_ON_SYS_NOTIFY) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
#ifndef _private
#define _private  //��ʶΪֻ˽��
#endif
#include<string_view>
#include<stdexcept>
#include<optional>
#include<vector>
#include<string>
#include<map>
namespace elibstl
{
	/*�׿�ͨ��,�����׿������*/





	struct ebin
	{
#pragma warning(disable:4200)
		std::uint32_t m_check;//��Ϊ1
		size_t m_size;//����
		std::uint8_t m_data[0];//�ֽڼ�ָ��
		ebin() {
			m_check = 1;
			m_size = 0;
		}
	};

	inline auto& args_to_ebin(PMDATA_INF pArgInf, size_t index) {
		return *reinterpret_cast<ebin*>(pArgInf[index].m_pBin);
	}


	INT WINAPI ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);
	// ��������ide������Ϣ
	INT WINAPI NotifySys(INT nMsg, DWORD dwParam1, DWORD dwParam2);
	//���԰����Ĵ���
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
		if (pArgInf[index].m_dtDataType == DATA_TYPE::_SDT_NULL)
		{
			return {};
		}
		return reinterpret_cast<T>(pArgInf[index].m_pCompoundData);

	}
	inline std::vector<unsigned char> arg_to_vdata(PMDATA_INF pArgInf, int index) {
		if (pArgInf[index].m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t)) >= 2) {
			//�����ԭʼָ������������ӳ��Ϊstring_view
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

		if (pArgInf[index].m_dtDataType == DATA_TYPE::SDT_TEXT && pArgInf[index].m_pText && *pArgInf[index].m_pText != '\0') {
			//�����ԭʼָ������������ӳ��Ϊstring_view
			return std::string_view(pArgInf[index].m_pText);
		}
		else {

			return std::string_view("");
		}
	}
	inline auto args_to_wsdata(PMDATA_INF pArgInf, int index)
	{
		if (pArgInf[index].m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t)) >= 2 && *reinterpret_cast<wchar_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2) != L'\0') {
			//�����ԭʼָ������������ӳ��Ϊstring_view
			return std::wstring_view(reinterpret_cast<wchar_t*>(pArgInf[index].m_pBin + sizeof(std::uint32_t) * 2));
		}
		else {
			return std::wstring_view();
		}
	}
	inline PCWSTR args_to_pszw(PMDATA_INF pArgInf, int idx)
	{
		if (pArgInf[idx].m_dtDataType == DATA_TYPE::_SDT_NULL)
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

	inline BOOL is_debug(char* szErrText)
	{
		return NotifySys(NRS_GET_PRG_TYPE, reinterpret_cast<DWORD>(szErrText), 0) == PT_DEBUG_RUN_VER;
	}

	// ���������������ڴ�, ��λΪ�ֽ�
	// ����������Ҫ��CRT��ͻ��
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
		//��ָ��������
		std::copy(ps, ps + nTextLen, pd);
		pd[nTextLen] = '\0';
		return pd;
	}
	// �����ֽڼ�, ���������Ը�ʽ���ֽڼ�,1ά����
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
		int count = *pn_data++; //��ȡά��

		int nElementCount = 1; //����Ԫ������
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
		int count = *pn_data++; //��ȡά��

		size_t nElementCount = 1; //����Ԫ������
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
		int count = *pn_data++; //��ȡά��
		int nElementCount = 1; //����Ԫ������
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
		int count = *pn_data++; //��ȡά��
		int nElementCount = 1; //����Ԫ������
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
	//��ȡ������ά��
	inline int get_array_dimension(LPVOID n_pAryData) {
		return static_cast<int*>(n_pAryData)[0];
	}
	//��ȡ�������Ӧά�ĳ�Ա����ָ���ά����
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







	/*�����ศ������*/

//�Ƿ�Ϊ����
	inline bool is_array(const MDATA_INF& pArgInf) {
		return	(pArgInf.m_dtDataType & DT_IS_ARY) == DT_IS_ARY;
	}
	//�Ƴ������־
	inline void remove_array_flags(PMDATA_INF pArgInf) {
		pArgInf->remove_dt_flag();
	}
	// ��������־
	inline void add_array_flags(PMDATA_INF pArgInf) {
		pArgInf->add_dt_flag();
	}
	//ȡ�������ͳ���
	inline size_t get_esys_datatype_size(DATA_TYPE pArgInf)
	{
		static  const std::map<DATA_TYPE, size_t> dataSizes = {
			{DATA_TYPE::SDT_BYTE, sizeof(BYTE)},
			{DATA_TYPE::SDT_SHORT, sizeof(SHORT)},
			{DATA_TYPE::SDT_BOOL, sizeof(BOOL)},
			{DATA_TYPE::SDT_INT, sizeof(INT)},
			{DATA_TYPE::SDT_FLOAT, sizeof(FLOAT)},
			{DATA_TYPE::SDT_SUB_PTR, sizeof(DWORD)},
			{DATA_TYPE::SDT_TEXT, sizeof(DWORD)},
			{DATA_TYPE::SDT_BIN, sizeof(DWORD)},
			{DATA_TYPE::SDT_INT64, sizeof(INT64)},
			{DATA_TYPE::SDT_DOUBLE, sizeof(DOUBLE)},
			{DATA_TYPE::SDT_DATE_TIME, sizeof(DATE)}
		};
		auto iter = dataSizes.find(pArgInf);
		if (iter != dataSizes.end()) {
			return iter->second;
		}
		return 0u;
	}
	/*��ȷ����Ϊ��*/
	inline bool wstring_to_arg(PMDATA_INF pArgInf, const std::wstring& str) {

		switch (pArgInf->m_dtDataType)
		{
		case DATA_TYPE::SDT_TEXT:
			efree(*pArgInf->m_ppText);
			*pArgInf->m_ppText = clone_text(str);
			break;
		case DATA_TYPE::SDT_BIN:
			efree(*pArgInf->m_ppBin);
			*pArgInf->m_ppBin = clone_textw(str);
			break;
		case DATA_TYPE::SDT_BYTE:
			*pArgInf->m_pByte = (BYTE)_wtoi(str.c_str());
			break;
		case DATA_TYPE::SDT_SHORT:
			*pArgInf->m_pShort = (SHORT)_wtoi(str.c_str());
			break;
		case DATA_TYPE::SDT_INT:
			*pArgInf->m_pInt = _wtoi(str.c_str());
			break;
		case DATA_TYPE::SDT_INT64:
			*pArgInf->m_pInt64 = _wtoi64(str.c_str());
			break;
		case DATA_TYPE::SDT_FLOAT:
			*pArgInf->m_pFloat = (FLOAT)_wtof(str.c_str());
			break;
		case DATA_TYPE::SDT_DOUBLE:
			*pArgInf->m_pDouble = _wtof(str.c_str());
			break;
		default:
			return false;
		}
		return true;
	}

	//�������ı�,�˴���Ὣ�׻������͸�ʽ��Ϊ�ı���������105���Ϊ"105"
	inline std::wstring arg_to_wstring(MDATA_INF pArgInf) {

		if (is_array(pArgInf))//������
		{
			remove_array_flags(&pArgInf); //ȥ�������־

			auto szData = get_esys_datatype_size(pArgInf.m_dtDataType);

			wchar_t* ret = nullptr;

			if (szData != 0) {
				auto array_to_string = [](void* pArry, size_t szData) -> wchar_t* {
					size_t dwSize;

					auto pText = elibstl::get_array_element_inf<wchar_t*>(pArry, &dwSize);

					if (dwSize == 0)
						return nullptr;

					//�����ܴ��ڵ�unicode�ַ���
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
			//�����Ƿ�ת���ɹ�������ӻ������־
			//pArgInf.add_array_flags();�ǿ���ȡ��

			if (ret)
				return ret;
			else
				return {};
		}
		else
		{
			std::wstring str;

			if (pArgInf.m_dtDataType == DATA_TYPE::SDT_TEXT) {
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
			//����ֵ����
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BYTE || pArgInf.m_dtDataType == DATA_TYPE::SDT_SHORT || pArgInf.m_dtDataType == DATA_TYPE::SDT_INT ||
				pArgInf.m_dtDataType == DATA_TYPE::SDT_SUB_PTR) {
				intptr_t nVal = 0;
				if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BYTE)
					nVal = pArgInf.m_byte;
				else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_SHORT)
					nVal = pArgInf.m_short;
				else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_INT)
					nVal = pArgInf.m_int;
				else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_SUB_PTR)
					nVal = pArgInf.m_int;
				return  std::to_wstring(nVal);
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_INT64) {
				return  std::to_wstring(pArgInf.m_int64);
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_FLOAT) {
				str = std::to_wstring(pArgInf.m_float);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_DOUBLE) {
				str = std::to_wstring(pArgInf.m_double);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();

			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BOOL) {
				if (pArgInf.m_bool)
					return  L"��";
				else
					return  L"��";

			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BIN) {//���Ϊ�ֽڼ�ֱ�ӷ��ؾͿ�
				if (pArgInf.m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t)) >= 2 && *reinterpret_cast<wchar_t*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2) != L'\0') {
					//�����ԭʼָ������������ӳ��Ϊstring_view
					return std::wstring(reinterpret_cast<wchar_t*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2), *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t));
				}
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_DATE_TIME) {

				wchar_t temp[MAX_PATH]{ 0 };
				SYSTEMTIME st = { 0 };
				VariantTimeToSystemTime(pArgInf.m_double, &st);
				wchar_t strFormat[128]{ 0 };
				wcscpy_s(strFormat, L"%d��%d��%d��");
				//��ʽ��ʱ�䲿��
				wchar_t strFormatTime[128]{ 0 };
				if (st.wSecond)
					wcscpy_s(strFormatTime, L"%dʱ%d��%d��");
				else if (st.wMinute && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%dʱ%d��");
				else if (st.wHour && st.wMinute == 0 && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%dʱ");
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
		if (is_array(pArgInf))//������
		{
			remove_array_flags(&pArgInf); //ȥ�������־

			auto szData = get_esys_datatype_size(pArgInf.m_dtDataType);

			wchar_t* ret = nullptr;

			if (szData != 0) {
				auto array_to_string = [](void* pArry, size_t szData) -> wchar_t* {
					size_t dwSize;

					auto pText = elibstl::get_array_element_inf<wchar_t*>(pArry, &dwSize);

					if (dwSize == 0)
						return nullptr;

					//�����ܴ��ڵ�unicode�ַ���
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
			//�����Ƿ�ת���ɹ�������ӻ������־
			//pArgInf.add_array_flags();�ǿ���ȡ��

			if (ret)
				return ret;
			else
				return {};
		}
		else
		{
			std::wstring str;

			if (pArgInf.m_dtDataType == DATA_TYPE::SDT_TEXT) {
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
			//����ֵ����
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BYTE || pArgInf.m_dtDataType == DATA_TYPE::SDT_SHORT || pArgInf.m_dtDataType == DATA_TYPE::SDT_INT ||
				pArgInf.m_dtDataType == DATA_TYPE::SDT_SUB_PTR) {
				intptr_t nVal = 0;
				if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BYTE)
					nVal = pArgInf.m_byte;
				else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_SHORT)
					nVal = pArgInf.m_short;
				else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_INT)
					nVal = pArgInf.m_int;
				else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_SUB_PTR)
					nVal = pArgInf.m_int;
				return  std::to_wstring(nVal);
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_INT64) {
				return  std::to_wstring(pArgInf.m_int64);
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_FLOAT) {
				str = std::to_wstring(pArgInf.m_float);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_DOUBLE) {
				str = std::to_wstring(pArgInf.m_double);
				str = str.substr(0, str.find_last_not_of(L'0') + 1);
				if (str.back() == L'.')
					str.pop_back();

			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BOOL) {
				if (pArgInf.m_bool)
					return  L"��";
				else
					return  L"��";

			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_BIN) {//���Ϊ�ֽڼ�ֱ�ӷ��ؾͿ�
				if (pArgInf.m_pBin && *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t)) >= 2 && *reinterpret_cast<wchar_t*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2) != L'\0') {
					//�����ԭʼָ������������ӳ��Ϊstring_view
					return std::wstring(reinterpret_cast<wchar_t*>(pArgInf.m_pBin + sizeof(std::uint32_t) * 2), *reinterpret_cast<std::uint32_t*>(pArgInf.m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t));
				}
			}
			else if (pArgInf.m_dtDataType == DATA_TYPE::SDT_DATE_TIME) {

				wchar_t temp[MAX_PATH]{ 0 };
				SYSTEMTIME st = { 0 };
				VariantTimeToSystemTime(pArgInf.m_double, &st);
				wchar_t strFormat[128]{ 0 };
				wcscpy_s(strFormat, L"%d��%d��%d��");
				//��ʽ��ʱ�䲿��
				wchar_t strFormatTime[128]{ 0 };
				if (st.wSecond)
					wcscpy_s(strFormatTime, L"%dʱ%d��%d��");
				else if (st.wMinute && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%dʱ%d��");
				else if (st.wHour && st.wMinute == 0 && st.wSecond == 0)
					wcscpy_s(strFormatTime, L"%dʱ");
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