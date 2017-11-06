/**********************************************************************
�ļ���:TfbPlatform.cpp
���ܺ�ģ���Ŀ��:�ļ�ʵ�����츻�����ʽ���ϵͳ�Ķ���ӿڡ������ͻص��ӿ�
�����߼�����:��� 2017.9.27
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
double CTfbTrade::m_dFrozenCash = 0.0;                      //�����ʽ�
double CTfbTrade::m_dPositionMargin = 0.0;                  //�ֱֲ�֤��
double CTfbTrade::m_dAvailable = 0.0;                       //�����ʽ�
int CTfbTrade::m_nUserNumber = 0;
/*********************************************************************
��������:CTfbTrade
��������:���캯����������ʱ��ʼ������
�����߼�����:��� 2017.9.27
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
��������:~CTfbPlatform
��������:���������ͷŶ�����ռ�õ���Դ
�����߼�����:��� 2017.9.27
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
��������:IniLib
��������:��̬���ʼ��
�����߼�����:��� 2017.9.27
*********************************************************************/
BOOL  CTfbTrade::IniLib()
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	m_hInstLibrary = LoadLibrary(_T("TfbTradeApi.dll"));
	if (NULL == m_hInstLibrary)
	{
		msg.strMsg = "���ض�̬��TfbTradeApi.dllʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	}
	if (!LoadFuncAddr())
	{
		return FALSE;
	}
	if (0 != myInit(TRUE))
	{
		msg.strMsg = "��̬���ʼ������";
		//	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}

	RegisterLibCallBack();

	return TRUE;
}

/*********************************************************************
��������:LoadFuncAddr
��������:��ȡ�츻���ӿں�����ַ
�����߼�����:��� 2017.9.27
*********************************************************************/
BOOL  CTfbTrade::LoadFuncAddr()
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;

	myInit = (p_TFBAPI_Initialize)GetProcAddress(m_hInstLibrary, "TFBAPI_Initialize");
	if (NULL == myInit)
	{
		msg.strMsg = "��ȡInit������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	myUninit = (p_TFBAPI_Uninitialize)GetProcAddress(m_hInstLibrary, "TFBAPI_Uninitialize");
	if (NULL == myUninit)
	{
		msg.strMsg = "��ȡmyUninit������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	GetUserFlag = (p_TFBAPI_GetUserFlag)GetProcAddress(m_hInstLibrary, "TFBAPI_GetUserFlag");
	if (NULL == GetUserFlag)
	{
		msg.strMsg = "��ȡGetUserFlag������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	Login = (p_TFBAPI_Login)GetProcAddress(m_hInstLibrary, "TFBAPI_Login");
	if (NULL == Login)
	{
		msg.strMsg = "��ȡLogin������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	Logout = (p_TFBAPI_Logout)GetProcAddress(m_hInstLibrary, "TFBAPI_Logout");
	if (NULL == Logout)
	{
		msg.strMsg = "��ȡLogout������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}

	GetUserInfo = (p_TFBAPI_GetUserInfo)GetProcAddress(m_hInstLibrary, "TFBAPI_GetUserInfo");
	if (NULL == GetUserInfo)
	{
		msg.strMsg = "��ȡGetUserInfo������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	LoadTradeReport = (p_TFBAPI_LoadTradeReport)GetProcAddress(m_hInstLibrary, "TFBAPI_LoadTradeReport");
	if (NULL == LoadTradeReport)
	{
		msg.strMsg = "��ȡLoadTradeReport������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	AddOrder = (p_TFBAPI_AddOrder)GetProcAddress(m_hInstLibrary, "TFBAPI_AddOrder");
	if (NULL == AddOrder)
	{
		msg.strMsg = "��ȡAddOrder������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	DelOrder = (p_TFBAPI_DeleteOrder)GetProcAddress(m_hInstLibrary, "TFBAPI_DeleteOrder");
	if (NULL == DelOrder)
	{
		msg.strMsg = "��ȡDelOrder������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	SubscribePrice = (p_TFBAPI_SubscribePrice)GetProcAddress(m_hInstLibrary, "TFBAPI_SubscribePrice");
	if (NULL == SubscribePrice)
	{
		msg.strMsg = "��ȡSubscribePrice������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	SetSourceAddress = (p_TFBAPI_SetSourceAddress)GetProcAddress(m_hInstLibrary, "TFBAPI_SetSourceAddress");
	if (NULL == SetSourceAddress)
	{
		msg.strMsg = "��ȡSetSourceAddress������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	LoadInstrumentList = (p_TFBAPI_LoadInstrumentList)GetProcAddress(m_hInstLibrary, "TFBAPI_LoadInstrumentList");
	if (NULL == LoadInstrumentList)
	{
		msg.strMsg = "��ȡLoadInstrumentList������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetInstrumentCount = (p_TFBAPI_GetInstrumentCount)GetProcAddress(m_hInstLibrary, "TFBAPI_GetInstrumentCount");
	if (NULL == GetInstrumentCount)
	{
		msg.strMsg = "��ȡGetInstrumentCount������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetInstrument = (p_TFBAPI_GetInstrument)GetProcAddress(m_hInstLibrary, "TFBAPI_GetInstrument");
	if (NULL == GetInstrument)
	{
		msg.strMsg = "��ȡGetInstrument������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	LoadProductInfoListByCode = (p_TFBAPI_LoadProductInfoListByCode)GetProcAddress(m_hInstLibrary, "TFBAPI_LoadProductInfoListByCode");
	if (NULL == LoadProductInfoListByCode)
	{
		msg.strMsg = "��ȡGetInstrument������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetProductCount = (p_TFBAPI_GetProductCount)GetProcAddress(m_hInstLibrary, "TFBAPI_GetProductCount");
	if (NULL == GetProductCount)
	{
		msg.strMsg = "��ȡGetInstrument������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	GetProduct = (p_TFBAPI_GetProduct)GetProcAddress(m_hInstLibrary, "TFBAPI_GetProduct");
	if (NULL == GetProduct)
	{
		msg.strMsg = "��ȡGetProduct������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}

	RegisterLoginRespond = (p_TFBAPI_RegisterLoginReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterLoginReply");
	if (NULL == RegisterLoginRespond)
	{
		msg.strMsg = "��ȡRegisterLoginRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterLogoutRespond = (p_TFBAPI_RegisterLogoutReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterLogoutReply");
	if (NULL == RegisterLogoutRespond)
	{
		msg.strMsg = "��ȡRegisterLogoutRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}

	RegisterUserInfoRespond = (p_TFBAPI_RegisterUserInfoReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterUserInfoReply");
	if (NULL == RegisterUserInfoRespond)
	{
		msg.strMsg = "��ȡRegisterUserInfoRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterLoadTradeReport = (p_TFBAPI_RegisterLoadTradeReport)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterLoadTradeReport");
	if (NULL == RegisterLoadTradeReport)
	{
		msg.strMsg = "��ȡRegisterLoadTradeReport������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterAddOrderRespond = (p_TFBAPI_RegisterAddOrderReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterAddOrderReply");
	if (NULL == RegisterAddOrderRespond)
	{
		msg.strMsg = "��ȡRegisterAddOrderRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		return FALSE;
	}
	RegisterDelOrderRespond = (p_TFBAPI_RegisterDelOrderReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterDelOrderReply");
	if (NULL == RegisterDelOrderRespond)
	{
		msg.strMsg = "��ȡRegisterDelOrderRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterApiPriceUpdate = (p_TFBAPI_RegisterApiPriceUpdate)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterApiPriceUpdate");
	if (NULL == RegisterApiPriceUpdate)
	{
		msg.strMsg = "��ȡRegisterApiPriceUpdate������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterUpdateTradeRespond = (p_TFBAPI_RegisterUpdateTradeReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterUpdateTradeReply");
	if (NULL == RegisterUpdateTradeRespond)
	{
		msg.strMsg = "��ȡRegisterUpdateTradeRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterInstrumentListRespond = (p_TFBAPI_RegisterInstrumentListReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterInstrumentListReply");
	if (NULL == RegisterInstrumentListRespond)
	{
		msg.strMsg = "��ȡRegisterInstrumentListRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	RegisterProductListRespond = (p_TFBAPI_RegisterProductListReply)GetProcAddress(m_hInstLibrary, "TFBAPI_RegisterProductListReply");
	if (NULL == RegisterProductListRespond)
	{
		msg.strMsg = "��ȡRegisterProductListRespond������ַʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		return FALSE;
	}
	
	return TRUE;
}

/*********************************************************************
��������:RegisterLibCallBack
��������:�����츻���ӿڻص�
�����߼�����:��� 2017.9.27
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
��������:LoginReply
��������:�����츻����½�ӿڻص�
�����߼�����:��� 2017.9.27
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
		msg.strMsg = "��¼�ɹ�";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

		LoginInfoMsg.strUserName = pUserRsp->m_strUserName;
		LoginInfoMsg.strLoginTime = Respond->pszTime;
		LoginInfoMsg.pfType = PLATFORM_TYPE::PF_TFB;
		switch (pUserRsp->m_nType)
		{
		case 0:LoginInfoMsg.strSystemName = "�츻���ͻ���";
			break;
		case 2:LoginInfoMsg.strSystemName = "�������츻���ͻ���";
			break;
		case 3:LoginInfoMsg.strSystemName = "������츻���ͻ���";
			break;
		default:LoginInfoMsg.strSystemName = "�쳣";
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
					GetInstrument(i, &Instrument);                       //������Ʒϵ��,��ȡ��Ʒ�������Ϣ

					LoadProductInfoListByCode(Instrument.pszTpCode);     //������Ʒ�����ȡ��Լ�����
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
							ContractInfoMsg.strExchangeNo = Instrument.pszMtCode; //����������
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
��������:LogoutReply
��������:�����츻���û��ǳ��ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::LogoutReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, char* pszMsg)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;

	if (nRetCode == 0)
	{
		msg.strMsg = "�ɹ��ǳ�";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		g_Event.m_bLogout = true;
	}
	if (nRetCode == -408)
	{
		msg.strMsg = "�û��ڱ𴦵�½";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	if (nRetCode == -406)
	{
		msg.strMsg = "���ӶϿ������������˲��Զ����� ";
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
��������:UserInfoReply
��������:�����츻���û���Ϣ�ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::UserInfoReply(AdminUserRsp_Trade* pUserRsp, TFBApiUserInforRespond* Respond)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "��ȡ�û���Ϣ�ص�";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	string sUserFlag;
	sUserFlag = m_pTfbTemplat->GetUserFlag(Respond->nUserID);

	//�˻��ʽ����
	XJRspFundAccountInfo FundMsg;                                    //�ʽ��˻���Ϣ
	if (Respond->nSizeOfPosition == 0)
	{
		FundMsg.strAccountId = Respond->pszName;                         //�ʽ��˻�
		FundMsg.FrozenCash = m_dFrozenCash = Respond->dOutFreezingFunds
			+ Respond->dOrderFreezingFunds
			+ Respond->dPositionsFreezingFunds;             //�����ʽ�
		FundMsg.PositionMargin = m_dPositionMargin = Respond->dPositionsFreezingFunds;       //�ֱֲ�֤��?�ֲֶ����ʽ�
		FundMsg.dAvailable = m_dAvailable = Respond->dNowFunds - (FundMsg.FrozenCash);       //�����ʽ�:�˻��ʽ��ȥ�����ʽ�
		FundMsg.PositionProfit = m_dPositionProfit;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_FUNDACCOUNT, &FundMsg);
	}
	

	m_pTfbTemplat->PushUserInforRespond(pUserRsp->m_strUserName, Respond);
//�ֲ���Ϣ
	bool bFindPosition = false;
	for (int i = 0; i < Respond->nSizeOfPosition; i++)
	{		
		bFindPosition = m_pTfbTemplat->PushPositionInfo(pUserRsp->m_strUserName, &Respond->pPosition[i]);
		if (!bFindPosition)
		{
			SubscribePrice(sUserFlag.c_str(), Respond->pPosition[i].pszTPmcode, 1);
		}
	}
	
	//������Ϣ
	for (int i = 0; i < Respond->nSizeOfOrder; i++)
	{
		m_pTfbTemplat->PushOrderInfo(pUserRsp->m_strUserName,&Respond->pOrder[i]);
	}
}

/*********************************************************************
��������:LoadTradeReply
��������:�����츻���û������ɽ��ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::LoadTradeReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoadTradeRespond* Respond)
{
	char cSizeofTradeItem[10];
	string sSizeofTradeItem;
	
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "��ȡ�ɽ�����ص�";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	_itoa_s(Respond->nSizeofTradeItem, cSizeofTradeItem, 10);
	sSizeofTradeItem = cSizeofTradeItem;

	msg.strMsg = "�ɽ�����";
	msg.strMsg += cSizeofTradeItem;
	//���涩����Ϣ
	for (int i = 0; i < Respond->nSizeofTradeItem; i++)
	{
		m_pTfbTemplat->PushLoadTradeOrder(pUserRsp->m_strUserName, &Respond->pTradeItem[i]);
	}
	
	//�ɽ���Ϣ
	XJRspTradeInfo TradeMsg;
	char cOrderNo[10];
	CLeeDateTime m_Time;

	string s_Time;
	m_Time = CLeeDateTime::GetCurrentTime();
	s_Time = m_Time.Format("%Y-%m-%d");//��ʽ������ʱ��

	TradeMsg.strAccountId = pUserRsp->m_strUserName;                      //�ʽ��˻�
	for (int i = 0; i < Respond->nSizeofTradeItem; i++)
	{
		if (strstr(Respond->pTradeItem[i].ohedealtime, s_Time.c_str()) != NULL)
		{
			sprintf_s(cOrderNo, "%d", Respond->pTradeItem[i].ohedoid);        //ί�б��
			TradeMsg.strOrderNo = cOrderNo;
			TradeMsg.strTradeDataTime = Respond->pTradeItem[i].ohedealtime;   //�ɽ�ʱ��
			TradeMsg.strContrctNo = Respond->pTradeItem[i].ohemcode;          //��Լ����
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
��������:UserInfoReply
��������:�����츻���û��µ��ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::AddOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg, char* pszRefID)
{
	string sMsg;
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "�µ��ص�";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	if (nRetCode == 0)
	{
		msg.strMsg = "�µ��ɹ�";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	else
	{
		sMsg = pszMsg;
		msg.strMsg = "�µ�ʧ��,����ԭ��:" + sMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
}

/*********************************************************************
��������:UserInfoReply
��������:�����츻���û������ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::DelOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "�����ص�";
	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	XJRspOrderInfo OrderInfoMsg;
	OrderInfoMsg.strAccountId = pUserRsp->m_strUserName;

	string sOrderId;
	char cOrderId[10];
	sprintf_s(cOrderId, "%d", nOrderID);
	sOrderId = cOrderId;

	if (nRetCode == 0)
	{
		msg.strMsg = "�����ص��ɹ�";
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
		msg.strMsg = "�����ص�ʧ��";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		msg.strMsg = pszMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
}

/*********************************************************************
��������:UserInfoReply
��������:�����츻���û�������Ʒ��Ϣ�ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::ApiPriceUpdate(const tPriceData *price)
{
	m_pTfbTemplat->PushCurPriceInfo(price);

	//XJRspFundAccountInfo FundMsg;                                    //�ʽ��˻���Ϣ

	//FundMsg.strAccountId = "xmnX2052";                               //�ʽ��˻�
	//FundMsg.FrozenCash = m_dFrozenCash;
	//FundMsg.PositionMargin = m_dPositionMargin;                        //�ֱֲ�֤��?�ֲֶ����ʽ�
	//FundMsg.dAvailable = m_dAvailable;                                 //�����ʽ�:�˻��ʽ��ȥ�����ʽ�
	//FundMsg.PositionProfit = m_dPositionProfit;
	//m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_QRY_FUNDACCOUNT, &FundMsg);
}

/*********************************************************************
��������:UserInfoReply
��������:�����츻���û������ɽ���Ϣ���½ӿڻص�
�����߼�����:��� 2017.9.27
*********************************************************************/
void TFBDLLCALL CTfbTrade::UpdateTrade(AdminUserRsp_Trade* pUserRsp, TFBApiUpDateTrade* Respond)
{
	XJRspShowTipMessage msg;
	msg.nErr = 0;
	msg.strMsg = "�����ɽ�";

	m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);

	XJRspTradeInfo TradeMsg;
	char cOrderNo[10];
	TradeMsg.strAccountId = pUserRsp->m_strUserName;                      //�ʽ��˻�
	sprintf_s(cOrderNo, "%d", Respond->nOrderId);        //ί�б��
	TradeMsg.strOrderNo = cOrderNo;
	TradeMsg.strTradeDataTime = Respond->pszTime;   //�ɽ�ʱ��
	TradeMsg.strContrctNo = Respond->pszProduct;          //��Լ����
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
��������:UserInfoReply
��������:�����츻��ϵͳ��Ʒϵ����Ϣ�ӿڻص�
�����߼�����:��� 2017.10.13
*********************************************************************/
void TFBDLLCALL CTfbTrade::InstrumentListReply(int nRetCode, const char* pszMsg)
{
	XJRspShowTipMessage msg;
	
	if (nRetCode == -1)
	{
		msg.strMsg = "������Ʒϵ����Ϣʧ��,ʧ��ԭ��:";
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
		msg.strMsg = pszMsg;
		m_pPlatformDataProc(XJ_PUSH_PLATFORMDATA_RSP::RSP_SHOW_TIPMESSAGE, &msg);
	}
	else
	{
		msg.strMsg = "������Ʒϵ����Ϣ�ɹ�";
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
		msg.strMsg = "��ȡ��Լ�������Ϣʧ��,ʧ��ԭ��:";
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