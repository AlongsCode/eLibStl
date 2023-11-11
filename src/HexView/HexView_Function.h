#ifndef _HEXVIEW_FUNCTION_H_
#define _HEXVIEW_FUNCTION_H_
#include <windows.h>

typedef struct _HEX_NODE
{
    LPWSTR text;
    struct _HEX_NODE* next;
}HEX_NODE, * PHEX_NODE;


// 跳转链表顺序, 查找链表里有没有重复项, 有的话把重复项调整到第一个位置, 返回是否调整了顺序
// 如果返回没有调整顺序, 需要把数据添加到链表头
// ppNode = 指向头节点指针, 调整顺序后会把最新的节点写入到这个地址里
// pStr = 查找的文本, 遍历链表查找这个文本, 如果有就把这个节点调整到第一个位置
BOOLEAN HexView_AdjustListOrder(PHEX_NODE* ppNode, LPWSTR pStr);

LPVOID HexViewAlloc(size_t size, bool isClear = false);
void HexViewFree(LPVOID p);

// 分配一个节点, 然后把值写入到节点中
PHEX_NODE HexView_NewNode(LPWSTR pStr, PHEX_NODE pNextNode);

void HexView_FreeList(PHEX_NODE pNode);
BOOLEAN HexView_SetClipboard(LPCWSTR str, int size);


#endif // _HEXVIEW_FUNCTION_H_