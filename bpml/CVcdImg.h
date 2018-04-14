#ifndef CVCDIMG_H_HEADER_INCLUDED_ADEDC216
#define CVCDIMG_H_HEADER_INCLUDED_ADEDC216

#include <string>

//##ModelId=521231CB032F
class CVcdImg
{
  public:
    // 0 成功
    // * 失败
    //##ModelId=521231F00256
    int Get(std::string &outVcdMd5, std::string &outImg);

    // 0 正确
    // * 失败
    //##ModelId=52123261005A
    int Check(const std::string & inVcd, const std::string &inVcdMd5);

	int LoginCheck(const std::string & uid,const std::string & inToken,std::string & outToken,int inIntval=1500);

	int LoginGen(const std::string & uid,std::string & outToken,int inIntval=1500);
};



#endif /* CVCDIMG_H_HEADER_INCLUDED_ADEDC216 */
