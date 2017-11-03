#include "stdafx.h"
#include "XJWorkProc.h"
#include "../Common/Cstring.h"
#include <process.h>

PFNSEND CXJWorkProc::m_pFnSend = NULL;
bool CXJWorkProc::m_bRunning = false;
CXJRecvBuffer* CXJWorkProc::m_pRecvBuffer = NULL;
CRITICAL_SECTION CXJWorkProc::m_csRecvBuffer;

HANDLE hEvent = NULL;

MSG_ROUTE CXJWorkProc::m_MsgRoute[] = { MSG_ROUTE(XJ_PUSH_PLATFORMDATA_RSP::RSP_USER_RLOGIN, &CXJWorkProc::UserLogin), 
										MSG_ROUTE(XJ_PUSH_PLATFORMDATA_RSP::RSP_NULL, NULL) };

CXJWorkProc::CXJWorkProc()
{
	m_nRef = 0;
	m_pRecvBuffer = new CXJRecvBuffer();
	m_hRecvEvent = NULL;
}


CXJWorkProc::~CXJWorkProc()
{
	m_nRef = 0;
	delete m_pRecvBuffer;
	DeleteCriticalSection(&m_csRecvBuffer);
}

void CXJWorkProc::Init(const PFNSEND pFnSend)
{
	m_pFnSend = *pFnSend;
	InitializeCriticalSection(&m_csRecvBuffer);
	m_hRecvEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hWorkThread = NULL;
	hWorkThread = (HANDLE)_beginthreadex(NULL, 0, WorkThreadProc, this, 0, NULL);
	if (NULL != hWorkThread)
	{
		CloseHandle(hWorkThread);
	}
}

void CXJWorkProc::Run(const SOCKET sSocket, const char* pszMessage, const int nSize)
{
	EnterCriticalSection(&m_csRecvBuffer);
	m_pRecvBuffer->Push(sSocket, pszMessage, nSize);
	LeaveCriticalSection(&m_csRecvBuffer);
	SetEvent(m_hRecvEvent);
}

unsigned __stdcall CXJWorkProc::WorkThreadProc(void *pParam)
{
	CXJWorkProc *pThis = (CXJWorkProc*)pParam;
	m_bRunning = true;
	while (m_bRunning)
	{
		WaitForSingleObject(pThis->m_hRecvEvent, INFINITE);
		EnterCriticalSection(&m_csRecvBuffer);
		RECV_BUFFER *pBuffer = m_pRecvBuffer->GetBuffer();
		LeaveCriticalSection(&m_csRecvBuffer);

		if (NULL != pBuffer)
		{
			MSG_ROUTE *pMsgRoute = m_MsgRoute;
			while (NULL != pMsgRoute->pFn)
			{
				if (pBuffer->pData->MsgId == pMsgRoute->msgId)
				{
					(pThis->*(pMsgRoute->pFn))(pBuffer->sSocket, pBuffer->pData);
					break;
				}
				else
				{
					pMsgRoute++;
				}
			}
			EnterCriticalSection(&m_csRecvBuffer);
			m_pRecvBuffer->Pop(pBuffer);
			LeaveCriticalSection(&m_csRecvBuffer);
		}
		//ResetEvent(pThis->m_hRecvEvent);
	}
	//AfxMessageBox(L"WorkThreadProc end", MB_OK);
	return 0;
}

void CXJWorkProc::Stop()
{
	m_bRunning = false;
	SetEvent(m_hRecvEvent);
	CloseHandle(hEvent);
}

void CXJWorkProc::AddRef()
{
	m_nRef++;
}

void CXJWorkProc::Release()
{
	if (0 == m_nRef)
	{
		delete this;
		return;
	}
	m_nRef--;
}

void CXJWorkProc::QueryInterface(GUID GIID, void **pInterface)
{
	if (IID_IXJWorkProc == GIID)
	{
		*pInterface = this;
	}
	else
	{
		*pInterface = NULL;
	}
}

void CXJWorkProc::UserLogin(SOCKET sSocket, XJRspMspHead* pMsg)
{
	XJRspLoginInfo *pLogin = (XJRspLoginInfo *)pMsg;
	Cstring str = "UserLogin";
	str += "  ";
	str += pLogin->strUserName;
	str += "  ";
	str += pLogin->strTradingDate;
	str += "  ";
	str += pLogin->strLoginTime;
	str += "  ";
	str += pLogin->strSystemName;
	AfxMessageBox(str, MB_OK);
}