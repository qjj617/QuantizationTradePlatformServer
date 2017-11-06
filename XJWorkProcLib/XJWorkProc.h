#pragma once
#include "../Common/IXJWorkProc.h"
#include "XJRecvBuffer.h"
#include "../protocol/XJplatform_callbck_push_protocol.h"
#include "XJPlatformManager.h"

class CXJWorkProc;
typedef void(CXJWorkProc::*PFNMSGPROC)(SOCKET, XJMsgHead*);
struct MSG_ROUTE
{
	MSG_ROUTE(int msgId, PFNMSGPROC pfn) :msgId(msgId), pFn(pfn) {}
	int msgId;
	PFNMSGPROC pFn;
};

typedef int(*PFNAPPMSG)(XJRspMspHead *);
struct APPMSG
{
	int nMsgId;
	PFNAPPMSG pFnAppMsg;

	APPMSG(int nMsgId, PFNAPPMSG pFn) : nMsgId(nMsgId), pFnAppMsg(pFn) {}
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

	//平台数据推送回调函数
	static int PushPlatformDataProc(int nMsgId, XJRspMspHead *pParam);

private:
	static unsigned __stdcall WorkThreadProc(void *pParam);
	void UserLogin(SOCKET sSocket, XJMsgHead* pMsg);

	static int OnRspLogin(XJRspMspHead *pParam);
	static int OnRspLogout(XJRspMspHead *pParam);
	static int OnRspAccountInfo(XJRspMspHead *pParam);

private:
	static SOCKET m_sSocket;
	static PFNSEND m_pFnSend;
	int m_nRef;
	static bool m_bRunning;
	static CXJRecvBuffer* m_pRecvBuffer;
	static CRITICAL_SECTION m_csRecvBuffer;
	HANDLE m_hRecvEvent;
	static MSG_ROUTE m_MsgRoute[];
	//自定义消息执行函数表
	static APPMSG m_AppMsgMap[];

	CPlatformManager *pPlatformManager;
};

