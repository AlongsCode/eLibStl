#pragma once
#include "zlib.h"
class Czlib
{
private:
    int err;
public:
    Czlib()
    {
        err = 0;
    }
    ~Czlib()
    {
        
    }
    // zlib压缩, 成功返回压缩后的数据,失败返回0, 返回的地址不会自动释放,需要调用 本对象的 free(); 来释放
    // data = 需要压缩的数据
    // size = 需要压缩数据的大小
    // compressSize = 返回压缩后的大小
    Bytef* compress(const void* data, uLongf size, uLongf* compressSize = 0)
    {
        uLongf bufSize = 0;
        compressEx(data, size, 0, 0, &bufSize);

        if (bufSize == 0) return 0;
        Bytef* ptr = (Bytef*)malloc(bufSize);
        if (!ptr)
        {
            err = 7;// QM_ERROR_LOCALALLOC;
            return 0;
        }

        return compressEx(data, size, ptr, bufSize, compressSize);
    }

    // zlib压缩, 成功返回压缩后的数据,失败返回0, 返回的地址不会自动释放,需要调用 本对象的 free(); 来释放
    // data = 需要压缩的数据
    // size = 需要压缩数据的大小
    // pBuffer = 压缩后的数据保存的缓冲区, 为0则返回缓冲区尺寸
    // nBufferSize = 缓冲区尺寸
    // compressSize = 返回压缩后的大小
    Bytef* compressEx(const void* data, uLongf size, LPVOID pBuffer, uLongf nBufferSize, uLongf* compressSize = 0)
    {
        const int offset = 10;
        if (compressSize) *compressSize = 0;
        if (!data)return 0;
        uLongf sourceLen = size;
        uLongf destLen = (uLongf)(((double)(sourceLen + 12)) * 1.1);    // 缓冲区长度, 要比原始数据长一点
        Bytef* ptr = (Bytef*)pBuffer;
        if (!ptr || destLen + offset > nBufferSize) // 传递的指针为0, 或者缓冲区小于需要的缓冲区尺寸, 返回缓冲区需要的尺寸
        {
            if (compressSize)*compressSize = destLen + offset;
            return 0;
        }
        
        memset(ptr, 0, destLen + offset);

        err = ::compress(ptr + offset, &destLen, (Bytef*)data, sourceLen);
        if (err != Z_OK) return 0;

        *((short*)ptr) = 31082;                 // 前两个字节是标志 小写的jy
        *((int*)(ptr + 2)) = sourceLen;         // 下来4个字节是原始长度
        *((int*)(ptr + 6)) = destLen;           // 在下来4个字节是压缩后的长度
        if (compressSize) *compressSize = destLen + offset;
        return ptr;
    }

    // zlib解压, 成功返回解压后的数据,失败返回0, 返回的地址不会自动释放,需要调用 本对象的 free(); 来释放
    // data = 需要解压的数据, 本类对象 compress 返回的值
    // uncompressSize = 返回解压后的大小
    Bytef* uncompress(const void* data, uLongf* uncompressSize = 0)
    {
        uLongf bufSize = 0;
        uncompressEx(data, 0, 0, &bufSize);

        if (bufSize == 0) return 0;
        Bytef* ptr = (Bytef*)malloc(bufSize);
        if (!ptr)
        {
            err = 7;// QM_ERROR_LOCALALLOC;
            return 0;
        }

        return uncompressEx(data, ptr, bufSize, uncompressSize);
    }

    // zlib解压, 成功返回解压后的数据,失败返回0, 返回的地址不会自动释放,需要调用 本对象的 free(); 来释放
    // data = 需要解压的数据, 本类对象 compress 返回的值
    // pBuffer = 解压后的数据保存的缓冲区, 为0则返回缓冲区尺寸
    // nBufferSize = 缓冲区尺寸
    // uncompressSize = 返回解压后的大小
    Bytef* uncompressEx(const void* data, LPVOID pBuffer, uLongf nBufferSize, uLongf* uncompressSize = 0)
    {
        const int offset = 10;
        if (uncompressSize)*uncompressSize = 0;
        if (!data)return 0;
        const short flag        = *((short*)data);                  // 前两个字节是标志 小写的jy
        uLongf destLen          = *((int*)((char*)data + 2));       // 下来4个字节是原始长度
        const uLongf dwLen      = *((int*)((char*)data + 6));       // 在下来4个字节是压缩后长度
        if (destLen <= 0 || flag != 31082 || dwLen <= 0) return 0;  // 只要有一个不符合就不解压

        //destLen
        Bytef* ptr = (Bytef*)pBuffer;
        if (!ptr || nBufferSize < destLen)     // 缓冲区不够大, 返回缓冲区需要的尺寸
        {
            if (uncompressSize)*uncompressSize = destLen;
            return 0;
        }

        memset(ptr, 0, destLen);
        err = ::uncompress(ptr, &destLen, (Bytef*)((char*)data + offset), dwLen);    // 前10个字节记录标志和长度,实际压缩数据从第10个字节开始
        if (err != Z_OK) return 0;
        if (uncompressSize)*uncompressSize = destLen;
        return ptr;
    }
    int GetError()const { return err; }

    // 释放由本类返回的地址, 释放成功 参数p 被置为0
    static void free(Bytef** p)
    {
        if (!p)return;
        ::free(*p);
        *p = 0;
        return;
    }
};

