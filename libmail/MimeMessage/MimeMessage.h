#pragma once
#include "IMimeMessage.h"

namespace libmailNS
{
	class CMimeMessage : public IMimeMessage
	{
	public:
		CMimeMessage();
		~CMimeMessage() override;

	public:
		void Reset() override;
		void Release() override;
		static IMimeMessage* CreateMessageInstance();

	public:
		int AddRecipient(const char* Recipient, const char* alias = nullptr) override final;
		int GetRecipientsCount() const override;
		const char* GetRecipient(unsigned int nIndex, unsigned int nNameIndex = 0) const override final;
		int ClearAllRecipients() override final;

		int AddCc(const char* CC, const char* alias = nullptr) override final;
		int GetCcsCount() const override final;
		const char* GetCc(unsigned int nIndex, unsigned int nNameIndex = 0) const override final;
		int ClearAllCcs() override final;

		int AddBcc(const char* Bcc, const char* alias = nullptr) override final;
		int GetBccsCount() const override final;
		const char* GetBcc(unsigned int nIndex, unsigned int nNameIndex = 0) const override final;
		int ClearAllBccs() override final;

		int AddAttachment(const char* Attachment) override final;
		int GetAttachmentsCount() const override final;
		const char* GetAttachment(unsigned int nIndex) const override final;
		int ClearAllAttachments() override final;

		int AddLinkedResource(const char* ResourcePath, const char* ContantID) override final;
		int GetLinkedResourcesCount() const override final;
		const char* GetLinkedResourceFileName(unsigned int nIndex) const override final;
		const char* GetLinkedResourceContantID(unsigned int nIndex) const override final;
		int ClearAllLinkedResources() override final;

		int SetSender(const char* Sender, const char* alias = nullptr) override final;
		const char* GetSender(unsigned int nIndex = 0) const override final;
		void ClearSender() override final;

		void SetMessageBodyFormat(bool bHTML = false) override final;
		bool GetMessageBodyFormat() const override final;

		void SetPriority(unsigned int nPriority = 0) override final;
		int GetPriority() const override final;

		void SetSubject(const char* Subject) override final;
		const char* GetSubject() const override final;

		void SetTransferEncoding(unsigned int nEncodeType = 0);
		int GetTransferEncoding() const override final;

		void SetMessageBody(const char* Body, unsigned int nBodyType/*0:PlainText 1:HTML*/) override final;
		void SetMessageBodyFromFile(const char* FileName, int iTextType) override final;
		const char* GetMessageBody(int iTextType/*0:PlainText 1:HTML*/) const override final;

	private:
		bool													m_bhtml;
		int														m_iPriority;
		EnCodingType											m_enumEncodingType;
		std::string												m_strSubject;
		std::string												m_strHTMLBody;
		std::string												m_strPlainTextBody;
		std::pair<std::string, std::string>						m_pairSender;
		std::vector<std::pair<std::string, std::string>>		m_vecRecipients;
		std::vector<std::pair<std::string, std::string>>		m_vecCCs;
		std::vector<std::pair<std::string, std::string>>		m_vecBccs;
		std::vector<std::string>								m_vecAttachments;
		std::vector<std::pair<std::string, std::string>>		m_vecResources;
	};
}
