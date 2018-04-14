#ifndef CLIFO_H_HEADER_INCLUDED_AF09B739
#define CLIFO_H_HEADER_INCLUDED_AF09B739

#include "CLIFOHeader.h"

#include "ENUM_ERRCD.h"

#include <iomanip>



// 后进先出队列，用来在连续内存上实现定长数据类型的堆栈。
// 
// 例如：做空闲内存回收再分配。
//##ModelId=50ED3F0901A7
template <class T>
class CLIFO
{
  public:
    //##ModelId=50ED3F0901CE
    void DumpInfo(std::ostream &os)
    {
    	
    	os << "CLIFO abstract infomation : \r\n ================================= \r\n "
			"Capacity  \tCount     \t\r\n";
		
		
		
		os << m_pHeader->m_uiCapacity<< " \t " 
			<< m_pHeader->m_uiSize<< "  \t  "
			<< "\n "<< std::endl;

		

		// 打印前10个原属，如果有的话
		os << "CLIFO First 10 Item : \r\n         1  \t         2  \t         3  \t         4  \t         5 \t         6 \t         7 \t         8 \t         9 \t         10 \r\n" ;

	
		
		for(int i=0;(i < m_pHeader->m_uiSize ) && (i < 10);i++)
		{			
		
			os << std::setw(10)<< *(T *)(m_pFirstItemAddress + (i * sizeof(T)))<< " \t " ;
		}

		

		os << std::endl;
    }

    // 初始化FILO对象
    // 
    // 0 初始化成功
    // * 失败
    //##ModelId=50ED3F0901D0
    int Init(char *io_pLineSpace)
    {
    	m_pStartAddress = io_pLineSpace;

		m_pHeader = (CLIFOHeader * )m_pStartAddress;

		m_pFirstItemAddress = m_pStartAddress + sizeof(CLIFOHeader);

		
		return 0;
    }
	const CLIFOHeader * GetHeader() const
	{
		return m_pHeader;
	}
	
	static size_t GetSpaceNeeded(size_t inObjCount)
    {		
		return sizeof(CLIFOHeader) + inObjCount * sizeof(T);			
	};

    // 推出最后进入队列的item
    // 
    // 0 成功
    // * 失败
    //##ModelId=50ED3F0901D4
    int Pop(T& o_objFixSize)
    {
    	if(!IsOk())
			return SPACE_MANAGER_FILO_NOT_INIT;
		
    	if( m_pHeader->m_uiSize <= 0)
		{
			return SPACE_MANAGER_LIFO_NO_ITEM;
		}

		o_objFixSize = *(T *)(m_pFirstItemAddress + (--(m_pHeader->m_uiSize)) * sizeof(T));

		return 0;
    }

    // 将数据压入队列最后的位置
    //##ModelId=50ED3F0901D6
    int Push(T in_objFixSize)
    {
    	if(!IsOk())
			return SPACE_MANAGER_FILO_NOT_INIT;
		
    	if(m_pHeader->m_uiSize >= m_pHeader->m_uiCapacity)
    	{
    		return SPACE_MANAGER_FILO_MAX_ITEM;
    	}

		*(T *)(m_pFirstItemAddress + ((m_pHeader->m_uiSize)++) * sizeof(T)) = in_objFixSize;

		return 0;
    }

	unsigned int GetCount()
	{
		if(!IsOk()) return 0;

		return m_pHeader->m_uiSize;
	}

	bool IsOk()
	{
		return ((m_pStartAddress != NULL) &&(m_pFirstItemAddress != NULL) && (m_pHeader != NULL)  );
	}

	CLIFO()
	{
		m_pStartAddress = NULL;
		m_pFirstItemAddress = NULL;
		m_pHeader = NULL;
	}

	~CLIFO()
	{
		
	}

  private:
    //##ModelId=50ED43620288
    char *m_pStartAddress;

    //##ModelId=50ED4367009C
    char *m_pFirstItemAddress;

    //##ModelId=50ED4182010E
    CLIFOHeader * m_pHeader;

	// 

};



#endif /* CLIFO_H_HEADER_INCLUDED_AF09B739 */
