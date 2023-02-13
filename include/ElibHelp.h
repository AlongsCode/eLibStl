#pragma once
#include"elib/lib2.h"
#include"elib/fnshare.h"
#include<vector>
#include<string>
#include"..\resource.h"

#include"Tace.hpp"
struct FucInfo
{
	CMD_INFO FucDef;
	PFN_EXECUTE_CMD pFuc;
	const char* FucName;
};
//字符串拼接重载运算符，也可使使用字符串拼接函数
extern HMODULE g_elibstl_hModule;
//extern vector<PFN_EXECUTE_CMD> s_ExecuteCommand;
//extern vector<const char*> s_CommandNames;
//extern vector<CMD_INFO> s_Commands;
//extern vector<LIB_DATA_TYPE_INFO> g_DataType;

//void AddFuc(FucInfo Func);
//void AddDataType(LIB_DATA_TYPE_INFO Func);
//LIB_INFO* elibkrnlnmake();
std::vector<unsigned char> ebin2v(LPBYTE bin);
