
namespace libmailNS
{
	using ProxyInfo = std::tuple<std::string, int, int, std::string, std::string>;
	// 代理类型;
	enum class SmtpProxyType : char
	{
		SMTP_PROXY_4 = 0,
		SMTP_PROXY_4A = 1,
		SMTP_PROXY_5 = 2,
		SMTP_PROXY_5A = 3
	};

	// 安全连接协议;
	enum class SmtpSSLVer : char
	{
		SMTP_SSLVERSION_DEFAULT = 0, // libcurl默认可接受范围版本，最低TLSv1.0
		SMTP_SSLVERSION_TLS_1_0,     // TLSv1.0版本
		SMTP_SSLVERSION_TLS_1_1,     // TLSv1.1版本
		SMTP_SSLVERSION_TLS_1_2,     // TLSv1.2版本
		SMTP_SSLVERSION_TLS_1_3      // TLSv1.3版本
	};

	// 证书校验标志
	enum class SecurityIgnoreFlag
	{
		IGNORE_SERVER_CERT = 0x00,
		IGNORE_UNKNOWN_CA = 0x01,
		IGNORE_CERT_DATE_INVALID = 0x02,
		IGNORE_CERT_CN_INVALID = 0x04,
		IGNORE_CERT_WRONG_USAGE = 0x08
	};


	class IMimeMessage;
	class ISmtpWrapper
	{
	public:
		ISmtpWrapper() {}
		virtual ~ISmtpWrapper() {}

	public:
		virtual int Send() = 0;
		virtual long SendAsync() = 0;

		virtual const char* GetLogInfo() const = 0;
		virtual void GetLogInfoToFile(const char* FileName) const = 0;
		virtual const char* GetLastLogInfo() const = 0;
		virtual int GetLastErrorCode() const = 0;

		virtual int SetProxyInfo(const char* host, int iport, int iProxyType = 2,
			const char* Username = nullptr, const char* Password = nullptr) = 0;
		virtual void GetProxyInfo(const char* ProxyInfo, int iIndex = 0) const = 0;

		virtual void SetProxy(bool bSetProxy) = 0;
		virtual bool GetProxy() const = 0;

		virtual void SetIgnoreServerCert(int dwIgnoreFlag /*= IGNORE_SERVER_CERT*/) = 0;
		virtual long GetIgnoreServerCert() const = 0;

		virtual void SetCheckServerCertRevocation(bool bCheck = false) = 0;
		virtual bool GetCheckServerCertRevocation() const = 0;

		virtual void SetEnableTLS(bool bEnable = true) = 0;
		virtual bool GetEnableTLS() const = 0;

		virtual void SetSecureProtocol(int iProtocol = 0) = 0;
		virtual int GetSecureProtocol() const = 0;

		virtual void SetTimeout(long lTimeout = 0) = 0;
		virtual long GetTimeout() const = 0;

		virtual void SetUsername(const char* Username) = 0;
		virtual const char* GetUsername() const = 0;

		virtual void SetPassword(const char* Password) = 0;
		virtual const char* GetPassword() const = 0;

		virtual void SetHost(const char* Host) = 0;
		virtual const char* GetHost() const = 0;

		virtual void SetPort(int iPort) = 0;
		virtual int GetPort() const = 0;

	public:
		virtual void SetMimeMessage(const IMimeMessage* spMessage) = 0;
		virtual IMimeMessage* GetMimeMessage() const = 0;
	};
}