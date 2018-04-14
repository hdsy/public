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

#ifndef MYFLOW_CMYEXPRESSION_H_HEADER_INCLUDED_B4FB4037
#define MYFLOW_CMYEXPRESSION_H_HEADER_INCLUDED_B4FB4037

#include "myflow_macro.h"

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "CMyExpression.h"
class CMyExpression;

using namespace std;

// 解析并执行表达式。myflow的表达式语法如下定义：
// 
// const = [0-9a-zA-Z%]{*}
// var = $[a-zA-Z_]{1}[0-9a-zA-Z_]{0,31}
// op = $[a-zA-Z_]{1}[0-9a-zA-Z_]{0,31}
// 
// expr := !op(expr|para)
// para := const | var
// 
// [0-9a-zA-z%(),]

enum EERROR {
        // 正确
        SUCCESS,
        // 变量ID不符合规则
        ERROR_VAR, 
        // 运算符 ()  不匹配
        ERROR_OP_END,
        ERROR_STATE,
		ERROR_SYMBOL,
		ERROR_BUF_READING,
		ERROR_BUF_END,
		ERROR_BROTHER,
		ERROR_PARENT
        };


#include "CMyWorker.h"
//##ModelId=4B0381C902E5
class CMyExpression
{
private:
	string m_sIndent,m_sSplitAttr,m_sSplitOp;
  public:
	  string Execute(CMyWorker * pWorker);
	  void	SetPrintVar(const char * indent = "",const char * splitAttr = ",",const char * splitOp="()")
	  {
			m_sIndent = indent;
			m_sSplitAttr = splitAttr;
			m_sSplitOp = splitOp;

	  }
	  string & Print(string & a,const string & indent);
    // 表达式用到的状态
    //##ModelId=4B04DBE3018E
    enum ESTATE { STATE_BEGIN, STATE_END, STATE_BROTHER, STATE_CHILD,
        // 读取
        STATE_BUF_READING,
        // 缓冲读取结束
        STATE_BUF_END,
        // 表达式结束
        STATE_PARENT };

    // 符号表："0-9a-zA_Z_% "
    // 
    // 符号类型枚举值
    //##ModelId=4B04DD690191
    enum ESYMBOL { 
        // a-zA-Z_0-9
        SYMBOL_ID, 
        // ,
        SYMBOL_COMMA, 
        // (
        SYMBOL_OP_BEGIN, 
        // )
        SYMBOL_OP_END, 
        // \t \r\n 以及空格
        SYMBOL_BLANK, 
        // $
        SYMBOL_VAR_FIRST, 
        // %
        SYMBOL_CONST_ONLY, 
        // 字符串结束符 \0
        // 
        // 文件结束符 
        SYMBOL_EOF, SYMBOL_UNKNOWN };

    // 符号类型
    //##ModelId=4B04E0AD03DB
    enum EIDTYPE {TYPE_UNKNOWN, TYPE_VAR, TYPE_CONST, TYPE_OP };
    //##ModelId=4B0504230125
    


    //##ModelId=4B038C6E00C8
    CMyExpression();

    //##ModelId=4B038C63023F
    CMyExpression(CMyExpression* pParent);

    //##ModelId=4B03903000E4
    CMyExpression(
        // 构造并立即执行表达式解析
        const string &sExpr, CMyExpression* pParent);

   //

    //##ModelId=4B03907803D3
    enum EERROR Identify(const string &sExpr);

    // 自我标识自己
    // 
    // 返回标记的类型
    //##ModelId=4B038D5F01D5
    enum EERROR Identify(
        // 字符串形式的表达式，形如：
        // 
        // op(op(para,op(para),para),para)
        const string &sExpr, string::const_iterator &pos,CMyExpression* &m_pCurrent);






    //##ModelId=4B038F08015D
    void Clear();

    //##ModelId=4B038F1D0073
    virtual ~CMyExpression();

  private:
    //##ModelId=4B04E23002CD
    ESYMBOL GetSymbolType(char const &c)
    {
    	enum ESYMBOL res = SYMBOL_UNKNOWN;

	switch(c)
	{		  
        // \t \r\n 以及空格         SYMBOL_BLANK, 
	case ' ':case '\t':case '\r':case '\n':
		res = SYMBOL_BLANK;
		break;
	// a-zA-Z_0-9         SYMBOL_ID, 
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
	case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
	case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
	case 'v': case 'w': case 'x': case 'y': case 'z': 
	case '_': 
	case '0': case '1': case '2': case '3': case '4': case '5': case '6':
	case '7': case '8': case '9':
		//考虑参数经常出现路径的字样，需要增加如下内容
	case ':':case '/':case '\\':case '@':case '&':case '?':case '.':
		res = SYMBOL_ID;
		break;
	// ,        SYMBOL_COMMA, 
	case ',':
		res = SYMBOL_COMMA;
		break;
        // $         SYMBOL_VAR_FIRST, 
	case '$':
		res = SYMBOL_VAR_FIRST;
		break;
	// (        SYMBOL_OP_BEGIN, 
	case '(':
		res = SYMBOL_OP_BEGIN;
		break;
	 // )        SYMBOL_OP_END, 
	case ')':
		res = SYMBOL_OP_END;
		break;
	// %         SYMBOL_CONST_ONLY, 
	case '%':
		res = SYMBOL_CONST_ONLY;
		break;
        // 字符串结束符 \0
        // 
        // 文件结束符         SYMBOL_EOF, 
	case '\0':
		res = SYMBOL_EOF;
		break;
		
	default:
		res = SYMBOL_UNKNOWN;
		break;
	}
	return res;
    }
    //##ModelId=4B04EA3701CF
    ESYMBOL GetSymbolType(string::const_iterator &iter)
    {
    	return GetSymbolType(*iter);
    }
    //##ModelId=4B04EA380308
//    ESYMBOL GetSymbolType(const char *p)
//    {
//    	return GetSymbolType(*p);
//    }
    //##ModelId=4B0500630296
    static void Delete(CMyExpression* pExpr);
    // 处理开始状态
    //##ModelId=4B050360023D
    enum EERROR Identify_STATE_BEGIN(const string &m_sExpr, string::const_iterator & pos ,CMyExpression* &m_pCurrent);
    // 处理读取状态
    //##ModelId=4B0507720189
    enum EERROR Identify_STATE_BUF_READING(const string &m_sExpr, string::const_iterator &       pos,CMyExpression* &m_pCurrent );
    // 处理读取结束状态
    //##ModelId=4B050CDB01B1
    enum EERROR Identify_STATE_BUF_END(const string &m_sExpr, string::const_iterator &      pos,CMyExpression* &m_pCurrent);
    // 处理兄弟节点状态
    //##ModelId=4B050E2F02EB
    enum EERROR Identify_STATE_BROTHER(const string &m_sExpr, string::const_iterator &     pos,CMyExpression* &m_pCurrent);
    // 处理子节点状态
    //##ModelId=4B068C6D0203
    enum EERROR Identify_STATE_CHILD(const string &m_sExpr, string::const_iterator &    pos,CMyExpression* &m_pCurrent);
    // 处理表达式结束节点状态
    //##ModelId=4B068E88004E
    enum EERROR Identify_STATE_PARENT(const string &m_sExpr, string::const_iterator &   pos,CMyExpression* &m_pCurrent);
    // 处理表达式全部结束状态
    //##ModelId=4B06B2190177
    enum EERROR Identify_STATE_END(const string &m_sExpr, string::const_iterator & pos,CMyExpression *& m_pCurrent);








    //##ModelId=4B03820C0340
    string m_sName;

    // 0  未知
    // 1  变量
    // 2  运算符
    // 3  常量
    //##ModelId=4B03822E035E
    EIDTYPE m_eType;

    // 符节点指针
    //##ModelId=4B03845B0260
    CMyExpression*             m_pParent;

    //##ModelId=4B0384670231
    vector<CMyExpression *> m_vChild;

    //##ModelId=4B04F27B0203
    ESTATE m_eState;


	
    //static 
	//	CMyExpression*             m_pCurrent;

};



#endif /* MYFLOW_CMYEXPRESSION_H_HEADER_INCLUDED_B4FB4037 */
