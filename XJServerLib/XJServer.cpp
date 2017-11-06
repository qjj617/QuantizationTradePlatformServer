#include "stdafx.h"
#include "XJServer.h"
#include "../Common/Cstring.h"
#include <process.h>
#include "../Common/XJLoadDll.h"
#pragma comment(lib, "XJLoadLibraryLib.lib")


IXJWorkProc* CXJServer::m_pIXJWorkProc = NULL;
list<IO_OPERATION_DATA*> CXJServer::m_listOperationData;

CXJServer::CXJServer()
{
	m_bRunning = false;
	m_nRef = 0;
	m_sListen = INVALID_SOCKET;
	m_listOperationData.clear();
}


CXJServer::~CXJServer()
{

}

bool CXJServer::Init()
{
	WSADATA wsd;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsd))
	{
		int nErr = WSAGetLastError();
		Cstring str;
		str.to_string<int>(nErr);
		Cstring msg = "Socket �汾�����ʧ�ܣ�������: " + str;
		AfxMessageBox(msg, MB_OK);
		return false;
	}

	IXJUnknown *pXJSer = NULL;
	pXJSer = CreateComObject("XJWorkProcLib", MID_XJWorkProcLib, IID_IXJWorkProc);
	if (NULL != pXJSer)
	{
		pXJSer->QueryInterface(IID_IXJWorkProc, (void **)&m_pIXJWorkProc);
		if (NULL == m_pIXJWorkProc)
		{
			AfxMessageBox(L"IXJWorkProc�ӿڻ�ȡʧ��", MB_OK);
			return false;
		}
		m_pIXJWorkProc->Init(PostSend);
	}
	else
	{
		AfxMessageBox(L"XJWorkProcLib �����ʧ��", MB_OK);
		return false;
	}
	return true;
}

void CXJServer::Run()
{
	if (INVALID_SOCKET == (m_sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		int nErr = WSAGetLastError();
		Cstring str;
		str.to_string<int>(nErr);
		Cstring msg = "socket() ����ʧ�ܣ�������: " + str;
		AfxMessageBox(msg, MB_OK);
		return;
	}

	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(5705);

	if (SOCKET_ERROR == bind(m_sListen, (const sockaddr*)&serverAddr, sizeof(SOCKADDR_IN)))
	{
		int nErr = WSAGetLastError();
		Cstring str;
		str.to_string<int>(nErr);
		Cstring msg = "bind() ����ʧ�ܣ�������: " + str;
		AfxMessageBox(msg, MB_OK);
		return;
	}

	if (SOCKET_ERROR == listen(m_sListen, 4))
	{
		int nErr = WSAGetLastError();
		Cstring str;
		str.to_string<int>(nErr);
		Cstring msg = "listen() ����ʧ�ܣ�������: " + str;
		AfxMessageBox(msg, MB_OK);
		return;
	}

	HANDLE hAcceptThread = (HANDLE)_beginthreadex(NULL, 0, AcceptThreadProc, this, 0, NULL);
	CloseHandle(hAcceptThread);
}

unsigned __stdcall CXJServer::AcceptThreadProc(void *pParam)
{
	CXJServer *pThis = (CXJServer*)pParam;
	pThis->m_bRunning = true;
	Cstring msg = "������������";
	AfxMessageBox(msg, MB_OK);
	SOCKET sClient = INVALID_SOCKET;
	SOCKADDR_IN clientAddr;
	int nLen = sizeof(SOCKADDR_IN);
	while (true)
	{
		sClient = INVALID_SOCKET;
		memset(&clientAddr, 0, sizeof(SOCKADDR_IN));
		if (INVALID_SOCKET == (sClient = accept(pThis->m_sListen, (sockaddr*)&clientAddr, &nLen)))
		{
			int nErr = WSAGetLastError();
			if (WSAEINTR == nErr)
			{
				Cstring msg = "AcceptThreadProc �������ѹر�";
				AfxMessageBox(msg, MB_OK);
			}
			else if (WSAEINVAL == nErr)
			{
				Cstring msg = "�������쳣";
				AfxMessageBox(msg, MB_OK);
				continue;
			}
			else
			{
				Cstring str;
				str.to_string<int>(nErr);
				Cstring msg = "accept() ����ʧ�ܣ�������: " + str;
				AfxMessageBox(msg, MB_OK);
			}
			break;
		}

		IO_OPERATION_DATA *pOperationData = new IO_OPERATION_DATA();
		if (NULL != pOperationData)
		{
			//printf("the socket %d has connected\n", sClient);
			pOperationData->sClient = sClient;
			pOperationData->sockaddr = clientAddr;
			//Ͷ�ݽ�����������
			PostRecv(pOperationData);

			pThis->m_listOperationData.push_back(pOperationData);
			DWORD dwRet = SleepEx(1000, TRUE);
			if (WAIT_IO_COMPLETION != dwRet)
			{				
				int nErr = WSAGetLastError();
				Cstring str;
				str.to_string<int>(nErr);
				Cstring msg = "SleepEx() ����ʧ�ܣ�������: " + str;
				AfxMessageBox(msg, MB_OK);
				break;
			}
		}
	}
	return 0;
}

void CXJServer::RecvWorkRoutineProc(DWORD dwError, DWORD dwTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	IO_OPERATION_DATA *pOperationData = (IO_OPERATION_DATA *)lpOverlapped;

	if ((0 != dwError) || (0 == dwTransferred))
	{
		int nErr = WSAGetLastError();
		Cstring str;
		str.to_string<int>(nErr);
		Cstring msg = "WorkRoutineProc() ����ʧ�ܣ�������: " + str;
		AfxMessageBox(msg, MB_OK);
		if (WSAECONNRESET == dwError)
		{
			Cstring msg = "�ͻ����Ѿ��ر�";
			AfxMessageBox(msg, MB_OK);
			closesocket(pOperationData->sClient);
		}
		return;
	}

	if (0 == dwTransferred)
	{
		Cstring msg = "�ͻ��˹ر�����";
		AfxMessageBox(msg, MB_OK);
	}
	else
	{
		//���յ����ݣ�����ҵ��㴦��
		m_pIXJWorkProc->Run(pOperationData->sClient, pOperationData->szBuff, dwTransferred);
	}

	//Ͷ�ݽ�����������
	PostRecv(pOperationData);
}

void CALLBACK CXJServer::SendWorkRoutineProc(DWORD dwError, DWORD dwTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	//WSASend()�����ɹ��������������
	IO_OPERATION_DATA *pOperationData = (IO_OPERATION_DATA *)lpOverlapped;

	if ((0 != dwError) || (0 == dwTransferred))
	{
		int nErr = WSAGetLastError();
		Cstring str;
		str.to_string<int>(nErr);
		Cstring msg = "SendWorkRoutineProc() ����ʧ�ܣ�������: " + str;
		AfxMessageBox(msg, MB_OK);
		if (WSAECONNRESET == dwError)
		{
			Cstring msg = "SendWorkRoutineProc �ͻ����Ѿ��ر�";
			AfxMessageBox(msg, MB_OK);
			closesocket(pOperationData->sClient);
		}
		return;
	}

	delete pOperationData;
}

int CXJServer::PostRecv(IO_OPERATION_DATA *pOperationData)
{
	pOperationData->reset();

	int nRet = 0;
	if (SOCKET_ERROR == (nRet = WSARecv(pOperationData->sClient, &(pOperationData->data), 1, &(pOperationData->dwRecvSize), 
		&(pOperationData->dwFlag), &(pOperationData->overlapped), RecvWorkRoutineProc)))
	{
		int nErr = WSAGetLastError();
		if (ERROR_IO_PENDING != nErr)
		{
			Cstring str;
			str.to_string<int>(nErr);
			Cstring msg = "WSARecv() ����ʧ�ܣ�������: " + str;
			AfxMessageBox(msg, MB_OK);
			return nRet;
		}
	}
	return nRet;
}

int CXJServer::PostSend(SOCKET sSocket, const char *pszMsg, const int nSize)
{
	IO_OPERATION_DATA *oper = new IO_OPERATION_DATA();
	memcpy(oper->szBuff, pszMsg, nSize);
	oper->sClient = sSocket;

	int nRet = 0;
	//����WSASendʱ������dwBufferCountҪ��WSABUF������ͬ����10022
	if (SOCKET_ERROR == (nRet = WSASend(oper->sClient, &(oper->data), 1, &(oper->dwRecvSize), oper->dwFlag, &(oper->overlapped), SendWorkRoutineProc)))
	{
		int nErr = WSAGetLastError();
		if (ERROR_IO_PENDING != nErr)
		{
			Cstring str;
			str.to_string<int>(nErr);
			Cstring msg = "WSASend() ����ʧ�ܣ�������: " + str;
			AfxMessageBox(msg, MB_OK);
			return nRet;
		}
	}

	return nRet;
}

void CXJServer::Stop()
{
	m_pIXJWorkProc->Stop();
	m_bRunning = false;
	for (auto &pair : m_listOperationData)
	{
		closesocket(pair->sClient);
		delete pair;
	}
	m_listOperationData.clear();
	shutdown(m_sListen, SB_BOTH);
	closesocket(m_sListen);
	WSACleanup();
	Cstring msg = "�������ѹر�";
	AfxMessageBox(msg, MB_OK);
}

bool CXJServer::IsRunning()
{
	return m_bRunning;
}

bool CXJServer::Clean()
{
	
	
	return true;
}


void CXJServer::AddRef()
{
	m_nRef++;
}

void CXJServer::Release()
{
	if (0 == m_nRef)
	{
		delete this;
		return;
	}
	m_nRef--;
}

void CXJServer::QueryInterface(GUID GIID, void **pInterface)
{
	if (IID_IXJServer == GIID)
	{
		*pInterface = this;
	}
	else
	{
		*pInterface = NULL;
	}
}
