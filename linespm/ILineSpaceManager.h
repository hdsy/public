#ifndef ILINESPACEMANAGER_H_HEADER_INCLUDED_AF099711
#define ILINESPACEMANAGER_H_HEADER_INCLUDED_AF099711
#include "CPointer.h"

//##ModelId=50EFD6130088
class ILineSpaceManager
{
  public:
    // 分配一个对象空间，当空间不够时，分配会失败
    //##ModelId=50EFD6F002C7
    virtual CPointer Alloc() = 0;

    //##ModelId=50EFD6F002C8
    virtual int Free(const CPointer &inPointer) = 0;

    // 转换为C指针，可进行相应的指针运算，但是越界要调用者保证
    //##ModelId=50EFD6F002CA
    virtual void *AsVoid(const CPointer &inPointer) = 0;

    //##ModelId=50EFD6F002D7
    virtual int Init(
        // 对象尺寸
        size_t inObjSize, 
        // 最大对象个数
        size_t inMaxObjCount, 
        // 模块名_Line_objSize_inName
        const char *inName = "",bool isMmap=true) = 0;

    // 返回实际成功分配的空间个数，可能小于需要的空间数。如果为0，表示空间不够
    //##ModelId=50EFD6F002DC
    virtual int Alloc(
        // 需要的可存放对象个数的空间
        size_t inObjCount, 
        // 用来接收分配空间的指针
        CPointer* iopCPointer) = 0;

    // 返回实际成功释放的空间个数
    //##ModelId=50EFD6F002E6
    virtual int Free(
        // 需要的释放的空间个数
        size_t inObjCount, 
        // 不改变输入顺序，释放成功的空间IsNull为true
        CPointer* iopCPointer) = 0;

    virtual size_t GetObjSize() = 0;
    virtual size_t GetObjCount() = 0;
    virtual size_t GetUsedCount() = 0;
};



#endif /* ILINESPACEMANAGER_H_HEADER_INCLUDED_AF099711 */
