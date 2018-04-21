#define _LARGEFILE64_SOURCE

#include "CLineSpaceMgr.h"

#include "ENUM_ERRCD.h"
#include "CCommandLineInfo.h"

#include <iomanip>


#include "CBaseEncode.h"


#define SPMTRACE m_sTraceMessage<<"\r\n"<<__FILE__<<" " <<__LINE__ << "  " << __FUNCTION__<<" " 


void CLineSpaceMgr::DumpInfo(std::ostream &os)
{
	if(!m_bInitOK) os<< "Not Init." << std::endl;

	// 打印头信息 m_pobjCLineSpaceHeader->m_ubNameLen 
	os << "CLineSpaceMgr abstract infomation : \r\n "
		"=========================================\r\n "
		"Capacity \tObjSize   \tObjCount  \tNameLen   \tName      \r\n" ;
	
	
	os << std::setw(10)<< m_pobjCLineSpaceHeader->m_uiSize << "\t" 
		<< std::setw(10)<< m_pobjCLineSpaceHeader->m_uiObjSize << "\t" 
		<< std::setw(10)<< m_pobjCLineSpaceHeader->m_uiUsed<< "\t" 
		<< std::setw(10)<< (unsigned short) m_pobjCLineSpaceHeader->m_ubNameLen << "\t";

	os	<< std::string(m_pobjCLineSpaceHeader->m_strName,(unsigned int)m_pobjCLineSpaceHeader->m_ubNameLen )
		<< "\n \n"<< std::endl;


	
	// 打印堆栈信息
	m_objCLIFOFree.DumpInfo(os);
}


//##ModelId=50EFDBF402A4
int CLineSpaceMgr::Init(size_t inObjSize, size_t inMaxObjCount, const char *inName,bool bMmap)
{
	if(bMmap)
		return InitMmap(inObjSize, inMaxObjCount,inName);
	else
		return InitShmat(inObjSize,inMaxObjCount,inName);
}

int CLineSpaceMgr::InitShmat(size_t inObjSize, size_t inMaxObjCount, const char *inName)
{
	if(m_bInitOK) return SPACE_MANAGER_ALREADY_INIT;

	// ObjSize按照8字节 对齐
	m_szObjSizeOrg = inObjSize;
	m_szObjSize = 8*(inObjSize/8+((inObjSize%8)?1:0));
	
	
	// spm 文件的尺寸
	size_t szTotalSizeInByte = 
		sizeof(CLineSpaceHeader) - 1  + strlen(inName)%250 + // head
		CLIFO<unsigned int>::GetSpaceNeeded(inMaxObjCount) + // lifo
		m_szObjSize * inMaxObjCount + // content
		sizeof(m_objCLineSpaceTail) // tail
		; 
	
	// 这里inname传入的是key，如0x12345678,则传入12345678
	key_t shmKey ;
	int t_iLen = strlen(inName);
	if (t_iLen > 8) t_iLen = 8;
	MyUtility::CBaseEncode::Bcd2ToAscii(inName,t_iLen,1,(char *)&shmKey);


	// 打开共享内存
	int iShmID = -1;

	iShmID = shmget(shmKey, 0, 0644 );

	if(iShmID == -1)
	{
		//errno =  ENOENT  表示确实不存在
	    SPMTRACE << "cannot get shareMemory errno "
			<< shmKey 
			<< errno << strerror(errno)
	    	<<" ENOENT="<<ENOENT
	    	<<" EACCES="<<EACCES
	    	<<" EEXIST="<<EEXIST
	    	<<" ENFILE="<<ENFILE
	    	<<" ENOMEM="<<ENOMEM
	    	<<" ENOSPC="<<ENOSPC
	    	<<" EPERM ="<< EPERM;

		// 尝试新创建
		iShmID = shmget(shmKey, szTotalSizeInByte, 0644| IPC_CREAT| IPC_EXCL);
	    
		if(iShmID == -1)
		{
		    SPMTRACE << "Failed to create share memory in exclusive wayerrno "
				<< shmKey 
				<< errno << strerror(errno)
		    	<<" ENOENT="<<ENOENT
		    	<<" EACCES="<<EACCES
		    	<<" EEXIST="<<EEXIST
		    	<<" ENFILE="<<ENFILE
		    	<<" ENOMEM="<<ENOMEM
		    	<<" ENOSPC="<<ENOSPC
		    	<<" EPERM ="<< EPERM;
	        
			return SPACE_MANAGER_INIT_FAIL;
		}
		// 初始化空间		
		struct shmid_ds m_objShmidDs;
		if(-1 == shmctl(iShmID, IPC_STAT, &m_objShmidDs))
		{
			SPMTRACE << " Failed to get share memory's info(created in exclusive way) "
				<< shmKey 
				<< errno << strerror(errno)
		    	<<" ENOENT="<<ENOENT
		    	<<" EACCES="<<EACCES
		    	<<" EEXIST="<<EEXIST
		    	<<" ENFILE="<<ENFILE
		    	<<" ENOMEM="<<ENOMEM
		    	<<" ENOSPC="<<ENOSPC
		    	<<" EPERM ="<< EPERM;
			
			return SPACE_MANAGER_INIT_FAIL;
		}
		char * m_pStartAddress;
		m_pStartAddress = (char *)shmat(iShmID, 0, 0);
	
		if((void *) -1 == m_pStartAddress)
		{
			SPMTRACE << " Failed to attach the share memory(created in exclusive way)"
				<< shmKey 
				<< errno << strerror(errno)
		    	<<" ENOENT="<<ENOENT
		    	<<" EACCES="<<EACCES
		    	<<" EEXIST="<<EEXIST
		    	<<" ENFILE="<<ENFILE
		    	<<" ENOMEM="<<ENOMEM
		    	<<" ENOSPC="<<ENOSPC
		    	<<" EPERM ="<< EPERM;
			
			m_pStartAddress = NULL;
			return SPACE_MANAGER_INIT_FAIL;
		}

		SPMTRACE << "Create shm " << inName << "ok. to init and allocate size ..." ;

		// 写初始化头部数据
			m_objCLineSpaceHeader.m_uiSize = inMaxObjCount;
			m_objCLineSpaceHeader.m_uiUsed = 0;
			m_objCLineSpaceHeader.m_uiObjSize = m_szObjSize/8;
			m_objCLineSpaceHeader.m_ubNameLen = strlen(inName) % 250;

			memcpy(m_pStartAddress,(char *) & m_objCLineSpaceHeader,sizeof(m_objCLineSpaceHeader)-1);
			memcpy(m_pStartAddress + sizeof(m_objCLineSpaceHeader)-1,inName,strlen(inName) % 250);

		//写堆栈信息，并流出足够空间
			CLIFOHeader objCLIFOHeader;
			objCLIFOHeader.m_uiCapacity = inMaxObjCount;
			objCLIFOHeader.m_uiSize = 0;
			
			memcpy(m_pStartAddress + sizeof(m_objCLineSpaceHeader)-1 + strlen(inName) % 250,
				(char *) & objCLIFOHeader,sizeof(objCLIFOHeader));
			
		// 偏移留出内容空间，写如尾部数据
			off64_t off0 = szTotalSizeInByte - sizeof(m_objCLineSpaceTail);
	
			memcpy(m_pStartAddress + off0,(char *) & m_objCLineSpaceTail,sizeof(m_objCLineSpaceTail));
		
	}

	// 检查是否正确的内存
	if(-1 == shmctl(iShmID, IPC_STAT, &m_objShmidDs))
	{
		SPMTRACE << " Failed to get share memory's info(created in exclusive way) "
			<< shmKey 
			<< errno << strerror(errno)
	    	<<" ENOENT="<<ENOENT
	    	<<" EACCES="<<EACCES
	    	<<" EEXIST="<<EEXIST
	    	<<" ENFILE="<<ENFILE
	    	<<" ENOMEM="<<ENOMEM
	    	<<" ENOSPC="<<ENOSPC
	    	<<" EPERM ="<< EPERM;

		
		return SPACE_MANAGER_INIT_FAIL;
	}
	if(m_objShmidDs.shm_segsz != szTotalSizeInByte)
	{
		SPMTRACE << "shm " << inName << " not match. Please check manule " << errno << ":" << strerror(errno);
		
		return SPACE_MANAGER_INIT_FAIL;
	}
	
	m_pStartAddress = (char *)shmat(iShmID, 0, 0);

	if((void *) -1 == m_pStartAddress)
	{
		SPMTRACE << " Failed to attach the share memory(created in exclusive way)"
			<< shmKey 
			<< errno << strerror(errno)
	    	<<" ENOENT="<<ENOENT
	    	<<" EACCES="<<EACCES
	    	<<" EEXIST="<<EEXIST
	    	<<" ENFILE="<<ENFILE
	    	<<" ENOMEM="<<ENOMEM
	    	<<" ENOSPC="<<ENOSPC
	    	<<" EPERM ="<< EPERM;
		
		m_pStartAddress = NULL;
		return SPACE_MANAGER_INIT_FAIL;
	}

	// 检查头
	m_pobjCLineSpaceHeader = (CLineSpaceHeader *)m_pStartAddress ;

	if((m_pobjCLineSpaceHeader->m_uiObjSize != m_szObjSize/8) ||
		(m_pobjCLineSpaceHeader->m_uiSize != inMaxObjCount) ||
		(strncmp(inName,m_pobjCLineSpaceHeader->m_strName,strlen(inName) % 250) != 0)
		)
	{
		SPMTRACE << "shm " << inName << " not match . [" 
			<< "obj size " << m_szObjSize/8 << " vs " << m_pobjCLineSpaceHeader->m_uiObjSize
			<< " | max count " << inMaxObjCount << " vs " << m_pobjCLineSpaceHeader->m_uiSize
			<< " | name " << inName << " vs " << m_pobjCLineSpaceHeader->m_strName
			<< "]"
			;
			
		return SPACE_MANAGER_INIT_FAIL;
	}

	// 初始化堆栈
	char * pStartLIFO = m_pStartAddress + sizeof(CLineSpaceHeader) - 1 + m_pobjCLineSpaceHeader->m_ubNameLen;

	m_objCLIFOFree.Init(pStartLIFO);

	const CLIFOHeader *  m_pobjCLIFOHeader = m_objCLIFOFree.GetHeader();

	if(m_pobjCLIFOHeader->m_uiCapacity != inMaxObjCount )
	{
		SPMTRACE << "shm " << inName << " not match . [" 
			<< "lifo size " << m_pobjCLIFOHeader->m_uiCapacity << " vs " <<inMaxObjCount
			<< "]"
			;
			
		return SPACE_MANAGER_INIT_FAIL;
	}

	m_pFirstObjAddress = m_pStartAddress + sizeof(CLineSpaceHeader) - 1  + m_pobjCLineSpaceHeader->m_ubNameLen + // head
		CLIFO<unsigned int>::GetSpaceNeeded(m_pobjCLineSpaceHeader->m_uiSize);

	m_bInitOK = true;

	return OK;
	
}


int CLineSpaceMgr::InitMmap(size_t inObjSize, size_t inMaxObjCount, const char *inName)
{
	if(m_bInitOK) return SPACE_MANAGER_ALREADY_INIT;

	// ObjSize按照8字节 对齐
	m_szObjSizeOrg = inObjSize;
	m_szObjSize = 8*(inObjSize/8+((inObjSize%8)?1:0));
	
	
	// spm 文件的尺寸
	size_t szTotalSizeInByte = 
		sizeof(CLineSpaceHeader) - 1  + strlen(inName)%250 + // head
		CLIFO<unsigned int>::GetSpaceNeeded(inMaxObjCount) + // lifo
		m_szObjSize * inMaxObjCount + // content
		sizeof(m_objCLineSpaceTail) // tail
		; 
	
	// 确定 spm 文件路径
	std::string sSpmFilePath = "";

	sSpmFilePath +=
			inName + "_" +
			MyUtility::CBaseEncode::UIntToString(inMaxObjCount) + "_" +
			MyUtility::CBaseEncode::UIntToString(inObjSize) + "_" +
			".spm";


	// 打开文件
	int iFileID = -1;
	
	iFileID = open(sSpmFilePath.c_str(),O_RDWR);

	// 如果打开文件失败，且原因是文件不存在 
	if(iFileID < 0 ) 
	{
		SPMTRACE << "Open file " << sSpmFilePath << " error. " << errno << ":" << strerror(errno);

		// 创建文件
		iFileID = open(sSpmFilePath.c_str(),O_RDWR|O_CREAT|O_EXCL,S_IRWXU);
		
		if(iFileID > 0)
		{
			SPMTRACE << "Create file " << sSpmFilePath << "ok. to init and allocate size ..." ;

			// 写初始化头部数据
			m_objCLineSpaceHeader.m_uiSize = inMaxObjCount;
			m_objCLineSpaceHeader.m_uiUsed = 0;
			m_objCLineSpaceHeader.m_uiObjSize = m_szObjSize/8;
			m_objCLineSpaceHeader.m_ubNameLen = strlen(inName) % 250;

			write(iFileID,(char *) & m_objCLineSpaceHeader,sizeof(m_objCLineSpaceHeader)-1);
			write(iFileID,inName,strlen(inName) % 250);

			//写堆栈信息，并流出足够空间
			CLIFOHeader objCLIFOHeader;
			objCLIFOHeader.m_uiCapacity = inMaxObjCount;
			objCLIFOHeader.m_uiSize = 0;
			write(iFileID,(char *) & objCLIFOHeader,sizeof(objCLIFOHeader));
			
			// 偏移留出内容空间，写如尾部数据
			off64_t off0 = szTotalSizeInByte - sizeof(m_objCLineSpaceTail);
			off64_t off1 = lseek64(iFileID, off0, SEEK_SET);
	
			if(off1 == -1)
			{
				SPMTRACE << "error in lseek64 (" <<iFileID << "," << szTotalSizeInByte << "SEEK_SET) . " << errno << ":" << strerror(errno);

				close(iFileID);
				
				return SPACE_MANAGER_INIT_FAIL;
			}
			write(iFileID,(char *) & m_objCLineSpaceTail,sizeof(m_objCLineSpaceTail));
		}
		else
		{
			SPMTRACE << "Create file " << sSpmFilePath << " error. " << errno << ":" << strerror(errno);
			return SPACE_MANAGER_INIT_FAIL;
		}
	}

	// 检查是否合法的spm文件
	struct stat statFile;
	
	if(fstat(iFileID,&statFile))
	{
		SPMTRACE << "fstat file " << sSpmFilePath << " error. " << errno << ":" << strerror(errno);
		
		return SPACE_MANAGER_INIT_FAIL;
	}

	if(statFile.st_size != szTotalSizeInByte)
	{
		SPMTRACE << "file " << sSpmFilePath << " not match. Please check manule " << errno << ":" << strerror(errno);
		
		return SPACE_MANAGER_INIT_FAIL;
	}
	
	// 
	// MAP_LOCKED 只能被root用户使用
	m_pStartAddress = (char *)mmap(NULL,statFile.st_size,PROT_WRITE|PROT_READ,MAP_SHARED/*|MAP_LOCKED*/,iFileID,0);
	
	close(iFileID);
	
	if(m_pStartAddress == (caddr_t) -1)
	{
		SPMTRACE << "mmap file " << sSpmFilePath << " error. " << errno << ":" << strerror(errno);
		
		return SPACE_MANAGER_INIT_FAIL;
	}

	// 检查头
	m_pobjCLineSpaceHeader = (CLineSpaceHeader *)m_pStartAddress ;

	if((m_pobjCLineSpaceHeader->m_uiObjSize != m_szObjSize/8) ||
		(m_pobjCLineSpaceHeader->m_uiSize != inMaxObjCount) ||
		(strncmp(inName,m_pobjCLineSpaceHeader->m_strName,strlen(inName) % 250) != 0)
		)
	{
		SPMTRACE << "file " << sSpmFilePath << " not match . [" 
			<< "obj size " << m_szObjSize/8 << " vs " << m_pobjCLineSpaceHeader->m_uiObjSize
			<< " | max count " << inMaxObjCount << " vs " << m_pobjCLineSpaceHeader->m_uiSize
			<< " | name " << inName << " vs " << m_pobjCLineSpaceHeader->m_strName
			<< "]"
			;
			
		return SPACE_MANAGER_INIT_FAIL;
	}

	// 初始化堆栈
	char * pStartLIFO = m_pStartAddress + sizeof(CLineSpaceHeader) - 1 + m_pobjCLineSpaceHeader->m_ubNameLen;

	m_objCLIFOFree.Init(pStartLIFO);

	const CLIFOHeader *  m_pobjCLIFOHeader = m_objCLIFOFree.GetHeader();

	if(m_pobjCLIFOHeader->m_uiCapacity != inMaxObjCount )
	{
		SPMTRACE << "file " << sSpmFilePath << " not match . [" 
			<< "lifo size " << m_pobjCLIFOHeader->m_uiCapacity << " vs " <<inMaxObjCount
			<< "]"
			;
			
		return SPACE_MANAGER_INIT_FAIL;
	}

	m_pFirstObjAddress = m_pStartAddress + sizeof(CLineSpaceHeader) - 1  + m_pobjCLineSpaceHeader->m_ubNameLen + // head
		CLIFO<unsigned int>::GetSpaceNeeded(m_pobjCLineSpaceHeader->m_uiSize);

	m_bInitOK = true;

	return OK;
	
}

//##ModelId=50EFDBF7037A
CPointer CLineSpaceMgr::Alloc()
{
	//printf("Debug: jeffzjiang, alloc.\n");
	if(!m_bInitOK) return CPointer(0,0);

	unsigned int uiOffsetID = 0;

	// 看堆栈有无空闲块
	if(0 == m_objCLIFOFree.Pop(uiOffsetID) )
	{
		return CPointer(m_uiID,uiOffsetID);
	}
	// 看线性空间是否足够
	else if(m_pobjCLineSpaceHeader->m_uiUsed < m_pobjCLineSpaceHeader->m_uiSize)
	{
		return CPointer(m_uiID,(m_pobjCLineSpaceHeader->m_uiUsed)++);
	}
	// 报告无空间
	else
		return CPointer(0,0);
	
}

//##ModelId=50EFDBF9006B
int CLineSpaceMgr::Free(const CPointer &inPointer)
{
	//printf("Debug: jeffzjiang, free.\n");
	if(!m_bInitOK) return SPACE_MANAGER_NOT_INIT;

	if(inPointer.m_uiBlock != m_uiID)
		return SPACE_MANAGER_FREE_BLOCK_NOT_MATCH;

	if(inPointer.m_uiOffset > m_pobjCLineSpaceHeader->m_uiUsed)
		return SPACE_MANAGER_FREE_POINTER_NOT_ALLOC;
	
	// 这里要判断会否是重复释放 20180409 ..........
	if(0 == m_objCLIFOFree.Push(inPointer.m_uiOffset))
	{
		return OK;
	}
	else
	{
		// 走到这里就是程序BUG，要仔细看看INIT函数是否正确.
		return SPACE_MANAGER_FILO_MAX_ITEM;
	}
		
}

//##ModelId=50EFDBFA0318
void *CLineSpaceMgr::AsVoid(const CPointer &inPointer)
{
	char * pResult = NULL;

	if((inPointer.IsNull()) ||
		(inPointer.m_uiOffset > m_pobjCLineSpaceHeader->m_uiSize)
		) 
		return pResult;

	size_t szOffset = inPointer.m_uiOffset;

	pResult = ((char *)m_pFirstObjAddress + 8 * szOffset * m_pobjCLineSpaceHeader->m_uiObjSize);
	
	return pResult;
	
}

//##ModelId=50EFDBFD0074
unsigned int CLineSpaceMgr::GetSize()
{
	if(!m_bInitOK) return 0;

	return m_pobjCLineSpaceHeader->m_uiUsed - m_objCLIFOFree.GetCount() ;
}


int CLineSpaceMgr::Alloc(size_t inObjCount, CPointer* iopCPointer)
{
	int iResult = 0;
	
	for(int i = 0; i < inObjCount ; i++)
	{
		iopCPointer[i] = Alloc();

		if(!iopCPointer[i].IsNull())
			iResult++;
		else
			break;
	}

	return iResult;
	
		
}

//##ModelId=50EFDBFE02E3
int CLineSpaceMgr::Free(size_t inObjCount, CPointer* iopCPointer)
{
	int iResult = 0;
	
	for(int i = 0; i < inObjCount ; i++)
	{
		if(0 == Free(iopCPointer[i]))
		{
			iopCPointer[i].m_uiBlock = 0;
		
			iResult++;
		}
	}

	return iResult;
}

//##ModelId=50EFDC0D0074
bool CLineSpaceMgr::IsFull()
{
	if(!m_bInitOK) return true;
	return ((m_pobjCLineSpaceHeader->m_uiUsed >= m_pobjCLineSpaceHeader->m_uiSize) && (m_objCLIFOFree.GetCount() == 0));
}

//##ModelId=50EFE4E700ED
unsigned int CLineSpaceMgr::GetFreeSize()
{
	if(!m_bInitOK) return 0;
	
	return  (m_pobjCLineSpaceHeader->m_uiSize - m_pobjCLineSpaceHeader->m_uiUsed + m_objCLIFOFree.GetCount());
}

//##ModelId=50F619AB00B7
unsigned int CLineSpaceMgr::GetTotalSize()
{
	if(!m_bInitOK) return 0;

	return m_pobjCLineSpaceHeader->m_uiSize ;
}

//##ModelId=50F619C203BA
//##ModelId=50F61BE60282
size_t CLineSpaceMgr::GetObjSize() 
{
    //return m_szObjSize;
    return m_szObjSizeOrg;
}


