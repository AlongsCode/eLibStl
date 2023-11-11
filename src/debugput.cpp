#include <sstream>  
#include <iomanip>
#include"ElibHelp.h"


static ARG_INFO Args[] =
{
		{
		/*name*/	"欲输出值",
		/*explain*/	"对于非“文本型”参数，将自动转换为文本。本参数可接受任意基本类型，但不接受数组以及自定义数据类型。",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	_SDT_ALL,
		/*default*/	0,
		/*state*/	ArgMark::AS_DEFAULT_VALUE_IS_EMPTY | ArgMark::AS_RECEIVE_ALL_TYPE_DATA,
			}
};

/*字节集转文本*/

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


/*兼容易语言原版*/
inline std::string DateTimeFormat(DATE dtDt)
{
	SYSTEMTIME st = { 0 };
	VariantTimeToSystemTime(dtDt, &st);
	std::ostringstream ss;
	ss << st.wYear << "年" << st.wMonth << "月" << st.wDay << "日";
	ss << std::setfill('0') << std::right << " " << std::setw(2) << st.wHour << "时" << std::setw(2) << st.wMinute << "分";
	if (st.wSecond)
	{
		ss << std::setw(2) << st.wSecond << "秒";
	}
	return ss.str();
}

// 打印单个参数的函数
static void printParam(std::ostringstream& oss, const PMDATA_INF& param)
{
	// 根据数据类型进行分支处理
	switch (param->m_dtDataType)
	{
	case SDT_INT:
		oss << param->m_int << " | "; break;
	case SDT_SHORT:
		oss << param->m_short << " | "; break;
	case SDT_BYTE:
		oss << static_cast<int>(param->m_byte) << " | "; break;
	case SDT_INT64:
		oss << param->m_int64 << " | "; break;
	case SDT_FLOAT:
		oss << param->m_float << " | "; break;
	case SDT_DOUBLE:
		oss << param->m_double << " | "; break;
	case SDT_BOOL:
		oss << (param->m_bool ? "真" : "假") << " | "; break;
	case SDT_TEXT:
	{
		const char* pText = param->m_pText;
		if (pText == nullptr || *pText == '\0')
		{
			oss << "[空文本] | ";
		}
		else
		{
			oss << "[文本:" << strlen(pText) << "] “" << pText << "” | ";
		}
		break;
	}
	case SDT_BIN:
	{
		const auto& bytes = elibstl::arg_to_vdata(param->m_pBin);
		oss << "[字节集:" << bytes.size() << "] " << ByteArrayToString<char>(bytes) << " | ";
		break;
	}
	case SDT_DATE_TIME:
		oss << "[" << DateTimeFormat(param->m_date) << "] | "; break;
	case SDT_SUB_PTR:
		oss << "(子程序地址:" << param->m_dwSubCodeAdr << ") | "; break;
	case _SDT_NULL:
		oss << "(空) | "; break;
	default:
		oss << "(?未知?) | "; break;
	}
}



inline int GetTypeSize(const int dtDataType) {
	switch (dtDataType) {
	case SDT_INT:
		return sizeof(INT);
	case SDT_SHORT:
		return sizeof(SHORT);
	case SDT_BYTE:
		return sizeof(BYTE);
	case SDT_INT64:
		return sizeof(INT64);
	case SDT_FLOAT:
		return sizeof(FLOAT);
	case SDT_DOUBLE:
		return sizeof(DOUBLE);
	case SDT_BOOL:
		return sizeof(BOOL);
	case SDT_TEXT:
		return sizeof(LPVOID);
	case SDT_BIN:
		return sizeof(LPVOID);
	case SDT_DATE_TIME:
		return sizeof(DATE);
	case SDT_SUB_PTR:
		return sizeof(LPVOID);
	case _SDT_NULL:
		return 1;
	default:
		return 1;
	}
}

static void printParamArray(std::ostringstream& oss, PMDATA_INF pParam)
{

	const int nDimension = elibstl::get_array_dimension(pParam->m_pAryData);
	oss << "[" << nDimension << "维数组:";
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
		case SDT_INT:
			oss << *(INT*)p;
			break;
		case SDT_SHORT:
			oss << *(SHORT*)p;
			break;
		case SDT_BYTE:
			oss << static_cast<int>(*(BYTE*)p);
			break;
		case SDT_INT64:
			oss << *(INT64*)p;
			break;
		case SDT_FLOAT:
			oss << *(FLOAT*)p;
			break;
		case SDT_DOUBLE:
			oss << *(DOUBLE*)p;
			break;
		case SDT_BOOL:
			oss << ((*(BOOL*)p) == TRUE ? "真" : "假");
			break;
		case SDT_TEXT:
		{
			char* pText = (char*)(*(LPVOID*)p);
			if (pText == NULL || strlen(pText) == 0)
			{
				oss << "空文本:“”";
				break;
			}
			oss << "文本:" << strlen(pText) << "“" << std::string(pText) << "”";

			break;
		}
		case SDT_BIN:
		{

			if ((*(LPVOID*)p) == 0)
			{
				oss << "字节集:0{}";
				break;
			}
			std::vector<unsigned char> pBin = elibstl::arg_to_vdata((LPBYTE)(*(LPVOID*)p));
			oss << "字节集:" << pBin.size() << "{";
			for (size_t i = 0; i < pBin.size(); i++)
			{
				oss << static_cast<int>(pBin.data()[i]);
				oss << ",";
			}
			oss.seekp(-1, std::ios_base::end); // 删除最后一个逗号
			oss << "} ";
			break;
		}
		case SDT_DATE_TIME:
		{
			const DATE temp = *(DATE*)p;  p += sizeof(DATE);
			oss << "[" << DateTimeFormat(temp) << "],";
			break;
		}
		case SDT_SUB_PTR:
			oss << "(子程序地址:" + std::to_string(*reinterpret_cast<const DWORD*>(p));
			break;
		case _SDT_NULL:
			oss << "(空)";
			break;
		default:
			oss << "(?未知?)";
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
		BOOL bIsArray = pParam->is_dt_flag(); //判断是否为数组
		if (bIsArray) pParam->remove_dt_flag();
		if (!bIsArray) //参数为非数组情况
		{
			printParam(str, pParam);
		}
		else //参数为数组的情况
		{
			printParamArray(str, pParam);
		}
	}
	
	//把" | "去掉
	if (str.str().size() >= 3) {
		str.str(str.str().substr(0, str.str().size() - 3));
	}
	OutputDebugStringA(("* " + str.str()).c_str());
}

FucInfo e_debugput = { {
		/*ccname*/  ("调试"),
		/*egname*/  ("debugput"),
		/*explain*/ ("同易语言调试输出"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_debugput ,"Fn_debugput" };





static ARG_INFO Args2[] =
{
		{
		/*name*/	"欲输出内容",
		/*explain*/	"请确保对象正确。",
		/*bmp inx*/	0,
		/*bmp num*/	0,
		/*type*/	SDT_BIN,
		/*default*/	0,
		/*state*/	ArgMark::AS_NONE,
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

	// 获取 Base64 编码后的字符串长度
	if (::CryptBinaryToStringA(image.data(),
		image.size(),
		CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
		nullptr, &base64Length)) {
		base64String.resize(base64Length);

		// 将二进制数据转换为 Base64 编码的字符串
		if (::CryptBinaryToStringA(image.data(),
			image.size(),
			CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
			&base64String[0], &base64Length)) {
			return base64String;
		}
	}

	// 失败时返回空字符串
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
	// 将图片数据转换为位图
	hBitmap = GetImageToBitmap(imageData.data(), imageData.size());
	if (hBitmap == NULL)
	{

		hBitmap = elibstl::make_hbm(const_cast<unsigned char*>(imageData.data()), imageData.size());
	}

	// 将位图设置到剪贴板
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
		ArgInf.m_dtDataType = SDT_TEXT;
		/*图片的话置剪辑板*/
		char* pDebugText = elibstl::clone_text("[elibstl::image]");
		SetImageToClipboard(data);
		ArgInf.m_pText = pDebugText;
		elibstl::CallElibFunc("krnln.fne", "输出调试文本", &RetData, 1, &ArgInf);
	}
}


FucInfo e_debugput_img = { {
		/*ccname*/  ("调试图片"),
		/*egname*/  ("debugputimg"),
		/*explain*/ ("调试输出字节流图片"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ Args2,
	} ,Fn_debugput_img ,"Fn_debugput_img" };
/*将宽字符转为对应的十六进制表示*/
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
		ArgInf.m_dtDataType = SDT_TEXT;

		char* pDebugText = elibstl::clone_text("[unicode文本:" + std::to_string(data.size()) + " ] " + UmakeA(data));
		ArgInf.m_pText = pDebugText;
		elibstl::CallElibFunc("krnln.fne", "输出调试文本", &RetData, 1, &ArgInf);
	}


}
FucInfo e_debugput_w = { {
		/*ccname*/  ("调试W"),
		/*egname*/  ("_wdebugput"),
		/*explain*/ ("仅用作调试输出宽字符,并不会对宽字符合法性进行检查"),
		/*category*/11,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG | CT_DISABLED_IN_RELEASE,
		/*ret*/     _SDT_NULL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/ Args2,
	} ,Fn_debugput_w ,"Fn_debugput_w" };

