/**********************************************************************
�ļ���:TfbTrade.h
���ܺ�ģ���Ŀ��:�ļ��������츻�����ʽ���ϵͳ�Ķ���ӿڡ������ͻص��ӿ�
�����߼�����:��� 2017.9.27
**********************************************************************/
#pragma once
#include "TfbTradeApi.h"                   //�츻��APIͷ�ļ�
#include "afxwin.h"
#include "../../protocol/XJIPlatformApi.h"      //ƽ̨�ص��ӿ�ͷ�ļ�
#include "TfbTemplat.h"
#include "SimpleEvent.h"                   //�¼�����

class CTfbTrade
{
public:
	CTfbTrade(PFNPLATFORMDATAPROC pfn);                           //���캯��
	~CTfbTrade();                          //��������
	static PFNPLATFORMDATAPROC m_pPlatformDataProc;

	HINSTANCE   m_hInstLibrary;
	//��̬���ʼ��
	BOOL  IniLib();
	//��ȡ�츻���ӿں�����ַ
	BOOL  LoadFuncAddr();
	//���ػص�
	BOOL  RegisterLibCallBack();

	static CTfbTemplat* m_pTfbTemplat;
	static double m_dPositionProfit;                  //ʵʱ�ֲ�ӯ��
	static double m_dFrozenCash;                      //�����ʽ�
	static double m_dPositionMargin;                  //�ֱֲ�֤��
	static double m_dAvailable;                       //�����ʽ�
	static int m_nUserNumber;                         //�û�����
	// ��̬�⺯��ָ��
    static p_TFBAPI_Initialize                 myInit;                      //�츻��API��ʼ��
	static p_TFBAPI_GetUserInfo                GetUserInfo;                 //��ȡ�û���Ϣ
	static p_TFBAPI_LoadTradeReport            LoadTradeReport;             //��ȡ���һ��ʱ��ĳɽ�����
	static p_TFBAPI_AddOrder                   AddOrder;                    //�µ� 
	static p_TFBAPI_DeleteOrder                DelOrder;                    //����
	static p_TFBAPI_SubscribePrice             SubscribePrice;              //���鶩��
	static p_TFBAPI_SetSourceAddress           SetSourceAddress;            //��������ԴIP
	static p_TFBAPI_LoadInstrumentList         LoadInstrumentList;          //������Ʒϵ��
	static p_TFBAPI_GetInstrumentCount         GetInstrumentCount;          //��ȡ��Ʒϵ�и���
	static p_TFBAPI_GetInstrument              GetInstrument;               //��ȡ��Ʒ��Ϣ(��Ʒ�����),���ڱ���
	static p_TFBAPI_LoadProductInfoListByCode  LoadProductInfoListByCode;   //������Ʒ������ظ���Ʒ��Լ(��Լ����)
	static p_TFBAPI_GetProductCount            GetProductCount;             //������Ʒ�����ȡ����Ʒ��Լ�������
	static p_TFBAPI_GetProduct                 GetProduct;                  //������Լ,������Ʒ�����ȡ����Ʒ���еĺ�Լ����

	p_TFBAPI_Uninitialize               myUninit;                        //�ͷ��츻��API
	p_TFBAPI_GetUserFlag                GetUserFlag;                     //��ȡ�û���ʶ
	p_TFBAPI_Login                      Login;                           //�û���½
	p_TFBAPI_Logout                     Logout;                          //�û��ǳ�

	p_TFBAPI_RegisterLoginReply          RegisterLoginRespond;           //ע���¼��Ӧ
	p_TFBAPI_RegisterLogoutReply         RegisterLogoutRespond;          //ע��ǳ���Ӧ
	p_TFBAPI_RegisterUserInfoReply       RegisterUserInfoRespond;        //ע���ȡ�û���Ϣ��Ӧ
	p_TFBAPI_RegisterLoadTradeReport     RegisterLoadTradeReport;        //ע���ȡ�ɽ������Ӧ 
	p_TFBAPI_RegisterAddOrderReply       RegisterAddOrderRespond;        //ע���µ���Ӧ
	p_TFBAPI_RegisterDelOrderReply       RegisterDelOrderRespond;        //ע�᳷����Ӧ
	p_TFBAPI_RegisterApiPriceUpdate      RegisterApiPriceUpdate;         //ע�����鶩�Ļ�Ӧ
	p_TFBAPI_RegisterUpdateTradeReply    RegisterUpdateTradeRespond;     //ע�ᶩ���ɽ���Ӧ
	p_TFBAPI_RegisterInstrumentListReply RegisterInstrumentListRespond;  //ע���ȡ��Ʒϵ����Ϣ��Ӧ																  
	p_TFBAPI_RegisterProductListReply    RegisterProductListRespond;     //ע���ȡ��Լ�������Ϣ�Ļ�Ӧ
	//��½�ص�
	static void TFBDLLCALL LoginReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoginRespond* Respond);
	//�ǳ��ص�
	static void TFBDLLCALL LogoutReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, char* pszMsg);
	//��ȡ�û���Ϣ�ص�
	static void TFBDLLCALL UserInfoReply(AdminUserRsp_Trade* pUserRsp, TFBApiUserInforRespond* Respond);
	//��ȡ�ɽ�����ص�
	static void TFBDLLCALL LoadTradeReply(AdminUserRsp_Trade* pUserRsp, TFBApiLoadTradeRespond* Respond);
	//�µ��ص�
	static void TFBDLLCALL AddOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg, char* pszRefID);
	//�����ص�
	static void TFBDLLCALL DelOrderReply(AdminUserRsp_Trade* pUserRsp, int nRetCode, int nOrderID, char* pszMsg);
	//��������ص�
	static void TFBDLLCALL ApiPriceUpdate(const tPriceData *price);
	//�����ɽ��ص�
	static void TFBDLLCALL UpdateTrade(AdminUserRsp_Trade* pUserRsp, TFBApiUpDateTrade* Respond);
	//��ȡ��Ʒϵ�лص�
	static void TFBDLLCALL InstrumentListReply(int nRetCode, const char* pszMsg);
	//��ȡ��Լ��Ϣ�Ļص�
	static void TFBDLLCALL ProductListByCodeReply(const char* pszProductCode, int nRetCode, const char* pszMsg);
};