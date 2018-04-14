// ***********************************************
// 创建日期： 2009-03-27
// 作    者： gaussgao
// 电子邮件： gycommunicate@vip.qq.com
// 主要功能： 实现对html文件的分析，查找和格式化
// ***********************************************

#ifndef CHTMLTAGMAP_H_HEADER_INCLUDED_B62B107F
#define CHTMLTAGMAP_H_HEADER_INCLUDED_B62B107F

#include "mysoft_html.h"
#include "CTagMap.h"

//##ModelId=49D46D1400FA
class CHtmlTagMap : public CTagMap
{
  public:
    //##ModelId=49D46D6A01E4
    static CHtmlTagMap const& GetInstance();

  private:
    //##ModelId=49D46D250399
    CHtmlTagMap();

};



#endif /* CHTMLTAGMAP_H_HEADER_INCLUDED_B62B107F */
