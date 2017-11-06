/**********************************************************************
文件名:TfbPlatform.cpp
功能和模块的目的:文件实现了天富宝国际交易系统的对外接口、函数和回调接口
开发者及日期:李宝鑫 2017.9.27
**********************************************************************/
#include "TfbTrade.h"
#include "afxwin.h"
#include <sstream>
#include <stdlib.h>
#include "../../Common/Common.h"
#include "../../Common/LeeDateTime.h"
#include "TfbTemplat.h"

extern char g_cUserFlag[60];
SimpleEvent    g_Event;
SimpleEvent    g_PlatformEvent;
PFNPLATFORMDATAPROC          CTfbTrade::m_pPlatformDataProc = NULL;
p_TFBAPI_Initialize          CTfbTrade::myInit = NULL;
p_TFBAPI_GetUserInfo         CTfbTrade::GetUserInfo = NULL;
p_TFBAPI_LoadTradeReport     CTfbTrade::LoadTradeReport = NULL;
p_TFBAPI_AddOrder            CTfbTrade::AddOrder = NULL;
p_TFBAPI_DeleteOrder         CTfbTrade::DelOrder = NULL;
p_TFBAPI_SubscribePrice      CTfbTrade::SubscribePrice = NULL;
p_TFBAPI_SetSourceAddress    CTfbTrade::SetSourceAddress = NULL;
p_TFBAPI_LoadInstrumentList  CTfbTrade::LoadInstrumentList = NULL;
p_TFBAPI_GetInstrumentCount  CTfbTrade::GetInstrumentCount = NULL;
p_TFBAPI_GetInstrument       CTfbTrade::GetInstrument = NULL;
p_TFBAPI_LoadProductInfoListByCode  CTfbTrade::LoadProductInfoListByCode = NULL;
p_TFBAPI_GetProductCount     CTfbTrade::GetProductCount = NULL;
p_TFBAPI_GetProduct          CTfbTrade::GetProduct = NULL;

CTfbTemplat* CTfbTrade::m_pTfbTemplat = NULL;

double CTfbTrade::m_dPositionProfit = 0.0;
double CTfbTrade::m_dFrozenCash = 0.0;                      //冻结资金
double CTfbTrade::m_dPositionMargin = 0.0;                  //持仓保证金
double CTfbTrade::m_dAvailable = 0.0;                       //可用资金
int CTfbTrade::m_nUserNumber = 0;
/*********************************************************************
函数名称:CTfbTrade
函数功能:构造函数创建对象时初始化对象
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
CTfbTrade::CTfbTrade(PFNPLATFORMDATAPROC pfn)
{
	myUninit = NULL;
	GetUserFlag = NULL;
	Login = NULL;
	Logout = NULL;
	m_pPlatformDataProc = pfn;
	m_pTfbTemplat = new CTfbTemplat(pfn);
}

/*********************************************************************
函数名称:~CTfbPlatform
函数功能:析构函数释放对象所占用的资源
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
CTfbTrade::~CTfbTrade()
{
	if (NULL != m_pTfbTemplat)
	{
		delete m_pTfbTemplat;
		m_pTfbTemplat = NULL;
	}
}

/*********************************************************************
函数名称:IniLib
函数功能:动态库初始化
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
BOOL  CTfbTrade::IniLib()
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	m_hInstLibrary = LoadLibrary(_T("TfbTradeApi.dll"));
	if (NULL == m_hInstLibrary)
	{
		msg.strMsg = "加载动态库TfbTradeApi.dll失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	}
	if (!LoadFuncAddr())
	{
		return FALSE;
	}
	if (0 != myInit(TRUE))
	{
		msg.strMsg = "动态库初始化错误";
		//	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}

	RegisterLibCallBack();

	return TRUE;
}

/*********************************************************************
函数名称:LoadFuncAddr
函数功能:获取天富宝接口函数地址
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
BOOL  CTfbTrade::LoadFuncAddr()
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;

	myInit = (p_TFBAPI_Initialize)GetProcAddress(m_hInstLibrary, "TFBAPI_Initialize");
	if (NULL == myInit)
	{
		msg.strMsg = "获取Init函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	myUninit = (p_TFBAPI_Uninitialize)GetProcAddress(m_hInstLibrary, "TFBAPI_Uninitialize");
	if (NULL == myUninit)
	{
		msg.strMsg = "获取myUninit函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	GetUserFlag = (p_TFBAPI_GetUserFlag)GetProcAddress(m_hInstLibrary, "TFBAPI_GetUserFlag");
	if (NULL == GetUserFlag)
	{
		msg.strMsg = "获取GetUserFlag函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	Login = (p_TFBAPI_Login)GetProcAddress(m_hInstLibrary, "TFBAPI_Login");
	if (NULL == Login)
	{
		msg.strMsg = "获取Login函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	Logout = (p_TFBAPI_Logout)GetProcAddress(m_hInstLibrary, "TFBAPI_Logout");
	if (NULL == Logout)
	{
		msg.strMsg = "获取Logout函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}

	GetUserInfo = (p_TFBAPI_GetUserInfo)GetProcAddress(m_hInstLibrary, "TFBAPI_GetUserInfo");
	if (NULL == GetUserInfo)
	{
		msg.strMsg = "获取GetUserInfo函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	LoadTradeReport = (p_TFBAPI_LoadTradeReport)GetProcAddress(m_hInstLibrary, "TFBAPI_LoadTradeReport");
	if (NULL == LoadTradeReport)
	{
		msg.strMsg = "获取LoadTradeReport函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	AddOrder = (p_TFBAPI_AddOrder)GetProcAddress(m_hInstLibrary, "TFBAPI_AddOrder");
	if (NULL == AddOrder)
	{
		msg.strMsg = "获取AddOrder函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	DelOrder = (p_TFBAPI_DeleteOrder)GetProcAddress(m_hInstLibrary, "TFBAPI_DeleteOrder");
	if (NULL == DelOrder)
	{
		msg.strMsg = "获取DelOrder函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	SubscribePrice = (p_TFBAPI_SubscribePrice)GetProcAddress(m_hInstLibrary, "TFBAPI_SubscribePrice");
	if (NULL == SubscribePrice)
	{
		msg.strMsg = "获取SubscribePrice函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	SetSourceAddress = (p_TFBAPI_SetSourceAddress)GetProcAddress(m_hInstLibrary, "TFBAPI_SetSourceAddress");
	if (NULL == SetSourceAddress)
	{
		msg.strMsg = "获取SetSourceAddress函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	LoadInstrumentList = (p_TFBAPI_LoadInstrumentList)GetProcAddress(m_hInstLibrary, "TFBAPI_LoadInstrumentList");
	if (NULL == LoadInstrumentList)
	{
		msg.strMsg = "获取LoadInstrumentList函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetInstrumentCount = (p_TFBAPI_GetInstrumentCount)GetProcAddress(m_hInstLibrary, "TFBAPI_GetInstrumentCount");
	if (NULL == GetInstrumentCount)
	{
		msg.strMsg = "获取GetInstrumentCount函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetInstrument = (p_TFBAPI_GetInstrument)GetProcAddress(m_hInstLibrary, "TFBAPI_GetInstrument");
	if (NULL == GetInstrument)
	{
		msg.strMsg = "获取GetInstrument函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	LoadProductInfoListByCode = (p_TFBAPI_LoadProductInfoListByCode)GetProcAddress(m_hInstLibrary, "TFBAPI_LoadProductInfoListByCode");
	if (NULL == LoadProductInfoListByCode)
	{
		msg.strMsg = "获取GetInstrument函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetProductCount = (p_TFBAPI_GetProductCount)GetProcAddress(m_hInstLibrary, "TFBAPI_GetProductCount");
	if (NULL == GetProductCount)
	{
		msg.strMsg = "获取GetInstrument函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetProduct = (p_TFBAPI_GetProduct)GetProcAddress(m_hInstLibrary, "TFBAPI_GetProduct");
	if (NULL == GetProduct)
	{
		msg.strMsg = "获取GetProduct函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}

	RegisterLoginRespond = (p_TFBAPI_RegisterLoginReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterLoginReply");
	if (NULL == RegisterLoginRespond)
	{
		msg.strMsg = "获取RegisterLoginRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterLogoutRespond = (p_TFBAPI_RegisterLogoutReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterLogoutReply");
	if (NULL == RegisterLogoutRespond)
	{
		msg.strMsg = "获取RegisterLogoutRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}

	RegisterUserInfoRespond = (p_TFBAPI_RegisterUserInfoReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterUserInfoReply");
	if (NULL == RegisterUserInfoRespond)
	{
		msg.strMsg = "获取RegisterUserInfoRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterLoadTradeReport = (p_TFBAPI_RegisterLoadTradeReport)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterLoadTradeReport");
	if (NULL == RegisterLoadTradeReport)
	{
		msg.strMsg = "获取RegisterLoadTradeReport函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterAddOrderRespond = (p_TFBAPI_RegisterAddOrderReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterAddOrderReply");
	if (NULL == RegisterAddOrderRespond)
	{
		msg.strMsg = "获取RegisterAddOrderRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	RegisterDelOrderRespond = (p_TFBAPI_RegisterDelOrderReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterDelOrderReply");
	if (NULL == RegisterDelOrderRespond)
	{
		msg.strMsg = "获取RegisterDelOrderRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterApiPriceUpdate = (p_TFBAPI_RegisterApiPriceUpdate)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterApiPriceUpdate");
	if (NULL == RegisterApiPriceUpdate)
	{
		msg.strMsg = "获取RegisterApiPriceUpdate函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterUpdateTradeRespond = (p_TFBAPI_RegisterUpdateTradeReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterUpdateTradeReply");
	if (NULL == RegisterUpdateTradeRespond)
	{
		msg.strMsg = "获取RegisterUpdateTradeRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterInstrumentListRespond = (p_TFBAPI_RegisterInstrumentListReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterInstrumentListReply");
	if (NULL == RegisterInstrumentListRespond)
	{
		msg.strMsg = "获取RegisterInstrumentListRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterProductListRespond = (p_TFBAPI_RegisterProductListReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterProductListReply");
	if (NULL == RegisterProductListRespond)
	{
		msg.strMsg = "获取RegisterProductListRespond函数地址失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	
	return TRUE;
}

/*********************************************************************
函数名称:RegisterLibCallBack
函数功能:加载天富宝接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
BOOL  CTfbTrade::RegisterLibCallBack()
{
	RegisterLoginRespond(LoginReply);
	RegisterLogoutRespond(LogoutReply);
	RegisterUserInfoRespond(UserInfoReply);
	RegisterLoadTradeReport(LoadTradeReply);
	RegisterAddOrderRespond(AddOrderReply);
	RegisterDelOrderRespond(DelOrderReply);
	RegisterApiPriceUpdate(ApiPriceUpdate);
	RegisterUpdateTradeRespond(UpdateTrade);
	RegisterInstrumentListRespond(InstrumentListReply);
	RegisterProductListRespond(ProductListByCodeReply);

	return TRUE;
}

/*********************************************************************
函数名称:LoginReply
函数功能:加载天富宝登陆接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::LoginReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoginRespond* Respond)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	XJRspLoginInfo LoginInfoMsg;
	XJRspContractInfo ContractInfoMsg;

	if (Respond->bResult)
	{
		g_Event.m_bLogout = false;

		m_nUserNumber++;
		msg.strMsg = "登录成功";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		LoginInfoMsg.strUserName = pUserRsp->m_strUserName;
		LoginInfoMsg.strLoginTime = Respond->pszTime;
		LoginInfoMsg.pfType = PLATFORM_TYPE::PF_TFB;
		switch (pUserRsp->m_nType)
		{
		case 0:LoginInfoMsg.strSystemName = "天富宝客户端";
			break;
		case 2:LoginInfoMsg.strSystemName = "新西兰天富宝客户端";
			break;
		case 3:LoginInfoMsg.strSystemName = "贵金属天富宝客户端";
			break;
		default:LoginInfoMsg.strSystemName = "异常";
			break;
		}
		
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_USER_RLOGIN, &LoginInfoMsg);

		if (m_nUserNumber == 1)
		{
			SetSourceAddress("115.29.7.167");
			LoadInstrumentList();
			g_Event.WaitEvent();
			if (g_Event.m_bLoadInstrumentList)
			{
				int nGetInstrumentCount = GetInstrumentCount();
				char cCount[10];
				TFBApiInstrument Instrument;
				TFBApiProduct Product;
				sprintf_s(cCount, "%d", nGetInstrumentCount);        
				
				int nGetProductCount = 0;
				for (int i = 0; i < nGetInstrumentCount; i++)
				{
					memset(&Instrument, 0, sizeof(TFBApiInstrument));
					GetInstrument(i, &Instrument);                       //加载商品系列,获取商品代码等信息

					LoadProductInfoListByCode(Instrument.pszTpCode);     //根据商品代码获取合约代码等
					g_Event.WaitEvent();
					if (g_Event.m_bLoadProductInfoList);
					{
						nGetProductCount = GetProductCount(Instrument.pszTpCode);
						for (int j = 0; j < nGetProductCount; j++)
						{
							GetProduct(Instrument.pszTpCode, j, &Product);
							ContractInfoMsg.strContractNo = Product.pszMPCode;
							ContractInfoMsg.strContractName = "";
							ContractInfoMsg.chContractType = '1';
							ContractInfoMsg.strExchangeNo = Instrument.pszMtCode; //交易所代码
							ContractInfoMsg.strProductID = Product.pszTpCode;
							ContractInfoMsg.chProductType = '1';
							ContractInfoMsg.strOpenDate = "";
							ContractInfoMsg.strExpireDate = "";
							ContractInfoMsg.dStrikePrice = 0;
							m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_CONTRACTINFO, &ContractInfoMsg);
						}
					}
				}
			}
			g_PlatformEvent.m_bLogin = true;
			g_PlatformEvent.SignalEvent();
		}	
		else
		{
			m_pTfbTemplat->PushUserInfo(g_cUserFlag, pUserRsp);
			string sUserFlag = m_pTfbTemplat->GetUserFlag(pUserRsp->m_nUserID);
			GetUserInfo(sUserFlag.c_str());
			LoadTradeReport(sUserFlag.c_str());
		}
	}
}

/*********************************************************************
函数名称:LogoutReply
函数功能:加载天富宝用户登出接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::LogoutReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, char* pszMsg)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;

	if (nRetCode == 0)
	{
		msg.strMsg = "成功登出";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		g_Event.m_bLogout = true;
	}
	if (nRetCode == -408)
	{
		msg.strMsg = "用户在别处登陆";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	if (nRetCode == -406)
	{
		msg.strMsg = "连接断开，并且设置了不自动重连 ";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	msg.strMsg = pszMsg;
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	if (m_nUserNumber != 1)
	{
		XJRspLogoutInfo LogoutMsg;
		LogoutMsg.strUserName = pUserRsp->m_strUserName;
		LogoutMsg.strLogoutReason = pszMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_USER_LOGOUT, &LogoutMsg);
	}
	g_Event.SignalEvent();
}

/*********************************************************************
函数名称:UserInfoReply
函数功能:加载天富宝用户信息接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::UserInfoReply(AdminUserRsp_Trade* pUserRsp, TFBApiUserInforRespond* Respond)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "获取用户信息回调";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	string sUserFlag;
	sUserFlag = m_pTfbTemplat->GetUserFlag(Respond->nUserID);

	//账户资金参数
	XJRspFundAccountInfo FundMsg;                                    //资金账户信息
	if (Respond->nSizeOfPosition == 0)
	{
		FundMsg.strAccountId = Respond->pszName;                         //资金账户
		FundMsg.FrozenCash = m_dFrozenCash = Respond->dOutFreezingFunds
			+ Respond->dOrderFreezingFunds
			+ Respond->dPositionsFreezingFunds;             //冻结资金
		FundMsg.PositionMargin = m_dPositionMargin = Respond->dPositionsFreezingFunds;       //持仓保证金?持仓冻结资金
		FundMsg.dAvailable = m_dAvailable = Respond->dNowFunds - (FundMsg.FrozenCash);       //可用资金:账户资金减去冻结资金
		FundMsg.PositionProfit = m_dPositionProfit;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_FUNDACCOUNT, &FundMsg);
	}
	

	m_pTfbTemplat->PushUserInforRespond(pUserRsp->m_strUserName, Respond);
//持仓信息
	bool bFindPosition = false;
	for (int i = 0; i < Respond->nSizeOfPosition; i++)
	{		
		bFindPosition = m_pTfbTemplat->PushPositionInfo(pUserRsp->m_strUserName, &Respond->pPosition[i]);
		if (!bFindPosition)
		{
			SubscribePrice(sUserFlag.c_str(), Respond->pPosition[i].pszTPmcode, 1);
		}
	}
	
	//订单信息
	for (int i = 0; i < Respond->nSizeOfOrder; i++)
	{
		m_pTfbTemplat->PushOrderInfo(pUserRsp->m_strUserName,&Respond->pOrder[i]);
	}
}

/*********************************************************************
函数名称:LoadTradeReply
函数功能:加载天富宝用户订单成交接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::LoadTradeReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoadTradeRespond* Respond)
{
	char cSizeofTradeItem[10];
	string sSizeofTradeItem;
	
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "获取成交报告回调";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	_itoa_s(Respond->nSizeofTradeItem, cSizeofTradeItem, 10);
	sSizeofTradeItem = cSizeofTradeItem;

	msg.strMsg = "成交数量";
	msg.strMsg += cSizeofTradeItem;
	//保存订单信息
	for (int i = 0; i < Respond->nSizeofTradeItem; i++)
	{
		m_pTfbTemplat->PushLoadTradeOrder(pUserRsp->m_strUserName, &Respond->pTradeItem[i]);
	}
	
	//成交信息
	XJRspTradeInfo TradeMsg;
	char cOrderNo[10];
	CLeeDateTime m_Time;

	string s_Time;
	m_Time = CLeeDateTime::GetCurrentTime();
	s_Time = m_Time.Format("%Y-%m-%d");//格式化日期时间

	TradeMsg.strAccountId = pUserRsp->m_strUserName;                      //资金账户
	for (int i = 0; i < Respond->nSizeofTradeItem; i++)
	{
		if (strstr(Respond->pTradeItem[i].ohedealtime, s_Time.c_str()) != NULL)
		{
			sprintf_s(cOrderNo, "%d", Respond->pTradeItem[i].ohedoid);        //委托编号
			TradeMsg.strOrderNo = cOrderNo;
			TradeMsg.strTradeDataTime = Respond->pTradeItem[i].ohedealtime;   //成交时间
			TradeMsg.strContrctNo = Respond->pTradeItem[i].ohemcode;          //合约代码
			if (Respond->pTradeItem[i].ohetype == 1)
			{
				TradeMsg.chOrderSide = '0';
			}
			if (Respond->pTradeItem[i].ohetype == 0)
			{
				TradeMsg.chOrderSide = '1';
			}
			switch (Respond->pTradeItem[i].oheAdverse)
			{
			case 0:TradeMsg.chOffset = '0';
				break;
			case 1:TradeMsg.chOffset = '1';
				break;
			case 2:TradeMsg.chOffset = '2';
				break;
			default:TradeMsg.chOffset = -1;
				break;
			}
			TradeMsg.dMatchPrice = Respond->pTradeItem[i].oheprice;
			TradeMsg.nMatchVolume = Respond->pTradeItem[i].ohenumber;
			m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_TRADEINFO, &TradeMsg);
		}	
	}
}

/*********************************************************************
函数名称:UserInfoReply
函数功能:加载天富宝用户下单接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::AddOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg, char* pszRefID)
{
	string sMsg;
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "下单回调";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	if (nRetCode == 0)
	{
		msg.strMsg = "下单成功";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	else
	{
		sMsg = pszMsg;
		msg.strMsg = "下单失败,错误原因:" + sMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
}

/*********************************************************************
函数名称:UserInfoReply
函数功能:加载天富宝用户撤单接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::DelOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "撤单回调";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	XJRspOrderInfo OrderInfoMsg;
	OrderInfoMsg.strAccountId = pUserRsp->m_strUserName;

	string sOrderId;
	char cOrderId[10];
	sprintf_s(cOrderId, "%d", nOrderID);
	sOrderId = cOrderId;

	if (nRetCode == 0)
	{
		msg.strMsg = "撤单回调成功";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		msg.strMsg = sOrderId;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		//OrderInfoMsg.
		OrderInfoMsg.chOrderstate = '1';
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_CHANGE_ORDER, &OrderInfoMsg);

		m_pTfbTemplat->PullOrderInfo(pUserRsp->m_strUserName, nOrderID);
	}
	else
	{
		msg.strMsg = "撤单回调失败";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		msg.strMsg = pszMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
}

/*********************************************************************
函数名称:UserInfoReply
函数功能:加载天富宝用户订阅商品信息接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::ApiPriceUpdate(const tPriceData *price)
{
	m_pTfbTemplat->PushCurPriceInfo(price);

	//XJRspFundAccountInfo FundMsg;                                    //资金账户信息

	//FundMsg.strAccountId = "xmnX2052";                               //资金账户
	//FundMsg.FrozenCash = m_dFrozenCash;
	//FundMsg.PositionMargin = m_dPositionMargin;                        //持仓保证金?持仓冻结资金
	//FundMsg.dAvailable = m_dAvailable;                                 //可用资金:账户资金减去冻结资金
	//FundMsg.PositionProfit = m_dPositionProfit;
	//m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_FUNDACCOUNT, &FundMsg);
}

/*********************************************************************
函数名称:UserInfoReply
函数功能:加载天富宝用户订单成交信息更新接口回调
开发者及日期:李宝鑫 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::UpdateTrade(AdminUserRsp_Trade* pUserRsp, TFBApiUpDateTrade* Respond)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "订单成交";

	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	XJRspTradeInfo TradeMsg;
	char cOrderNo[10];
	TradeMsg.strAccountId = pUserRsp->m_strUserName;                      //资金账户
	sprintf_s(cOrderNo, "%d", Respond->nOrderId);        //委托编号
	TradeMsg.strOrderNo = cOrderNo;
	TradeMsg.strTradeDataTime = Respond->pszTime;   //成交时间
	TradeMsg.strContrctNo = Respond->pszProduct;          //合约代码
	if (Respond->nIsBuy == 1)
	{
		TradeMsg.chOrderSide = '0';
	}
	if (Respond->nIsBuy == 0)
	{
		TradeMsg.chOrderSide = '1';
	}
	switch (Respond->nAdverse)
	{
	case 0:TradeMsg.chOffset = '0';
		break;
	case 1:TradeMsg.chOffset = '1';
		break;
	case 2:TradeMsg.chOffset = '2';
		break;
	default:TradeMsg.chOffset = -1;
		break;
	}
	TradeMsg.dMatchPrice = Respond->dPrice;
	TradeMsg.nMatchVolume = Respond->dNumber;
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_TRADEINFO, &TradeMsg);
	m_pTfbTemplat->ModifyOrderInfo(pUserRsp->m_strUserName, Respond->nOrderId);
	m_pTfbTemplat->ModifyPositionInfo(pUserRsp->m_strUserName, pUserRsp->m_nUserID, Respond->pszProduct, Respond->dNumber, Respond->nIsBuy);
	m_pTfbTemplat->ModifyLoadTradeOrder(pUserRsp->m_strUserName, Respond);
}
/*********************************************************************
函数名称:UserInfoReply
函数功能:加载天富宝系统商品系列信息接口回调
开发者及日期:李宝鑫 2017.10.13
*********************************************************************/
void TFBDLLCALL CTfbTrade::InstrumentListReply(int nRetCode, const char* pszMsg)
{
	XJRspShowTipMessage msg;
	
	if (nRetCode == -1)
	{
		msg.strMsg = "加载商品系列信息失败,失败原因:";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		msg.strMsg = pszMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	else
	{
		msg.strMsg = "加载商品系列信息成功";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		g_Event.m_bLoadInstrumentList = true;
	}
	g_Event.SignalEvent();
}

void TFBDLLCALL CTfbTrade::ProductListByCodeReply(const char* pszProductCode, int nRetCode, const char* pszMsg)
{
	XJRspShowTipMessage msg;
	if (nRetCode == -1)
	{
		msg.strMsg = "获取合约代码等信息失败,失败原因:";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		msg.strMsg = pszMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	else
	{
		g_Event.m_bLoadProductInfoList = true;
	}
	g_Event.SignalEvent();
}