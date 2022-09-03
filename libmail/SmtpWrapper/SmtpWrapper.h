#include "ISmtpWrapper.h"

namespace libmailNS
{
	class CSmtpWrapper : public ISmtpWrapper
	{
	public:
		CSmtpWrapper();
		~CSmtpWrapper();

	public:
		static ISmtpWrapper* CreateSmtpClientInstance();

	public:
		int Send() override final;
		long SendAsync() override final;

		const char* GetLogInfo() const override final;
		void GetLogInfoToFile(const char* FileName) const override final;
		const char* GetLastLogInfo() const override final;
		int GetLastErrorCode() const override final;

		int SetProxyInfo(const char* host, int iport, int iProxyType = 2,
		const char* Username = nullptr, const char* Password = nullptr) override final;
		void GetProxyInfo(const char* wszInfo, int iIndex = 0) const override final;

		void SetProxy(bool bSetProxy) override final;
		bool GetProxy() const override final;

		void SetIgnoreServerCert(int dwIgnoreFlag /*= IGNORE_SERVER_CERT*/) override final;
		long GetIgnoreServerCert() const override final;

		void SetCheckServerCertRevocation(bool bCheck = false) override final;
		bool GetCheckServerCertRevocation() const override final;

		void SetEnableTLS(bool bEnable = true) override final;
		bool GetEnableTLS() const override final;

		void SetSecureProtocol(int iProtocol = 0) override final;
		int GetSecureProtocol() const override final;

		void SetTimeout(long lTimeout = 0) override final;
		long GetTimeout() const override final;

		void SetUsername(const char* Username) override final;
		const char* GetUsername() const override final;

		void SetPassword(const char* Password) override final;
		const char* GetPassword() const override final;

		void SetHost(const char* Host) override final;
		const char* GetHost() const override final;

		void SetPort(int iPort) override final;
		int GetPort() const override final;

	public:
		//void SetMimeMessage(const std::shared_ptr<IMimeMessage*> spMessage) override final;
		//std::shared_ptr<IMimeMessage*> GetMimeMessage() const override final;

		virtual void SetMimeMessage(const IMimeMessage* spMessage);
		virtual IMimeMessage* GetMimeMessage() const;
	private:
		IMimeMessage*						m_spMimeMessage;
	
	private:
		bool								m_bCheckRevocation;
		bool								m_bSetProxy;
		bool								m_bEnableTLS;
		int									m_iProtocolType;
		int									m_iPort;
		int									m_iServerCert;
		int									m_iErrorCode;
		long								m_lTimeout;
		std::string							m_strUsername;
		std::string							m_strPassword;
		std::string							m_strHost;
		std::string							m_strLog;
		std::string							m_strLogFileName;
		ProxyInfo							m_tupProxyInfo;
		std::queue<std::string>				m_fullLogInfo;
		std::queue<std::string>				m_fileLogInfo;
	};
}