#pragma once
#include "../protocol/XJTradePlatform_network_protocol.h"
#include "../protocol/XJplatform_callbck_push_protocol.h"

struct RECV_BUFFER
{
	RECV_BUFFER()
	{
		pLast = NULL;
		pNext = NULL;
		sSocket = INVALID_SOCKET;
	}
	~RECV_BUFFER()
	{
		delete pData;
	}
	SOCKET sSocket;
	XJMsgHead *pData;

	RECV_BUFFER *pLast;
	RECV_BUFFER *pNext;
};

class CXJRecvBuffer
{
public:
	CXJRecvBuffer();
	~CXJRecvBuffer();


	void Push(SOCKET sSocket, const char *pszMsg, const int nSize);
	RECV_BUFFER *GetBuffer();
	void Pop(RECV_BUFFER *pBuffer);

private:
	void Add(SOCKET sSocket, XJMsgHead *pBuffer);

private:
	RECV_BUFFER *m_pHead;
	RECV_BUFFER *m_pTail;
};

