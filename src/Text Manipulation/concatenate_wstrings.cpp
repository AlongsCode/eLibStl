#include"ElibHelp.h"
static ARG_INFO WArgs[] =
{
	{
		/*name*/    "欲拼接的文本",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

/*字符串的拼接一定需要极致的效率,纯C写虽然仍然返回的是拷贝对象，不如直接引用对象指针操作，但是对于面向过程来说易即使传递参考依然需要释放再申请*/
EXTERN_C void efn_concatenate_wstrings(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{

	size_t totalLength = 0;

	// 计算所有字符串的总长度
	for (int i = 0; i < nArgCount; i++)
	{
		totalLength += *reinterpret_cast<std::uint32_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t) - 1;
	}
	// 分配足够的内存空间
	wchar_t* result = new wchar_t[totalLength + 1]{ 0 };

	// 拷贝字符串
	size_t currentPosition = 0;
	for (int i = 0; i < nArgCount; ++i)
	{
		size_t length = *reinterpret_cast<std::uint32_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t)) / sizeof(wchar_t) - 1;
		std::memcpy(result + currentPosition, reinterpret_cast<wchar_t*>(pArgInf[i].m_pBin + sizeof(std::uint32_t) * 2), length * sizeof(wchar_t));
		currentPosition += length;
	}
	pRetData->m_pBin = elibstl::clone_textw(result);
}
FucInfo g_concatenate_wstrings = { {
		/*ccname*/  ("拼接文本W"),
		/*egname*/  ("concatenate_wstrings"),
		/*explain*/ ("请确保拼接的字符为带结束符的标准unicode文本,代码因为需要效率,所以不会取判断,如果不带结束符直接用易语言重载的“+”拼接字节集就可以"),
		/*category*/2,
		/*state*/    CT_ALLOW_APPEND_NEW_ARG,
		/*ret*/     SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &WArgs[0],
	} ,efn_concatenate_wstrings ,"efn_concatenate_wstrings" };