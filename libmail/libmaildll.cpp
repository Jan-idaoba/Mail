#include "pch.h"
#include "../libmail/MimeMessage/MimeMessage.h"
#include "../libmail/SmtpWrapper/SmtpWrapper.h"

namespace libmailNS
{
#ifndef SUPPORT_WEB_PLATFROM
	extern "C" __declspec(dllexport) IMimeMessage * CreateMimeMessage() {
		return CMimeMessage::CreateMessageInstance();
	}
#else
	IMimeMessage* CreateMimeMessage() {
		return CMimeMessage::CreateMessageInstance();
	}
#endif // !SUPPORT_WEB_PLATFROM

#ifndef SUPPORT_WEB_PLATFROM
	extern "C" __declspec(dllexport) ISmtpWrapper * CreateSmtpClient() {
		return CSmtpWrapper::CreateSmtpClientInstance();
	}
#else
	ISmtpWrapper* CreateSmtpClient() {
		return CSmtpWrapper::CreateSmtpClientInstance();
	}
#endif // !SUPPORT_WEB_PLATFROM
}


