#include"ElibHelp.h"

ESTL_NAMESPACE_BEGIN

#if !defined(__E_STATIC_LIB) || defined(__ISFNE__)

static LIB_CONST_INFO LibStl_ConstInfo[] =
{
    //#define    CT_NULL 0
    //#define    CT_NUM  1      // value sample: 3.1415926
    //#define    CT_BOOL 2      // value sample: 1
    //#define    CT_TEXT 3      // value sample: "abc"
    //LPCSTR m_szName;          // ������
    //LPCSTR m_szEgName;        // Ӣ����
    //LPCSTR m_szExplain;       // ˵��
    //SHORT  m_shtLayout;       // ����Ϊ 1
    //SHORT  m_shtType;         // ��������, CT_NULL=�ճ���, CT_NUM=��ֵ��,double����ֵ, CT_BOOL=�߼���, CT_TEXT=�ı���
    //LPCSTR m_szText;          // CT_TEXT
    //DOUBLE m_dbValue;         // CT_NUM��CT_BOOL



    // ����û�������ط�ʹ�õ�, ����Ͳ���Ҫ��˳����

    { "������", "Ӣ����", "��������Ǵ�����, û���κ�ʵ������, �����Ҫ���ӳ����������￪ʼ��", 1, CT_NUM, NULL, 123},


};

PLIB_CONST_INFO LibStl_GetConstInfo()
{
    return 0;
    //return LibStl_ConstInfo;
}
int LibStl_GetConstSize()
{
    return 0;
    //return sizeof(LibStl_ConstInfo) / sizeof(LibStl_ConstInfo[0]);
}
#else
// ��̬�ⲻ��Ҫ��Щ����
PLIB_CONST_INFO LibStl_GetConstInfo()
{
    return 0;
}
int LibStl_GetConstSize()
{
    return 0;
}
#endif


ESTL_NAMESPACE_END
