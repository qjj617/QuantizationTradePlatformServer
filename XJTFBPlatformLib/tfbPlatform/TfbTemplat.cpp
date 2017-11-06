/**********************************************************************
文件名:TfbTemplat.cpp
功能和模块的目的:文件实现了天富宝国际交易系统模板类
开发者及日期:李宝鑫 2017.10.10
**********************************************************************/
#include "TfbTemplat.h"

extern char g_cUserFlag[60];
/*********************************************************************
函数名称:CTfTemplat
函数功能:构造函数创建对象时初始化对象
开发者及日期:李宝鑫 2017.10.10
*********************************************************************/
CTfbTemplat::CTfbTemplat(PFNPLATFORMDATAPROC pfn) : m_pPlatformDataProc(pfn)
{
	::InitializeCriticalSection(&cs);
	dPositionProfit = 0.0;
}

/*********************************************************************
函数名称:~CTfTemplat
函数功能:析构函数释放对象所占用的资源
开发者及日期:李宝鑫 2017.10.10
*********************************************************************/
CTfbTemplat::~CTfbTemplat()
{
	::DeleteCriticalSection(&cs);
}

/*********************************************************************
函数名称:PushPositionInfo
函数功能:持仓数据存入map容器及向界面推送
开发者及日期:李宝鑫 2017.10.10
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
					bFindTPmcode = true;//同一用户,合约代码在vector里面,且买卖方向相同

					if (it->second.at(i).dNumber == pPositionInfo->dNumber) //持仓数相同,无需推送持仓更新,退出第二层循环
					{
						break;
					}
					else   //持仓数不同,需更新持仓数,且向平台推送, 修改完毕,退出第二层循环
					{
						it->second.at(i).dNumber = pPositionInfo->dNumber;
						it->second.at(i).dPrice = pPositionInfo->dPrice;

						PositionMsg.strContractNo = pPositionInfo->pszTPmcode; //合约代码对应商品码
						PositionMsg.nPositions = pPositionInfo->dNumber;       //总持仓对应持仓手数
						PositionMsg.dOpenAveragePrice = pPositionInfo->dPrice;    //持仓均价是成交均价?
						if (pPositionInfo->bIsBuy)
						{
							PositionMsg.chOrderSide = '0';         //??
						}
						else
						{
							PositionMsg.chOrderSide = '1';         //??
						}
						PositionMsg.dMargin = pPositionInfo->dMargin;          //保证金
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
		if (bFindUserName)//已找到用户名,退出第一层循环
		{
			break;
		}
	}
	if (!bFindTPmcode)//没找到合约代码,插入
	{
		m_PositionMap[sUserName].push_back(*pPositionInfo);

		PositionMsg.strContractNo = pPositionInfo->pszTPmcode; //合约代码对应商品码
		PositionMsg.nPositions = pPositionInfo->dNumber;       //总持仓对应持仓手数
		PositionMsg.dOpenAveragePrice = pPositionInfo->dPrice;    //持仓均价是成交均价?
		if (pPositionInfo->bIsBuy)
		{
			PositionMsg.chOrderSide = '0';         
		}
		else
		{
			PositionMsg.chOrderSide = '1';         
		}
		PositionMsg.dMargin = pPositionInfo->dMargin;          //保证金
		PositionMsg.chCommodityType = '1';
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_FUNDACCOUNT_POSITION, &PositionMsg);
	}

	::LeaveCriticalSection(&cs);

	return bFindTPmcode;
}

/*********************************************************************
函数名称:PushUserInforRespond
函数功能:保存多用户回调信息
开发者及日期:李宝鑫 2017.10.23
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
函数名称:PushOrderInfo
函数功能:订单数据存入map容器,往平台推送订单信息
开发者及日期:李宝鑫 2017.10.20
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
		OrderMsg.strOrderNo = cOrderNo;                         //委托编号
		OrderMsg.strInsertDataTime = pOrderInfo->pszTime;       //委托时间
		OrderMsg.strContrctNo = pOrderInfo->pszMCode;           //合约代码
		OrderMsg.dOrderPrice = pOrderInfo->dPrice;              //委托价格
		OrderMsg.nOrderVolume = pOrderInfo->dNumber;            //委托数量
		if (pOrderInfo->bIsBuy)                                 //买卖
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
函数名称:PushLoadTradeOrder
函数功能:加载成交订单
开发者及日期:李宝鑫 2017.10.25
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
函数名称:GetLoadTradeOrder
函数功能:推送自定日期的成交信息
开发者及日期:李宝鑫 2017.10.25
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
函数名称:PullOrderInfo
函数功能:将撤单移除Map,且向平台推送撤单信息
开发者及日期:李宝鑫 2017.10.20
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
					OrderMsg.strOrderNo = cOrderNo;                         //委托编号
					OrderMsg.strInsertDataTime = it->second.at(i).pszTime;       //委托时间
					OrderMsg.strContrctNo = it->second.at(i).pszMCode;           //合约代码
					OrderMsg.dOrderPrice = it->second.at(i).dPrice;              //委托价格
					OrderMsg.nOrderVolume = it->second.at(i).dNumber;            //委托数量
					if (it->second.at(i).bIsBuy)                                 //买卖
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
函数名称:ModifyOrderInfo
函数功能:更新订单信息
开发者及日期:李宝鑫 2017.10.12
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
					OrderMsg.strOrderNo = cOrderNo;                         //委托编号
					OrderMsg.strInsertDataTime = it->second.at(i).pszTime;       //委托时间
					OrderMsg.strContrctNo = it->second.at(i).pszMCode;           //合约代码
					OrderMsg.dOrderPrice = it->second.at(i).dPrice;              //委托价格
					OrderMsg.nOrderVolume = it->second.at(i).dNumber;            //委托数量
					if (it->second.at(i).bIsBuy)                                 //买卖
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
函数名称:ModifyPositionInfo
函数功能:平仓时需要把持仓量0发给界面
参    数:sUserName---------用户名
		 sProductCode------合约代码
		 dNumber-----------成交手数
		 nIsBuy------------买卖方向,卖0,买1         
开发者及日期:李宝鑫 2017.10.24
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
函数名称:ModifyLoadTradeOrder
函数功能:用户已成交订单数据更新
开发者及日期:李宝鑫 2017.10.12
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
函数名称:ClearOrderInfo
函数功能:清空某用户订单信息
开发者及日期:李宝鑫 2017.10.12
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
函数名称:ClearOrderInfo
函数功能:清空某用户订单信息
开发者及日期:李宝鑫 2017.10.12
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
函数名称:ClearOrderInfo
函数功能:ClearUserInfofRespond
开发者及日期:李宝鑫 2017.10.12
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
函数名称:ClearLoadTradeOrder
函数功能:用户退出,清空用户订单数据
开发者及日期:李宝鑫 2017.10.23
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
函数名称:PushCurPriceInfo
函数功能:往平台推送持仓盈亏信息
开发者及日期:李宝鑫 2017.10.23
*********************************************************************/
double CTfbTemplat::PushCurPriceInfo(const tPriceData *pPriceDateInfo)
{
	double dPositionProfit = 0;
	XJRspFundAccountInfo FundMsg;                                    //资金账户信息
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
函数名称:ClearPositionInfo
函数功能:清空某用户持仓
开发者及日期:李宝鑫 2017.10.12
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
函数名称:PushUserInfo
函数功能:保存多用户信息
开发者及日期:李宝鑫 2017.10.12
*********************************************************************/
bool CTfbTemplat::PushUserInfo(string sUserFlag, AdminUserRsp_Trade* pUserRsp)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "**用户名**:";
	msg.strMsg += pUserRsp->m_strUserName;
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	::EnterCriticalSection(&cs);
	m_UserMap[sUserFlag.c_str()].push_back(*pUserRsp);
	::LeaveCriticalSection(&cs);
	return true;
}

/*********************************************************************
函数名称:GetUserFlag
函数功能:多用户中根据UserID获取用户标识
开发者及日期:李宝鑫 2017.10.18
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
函数名称:GetUserFlag
函数功能:多用户中根据UserID获取用户标识
开发者及日期:李宝鑫 2017.10.18
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
函数名称:PushUserInfo
函数功能:多用户中获取用户名
开发者及日期:李宝鑫 2017.10.18
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