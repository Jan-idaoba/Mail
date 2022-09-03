#include "pch.h"
#include "SmtpLog.h"

namespace SMTPClientNS
{
	//string CSmtpLog::m_strSingleLog;
	//queue<string> CSmtpLog::m_queueFullLog;
	//string CSmtpLog::m_strFileSingleLog;
	//queue<string> CSmtpLog::m_queueFileFullLog;
	//unsigned int CSmtpLog::m_nCount = 0;
	/*@class
	*******************************************************************
	功	能:	获取日志对象实例.
	参	数:	
	返回值:	日志对象引用.
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	SMTPClientNS::CSmtpLog& CSmtpLog::GetLogInstance()
	{
		static CSmtpLog LogInstance;
		return LogInstance;
	}

	/*@class
	*******************************************************************
	功	能:	构造函数.
	参	数:
	返回值:
	作	者:	zengzhaofa. 2022.05.16.	
	*******************************************************************/
	//CSmtpLog::CSmtpLog()
	//{

	//}

	///*@class
	//*******************************************************************
	//功	能:	析构函数.
	//参	数:
	//返回值:
	//作	者:	zengzhaofa. 2022.05.16.	
	//*******************************************************************/
	//CSmtpLog::~CSmtpLog()
	//{

	//}

	/*@class
	*******************************************************************
	功	能:	日志trace回调函数.
	参	数:	handle:	curl对象指针.
			type:	日志类型.
			data:	字符指针.
			size:	字符长度.
			userp:
	返回值:
	作	者:	zengzhaofa. 2022.05.16.
	*******************************************************************/
	//int CSmtpLog::TraceCallBack(CURL* handle, curl_infotype type, char* data, size_t size, void* userp)
	//{
	//	struct data* config = (struct data*)userp;
	//	const char* text;
	//	(void)handle; /* prevent compiler warning */
	//	m_strSingleLog.clear();
	//	m_strFileSingleLog.clear();

	//	switch (type) {
	//		case CURLINFO_TEXT:
	//		{
	//			m_strSingleLog.append("== Info: ");
	//			m_strFileSingleLog.append("== Info: ");
	//			fprintf(stderr, "== Info: %s", data);
	//			m_strSingleLog.append(data);
	//			m_strFileSingleLog.append(data);
	//			m_queueFullLog.push(m_strSingleLog);
	//			m_queueFileFullLog.push(m_strFileSingleLog);
	//		}
	//		/* FALLTHROUGH */
	//		default: /* in case a new one is introduced to shock us */
	//			return 0;

	//		case CURLINFO_HEADER_OUT:
	//			text = "=> Send header";
	//			break;
	//		case CURLINFO_DATA_OUT:
	//			m_nCount++;
	//			text = "=> Send data";
	//			break;
	//		case CURLINFO_SSL_DATA_OUT:
	//			text = "=> Send SSL data";
	//			break;
	//		case CURLINFO_HEADER_IN:
	//			text = "<= Recv header";
	//			break;
	//		case CURLINFO_DATA_IN:
	//			text = "<= Recv data";
	//			break;
	//		case CURLINFO_SSL_DATA_IN:
	//			text = "<= Recv SSL data";
	//			break;
	//	}

	//	DumpCallBack(text, stderr, (unsigned char*)data, size, config->trace_ascii);
	//	return 0;
	//}

	///*@class
	//*******************************************************************
	//功	能:	日志详细信息.
	//参	数:	text:	信息头.
	//		stream:	文件流对象.
	//		ptr:	字符指针.
	//		size:	长度.
	//		nohex:
	//返回值:
	//作	者:	zengzhaofa. 2022.05.16.
	//*******************************************************************/
	//void CSmtpLog::DumpCallBack(const char* text, FILE* stream, unsigned char* ptr, size_t size, char nohex)
	//{
	//	size_t i;
	//	size_t c;
	//	char szBuffer[256] = { 0 };
	//	unsigned int width = 0x10;

	//	if (nohex)
	//		/* without the hex output, we can fit more on screen */
	//		width = 0x40;

	//	sprintf_s(szBuffer, sizeof(szBuffer), "%s, %10.10lu bytes (0x%8.8lx)\n", text, (unsigned long)size, (unsigned long)size);
	//	if (m_nCount != 1 && strcmp(text, "=> Send data"))
	//	{
	//		m_strFileSingleLog.append(szBuffer);
	//	}
	//	m_strSingleLog.append(szBuffer);


	//	for (i = 0; i < size; i += width) {
	//		szBuffer[0] = '\0';
	//		sprintf_s(szBuffer, sizeof(szBuffer), "%4.4lx: ", (unsigned long)i);
	//		if (m_nCount != 1 && strcmp(text, "=> Send data"))
	//		{
	//			m_strFileSingleLog.append(szBuffer);
	//		}
	//		m_strSingleLog.append(szBuffer);


	//		if (!nohex) {
	//			/* hex not disabled, show it */
	//			for (c = 0; c < width; c++)
	//			{
	//				if (i + c < size)
	//				{
	//					szBuffer[0] = '\0';
	//					sprintf_s(szBuffer, sizeof(szBuffer), "%02x ", ptr[i + c]);
	//					if (m_nCount != 1 && strcmp(text, "=> Send data"))
	//					{
	//						m_strFileSingleLog.append(szBuffer);
	//					}
	//					m_strSingleLog.append(szBuffer);

	//				}
	//				else
	//				{
	//					szBuffer[0] = '\0';
	//					sprintf_s(szBuffer, sizeof(szBuffer), "    ");
	//					if (m_nCount != 1 && strcmp(text, "=> Send data"))
	//					{
	//						m_strFileSingleLog.append(szBuffer);
	//					}
	//					m_strSingleLog.append(szBuffer);
	//				}
	//			}
	//		}

	//		for (c = 0; (c < width) && (i + c < size); c++) {
	//			/* check for 0D0A; if found, skip past and start a new line of output */
	//			if (nohex && (i + c + 1 < size) && ptr[i + c] == 0x0D &&
	//				ptr[i + c + 1] == 0x0A) {
	//				i += (c + 2 - width);
	//				break;
	//			}
	//			szBuffer[0] = '\0';
	//			sprintf_s(szBuffer, sizeof(szBuffer), "%c", (ptr[i + c] >= 0x20) && (ptr[i + c] < 0x80) ? ptr[i + c] : '.');
	//			if (m_nCount != 1 && strcmp(text, "=> Send data"))
	//			{
	//				m_strFileSingleLog.append(szBuffer);
	//			}
	//			m_strSingleLog.append(szBuffer);

	//			/* check again for 0D0A, to avoid an extra \n if it's at width */
	//			if (nohex && (i + c + 2 < size) && ptr[i + c + 1] == 0x0D &&
	//				ptr[i + c + 2] == 0x0A) {
	//				i += (c + 3 - width);
	//				break;
	//			}
	//		}

	//		if (m_nCount != 1 && strcmp(text, "=> Send data"))
	//		{
	//			/* newline */
	//			m_strFileSingleLog.append("\n");
	//		}
	//		m_strSingleLog.append("\n");
	//	}
	//	m_queueFullLog.push(m_strSingleLog);
	//	m_queueFileFullLog.push(m_strFileSingleLog);
	//}

	///*@class
	//*******************************************************************
	//功	能:	清除日志信息.
	//参	数:
	//返回值:	
	//作	者:	zengzhaofa. 2022.05.16.
	//*******************************************************************/
	//void CSmtpLog::ClearLogInfo()
	//{
	//	m_nCount = 0;
	//	while (!m_queueFullLog.empty())
	//	{
	//		m_queueFullLog.pop();
	//	}
	//	while (!m_queueFileFullLog.empty())
	//	{
	//		m_queueFileFullLog.pop();
	//	}
	//	m_strSingleLog.clear();
	//	m_strFileSingleLog.clear();
	//}

	///*@class
	//*******************************************************************
	//功	能:	将最后的日志信息压进队列.
	//参	数:	iErrorCode:	libcurl错误码.
	//返回值:
	//作	者:	zengzhaofa. 2022.05.16.
	//*******************************************************************/
	//void CSmtpLog::SetLastLogInfo(int& iErrorCode)
	//{
	//	string strbuffer;
	//	if (iErrorCode == 0)
	//	{
	//		strbuffer = CErrorCodeMap::GetErrorCodeInstance().GetErrorInfoFromMap(iErrorCode);
	//		iErrorCode = CErrorCodeMap::GetErrorCodeInstance().GetErrorCodeFromMap(iErrorCode);
	//		m_strSingleLog.append("Info: ");
	//		m_strSingleLog.append(strbuffer);
	//		m_strFileSingleLog.append("Info: ");
	//		m_strFileSingleLog.append(strbuffer);
	//	}
	//	else
	//	{
	//		strbuffer = CErrorCodeMap::GetErrorCodeInstance().GetErrorInfoFromMap(iErrorCode);
	//		iErrorCode = CErrorCodeMap::GetErrorCodeInstance().GetErrorCodeFromMap(iErrorCode);
	//		m_strSingleLog.append("Error Info: ");
	//		m_strSingleLog.append(strbuffer);
	//		m_strFileSingleLog.append("Error Info: ");
	//		m_strFileSingleLog.append(strbuffer);
	//	}
	//	m_queueFullLog.push(m_strSingleLog);
	//	m_queueFileFullLog.push(m_strFileSingleLog);
	//}

	///*@class
	//*******************************************************************
	//功	能:	获取日志数据.
	//参	数:	Alllogs:	完整的日志信息.
	//		Filelogs:	文件简版的日志信息.
	//返回值:
	//作	者:	zengzhaofa. 2022.05.16.
	//*******************************************************************/
	//void CSmtpLog::GetLogData(queue<string>& Alllogs, queue<string>& Filelogs)
	//{
	//	while (!m_queueFullLog.empty())
	//	{
	//		Alllogs.push(m_queueFullLog.front());
	//		m_queueFullLog.pop();
	//	}
	//	while (!m_queueFileFullLog.empty())
	//	{
	//		Filelogs.push(m_queueFileFullLog.front());
	//		m_queueFileFullLog.pop();
	//	}
	//}
}
