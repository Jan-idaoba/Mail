#pragma once

//@class
//类名: CommonFunction
//功能: 公共方法类
//备注:
//作者: zengzhaofa. 2022.05.16.
class IMimeMessage;
class CommonFunction
{
public:
	CommonFunction() = delete;
	~CommonFunction() = delete;
	CommonFunction(const CommonFunction&) = delete;
	CommonFunction& operator=(const CommonFunction&) = delete;
	CommonFunction(const CommonFunction&&) = delete;
	CommonFunction& operator=(const CommonFunction&&) = delete;

	static std::string UnicodeToUTF8(const std::wstring& wstrSrc);
	static std::wstring UTF8ToUnicode(const std::string& strSrc);

	static std::string UnicodeToAscii(const std::wstring& wstrSrc);
	static std::wstring AsciiToUnicode(const std::string& strSrc);

	static std::string UTF8ToAscii(const std::string& strSrc);
	static std::string AsciiToUTF8(const std::string& strSrc);


	// 生成GUID
	static void GenerateGUID(std::wstring& wstrGUID);

	// 读文件 & 写文件
	//static bool GetFileInfo(const wchar_t* szFile, unsigned char*& pData, DWORD& dReadCount);
	//static bool SetFileInfo(const wchar_t* szFile, unsigned char* pData, DWORD dWriteCount);



};


