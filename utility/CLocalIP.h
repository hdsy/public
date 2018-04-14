// *************************************************
// 创建日期： 2010-5-14                      
// 作    者：高勇 (gaussgao@tencent.com)
// 主要功能： 实现基本格式转换，支持HTTP的解析与转换。  
// *************************************************

#ifndef CLOCALIP_H_HEADER_INCLUDED_B3FA04FE
#define CLOCALIP_H_HEADER_INCLUDED_B3FA04FE

#include "mysoft_utility.h"
#include "CStringMap.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
 #include <unistd.h>


namespace MyUtility {


class CLocalIP
{
private:
	static CLocalIP * m_pCLocalIP;

	CStringMap m_mIpList;
      

protected:	
        CLocalIP()
        	{	
        	};        

	
	void getIP()
	{
	        int sock_fd;
	        struct ifreq buf[16];
	        struct ifconf ifc;
	        int inter_num;
	        char *temp = NULL;

	        if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	        	return;

	        ifc.ifc_len = sizeof(buf);
	        ifc.ifc_req = buf;

	        if(ioctl(sock_fd, SIOCGIFCONF, (char *)&ifc) < 0)
	              goto tag_exit;

	        inter_num = ifc.ifc_len / sizeof(struct ifreq);

	        while(inter_num--) 
		{
			if(ioctl(sock_fd, SIOCGIFADDR, (char *)&buf[inter_num]) < 0)
			        goto tag_exit;
			m_mIpList[buf[inter_num].ifr_name] = inet_ntoa(((struct sockaddr_in*)(&buf[inter_num].ifr_addr))->sin_addr);
		}

	tag_exit:        
	        close(sock_fd);
	        
	}
	
public:
       virtual  ~CLocalIP(){};

       static CLocalIP * GetInstance()
       	{
       		if(NULL == m_pCLocalIP)
       		{
       			m_pCLocalIP = new CLocalIP;

       			m_pCLocalIP->getIP();
       		}

       		return m_pCLocalIP;
       	}

	const CStringMap & GetIpMap() const
	{
		return m_mIpList;
	}

};
CLocalIP * CLocalIP::m_pCLocalIP = NULL;

} //MyUtility
#endif //CLOCALIP_H_HEADER_INCLUDED_B3FA04FE

