/**********************************************************************
�ļ���:TfbPlatform.cpp
���ܺ�ģ���Ŀ��:�ļ�ʵ�����츻�����ʽ���ϵͳ�Ķ���ӿڡ������ͻص��ӿ�
�����߼�����:��� 2017.9.27
**********************************************************************/
#include"TfbPlatform.h"
#include "../../Common/Common.h"

/*********************************************************************
��������:CTfbPlatform
��������:���캯����������ʱ��ʼ������
�����߼�����:��� 2017.9.27
*********************************************************************/
char g_cUserFlag[60];//�û���ʶ
extern SimpleEvent    g_PlatformEvent;
extern SimpleEvent    g_Event;
CTfbPlatform::CTfbPlatform(PFNPLATFORMDATAPROC pfn) :IPlatformApi(pfn), TfbTrade(m_pPlatformDataProc)
{
	
}

/*********************************************************************
��������:~CTfbPlatform
��������:���������ͷŶ�����ռ�õ���Դ
�����߼�����:��� 2017.9.27
*********************************************************************/
CTfbPlatform::~CTfbPlatform()
{

}

//��ʼ��ƽ̨															   													  
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
//��¼һ�������˻�
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
//��ѯ�ʽ��˺�
void CTfbPlatform::QueryTradeAccount(const string& userID)
{

}
//�ǳ�һ�������˻�
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
//�ǳ����н����˻�
void CTfbPlatform::LogoutAll()
{

}
//�½�ί��
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
	Order.nStopType = ST_NODEFINE;                   // ��ֹ��
	Order.nPID = 0;									 // ��ƽ�ֵ�
	Order.nType = OT_USERORDER;						 // �û�����
	Order.fPrice = order_price;                      // �����۸�
	Order.fStopLevel = 0;                            // ֹ��۸�
	APIStrncpy(Order.pszRefId, "TestRefID");         // ����ID

	TfbTrade.AddOrder(sUserFlag.c_str(), &Order);
}
//����ί��
void CTfbPlatform::CancelOrder(const string& userID, const string &OrderSysID, const string &ExchangeID)
{
	string sUserFlag = TfbTrade.m_pTfbTemplat->GetUserFlag(userID);
	int nOrderCode = atoi(OrderSysID.c_str());

	TfbTrade.DelOrder(sUserFlag.c_str(), nOrderCode);
}
//��ѯ�ֲ�(����)
void CTfbPlatform::QueryPostion(const string& userID, const string& contract)
{

}
//��ѯ�ֲ���ϸ
void CTfbPlatform::QueryPostionDetail(const string& userID, const string& contract)
{
	
}

//��ѯ�ɽ���Ϣ,��ָ����ʼ���ڣ�����Ϊ��ʱĬ��Ϊ���ճɽ���Ϣ
void CTfbPlatform::QueryTrade(const string& userID, const string& strStartDate, const string& strEndDate)
{
	TfbTrade.m_pTfbTemplat->GetLoadTradeOrder(userID, strStartDate, strEndDate);
}

//��������
void CTfbPlatform::RestartStrategy(const string& userID, const string& strategyID)
{

}
//�رղ���
void CTfbPlatform::CloseStrategy(const string& userID, const string& strategyID)
{

}

