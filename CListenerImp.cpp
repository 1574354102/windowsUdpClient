#include "CListenerImp.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "QDebug"
using namespace rapidjson;
using namespace std;

EnHandleResult CListenerImp::OnPrepareListen(IUdpNode* pSender, SOCKET soListen)
{
	emit message.SigPrepareListen();
	return HR_OK;
}
EnHandleResult CListenerImp::OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
{
	Document dom;
	
	if (dom.Parse((char*)pData, iLength).HasParseError())
	{
		return HR_IGNORE;
	}
	if (dom.HasMember("msgType") && dom["msgType"].IsInt())
	{
		if (dom["msgType"].GetInt() == 0 || dom["msgType"].GetInt() == 1)
		{
			if (dom.HasMember("msgInfo") && dom["msgInfo"].IsString())
			{
				if (dom["msgType"].GetInt() == 0)
				{
					emit message.SigReceive(false, QString(dom["msgInfo"].GetString()));
				}
				else if (dom["msgType"].GetInt() == 1 && dom.HasMember("userName") && dom["userName"].IsString())
				{
					emit message.SigReceive(true, QString(dom["userName"].GetString() + QString(":\n        ") + dom["msgInfo"].GetString()));
				}
			}
		}
		else if (dom["msgType"].GetInt() == 2)
		{
			if (dom.HasMember("onlineUsersName") && dom["onlineUsersName"].IsArray())
			{
				QString userOnline;
				Value& usersName = dom["onlineUsersName"];
				for (int i = 0; i < usersName.Size(); i++)
				{
					if (usersName[i].IsString())
					{
						userOnline.append(usersName[i].GetString());
						userOnline.append("\n");
					}
				}
				emit message.SigReceiveOnlineInfo(usersName.Size(), userOnline);
			}
		}
	}
	return HR_OK;
}
EnHandleResult CListenerImp::OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
{
	emit message.SigSend(pData, iLength);
	return HR_OK;
}
EnHandleResult CListenerImp::OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)
{
	emit message.SigError(iErrorCode);
	return HR_OK;
}
EnHandleResult CListenerImp::OnShutdown(IUdpNode* pSender)
{
	emit message.SigShutdown();
	return HR_OK;
}