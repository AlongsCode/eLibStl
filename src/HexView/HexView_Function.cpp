#include "HexView_Function.h"

// 跳转链表顺序, 查找链表里有没有重复项, 有的话把重复项调整到第一个位置, 返回是否调整了顺序
// 如果返回没有调整顺序, 需要把数据添加到链表头
// ppNode = 指向头节点指针, 调整顺序后会把最新的节点写入到这个地址里
// pStr = 查找的文本, 遍历链表查找这个文本, 如果有就把这个节点调整到第一个位置
BOOLEAN HexView_AdjustListOrder(PHEX_NODE* ppNode, LPWSTR pStr)
{
    PHEX_NODE node_base = *ppNode;

    // 先枚举一下链表, 看看有没有重复项, 有的话把重复项拿出来放到第一个位置
    PHEX_NODE node = node_base;
    PHEX_NODE find = 0;
    PHEX_NODE prev = 0;
    while ( node )
    {
        if ( wcscmp(node->text, pStr) == 0 )
        {
            find = node;
            if ( prev )
            {
                // 这个节点不是首节点, 那就让上一个节点指向这个节点的下一个节点
                // 然后把这个节点放到第一个位置
                prev->next = node->next;
                find->next = prev;
                *ppNode = find;

                HexViewFree(find->text);
                find->text = pStr;
                return TRUE;
            }

            // 第一个就是重复项的, 也返回真, 让调用方不用新创建节点
            return TRUE;
        }
        prev = node;
        node = node->next;
    }
    return FALSE;
}


LPVOID HexViewAlloc(size_t size, bool isClear)
{
    LPVOID p = ::malloc(size);
    if ( !p )
    {
        MessageBoxW(NULL, L"申请内存失败, 无法继续", L"申请内存失败", MB_ICONERROR);
        throw;
    }
    if ( isClear )
        memset(p, 0, size);
    return p;
}

void HexViewFree(LPVOID p)
{
    if ( p )
        ::free(p);
}

// 分配一个节点, 然后把值写入到节点中
PHEX_NODE HexView_NewNode(LPWSTR pStr, PHEX_NODE pNextNode)
{
    PHEX_NODE node = (PHEX_NODE)HexViewAlloc(sizeof(HEX_NODE));
    node->text = pStr;
    node->next = pNextNode;
    return node;
}

void HexView_FreeList(PHEX_NODE pNode)
{
    PHEX_NODE node = pNode;
    while ( node )
    {
        HexViewFree(node->text);
        PHEX_NODE pFree = node;
        node = node->next;
        free(pFree);
    }
}


BOOLEAN HexView_SetClipboard(LPCWSTR str, int size)
{
    if ( !str )
        return FALSE;
    if ( size <= 0 )
        size = (int)(LONG_PTR)wcslen(str);
    size_t len = size + 1;
    HGLOBAL hMem = GlobalAlloc(GHND, len * 2);
    if ( !hMem )
        return FALSE;
    void* p = GlobalLock(hMem);
    if ( p )
    {
        memcpy(p, str, len * 2);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_UNICODETEXT, hMem);
        //GlobalFree(hMem);
        CloseClipboard();
    }
    return TRUE;
}