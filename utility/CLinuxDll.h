// author      :  gaussgao
// create date :  2011-03-02
// modify date :  2011-03-02
// descriptor  :  qzone feeds format dll  

#ifndef CLINUXDLL_H_HEADER_INCLUDED_B2916BA0
#define CLINUXDLL_H_HEADER_INCLUDED_B2916BA0

#include "mysoft_utility.h"

// ����̬�⣺uc������Ҫ�ǶԸ�ʽת����̬��Ĺ���
//##ModelId=4D6EF93903D1
class CLinuxDll
{
  public:
    // ����ָ��Ŀ¼��ָ��ƥ�����Ķ�̬�⣬
	//����ֵ��  -1  ָ��Ŀ¼û��ƥ����ļ�
    //##ModelId=4D6EF98001A2
    int Load(
        // Ŀ¼��
        const std::string & inDir, 
        // ls��ƥ������磺*.so exchange_*.so�ȵ�
        const std::string &inMatch);


    // ж��ȫ������ָ���ļ����Ķ�̬��
    //##ModelId=4D6EFA6C0062
    int Free(
        // Ϊall��ʱ��ж�������Ѿ����صĶ�̬��
        // 
        // ����ж��ָ���ļ����Ķ�̬��
        const std::string & inFileName);

    //##ModelId=4D6EFB51026A
    CLinuxDll();

    //##ModelId=4D6EFB51028C
    virtual ~CLinuxDll();
    // ����ucԭexchange-*.so
    int GenSymbolMap(const std::string & inFunctionName); 

    void * GetSymbol(const std::string & inSoName); 

    void Dump(std::string & ostr);

    const std::string & GetLastError(){return m_sLastError;};

  private:
    // �Ѿ����صĶ�̬���б�
    //##ModelId=4D6EFB73029B
    std::map<std::string, void *, less<std::string> > m_mdlib;

    std::map<std::string, void *, less<std::string> > m_msym;

    std::string m_sLastError;

};

extern CLinuxDll g_CLinuxDll;

#endif /* CLINUXDLL_H_HEADER_INCLUDED_B2916BA0 */

