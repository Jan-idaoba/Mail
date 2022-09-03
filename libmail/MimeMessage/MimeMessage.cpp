#include "pch.h"
#include "MimeMessage.h"
#include <fstream>

namespace libmailNS
{
	CMimeMessage::CMimeMessage()
		: m_bhtml(false)
		, m_iPriority(0)
		, m_enumEncodingType(EnCodingType::eASCII)
	{
	}

	CMimeMessage::~CMimeMessage()
	{
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::Reset()
	{
		m_bhtml = false;
		m_iPriority = 0;
		m_enumEncodingType = EnCodingType::eASCII;
		m_strSubject.clear();
		m_strHTMLBody.clear();
		m_strPlainTextBody.clear();
		m_pairSender = std::make_pair<std::string, std::string>("", "");
		m_vecRecipients.clear();
		m_vecCCs.clear();
		m_vecBccs.clear();
		m_vecAttachments.clear();
		m_vecResources.clear();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::Release()
	{

	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	IMimeMessage* CMimeMessage::CreateMessageInstance()
	{
		return new CMimeMessage();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::AddRecipient(const char* Recipient, const char* alias)
	{
		auto iRet = -1;
		decltype(m_pairSender) recipient;

		if (Recipient && strlen(Recipient)) {
			get<0>(recipient) = Recipient;
			if (alias && strlen(alias)) {
				get<1>(recipient) = alias;
			}
			m_vecRecipients.push_back(recipient);
			iRet = m_vecRecipients.size();
		}
		return iRet;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetRecipientsCount() const
	{
		return m_vecRecipients.size();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetRecipient(unsigned int nIndex, unsigned int nNameIndex) const
	{
		if (nIndex > 0 && nIndex <= m_vecRecipients.size()) {
			if (nNameIndex) {
				return get<1>(m_vecRecipients[nIndex - 1]).c_str();
			}
			else {
				return get<0>(m_vecRecipients[nIndex - 1]).c_str();
			}
		}
		return "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::ClearAllRecipients()
	{
		int iCount = m_vecRecipients.size();
		m_vecRecipients.clear();
		return iCount;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::AddCc(const char* CC, const char* alias)
	{
		auto iRet = -1;
		decltype(m_pairSender) pairCC;

		if (CC && strlen(CC)) {
			get<0>(pairCC) = CC;
			if (alias && strlen(alias)) {
				get<1>(pairCC) = alias;
			}
			m_vecCCs.push_back(pairCC);
			iRet = m_vecCCs.size();
		}
		return iRet;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetCcsCount() const
	{
		return m_vecCCs.size();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetCc(unsigned int nIndex, unsigned int nNameIndex) const
	{
		if (nIndex > 0 && nIndex <= m_vecCCs.size()) {
			if (nNameIndex) {
				return get<1>(m_vecCCs[nIndex - 1]).c_str();
			}
			else {
				return get<0>(m_vecCCs[nIndex - 1]).c_str();
			}
		}
		return "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::ClearAllCcs()
	{
		int iCount = m_vecCCs.size();
		m_vecCCs.clear();
		return iCount;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::AddBcc(const char* Bcc, const char* alias)
	{
		auto iRet = -1;
		decltype(m_pairSender) pairBcc;

		if (Bcc && strlen(Bcc)) {
			get<0>(pairBcc) = Bcc;
			if (alias && strlen(alias)) {
				get<1>(pairBcc) = alias;
			}
			m_vecBccs.push_back(pairBcc);
			iRet = m_vecBccs.size();
		}
		return iRet;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetBccsCount() const
	{
		return m_vecBccs.size();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetBcc(unsigned int nIndex, unsigned int nNameIndex) const
	{
		if (nIndex > 0 && nIndex <= m_vecBccs.size()) {
			if (nNameIndex) {
				return get<1>(m_vecBccs[nIndex - 1]).c_str();
			}
			else {
				return get<0>(m_vecBccs[nIndex - 1]).c_str();
			}
		}
		return "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::ClearAllBccs()
	{
		int iCount = m_vecBccs.size();
		m_vecBccs.clear();
		return iCount;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::AddAttachment(const char* Attachment)
	{
		auto iRet = -1;
		if (!Attachment || strlen(Attachment) == 0) {
			return iRet;
		}

		std::ifstream ifs(Attachment);
		if (!ifs.good())
			return iRet;

		m_vecAttachments.push_back(Attachment);
		iRet = m_vecAttachments.size();
		return iRet;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetAttachmentsCount() const
	{
		return m_vecAttachments.size();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetAttachment(unsigned int nIndex) const
	{
		return nIndex > 0 && nIndex <= m_vecAttachments.size() ? m_vecAttachments[nIndex - 1].c_str() : "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::ClearAllAttachments()
	{
		int iCount = m_vecAttachments.size();
		m_vecAttachments.clear();
		return iCount;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::AddLinkedResource(const char* ResourcePath, const char* ContantID)
	{
		auto iRet = -1;
		if (!ResourcePath
			|| strlen(ResourcePath) == 0
			|| !ContantID
			|| strlen(ContantID) == 0)
		{
			return iRet;
		}

		std::ifstream ifs(ResourcePath);
		if (!ifs.good())
			return iRet;

		decltype(m_pairSender) pairResource;
		get<0>(m_pairSender) = ResourcePath;
		get<1>(m_pairSender) = ContantID;
		m_vecResources.push_back(pairResource);
		iRet = m_vecResources.size();
		return iRet;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetLinkedResourcesCount() const
	{
		return m_vecResources.size();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetLinkedResourceFileName(unsigned int nIndex) const
	{
		return nIndex > 0 && nIndex <= m_vecResources.size() ? get<0>(m_vecResources[nIndex - 1]).c_str() : "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetLinkedResourceContantID(unsigned int nIndex) const
	{
		return nIndex > 0 && nIndex <= m_vecResources.size() ? get<1>(m_vecResources[nIndex - 1]).c_str() : "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::ClearAllLinkedResources()
	{
		int iCount = m_vecResources.size();
		m_vecResources.clear();
		return iCount;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::SetSender(const char* Sender, const char* alias)
	{
		auto iRet = -1;
		if (Sender && strlen(Sender)) {
			get<0>(m_pairSender) = Sender;
			if (alias && strlen(alias)) {
				get<1>(m_pairSender) = alias;
			}
			iRet = 1;
		}
		return iRet;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetSender(unsigned int nIndex) const
	{
		if (nIndex) {
			return (get<1>(m_pairSender)).c_str();
		}
		else {
			return (get<0>(m_pairSender)).c_str();
		}
		return "";
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::ClearSender()
	{
		m_pairSender = std::make_pair("", "");
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::SetMessageBodyFormat(bool bHTML)
	{
		m_bhtml = bHTML;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	bool CMimeMessage::GetMessageBodyFormat() const
	{
		return m_bhtml;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::SetPriority(unsigned int nPriority)
	{
		m_iPriority = nPriority;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetPriority() const
	{
		return m_iPriority;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::SetSubject(const char* Subject)
	{
		m_strSubject = Subject;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetSubject() const
	{
		return m_strSubject.c_str();
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::SetTransferEncoding(unsigned int nEncodeType)
	{
		if (nEncodeType == 0) {
			m_enumEncodingType = EnCodingType::eASCII;
		}
		else if (nEncodeType == 1) {
			m_enumEncodingType = EnCodingType::eUTF8;
		}
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	int CMimeMessage::GetTransferEncoding() const
	{
		if (m_enumEncodingType == EnCodingType::eASCII) {
			return 0;
		}
		else if (m_enumEncodingType == EnCodingType::eUTF8) {
			return 1;
		}
		return 0;
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::SetMessageBody(const char* Body, unsigned int nBodyType)
	{
		if (nBodyType) {
			m_strPlainTextBody = Body;
		}
		else {
			m_strHTMLBody = Body;
		}
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	void CMimeMessage::SetMessageBodyFromFile(const char* FileName, int iTextType)
	{
		unsigned char* pData = nullptr;
		DWORD dwCount = 0;
		//if (CommonFunction::GetFileInfo(FileName, pData, dwCount)) {
		//	if (iTextType == 0) {
		//		CommonFunction::MultiByte2WideChar((char*)pData, m_wstrPlainTextBody, EnCodingType::eASCII);
		//	}
		//	else if (iTextType == 1) {
		//		CommonFunction::MultiByte2WideChar((char*)pData, m_wstrPlainTextBody, EnCodingType::eUTF8);
		//	}
		//	else if (iTextType == 2) {
		//		CommonFunction::MultiByte2WideChar((char*)pData, m_wstrHTMLBody, EnCodingType::eASCII);
		//	}
		//	else if (iTextType == 3) {
		//		CommonFunction::MultiByte2WideChar((char*)pData, m_wstrHTMLBody, EnCodingType::eUTF8);
		//	}
		//	else if (iTextType == 4) {
		//		CommonFunction::MultiByte2WideChar((char*)pData, m_wstrHTMLBody, EnCodingType::eASCII);
		//		CommonFunction::ParseHTMLResource(this);
		//	}
		//	else if (iTextType == 5) {
		//		CommonFunction::MultiByte2WideChar((char*)pData, m_wstrHTMLBody, EnCodingType::eUTF8);
		//		CommonFunction::ParseHTMLResource(this);
		//	}
		//}
	}

	/*@class
	*******************************************************************
	功	能 :	.
	作	者:	zengzhaofa.
	*******************************************************************/
	const char* CMimeMessage::GetMessageBody(int iTextType) const
	{
		if (iTextType) {
			return m_strHTMLBody.c_str();
		}
		else {
			return m_strPlainTextBody.c_str();
		}
	}
}
