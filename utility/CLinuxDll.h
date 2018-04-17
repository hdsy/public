// author      :  gaussgao
// create date :  2011-03-02
// modify date :  2011-03-02
// descriptor  :  qzone feeds format dll  

#ifndef CLINUXDLL_H_HEADER_INCLUDED_B2916BA0
#define CLINUXDLL_H_HEADER_INCLUDED_B2916BA0

#include "mysoft_utility.h"

// 管理动态库：uc这里主要是对格式转换动态库的管理
//##ModelId=4D6EF93903D1
class CLinuxDll
{
  public:
    // 加载指定目录，指定匹配规则的动态库，
	//返回值：  -1  指定目录没有匹配的文件
    //##ModelId=4D6EF98001A2
    int Load(
        // 目录名
        const std::string & inDir, 
        // ls的匹配参数如：*.so exchange_*.so等等
        const std::string &inMatch);


    // 卸载全部或者指定文件名的动态库
    //##ModelId=4D6EFA6C0062
    int Free(
        // 为all的时候，卸载所有已经加载的动态库
        // 
        // 否则卸载指定文件名的动态库
        const std::string & inFileName);

    //##ModelId=4D6EFB51026A
    CLinuxDll();

    //##ModelId=4D6EFB51028C
    virtual ~CLinuxDll();
    // 兼容uc原exchange-*.so
    int GenSymbolMap(const std::string & inFunctionName); 

    void * GetSymbol(const std::string & inSoName); 

    void Dump(std::string & ostr);

    const std::string & GetLastError(){return m_sLastError;};

  private:
    // 已经加载的动态库列表
    //##ModelId=4D6EFB73029B
    std::map<std::string, void *, less<std::string> > m_mdlib;

    std::map<std::string, void *, less<std::string> > m_msym;

    std::string m_sLastError;

};

extern CLinuxDll g_CLinuxDll;

#endif /* CLINUXDLL_H_HEADER_INCLUDED_B2916BA0 */

