/**********************************************************************
文件名:TfbPlatform.cpp
功能和模块的目的:文件实现了天富宝国际交易系统的对外接口、函数和回调接口
开发者及日期:李宝鑫 2017.9.27
**********************************************************************/
#include"TfbPlatform.h"
#include "../../Common/Common.h"

/*********************************************************************
函数名称:CTfbPlatform
函数功能:构造函数创建对象时初始化对象
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
char g_cUserFlag[60];//用户标识
extern SimpleEvent    g_PlatformEvent;
extern SimpleEvent    g_Event;
CTfbPlatform::CTfbPlatform(PFNPLATFORMDATAPROC pfn) :IPlatformApi(pfn), TfbTrade(m_pPlatformDataProc)
{
	
}

/*********************************************************************
函数名称:~CTfbPlatform
函数功能:析构函数释放对象所占用的资源
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
CTfbPlatform::~CTfbPlatform()
{

}

//初始化平台															   													  
void CTfbPlatform::InitializePlatform()
{
	string sUserFlag;
	TFBApiLoginInfo tApiLgoin;
	TfbTrade.IniLib();
	sUserFlag = TfbTrade.GetUserFlag("xmnX2054 ", "120.27.108.72", 9403);
	memset(&tApiLgoin, 0, sizeof(TFBApiLoginInfo));
	APIStrncpy(tApiLgoin.pszIP, "120.27.108.72");
	tApiLgoin.nPort = 9403;
	APIStrncpy(tApiLgoin.pszUserName, "xmnX2054");
	APIStrncpy(tApiLgoin.pszPassWord, "123456");
	tApiLgoin.nLoginType = 2;
	tApiLgoin.bAutoRelogin = FALSE;
	APIStrncpy(tApiLgoin.pszClientVer, "");

	TfbTrade.Login(sUserFlag.c_str(), tApiLgoin);

	g_PlatformEvent.WaitEvent();

	if (g_PlatformEvent.m_bLogin)
	{
		TfbTrade.Logout(sUserFlag.c_str());
		g_Event.WaitEvent();
	}
}
//登录一个交易账户
void CTfbPlatform::Login(const string& userID, const string& password, bool b_t, bool b_n, bool bSimulate)
{
	/*CString csUserFlag;

	csUserFlag = TfbTrade.GetUserFlag(userID.c_str(), "120.27.108.72", 9403);
	TcharToChar(csUserFlag, g_cUserFlag);*/
	const char *pUserFlag = TfbTrade.GetUserFlag(userID.c_str(), "120.27.108.72", 9403);
	strcpy_s(g_cUserFlag, pUserFlag);
	
	TFBApiLoginInfo tApiLgoin;
	memset(&tApiLgoin, 0, sizeof(TFBApiLoginInfo));
	APIStrncpy(tApiLgoin.pszIP, "120.27.108.72");
	tApiLgoin.nPort = 9403;
	APIStrncpy(tApiLgoin.pszUserName, userID.c_str());
	APIStrncpy(tApiLgoin.pszPassWord, password.c_str());
	tApiLgoin.nLoginType = 2;
	tApiLgoin.bAutoRelogin = FALSE;
	APIStrncpy(tApiLgoin.pszClientVer, "");

	TfbTrade.Login(g_cUserFlag, tApiLgoin);
}
//查询资金账号
void CTfbPlatform::QueryTradeAccount(const string& userID)
{

}
//登出一个交易账户
void CTfbPlatform::Logout(const string& userID)
{
	string sUserFlag;
	sUserFlag = TfbTrade.m_pTfbTemplat->GetUserFlag(userID);
	TfbTrade.Logout(sUserFlag.c_str());

	g_Event.WaitEvent();

	if (g_Event.m_bLogout)
	{
		TfbTrade.m_pTfbTemplat->ClearOrderInfo(userID);
		TfbTrade.m_pTfbTemplat->ClearPositionInfo(userID);
		TfbTrade.m_pTfbTemplat->ClearUserInfo(userID);
		TfbTrade.m_pTfbTemplat->ClearUserInfofRespond(userID);
		TfbTrade.m_pTfbTemplat->ClearLoadTradeOrder(userID);
	}
}
//登出所有交易账户
void CTfbPlatform::LogoutAll()
{

}
//新建委托
void CTfbPlatform::InsertOrder(const string& userID, const string& contract,
	char buy_or_sell, char open_or_cover, int order_num, double order_price)
{
	string sUserFlag = TfbTrade.m_pTfbTemplat->GetUserFlag(userID);
	TFBApiAddOrder Order;
	memset(&Order, 0, sizeof(TFBApiAddOrder));

	APIStrncpy(Order.pszProdcode, contract.c_str());
	if (buy_or_sell == '0')
	{
		Order.bIsBuy = true;
	}
	if (buy_or_sell == '1')
	{
		Order.bIsBuy = false;
	}

	Order.nNumberOfHand = order_num;
	Order.nOrderType = OD_PENDING;
	Order.nStopType = ST_NODEFINE;                   // 非止损单
	Order.nPID = 0;									 // 非平仓单
	Order.nType = OT_USERORDER;						 // 用户订单
	Order.fPrice = order_price;                      // 订单价格
	Order.fStopLevel = 0;                            // 止损价格
	APIStrncpy(Order.pszRefId, "TestRefID");         // 引用ID

	TfbTrade.AddOrder(sUserFlag.c_str(), &Order);
}
//撤消委托
void CTfbPlatform::CancelOrder(const string& userID, const string &OrderSysID, const string &ExchangeID)
{
	string sUserFlag = TfbTrade.m_pTfbTemplat->GetUserFlag(userID);
	int nOrderCode = atoi(OrderSysID.c_str());

	TfbTrade.DelOrder(sUserFlag.c_str(), nOrderCode);
}
//查询持仓(汇总)
void CTfbPlatform::QueryPostion(const string& userID, const string& contract)
{

}
//查询持仓明细
void CTfbPlatform::QueryPostionDetail(const string& userID, const string& contract)
{
	
}

//查询成交信息,可指定起始日期，日期为空时默认为当日成交信息
void CTfbPlatform::QueryTrade(const string& userID, const string& strStartDate, const string& strEndDate)
{
	TfbTrade.m_pTfbTemplat->GetLoadTradeOrder(userID, strStartDate, strEndDate);
}

//重启策略
void CTfbPlatform::RestartStrategy(const string& userID, const string& strategyID)
{

}
//关闭策略
void CTfbPlatform::CloseStrategy(const string& userID, const string& strategyID)
{

}

