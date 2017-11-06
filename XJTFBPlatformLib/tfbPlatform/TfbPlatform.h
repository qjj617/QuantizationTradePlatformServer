/**********************************************************************
文件名:TfbPlatform.h
功能和模块的目的:文件定义了天富宝国际交易系统的对外接口、函数和回调接口
开发者及日期:李宝鑫 2017.9.27
**********************************************************************/
#pragma once

#include "../../protocol/XJIPlatformApi.h"      //平台回调接口头文件
#include "TfbTrade.h"
#include "TfbTradeApi.h"                   //天富宝API头文件

/**********************************************************************
类名:CTfbPlatform
功能:天富宝对IPlatformApi的实现及天富宝系统对外接口、函数和回调实现
接口说明:
开发者及日期:李宝鑫 2017.9.27
**********************************************************************/
class CTfbPlatform :public IPlatformApi
{
private:
	CTfbPlatform(PFNPLATFORMDATAPROC pfn);                     //构造函数.私有,防止被手动构造对象

	HINSTANCE   m_hInstLibrary;

public:
	static CTfbPlatform& TheCTfbPlatform(PFNPLATFORMDATAPROC pfn) 
	{
		static CTfbPlatform tfb_platform(pfn);
		return tfb_platform;
	}
	~CTfbPlatform();                                           //析构函数
	CTfbPlatform(const CTfbPlatform&) = delete;                //禁止拷贝构造
	CTfbPlatform& operator = (const CTfbPlatform&) = delete;   //禁止

	//初始化平台															   													  
	void InitializePlatform();
	//登录一个交易账户
	void Login(const string& userID, const string& password, bool b_t = false, bool b_n = false, bool bSimulate = false);
	//查询资金账号
	void QueryTradeAccount(const string& userID);
	//登出一个交易账户
	void Logout(const string& userID);
	//登出所有交易账户
	void LogoutAll();
	//新建委托
	void InsertOrder(const string& userID, const string& contract,
		char buy_or_sell, char open_or_cover, int order_num, double order_price = 0.0);
	//撤消委托
	void CancelOrder(const string& userID, const string &OrderSysID, const string &ExchangeID);
	//查询持仓(汇总)
	void QueryPostion(const string& userID, const string& contract = "");
	//查询持仓明细
	void QueryPostionDetail(const string& userID, const string& contract = "");
	//查询成交信息,可指定起始日期，日期为空时默认为当日成交信息
	void QueryTrade(const string& userID, const string& strStartDate = "", const string& strEndDate = "");
	//重启策略
	void RestartStrategy(const string& userID, const string& strategyID);
	//关闭策略
	void CloseStrategy(const string& userID, const string& strategyID);

	CTfbTrade TfbTrade;
};


