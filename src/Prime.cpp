#include"ElibHelp.h"
#include <random>
#undef max
static ARG_INFO Args[] =
{
	{
		/*name*/    "���жϵ�ֵ",
		/*explain*/ (""),
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*type*/    DATA_TYPE::SDT_INT,
		/*default*/ 0,
		/*state*/   0,
	}
};


EXTERN_C void Fn_Prime(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int x = pArgInf->m_int;
	if (x < 2) {
		// С�� 2 ��������������
		pRetData->m_bool = false;
		return;
	}
	if (x == 2 || x == 3) {
		// 2 �� 3 ������
		pRetData->m_bool = true;
		return;
	}
	if (x % 2 == 0 || x % 3 == 0) {
		// ����ܹ��� 2 �� 3 ��������������
		pRetData->m_bool = false;
		return;
	}
	// �� 5 ��ʼö�ٵ� sqrt(x)����� x �ܹ���ö�ٵ�������������������
	for (unsigned long long i = 5; i * i <= x; i += 6) {
		if (x % i == 0 || x % (i + 2) == 0) {
			pRetData->m_bool = false;
			return;
		}
	}
	// ���û�б���������������
	pRetData->m_bool = true;
}

FucInfo prime = { {
		/*ccname*/  ("�Ƿ�����"),
		/*egname*/  (""),
		/*explain*/ ("�ж��Ƿ�Ϊ����"),
		/*category*/1,
		/*state*/   NULL,
		/*ret*/     DATA_TYPE::SDT_BOOL,
		/*reserved*/NULL,
		/*level*/   LVL_HIGH,
		/*bmp inx*/ 0,
		/*bmp num*/ 0,
		/*ArgCount*/1,
		/*arg lp*/  &Args[0],
	} ,Fn_Prime ,"Fn_Prime" };
