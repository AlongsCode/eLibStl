#pragma once
#include "HexView_Function.h"


typedef struct _HEXJMP
{
    HWND        hParent;    // 对话框父窗口
    LPCWSTR     szCaption;  // 对话框标题
    PHEX_NODE   listText;   // 默认搜索的文本链表
    int         nMode;      // 跳转模式, 0=从文件开始, 1=当前位置, 2现在位置往上, 3=从文件结束, 高位 = 是否是16进制, 同时接收搜索时选中的模式

    LPWSTR      pRet;       // 返回输入的跳转文本
    INT64       pos;        // 输入的位置
    BOOLEAN     isOffset;   // 是否输入了偏移

    BOOLEAN     isAsm;      // 是否是汇编窗口进来的跳转
}HEXJMP, * PHEXJMP;


// 返回输入的数据尺寸
int HexView_Jmp_Dialog(PHEXJMP arg);

// 释放搜索返回的数据
void HexView_Jmp_Free(LPVOID ptr);

