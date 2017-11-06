/**********************************************************************
�ļ���:TfbPlatform.h
���ܺ�ģ���Ŀ��:�ļ��������츻�����ʽ���ϵͳ�Ķ���ӿڡ������ͻص��ӿ�
�����߼�����:��� 2017.9.27
**********************************************************************/
#pragma once

#include "../../protocol/XJIPlatformApi.h"      //ƽ̨�ص��ӿ�ͷ�ļ�
#include "TfbTrade.h"
#include "TfbTradeApi.h"                   //�츻��APIͷ�ļ�

/**********************************************************************
����:CTfbPlatform
����:�츻����IPlatformApi��ʵ�ּ��츻��ϵͳ����ӿڡ������ͻص�ʵ��
�ӿ�˵��:
�����߼�����:��� 2017.9.27
**********************************************************************/
class CTfbPlatform :public IPlatformApi
{
private:
	CTfbPlatform(PFNPLATFORMDATAPROC pfn);                     //���캯��.˽��,��ֹ���ֶ��������

	HINSTANCE   m_hInstLibrary;

public:
	static CTfbPlatform& TheCTfbPlatform(PFNPLATFORMDATAPROC pfn) 
	{
		static CTfbPlatform tfb_platform(pfn);
		return tfb_platform;
	}
	~CTfbPlatform();                                           //��������
	CTfbPlatform(const CTfbPlatform&) = delete;                //��ֹ��������
	CTfbPlatform& operator = (const CTfbPlatform&) = delete;   //��ֹ

	//��ʼ��ƽ̨															   													  
	void InitializePlatform();
	//��¼һ�������˻�
	void Login(const string& userID, const string& password, bool b_t = false, bool b_n = false, bool bSimulate = false);
	//��ѯ�ʽ��˺�
	void QueryTradeAccount(const string& userID);
	//�ǳ�һ�������˻�
	void Logout(const string& userID);
	//�ǳ����н����˻�
	void LogoutAll();
	//�½�ί��
	void InsertOrder(const string& userID, const string& contract,
		char buy_or_sell, char open_or_cover, int order_num, double order_price = 0.0);
	//����ί��
	void CancelOrder(const string& userID, const string &OrderSysID, const string &ExchangeID);
	//��ѯ�ֲ�(����)
	void QueryPostion(const string& userID, const string& contract = "");
	//��ѯ�ֲ���ϸ
	void QueryPostionDetail(const string& userID, const string& contract = "");
	//��ѯ�ɽ���Ϣ,��ָ����ʼ���ڣ�����Ϊ��ʱĬ��Ϊ���ճɽ���Ϣ
	void QueryTrade(const string& userID, const string& strStartDate = "", const string& strEndDate = "");
	//��������
	void RestartStrategy(const string& userID, const string& strategyID);
	//�رղ���
	void CloseStrategy(const string& userID, const string& strategyID);

	CTfbTrade TfbTrade;
};


