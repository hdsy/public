// ***********************************************
// 
// 创建日期： 2009-11-18
// 
// 作    者： gaoyong
// 
// 电子邮件： gaoyong@my-soft.net.cn
// 
// 主要功能： 实现对html文件的格式化输出，以及类似
// 
//            BPEL的流程控制。
// 
// ***********************************************

#ifndef MYFLOW_CMYDISPATCHER_H_HEADER_INCLUDED_B4EB099C
#define MYFLOW_CMYDISPATCHER_H_HEADER_INCLUDED_B4EB099C

#include "myflow_macro.h"

#include <map>

#include <vector>

#include <string>

using namespace std;


#include "CHtml.h"


#include "CMyWorker.h"
#include "CMyAnyMap.h"
#include "CMyVarSpace.h"

// 拥有独立的名字空间，并支持并行和串行模式
// 
// 可解析flow.xml文件，按照流程执行
//##ModelId=4B039295005F
class CMyDispatcher
{
	// 关键字的定义
    //##ModelId=4B04DBE3018E
    enum EKEY { 
		KEY_ASSIGN, 

		KEY_SWITCH,
		KEY_CASE,
		KEY_DEFAULT,

		KEY_ECHO,

		KEY_FOR,
	//	KEY_BREAK,
	//	KEY_CONTINUE,

		KEY_INVOKE,
		KEY_PARAMETER,

		KEY_UNKNOWN };
    // 迭代函数
    //##ModelId=4B1491690175
    int Run(
        // 当前节点
        const CNode *pCurNode, 
        // 输出，采用深度优先遍历
        // 
        // 只能累加
        string &res);
    // 将迭代调用Run
    //##ModelId=4B1491690175
    int Do_KEY_SWITCH(
        // 当前节点
        const CNode *pCurNode, 
        // 输出，采用深度优先遍历
        // 
        // 只能累加
        string &res);
	//##ModelId=4B149377008B
  public:
    //##ModelId=4B14894401E3
    CMyDispatcher();

    //##ModelId=4B1489440212
    virtual ~CMyDispatcher();

    // 输入是一个流程定义文件
    // 输出是一个字符串
    // 
    // 返回值是一个整数，用以标记成功或者失败 
    // 
    // 0 成功
    // * 失败
    // 
    // GetLastError可以获取错误信息
    //##ModelId=4B1489650146
    int StartWork(
        // 流程定义文件
        const string &flowFile, 
        // 输出内容
        string &res,
		const string & inParas="",int parse=1);
    int StartWork(
        // 流程定义文件
        const string &flowFile, 
        // 输出内容
        string &res,
		const CStringMap & inParas);
    int StartWork(
        // 流程定义文件
        const string &flowFile, 
        // 输出内容
        string &res,
		const CStringVector & inParas);
    int StartWork(
        // 流程定义文件
        const string &flowFile, 
        // 输出内容
        string &res,
		const CStringVectorMap & inParas);

  private:
	  string GetExprResult(const string & expr);
	  void InitSysVar();
	  int Do_KEY_ASSIGN(const CNode * pCurNode);
	  int Do_KEY_INVOKE(const CNode * pCurNode);
	  int Do_KEY_ECHO(const CNode * pCurNode,string & res);
	  int Do_KEY_FOR(const CNode * pCurNode,string & res);
	  void InitMyKey();


	  void InitParameters(const std::string & inPara,int parse = 1);
	  void InitParameters(const CStringVectorMap & inPara);
	  void InitParameters(const CStringVector & inPara);
	  void InitParameters(const CStringMap & inPara);
    //##ModelId=4B148C8D028F

    // 流程定义对象
    //##ModelId=4B03940700A2
    CHtml m_htmlFlow;

	CMyWorker * m_pMyWorker;

	CMyVarSpace m_mVar;

	
	map<string,EKEY> m_mKey;

};



#endif /* MYFLOW_CMYDISPATCHER_H_HEADER_INCLUDED_B4EB099C */
