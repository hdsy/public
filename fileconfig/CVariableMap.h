// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#ifndef CVARIABLEMAP_H_HEADER_INCLUDED_B3F0C1D9
#define CVARIABLEMAP_H_HEADER_INCLUDED_B3F0C1D9

#include "mysoft_config.h"
#include "CVariable.h"

namespace MyConfig {

//##ModelId=4C0C5F700221
typedef std::map<std::string,CVariable> CVariableMap;

typedef std::vector<CVariable>CVariableVector;

typedef std::map<std::string,CVariableVector> CVariableVectorMap;

} // namespace MyConfig



#endif /* CVARIABLEMAP_H_HEADER_INCLUDED_B3F0C1D9 */
