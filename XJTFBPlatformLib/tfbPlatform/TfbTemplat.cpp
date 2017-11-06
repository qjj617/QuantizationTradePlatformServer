/**********************************************************************
�ļ���:TfbTemplat.cpp
���ܺ�ģ���Ŀ��:�ļ�ʵ�����츻�����ʽ���ϵͳģ����
�����߼�����:��� 2017.10.10
**********************************************************************/
#include "TfbTemplat.h"

extern char g_cUserFlag[60];
/*********************************************************************
��������:CTfTemplat
��������:���캯����������ʱ��ʼ������
�����߼�����:��� 2017.10.10
*********************************************************************/
CTfbTemplat::CTfbTemplat(PFNPLATFORMDATAPROC pfn) : m_pPlatformDataProc(pfn)
{
	::InitializeCriticalSection(&cs);
	dPositionProfit = 0.0;
}

/*********************************************************************
��������:~CTfTemplat
��������:���������ͷŶ�����ռ�õ���Դ
�����߼�����:��� 2017.10.10
*********************************************************************/
CTfbTemplat::~CTfbTemplat()
{
	::DeleteCriticalSection(&cs);
}

/*********************************************************************
��������:PushPositionInfo
��������:�ֲ����ݴ���map���������������
�����߼�����:��� 2017.10.10
*********************************************************************/
bool CTfbTemplat::PushPositionInfo(string sUserName, TFBApiPosition *pPositionInfo)
{
	bool bFindTPmcode = false;
	bool bFindUserName = false;
	XJRspAccountPosition PositionMsg;
	PositionMsg.strAccountId = sUserName;

	map<string, vector<TFBApiPosition>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_PositionMap.begin(); it != m_PositionMap.end(); it++)
	{
		if (sUserName == it->first)
		{
			bFindUserName = true;
			for (int i = 0; i < it->second.size(); i++)
			{
				if (strcmp(it->second.at(i).pszTPmcode, pPositionInfo->pszTPmcode) == 0
					&& it->second.at(i).bIsBuy == pPositionInfo->bIsBuy)
				{
					bFindTPmcode = true;//ͬһ�û�,��Լ������vector����,������������ͬ

					if (it->second.at(i).dNumber == pPositionInfo->dNumber) //�ֲ�����ͬ,�������ͳֲָ���,�˳��ڶ���ѭ��
					{
						break;
					}
					else   //�ֲ�����ͬ,����³ֲ���,����ƽ̨����, �޸����,�˳��ڶ���ѭ��
					{
						it->second.at(i).dNumber = pPositionInfo->dNumber;
						it->second.at(i).dPrice = pPositionInfo->dPrice;

						PositionMsg.strContractNo = pPositionInfo->pszTPmcode; //��Լ�����Ӧ��Ʒ��
						PositionMsg.nPositions = pPositionInfo->dNumber;       //�ֲֶܳ�Ӧ�ֲ�����
						PositionMsg.dOpenAveragePrice = pPositionInfo->dPrice;    //�ֲ־����ǳɽ�����?
						if (pPositionInfo->bIsBuy)
						{
							PositionMsg.chOrderSide = '0';         //??
						}
						else
						{
							PositionMsg.chOrderSide = '1';         //??
						}
						PositionMsg.dMargin = pPositionInfo->dMargin;          //��֤��
						PositionMsg.chCommodityType = '1';
						m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_FUNDACCOUNT_POSITION, &PositionMsg);
						break;
					}
				}
			}
		}
		else
		{
			bFindTPmcode = false;
		}
		if (bFindUserName)//���ҵ��û���,�˳���һ��ѭ��
		{
			break;
		}
	}
	if (!bFindTPmcode)//û�ҵ���Լ����,����
	{
		m_PositionMap[sUserName].push_back(*pPositionInfo);

		PositionMsg.strContractNo = pPositionInfo->pszTPmcode; //��Լ�����Ӧ��Ʒ��
		PositionMsg.nPositions = pPositionInfo->dNumber;       //�ֲֶܳ�Ӧ�ֲ�����
		PositionMsg.dOpenAveragePrice = pPositionInfo->dPrice;    //�ֲ־����ǳɽ�����?
		if (pPositionInfo->bIsBuy)
		{
			PositionMsg.chOrderSide = '0';         
		}
		else
		{
			PositionMsg.chOrderSide = '1';         
		}
		PositionMsg.dMargin = pPositionInfo->dMargin;          //��֤��
		PositionMsg.chCommodityType = '1';
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_FUNDACCOUNT_POSITION, &PositionMsg);
	}

	::LeaveCriticalSection(&cs);

	return bFindTPmcode;
}

/*********************************************************************
��������:PushUserInforRespond
��������:������û��ص���Ϣ
�����߼�����:��� 2017.10.23
*********************************************************************/
bool CTfbTemplat::PushUserInforRespond(string sUserName, TFBApiUserInforRespond *pUserInforRespond)
{
	bool bFindUserName = false;
	map<string, vector<TFBApiUserInforRespond>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_UserInforRespondMap.begin(); it != m_UserInforRespondMap.end(); it++)
	{
		if (sUserName == it->first)
		{
			bFindUserName = true;
			for (int i = 0; i < it->second.size(); i++)
			{
				it->second.at(i).dNowFunds = pUserInforRespond->dNowFunds;
				it->second.at(i).dOutFreezingFunds = pUserInforRespond->dOutFreezingFunds;
				it->second.at(i).dOrderFreezingFunds = pUserInforRespond->dOrderFreezingFunds;
				it->second.at(i).dPositionsFreezingFunds = pUserInforRespond->dPositionsFreezingFunds;
			}
			break;
		}
	}
	if (!bFindUserName)
	{
		m_UserInforRespondMap[sUserName].push_back(*pUserInforRespond);
	}
	::LeaveCriticalSection(&cs);

	return true;
}


/*********************************************************************
��������:PushOrderInfo
��������:�������ݴ���map����,��ƽ̨���Ͷ�����Ϣ
�����߼�����:��� 2017.10.20
*********************************************************************/
bool CTfbTemplat::PushOrderInfo(string sUserName, TFBApiOrder* pOrderInfo)
{
	bool bFindUserName = false;
	bool bFindOrderID = false;
	char cOrderNo[10];
	XJRspOrderInfo OrderMsg;
	OrderMsg.strAccountId = sUserName;

	map<string, vector<TFBApiOrder>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_OrderMap.begin(); it != m_OrderMap.end(); it++)
	{
		if (sUserName == it->first)
		{
			bFindUserName = true;
			{
				for (int i = 0; i < it->second.size(); i++)
				{
					if (it->second.at(i).nOrderID == pOrderInfo->nOrderID)
					{
						bFindOrderID = true;
						break;
					}
				}
			}		
		}
		if (bFindUserName)
		{
			break;
		}
	}

	if (!bFindOrderID)
	{
		m_OrderMap[sUserName].push_back(*pOrderInfo);

		sprintf_s(cOrderNo, "%d", pOrderInfo->nOrderID);
		OrderMsg.strOrderNo = cOrderNo;                         //ί�б��
		OrderMsg.strInsertDataTime = pOrderInfo->pszTime;       //ί��ʱ��
		OrderMsg.strContrctNo = pOrderInfo->pszMCode;           //��Լ����
		OrderMsg.dOrderPrice = pOrderInfo->dPrice;              //ί�м۸�
		OrderMsg.nOrderVolume = pOrderInfo->dNumber;            //ί������
		if (pOrderInfo->bIsBuy)                                 //����
		{
			OrderMsg.chOrderSide = '0';
		}
		else
		{
			OrderMsg.chOrderSide = '1';
		}
		if (pOrderInfo->bAdverse)
		{
			OrderMsg.chOffset = '1';
		}
		else
		{
			OrderMsg.chOffset = '0';
		}

		if (pOrderInfo->nModeType == 9)
		{
			OrderMsg.chOrderstate = '0';
		}
		if (pOrderInfo->nModeType == 8)
		{
			OrderMsg.chOrderstate = '4';
		}
		if (pOrderInfo->nModeType == 10)
		{
			OrderMsg.chOrderstate = '1';
		}
		if (pOrderInfo->nModeType == 1)
		{
			OrderMsg.chOrderstate = '2';
		}

		OrderMsg.chCommodityType = '1';
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_CHANGE_ORDER, &OrderMsg);
	}
	::LeaveCriticalSection(&cs);

	return bFindOrderID;
}

/*********************************************************************
��������:PushLoadTradeOrder
��������:���سɽ�����
�����߼�����:��� 2017.10.25
*********************************************************************/
bool CTfbTemplat::PushLoadTradeOrder(string sUserName, TFBApiLoadTrade *pLoadTrade)
{
	bool bFindUserName = false;
	TfbLoadTrade TLoadTrade;
	
	::EnterCriticalSection(&cs);
	APIStrncpy(TLoadTrade.sUserName, sUserName.c_str());

	TLoadTrade.nOrderNo = pLoadTrade->ohedoid;

	APIStrncpy(TLoadTrade.cTradeDataTime, pLoadTrade->ohedealtime);
	APIStrncpy(TLoadTrade.sContrctNo, pLoadTrade->ohemcode);
	if (pLoadTrade->ohetype == 1)
	{
		TLoadTrade.chOrderSide = '0';
	}
	if (pLoadTrade->ohetype == 0)
	{
		TLoadTrade.chOrderSide = '1';
	}
	switch (pLoadTrade->oheAdverse)
	{
	case 0:TLoadTrade.chOffset = '0';
		break;
	case 1:TLoadTrade.chOffset = '1';
		break;
	case 2:TLoadTrade.chOffset = '2';
		break;
	default:TLoadTrade.chOffset = '9';
		break;
	}
	TLoadTrade.dMatchPrice = pLoadTrade->oheprice;
	TLoadTrade.nMatchVolume = pLoadTrade->ohenumber;
	m_LoadTradeOrder[sUserName].push_back(TLoadTrade);

	::LeaveCriticalSection(&cs);

	return true;
}

/*********************************************************************
��������:GetLoadTradeOrder
��������:�����Զ����ڵĳɽ���Ϣ
�����߼�����:��� 2017.10.25
*********************************************************************/
bool CTfbTemplat::GetLoadTradeOrder(string sUserName, string sStartDate, string sEndDate)
{
	XJRspTradeInfo TradeMsg;
	map<string, vector<TfbLoadTrade>>::iterator it;
	bool bFindUserName = false;
	char cOrderNo[10];
	int nStartDate;
	int nEndDate;
	int nTradeDataTime;
	nStartDate = DatetoInt(sStartDate);
	nEndDate = DatetoInt(sEndDate);
	

	::EnterCriticalSection(&cs);
	for (it = m_LoadTradeOrder.begin(); it != m_LoadTradeOrder.end(); it++)
	{
		if (sUserName == it->first)
		{
			TradeMsg.strAccountId = it->first;
			for (int i = 0; i < it->second.size(); i++)
			{
				TradeMsg.strTradeDataTime = it->second.at(i).cTradeDataTime;
				nTradeDataTime = TimetoInt(TradeMsg.strTradeDataTime);
				if (nTradeDataTime >= nStartDate && nTradeDataTime <= nEndDate)
				{
					sprintf_s(cOrderNo, "%d", it->second.at(i).nOrderNo);
					TradeMsg.strOrderNo = cOrderNo;
					TradeMsg.strContrctNo = it->second.at(i).sContrctNo;
					TradeMsg.chOrderSide = it->second.at(i).chOrderSide;
					TradeMsg.chOffset = it->second.at(i).chOffset;
					TradeMsg.dMatchPrice = it->second.at(i).dMatchPrice;
					TradeMsg.nMatchVolume = it->second.at(i).nMatchVolume;
					TradeMsg.dFeeValue = it->second.at(i).dFeeValue;
					m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_TRADEINFO, &TradeMsg);
				}
				
			}
			bFindUserName = true;
		}
		if (bFindUserName)
		{
			break;
		}
	}
	::LeaveCriticalSection(&cs);

	return true;
}

/*********************************************************************
��������:PullOrderInfo
��������:�������Ƴ�Map,����ƽ̨���ͳ�����Ϣ
�����߼�����:��� 2017.10.20
*********************************************************************/
bool CTfbTemplat::PullOrderInfo(string sUserName, int nOrderID)
{
	map<string, vector<TFBApiOrder>>::iterator it;
	bool b_FindUserName = false;
	char cOrderNo[10];
	XJRspOrderInfo OrderMsg;

	::EnterCriticalSection(&cs);
	for (it = m_OrderMap.begin(); it != m_OrderMap.end(); it++)
	{
		if (sUserName == it->first)
		{
			b_FindUserName = true;
			for (int i = 0; i < it->second.size(); i++)
			{
				if (nOrderID == it->second.at(i).nOrderID)
				{
					sprintf_s(cOrderNo, "%d", it->second.at(i).nOrderID);
					OrderMsg.strAccountId = sUserName;
					OrderMsg.strOrderNo = cOrderNo;                         //ί�б��
					OrderMsg.strInsertDataTime = it->second.at(i).pszTime;       //ί��ʱ��
					OrderMsg.strContrctNo = it->second.at(i).pszMCode;           //��Լ����
					OrderMsg.dOrderPrice = it->second.at(i).dPrice;              //ί�м۸�
					OrderMsg.nOrderVolume = it->second.at(i).dNumber;            //ί������
					if (it->second.at(i).bIsBuy)                                 //����
					{
						OrderMsg.chOrderSide = '0';
					}
					else
					{
						OrderMsg.chOrderSide = '1';
					}
					if (it->second.at(i).bAdverse)
					{
						OrderMsg.chOffset = '1';
					}
					else
					{
						OrderMsg.chOffset = '0';
					}
					OrderMsg.chOrderstate = '1';
					OrderMsg.chCommodityType = '1';
					m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_CHANGE_ORDER, &OrderMsg);

					m_OrderMap[it->first].erase(it->second.begin() + i);
					break;
				}
			}
		}
		if (b_FindUserName)
		{
			break;
		}
	}
	::LeaveCriticalSection(&cs);
	return b_FindUserName;
}

/*********************************************************************
��������:ModifyOrderInfo
��������:���¶�����Ϣ
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::ModifyOrderInfo(string sUserName, int nOrderID)
{
	bool bFindUserName = false;
	char cOrderNo[10];
	XJRspOrderInfo OrderMsg;

	map<string, vector<TFBApiOrder>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_OrderMap.begin(); it != m_OrderMap.end(); it++)
	{
		if (sUserName == it->first)
		{
			bFindUserName = true;
			for (int i = 0; i < it->second.size(); i++)
			{
				if (nOrderID == it->second.at(i).nOrderID)
				{
					sprintf_s(cOrderNo, "%d", it->second.at(i).nOrderID);
					OrderMsg.strAccountId = sUserName;
					OrderMsg.strOrderNo = cOrderNo;                         //ί�б��
					OrderMsg.strInsertDataTime = it->second.at(i).pszTime;       //ί��ʱ��
					OrderMsg.strContrctNo = it->second.at(i).pszMCode;           //��Լ����
					OrderMsg.dOrderPrice = it->second.at(i).dPrice;              //ί�м۸�
					OrderMsg.nOrderVolume = it->second.at(i).dNumber;            //ί������
					if (it->second.at(i).bIsBuy)                                 //����
					{
						OrderMsg.chOrderSide = '0';
					}
					else
					{
						OrderMsg.chOrderSide = '1';
					}
					if (it->second.at(i).bAdverse)
					{
						OrderMsg.chOffset = '1';
					}
					else
					{
						OrderMsg.chOffset = '0';
					}
					it->second.at(i).nModeType = 9;
					OrderMsg.chOrderstate = '0';
					OrderMsg.chCommodityType = '1';
					m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_CHANGE_ORDER, &OrderMsg);
					break;
				}
			}	
		}
		if (bFindUserName)
		{
			break;
		}
	}

	::LeaveCriticalSection(&cs);
	return true;
}
/*********************************************************************
��������:ModifyPositionInfo
��������:ƽ��ʱ��Ҫ�ѳֲ���0��������
��    ��:sUserName---------�û���
		 sProductCode------��Լ����
		 dNumber-----------�ɽ�����
		 nIsBuy------------��������,��0,��1         
�����߼�����:��� 2017.10.24
*********************************************************************/
bool CTfbTemplat::ModifyPositionInfo(string sUserName, int nUserID, string sProductCode, double dNumber, int nIsBuy)
{
	XJRspAccountPosition PositionMsg;
	map<string, vector<TFBApiPosition>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_PositionMap.begin(); it != m_PositionMap.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			if (nUserID == it->second.at(i).nUserID
				&& strcmp(sProductCode.c_str(), it->second.at(i).pszTPmcode) == 0
				&& dNumber == it->second.at(i).dNumber
				&& nIsBuy != it->second.at(i).bIsBuy)
			{
				PositionMsg.strAccountId = sUserName;
				PositionMsg.strContractNo = it->second.at(i).pszTPmcode;
				PositionMsg.nPositions = 0;
				
				m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_FUNDACCOUNT_POSITION, &PositionMsg);

				m_PositionMap[it->first].erase(it->second.begin() + i);
			}
		}
	}
	::LeaveCriticalSection(&cs);
	return true;
}

/*********************************************************************
��������:ModifyLoadTradeOrder
��������:�û��ѳɽ��������ݸ���
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::ModifyLoadTradeOrder(string sUserName, TFBApiUpDateTrade *pUpdateTrade)
{
	bool bFindUserName = false;
	TfbLoadTrade TLoadTrade;
	map<string, vector<TfbLoadTrade>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_LoadTradeOrder.begin(); it != m_LoadTradeOrder.end(); it++)
	{
		if (sUserName == it->first)
		{
			bFindUserName = true;
			APIStrncpy(TLoadTrade.sUserName, it->first.c_str());
			TLoadTrade.nOrderNo = pUpdateTrade->nOrderId;
			APIStrncpy(TLoadTrade.cTradeDataTime, pUpdateTrade->pszTime);
			APIStrncpy(TLoadTrade.sContrctNo, pUpdateTrade->pszProduct);
			if (pUpdateTrade->nIsBuy == 1)
			{
				TLoadTrade.chOrderSide = '0';
			}
			if (pUpdateTrade->nIsBuy == 0)
			{
				TLoadTrade.chOrderSide = '1';
			}
			switch (pUpdateTrade->nAdverse)
			{
			case 0:TLoadTrade.chOffset = '0';
				break;
			case 1:TLoadTrade.chOffset = '1';
				break;
			case 2:TLoadTrade.chOffset = '2';
				break;
			default:TLoadTrade.chOffset = 'x';
				break;
			}
			TLoadTrade.dMatchPrice = pUpdateTrade->dPrice;
			TLoadTrade.nMatchVolume = pUpdateTrade->dNumber;
			m_LoadTradeOrder[sUserName].push_back(TLoadTrade);
			break;
		}
	}
	::LeaveCriticalSection(&cs);

	return true;
}


/*********************************************************************
��������:ClearOrderInfo
��������:���ĳ�û�������Ϣ
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::ClearOrderInfo(string sUserName)
{
	map<string, vector<TFBApiOrder>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_OrderMap.begin(); it != m_OrderMap.end(); it++)
	{
		if (it->first == sUserName)
		{
			m_OrderMap.erase(it);
			break;
		}
	}
	::LeaveCriticalSection(&cs);

	return true;
}
/*********************************************************************
��������:ClearOrderInfo
��������:���ĳ�û�������Ϣ
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::ClearUserInfo(string sUserName)
{
	string sUserFlag = GetUserFlag(sUserName);

	map<string, vector<AdminUserRsp_Trade>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_UserMap.begin(); it != m_UserMap.end(); it++)
	{
		if (it->first == sUserFlag)
		{
			m_UserMap.erase(it);
			break;
		}
	}

	::LeaveCriticalSection(&cs);
	return true;
}
/*********************************************************************
��������:ClearOrderInfo
��������:ClearUserInfofRespond
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::ClearUserInfofRespond(string sUserName)
{
	map<string, vector<TFBApiUserInforRespond>>::iterator it;
	::EnterCriticalSection(&cs);

	for (it = m_UserInforRespondMap.begin(); it != m_UserInforRespondMap.end(); it++)
	{
		if (it->first == sUserName)
		{
			m_UserInforRespondMap.erase(it);
			break;
		}
	}
	::LeaveCriticalSection(&cs);
	return true;
}

/*********************************************************************
��������:ClearLoadTradeOrder
��������:�û��˳�,����û���������
�����߼�����:��� 2017.10.23
*********************************************************************/
bool CTfbTemplat::ClearLoadTradeOrder(string sUserName)
{
	map<string, vector<TfbLoadTrade>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_LoadTradeOrder.begin(); it != m_LoadTradeOrder.end(); it++)
	{
		if (sUserName == it->first)
		{
			m_LoadTradeOrder.erase(it);
			break;
		}
	}
	::LeaveCriticalSection(&cs);
	return true;
}

/*********************************************************************
��������:PushCurPriceInfo
��������:��ƽ̨���ͳֲ�ӯ����Ϣ
�����߼�����:��� 2017.10.23
*********************************************************************/
double CTfbTemplat::PushCurPriceInfo(const tPriceData *pPriceDateInfo)
{
	double dPositionProfit = 0;
	XJRspFundAccountInfo FundMsg;                                    //�ʽ��˻���Ϣ
	map<string, vector<TFBApiPosition>>::iterator it;
	map<string, vector<TFBApiUserInforRespond>>::iterator itUser;

	::EnterCriticalSection(&cs);
	for (it = m_PositionMap.begin(); it != m_PositionMap.end(); it++)
	{
		FundMsg.strAccountId = it->first;
		for (itUser = m_UserInforRespondMap.begin(); itUser != m_UserInforRespondMap.end(); itUser++)
		{
			if (it->first == itUser->first)
			{
				for (int i = 0; i < it->second.size(); i++)
				{
					if (strcmp(pPriceDateInfo->mProdCode, it->second.at(i).pszTPmcode) == 0 && pPriceDateInfo->mCurPrice != it->second.at(i).dPrice)
					{
						if (it->second.at(i).bIsBuy)
						{
							dPositionProfit += (pPriceDateInfo->mCurPrice - it->second.at(i).dPrice)*it->second.at(i).dNumber*it->second.at(i).nMPAmount;
						}
						else
						{
							dPositionProfit += (it->second.at(i).dPrice - pPriceDateInfo->mCurPrice)*it->second.at(i).dNumber*it->second.at(i).nMPAmount;
						}
					}
				}
				for (int j = 0; j < itUser->second.size(); j++)
				{
					FundMsg.FrozenCash = itUser->second.at(j).dOutFreezingFunds
						+ itUser->second.at(j).dOrderFreezingFunds
						+ itUser->second.at(j).dPositionsFreezingFunds;

					FundMsg.PositionMargin = itUser->second.at(j).dPositionsFreezingFunds;
					FundMsg.dAvailable = itUser->second.at(j).dNowFunds - FundMsg.FrozenCash;
					FundMsg.PositionProfit = dPositionProfit;
					m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_FUNDACCOUNT, &FundMsg);
				}
				double dPositionProfit = 0;
			}
		}
	}

	::LeaveCriticalSection(&cs);
	return 0.0;
}

/*********************************************************************
��������:ClearPositionInfo
��������:���ĳ�û��ֲ�
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::ClearPositionInfo(string sUserName)
{
	map<string, vector<TFBApiPosition>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_PositionMap.begin(); it != m_PositionMap.end(); it++)
	{
		if (it->first == sUserName)
		{
			m_PositionMap.erase(it);
			break;
		}
	}
	::LeaveCriticalSection(&cs);

	return true;
}

/*********************************************************************
��������:PushUserInfo
��������:������û���Ϣ
�����߼�����:��� 2017.10.12
*********************************************************************/
bool CTfbTemplat::PushUserInfo(string sUserFlag, AdminUserRsp_Trade* pUserRsp)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "**�û���**:";
	msg.strMsg += pUserRsp->m_strUserName;
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	::EnterCriticalSection(&cs);
	m_UserMap[sUserFlag.c_str()].push_back(*pUserRsp);
	::LeaveCriticalSection(&cs);
	return true;
}

/*********************************************************************
��������:GetUserFlag
��������:���û��и���UserID��ȡ�û���ʶ
�����߼�����:��� 2017.10.18
*********************************************************************/
string CTfbTemplat::GetUserFlag(int nUserID)
{
	string sUserFlag;
	map<string, vector<AdminUserRsp_Trade>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_UserMap.begin(); it != m_UserMap.end(); it++)
	{
		if (it->second.size() >= 1)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				if (nUserID == it->second[i].m_nUserID)
				{
					sUserFlag = it->first;
				}
			}
		}
	}
	::LeaveCriticalSection(&cs);
	return sUserFlag;
}

/*********************************************************************
��������:GetUserFlag
��������:���û��и���UserID��ȡ�û���ʶ
�����߼�����:��� 2017.10.18
*********************************************************************/
string CTfbTemplat::GetUserFlag(string sUserName)
{
	string sUserFlag;
	map<string, vector<AdminUserRsp_Trade>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_UserMap.begin(); it != m_UserMap.end(); it++)
	{
		if (it->second.size() >= 1)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				if (strcmp(sUserName.c_str(), it->second[i].m_strUserName) == 0)
				{
					sUserFlag = it->first;
				}
			}
		}
	}

	::LeaveCriticalSection(&cs);
	return sUserFlag;
}

/*********************************************************************
��������:PushUserInfo
��������:���û��л�ȡ�û���
�����߼�����:��� 2017.10.18
*********************************************************************/
string CTfbTemplat::TfbGetUserName(int nUserID)
{
	string sUserName;
	map<string, vector<AdminUserRsp_Trade>>::iterator it;
	::EnterCriticalSection(&cs);
	for (it = m_UserMap.begin(); it != m_UserMap.end(); it++)
	{
		if (it->second.size() >= 1)
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				if (nUserID == it->second[i].m_nUserID)
				{
					sUserName = it->second[i].m_strUserName;
				}
			}
		}
	}
	::EnterCriticalSection(&cs);

	return sUserName;
}