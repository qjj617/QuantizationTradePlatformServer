/**********************************************************************
文件名:TfbTrade.h
功能和模块的目的:文件定义了天富宝国际交易系统的对外接口、函数和回调接口
开发者及日期:李宝鑫 2017.9.27
**********************************************************************/
#pragma once
#include "TfbTradeApi.h"                   //天富宝API头文件
#include "afxwin.h"
#include "../../protocol/XJIPlatformApi.h"      //平台回调接口头文件
#include "TfbTemplat.h"
#include "SimpleEvent.h"                   //事件控制

class CTfbTrade
{
public:
	CTfbTrade(PFNPLATFORMDATAPROC pfn);                           //构造函数
	~CTfbTrade();                          //析构函数
	static PFNPLATFORMDATAPROC m_pPlatformDataProc;

	HINSTANCE   m_hInstLibrary;
	//动态库初始化
	BOOL  IniLib();
	//获取天富宝接口函数地址
	BOOL  LoadFuncAddr();
	//加载回调
	BOOL  RegisterLibCallBack();

	static CTfbTemplat* m_pTfbTemplat;
	static double m_dPositionProfit;                  //实时持仓盈亏
	static double m_dFrozenCash;                      //冻结资金
	static double m_dPositionMargin;                  //持仓保证金
	static double m_dAvailable;                       //可用资金
	static int m_nUserNumber;                         //用户数量
	// 动态库函数指针
    static p_TFBAPI_Initialize                 myInit;                      //天富宝API初始化
	static p_TFBAPI_GetUserInfo                GetUserInfo;                 //获取用户信息
	static p_TFBAPI_LoadTradeReport            LoadTradeReport;             //获取最近一段时间的成交报告
	static p_TFBAPI_AddOrder                   AddOrder;                    //下单 
	static p_TFBAPI_DeleteOrder                DelOrder;                    //撤单
	static p_TFBAPI_SubscribePrice             SubscribePrice;              //行情订阅
	static p_TFBAPI_SetSourceAddress           SetSourceAddress;            //设置数据源IP
	static p_TFBAPI_LoadInstrumentList         LoadInstrumentList;          //加载商品系列
	static p_TFBAPI_GetInstrumentCount         GetInstrumentCount;          //获取商品系列个数
	static p_TFBAPI_GetInstrument              GetInstrument;               //获取商品信息(商品代码等),用于遍历
	static p_TFBAPI_LoadProductInfoListByCode  LoadProductInfoListByCode;   //根据商品代码加载该商品合约(合约代码)
	static p_TFBAPI_GetProductCount            GetProductCount;             //根据商品代码获取该商品合约代码个数
	static p_TFBAPI_GetProduct                 GetProduct;                  //遍历合约,根据商品代码获取该商品所有的合约代码

	p_TFBAPI_Uninitialize               myUninit;                        //释放天富宝API
	p_TFBAPI_GetUserFlag                GetUserFlag;                     //获取用户标识
	p_TFBAPI_Login                      Login;                           //用户登陆
	p_TFBAPI_Logout                     Logout;                          //用户登出

	p_TFBAPI_RegisterLoginReply          RegisterLoginRespond;           //注册登录回应
	p_TFBAPI_RegisterLogoutReply         RegisterLogoutRespond;          //注册登出回应
	p_TFBAPI_RegisterUserInfoReply       RegisterUserInfoRespond;        //注册获取用户信息回应
	p_TFBAPI_RegisterLoadTradeReport     RegisterLoadTradeReport;        //注册获取成交报告回应 
	p_TFBAPI_RegisterAddOrderReply       RegisterAddOrderRespond;        //注册下单回应
	p_TFBAPI_RegisterDelOrderReply       RegisterDelOrderRespond;        //注册撤单回应
	p_TFBAPI_RegisterApiPriceUpdate      RegisterApiPriceUpdate;         //注册行情订阅回应
	p_TFBAPI_RegisterUpdateTradeReply    RegisterUpdateTradeRespond;     //注册订单成交回应
	p_TFBAPI_RegisterInstrumentListReply RegisterInstrumentListRespond;  //注册获取商品系列信息回应																  
	p_TFBAPI_RegisterProductListReply    RegisterProductListRespond;     //注册获取合约代码等信息的回应
	//登陆回调
	static void TFBDLLCALL LoginReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoginRespond* Respond);
	//登出回调
	static void TFBDLLCALL LogoutReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, char* pszMsg);
	//获取用户信息回调
	static void TFBDLLCALL UserInfoReply(AdminUserRsp_Trade* pUserRsp, TFBApiUserInforRespond* Respond);
	//获取成交报告回调
	static void TFBDLLCALL LoadTradeReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoadTradeRespond* Respond);
	//下单回调
	static void TFBDLLCALL AddOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg, char* pszRefID);
	//撤单回调
	static void TFBDLLCALL DelOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg);
	//订阅行情回调
	static void TFBDLLCALL ApiPriceUpdate(const tPriceData *price);
	//订单成交回调
	static void TFBDLLCALL UpdateTrade(AdminUserRsp_Trade* pUserRsp, TFBApiUpDateTrade* Respond);
	//获取商品系列回调
	static void TFBDLLCALL InstrumentListReply(int nRetCode, const char* pszMsg);
	//获取合约信息的回调
	static void TFBDLLCALL ProductListByCodeReply(const char* pszProductCode, int nRetCode, const char* pszMsg);
};