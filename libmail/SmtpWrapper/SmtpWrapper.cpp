#include "pch.h"
#include "SmtpWrapper.h"

namespace libmailNS
{
	CSmtpWrapper::CSmtpWrapper()
		: m_bCheckRevocation(false)
		, m_bSetProxy(false)
		, m_bEnableTLS(true)
		, m_iProtocolType(0)
		, m_iPort(-1)
		, m_iServerCert(0)
		, m_iErrorCode(-1)
		, m_lTimeout(0)
		, m_spMimeMessage(nullptr)
	{
	}

	CSmtpWrapper::~CSmtpWrapper()
	{ 

	}

	ISmtpWrapper* CSmtpWrapper::CreateSmtpClientInstance()
	{
		return new CSmtpWrapper();
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	int CSmtpWrapper::Send()
	{
		return 0;
	}

	//@func
	//��	��:	.
	//����:	zengzhaofa.
	long CSmtpWrapper::SendAsync()
	{
		return 0;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	const char* CSmtpWrapper::GetLogInfo() const
	{
		return nullptr;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	///
	void CSmtpWrapper::GetLogInfoToFile(const char* wszFileName) const
	{
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	const char* CSmtpWrapper::GetLastLogInfo() const
	{
		return nullptr;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	int CSmtpWrapper::GetLastErrorCode() const
	{
		return 0;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	int CSmtpWrapper::SetProxyInfo(const char* host, int iport, int iProxyType, const char* Username, const char* Password)
	{
		auto ret = 0;
		if (host && strlen(host)) {
			m_bSetProxy = true;
			get<0>(m_tupProxyInfo) = host;
			get<1>(m_tupProxyInfo) = iport;
			get<2>(m_tupProxyInfo) = iProxyType;
			if (Username && Password) {
				if (strlen(Username) && strlen(Password)) {
					get<3>(m_tupProxyInfo) = Username;
					get<4>(m_tupProxyInfo) = Password;
				}
			}
			ret = 1;
		}
		return ret;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::GetProxyInfo(const char* wszInfo, int iIndex) const
	{

	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetProxy(bool bSetProxy)
	{
		m_bSetProxy = bSetProxy;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	bool CSmtpWrapper::GetProxy() const
	{
		return m_bSetProxy;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetIgnoreServerCert(int dwIgnoreFlag)
	{
		m_iServerCert = dwIgnoreFlag;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	long CSmtpWrapper::GetIgnoreServerCert() const
	{
		return m_iServerCert;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetCheckServerCertRevocation(bool bCheck)
	{
		m_bCheckRevocation = bCheck;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	bool CSmtpWrapper::GetCheckServerCertRevocation() const
	{
		return m_bCheckRevocation;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetEnableTLS(bool bEnable)
	{
		m_bEnableTLS = bEnable;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	bool CSmtpWrapper::GetEnableTLS() const
	{
		return m_bEnableTLS;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetSecureProtocol(int iProtocol)
	{
		m_iProtocolType = iProtocol;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	int CSmtpWrapper::GetSecureProtocol() const
	{
		return m_iProtocolType;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetTimeout(long lTimeout)
	{
		m_lTimeout = lTimeout;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	long CSmtpWrapper::GetTimeout() const
	{
		return m_lTimeout;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetUsername(const char* Username)
	{
		m_strUsername = Username;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	const char* CSmtpWrapper::GetUsername() const
	{
		return m_strUsername.c_str();
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetPassword(const char* Password)
	{
		m_strPassword = Password;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	const char* CSmtpWrapper::GetPassword() const
	{
		return m_strPassword.c_str();
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetHost(const char* Host)
	{
		m_strHost = Host;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	const char* CSmtpWrapper::GetHost() const
	{
		return m_strHost.c_str();
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	void CSmtpWrapper::SetPort(int iPort)
	{
		m_iPort = iPort;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	int CSmtpWrapper::GetPort() const
	{
		return m_iPort;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	//void CSmtpWrapper::SetMimeMessage(const std::shared_ptr<IMimeMessage*> spMessage)
	//{
	//	m_spMimeMessage = spMessage;
	//}

	void CSmtpWrapper::SetMimeMessage(const IMimeMessage* spMessage)
	{

	}

	IMimeMessage* CSmtpWrapper::GetMimeMessage() const
	{
		return nullptr;
	}

	//@func
	//��	��:	.
	//��	��:	zengzhaofa.
	//std::shared_ptr<IMimeMessage*> CSmtpWrapper::GetMimeMessage() const
	//{
	//	return m_spMimeMessage;
	//}
}