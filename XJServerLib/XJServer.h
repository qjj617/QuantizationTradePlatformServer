#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <MSWSock.h>
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

	IO_OPERATION_DATA() { reset(); }
	void reset() { memset(this, 0, sizeof(IO_OPERATION_DATA)); }
};

class CXJServer : public IXJServer
{
public:
	CXJServer();
	~CXJServer();

	virtual void Init();
	virtual void Run();
	virtual void Stop();
	virtual bool IsRunning();
	virtual bool Clean();

	virtual void AddRef();
	virtual void Release();
	virtual void QueryInterface(GUID GIID, void **pInterface);

private:
	static unsigned __stdcall AcceptThreadProc(void *pParam);
	static void CALLBACK WorkRoutineProc(DWORD dwError, DWORD dwTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);

private:
	bool m_bRunning;
	int m_nRef;
	SOCKET m_sListen;
	list<IO_OPERATION_DATA*> m_listOperationData;
};

