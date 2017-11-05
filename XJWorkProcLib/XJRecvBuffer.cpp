#include "stdafx.h"
#include "XJRecvBuffer.h"


CXJRecvBuffer::CXJRecvBuffer()
{
	m_pHead = NULL;
	m_pTail = NULL;
}


CXJRecvBuffer::~CXJRecvBuffer()
{
	RECV_BUFFER *pTemp = m_pHead;
	while (NULL != m_pHead)
	{
		m_pHead = m_pHead->pNext;
		delete pTemp;
		pTemp = m_pHead;
	}
}

void CXJRecvBuffer::Push(SOCKET sSocket, const char *pszMsg, const int nSize)
{
	if(NULL == pszMsg)
	{
		return;
	}

	void *pMsg = malloc(nSize);
	if (NULL != pMsg)
	{
		memcpy(pMsg, pszMsg, nSize);
		Add(sSocket, (XJRspMspHead *)pMsg);
	}
}

void CXJRecvBuffer::Add(SOCKET sSocket, XJRspMspHead *pMsg)
{		
	RECV_BUFFER *pNewBuffer = new RECV_BUFFER();
	if (NULL != pNewBuffer)
	{
		pNewBuffer->pData = pMsg;
		pNewBuffer->sSocket = sSocket;
		if (NULL == m_pHead)
		{
			m_pHead = pNewBuffer;
			m_pTail = m_pHead;
		}
		else
		{
			m_pTail->pNext = pNewBuffer;
			pNewBuffer->pLast = m_pTail;
			m_pTail = m_pTail->pNext;
		}
	}
}

RECV_BUFFER *CXJRecvBuffer::GetBuffer()
{
	RECV_BUFFER *pTemp = NULL;
	if (NULL != m_pHead)
	{
		pTemp = m_pHead;		
	}
	
	return pTemp;
}

void CXJRecvBuffer::Pop(RECV_BUFFER *pBuffer)
{
	if ((NULL != pBuffer) && (NULL != m_pHead))
	{
		if (m_pHead == pBuffer)
		{
			if (m_pTail == m_pHead)
			{
				m_pTail = m_pTail->pNext;
				m_pHead = NULL;
			}
			else
			{
				m_pHead = m_pHead->pNext;
				m_pHead->pLast = NULL;
			}
		}
		else if(m_pTail == pBuffer)
		{
			m_pTail = m_pTail->pLast;
			m_pTail->pNext = NULL;
		}
		else
		{
			pBuffer->pLast->pNext = pBuffer->pNext;
		}
		delete pBuffer;
		pBuffer = NULL;
	}
}
