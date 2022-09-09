#pragma once

namespace libmailNS
{
	// 字符编码类型
	enum class EnCodingType : char
	{
		eASCII = 0,
		eUTF8 = 1
	};

	// 邮件优先级 1（最高），2（高），3（正常），4（低），5（最低）。如果省略该字段，则默认为 3（正常）。
	enum class MailPriority : char
	{
		eMAILPRIORITY_NORMAL = 0,
		eMAILPRIORITY_LOW,
		eMAILPRIORITY_HIGH
	};

	class IMimeMessage
	{
	public:
		IMimeMessage() {}
		virtual ~IMimeMessage() {}

	public:
		 // 重置
		virtual void Reset() = 0;

	public:
		// 接收人
		virtual int AddRecipient(const char* Recipient, const char* alias = nullptr) = 0;
		virtual int GetRecipientsCount() const = 0;
		virtual const char* GetRecipient(unsigned int nIndex, unsigned int nNameIndex = 0) const = 0;
		virtual int ClearAllRecipients() = 0;

		// 抄送人
		virtual int AddCc(const char* CC, const char* alias = nullptr) = 0;
		virtual int GetCcsCount() const = 0;
		virtual const char* GetCc(unsigned int nIndex, unsigned int nNameIndex = 0) const = 0;
		virtual int ClearAllCcs() = 0;

		// 密送人
		virtual int AddBcc(const char* Bcc, const char* alias = nullptr) = 0;
		virtual int GetBccsCount() const = 0;
		virtual const char* GetBcc(unsigned int nIndex, unsigned int nNameIndex = 0) const = 0;
		virtual int ClearAllBccs() = 0;

		// 附件
		virtual int AddAttachment(const char* Attachment) = 0;
		virtual int GetAttachmentsCount() const = 0;
		virtual const char* GetAttachment(unsigned int nIndex) const = 0;
		virtual int ClearAllAttachments() = 0;

		// 链接资源
		virtual int AddLinkedResource(const char* ResourcePath, const char* ContantID) = 0;
		virtual int GetLinkedResourcesCount() const = 0;
		virtual const char* GetLinkedResourceFileName(unsigned int nIndex) const = 0;
		virtual const char* GetLinkedResourceContantID(unsigned int nIndex) const = 0;
		virtual int ClearAllLinkedResources() = 0;

		// 发送人
		virtual int SetSender(const char* Sender, const char* alias = nullptr) = 0;
		virtual const char* GetSender(unsigned int nIndex = 0) const = 0;
		virtual void ClearSender() = 0;

		// 准备出除接口
		virtual void SetMessageBodyFormat(bool bHTML = false) = 0;
		virtual bool GetMessageBodyFormat() const = 0;

		// 优先级
		virtual void SetPriority(unsigned int nPriority = 0) = 0;
		virtual int GetPriority() const = 0;

		// 主题
		virtual void SetSubject(const char* Subject) = 0;
		virtual const char* GetSubject() const = 0;

		// 设置传输编码
		virtual void SetTransferEncoding(unsigned int nEncodeType = 0) = 0;
		virtual int GetTransferEncoding() const = 0;

		// 设置MessageBody HTML
		virtual void SetMessageHtmlBody(const char* Body) = 0;
		virtual const char* GetMessageHtmlBody() const = 0;

		// 设置MessageBody Plain
		virtual void SetMessagePlainBody(const char* Body) = 0;
		virtual const char* GetMessagePlainBody() const = 0;

		// 从文件中设置MessageBody
		virtual void SetMessageBodyFromFile(const char* FileName, int iTextType = 0) = 0;	
	};
}