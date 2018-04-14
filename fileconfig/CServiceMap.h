// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#ifndef CSERVICEMAP_H_HEADER_INCLUDED_B3F08666
#define CSERVICEMAP_H_HEADER_INCLUDED_B3F08666

#include "mysoft_config.h"
#include "CService.h"

namespace MyConfig {

//##ModelId=4C0C678600FC
typedef std::map<std::string,CService> CServiceMap;

} // namespace MyConfig



#endif /* CSERVICEMAP_H_HEADER_INCLUDED_B3F08666 */
