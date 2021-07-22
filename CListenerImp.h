#pragma once
#include "SocketInterface.h"
#include "qobject.h"
class Message :
	public QObject
{
	Q_OBJECT

signals:
	void SigPrepareListen();
signals:
	void SigReceive(bool isNotSelfMsg, QString msg);
signals:
	void SigReceiveOnlineInfo(int onlineNum, QString usersName);
signals:
	void SigSend(const BYTE* pData, int iLength);
signals:
	void SigError(int iErrorCode);
signals:
	void SigShutdown();
};
class CListenerImp :
    public IUdpNodeListener
{

public:
	virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen);
	virtual EnHandleResult OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
	virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
	virtual EnHandleResult OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength);
	virtual EnHandleResult OnShutdown(IUdpNode* pSender);

	Message message;
};

