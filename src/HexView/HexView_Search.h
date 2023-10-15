#pragma once
#include "HexView_Function.h"

enum HEXSEARCH_WINDOWTYPE
{
    HEXSEARCH_WINDOWTYPE_ASM = 1,   // 汇编窗口
    HEXSEARCH_WINDOWTYPE_HEX,       // 十六进制窗口
    HEXSEARCH_WINDOWTYPE_MEMORY,    // 输入内存地址和尺寸的窗口

};
typedef struct _HEXSEARCH
{
    HWND        hParent;    // 对话框父窗口
    LPCWSTR     szCaption;  // 对话框标题
    LPCWSTR     szTips;     // 提示文本
    PHEX_NODE   listText;   // 默认搜索的文本链表
    int         nMode;      // 搜索模式, 0=十六进制, 1=ansi字符串, 2=10进制, 3=Unicode字符串, 4=单精度浮点数, 5=双精度浮点数, 同时接收搜索时选中的模式
    int         windowType; // 窗口类型, 根据这个类型做不同的处理

    LPWSTR      pRet;       // 返回输入的搜索文本
    LPWSTR      pRet2;      // 返回输入的搜索文本2
}HEXSEARCH, * PHEXSEARCH;


// 返回输入的数据尺寸
int HexView_Search_Dialog(PHEXSEARCH arg);

// 释放搜索返回的数据
void HexView_Search_Free(LPVOID ptr);

