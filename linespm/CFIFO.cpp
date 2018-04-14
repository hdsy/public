/* by Joedge */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <set>
/*****/
#include "CFIFO.h"
#include "ShareMemory_Errorcd.h"

//##ModelId=5020CFD80069
int CFIFO::Init(char *io_pLineSpace, size_t in_szFIFO, bool in_ExistFlag)
{
	m_uiTotalSize = in_szFIFO;

	m_pStartAddress  = io_pLineSpace;

	m_pobjCFIFOHEader = (CFIFOHEader * )m_pStartAddress;

	if(in_ExistFlag == 0)
	{
		m_pobjCFIFOHEader->m_szOffsetOfRead  = 0;
		m_pobjCFIFOHEader->m_szOffsetOfWrite = 0;
		m_pobjCFIFOHEader->m_uiRecordNumber  = 0;
		m_pobjCFIFOHEader->m_szOffsetOfData  = sizeof(m_pobjCFIFOHEader);
	}

	//io_pLineSpace += m_uiTotalSize;

	return 0;

	

	
}

void CFIFO::SequenceWrite(const char * src,unsigned int sz)
{	
	if(sz == 0)  return;
	
	memcpy(m_pStartAddress + m_pobjCFIFOHEader->m_szOffsetOfData+m_pobjCFIFOHEader->m_szOffsetOfWrite,src,sz);
	
	m_pobjCFIFOHEader->m_szOffsetOfWrite+=sz;

	if(m_pobjCFIFOHEader->m_szOffsetOfWrite == m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData)
		m_pobjCFIFOHEader->m_szOffsetOfWrite =0;
};
void CFIFO::SequenceRead(char * dst,unsigned int sz)
{	
	if(sz == 0)  return;
	
	memcpy(dst,m_pStartAddress + m_pobjCFIFOHEader->m_szOffsetOfData+m_pobjCFIFOHEader->m_szOffsetOfRead,sz);
	
	m_pobjCFIFOHEader->m_szOffsetOfRead+=sz;

	if(m_pobjCFIFOHEader->m_szOffsetOfRead == m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData)
		m_pobjCFIFOHEader->m_szOffsetOfRead =0;
};
void CFIFO::SequenceRead(std::string &dst,unsigned int sz)
{	
	if(sz == 0)  return;

	dst.append(m_pStartAddress + m_pobjCFIFOHEader->m_szOffsetOfData+m_pobjCFIFOHEader->m_szOffsetOfRead,sz);
	
	//memcpy(dst,m_pStartAddress + m_pobjCFIFOHEader->m_szOffsetOfData+m_pobjCFIFOHEader->m_szOffsetOfRead,sz);
	
	m_pobjCFIFOHEader->m_szOffsetOfRead+=sz;

	if(m_pobjCFIFOHEader->m_szOffsetOfRead == m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData)
		m_pobjCFIFOHEader->m_szOffsetOfRead =0;
};

//##ModelId=5020D17E016A
int CFIFO::PushBack(const char *in_pszBuf, unsigned int in_uiSize)
{
	if((m_pobjCFIFOHEader == NULL) ||(m_uiTotalSize==0)||(m_pStartAddress == NULL))
	{
		return SHM_FIFO_NOT_INIT;
	}
	
	unsigned int uiSize =  sizeof(unsigned int) + in_uiSize;
	
	// 0. m_pobjCFIFOHEader->m_szOffsetOfRead == m_pobjCFIFOHEader->m_szOffsetOfWrite
	if( m_pobjCFIFOHEader->m_szOffsetOfRead == m_pobjCFIFOHEader->m_szOffsetOfWrite)
	{
		if(m_pobjCFIFOHEader->m_uiRecordNumber > 0)
		{
			return SHM_FIFO_NOT_ENOUGH_SPACE;
		}

		m_pobjCFIFOHEader->m_szOffsetOfRead = m_pobjCFIFOHEader->m_szOffsetOfWrite = 0;

		if(m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData < uiSize)
		{
			return SHM_FIFO_NOT_ENOUGH_SPACE;
		}
		// 写整数
		SequenceWrite((char *)&in_uiSize,sizeof(in_uiSize));
		// 写内容
		SequenceWrite(in_pszBuf,in_uiSize);

		m_pobjCFIFOHEader->m_uiRecordNumber++;
		
	}

	// 1. m_pobjCFIFOHEader->m_szOffsetOfRead < m_pobjCFIFOHEader->m_szOffsetOfWrite
	else if( m_pobjCFIFOHEader->m_szOffsetOfRead < m_pobjCFIFOHEader->m_szOffsetOfWrite)
	{	
	// 1.1. m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfWrite - m_pobjCFIFOHEader->m_szOffsetOfData > in_uiSize
		if(m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfWrite - m_pobjCFIFOHEader->m_szOffsetOfData >= uiSize)
		{
			// 写整数
			SequenceWrite((char *)&in_uiSize,sizeof(in_uiSize));
			// 写内容
			SequenceWrite(in_pszBuf,in_uiSize);

			m_pobjCFIFOHEader->m_uiRecordNumber++;
		}

	// 1.2.m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfWrite - m_pobjCFIFOHEader->m_szOffsetOfData 
	//		+ m_pobjCFIFOHEader->m_szOffsetOfRead
	//		> in_uiSize
		else if(m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfWrite - m_pobjCFIFOHEader->m_szOffsetOfData +m_pobjCFIFOHEader->m_szOffsetOfRead >= uiSize)
		{
			unsigned int uiFirstSize = m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfWrite - m_pobjCFIFOHEader->m_szOffsetOfData;

			unsigned int uiSecondSize = uiSize - uiFirstSize;
			
			// 写整数
			if(uiFirstSize >= sizeof(unsigned int))
			{
				SequenceWrite((char *)&in_uiSize,sizeof(in_uiSize));
			}
			else 
			{
				SequenceWrite((char *)&in_uiSize,uiFirstSize);
				SequenceWrite(((char *)&in_uiSize)+uiFirstSize,sizeof(in_uiSize)-uiFirstSize);
			}
			// 写内容
			if(uiFirstSize >= sizeof(unsigned int))
			{
				SequenceWrite(in_pszBuf,uiFirstSize-sizeof(unsigned int));
				SequenceWrite(in_pszBuf,uiSecondSize);
			}
			else
			{
				SequenceWrite(in_pszBuf,uiSecondSize-sizeof(in_uiSize)+uiFirstSize);
			}

			m_pobjCFIFOHEader->m_uiRecordNumber++;
		}
		else
		{
			return SHM_FIFO_NOT_ENOUGH_SPACE;
		}
	}


	// 2.m_pobjCFIFOHEader->m_szOffsetOfRead > m_pobjCFIFOHEader->m_szOffsetOfWrite
	else if(m_pobjCFIFOHEader->m_szOffsetOfRead > m_pobjCFIFOHEader->m_szOffsetOfWrite)
	{
	// 2.1 m_pobjCFIFOHEader->m_szOffsetOfRead-m_pobjCFIFOHEader->m_szOffsetOfWrite > in_uiSize
		if(m_pobjCFIFOHEader->m_szOffsetOfRead-m_pobjCFIFOHEader->m_szOffsetOfWrite >= uiSize)
		{
			// 写整数
			SequenceWrite((char *)&in_uiSize,sizeof(in_uiSize));
			// 写内容
			SequenceWrite(in_pszBuf,in_uiSize);

			m_pobjCFIFOHEader->m_uiRecordNumber++;
		}
		else
		{
			return SHM_FIFO_NOT_ENOUGH_SPACE;
		}
	}

	return 0;

}

//##ModelId=5020D1DC0333
int CFIFO::RemoveTop(std::string &io_sRes)
{
	if((m_pobjCFIFOHEader == NULL) ||(m_uiTotalSize==0)||(m_pStartAddress == NULL))
	{
		return SHM_FIFO_NOT_INIT;
	}

	unsigned int uiSize = 0;
	
	// 1.m_pobjCFIFOHEader->m_uiRecordNumber > 0
	if(m_pobjCFIFOHEader->m_uiRecordNumber <= 0) 
	{
		return SHM_FIFO_NO_ITEM;
	}
	
	// 1.1 m_pobjCFIFOHEader->m_szOffsetOfRead < m_pobjCFIFOHEader->m_szOffsetOfWrite
	if(m_pobjCFIFOHEader->m_szOffsetOfRead < m_pobjCFIFOHEader->m_szOffsetOfWrite)
	{
		// 检查
		if( sizeof(unsigned int)  > m_pobjCFIFOHEader->m_szOffsetOfWrite-m_pobjCFIFOHEader->m_szOffsetOfRead)
		{
			return SHM_FIFO_ERROR_DATA;
		}
		// 读取长度
		SequenceRead((char *) &uiSize,sizeof(unsigned int));

		// 检查
		if(uiSize + sizeof(unsigned int)  > m_pobjCFIFOHEader->m_szOffsetOfWrite-m_pobjCFIFOHEader->m_szOffsetOfRead)
		{
			return SHM_FIFO_ERROR_DATA;
		}

		// 读取内容
		SequenceRead(io_sRes,uiSize);

		m_pobjCFIFOHEader->m_uiRecordNumber--;		
	}
	else if(m_pobjCFIFOHEader->m_szOffsetOfRead >= m_pobjCFIFOHEader->m_szOffsetOfWrite)
	{
		if(m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData - m_pobjCFIFOHEader->m_szOffsetOfRead >= sizeof(unsigned int))
		{
			// 读取长度
			SequenceRead((char *) &uiSize,sizeof(unsigned int));
		}
		else
		{
			unsigned int szFirstSize = m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData - m_pobjCFIFOHEader->m_szOffsetOfRead;
			// 读取长度
			SequenceRead((char *) &uiSize,szFirstSize);
			SequenceRead(((char *) &uiSize) + szFirstSize,sizeof(unsigned int) - szFirstSize);
		}

		// 检查
		if(uiSize + sizeof(unsigned int)  >m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData)
		{
			return SHM_FIFO_ERROR_DATA;
		}

		if(m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData - m_pobjCFIFOHEader->m_szOffsetOfRead >= uiSize)
		{
			// 读取内容
			SequenceRead(io_sRes,uiSize);
		}
		else
		{
			unsigned int szFirstSize = m_uiTotalSize - m_pobjCFIFOHEader->m_szOffsetOfData - m_pobjCFIFOHEader->m_szOffsetOfRead;
			// 读取长度
			SequenceRead(io_sRes,szFirstSize);
			SequenceRead(io_sRes,uiSize - szFirstSize);
		}

		m_pobjCFIFOHEader->m_uiRecordNumber--;		
		
	}

	return 0;
}

//##ModelId=5020D9990273
CFIFO::CFIFO()
{
	m_uiTotalSize = 0;
	m_pStartAddress = NULL;
	m_pobjCFIFOHEader = NULL;
}


//##ModelId=5020D99902A2
CFIFO::~CFIFO()
{
}

