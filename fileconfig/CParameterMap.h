// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现xml-like配置文件的读取。  
// *************************************************

#ifndef CPARAMETERMAP_H_HEADER_INCLUDED_B3F0E558
#define CPARAMETERMAP_H_HEADER_INCLUDED_B3F0E558

#include "mysoft_config.h"
#include "CParamerter.h"

namespace MyConfig {

//##ModelId=4C0C5FF40281
typedef std::map<std::string,CParameter> CParameterMap;

typedef std::vector<CParameter>CParameterVector;

typedef std::map<std::string,CParameterVector> CParameterVectorMap;

} // namespace MyConfig



#endif /* CPARAMETERMAP_H_HEADER_INCLUDED_B3F0E558 */
