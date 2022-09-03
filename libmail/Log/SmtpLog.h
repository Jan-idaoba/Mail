#pragma once


namespace SMTPClientNS
{
	/*@class
	*******************************************************************
	类名: CSmtpLog
	功能: 保存libcurl错误日志.
	备注:
	作者: zengzhaofa. 2022.05.16. 
	*******************************************************************/
	class CSmtpLog
	{
		public:
			static CSmtpLog& GetLogInstance();

		//public:
		//	static int TraceCallBack(CURL* handle, curl_infotype type, char* data, size_t size, void* userp);
		//	static void DumpCallBack(const char* text, FILE* stream, unsigned char* ptr, size_t size, char nohex);

		//public:
		//	void ClearLogInfo();
		//	void SetLastLogInfo(int& iErrorCode);
		//	void GetLogData(queue<string>& Alllogs, queue<string>& Filelogs);

		//private:
		//	CSmtpLog();
		//	~CSmtpLog();
		//	CSmtpLog(const CSmtpLog&) = delete;
		//	CSmtpLog& operator=(const CSmtpLog&) = delete;

		//private:
		//	static unsigned int				m_nCount;
		//	static string					m_strSingleLog;
		//	static queue<string>			m_queueFullLog;
		//	static string					m_strFileSingleLog;
		//	static queue<string>			m_queueFileFullLog;
	};
}


