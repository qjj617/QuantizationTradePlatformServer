/**********************************************************************
�ļ���:TfbTemplat.h
���ܺ�ģ���Ŀ��:�ļ��������츻�����ʽ���ϵͳģ����
�����߼�����:��� 2017.10.10
**********************************************************************/
#pragma once
#include <vector>
#include "TfbTradeApi.h"
#include "windows.h"
#include "../../protocol/XJIPlatformApi.h"      //ƽ̨�ص��ӿ�ͷ�ļ�
#include <string>
#include "TfbCommon.h"

struct TfbLoadTrade
{
	//�û���
	STR64 sUserName;
	//������
	int nOrderNo;
	//�ɽ�ʱ��
	STR64 cTradeDataTime;
	//��Լ
	STR16 sContrctNo;
	//����
	char chOrderSide;
	//ƽ����־
	char chOffset;
	//�ɽ��۸�
	double dMatchPrice;
	//�ɽ�����
	int nMatchVolume;
	//������
	double dFeeValue;
};

class CTfbTemplat
{
public:
	CTfbTemplat(PFNPLATFORMDATAPROC pfn);
	~CTfbTemplat();

//���û�����
	double PushCurPriceInfo(const tPriceData *pPriceDateInfo);//����������㸡��ӯ��
	bool PushUserInfo(string sUserFlag, AdminUserRsp_Trade* pUserRsp);
	string GetUserFlag(int nUserID);      //����UserID��ȡUserFlag
	string GetUserFlag(string sUserName); //����UserName��ȡUserFlag
	string TfbGetUserName(int nUserID);   //����UserID��ȡ�û���
	bool PushPositionInfo(string sUserName, TFBApiPosition *pPositionInfo);
	bool PushOrderInfo(string sUserName, TFBApiOrder* pOrderInfo);
	bool ModifyOrderInfo(string sUserName, int nOrderID);           //�޸Ķ���״̬
	//�����ɽ�ʱ���ݳֲ�ID�޸ĳֲ���(ƽ��ʱ��Ҫ�ѳֲ���0��������,�û���Ϣ��������ƽ�ֲ�����ƽ����Ʒ�ĳֲ���)
	bool ModifyPositionInfo(string sUserName, int  nUserID, string sProductCode, double dNumber, int nIsBuy);
	bool PullOrderInfo(string sUserName, int nOrderID);             //����
	bool ClearPositionInfo(string sUserName);                       //���ĳ�û��ֲ�
	bool ClearOrderInfo(string sUserName);                          //���ĳ�û�����
	bool ClearUserInfo(string sUserName);                           //���ĳ�û�����

	bool PushUserInforRespond(string sUserName, TFBApiUserInforRespond *pUserInforRespond);
	bool ClearUserInfofRespond(string sUserName);                   //����û��ص�����

	bool PushLoadTradeOrder(string sUserName, TFBApiLoadTrade *pLoadTrade);//���سɽ�������Ϣ
	bool GetLoadTradeOrder(string sUserName, string sStartDate, string sEndDate); //�����ƶ���ֹ���ڳɽ�����
	bool ClearLoadTradeOrder(string sUserName);//���ĳ�û��ѳɽ���������
	bool ModifyLoadTradeOrder(string sUserName, TFBApiUpDateTrade *pUpdateTrade); //�³ɽ��������
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