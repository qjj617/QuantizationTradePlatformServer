#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
#include "../Common/IXJWorkProc.h"
#include "../Common/IXJServer.h"
#pragma comment(lib, "ws2_32")
#include <list>
using namespace std;

#define DATA_BUFF_LEN 1024

struct IO_OPERATION_DATA
{
	WSAOVERLAPPED overlapped;
	WSABUF data;
	char szBuff[DATA_BUFF_LEN];
	SOCKET sClient;
	SOCKADDR_IN sockaddr;
	DWORD dwRecvSize;
	DWORD dwFlag;

	IO_OPERATION_DATA() { init(); }
	void init() { memset(this, 0, sizeof(IO_OPERATION_DATA)); data.buf = szBuff; data.len = DATA_BUFF_LEN; dwRecvSize = 0; dwFlag; }
	void reset() { memset(szBuff, 0, DATA_BUFF_LEN); memset(&overlapped, 0, sizeof(WSAOVERLAPPED)); dwRecvSize = 0; dwFlag; }
};

class CXJServer : public IXJServer
{
public:
	CXJServer();
	~CXJServer();

	virtual bool Init();
	virtual void Run();
	virtual void Stop();
	virtual bool IsRunning();
	virtual bool Clean();

	virtual void AddRef();
	virtual void Release();
	virtual void QueryInterface(GUID GIID, void **pInterface);

private:
	static unsigned __stdcall AcceptThreadProc(void *pParam);
	static void CALLBACK RecvWorkRoutineProc(DWORD dwError, DWORD dwTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
	static void CALLBACK SendWorkRoutineProc(DWORD dwError, DWORD dwTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
	static int PostRecv(IO_OPERATION_DATA *pOperationData);
	static int PostSend(SOCKET sSocket, const char *pszMsg, const int nSize);

private:
	bool m_bRunning;
	int m_nRef;
	SOCKET m_sListen;
	static list<IO_OPERATION_DATA*> m_listOperationData;

	static IXJWorkProc* m_pIXJWorkProc;
};

