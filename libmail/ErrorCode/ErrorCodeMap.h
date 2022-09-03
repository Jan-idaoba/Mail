#pragma once
namespace SMTPClientNS
{
	//@class
	//����: CErrorCodeMap
	//����: libcurl������ת����PB������
	//��ע:
	//����: zengzhaofa. 2022.05.16.
	class CErrorCodeMap
	{
	public:
		static CErrorCodeMap& GetErrorCodeInstance();

	public:
		const char* GetErrorInfoFromMap(int iErrorCode) const;
		int GetErrorCodeFromMap(int iErrorCode) const;

	private:
		CErrorCodeMap();
		~CErrorCodeMap();
		CErrorCodeMap(const CErrorCodeMap&) = delete;
		CErrorCodeMap& operator=(const CErrorCodeMap&) = delete;
		void GenerateErrorCodeMappingTable();
		void InsertErrorInfo(int iCurlErrorCode, int iPBErrorCode, unsigned int nErrorCodeID);

	private:
		std::map<int, std::pair<int, std::string>>		m_mapErrorInfo;
	};
}


