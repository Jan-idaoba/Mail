#include "pch.h"
#include "Common.h"
#include <codecvt>
#include <locale>
#include <objbase.h>
#include "../MimeMessage/IMimeMessage.h"

std::string CommonFunction::UnicodeToUTF8(const std::wstring& wstrSrc)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wcv;
	return wcv.to_bytes(wstrSrc);
}

std::wstring CommonFunction::UTF8ToUnicode(const std::string& strSrc)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wcv;
	return wcv.from_bytes(strSrc);
}

std::string CommonFunction::UnicodeToAscii(const std::wstring& wstrSrc)
{
	size_t len;
	std::string strDest;
	std::mbstate_t state = {};
	const wchar_t* src = wstrSrc.data();
	
	errno_t err = wcsrtombs_s(&len, nullptr, 0, &src, 0, &state);
	if (!err)
	{
		auto buff = std::make_unique<char[]>(len + 1);
		err = wcsrtombs_s(&len, buff.get(), len + 1, &src, len + 1, &state);
		if (!err) {
			strDest.assign(buff.get(), len);
		}
	}

	return strDest;
}

std::wstring CommonFunction::AsciiToUnicode(const std::string& strSrc)
{
	size_t len;
	std::wstring wstrDest;
	std::mbstate_t state = {};
	const char* src = strSrc.data();

	errno_t err = mbsrtowcs_s(&len,nullptr,0, &src, 0, &state);
	if (!err)
	{
		auto buff = std::make_unique<wchar_t[]>(len + 1);
		mbsrtowcs_s(&len, buff.get(), len + 1, &src, len+1, &state);
		if (static_cast<size_t>(-1) != len) {
			wstrDest.assign(buff.get(), len);
		}
	}

	return wstrDest;
}

std::string CommonFunction::UTF8ToAscii(const std::string& strSrc)
{
	return UnicodeToAscii(UTF8ToUnicode(strSrc));
}

std::string CommonFunction::AsciiToUTF8(const std::string& strSrc)
{
	return UnicodeToUTF8(AsciiToUnicode(strSrc));
}

//void CommonFunction::GenerateGUID(std::wstring& wstrGUID)
//{
//	HRESULT hr = CoInitialize(NULL);
//
//	GUID guid = { 0 };
//	hr = CoCreateGuid(&guid);
//	if (SUCCEEDED(hr)) {
//		wchar_t szGUID[80] = { 0 };
//		wsprintf(szGUID, L"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
//			guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
//			guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
//
//		wstrGUID = szGUID;
//	}
//
//	CoUninitialize();
//}

