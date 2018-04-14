// HttpClient.h: interface for the CHttpClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPCLIENT_H__255D115E_CC34_41C0_8C6D_074DAF6E80FC__INCLUDED_)
#define AFX_HTTPCLIENT_H__255D115E_CC34_41C0_8C6D_074DAF6E80FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mysoft_http.h"

#include "CStringVector.h"

#include "CStringMap.h"
#include "CBaseEncode.h"



using namespace MyUtility;

/*
set-cookie      =       "Set-Cookie:" cookies
   cookies         =       1#cookie
   cookie          =       NAME "=" VALUE *(";" cookie-av)
   NAME            =       attr
   VALUE           =       value
   cookie-av       =       "Comment" "=" value
                   |       "Domain" "=" value
                   |       "Max-Age" "=" value
                   |       "Path" "=" value
                   |       "Secure"
                   |       "Version" "=" 1*DIGIT

Set-Cookie: MSPOK= ; expires=Thu, 30-Oct-1980 16:00:00 GMT;domain=login.live.com;path=/;HTTPOnly= ;version=1
Set-Cookie: PPAuth=AV0DwD0E7lGUTEfPD6veX4Fs!l!W37BU!y6azV3L3w9wQffoc!WEC268i6TkipK3sZFaNe6mmijCEMxRl3lCyh2p2DrxdBcF4b0pxUC7gmYHEZAFaxt278EY0REzJ7*e*o3eR6!!SogEnM3O7VwowtVUjkWvAIfW!SnMRbgfLCERHfdTn90RhE9uU86fVQMSGbE3HYW*VpkTsq4UX5rgm8rhK8RNsIxJuVr!JmbL1PJYcfjBrg$$; domain=login.live.com;secure= ;path=/;HTTPOnly= ;version=1
Set-Cookie: PPLState=1; domain=.live.com;path=/;version=1
Set-Cookie: MSPShared= ; HTTPOnly= ; domain=login.live.com;path=/;Expires=Thu, 30-Oct-1980 16:00:00 GMT
Set-Cookie: MSPPre=gycommunicate@hotmail.com;domain=login.live.com;path=/;Expires=Wed, 30-Dec-2037 16:00:00 GMT
Set-Cookie: MSPCID=0d6282f37ed3a8bc; HTTPOnly= ; domain=login.live.com;path=/;Expires=Wed, 30-Dec-2037 16:00:00 GMT
Set-Cookie: WLOpt=credtype=1&act=[1];domain=login.live.com;path=/;Expires=Wed, 30-Dec-2037 16:00:00 GMT
Set-Cookie: RPSTAuth=EwDYARAnAAAUWkziSC7RbDJKS1VkhugDegv7L0eAAGX6SWmQQ/mDh/g7xpWa2h3Uz4zMwgUxNevM2PkkPNoJLHuSoJ8eOjOIKlRBkwB/6qdwk1wHUSYNzKiBVeIfviNjXXJAMefLCfEZ1LSWFVEW/dabqEd80Z+FiuPRdBWyWxTQMHANQoWyL16aU2UGGaDwv9k+uxGK1sJ3MvGPYu4gA2YAAAgZJ0jEv13YdygB5NJWuLuGH/RC4DIFzG+c1c6eq4qwjWFMZkjpsd4EzYN1m9NvOd/c5s8eUEgL2elr7Lcg8l1R89JrLfvhpbU5ha2Rr7nLFEGA8Nl0HZ6AwtxhZNG5nFdhSUMyihyikTU3g1SIyHEnHW0aGBmhyVBAsW5iNj3NjjRmQLTAn/2qHDoxV40DJi9V2ROBWzWFMxCwJuUV+/n2YDHSrqcNILaJEKymanJz05y6DuGwgtEtCyD2hyg/sdQci09L67rYQ6VNiTbc6h8A+S1A0bMZam72TXI7isBsnN3m5XCHr8Pm1RUXR9UxVZuh6ecNTpNquJ+sMYQSR+UXxygiM6MN8KrfFmCjf8LgXKPnVxQzjqQHkoiy0HdAawzmZ0MTanfuRG9Bn+CvB0dLGQVHAQ==; domain=.live.com;path=/;HTTPOnly= ;version=1
Set-Cookie: RPSTAuthTime=1236676821; domain=login.live.com;path=/;HTTPOnly= ;version=1
Set-Cookie: MSPAuth=2JtKdxiInAzMjWuy!!UL!bSeHDmIK0WGPCeCQnEHpoBPbSPiVZ2KlElwG8EmvH9uf3tXXHQ*zxGK5i0vX243OkPScVbjH82K9dFcy7SW5O3p509WbM42Zs7H!yf6rSvwtH; domain=.live.com;path=/;HTTPOnly= ;version=1
Set-Cookie: MSPProf=2poSSmDDSGlAXtvZuWJzbO4M*dE0VuB8khzJlXV7ZgSjBiZJa7SAjn6m*s5zXhMBwKXHymCu6y*M3TTsF92vmZ9Dtfvy4s1ZxONt*KE0WmWTkwQ1KFpIckPaOnHRKvK44khj9PwQQ0*eXABrHG6H4!MUZL5fdo3*JfTfAwqnUFssxVUvYeHkZ5Ol4gfFFgDjQH; domain=.live.com;path=/;HTTPOnly= ;version=1
Set-Cookie: MSNPPAuth=B*aNycg!I8GrR55pjL3T3LkaAA3YV7QsMENWwdGFeoqqwVOl0Jd6c2NcJWB78X9XLeBvfdDkjmN0oECZsqtD4dO1ZuSB5BC1*bnFsZBO1sY*5bP5GNHz!6WsFG0knD5nFONEkLsfqhvcgHkBboH6LPFepB!0VD2XlIIKzQ5Imc9F1*Limqgb*CyACl*1D*dBRlaxKc9MwH9jD0k6orX*XHnWIKoQDnMhp0pgk5J*q22yofEwqd7ompElWl6q4z8Fy5l!shrMEK2HO9qYykx6P8WmB2ltTjA!x!FjehZ0GUftcX6n6JSR!YFJGa9aCBSPkjq3Ly2El0aAKkkx1BGh2VFWj3LusoEBoGfOAP!3XSW6DjPdOMIQnwjNtQ*mIgQGRvIvDJfHS7FBX91B9fsYLSblrndA5Q2KzmLeCkdZvWqZfM7EnaKB*0*MkV9IB2*eCv2moamEhpeP0P5ZVLUK0wLHcB2rMNuvnapcrBA$; domain=.live.com;path=/;HTTPOnly= ;version=1
Set-Cookie: MH=MSFT; expires=Wed, 30-Dec-2037 16:00:00 GMT;domain=.live.com;path=/;version=1
Set-Cookie: MHW=; expires=Thu, 30-Oct-1980 16:00:00 GMT;domain=.live.com;path=/;version=1
Set-Cookie: MHList=; expires=Thu, 30-Oct-1980 16:00:00 GMT;domain=.live.com;path=/;version=1
Set-Cookie: NAP=V=1.8&E=7c1&C=Dz8pC-PLRM-mH4mkOHromR3gglamW_DMBoLcQt2PV59Fff-jK9LW5w&W=1;domain=.live.com;path=/;Expires=Thu, 18-Jun-2009 16:20:21 GMT
Set-Cookie: ANON=A=92714A2738C46083158EB302FFFFFFFF&E=81b&W=1;domain=.live.com;path=/;Expires=Sat, 26-Sep-2009 16:20:21 GMT
Set-Cookie: MSPVis=$9;domain=login.live.com;path=/
Set-Cookie: MSPSoftVis=@72198325083833620@:@; domain=login.live.com;path=/;version=1*/
class CCookie
{
public:
	CCookie(){m_sName="";m_sValue="";};
	CCookie(const string & strck,int mode=1)
	{
		if(mode == 1)
			ParseRes(strck);

		if(mode == 0)
			ParseReq(strck);
	};
	virtual ~CCookie(){m_mAttr.clear();};

	string	m_sName;
	string	m_sValue;

	CStringMap m_mAttr;

	int ParseRes(const string & strck)
	{
		CStringVector t_aEle,t_aNv;

		t_aEle.Split(strck.c_str(),";");
		
		for(int i = 0; i< t_aEle.size();i++)
		{
			t_aNv.Split(t_aEle[i],"=");
			if(i == 0) //取cookie名值
			{
				if(t_aNv.size() < 2)
					return -1;//格式错误

				m_sName = t_aNv[0];
				m_sValue = t_aNv[1];
			}
			else // 取属性值
			{
				if(t_aNv.size() < 2)
				{
					m_mAttr.insert(map<string,string>::value_type(t_aNv[0],string("")));;
				}
				else
				{
					m_mAttr.insert(map<string,string>::value_type(t_aNv[0],t_aNv[1]));
				}
			}
		}
		return 0;
	};
	int ParseReq(const string & strck)
	{
		CStringVector t_aEle,t_aNv;

		t_aEle.Split(strck.c_str(),";");
		
		for(int i = 0; i< t_aEle.size();i++)
		{
			t_aNv.Split(t_aEle[i],"=");
			//取cookie名值,req里全部都是NV
			{
				if(t_aNv.size() < 2)
					return -1;//格式错误

				m_sName = t_aNv[0];
				m_sValue = t_aNv[1];
			}
		}
		return 0;
	};

};


typedef std::vector<CCookie> CCookieArray;


class CHttpClient  
{
private:
	string m_sSesDir;
public:
	int StoreSession();
	int Analysis();
	
	
	CHttpClient();
	virtual ~CHttpClient();

//TCP,SSL相关参数	
	string	m_sHost,m_sPort;
	//1 tcp; 2 ssl s->c ; 3 ssl c->s; 4 ssl c<->s
	int	m_iType;
	//客户端证书路径
	string	m_sClientCert;
	//证书密码
	string m_sClientCertPwd;
	//受信任跟证书路径，用来验证客户端证书合法性，服务证书合法性
	string	m_sRootCert;
//会话信息:最后一次通讯的状态	
	//请求信息头
		//名值对
		CStringMap m_mReqHead;
		//请求的目标位置，类似/index.html
		string	m_sLocation;
		//协议：HTTP/1.1 HTTP/1.0
		string	m_sReqProtocol;
		//方法：GET POST
		string	m_sMethod;

	//响应信息头
		//名值对
		CStringMap m_mResHead;
		string	m_sResProtocol;
		string	m_sRetCode;
		string	m_sRetDes;
		CCookieArray m_aResCookie;
	//响应信息体
		string	m_sResBody;
	//相应信息体分析
		int	m_iStatus;
		

	//最近会话的COOKIE
		CStringMap m_mCookie;

		CStringMap m_mFixPara;
		CStringMap m_mInpPara;


	int SendAndRecv();

	int LoadConfig(const string & fname,const string & servid);

	int LoadSession();



	int LoadInput(CStringMap & paraMap)
	{
		CStringMap::iterator mapPos;
		
		mapPos = paraMap.begin();
		for(mapPos;mapPos != paraMap.end();mapPos++)
		{
			CStringMap::iterator curPos = m_mInpPara.find(mapPos->first);
			if(curPos != m_mInpPara.end())
			{
				curPos->second = mapPos->second;
			}
		}

//增加此特性，用以支持URL的参数化传递
		if(m_sLocation == string("$_HTTPCALL_URL"))
		{
			m_sLocation = paraMap["_HTTPCALL_URL"];
		}

		if(m_mReqHead["Referer"] == string("$_HTTPCALL_REFERER"))
		{
			m_mReqHead["Referer"]= paraMap["_HTTPCALL_REFERER"];
		}
		
		return 0;
	}


};

#endif // !defined(AFX_HTTPCLIENT_H__255D115E_CC34_41C0_8C6D_074DAF6E80FC__INCLUDED_)
