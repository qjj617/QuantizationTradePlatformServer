#pragma once
#include "../Common/IXJWorkProc.h"
#include "XJRecvBuffer.h"

class CXJWorkProc;
typedef void(CXJWorkProc::*PFNMSGPROC)(SOCKET, XJRspMspHead*);
struct MSG_ROUTE
{
	MSG_ROUTE(XJ_PUSH_PLATFORMDATA_RSP msgId, PFNMSGPROC pfn) :msgId(msgId), pFn(pfn) {}
	XJ_PUSH_PLATFORMDATA_RSP msgId;
	PFNMSGPROC pFn;
};

class CXJWorkProc :	public IXJWorkProc
{
public:
	CXJWorkProc();
	~CXJWorkProc();

	virtual void Init(const PFNSEND pFnSend);
	virtual void Run(const SOCKET sSocket, const char* pszMessage, const int nSize);
	virtual void Stop();
	virtual void AddRef();
	virtual void Release();
	virtual void QueryInterface(GUID GIID, void **pInterface);

private:
	static unsigned __stdcall WorkThreadProc(void *pParam);
	void UserLogin(SOCKET sSocket, XJRspMspHead* pMsg);

private:
	static PFNSEND m_pFnSend;
	int m_nRef;
	static bool m_bRunning;
	static CXJRecvBuffer* m_pRecvBuffer;
	static CRITICAL_SECTION m_csRecvBuffer;
	HANDLE m_hRecvEvent;
	static MSG_ROUTE m_MsgRoute[];
};

