#ifndef CLINESPACEMGR_H_HEADER_INCLUDED_AF09D4A4
#define CLINESPACEMGR_H_HEADER_INCLUDED_AF09D4A4

#include "ILineSpaceManager.h"

#include <sstream>

#include "CLineSpaceHeader.h"



//

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>


#include "CLIFO.h"

//##ModelId=50EFD36001C0
class CLineSpaceMgr : public ILineSpaceManager
{
  private:
  	std::ostringstream m_sTraceMessage;

	
  	
  public:

	void DumpInfo(std::ostream &os);

	const std::string GetTraceLog() const {return m_sTraceMessage.str();};
    void  ClearTraceLog()  { m_sTraceMessage.str("");};
	
    
    //##ModelId=50EFDBF402A4 
    // inName 唯一标记一个内存块,< 250 字节,一般写一个表名
    // 当是shget类型时，只能为一个8位的数字字符串，用来标记一块内存，具体含义，配置文件指定
    virtual int Init(
    // 对象尺寸
        size_t inObjSize, 
        // 最大对象个数
        size_t inMaxObjCount, 
        // 模块名_Line_objSize_inName
        const char *inName="",
        bool bMmap = true
     	);

	virtual int InitShmat(
		// 对象尺寸
        size_t inObjSize, 
        // 最大对象个数
        size_t inMaxObjCount, 
        // 模块名_Line_objSize_inName
        const char *inName = "88888888"
		);
    virtual int InitMmap(
        // 对象尺寸
        size_t inObjSize, 
        // 最大对象个数
        size_t inMaxObjCount, 
        // 模块名_Line_objSize_inName
        const char *inName = "");

    // 分配一个对象空间，当空间不够时，分配会失败
    //##ModelId=50EFDBF7037A
    virtual CPointer Alloc();

    //##ModelId=50EFDBF9006B
    virtual int Free(const CPointer &inPointer);

    // 转换为C指针，可进行相应的指针运算，但是越界要调用者保证
    //##ModelId=50EFDBFA0318
    virtual void *AsVoid(const CPointer &inPointer);

    // 返回实际成功分配的空间个数，可能小于需要的空间数。如果为0，表示空间不够
    //##ModelId=50EFDBFD0074
    virtual int Alloc(
        // 需要的可存放对象个数的空间
        size_t inObjCount, 
        // 用来接收分配空间的指针
        CPointer* iopCPointer);

    // 返回实际成功释放的空间个数
    //##ModelId=50EFDBFE02E3
    virtual int Free(
        // 需要的释放的空间个数
        size_t inObjCount, 
        // 不改变输入顺序，释放成功的空间IsNull为true
        CPointer* iopCPointer);

    // 查看是否还有空闲空间
    //##ModelId=50EFDC0D0074
    bool IsFull();

    // 返回可分配的对象空间个数
    //##ModelId=50EFE4E700ED
    unsigned int GetFreeSize();

    // 返回总的对象空间个数
    //##ModelId=50F619AB00B7
    unsigned int GetTotalSize();

    // 返回存放的对象空间个数
    //##ModelId=50F619C203BA
    unsigned int GetSize();

    //##ModelId=50F61BE60282
    virtual size_t GetObjSize();

    virtual size_t GetObjCount(){return GetTotalSize();};
    virtual size_t GetUsedCount(){return GetSize();}

    //##ModelId=50EFD5C30096
    CLineSpaceHeader * m_pobjCLineSpaceHeader;
	CLineSpaceTail * m_pobjCLineSpaceTail;
	
	const CLineSpaceTail m_objCLineSpaceTail;
	CLineSpaceHeader m_objCLineSpaceHeader;

	CLineSpaceMgr(){m_bInitOK = false; m_szObjSize=0; m_uiID = 1;};
	~CLineSpaceMgr(){};

  private:
    //##ModelId=50EFDACD03E7
    unsigned int m_uiID;

    //##ModelId=50EFDADE01BB
    std::string m_sName;

    //##ModelId=50EFE47D03B3
    char  *m_pStartAddress;

    //##ModelId=50EFD83C006D
    CLIFO<unsigned int> m_objCLIFOFree;

	// 对象尺寸
	size_t m_szObjSize;	
	size_t m_szObjSizeOrg;	


	char * m_pFirstObjAddress;

	
	bool m_bInitOK;

	// shmget base info
	// 共享内存的基本信息静态
	int m_iShareMemoryID;				// 共享内存标记号
	struct shmid_ds m_objShmidDs;		// 共享内存的描述

};



#endif /* CLINESPACEMGR_H_HEADER_INCLUDED_AF09D4A4 */
