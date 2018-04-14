#ifndef E_GTC_UML_CPOINTER_H_HEADER_INCLUDED_AF098402
#define E_GTC_UML_CPOINTER_H_HEADER_INCLUDED_AF098402

#include <sys/types.h>


//##ModelId=50ED1E5F024C
typedef struct ST_CPointer
{
    // 如果地址无效，则返回fasle。
    //##ModelId=50ED2A36018B
    bool IsNull()const
    {
        return (m_uiBlock == 0);
    }


    //##ModelId=50EF7CBF03A2
    void Clear()
    {
        m_uiBlock = 0; m_uiOffset = 0;
    }


    // 唯一标记一块连续的存储空间。
    // 
    // 0 表示无效空间
    //##ModelId=50ED1E9A010B
    unsigned int m_uiBlock;

    // 一个整型，指向一个具体对象在m_Block中的偏移量，按照8BYTE为最小单位
    //##ModelId=50ED1F500372
    unsigned int m_uiOffset;

	ST_CPointer(){m_uiBlock= m_uiOffset = 0;};


	ST_CPointer(unsigned int in_uiBID,unsigned int in_uiOffsetID):m_uiBlock(in_uiBID),m_uiOffset(in_uiOffsetID){};

}CPointer;

inline bool IsNull(CPointer p) {
    return (p.m_uiBlock == 0);
}

static CPointer CPTR_SWAPPED(0, 0xffffffff);

#endif /* E_GTC_UML_CPOINTER_H_HEADER_INCLUDED_AF098402 */
