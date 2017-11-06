#pragma once
#include "../protocol/XJplatform_callbck_push_protocol.h"
#include "../Common/Common.h"
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

class CAccountInfo
{
public:
	CAccountInfo();
	~CAccountInfo();

	//�����ʽ��˻���Ϣ
	void SetAccountInfo(XJRspFundAccountInfo *pAccountInfo);
	//���õ�����Ϣ
	void SetLoginInfo(XJRspLoginInfo *pLoginInfo);
	//����ƽ̨����
	void SetPlatformType(PLATFORM_TYPE pfType);
	//��ѯƽ̨����
	PLATFORM_TYPE GetPlatformType();
	//���Ӳ�����Ϣ
	void AddStrategyInfo(XJRspAccountStrategyInfo *pStrategyInfo);
	//ɾ��������Ϣ
	void DeleteStrategyInfo(XJRspAccountStrategyInfo *pStrategyInfo);
	//���ӳֲ���Ϣ
	void AddPositionInfo(XJRspAccountPosition *pPositionInfo);
	//ɾ���ֲ���Ϣ
	void DeletePositionInfo(XJRspAccountPosition *pPositionInfo);
	//����ί����Ϣ
	void AddOrderInfo(XJRspOrderInfo *pOrderInfo);
	//ɾ��ί����Ϣ
	void DeleteOrderInfo(XJRspOrderInfo *pOrderInfo);
	//���ӳɽ���Ϣ
	void AddTradeInfo(XJRspTradeInfo *pTradeInfo);
	//ɾ���ɽ���Ϣ
	void DeleteTradeInfo(XJRspTradeInfo *pTradeInfo);
	//��ѯ������Ϣ
	const XJRspLoginInfo* GetLoginInfo();
	//��ѯ�ʽ��˻���Ϣ
	const XJRspFundAccountInfo* GetAccountInfo();
	//��ѯ������Ϣ
	const list<XJRspAccountStrategyInfo *>& GetStrategyInfos();
	//��ѯ�ֲ���Ϣ
	const list<XJRspAccountPosition *>& GetPositionInfos();
	//���ݺ�Լ�Ų��ҳֲ���Ϣ
	XJRspAccountPosition *GetPositionInfoByContractNo(const string &strContractNo);
	//���ݺ�Լ�����óֲ���Ϣ
	void SetPositionInfoByContractNo(const string &strContractNo, XJRspAccountPosition *pPositionInfo);
	//��ѯί����Ϣ
	const list<XJRspOrderInfo*>& GetOrderInfos();
	//����ί�б�Ų���ί����Ϣ
	XJRspOrderInfo* GetOrderInfosByOrderNo(const string &strOrderNo);
	//����ί�б������ί����Ϣ
	void SetOrderInfosByOrderNo(const string &strOrderNo, XJRspOrderInfo* pOrderInfo);
	//����ί�б�����óɽ���Ϣ
	void SetTradeInfoByOrderNo(const string &strOrderNo, XJRspTradeInfo *pTradeInfo);
	//�жϳɽ���Ϣ�Ƿ��ڳɽ���Ϣ������
	bool IsInTradeInfolist(const string &strOrderNo);
	//��ѯ�ɽ���Ϣ
	const list<XJRspTradeInfo*>& GetTradeInfos();

private:
	PLATFORM_TYPE m_PlatformType;
	//�˻�������Ϣ
	XJRspLoginInfo* m_pLoginInfo;
	//�ʽ��˻���Ϣ
	XJRspFundAccountInfo* m_pAccountInfo;
	//������Ϣ����
	list<XJRspAccountStrategyInfo *> m_StrategyInfos_list;
	//�ֲ���Ϣ����
	list<XJRspAccountPosition *> m_PositionsInfos_list;
	//ί����Ϣ����
	list<XJRspOrderInfo*> m_OrderInfos_list;
	//�ɽ���Ϣ����
	list<XJRspTradeInfo*> m_TradeInfos_list;
};

