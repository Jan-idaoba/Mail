#pragma once
#include "../Libcurl/include/curl/curl.h"

namespace libmailNS
{
	class ISmtpWrapper;
	class IMimeMessage;
	//@class
	//*******************************************************************
	//类名: 
	//功能: 公共方法类
	//备注:
	//作者: zengzhaofa. 2022.05.16.
	class LibcurlWrapper
	{
		public:	
			LibcurlWrapper() = delete;
			~LibcurlWrapper() = delete;
			LibcurlWrapper(const LibcurlWrapper&) = delete;
			LibcurlWrapper& operator=(const LibcurlWrapper&) = delete;
			LibcurlWrapper(const LibcurlWrapper&&) = delete;
			LibcurlWrapper& operator=(const LibcurlWrapper&&) = delete;

		public:
			static void InitCurlInfo(CURL* pCurl, struct curl_slist*& recipients, 
										struct curl_slist*& headers, curl_mime*& pMime, 
										curl_mime*& pMixed, curl_mime*& pRelated,
										curl_mime*& pAlternative, ISmtpWrapper* pSmtpObject);
			static void FreeCurlRes(CURL* pCurl, struct curl_slist*& recipients, struct curl_slist*& headers,
										curl_mime*& pMime, curl_mime*& pMixed, curl_mime*& pRelated, 
										curl_mime*& pAlternative);
			static void ResetCurlRes(CURL* pCurl, struct curl_slist*& recipients,struct curl_slist*& headers,
										curl_mime*& pMime,curl_mime*& pMixed, curl_mime*& pRelated, 
										curl_mime*& pAlternative);
			// 设置Curl对象信息
			static void SetCurlInfo(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void SetCurlSender(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void SetCurlContactLists(CURL* pCurl, struct curl_slist*& recipients, 
				ISmtpWrapper* pSmtpClient);
			static void GetCurlContactLists(ISmtpWrapper* pSmtpClient, std::vector<std::string>& vecContactLists);
			static void SetCurlMessageHeader(CURL* pCurl, struct curl_slist*& headers, ISmtpWrapper* pSmtpClient);
			static void SetCurlMessageBody(curl_mime*& pMime, curl_mime*& pAlternative, ISmtpWrapper* pSmtpClient);
			static void SetCurlAttachment(curl_mime*& pMime, curl_mime*& pMix, 
				ISmtpWrapper* pSmtpClient);
			static void GetCurlAttachment(IMimeMessage* pMimeMessage, std::vector<std::string>& vec_AttachmentResources);
			static void SetCurlLinkedResource(curl_mime*& pMime, curl_mime*& pRelated, 
				ISmtpWrapper* pSmtpClient);
			static void GetCurlLinkedResource(IMimeMessage* pMimeMessage, std::vector<std::pair<std::string, std::string>>& vec_LinkedResources);

			// 初始化curl对象信息
			static void SetCurlProxy(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void SetCurlHost(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void SetCurlAccountPassWord(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void EnableCurlSSL(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void SetCurlVerifyPeer(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static void SetCurlVerifyStatus(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			static auto ConversionProxyType(SmtpProxyType eType)->int;
			static void SetCurlConnectTimeout(CURL* pCurl, ISmtpWrapper* pSmtpClient);
			
			// 拼接消息头
			static void AssembleRecipient(IMimeMessage* pMimeMessage, std::string& strRecipient);
			static void AssembleFrom(IMimeMessage* pMimeMessage, std::string& strFrom);
			static void AssembleCC(IMimeMessage* pMimeMessage, std::string& strCC);
			static void AssembleBcc(IMimeMessage* pMimeMessage, std::string& strBcc);
			static void AssemblePriority(IMimeMessage* pMimeMessage, std::string& strPriority);
			static void AssembleMessageID(IMimeMessage* pMimeMessage, std::string& strMessageID);
			static void AssembleSubject(IMimeMessage* pMimeMessage, std::string& strSubject);
			static void AssembleBody(IMimeMessage* pMimeMessage, std::string& strBody);
			static void GenerateMessageHeader(ISmtpWrapper* pSmtpClient, std::string& strHeader);

			// 解析HTML
			static void ParseHTMLResource(IMimeMessage* pMimeMessage);

			// MIME类型转换
			static const char* ConversionMimeType(const char* FileName); 
	};	
}


