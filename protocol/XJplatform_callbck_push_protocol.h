#pragma once


#include <string>
using namespace std;

//����ƽ̨������Ӧ����
enum XJ_PUSH_PLATFORMDATA_RSP
{
	RSP_NULL = 0,
	//������ʾ��Ϣ,��Ӧ XJRspShowTipMessage �ṹ��
	RSP_SHOW_TIPMESSAGE,
	//���ͺ�Լ��Ϣ,��Ӧ XJRspContractInfo �ṹ��
	RSP_QRY_CONTRACTINFO,
	//�˺ŵ���,��Ӧ XJRspLoginInfo �ṹ��
	RSP_USER_RLOGIN,
	//�˺ŵǳ�,��Ӧ XJRspLogoutInfo �ṹ��
	RSP_USER_LOGOUT,
	//�����ʽ��˺�,��Ӧ XJRspFundAccountInfo �ṹ��
	RSP_QRY_FUNDACCOUNT,
	//�����ʽ��˺Ų���,��Ӧ XJRspAccountStrategyInfo �ṹ��
	RSP_FUNDACCOUNT_STRATEGY,
	//�ʽ��˺ųֲ�,��Ӧ XJRspAccountPosition �ṹ��
	RSP_FUNDACCOUNT_POSITION,
	//ί�б��,��Ӧ XJRspOrderInfo �ṹ��
	RSP_CHANGE_ORDER,
	//���ͳɽ���Ϣ,��Ӧ XJRspTradeInfo �ṹ��
	RSP_QRY_TRADEINFO
};

//��Ʒ����
enum PRODUCT_TYPE
{
	//�ڻ�
	PDT_FUTURES = '1',
	//��Ȩ
	PDT_OPTION = '2',
	//���
	PDT_COMBINATION = '3',
};

//������������
enum SIDE_TYPE
{
	//��
	SIZE_BUY = '0',
	//��
	SIZD_SELL = '1',
};

//��ƽ����
enum POSITION_EFFECT_TYPE
{
	//����
	PF_OPEN = '0',
	//ƽ��
	PF_CLOSE = '1',
	//ƽ��
	PF_CLOSE_TODAY = '3',
	//ƽ��
	PF_CLOSE_YESTERDAY = '4',
};

//�ֲַ���
enum POSITION_DIRECTOIN_TYPE
{
	//��
	PD_NET = '1',
	//��ͷ
	PD_LONG = '2',
	//��ͷ
	PD_SHORT = '3'
};

//ί��״̬
enum ORDER_STATE_TYPE
{
	//��ȫ�ɽ�
	OS_FINISHED = '0',
	//����
	OS_CANCELED = '1',
	//�Ŷ�
	OS_QUEUED = '2',
	//�ѹ���
	OS_SUPPENDED = '3',
	//���ֳɽ�
	OS_PARTFINISHED = '4',
};

//ƽ̨����
enum PLATFORM_TYPE
{
	PF_NULL = 0,
	//CTP
	PF_CTP,
	//��ʢ
	PF_Esunny,
	//�츻��
	PF_TFB
};

//��Ϣͷ
struct XJRspMspHead
{
	virtual ~XJRspMspHead() {}
	//ƽ̨����
	PLATFORM_TYPE pfType;
	//������
	int nErr;
	//��ʾ��Ϣ
	string strMsg;
};

//��ʾ��Ϣ
struct XJRspShowTipMessage : XJRspMspHead
{
	//��Ϣͷ����ʾ��Ϣ����ϢͷszMsg��
};

//��Լ��Ϣ
struct XJRspContractInfo : XJRspMspHead
{
	//��Լ����
	string strContractNo;
	//��Լ����
	string strContractName;
	//��Լ����
	char chContractType;
	//���������
	string strExchangeNo;
	//��Ʒ����
	string strProductID;
	//��Ʒ����
	char chProductType;
	//������
	string strOpenDate;
	//������
	string strExpireDate;
	//ִ�м�
	double dStrikePrice;
};

//�û����뷵����Ϣ
struct XJRspLoginInfo : XJRspMspHead
{
	//�û���
	string strUserName;
	//��ǰ�������� 
	string strTradingDate;
	//����ʱ��
	string strLoginTime;
	//���͹�˾����
	string strBrokerID;
	//����ƽ̨����
	string strSystemName;
};

//�û��ǳ�������Ϣ
struct XJRspLogoutInfo : XJRspMspHead
{
	//�û���
	string strUserName;
	//�ǳ�ԭ��
	string strLogoutReason;
};

//�ʽ��˺ŷ�����Ϣ
struct XJRspFundAccountInfo : XJRspMspHead
{
	//�ʽ��˺�
	string strAccountId;
	//����
	string strCurrency;
	//�����ʽ�
	double dAvailable;
	//���ս��	
	double PreBalance;
	//ƽ��ӯ��
	double CloseProfit;
	//�ֲ�ӯ��
	double PositionProfit;
	//������
	double Commission;
	//�ֱֲ�֤��
	double PositionMargin;
	//�����ʽ�
	double FrozenCash;
	//�����Ʒռ�ñ�֤��
	double SpecProductMargin;
	//�����Ʒ���ᱣ֤��
	double SpecProductFrozenMargin;
	//�����Ʒ������
	double SpecProductCommission;
	//�����Ʒ����������
	double SpecProductFrozenCommission;
	//�����Ʒ�ֲ�ӯ��
	double SpecProductPositionProfit;
	//�����Ʒƽ��ӯ��
	double SpecProductCloseProfit;
};

//���Բ���
struct XJStrategyParam
{
	//��Ʒ����
	string strCommodityName;
	//MABrate
	int nMABrate;
	//MABLen
	int nMABLen;
	//initialcp
	int nInitialCP;
	//finalper
	float fFinalPer;
	//perm
	float fPerm;
	//MaxRangeRate
	float fMaxRangeRate;
	//PrevBars
	int nPrevBars;
	//monthhour
	int nMonthHour;
	//ContractUnit
	int nContractUnit;
	//MarginRatio
	float fMarginRatio;
	//minp
	float fMinp;
};

//�ʽ��˺Ų�����Ϣ
struct XJRspAccountStrategyInfo : XJRspMspHead
{
	//�ʽ��˺�
	string strAccountId;
	//������
	string strStrategyName;
	//��Ʒ����
	string strCommodityName;
	//���۳ֲ�
	int nTheoreticalPosition;
	//ʵ�ʳֲ�
	int nPracticalPosition;
	//���һ�ε���ʱ��
	string strLastInvokeTime;
	//���Բ���
	//XJStrategyParam StrategyParam;
};

//�ʽ��˺ųֲ�
struct XJRspAccountPosition : XJRspMspHead
{
	//�ʽ��˺�
	string strAccountId;
	//��Ʒ���
	string strCommodityId;
	//��Ʒ����
	string strCommodityName;
	//��Ʒ����
	char chCommodityType;
	//��Լ
	string strContractNo;
	//����
	char chOrderSide;
	//�ֲܳ�
	int nPositions;
	//���־���
	double dOpenAveragePrice;
	//ƽ��ӯ��
	double dCloseProfit;
	//����ӯ��
	double dFloatProfit;
	//��֤��
	double dMargin;
};

//ί�б��
struct XJRspOrderInfo : XJRspMspHead
{
	//�ʽ��˺�
	string strAccountId;
	//���������
	string strExchangeId;
	//ί�б��
	string strOrderNo;
	//ί��ʱ��
	string strInsertDataTime;
	//��Ʒ���
	string strCommodityId;
	//��Ʒ����
	string strCommodityName;
	//��Ʒ����
	char chCommodityType;
	//��Լ
	string strContrctNo;
	//����
	char chOrderSide;
	//ƽ����־
	char chOffset;
	//ί�м۸�
	double dOrderPrice;
	//ί������
	int nOrderVolume;
	//�ѳɽ���
	int nnMatchVolume;
	//ί��״̬
	char chOrderstate;
};

//�ɽ���Ϣ
struct XJRspTradeInfo : XJRspMspHead
{
	//�ʽ��˺�
	string strAccountId;
	//ί�б��
	string strOrderNo;
	//�ɽ�ʱ��
	string strTradeDataTime;
	//��Լ
	string strContrctNo;
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

typedef int(*PFNPLATFORMDATAPROC)(int, XJRspMspHead*);
