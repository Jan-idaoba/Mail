#include "pch.h"
#include "ErrorCodeMap.h"

namespace SMTPClientNS
{
	//@class
	//��	��:	��ȡCErrorCodeMapʵ������.
	//��	��:
	//����ֵ:	CErrorCodeMap��������.
	//��	��:	zengzhaofa. 2022.05.16.
	CErrorCodeMap& CErrorCodeMap::GetErrorCodeInstance()
	{
		static CErrorCodeMap ErrorInfoInstance;
		return ErrorInfoInstance;
	}

	/*@class
	*******************************************************************
	��	��:	���캯��.
	��	��:
	����ֵ:	
	��	��:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	CErrorCodeMap::CErrorCodeMap()
	{
		GenerateErrorCodeMappingTable();
	}

	/*@class
	*******************************************************************
	��	��:	��������.
	��	��:
	����ֵ:
	��	��:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	CErrorCodeMap::~CErrorCodeMap()
	{
		m_mapErrorInfo.clear();
	}

	/*@class
	*******************************************************************
	��	��:	�Ӵ�����ӳ����л�ȡ������Ϣ.
	��	��:	iErrorCode:	libcurl������.
	����ֵ:	������Ϣ.
	��	��:	zengzhaofa. 2022.05.16.
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
	��	��:	ת����PB������.
	��	��:	iErrorCode:	libcurl������.
	����ֵ:
	��	��:	zengzhaofa. 2022.05.16.
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
	��	��:	���ɴ�����ӳ���.
	��	��:
	����ֵ:
	��	��:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void CErrorCodeMap::GenerateErrorCodeMappingTable()
	{
		//InsertErrorInfo(CURLE_OK, 1, IDS_STRING_SUCCESSED);													// �ɹ�
		//InsertErrorInfo(CURLE_COULDNT_RESOLVE_HOST, -6, IDS_STRING_RESOLVE_HOST_ERROR);						// ��������ʧ��	
		//InsertErrorInfo(CURLE_AUTH_ERROR, -15, IDS_STRING_AUTH_ERROR);										// ��֤ʧ��
		//InsertErrorInfo(CURLE_READ_ERROR, -16, IDS_STRING_READFILE_ERROR);									// �ļ�·������
		//InsertErrorInfo(CURLE_URL_MALFORMAT, -17, IDS_STRING_URL_ERROR);									// URL����
		//InsertErrorInfo(100, -1, IDS_STRING_GENERIC_ERROR);													// һ�����
		//InsertErrorInfo(CURLE_FAILED_INIT, -2, IDS_STRING_CONNECT_PROXY_ERROR);								// ���Ӵ������
		//InsertErrorInfo(CURLE_COULDNT_RESOLVE_PROXY, -3, IDS_STRING_RESOLVE_PROXY_ERROR);					// �����������
		//InsertErrorInfo(CURLE_COULDNT_CONNECT, -5, IDS_STRING_CONNECT_ERROR);								// ���Ӵ���
		//InsertErrorInfo(CURLE_LOGIN_DENIED, -12, IDS_STRING_LOGIN_ERROR);									// �������
		//InsertErrorInfo(CURLE_SEND_ERROR, -13, IDS_STRING_SENDER_ERROR);									// ���ʹ���
		//InsertErrorInfo(CURLE_RECV_ERROR, -14, IDS_STRING_RECIPIENT_ERROR);									// ���մ���
		//InsertErrorInfo(CURLE_UNSUPPORTED_PROTOCOL, -7, IDS_STRING_PROTOCOL_ERROR);
		//InsertErrorInfo(CURLE_SSL_CONNECT_ERROR, -8, IDS_STRING_CERTIFICATE_EXIST_ERROR);
		//InsertErrorInfo(CURLE_PEER_FAILED_VERIFICATION, -9, IDS_STRING_CERTIFICATE_REVOKED_ERROR);
		//InsertErrorInfo(CURLE_FTP_ACCEPT_FAILED, -10, IDS_STRING_CERTIFICATE_AUTHENTICATION_ERROR);
		//InsertErrorInfo(CURLE_OPERATION_TIMEDOUT, -11, IDS_STRING_TIMEOUT_ERROR);
	}

	/*@class
	*******************************************************************
	��	��:	���������Ϣ.
	��	��:	iCurlErrorCode:	libcurl������.
			iPBErrorCode:	PB������.
			nErrorCodeID:	��ԴID.
	����ֵ:
	��	��:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	void CErrorCodeMap::InsertErrorInfo(int iCurlErrorCode, int iPBErrorCode, unsigned int nErrorCodeID)
	{
		//char szbuffer[512] = { 0 };
		//LoadStringA(g_hInstance, nErrorCodeID, szbuffer, sizeof(szbuffer));
		//m_mapErrorInfo[iCurlErrorCode] = make_pair(iPBErrorCode, szbuffer);
	}
}