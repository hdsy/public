#include "CVcdImg.h"


#include <stdio.h>
#include <stdlib.h>
#include <gd.h>
#include <gdfontl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "CBaseEncode.h"
#include "CTime.h"
//#include "CMyLogApi.h"


/*
img:
cookie : md5(vcd+key)
*/

#define VCD_CHARACTER_COUNT	4

#define VCD_CHARSET "ABCDEFGHIJKLMNOPQRST1234567890"

#define VCD_KEY "|znd_lta_20120819232400|"

#define LOGIN_KEY "|znd_lta_20120820144300|"

#define VCD_VALID_INTERVAL 300

//##ModelId=521231F00256
int CVcdImg::Get(std::string &outVcdMd5, std::string &outImg)
{	
	//LOGER_DEBUG << LOGER_ETAG;
	std::string sTmp(""),sStamp(""),sRes("");

	const char * src= VCD_CHARSET;

	char szText[VCD_CHARACTER_COUNT+1];

	int color[VCD_CHARACTER_COUNT];

	unsigned char szPrint[2];

	int gifsize= 0;
	void * gifbuffer;
	
	outImg="";

	srand(getpid() * time(NULL));
	
	gdImagePtr im;
	gdImagePtr prev =NULL;

	im = gdImageCreate(25+VCD_CHARACTER_COUNT*gdFontGetLarge()->w, 10+gdFontGetLarge()->h);

	if (!im) 
	{
		//LOGER_DEBUG << LOGER_ETAG;
		return 1;
	}
	
	gdImageColorAllocate(im, 255, 255, 255); /* allocate white as side effect */

	gifbuffer = gdImageGifAnimBeginPtr(im, &gifsize, 1, 0);
	outImg.append((const char *)gifbuffer,gifsize);
	gdFree(gifbuffer);



	memset(szText,' ',sizeof(szText));	
	szText[VCD_CHARACTER_COUNT]=0;

		
	for(int i = 0; i <= VCD_CHARACTER_COUNT; i++)
	{
		im = gdImageCreate(25+VCD_CHARACTER_COUNT*gdFontGetLarge()->w, 10+gdFontGetLarge()->h);

		gdImageColorAllocate(im, 94, 93, 83);  /* allocate white as side effect */

		if(i != VCD_CHARACTER_COUNT)
		{

			int white= gdImageColorAllocate(im, 255, 255, 255);
			int black= gdImageColorAllocate(im, 0, 0, 0);
			int red  = gdImageColorAllocate(im, 255, 0, 0);
			int yellow= gdImageColorAllocate(im, 0, 255, 0);
			int green= gdImageColorAllocate(im, 0, 0, 255);
			int blue = gdImageColorAllocate(im, 255, 255, 0);

			int colors[]={white,red,yellow,green,blue};
			color[i] = colors[((1+i)*rand())%5];

				szText[i] = src[ rand()%strlen(src)];

				szPrint[1]=0;


				for(int j = 0;j <= i; j++)
				{
						szPrint[0] = szText[j];
						gdImageString(im,
								gdFontGetLarge(),
								(j+1)*5 + (j * gdFontGetLarge()->w),
								5,
								szPrint,
								color[j]);
				}
		}
		else
		{
				//gdImageFilledRectangle(im, 0, 0, im->sx, im->sy, color[i]);
		}

		gifbuffer = gdImageGifAnimAddPtr(im, &gifsize, 1, 0, 0, 80, 1, prev);
		outImg.append((const char *)gifbuffer,gifsize);
		gdFree(gifbuffer);

		if(prev)
		{
				gdImageDestroy(prev);
		}
		prev = im;

		
	}
	

	gifbuffer = gdImageGifAnimEndPtr(&gifsize);
	outImg.append((const char *)gifbuffer,gifsize);
	gdFree(gifbuffer);



	sTmp= sStamp = MyUtility::CBaseEncode::UIntToString(time(NULL));
	
	sTmp += szText;

	sTmp.append(VCD_KEY);
	

	MyUtility::CBaseEncode::md5(sTmp,sRes);

	outVcdMd5 = sStamp + sRes;


	//LOGER_DEBUG <<outVcdMd5 <<"|  img size is "  <<  outImg.size() << LOGER_ETAG;
	
	return 0;
}

int CVcdImg::LoginGen(const std::string & uid,std::string & outToken,int inIntval)
{
	std::string sTmp,sRes,sStamp,sStampEnd;

	unsigned int uiStamp,uiStampEnd,uiNow = time(NULL);

	uiStamp = uiNow; uiStampEnd=uiNow+inIntval;

	sStamp = MyUtility::CBaseEncode::UIntToString(uiStamp);

	sStampEnd = MyUtility::CBaseEncode::UIntToString(uiStampEnd);

	sTmp =	uid + sStamp + sStampEnd + LOGIN_KEY;

	MyUtility::CBaseEncode::md5(sTmp,sRes);

	outToken = sStamp + sStampEnd + sRes;

	return 0;
	
}


int CVcdImg::LoginCheck(const std::string & uid,const std::string & inToken,std::string & outToken,int inIntval)
{
	std::string sTmp,sRes,sStamp,sStampEnd;

	sStamp = inToken.substr(0,10);

	sStampEnd = inToken.substr(10,10);

	sTmp = uid + sStamp+sStampEnd + LOGIN_KEY;

	MyUtility::CBaseEncode::md5(sTmp,sRes);

	sRes = sStamp + sStampEnd + sRes;

	if(inToken != sRes)
		return -1 ; //  非法

	unsigned int uiStamp,uiStampEnd,uiNow;

	uiStamp =  MyUtility::CBaseEncode::StringToUInt(sStamp);
	uiStampEnd =  MyUtility::CBaseEncode::StringToUInt(sStampEnd);
	uiNow = time(NULL);

	if(uiNow > uiStampEnd || uiNow < uiStamp)
		return -2 ;// 过期


	uiStamp = uiNow; uiStampEnd=uiNow+inIntval;

	sStamp = MyUtility::CBaseEncode::UIntToString(uiStamp);
	sStampEnd = MyUtility::CBaseEncode::UIntToString(uiStampEnd);

	sTmp =  uid + sStamp+sStampEnd + LOGIN_KEY;

	MyUtility::CBaseEncode::md5(sTmp,sRes);

	outToken = sStamp + sStampEnd + sRes;

	return 0;
	
}

//##ModelId=52123261005A
int CVcdImg::Check(const std::string & inVcd, const std::string &inVcdMd5)
{
//	std::cout<<"input " << inVcd << " " << inVcdMd5 << std::endl;

	std::string sTmp,sRes,sStamp;
	sStamp = inVcdMd5.substr(0,10);
	sTmp=sStamp;
	sTmp.append(inVcd);
	sTmp.append(VCD_KEY);

	MyUtility::CBaseEncode::md5(sTmp,sRes);

	sRes = sStamp + sRes;
//	std::cout <<"combine {"<< sTmp << "] " << sRes << std::endl;

	if (inVcdMd5 != sRes)
		return -1;//非法


	unsigned int uiStamp,uiNow;

	uiStamp = MyUtility::CBaseEncode::StringToUInt(sStamp);
	uiNow = time(NULL);

//	std::cout << uiStamp << " " << uiNow << " " << uiNow-uiStamp << std::endl;

	if (uiNow - uiStamp > VCD_VALID_INTERVAL)
		return -2; // 超时

	return 0;
	
}

