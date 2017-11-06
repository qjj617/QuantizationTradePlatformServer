/**********************************************************************
文件名:TfbTemplat.h
功能和模块的目的:文件定义了天富宝国际交易系统模板类
开发者及日期:李宝鑫 2017.10.10
**********************************************************************/
#pragma once
#include <vector>
#include "TfbTradeApi.h"
#include "windows.h"
#include "../../protocol/XJIPlatformApi.h"      //平台回调接口头文件
#include <string>
#include "TfbCommon.h"

struct TfbLoadTrade
{
	//用户名
	STR64 sUserName;
	//订单号
	int nOrderNo;
	//成交时间
	STR64 cTradeDataTime;
	//合约
	STR16 sContrctNo;
	//买卖
	char chOrderSide;
	//平开标志
	char chOffset;
	//成交价格
	double dMatchPrice;
	//成交数量
	int nMatchVolume;
	//手续费
	double dFeeValue;
};

class CTfbTemplat
{
public:
	CTfbTemplat(PFNPLATFORMDATAPROC pfn);
	~CTfbTemplat();

//多用户开发
	double PushCurPriceInfo(const tPriceData *pPriceDateInfo);//根据行情计算浮动盈亏
	bool PushUserInfo(string sUserFlag, AdminUserRsp_Trade* pUserRsp);
	string GetUserFlag(int nUserID);      //根据UserID获取UserFlag
	string GetUserFlag(string sUserName); //根据UserName获取UserFlag
	string TfbGetUserName(int nUserID);   //根据UserID获取用户名
	bool PushPositionInfo(string sUserName, TFBApiPosition *pPositionInfo);
	bool PushOrderInfo(string sUserName, TFBApiOrder* pOrderInfo);
	bool ModifyOrderInfo(string sUserName, int nOrderID);           //修改订单状态
	//订单成交时根据持仓ID修改持仓量(平仓时需要把持仓量0发给界面,用户信息里由于已平仓不会有平仓商品的持仓量)
	bool ModifyPositionInfo(string sUserName, int  nUserID, string sProductCode, double dNumber, int nIsBuy);
	bool PullOrderInfo(string sUserName, int nOrderID);             //撤单
	bool ClearPositionInfo(string sUserName);                       //清空某用户持仓
	bool ClearOrderInfo(string sUserName);                          //清空某用户订单
	bool ClearUserInfo(string sUserName);                           //清空某用户数据

	bool PushUserInforRespond(string sUserName, TFBApiUserInforRespond *pUserInforRespond);
	bool ClearUserInfofRespond(string sUserName);                   //清空用户回调数据

	bool PushLoadTradeOrder(string sUserName, TFBApiLoadTrade *pLoadTrade);//加载成交订单信息
	bool GetLoadTradeOrder(string sUserName, string sStartDate, string sEndDate); //推送制定起止日期成交订单
	bool ClearLoadTradeOrder(string sUserName);//清空某用户已成交订单数据
	bool ModifyLoadTradeOrder(string sUserName, TFBApiUpDateTrade *pUpdateTrade); //新成交订单添加
public:
	PFNPLATFORMDATAPROC  m_pPlatformDataProc;
private:
	CRITICAL_SECTION cs;
	
	map <string, vector<AdminUserRsp_Trade>> m_UserMap;
	map <string, vector<TFBApiPosition>> m_PositionMap;
	map <string, vector<TFBApiOrder>> m_OrderMap;
	map <string, vector<TFBApiUserInforRespond>> m_UserInforRespondMap;
	map <string, vector<TfbLoadTrade>> m_LoadTradeOrder;

	double dPositionProfit;
};