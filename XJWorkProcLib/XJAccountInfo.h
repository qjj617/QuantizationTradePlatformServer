#pragma once
#include "../protocol/XJplatform_callbck_push_protocol.h"
#include "../Common/Common.h"
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

class CAccountInfo
{
public:
	CAccountInfo();
	~CAccountInfo();

	//设置资金账户信息
	void SetAccountInfo(XJRspFundAccountInfo *pAccountInfo);
	//设置登入信息
	void SetLoginInfo(XJRspLoginInfo *pLoginInfo);
	//设置平台类型
	void SetPlatformType(PLATFORM_TYPE pfType);
	//查询平台类型
	PLATFORM_TYPE GetPlatformType();
	//增加策略信息
	void AddStrategyInfo(XJRspAccountStrategyInfo *pStrategyInfo);
	//删除策略信息
	void DeleteStrategyInfo(XJRspAccountStrategyInfo *pStrategyInfo);
	//增加持仓信息
	void AddPositionInfo(XJRspAccountPosition *pPositionInfo);
	//删除持仓信息
	void DeletePositionInfo(XJRspAccountPosition *pPositionInfo);
	//增加委托信息
	void AddOrderInfo(XJRspOrderInfo *pOrderInfo);
	//删除委托信息
	void DeleteOrderInfo(XJRspOrderInfo *pOrderInfo);
	//增加成交信息
	void AddTradeInfo(XJRspTradeInfo *pTradeInfo);
	//删除成交信息
	void DeleteTradeInfo(XJRspTradeInfo *pTradeInfo);
	//查询登入信息
	const XJRspLoginInfo* GetLoginInfo();
	//查询资金账户信息
	const XJRspFundAccountInfo* GetAccountInfo();
	//查询策略信息
	const list<XJRspAccountStrategyInfo *>& GetStrategyInfos();
	//查询持仓信息
	const list<XJRspAccountPosition *>& GetPositionInfos();
	//根据合约号查找持仓信息
	XJRspAccountPosition *GetPositionInfoByContractNo(const string &strContractNo);
	//根据合约号设置持仓信息
	void SetPositionInfoByContractNo(const string &strContractNo, XJRspAccountPosition *pPositionInfo);
	//查询委托信息
	const list<XJRspOrderInfo*>& GetOrderInfos();
	//根据委托编号查找委托信息
	XJRspOrderInfo* GetOrderInfosByOrderNo(const string &strOrderNo);
	//根据委托编号设置委托信息
	void SetOrderInfosByOrderNo(const string &strOrderNo, XJRspOrderInfo* pOrderInfo);
	//根据委托编号设置成交信息
	void SetTradeInfoByOrderNo(const string &strOrderNo, XJRspTradeInfo *pTradeInfo);
	//判断成交信息是否在成交信息集合中
	bool IsInTradeInfolist(const string &strOrderNo);
	//查询成交信息
	const list<XJRspTradeInfo*>& GetTradeInfos();

private:
	PLATFORM_TYPE m_PlatformType;
	//账户登入信息
	XJRspLoginInfo* m_pLoginInfo;
	//资金账户信息
	XJRspFundAccountInfo* m_pAccountInfo;
	//策略信息集合
	list<XJRspAccountStrategyInfo *> m_StrategyInfos_list;
	//持仓信息集合
	list<XJRspAccountPosition *> m_PositionsInfos_list;
	//委托信息集合
	list<XJRspOrderInfo*> m_OrderInfos_list;
	//成交信息集合
	list<XJRspTradeInfo*> m_TradeInfos_list;
};

