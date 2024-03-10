#include"ElibHelp.h"

ESTL_NAMESPACE_BEGIN

#if !defined(__E_STATIC_LIB) || defined(__ISFNE__)

static LIB_CONST_INFO LibStl_ConstInfo[] =
{
    //#define    CT_NULL 0
    //#define    CT_NUM  1      // value sample: 3.1415926
    //#define    CT_BOOL 2      // value sample: 1
    //#define    CT_TEXT 3      // value sample: "abc"
    //LPCSTR m_szName;          // 常量名
    //LPCSTR m_szEgName;        // 英文名
    //LPCSTR m_szExplain;       // 说明
    //SHORT  m_shtLayout;       // 必须为 1
    //SHORT  m_shtType;         // 常量类型, CT_NULL=空常量, CT_NUM=数值型,double保存值, CT_BOOL=逻辑型, CT_TEXT=文本型
    //LPCSTR m_szText;          // CT_TEXT
    //DOUBLE m_dbValue;         // CT_NUM、CT_BOOL



    // 常量没有其他地方使用到, 这里就不需要列顺序了

    { "常量名", "英文名", "这个常量是打样用, 没有任何实际意义, 如果需要增加常量就在这里开始加", 1, CT_NUM, NULL, 123},


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
// 静态库不需要这些数据
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
