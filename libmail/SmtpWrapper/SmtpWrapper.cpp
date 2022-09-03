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

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	int CSmtpWrapper::Send()
	{
		return 0;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	long CSmtpWrapper::SendAsync()
	{
		return 0;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	const char* CSmtpWrapper::GetLogInfo() const
	{
		return nullptr;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::GetLogInfoToFile(const char* wszFileName) const
	{
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	const char* CSmtpWrapper::GetLastLogInfo() const
	{
		return nullptr;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	int CSmtpWrapper::GetLastErrorCode() const
	{
		return 0;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
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

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::GetProxyInfo(const char* wszInfo, int iIndex) const
	{

	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetProxy(bool bSetProxy)
	{
		m_bSetProxy = bSetProxy;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	bool CSmtpWrapper::GetProxy() const
	{
		return m_bSetProxy;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetIgnoreServerCert(int dwIgnoreFlag)
	{
		m_iServerCert = dwIgnoreFlag;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	long CSmtpWrapper::GetIgnoreServerCert() const
	{
		return m_iServerCert;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetCheckServerCertRevocation(bool bCheck)
	{
		m_bCheckRevocation = bCheck;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	bool CSmtpWrapper::GetCheckServerCertRevocation() const
	{
		return m_bCheckRevocation;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetEnableTLS(bool bEnable)
	{
		m_bEnableTLS = bEnable;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	bool CSmtpWrapper::GetEnableTLS() const
	{
		return m_bEnableTLS;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetSecureProtocol(int iProtocol)
	{
		m_iProtocolType = iProtocol;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	int CSmtpWrapper::GetSecureProtocol() const
	{
		return m_iProtocolType;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetTimeout(long lTimeout)
	{
		m_lTimeout = lTimeout;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	long CSmtpWrapper::GetTimeout() const
	{
		return m_lTimeout;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetUsername(const char* Username)
	{
		m_strUsername = Username;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	const char* CSmtpWrapper::GetUsername() const
	{
		return m_strUsername.c_str();
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetPassword(const char* Password)
	{
		m_strPassword = Password;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	const char* CSmtpWrapper::GetPassword() const
	{
		return m_strPassword.c_str();
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetHost(const char* Host)
	{
		m_strHost = Host;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	const char* CSmtpWrapper::GetHost() const
	{
		return m_strHost.c_str();
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	void CSmtpWrapper::SetPort(int iPort)
	{
		m_iPort = iPort;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	int CSmtpWrapper::GetPort() const
	{
		return m_iPort;
	}

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
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

	/*@class
	*******************************************************************
	��	�� :	.
	��	��:	zengzhaofa.
	*******************************************************************/
	//std::shared_ptr<IMimeMessage*> CSmtpWrapper::GetMimeMessage() const
	//{
	//	return m_spMimeMessage;
	//}
}