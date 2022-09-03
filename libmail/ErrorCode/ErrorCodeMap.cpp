#include "pch.h"
#include "ErrorCodeMap.h"

namespace SMTPClientNS
{
	//@class
	//功	能:	获取CErrorCodeMap实例对象.
	//参	数:
	//返回值:	CErrorCodeMap对象引用.
	//作	者:	zengzhaofa. 2022.05.16.
	CErrorCodeMap& CErrorCodeMap::GetErrorCodeInstance()
	{
		static CErrorCodeMap ErrorInfoInstance;
		return ErrorInfoInstance;
	}

	/*@class
	*******************************************************************
	功	能:	构造函数.
	参	数:
	返回值:	
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	CErrorCodeMap::CErrorCodeMap()
	{
		GenerateErrorCodeMappingTable();
	}

	/*@class
	*******************************************************************
	功	能:	析构函数.
	参	数:
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	CErrorCodeMap::~CErrorCodeMap()
	{
		m_mapErrorInfo.clear();
	}

	/*@class
	*******************************************************************
	功	能:	从错误码映射表中获取错误信息.
	参	数:	iErrorCode:	libcurl错误码.
	返回值:	错误信息.
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	const char* CErrorCodeMap::GetErrorInfoFromMap(int iErrorCode) const
	{
		auto it = m_mapErrorInfo.find(iErrorCode);
		if (it != m_mapErrorInfo.end()){
			return it->second.second.c_str();
		}

		return m_mapErrorInfo.find(100)->second.second.c_str();
	}

	/*@class
	*******************************************************************
	功	能:	转换成PB错误码.
	参	数:	iErrorCode:	libcurl错误码.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	int CErrorCodeMap::GetErrorCodeFromMap(int iErrorCode) const
	{
		auto it = m_mapErrorInfo.find(iErrorCode);
		if (it != m_mapErrorInfo.end()){
			return it->second.first;
		}

		return -1;
	}

	/*@class
	*******************************************************************
	功	能:	生成错误码映射表.
	参	数:
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void CErrorCodeMap::GenerateErrorCodeMappingTable()
	{
		//InsertErrorInfo(CURLE_OK, 1, IDS_STRING_SUCCESSED);													// 成功
		//InsertErrorInfo(CURLE_COULDNT_RESOLVE_HOST, -6, IDS_STRING_RESOLVE_HOST_ERROR);						// 解析主机失败	
		//InsertErrorInfo(CURLE_AUTH_ERROR, -15, IDS_STRING_AUTH_ERROR);										// 认证失败
		//InsertErrorInfo(CURLE_READ_ERROR, -16, IDS_STRING_READFILE_ERROR);									// 文件路径错误
		//InsertErrorInfo(CURLE_URL_MALFORMAT, -17, IDS_STRING_URL_ERROR);									// URL错误
		//InsertErrorInfo(100, -1, IDS_STRING_GENERIC_ERROR);													// 一般错误
		//InsertErrorInfo(CURLE_FAILED_INIT, -2, IDS_STRING_CONNECT_PROXY_ERROR);								// 连接代理错误
		//InsertErrorInfo(CURLE_COULDNT_RESOLVE_PROXY, -3, IDS_STRING_RESOLVE_PROXY_ERROR);					// 解析代理错误
		//InsertErrorInfo(CURLE_COULDNT_CONNECT, -5, IDS_STRING_CONNECT_ERROR);								// 连接错误
		//InsertErrorInfo(CURLE_LOGIN_DENIED, -12, IDS_STRING_LOGIN_ERROR);									// 密码错误
		//InsertErrorInfo(CURLE_SEND_ERROR, -13, IDS_STRING_SENDER_ERROR);									// 发送错误
		//InsertErrorInfo(CURLE_RECV_ERROR, -14, IDS_STRING_RECIPIENT_ERROR);									// 接收错误
		//InsertErrorInfo(CURLE_UNSUPPORTED_PROTOCOL, -7, IDS_STRING_PROTOCOL_ERROR);
		//InsertErrorInfo(CURLE_SSL_CONNECT_ERROR, -8, IDS_STRING_CERTIFICATE_EXIST_ERROR);
		//InsertErrorInfo(CURLE_PEER_FAILED_VERIFICATION, -9, IDS_STRING_CERTIFICATE_REVOKED_ERROR);
		//InsertErrorInfo(CURLE_FTP_ACCEPT_FAILED, -10, IDS_STRING_CERTIFICATE_AUTHENTICATION_ERROR);
		//InsertErrorInfo(CURLE_OPERATION_TIMEDOUT, -11, IDS_STRING_TIMEOUT_ERROR);
	}

	/*@class
	*******************************************************************
	功	能:	插入错误信息.
	参	数:	iCurlErrorCode:	libcurl错误码.
			iPBErrorCode:	PB错误码.
			nErrorCodeID:	资源ID.
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void CErrorCodeMap::InsertErrorInfo(int iCurlErrorCode, int iPBErrorCode, unsigned int nErrorCodeID)
	{
		//char szbuffer[512] = { 0 };
		//LoadStringA(g_hInstance, nErrorCodeID, szbuffer, sizeof(szbuffer));
		//m_mapErrorInfo[iCurlErrorCode] = make_pair(iPBErrorCode, szbuffer);
	}
}