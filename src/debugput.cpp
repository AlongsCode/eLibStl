#include <sstream>  
#include <iomanip>
#include"ElibHelp.h"


static ARG_INFO Args[] =
{
		{
		/*name*/	"�����ֵ",
		/*explain*/	"���ڷǡ��ı��͡����������Զ�ת��Ϊ�ı����������ɽ�������������ͣ��������������Լ��Զ����������͡�",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::_SDT_ALL,
		/*default*/	0,
		/*state*/	AS_DEFAULT_VALUE_IS_EMPTY | AS_RECEIVE_ALL_TYPE_DATA,
			}
};

/*�ֽڼ�ת�ı�*/

template <typename T>
inline std::basic_string<T> ByteArrayToString(const std::vector<unsigned char>& byteVector) {
	if (byteVector.empty()) {
		return std::basic_string<T>();
	}

	const size_t length = byteVector.size();
	std::vector<T> buffer(length * 4 + sizeof("{}"));

	size_t bufferIndex = 0;
	buffer[bufferIndex++] = '{';

	for (const auto byte : byteVector) {
		auto hundreds = byte / 100;
		auto tens = byte % 100 / 10;
		auto ones = byte % 10;

		if (hundreds > 0) {
			buffer[bufferIndex++] = hundreds + T('0');
			buffer[bufferIndex++] = tens + T('0');
		}
		else if (tens > 0) {
			buffer[bufferIndex++] = tens + T('0');
		}
		buffer[bufferIndex++] = ones + T('0');
		buffer[bufferIndex++] = ',';
	}
	buffer[bufferIndex - 1] = '}';

	return std::basic_string<T>(buffer.data(), bufferIndex);
}


/*����������ԭ��*/
inline std::string DateTimeFormat(DATE dtDt)
{
	SYSTEMTIME st = { 0 };
	VariantTimeToSystemTime(dtDt, &st);
	std::ostringstream ss;
	ss << st.wYear << "��" << st.wMonth << "��" << st.wDay << "��";
	ss << std::setfill('0') << std::right << " " << std::setw(2) << st.wHour << "ʱ" << std::setw(2) << st.wMinute << "��";
	if (st.wSecond)
	{
		ss << std::setw(2) << st.wSecond << "��";
	}
	return ss.str();
}

// ��ӡ���������ĺ���
static void printParam(std::ostringstream& oss, const PMDATA_INF& param)
{
	// �����������ͽ��з�֧����
	switch (param->m_dtDataType)
	{
	case DATA_TYPE::SDT_INT:
		oss << param->m_int << " | "; break;
	case DATA_TYPE::SDT_SHORT:
		oss << param->m_short << " | "; break;
	case DATA_TYPE::SDT_BYTE:
		oss << static_cast<int>(param->m_byte) << " | "; break;
	case DATA_TYPE::SDT_INT64:
		oss << param->m_int64 << " | "; break;
	case DATA_TYPE::SDT_FLOAT:
		oss << param->m_float << " | "; break;
	case DATA_TYPE::SDT_DOUBLE:
		oss << param->m_double << " | "; break;
	case DATA_TYPE::SDT_BOOL:
		oss << (param->m_bool ? "true" : "false") << " | "; break;
	case DATA_TYPE::SDT_TEXT:
	{
		const char* pText = param->m_pText;
		if (pText == nullptr || *pText == '\0')
		{
			oss << "[���ı�] | ";
		}
		else
		{
			oss << "[�ı�:" << strlen(pText) << "] ��" << pText << "�� | ";
		}
		break;
	}
	case DATA_TYPE::SDT_BIN:
	{
		const auto& bytes = elibstl::arg_to_vdata(param->m_pBin);
		oss << "[�ֽڼ�:" << bytes.size() << "] " << ByteArrayToString<char>(bytes) << " | ";
		break;
	}
	case DATA_TYPE::SDT_DATE_TIME:
		oss << "[" << DateTimeFormat(param->m_date) << "] | "; break;
	case DATA_TYPE::SDT_SUB_PTR:
		oss << "(�ӳ����ַ:" << param->m_dwSubCodeAdr << ") | "; break;
	case DATA_TYPE::_SDT_NULL:
		oss << "(��) | "; break;
	default:
		oss << "(?δ֪?) | "; break;
	}
}



inline int GetTypeSize(const int dtDataType) {
	switch (dtDataType) {
	case DATA_TYPE::SDT_INT:
		return sizeof(INT);
	case DATA_TYPE::SDT_SHORT:
		return sizeof(SHORT);
	case DATA_TYPE::SDT_BYTE:
		return sizeof(BYTE);
	case DATA_TYPE::SDT_INT64:
		return sizeof(INT64);
	case DATA_TYPE::SDT_FLOAT:
		return sizeof(FLOAT);
	case DATA_TYPE::SDT_DOUBLE:
		return sizeof(DOUBLE);
	case DATA_TYPE::SDT_BOOL:
		return sizeof(BOOL);
	case DATA_TYPE::SDT_TEXT:
		return sizeof(LPVOID);
	case DATA_TYPE::SDT_BIN:
		return sizeof(LPVOID);
	case DATA_TYPE::SDT_DATE_TIME:
		return sizeof(DATE);
	case DATA_TYPE::SDT_SUB_PTR:
		return sizeof(LPVOID);
	case DATA_TYPE::_SDT_NULL:
		return 1;
	default:
		return 1;
	}
}

static void printParamArray(std::ostringstream& oss, PMDATA_INF pParam)
{

	const int nDimension = elibstl::get_array_dimension(pParam->m_pAryData);
	oss << "[" << nDimension << "ά����:";
	int nElementCount = 0;
	for (int i = 0; i < nDimension; i++) {
		oss << (i == 0 ? "" : "-") << elibstl::get_array_count(pParam->m_pAryData, i + 1);
		if (i == 0)
		{
			nElementCount = elibstl::get_array_count(pParam->m_pAryData, 1);
		}
		else
		{
			nElementCount *= elibstl::get_array_count(pParam->m_pAryData, i + 1);
		}


	}
	oss << "] {";
	const auto pStart = reinterpret_cast<const LPBYTE>(pParam->m_pAryData) + (nDimension + 1) * sizeof(INT);
	const auto pEnd = pStart + nElementCount * GetTypeSize(pParam->m_dtDataType);
	std::string s = ", ";
	for (auto p = pStart; p < pEnd; p += GetTypeSize(pParam->m_dtDataType)) {

		if (p + GetTypeSize(pParam->m_dtDataType) == pEnd) {
			s = "";
		}
		switch (pParam->m_dtDataType)
		{
		case DATA_TYPE::SDT_INT:
			oss << *(INT*)p;
			break;
		case DATA_TYPE::SDT_SHORT:
			oss << *(SHORT*)p;
			break;
		case DATA_TYPE::SDT_BYTE:
			oss << static_cast<int>(*(BYTE*)p);
			break;
		case DATA_TYPE::SDT_INT64:
			oss << *(INT64*)p;
			break;
		case DATA_TYPE::SDT_FLOAT:
			oss << *(FLOAT*)p;
			break;
		case DATA_TYPE::SDT_DOUBLE:
			oss << *(DOUBLE*)p;
			break;
		case DATA_TYPE::SDT_BOOL:
			oss << ((*(BOOL*)p) == TRUE ? "��" : "��");
			break;
		case DATA_TYPE::SDT_TEXT:
		{
			char* pText = (char*)(*(LPVOID*)p);
			if (pText == NULL || strlen(pText) == 0)
			{
				oss << "���ı�:����";
				break;
			}
			oss << "�ı�:" << strlen(pText) << "��" << std::string(pText) << "��";

			break;
		}
		case DATA_TYPE::SDT_BIN:
		{

			if ((*(LPVOID*)p) == 0)
			{
				oss << "�ֽڼ�:0{}";
				break;
			}
			std::vector<unsigned char> pBin = elibstl::arg_to_vdata((LPBYTE)(*(LPVOID*)p));
			oss << "�ֽڼ�:" << pBin.size() << "{";
			for (size_t i = 0; i < pBin.size(); i++)
			{
				oss << static_cast<int>(pBin.data()[i]);
				oss << ",";
			}
			oss.seekp(-1, std::ios_base::end); // ɾ�����һ������
			oss << "} ";
			break;
		}
		case DATA_TYPE::SDT_DATE_TIME:
		{
			const DATE temp = *(DATE*)p;  p += sizeof(DATE);
			oss << "[" << DateTimeFormat(temp) << "],";
			break;
		}
		case DATA_TYPE::SDT_SUB_PTR:
			oss << "(�ӳ����ַ:" + std::to_string(*reinterpret_cast<const DWORD*>(p));
			break;
		case DATA_TYPE::_SDT_NULL:
			oss << "(��)";
			break;
		default:
			oss << "(?δ֪?)";
			break;
		}
		oss << s;
	}
	//oss.seekp(-1, std::ios::end);
	oss << "} | ";
}







EXTERN_C void Fn_debugput(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	std::ostringstream str;
	for (int i = 0; i < nArgCount; i++)
	{
		PMDATA_INF pParam = &pArgInf[i];
		BOOL bIsArray = pParam->is_dt_flag();/*ʱ������*/
		if (bIsArray) pParam->remove_dt_flag();/*�Ƴ������־*/
		if (!bIsArray) //����Ϊ���������
		{
			printParam(str, pParam);
		}
		else //����Ϊ��������
		{
			printParamArray(str, pParam);
		}
	}
	//��" | "ȥ��
	if (str.str().size() >= 3) {
		str.str(str.str().substr(0, str.str().size() - 3));
	}
	MDATA_INF RetData, ArgInf;
	ArgInf.m_dtDataType = DATA_TYPE::SDT_TEXT;
	char* pDebugText = elibstl::clone_text(str.str());
	ArgInf.m_pText = pDebugText;
	elibstl::CallElibFunc("krnln.fne", "��������ı�", &RetData, 1, &ArgInf);

}

FucInfo e_debugput = { {
		/*ccname*/  ("����"),
		/*egname*/  ("debugput"),
		/*explain*/ ("ͬ�����Ե������"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_debugput ,"Fn_debugput" };





static ARG_INFO Args2[] =
{
		{
		/*name*/	"���������",
		/*explain*/	"��ȷ��������ȷ��",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	DATA_TYPE::SDT_BIN,
		/*default*/	0,
		/*state*/	NULL,
			}
};
namespace elibstl {
	void e_debugbox_putimg(unsigned char* pPicData, size_t cbSize);
	void _w_e_debugbox_put(const std::wstring_view& wstr);
}


#pragma comment (lib,"Crypt32.lib")
inline std::string StringToBase64(const std::vector<unsigned char>& image)
{

	std::string base64String;
	DWORD base64Length = 0;

	// ��ȡ Base64 �������ַ�������
	if (::CryptBinaryToStringA(image.data(),
		image.size(),
		CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
		nullptr, &base64Length)) {
		base64String.resize(base64Length);

		// ������������ת��Ϊ Base64 ������ַ���
		if (::CryptBinaryToStringA(image.data(),
			image.size(),
			CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
			&base64String[0], &base64Length)) {
			return base64String;
		}
	}

	// ʧ��ʱ���ؿ��ַ���
	return "";
}

#include <OleCtl.h>

inline HBITMAP GetImageToBitmap(const BYTE* imageData, int imageSize)
{
	HBITMAP hBitmap = NULL;
	if (imageSize > 0)
	{
		HGLOBAL hImageMemory = GlobalAlloc(GMEM_MOVEABLE, imageSize);
		if (hImageMemory != NULL)
		{
			LPVOID pImageMemory = GlobalLock(hImageMemory);
			memcpy(pImageMemory, imageData, imageSize);
			GlobalUnlock(hImageMemory);

			IStream* pIStream = NULL;
			if (CreateStreamOnHGlobal(hImageMemory, FALSE, &pIStream) == S_OK && pIStream != NULL)
			{
				IPicture* pIPicture = NULL;
				if (OleLoadPicture(pIStream, imageSize, FALSE, IID_IPicture, (LPVOID*)&pIPicture) == S_OK && pIPicture != NULL)
				{
					LONG_PTR pHandle = NULL;
					if (pIPicture->get_Handle((OLE_HANDLE*)&pHandle) == S_OK && pHandle != NULL)
					{
						hBitmap = (HBITMAP)CopyImage((HBITMAP)pHandle, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
					}
					pIPicture->Release();
				}
				pIStream->Release();
			}
			GlobalFree(hImageMemory);
		}
	}
	return hBitmap;
}
inline void SetImageToClipboard(const std::vector<unsigned char>& imageData)
{
	HBITMAP hBitmap = NULL;
	// ��ͼƬ����ת��Ϊλͼ
	hBitmap = GetImageToBitmap(imageData.data(), imageData.size());
	if (hBitmap == NULL)
	{

		hBitmap = elibstl::make_hbm(const_cast<unsigned char*>(imageData.data()), imageData.size());
	}

	// ��λͼ���õ�������
	if (hBitmap != NULL && OpenClipboard(NULL))
	{
		EmptyClipboard();
		SetClipboardData(CF_BITMAP, hBitmap);
		CloseClipboard();
	}
}
EXTERN_C void Fn_debugput_img(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	for (int i = 0; i < nArgCount; i++)
	{
		auto data = elibstl::arg_to_vdata(pArgInf, i);

		MDATA_INF RetData, ArgInf;
		ArgInf.m_dtDataType = DATA_TYPE::SDT_TEXT;
		/*ͼƬ�Ļ��ü�����*/
		char* pDebugText = elibstl::clone_text("[elbbstl::image]");
		SetImageToClipboard(data);
		ArgInf.m_pText = pDebugText;
		elibstl::CallElibFunc("krnln.fne", "��������ı�", &RetData, 1, &ArgInf);
	}
}


FucInfo e_debugput_img = { {
		/*ccname*/  ("����ͼƬ"),
		/*egname*/  ("debugputimg"),
		/*explain*/ ("��������ֽ���ͼƬ"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ Args2,
	} ,Fn_debugput_img ,"Fn_debugput_img" };
/*�����ַ�תΪ��Ӧ��ʮ�����Ʊ�ʾ*/
inline std::string UmakeA(const std::wstring_view& wstr)
{
	std::ostringstream oss;

	for (const auto& ch : wstr)
	{
		int unicodeValue = static_cast<int>(ch);
		oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << unicodeValue;
	}

	return oss.str();
}




EXTERN_C void Fn_debugput_w(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	for (int i = 0; i < nArgCount; i++)
	{
		auto data = elibstl::args_to_wsdata(pArgInf, i);
		std::string str = "";

		MDATA_INF RetData, ArgInf;
		ArgInf.m_dtDataType = DATA_TYPE::SDT_TEXT;

		char* pDebugText = elibstl::clone_text("[unicode�ı�:" + std::to_string(data.size()) + " ] " + UmakeA(data));
		ArgInf.m_pText = pDebugText;
		elibstl::CallElibFunc("krnln.fne", "��������ı�", &RetData, 1, &ArgInf);
	}


}
FucInfo e_debugput_w = { {
		/*ccname*/  ("����W"),
		/*egname*/  ("_wdebugput"),
		/*explain*/ ("����������������ַ�,������Կ��ַ��Ϸ��Խ��м��"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     DATA_TYPE::_SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ Args2,
	} ,Fn_debugput_w ,"Fn_debugput_w" };

