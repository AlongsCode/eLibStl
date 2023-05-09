rem 易语言主程序路径
wmic ENVIRONMENT where "name='ESTL_DBG_EMAIN_PATH___'" delete
rem 其他EXE路径
wmic ENVIRONMENT where "name='ESTL_DBG_EXE_PATH___'" delete
rem 易语言lib路径
wmic ENVIRONMENT where "name='ESTL_DBG_ELIB_PATH___'" delete