#pragma once
#include "XJplatform_callbck_push_protocol.h"
#include <string>
using namespace std;

#ifdef XJSERVICESLIB_EXPORTS
#define DLL_PORT __declspec(dllexport)
#else 
#define DLL_PORT __declspec(dllimport)
#endif

class DLL_PORT IPlatformApi
{
public:
	//�̳�ʱ����һ��ƽ̨�������ͻص�����
	IPlatformApi(PFNPLATFORMDATAPROC pFn);
	virtual ~IPlatformApi() = 0;
	//��ʼ��ƽ̨
	virtual void InitializePlatform() = 0;
	//��¼һ�������˻�
	virtual void Login(const string& userID, const string& password, bool b_t = false, bool b_n = false, bool bSimulate = false) = 0;
	//��ѯ�ʽ��˺�
	virtual void QueryTradeAccount(const string& userID) = 0;
	//�ǳ�һ�������˻�
	virtual void Logout(const string& userID) = 0;
	//�ǳ����н����˻�
	virtual void LogoutAll() = 0;
	//�½�ί��
	virtual void InsertOrder(const string& userID, const string& contract,
		char buy_or_sell, char open_or_cover, int order_num, double order_price = 0.0) = 0;
	//����ί��
	virtual void CancelOrder(const string& userID, const string &strOrderNo, const string &ExchangeID) = 0;
	//��ѯ�ֲ�(����)
	virtual void QueryPostion(const string& userID, const string& contract = "") = 0;
	//��ѯ�ֲ���ϸ
	virtual void QueryPostionDetail(const string& userID, const string& contract = "") = 0;
	//��ѯ�ɽ���Ϣ,��ָ����ʼ���ڣ�����Ϊ��ʱĬ��Ϊ���ճɽ���Ϣ
	virtual void QueryTrade(const string& userID, const string& strStartDate = "", const string& strEndDate = "") = 0;
	//��������
	virtual void RestartStrategy(const string& userID, const string& strategyID) = 0;
	//�رղ���
	virtual void CloseStrategy(const string& userID, const string& strategyID) = 0;

protected:
	static PFNPLATFORMDATAPROC m_pPlatformDataProc;
};
