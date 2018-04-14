#ifndef MYUTILITY_MYENCRYPT_H
#define MYUTILITY_MYENCRYPT_H

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <openssl/bio.h> 
#include <openssl/rsa.h> 
#include <openssl/pem.h> 
#include <openssl/err.h> 


#include <openssl/des.h>

class CMyEncrypt
{ 
public:
	
	static int AlipayNotifyVerifySign(const string & origin,const string & sign,const string & type,const string & key)
	{
		int res = -1;
		// type always is RSA2,so ignore

		// key 
		string compactkey;
		compactkey = key;
		{  
			int nPublicKeyLen = compactkey.size();      //strPublicKey为base64编码的公钥字符串  
			for(int i = 64; i < nPublicKeyLen; i+=64)  
			{  
				if(compactkey[i] != '\n')  
				{  
					compactkey.insert(i, "\n");  
				}  
				i++;  
			}  
			compactkey.insert(0, "-----BEGIN PUBLIC KEY-----\n");  
			compactkey.append("\n-----END PUBLIC KEY-----\n");  
		}  
		
		//printf("\r\n publickey : \r\n[%s]\r\n",compactkey.c_str());
		
		// origin should be sha256
		unsigned char sha256[SHA256_DIGEST_LENGTH];//208F9190813FA1F6949F495A4CE3040126ED625343CCB5ADEA8B618E30CAB0D2

		int sha256Len = EVP_Digest((void *)origin.data(),origin.size(),sha256,NULL,EVP_sha256(), NULL);
		
		//printf("\r\n origin data : [%s]\r\n",origin.c_str());

		//printf("\r\n origin sha256 : %d\r\n[",sha256Len);
		//for (int i=0; i<SHA256_DIGEST_LENGTH; i++)
		//	printf("%02X",sha256[i]);
		//printf("]\r\n");
		
		// sign is base64 encoded
		unsigned char szDeSign[1024];memset(szDeSign,0,sizeof(szDeSign));
		int szSignLen = EVP_DecodeBlock(szDeSign,(unsigned char *)sign.data(), sign.size());
		
		//printf("\r\n sign : [%s]\r\n",sign.c_str());
		//printf("\r\n decode sign : %d\r\n[",szSignLen);
		//for (int i=0; i<szSignLen; i++)
		//	printf("%02X",szDeSign[i]);
		//printf("]\r\n");
		szSignLen=szSignLen-2;

		// check
		BIO* memBIO = NULL;  
		memBIO = BIO_new(BIO_s_mem());  
		int bioWriteLen = BIO_write(memBIO, compactkey.c_str(), compactkey.length());  
		RSA* rsa = PEM_read_bio_RSA_PUBKEY(memBIO, NULL, NULL, NULL);  
		if(NULL != rsa) 
		{
			int verifyResult = RSA_verify(NID_sha256, sha256, SHA256_DIGEST_LENGTH, szDeSign, szSignLen, rsa); 
			//int verifyResult2 = RSA_verify(NID_sha256, (const unsigned char*)origin.data(), origin.size(), szDeSign, szSignLen, rsa);  
			
			//printf("\r\n RSA_verify :%d - %d \r\n",verifyResult,verifyResult2);
			
			if(verifyResult == 1) return 0;
		}
		return res;
	}
	static string &sha256(const string &in, string &out)
	{
		char szSign[1024] = {0};

		unsigned char md[SHA256_DIGEST_LENGTH];

		char *pszResult = szSign;

		EVP_Digest((void *)in.data(),in.size(),md,NULL,EVP_sha256(), NULL);

		for (int i=0; i<SHA256_DIGEST_LENGTH; i++)
			sprintf(pszResult+2*i,"%02X",md[i]);

		out =  szSign;

		return out;
	}
	static string &sha1(const string &in, string &out)
	{
		char szSign[1024] = {0};

		unsigned char md[SHA_DIGEST_LENGTH];

		char *pszResult = szSign;

		EVP_Digest((void *)in.data(),in.size(),md,NULL,EVP_sha1(), NULL);

		for (int i=0; i<SHA_DIGEST_LENGTH; i++)
			sprintf(pszResult+2*i,"%02X",md[i]);

		out =  szSign;

		return out;
	}
	static string &md5(const string &in, string &out)
	{
		char szSign[1024] = {0};

		unsigned char md[MD5_DIGEST_LENGTH];

		char *pszResult = szSign;

		EVP_Digest((void *)in.data(),in.size(),md,NULL,EVP_md5(), NULL);

		for (int i=0; i<MD5_DIGEST_LENGTH; i++)
			sprintf(pszResult+2*i,"%02X",md[i]);

		out =  szSign;

		return out;
	}


	static string &Des3(const string &in,const string &key, string &out)
	{
		string inTmp = in;
		string keyTmp = key;

		if(keyTmp.size() == 8)
			return Des(in,key,out);

		else if(keyTmp.size() == 16)
			keyTmp.append(key.data(),8);

		else if(keyTmp.size() < 24)
			keyTmp.append(1,'\0');

		des_key_schedule ks1,ks2,ks3;
                des_cblock 	 desKey,desIV;

                memset(desIV, 0, sizeof(desIV));

                memcpy(desKey, keyTmp.data()+0, sizeof(desKey));
		des_set_key_unchecked(&desKey, ks1);

                memcpy(desKey, keyTmp.data()+8, sizeof(desKey));
		des_set_key_unchecked(&desKey, ks2);

                memcpy(desKey, keyTmp.data()+16, sizeof(desKey));
		des_set_key_unchecked(&desKey, ks3);

                int iBlockCount =  in.size() / sizeof(des_cblock);
                if (in.size() % sizeof(des_cblock) > 0)       iBlockCount++;
                int     iDestLen = iBlockCount * sizeof(des_cblock);

                unsigned char *des = (unsigned  char*)malloc(iDestLen * sizeof(unsigned char));
                memset(des , 0 ,iDestLen);

		des_ede3_cbc_encrypt((const unsigned char *)in.data(), des, in.size(), ks1,ks2,ks3, &desIV, DES_ENCRYPT);

		out.append((const char *)des,iDestLen * sizeof(unsigned char));

		delete []des;

		return out;
	

	}
	static string &UnDes3(const string &in,const string &key, string &out)
	{
		string inTmp = in;
		string keyTmp = key;

		if(keyTmp.size() == 8)
			return UnDes(in,key,out);

		else if(keyTmp.size() == 16)
			keyTmp.append(key.data(),8);

		else if(keyTmp.size() < 24)
			keyTmp.append(1,'\0');

		des_key_schedule ks1,ks2,ks3;
                des_cblock 	 desKey,desIV;

                memset(desIV, 0, sizeof(desIV));

                memcpy(desKey, keyTmp.data()+0, sizeof(desKey));
		des_set_key_unchecked(&desKey, ks1);

                memcpy(desKey, keyTmp.data()+8, sizeof(desKey));
		des_set_key_unchecked(&desKey, ks2);

                memcpy(desKey, keyTmp.data()+16, sizeof(desKey));
		des_set_key_unchecked(&desKey, ks3);

                int iBlockCount =  in.size() / sizeof(des_cblock);
                if (in.size() % sizeof(des_cblock) > 0)       iBlockCount++;
                int     iDestLen = iBlockCount * sizeof(des_cblock);

                unsigned char *des = (unsigned  char*)malloc(iDestLen * sizeof(unsigned char));
                memset(des , 0 ,iDestLen);

		des_ede3_cbc_encrypt((const unsigned char *)in.data(), des, in.size(), ks1,ks2,ks3, &desIV, DES_DECRYPT);

		out.append((const char *)des,iDestLen * sizeof(unsigned char));

		delete []des;

		return out;
	

	}

	static string &Des(const string &in,const string &key, string &out)
	{
		des_key_schedule ks;
                des_cblock 	 desKey,desIV;

		string keyTmp = key;
		while(keyTmp.size() < 8)
			keyTmp.append(1,'\0');
		

                memcpy(desKey, keyTmp.data(), sizeof(desKey));
                memset(desIV, 0, sizeof(desIV));
		/**
  		* 检查key的强度
                switch(des_set_key_checked(&desKey, ks))
                {
                        case -1:
                                DEBUG_LOGER << "DES KEY Bad parity";
                                throw(MyUtility::CMyException("DES KEY Bad parity.",10003006));
                                return 6;
                                break;
                        break;
                        case -2:
                                DEBUG_LOGER << "DES KEY weak";
                                throw(MyUtility::CMyException("DES KEY weak.",10003006));
                                return 6;
                                break;
                        default:
                                // good
                                break;
                }
		**/
		des_set_key_unchecked(&desKey, ks);

                int iBlockCount =  in.size() / sizeof(des_cblock);
                if (in.size() % sizeof(des_cblock) > 0)       iBlockCount++;
                int     iDestLen = iBlockCount * sizeof(des_cblock);

                unsigned char *des = (unsigned  char*)malloc(iDestLen * sizeof(unsigned char));
                memset(des , 0 ,iDestLen);

		des_ncbc_encrypt((const unsigned char *)in.data(), des, in.size(), ks, &desIV, DES_ENCRYPT);

		out.append((const char *)des,iDestLen * sizeof(unsigned char));

		delete []des;

		return out;
	}

	static string &UnDes(const string &in,const string &key, string &out)
	{
		des_key_schedule ks;
                des_cblock 	 desKey,desIV;

		string keyTmp = key;
		while(keyTmp.size() < 8)
			keyTmp.append(1,'\0');

                memcpy(desKey, keyTmp.data(), sizeof(desKey));
                memset(desIV, 0, sizeof(desIV));
		/**
  		* 检查key的强度
                switch(des_set_key_checked(&desKey, ks))
                {
                        case -1:
                                DEBUG_LOGER << "DES KEY Bad parity";
                                throw(MyUtility::CMyException("DES KEY Bad parity.",10003006));
                                return 6;
                                break;
                        break;
                        case -2:
                                DEBUG_LOGER << "DES KEY weak";
                                throw(MyUtility::CMyException("DES KEY weak.",10003006));
                                return 6;
                                break;
                        default:
                                // good
                                break;
                }
		**/
		des_set_key_unchecked(&desKey, ks);

                int iBlockCount =  in.size() / sizeof(des_cblock);
                if (in.size() % sizeof(des_cblock) > 0)       iBlockCount++;
                int     iDestLen = iBlockCount * sizeof(des_cblock);

                unsigned char *des = (unsigned  char*)malloc(iDestLen * sizeof(unsigned char));
                memset(des , 0 ,iDestLen);

		des_ncbc_encrypt((const unsigned char *)in.data(), des, in.size(), ks, &desIV, DES_DECRYPT);

		out.append((const char *)des,iDestLen * sizeof(unsigned char));

		delete []des;

		return out;
	}
};

#endif


