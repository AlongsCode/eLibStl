#include"ElibHelp.h"
#pragma warning(disable:4996)
using namespace std;
static wstring normalization_path(const wstring& szPath)
{
	if (szPath.empty())
	{
		return {};
	}
	wchar_t* str = new wchar_t[szPath.size() + 1];
	memset(str, 0, sizeof(wchar_t) * (szPath.size() + 1));
	wcscpy(str, szPath.c_str());
	for (wchar_t* p = str; *p != 0; ++p)
	{
		if (*p >= L'A' && *p <= L'Z') {
			*p += (L'a' - L'A');
		}
		if (*p == L'\\') {
			*p = L'/';
		}
	}
	wstring	ret(str);
	delete[]str;
	return ret;
}

static ARG_INFO Args[] =
{

	{
		/*name*/    "·����",
		/*explain*/ ("���淶����·��"),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_BIN,
		/*default*/ 0,
		/*state*/   NULL,
	}
};

EXTERN_C void Fn_normalization_path_W(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	auto path = elibstl::args_to_wsdata(pArgInf, 0);
	pRetData->m_pBin = elibstl::clone_textw(normalization_path(wstring(path)));
}

FucInfo normalization_path_W = { {
		/*ccname*/  ("�淶��·��W"),
		/*egname*/  ("NormalizationPathW"),
		/*explain*/ ("��·���е�Ӣ��ȫ������ΪСд,��\\ȫ������Ϊ/,����·���Աȷǳ���Ҫ"),
		/*category*/8,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BIN,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  Args,
	} ,Fn_normalization_path_W ,"Fn_normalization_path_W" };
