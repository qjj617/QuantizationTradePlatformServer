#include "stdafx.h"
#include "XJAccountInfo.h"
#include <algorithm>

CAccountInfo::CAccountInfo()
{
	m_PlatformType = PLATFORM_TYPE::PF_NULL;
	m_pAccountInfo = NULL;
	m_pLoginInfo = NULL;
}


CAccountInfo::~CAccountInfo()
{
	if (NULL != m_pAccountInfo)
	{
		delete m_pAccountInfo;
	}

  	if (NULL != m_pLoginInfo)
	{
		delete m_pLoginInfo;
	}

	for (auto &pair : m_StrategyInfos_list)
	{
		delete (pair);
	}

	for (auto &pair : m_PositionsInfos_list)
	{
		delete (pair);
	}

	for (auto &pair : m_OrderInfos_list)
	{
		delete (pair);
	}

	for (auto &pair : m_TradeInfos_list)
	{
		delete (pair);
	}
}

//�����ʽ��˻���Ϣ
void CAccountInfo::SetAccountInfo(XJRspFundAccountInfo *pAccountInfo)
{
	if (NULL != m_pAccountInfo)
	{
		delete m_pAccountInfo;
	}
	m_pAccountInfo = pAccountInfo;
}

//���õ�����Ϣ
void CAccountInfo::SetLoginInfo(XJRspLoginInfo *pLoginInfo)
{
	if (NULL != m_pLoginInfo)
	{
		delete m_pLoginInfo;
	}
	m_pLoginInfo = pLoginInfo;
}

//����ƽ̨����
void CAccountInfo::SetPlatformType(PLATFORM_TYPE pfType)
{
	m_PlatformType = pfType;
}

//��ѯƽ̨����
PLATFORM_TYPE CAccountInfo::GetPlatformType()
{
	return m_PlatformType;
}

//���Ӳ�����Ϣ
void CAccountInfo::AddStrategyInfo(XJRspAccountStrategyInfo *pStrategyInfo)
{
	m_StrategyInfos_list.push_back(pStrategyInfo);
}

//ɾ��������Ϣ
void CAccountInfo::DeleteStrategyInfo(XJRspAccountStrategyInfo *pStrategyInfo)
{
	list<XJRspAccountStrategyInfo *>::const_iterator it = find_if(m_StrategyInfos_list.cbegin(), m_StrategyInfos_list.cend(),
		[&pStrategyInfo](const XJRspAccountStrategyInfo* pInfo) {return pInfo->strAccountId == pStrategyInfo->strAccountId; });
	if (it != m_StrategyInfos_list.cend())
	{
		delete (*it);
		m_StrategyInfos_list.erase(it);
	}
}

//���ӳֲ���Ϣ
void CAccountInfo::AddPositionInfo(XJRspAccountPosition *pPositionInfo)
{
	m_PositionsInfos_list.push_back(pPositionInfo);
}

//ɾ���ֲ���Ϣ
void CAccountInfo::DeletePositionInfo(XJRspAccountPosition *pPositionInfo)
{
	list<XJRspAccountPosition *>::const_iterator it = find_if(m_PositionsInfos_list.cbegin(), m_PositionsInfos_list.cend(),
		[&pPositionInfo](const XJRspAccountPosition* pInfo) {return pInfo->strContractNo == pPositionInfo->strContractNo; });
	if (it != m_PositionsInfos_list.cend())
	{
		delete (*it);
		m_PositionsInfos_list.erase(it);
	}
}

//����ί����Ϣ
void CAccountInfo::AddOrderInfo(XJRspOrderInfo *pOrderInfo)
{
	m_OrderInfos_list.push_back(pOrderInfo);
}

//ɾ��ί����Ϣ
void CAccountInfo::DeleteOrderInfo(XJRspOrderInfo *pOrderInfo)
{
	list<XJRspOrderInfo *>::const_iterator it = find_if(m_OrderInfos_list.cbegin(), m_OrderInfos_list.cend(),
		[&pOrderInfo](const XJRspOrderInfo* pInfo) {return pInfo->strAccountId == pOrderInfo->strAccountId; });
	if (it != m_OrderInfos_list.cend())
	{
		delete (*it);
		m_OrderInfos_list.erase(it);
	}
}

//���ӳɽ���Ϣ
void CAccountInfo::AddTradeInfo(XJRspTradeInfo *pTradeInfo)
{
	m_TradeInfos_list.push_back(pTradeInfo);
}

//ɾ���ɽ���Ϣ
void CAccountInfo::DeleteTradeInfo(XJRspTradeInfo *pTradeInfo)
{
	list<XJRspTradeInfo *>::const_iterator it = find_if(m_TradeInfos_list.cbegin(), m_TradeInfos_list.cend(),
		[&pTradeInfo](const XJRspTradeInfo* pInfo) {return pInfo->strAccountId == pTradeInfo->strAccountId; });
	if (it != m_TradeInfos_list.cend())
	{
		delete (*it);
		m_TradeInfos_list.erase(it);
	}
}

//��ѯ������Ϣ
const XJRspLoginInfo* CAccountInfo::GetLoginInfo()
{
	return m_pLoginInfo;
}

//��ѯ�ʽ��˻���Ϣ
const XJRspFundAccountInfo* CAccountInfo::GetAccountInfo()
{
	return m_pAccountInfo;
}

//��ѯ������Ϣ
const list<XJRspAccountStrategyInfo *>& CAccountInfo::GetStrategyInfos()
{
	return m_StrategyInfos_list;
}

//��ѯ�ֲ���Ϣ
const list<XJRspAccountPosition *>& CAccountInfo::GetPositionInfos()
{
	return m_PositionsInfos_list;
}

//���ݺ�Լ�Ų��ҳֲ���Ϣ
XJRspAccountPosition *CAccountInfo::GetPositionInfoByContractNo(const string &strContractNo)
{
	list<XJRspAccountPosition *>::const_iterator it = find_if(m_PositionsInfos_list.cbegin(), m_PositionsInfos_list.cend(),
		[&strContractNo](XJRspAccountPosition *pPosition) {return 0 == pPosition->strContractNo.compare(strContractNo); });
	if (it != m_PositionsInfos_list.cend())
	{
		return (*it);
	}
	return NULL;
}

void CAccountInfo::SetPositionInfoByContractNo(const string &strContractNo, XJRspAccountPosition *pPositionInfo)
{
	list<XJRspAccountPosition *>::iterator it = find_if(m_PositionsInfos_list.begin(), m_PositionsInfos_list.end(),
		[&strContractNo](XJRspAccountPosition *pPosition) {return 0 == pPosition->strContractNo.compare(strContractNo); });
	if (it != m_PositionsInfos_list.cend())
	{
		delete (*it);
		(*it) = pPositionInfo;
	}
}

//��ѯί����Ϣ
const list<XJRspOrderInfo*>& CAccountInfo::GetOrderInfos()
{
	return m_OrderInfos_list;
}

//����ί�б�Ų���ί����Ϣ
XJRspOrderInfo* CAccountInfo::GetOrderInfosByOrderNo(const string &strOrderNo)
{
	list<XJRspOrderInfo *>::const_iterator it = find_if(m_OrderInfos_list.cbegin(), m_OrderInfos_list.cend(),
		[&strOrderNo](XJRspOrderInfo *pOrderInfo) {return 0 == pOrderInfo->strOrderNo.compare(strOrderNo); });
	if (it != m_OrderInfos_list.cend())
	{
		return (*it);
	}
	return NULL;
}

void CAccountInfo::SetOrderInfosByOrderNo(const string &strOrderNo, XJRspOrderInfo* pOrderInfo)
{
	list<XJRspOrderInfo *>::iterator it = find_if(m_OrderInfos_list.begin(), m_OrderInfos_list.end(),
		[&strOrderNo](XJRspOrderInfo *pOrderInfo) {return 0 == pOrderInfo->strOrderNo.compare(strOrderNo); });
	if (it != m_OrderInfos_list.cend())
	{
		delete (*it);
		(*it) = pOrderInfo;
	}
}

//����ί�б�����óɽ���Ϣ
void CAccountInfo::SetTradeInfoByOrderNo(const string &strOrderNo, XJRspTradeInfo *pTradeInfo)
{
	list<XJRspTradeInfo *>::iterator it = find_if(m_TradeInfos_list.begin(), m_TradeInfos_list.end(),
		[&strOrderNo](XJRspTradeInfo *pTradeInfo) {return 0 == pTradeInfo->strOrderNo.compare(strOrderNo); });
	if (it != m_TradeInfos_list.cend())
	{
		delete (*it);
		(*it) = pTradeInfo;
	}
}

//�жϳɽ���Ϣ�Ƿ��ڳɽ���Ϣ������
bool CAccountInfo::IsInTradeInfolist(const string &strOrderNo)
{
	list<XJRspTradeInfo *>::iterator it = find_if(m_TradeInfos_list.begin(), m_TradeInfos_list.end(),
		[&strOrderNo](XJRspTradeInfo *pTradeInfo) {return 0 == pTradeInfo->strOrderNo.compare(strOrderNo); });
	if (it != m_TradeInfos_list.cend())
	{
		return true;
	}

	return false;
}

//��ѯ�ɽ���Ϣ
const list<XJRspTradeInfo*>& CAccountInfo::GetTradeInfos()
{
	return m_TradeInfos_list;
}
