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

	XJMsgHead *pMessage = NULL;
	XJMsgHead MsgHead;
	MsgHead.to_object(pszMsg);

	if (XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE == MsgHead.nEvent)
	{//推送提示信息
		/*pMessage = new XJRspShowTipMessage();
		*((XJRspShowTipMessage*)pMessage) = *((XJRspShowTipMessage*)pParam);*/
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_CONTRACTINFO == MsgHead.nEvent)
	{//推送合约信息
		/*pMessage = new XJRspContractInfo();
		*((XJRspContractInfo*)pMessage) = *((XJRspContractInfo*)pParam);*/
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_USER_RLOGIN == MsgHead.nEvent)
	{//账号登入
		pMessage = new XJReqUserLogin();
		pMessage->to_object(pszMsg);
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_USER_LOGOUT == MsgHead.nEvent)
	{//账号登出
		pMessage = new XJReqUserLogout();
		pMessage->to_object(pszMsg);
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_FUNDACCOUNT == MsgHead.nEvent)
	{//推送资金账号
		pMessage = new XJReqAccountInfo();
		pMessage->to_object(pszMsg);
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_FUNDACCOUNT_STRATEGY == MsgHead.nEvent)
	{//推送资金账号策略
		/*pMessage = new XJRspAccountStrategyInfo();
		*((XJRspAccountStrategyInfo*)pMessage) = *((XJRspAccountStrategyInfo*)pParam);*/
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_FUNDACCOUNT_POSITION == MsgHead.nEvent)
	{//资金账号持仓
		/*pMessage = new XJRspAccountPosition();
		*((XJRspAccountPosition*)pMessage) = *((XJRspAccountPosition*)pParam);*/
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_CHANGE_ORDER == MsgHead.nEvent)
	{//新建委托
		/*pMessage = new XJRspOrderInfo();
		*((XJRspOrderInfo*)pMessage) = *((XJRspOrderInfo*)pParam);*/
	}
	else if (XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_TRADEINFO == MsgHead.nEvent)
	{//推送成交信息
		/*pMessage = new XJRspTradeInfo();
		*((XJRspTradeInfo*)pMessage) = *((XJRspTradeInfo*)pParam);*/
	}

	if (NULL != pMessage)
	{
		Add(sSocket, pMessage);
	}
}

void CXJRecvBuffer::Add(SOCKET sSocket, XJMsgHead *pMsg)
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
