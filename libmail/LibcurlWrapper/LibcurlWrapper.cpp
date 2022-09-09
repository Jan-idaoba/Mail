#include "pch.h"
#include "../SmtpWrapper/ISmtpWrapper.h"
#include "../MimeMessage/IMimeMessage.h"
#include "LibcurlWrapper.h"
#include <memory>

constexpr const char* ASCII_HTML = { "text/html" };
constexpr const char* UTF8_HTML = { "text/html;charset=UTF-8" };
constexpr const char* PLAIN_TEXT = { "text/plain" };
constexpr const char* CONTENT_ID = { "Content-ID: " };
constexpr const char* CONTENT_INLINE = { "Content-Disposition: inline" };
constexpr const char* MULTIPART_ALTERNATIVE = { "multipart/alternative" };
constexpr const char* MULTIPART_RELATED = { "multipart/related" };
constexpr const char* MULTIPART_MIXED = { "multipart/mixed" };
constexpr const char* szTo = { "TO: " };
constexpr const char* szFrom = { "FROM: " };
constexpr const char* szCC = { "CC: " };
constexpr const char* szBcc = { "CC: " };
constexpr const char* szSubject = "Subject: ";
constexpr const char* szCid = "cid:";
constexpr const char* Base64 = { "base64" };
constexpr const char* szEnter = { "\r\n" };

namespace libmailNS
{
	//@class
	//功	能:	初始化CURL对象数据
	//作	者:	zengzhaofa. 2022.05.16.
	void LibcurlWrapper::InitCurlInfo(CURL* pCurl, struct curl_slist*& recipients,
										struct curl_slist*& headers, curl_mime*& pMime,
										curl_mime*& pMixed, curl_mime*& pRelated,
										curl_mime*& pAlternative, ISmtpWrapper* pSmtpWrapper)
	{
		if (pCurl && pSmtpWrapper && pMime && pMixed && pRelated && pAlternative) {
			// 设置CURL相关信息
			SetCurlInfo(pCurl, pSmtpWrapper);
			// 设置发送人
			SetCurlSender(pCurl, pSmtpWrapper);
			// 设置联系人
			SetCurlContactLists(pCurl, recipients, pSmtpWrapper);
			// 设置消息头
			SetCurlMessageHeader(pCurl, headers, pSmtpWrapper);
			// 设置消息体
			SetCurlMessageBody(pMime, pAlternative, pSmtpWrapper);
			// 设置链接资源
			SetCurlLinkedResource(pMime, pRelated, pSmtpWrapper);
			// 设置附件资源
			SetCurlAttachment(pMime, pMixed, pSmtpWrapper);
			curl_easy_setopt(pCurl, CURLOPT_MIMEPOST, pMime);
		}
	}

	//@class
	//功	能:	释放CURL对象
	//作	者:	zengzhaofa. 2022.05.16.
	void LibcurlWrapper::FreeCurlRes(CURL* pCurl, struct curl_slist*& recipients,
										struct curl_slist*& headers, curl_mime*& pMime,
										curl_mime*& pMixed, curl_mime*& pRelated, curl_mime*& pAlternative)
	{
		if (!pCurl) {
			return;
		}

		if (recipients != nullptr) {
			curl_slist_free_all(recipients);
			recipients = nullptr;
		}

		if (headers != nullptr) {
			curl_slist_free_all(headers);
			headers = nullptr;
		}

		if (pAlternative) {
			curl_mime_free(pAlternative);
			pAlternative = nullptr;
		}

		if (pRelated) {
			curl_mime_free(pRelated);
			pRelated = nullptr;
		}

		if (pMixed) {
			curl_mime_free(pMixed);
			pMixed = nullptr;
		}

		if (pMime) {
			curl_mime_free(pMime);
			pMime = nullptr;
		}

		// Free
		curl_easy_cleanup(pCurl);
	}

	//@class
	//功	能:	重置CURL对象
	//作	者:	zengzhaofa. 2022.05.16.
	//
	void LibcurlWrapper::ResetCurlRes(CURL* pCurl, struct curl_slist*& recipients,
										struct curl_slist*& headers, curl_mime*& pMime,
										curl_mime*& pMixed, curl_mime*& pRelated, curl_mime*& pAlternative)
	{
		if (!pCurl) {
			return;
		}

		if (recipients != nullptr) {
			curl_slist_free_all(recipients);
			recipients = nullptr;
		}

		if (headers != nullptr) {
			curl_slist_free_all(headers);
			headers = nullptr;
		}

		if (pAlternative) {
			curl_mime_free(pAlternative);
			pAlternative = nullptr;
		}

		if (pRelated) {
			curl_mime_free(pRelated);
			pRelated = nullptr;
		}

		if (pMixed) {
			curl_mime_free(pMixed);
			pMixed = nullptr;
		}

		if (pMime) {
			curl_mime_free(pMime);
			pMime = nullptr;
		}

		// reset
		curl_easy_reset(pCurl);
	}

	/*@class
	*******************************************************************
	功	能:	生成消息头
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::GenerateMessageHeader(ISmtpWrapper* pSmtpClient, std::string& strHeader)
	{
		if (pSmtpClient) {
			auto pMimeMessage = pSmtpClient->GetMimeMessage();
			if (pMimeMessage) {
				AssembleRecipient(pMimeMessage, strHeader);
				AssembleFrom(pMimeMessage, strHeader);
				AssembleCC(pMimeMessage, strHeader);
				AssembleBcc(pMimeMessage, strHeader);
				AssemblePriority(pMimeMessage, strHeader);
				AssembleMessageID(pMimeMessage, strHeader);
				AssembleSubject(pMimeMessage, strHeader);
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置CURL对象数据
	参	数:	pCurl:			curl对象指针.
			pSmtpClient:	SmtpClient对象指针.
			bAsync:			是否异步.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlInfo(CURL* pCurl, ISmtpWrapper* pSmtpWrapper)
	{
		if (pCurl && pSmtpWrapper) {
			do {
				// Set Proxy
				SetCurlProxy(pCurl, pSmtpWrapper);
				// Set Host
				SetCurlHost(pCurl, pSmtpWrapper);
				// Timeout
				SetCurlConnectTimeout(pCurl, pSmtpWrapper);
				// Set User & Password
				SetCurlAccountPassWord(pCurl, pSmtpWrapper);
				// 设置是否启用SSL以及SSL版本
				EnableCurlSSL(pCurl, pSmtpWrapper);
				// 设置是否校验服务器证书
				SetCurlVerifyPeer(pCurl, pSmtpWrapper);
				// 设置是否启用OCSP装订进行证书吊销在线查询
				SetCurlVerifyStatus(pCurl, pSmtpWrapper);
			} while (false);
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置发送者
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlSender(CURL* pCurl, ISmtpWrapper* pSmtpWrapper)
	{
		if (pSmtpWrapper && pCurl) {
			auto pMimeMessage = pSmtpWrapper->GetMimeMessage();
			if (pMimeMessage) {
				auto Sender = pMimeMessage->GetSender();
				if (Sender && strlen(Sender)) {
					curl_easy_setopt(pCurl, CURLOPT_MAIL_FROM, Sender);
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置联系人
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlContactLists(CURL* pCurl, struct curl_slist*& recipients,
												ISmtpWrapper* pSmtpWrapper)
	{
		std::vector<std::string> vecContactLists;
		if (pSmtpWrapper && pCurl) {
			auto pMimeMessage = pSmtpWrapper->GetMimeMessage();
			if (pMimeMessage) {
				GetCurlContactLists(pSmtpWrapper, vecContactLists);
				if (!vecContactLists.empty()) {
					for (auto& Contact : vecContactLists) {
						recipients = curl_slist_append(recipients, Contact.c_str());
					}
				}
				curl_easy_setopt(pCurl, CURLOPT_MAIL_RCPT, recipients);
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置消息头
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlMessageHeader(CURL* pCurl, struct curl_slist*& headers,
												ISmtpWrapper* pSmtpClient)
	{
		std::string strHeader;
		if (pSmtpClient && pCurl) {
			GenerateMessageHeader(pSmtpClient, strHeader);
			//std::unique_ptr<char[]> pText(new char[strHeader.size() + 1]());
			auto pText = std::make_unique<char[]>(strHeader.size() + 1);
			memcpy_s(pText.get(), strHeader.size(), strHeader.c_str(), strHeader.size());
			headers = curl_slist_append(headers, pText.get());
			curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, headers);
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置消息体
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlMessageBody(curl_mime*& pMime, curl_mime*& pAlternative,
												ISmtpWrapper* pSmtpClient)
	{
		curl_mimepart* part;
		std::string strHTMLBody;
		std::string strPlainTextBody;
		struct curl_slist* slist = nullptr;

		if (pSmtpClient) {
			auto pMimeMessage = pSmtpClient->GetMimeMessage();
			if (pMimeMessage) {
				// HTML message
				//strHTMLBody = pMimeMessage->GetMessageBody(1);
				int iEncodingType = pMimeMessage->GetTransferEncoding();
				if (!strHTMLBody.empty()) {
					if (iEncodingType == 0) {
						//WideChar2MultiByte(wstrHTMLBody.c_str(), strbuffer, EnCodingType::eASCII);
					}
					else if (iEncodingType == 1) {
						//WideChar2MultiByte(wstrHTMLBody.c_str(), strbuffer, EnCodingType::eUTF8);
					}
					if (pMimeMessage->GetMessageBodyFormat()) {
						part = curl_mime_addpart(pAlternative);
						curl_mime_data(part, strHTMLBody.c_str(), CURL_ZERO_TERMINATED);
						if (iEncodingType == 0) {
							curl_mime_type(part, ASCII_HTML);
						}
						else if (iEncodingType == 1) {
							curl_mime_type(part, UTF8_HTML);
						}
					}
				}

				// plain text message
				//strPlainTextBody = pMimeMessage->GetMessageBody();
				if (!strPlainTextBody.empty()) {
					part = curl_mime_addpart(pAlternative);
					if (iEncodingType == 0) {
						//WideChar2MultiByte(wstrHTMLBody.c_str(), strbuffer, EnCodingType::eASCII);
					}
					else if (iEncodingType == 1) {
						//WideChar2MultiByte(wstrHTMLBody.c_str(), strbuffer, EnCodingType::eUTF8);
					}
					curl_mime_data(part, strPlainTextBody.c_str(), CURL_ZERO_TERMINATED);
					curl_mime_type(part, PLAIN_TEXT);
				}

				// build Alternative part				
				if (!strPlainTextBody.empty() || !strHTMLBody.empty()) {
					part = curl_mime_addpart(pMime);
					curl_mime_subparts(part, pAlternative);
					curl_mime_type(part, MULTIPART_ALTERNATIVE);
					slist = curl_slist_append(nullptr, CONTENT_INLINE);
					curl_mime_headers(part, slist, 1);
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置附件信息
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlAttachment(curl_mime*& pMime, curl_mime*& pMixed,
		ISmtpWrapper* pSmtpClient)
	{
		curl_mimepart* part;
		std::vector<std::string> vecAttachments;

		if (pSmtpClient) {
			auto pMimeMessage = pSmtpClient->GetMimeMessage();
			if (pMimeMessage) {
				GetCurlAttachment(pMimeMessage, vecAttachments);
				if (!vecAttachments.empty()) {
					for (auto& attachment : vecAttachments) {
						if (!attachment.empty()) {
							part = curl_mime_addpart(pMixed);
							curl_mime_filedata(part, attachment.c_str());
							curl_mime_encoder(part, Base64);
						}
					}
					// build mixed part
					part = curl_mime_addpart(pMime);
					curl_mime_subparts(part, pMixed);
					curl_mime_type(part, MULTIPART_MIXED);
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置代理信息
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlProxy(CURL* pCurl, ISmtpWrapper* pSmtpWrapper)
	{
		// Set Proxy
		std::string strbuffer;
		std::string strUsername;
		std::string strPassword;
		wchar_t wszProxyInfo[256] = { 0 };
		wchar_t wszProxyUsername[256] = { 0 };
		wchar_t wszProxyPassword[256] = { 0 };
		//if (pCurl) {
		//	if (pSmtpClient->GetProxy()) {
		//		pSmtpClient->GetProxyInfo(wszProxyInfo, static_cast<int>(ProxyInfo::eHOST));
		//		WideChar2MultiByte(wszProxyInfo, strbuffer);
		//		curl_easy_setopt(pCurl, CURLOPT_PROXY, strbuffer.c_str());														// host
		//		pSmtpClient->GetProxyInfo(wszProxyInfo, static_cast<int>(ProxyInfo::ePORT));
		//		WideChar2MultiByte(wszProxyInfo, strbuffer);
		//		curl_easy_setopt(pCurl, CURLOPT_PROXYPORT, stoi(strbuffer));													// port
		//		pSmtpClient->GetProxyInfo(wszProxyInfo, static_cast<int>(ProxyInfo::ePROXYTYPE));
		//		WideChar2MultiByte(wszProxyInfo, strbuffer);
		//		curl_easy_setopt(pCurl, CURLOPT_PROXYTYPE, ConversionProxyType(static_cast<SmtpProxyType>(stoi(strbuffer))));	// type
		//		pSmtpClient->GetProxyInfo(wszProxyPassword, static_cast<int>(ProxyInfo::ePASSWORD));
		//		pSmtpClient->GetProxyInfo(wszProxyUsername, static_cast<int>(ProxyInfo::eUSERNAME));
		//		WideChar2MultiByte(wszProxyPassword, strPassword);
		//		WideChar2MultiByte(wszProxyUsername, strUsername);
		//		if (!strUsername.empty() && !strPassword.empty()) {
		//			curl_easy_setopt(pCurl, CURLOPT_PROXYUSERNAME, strUsername.c_str());							// username
		//			curl_easy_setopt(pCurl, CURLOPT_PROXYPASSWORD, strPassword.c_str());							// password
		//		}
		//	}
		//}
	}

	/*@class
	*******************************************************************
	功	能:	设置连接主机
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlHost(CURL* pCurl, ISmtpWrapper* pSmtpClient)
	{
		// Set Domain
		if (pCurl && pSmtpClient) {
			std::string strHost = pSmtpClient->GetHost();
			int iPort = pSmtpClient->GetPort();
			if (!strHost.empty()) {
				curl_easy_setopt(pCurl, CURLOPT_URL, strHost.c_str());
				if (iPort != -1) {
					curl_easy_setopt(pCurl, CURLOPT_PORT, iPort);
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置用户名密码
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlAccountPassWord(CURL* pCurl, ISmtpWrapper* pSmtpClient)
	{
		// Set User & Password
		if (pCurl && pSmtpClient) {
			std::string strUsername = pSmtpClient->GetUsername();
			std::string strPassword = pSmtpClient->GetPassword();
			if (!strUsername.empty()) {
				curl_easy_setopt(pCurl, CURLOPT_USERNAME, strUsername.c_str());
			}
			if (!strPassword.empty()) {
				curl_easy_setopt(pCurl, CURLOPT_PASSWORD, strPassword.c_str());
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置是否启用SSL以及SSL版本
	作	者:
	*******************************************************************/
	void LibcurlWrapper::EnableCurlSSL(CURL* pCurl, ISmtpWrapper* pSmtpClient)
	{
		bool bEnbleSSL = true;
		int nSSLProtocolVersion = static_cast<int>(SmtpSSLVer::SMTP_SSLVERSION_DEFAULT);

		if (!pCurl || !pSmtpClient) {
			return;
		}

		// 是否启用SSL
		bEnbleSSL = pSmtpClient->GetEnableTLS();
		if (bEnbleSSL)
		{
			curl_easy_setopt(pCurl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

			// 设置SSL版本
			nSSLProtocolVersion = pSmtpClient->GetSecureProtocol();
			switch (nSSLProtocolVersion)
			{
			case 0:
				curl_easy_setopt(pCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_DEFAULT);
				break;
			case 1:
				curl_easy_setopt(pCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_0 | CURL_SSLVERSION_MAX_TLSv1_0);
				break;
			case 2:
				curl_easy_setopt(pCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_1 | CURL_SSLVERSION_MAX_TLSv1_1);
				break;
			case 3:
				curl_easy_setopt(pCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2 | CURL_SSLVERSION_MAX_TLSv1_2);
				break;
			case 4:
				curl_easy_setopt(pCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_3 | CURL_SSLVERSION_MAX_TLSv1_3);
				break;
			default:
				break;
			}
		}
		else
		{
			curl_easy_setopt(pCurl, CURLOPT_USE_SSL, CURLUSESSL_NONE);
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置是否校验服务器证书
	作	者:
	*******************************************************************/
	void LibcurlWrapper::SetCurlVerifyPeer(CURL* pCurl, ISmtpWrapper* pSmtpClient)
	{
		int nIgnoreServerCert = static_cast<int>(SecurityIgnoreFlag::IGNORE_SERVER_CERT);
		if (!pCurl || !pSmtpClient) {
			return;
		}

		// 是否校验服务器证书
		nIgnoreServerCert = pSmtpClient->GetIgnoreServerCert();
		if (nIgnoreServerCert == static_cast<int>(SecurityIgnoreFlag::IGNORE_SERVER_CERT)) {
			// 不验证
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
		}
		else {
			// 验证
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 1L);

			// 默认使用操作系统的本地 CA 存储进行证书验证
			curl_easy_setopt(pCurl, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置是否启用OCSP装订，在线校验证书是否吊销
	作	者:
	*******************************************************************/
	void LibcurlWrapper::SetCurlVerifyStatus(CURL* pCurl, ISmtpWrapper* pSmtpClient)
	{
		bool bCheckRevocation = false;

		if (!pCurl || !pSmtpClient) {
			return;
		}

		// 是否启用OCSP装订
		bCheckRevocation = pSmtpClient->GetCheckServerCertRevocation();
		if (bCheckRevocation) {
			// 启用
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYSTATUS, 1L);
		}
		else {
			// 不启用
			curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYSTATUS, 0L);
		}
	}

	/*@class
	*******************************************************************
	功	能:	转换代理类型
	参	数:	eType:	代理类型.

	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	auto LibcurlWrapper::ConversionProxyType(SmtpProxyType eType) ->int
	{
		if (eType == SmtpProxyType::SMTP_PROXY_4) {
			return CURLPROXY_SOCKS4;
		}
		else if (eType == SmtpProxyType::SMTP_PROXY_4A) {
			return CURLPROXY_SOCKS4A;
		}
		else if (eType == SmtpProxyType::SMTP_PROXY_5) {
			return CURLPROXY_SOCKS5;
		}
		else if (eType == SmtpProxyType::SMTP_PROXY_5A) {
		}
		return CURLPROXY_SOCKS5;
	}

	/*@class
	*******************************************************************
	功	能:	设置连接超时
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlConnectTimeout(CURL* pCurl, ISmtpWrapper* pSmtpClient)
	{
		if (pCurl && pSmtpClient) {
			long lTimeout = pSmtpClient->GetTimeout();
			if (lTimeout >= 0) {
				curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, lTimeout);
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	获取联系人列表
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::GetCurlContactLists(ISmtpWrapper* pSmtpWrapper, std::vector<std::string>& vecContactLists)
	{
		if (pSmtpWrapper) {
			auto pMimeMessage = pSmtpWrapper->GetMimeMessage();
			if (pMimeMessage) {
				int iRecipientsCount = pMimeMessage->GetRecipientsCount();
				int iCcCount = pMimeMessage->GetCcsCount();
				int iBccCount = pMimeMessage->GetBccsCount();
				for (int i = 1; i <= iRecipientsCount; ++i) {
					vecContactLists.push_back(pMimeMessage->GetRecipient(i));
				}
				for (int i = 1; i <= iCcCount; ++i) {
					vecContactLists.push_back(pMimeMessage->GetCc(i));
				}
				for (int i = 1; i <= iBccCount; ++i) {
					vecContactLists.push_back(pMimeMessage->GetBcc(i));
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	获取附件列表
	参	数:	pMimeMessage:			Message对象指针.
			vec_AttachmentResources:附件资源容器.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::GetCurlAttachment(IMimeMessage* pMimeMessage, std::vector<std::string>& vecAttachmentResources)
	{
		if (pMimeMessage) {
			unsigned int iAttachmentsCount = pMimeMessage->GetAttachmentsCount();
			for (unsigned int i = 1; i <= iAttachmentsCount; ++i) {
				vecAttachmentResources.push_back(pMimeMessage->GetAttachment(i));
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	设置引用资源列表
	参	数:	pCurl:		curl对象指针.
			pMime:		mime结构对象.
			part:		mime部分对象.
			pSmtpClient:Smtpclient对象指针.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::SetCurlLinkedResource(curl_mime*& pMime, curl_mime*& pRelated,
												ISmtpWrapper* pSmtpClient)
	{
		std::string strbuffer;
		std::string	strHTMLBody;
		curl_mimepart* part;
		struct curl_slist* slist = NULL;
		std::vector<std::pair<std::string, std::string>> vecResource;

		if (pSmtpClient) {
			auto pMimeMessage = pSmtpClient->GetMimeMessage();
			if (pMimeMessage) {
				//strHTMLBody = pMimeMessage->GetMessageBody(1);
				if (!pMimeMessage->GetMessageBodyFormat() || strHTMLBody.empty()) {
					return;
				}
				GetCurlLinkedResource(pMimeMessage, vecResource);
				if (!vecResource.empty()) {
					for (auto& resource : vecResource) {
						if (!get<0>(resource).empty() && !get<1>(resource).empty()) {
							std::string strcontentID(CONTENT_ID);
							part = curl_mime_addpart(pRelated);
							curl_mime_filedata(part, get<0>(resource).c_str());
							//strbuffer = ConversionMimeType(get<0>(resource).c_str());
							if (!strbuffer.empty()) {
								curl_mime_type(part, strbuffer.c_str());
							}
							//WideChar2MultiByte(get<1>(resource).c_str(), strbuffer);
							//strbuffer.insert(0, "<");
							//strbuffer.append(">");
							//strcontentID.append(strbuffer);
							slist = curl_slist_append(nullptr, strcontentID.c_str());
							slist = curl_slist_append(slist, CONTENT_INLINE);
							curl_mime_headers(part, slist, 1);
							curl_mime_encoder(part, Base64);
						}
					}
					// build related part
					part = curl_mime_addpart(pMime);
					curl_mime_subparts(part, pRelated);
					curl_mime_type(part, MULTIPART_RELATED);
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	获取引用资源列表
	参	数:	pMimeMessage:		message对象指针.
			vec_LinkedResources:链接资源容器.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::GetCurlLinkedResource(IMimeMessage* pMimeMessage, std::vector<std::pair<std::string, std::string>>& vecLinkedResources)
	{
		if (pMimeMessage) {
			unsigned int iResourcesCount = pMimeMessage->GetLinkedResourcesCount();
			for (unsigned int i = 1; i <= iResourcesCount; ++i) {
				std::pair<std::string, std::string> Resources;
				std::string strResource = pMimeMessage->GetLinkedResourceFileName(i);
				std::string strContantID = pMimeMessage->GetLinkedResourceContantID(i);
				if (!strResource.empty()) {
					get<0>(Resources) = strResource;
				}
				if (!strContantID.empty()) {
					get<1>(Resources) = strContantID;
				}
				vecLinkedResources.push_back(Resources);
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	拼接接收人
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleRecipient(IMimeMessage* pMimeMessage, std::string& strRecipient)
	{
		if (!pMimeMessage) {
			return;
		}

		unsigned int iRecipientCount = pMimeMessage->GetRecipientsCount();
		for (unsigned int i = 1; i <= iRecipientCount; ++i) {
			std::string strReceiver = pMimeMessage->GetRecipient(i);
			std::string strOtherName = pMimeMessage->GetRecipient(i, 1);
			if (!strOtherName.empty() || !strReceiver.empty()) {
				if (strOtherName.empty()) {
					strRecipient += szTo + strReceiver + szEnter;
				}
				else {
					strRecipient += szTo + strOtherName + szEnter;
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	拼接发送人
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleFrom(IMimeMessage* pMimeMessage, std::string& strFrom)
	{
		if (!pMimeMessage) {
			return;
		}

		std::string strSender = pMimeMessage->GetSender();
		std::string strOtherName = pMimeMessage->GetSender(1);
		if (!strSender.empty() || !strOtherName.empty()) {
			if (strOtherName.empty()) {
				strFrom += szFrom + strSender + szEnter;
			}
			else {
				strFrom += szFrom + strOtherName + szEnter;
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	拼接抄送人
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleCC(IMimeMessage* pMimeMessage, std::string& strCC)
	{
		if (!pMimeMessage) {
			return;
		}

		unsigned int iCcCount = pMimeMessage->GetCcsCount();
		for (unsigned int i = 1; i <= iCcCount; ++i) {
			std::string str_Cc = pMimeMessage->GetCc(i);
			std::string strOtherName = pMimeMessage->GetCc(i, 1);
			if (!strOtherName.empty() || !str_Cc.empty()) {
				if (strOtherName.empty()) {
					strCC += szCC + str_Cc + szEnter;
				}
				else {
					strCC += szCC + strOtherName + szEnter;
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	拼接隐私抄送人
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleBcc(IMimeMessage* pMimeMessage, std::string& strBcc)
	{
		if (!pMimeMessage) {
			return;
		}

		unsigned int iBccCount = pMimeMessage->GetBccsCount();
		for (unsigned int i = 1; i <= iBccCount; ++i) {
			std::string str_Bcc = pMimeMessage->GetBcc(i);
			std::string strOtherName = pMimeMessage->GetBcc(i, 1);
			if (!strOtherName.empty() || !str_Bcc.empty()) {
				if (strOtherName.empty()) {
					strBcc += szBcc + str_Bcc + szEnter;
				}
				else {
					strBcc += szBcc + strOtherName + szEnter;
				}
			}
		}
	}

	/*@class
	*******************************************************************
	功	能:	拼接邮件等级
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssemblePriority(IMimeMessage* pMimeMessage, std::string& strPriority)
	{
		if (!pMimeMessage) {
			return;
		}

		int iPriority = pMimeMessage->GetPriority();
		if (iPriority == static_cast<int>(MailPriority::eMAILPRIORITY_NORMAL)) {
			strPriority += "X-Priority: 3 \r\n";
		}
		else if (iPriority == static_cast<int>(MailPriority::eMAILPRIORITY_LOW)) {
			strPriority += "X-Priority: 4 \r\n";
		}
		else if (iPriority == static_cast<int>(MailPriority::eMAILPRIORITY_HIGH)) {
			strPriority += "X-Priority: 2 \r\n";
		}
	}

	/*@class
	*******************************************************************
	功	能:	拼接邮件MessageID
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleMessageID(IMimeMessage* pMimeMessage, std::string& strMessageID)
	{
		if (!pMimeMessage) {
			return;
		}
		std::string strGUID;
		//GenerateGUID(wstr_GUID);
		wchar_t szBuffer[256] = { 0 };
		DWORD dwLength = sizeof(szBuffer);
		//GetComputerNameEx((COMPUTER_NAME_FORMAT)0, szBuffer, &dwLength);
		strMessageID.append("Message - ID: ");
		strMessageID.append(strGUID);
		strMessageID.append("@");
		//strMessageID.append(szBuffer);
		strMessageID.append(szEnter);
	}

	/*@class
	*******************************************************************
	功	能:	拼接主题
	参	数:	pMimeMessage:	message对象指针.
			wstrMessageID:	拼接字段.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleSubject(IMimeMessage* pMimeMessage, std::string& strSubject)
	{
		if (!pMimeMessage) {
			return;
		}

		strSubject.append(szSubject);
		strSubject.append(pMimeMessage->GetSubject());
		strSubject.append(szEnter); 
		strSubject.append(szEnter);
	}

	/*@class
	*******************************************************************
	功	能:	拼接邮件消息体
	参	数:	pMimeMessage:	message对象指针.
			wstrBody:		拼接字段.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void LibcurlWrapper::AssembleBody(IMimeMessage* pMimeMessage, std::string& strBody)
	{
		if (!pMimeMessage) {
			return;
		}

		//strBody.append(pMimeMessage->GetMessageBody());
		strBody.append(szEnter);
		strBody.append(szEnter);
	}

	///*@class
	//*******************************************************************
	//功	能:	读文件.
	//参	数:	szFile:		文件名.
	//		pData:		文件数据指针.
	//		dReadCount: 字符数量
	//返回值:	成功->ture, 失败->false.
	//作	者:	zengzhaofa. 2022.05.16.
	//*******************************************************************/
	//bool LibcurlWrapper::GetFileInfo(const wchar_t* szFile, unsigned char*& pData, DWORD& dReadCount)
	//{
	//	HANDLE hFile = CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
	//	if (!hFile) {
	//		return false;
	//	}

	//	bool bRet = false;
	//	LARGE_INTEGER lFileSize = { 0 };
	//	do {
	//		if (!GetFileSizeEx(hFile, &lFileSize)) {
	//			break;
	//		}

	//		pData = new unsigned char[lFileSize.LowPart + 1]();
	//		if (!pData) {
	//			break;
	//		}

	//		if (!ReadFile(hFile, pData, lFileSize.LowPart, &dReadCount, NULL)) {
	//			delete[] pData;
	//			break;
	//		}
	//		bRet = true;
	//	} while (false);

	//	CloseHandle(hFile);
	//	return bRet;
	//}

	///*@class
	//*******************************************************************
	//功	能:	写文件.
	//参	数:	szFile:		文件名称.
	//		pData:		文件数据指针.
	//		dWriteCount:字符长度.
	//返回值:	成功->ture,失败->false.
	//作	者:	zengzhaofa. 2022.05.16.
	//*******************************************************************/
	//bool LibcurlWrapper::SetFileInfo(const wchar_t* szFile, unsigned char* pData, DWORD dWriteCount)
	//{
	//	HANDLE hFile = CreateFile(szFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, NULL, NULL);
	//	if (!hFile) {
	//		return false;
	//	}

	//	DWORD dWrittenCount = 0;
	//	if (!WriteFile(hFile, pData, dWriteCount, &dWrittenCount, NULL)) {
	//		CloseHandle(hFile);
	//		return false;
	//	}

	//	CloseHandle(hFile);
	//	return true;
	//}

	/*@class
	*******************************************************************
	功	能:	解析HTML & 内联资源.
	参	数:	pMimeMessage:	Messgae对象指针.
	返回值:
	作	者:	zengzhaofa. 2022.05.27.
	*******************************************************************/
	void LibcurlWrapper::ParseHTMLResource(IMimeMessage* pMimeMessage)
	{
		int iPos = 0;
		int iBegin = 0;
		int iCount = 0;
		std::string strbuffer;
		std::vector<std::string> _vec;
		std::map<int, std::pair<bool, std::string>> _map;

		if (pMimeMessage) {
			//std::string strBody = pMimeMessage->GetMessageBody(1);
			//if (!strBody.empty()) {
			//	// 拆分HTML.
			//	while (strBody.find('>', iBegin) != std::string::npos) {
			//		std::pair<bool, std::string> _pair;
			//		_pair.first = false;
			//		iPos = strBody.find('>', iBegin);
			//		strbuffer.assign(strBody, iBegin, iPos - iBegin + 1);
			//		int iLeftPos = strBody.find('<', iBegin);
			//		if (iLeftPos != std::string::npos && iLeftPos < iPos) {
			//			if (tolower(strBody[iLeftPos + 1]) == 'i'
			//				&& tolower(strBody[iLeftPos + 2]) == 'm'
			//				&& tolower(strBody[iLeftPos + 3]) == 'g') {
			//				int iLeft = strBody.find('"', iLeftPos);
			//				int iRight = strBody.find('"', iLeft + 1);
			//				if (iLeft != std::string::npos
			//					&& iRight != std::string::npos
			//					&& iLeft < iPos && iRight < iPos) {
			//					_vec.push_back(strBody.substr(iLeft + 1, iRight - iLeft - 1));
			//					_pair.first = true;
			//				}
			//			}
			//		}
			//		_pair.second = strbuffer;
			//		_map[iCount++] = _pair;
			//		iBegin = iPos + 1;
			//	}

			//	// 剩余部分.
			//	if (iPos < (int)(strBody.size() - 1)) {
			//		_map[iCount++] = std::make_pair(false, strBody.substr(iPos + 1, strBody.size() - iPos));
			//	}

			//	// Add内联资源.
			//	for (auto& i : _vec) {
			//		pMimeMessage->AddLinkedResource(i.c_str(), i.c_str());
			//	}

			//	// 拼装Body.
			//	strBody.clear();
			//	for (auto& i : _map) {
			//		if (i.second.first) {
			//			int iIndex = i.second.second.find('"', 0);
			//			if (iIndex != std::string::npos) {
			//				i.second.second.insert(iIndex + 1, szCid);
			//			}
			//			strBody.append(i.second.second);
			//		}
			//		else {
			//			strBody.append(i.second.second);
			//		}
			//	}
			//	//pMimeMessage->SetMessageBody(strBody.c_str(), 1);
			//}
		}
	}

	/*@class
	*******************************************************************
	功	能:	转换引用资源的资源类型
	参	数:	szFile:		文件名.
	返回值:	资源类型.
	作	者:	zengzhaofa. 2022.06.08.
	*******************************************************************/
	const char* LibcurlWrapper::ConversionMimeType(const char* FileName)
	{
		std::string src(FileName);
		std::string s;

		if (!src.empty()) {
			int iPos = src.rfind('.');
			if (iPos != std::string::npos) {
				src = src.substr(iPos + 1, src.size() - iPos - 1);
				for (unsigned int i = 0; i < src.size(); ++i) {
					s += tolower(src[i]);
				}

				if (s.compare("bmp") == 0) {
					return "image/bmp";
				}
				else if (s.compare("png") == 0) {
					return "image/png";
				}
			}
		}
		return "";
	}
}