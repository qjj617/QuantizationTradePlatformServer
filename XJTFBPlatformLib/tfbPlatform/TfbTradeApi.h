// 2016.5.23   create by xiaozheng  ver:2.0.3.4
// 2016.7.18   modify by xiaozheng  ver:2.0.4.1
// 2016.8.9    modify by xiaozheng  ver:2.0.5.2
// 2016.9.22   modify by wzh        ver:3.0.0.1
#pragma once

#ifdef TFBTRADEAPI_EXPORTS
#define TFBTRADEAPI_API  extern "C"  __declspec(dllexport)
#else
#define TFBTRADEAPI_API  extern "C"  __declspec(dllimport)
#endif

#include <vector>
#include <map>
using namespace std;

typedef char  STR16[16];
typedef char  STR32[32];
typedef char  STR64[64];
typedef char  STR128[128];

// ������
int const TFBERR_MISS_LOGININFO                  = -401;    // ��¼ȱ�ٱ�Ҫ����Ϣ
int const TFBERR_MEM_USEOUT                      = -402;    // �ڴ����(����)
int const TFBERR_ERR_PARAM                       = -403;    // ��������
int const TFBERR_UNLOGIN                         = -404;    // ��δ��¼
int const TFBERR_CONN_MISS                       = -405;    // ʧȥ����(Զ�˶���)
int const TFBERR_CONN_BREAK                      = -406;    // �Ͽ�����(�����Ͽ�)
int const TFBERR_CONN_UNSUCC                     = -407;    // ����ʧ��
int const TFBERR_CONN_USEROUT                    = -408;    // ��¼�û���������
int const TFBERR_LOGIN_FAILD                     = -409;    // ��¼ʧ��
int const TFBERR_OPERATION_FAILD                 = -410;    // ����ʧ��
int const TFBERR_OVERAGE_LOGIN                   = -411;    // �Ѿ���¼���ٴε�¼
int const TFBERR_MERPINFO_FAIL                   = -412;    // ��ȡ��Ʒ��Ϣʧ��
int const TFBERR_CREATEDIR_FAIL                  = -413;    // ����Ŀ¼ʧ��
int const TFBERR_QUOTE_UNCONNECTED               = -414;    // ��δ���������鱨�۷��������Ժ���ܽ��ж���

int const TFBERR_API_WRONG_PORT                  = -400;    // VIP�ʺ��µ��˿ڴ���
int const TFBERR_USER_WRONG_PORT                 = -399;    // ��ͨ�ʺ��µ��˿ڴ���
int const TFBERR_API_ADD_ORDER                   = -398;    // VIP�û��޷������µ�
int const TFBERR_API_WRONG_USER                  = -397;    // û���ҵ������µ���VIP�û�
int const TFBERR_NO_COMMODITY                    = -396;    // ��Լû�ж�Ӧ����Ʒ
int const TFBERR_NO_START_TIME                   = -395;    // ����ʱ��Ϊ��
int const TFBERR_NO_END_TIME                     = -394;    // ����ʱ��Ϊ��
int const TFBERR_NO_MCODE                        = -393;    // ��Լ��Ϊ��
int const TFBERR_WRONG_ACCOUNT                   = -392;    // �µ��û�û�ҵ�
int const TFBERR_NO_ACCOUNT                      = -391;    // �µ��û�Ϊ��
int const TFBERR_SERVER_ERROR                    = -390;    // �������ڴ治��
int const TFBERR_SIMULATE_WRONG_USER             = -389;    // ģ�����ڻ�ʵ���û��޷��µ�
int const TFBERR_WRONG_TIME                      = -388;    // �ǿ���ʱ���޷��µ�
int const TFBERR_WRONG_BUY_PRICE                 = -387;    // ����ֹ��,ִ�м�Ӧ�ô���ֹ���,ֹ���Ӧ�ô������¼�
int const TFBERR_WRONG_SELL_PRICE                = -386;    // ����ֹ��,ִ�м�Ӧ��С��ֹ���,ֹ���Ӧ��С�����¼�
int const TFBERR_REAL_WRONG_USER                 = -385;    // ʵ���ڻ�ģ���û��޷��µ�
int const TFBERR_WRONG_USERTYPE                  = -384;    // �û����Ͳ���ȷ
int const TFBERR_PARENTS_ORDER                   = -383;    // �˻��������˻�,�޷��µ�
int const TFBERR_WRONG_ORDER_DIRECTION           = -382;    // �µ�������ʽ����
int const TFBERR_WRONG_ORDER_NUMBER              = -381;    // �µ���������
int const TFBERR_UNVERIFY_COMMODITY              = -380;    // ��ǰ��Ʒδ���,�޷�����
int const TFBERR_COMMODITY_NOPRICE               = -379;    // ��ǰ��Ʒû�м۸�,�޷�����
int const TFBERR_BROKER_DETAILS                  = -378;    // ��ƷӶ������ϸȱʧ,�޷�����
int const TFBERR_WRONG_STEP                      = -377;    // ��������ȷ
int const TFBERR_WRONG_CONTRACT_SIZE             = -376;    // ��Լֵ����ȷ
int const TFBERR_WRONG_CURRENCY                  = -375;    // ���ֲ���ȷ
int const TFBERR_WRONG_ACCURACY                  = -374;    // ���Ȳ���ȷ
int const TFBERR_WRONG_SUPERIORCODE              = -373;    // ��Ʒ���ֱ��벻��ȷ
int const TFBERR_LIMIT_COMMODITY                 = -372;    // �û���Ȩ�޽��׸���Ʒ
int const TFBERR_WRONG_ORDERTYPE                 = -371;    // �������Ͳ���ȷ
int const TFBERR_WRONG_LIMIT_ORDER_PRICE         = -370;    // �޼۵��۸���Ϊ����
int const TFBERR_WRONG_STOP_ORDERTYPE            = -369;    // ֹ���־����ȷ
int const TFBERR_WRONG_STOP_ORDER_PRICE          = -368;    // ֹ��ֹ��۸���Ϊ����
int const TFBERR_WRONG_LIMIT_ORDER_GAP           = -367;    // �޼ۼ۲��ȷ
int const TFBERR_WRONG_STOP_ORDER_GAP            = -366;    // ֹ��ۼ۲��ȷ
int const TFBERR_WRONG_COMMISSION                = -365;    // �����Ѳ���ȷ
int const TFBERR_WRONG_MARGIN_DETAILS            = -364;    // �û���֤����ϸ����ȷ
int const TFBERR_USER_LIMITED                    = -363;    // �û���ֹ����
int const TFBERR_COMMODITY_OPEN_POSITION_LIMIT   = -362;    // ����Ʒ��ֹ����
int const TFBERR_COMMODITY_CLOSE_POSITION_LIMIT  = -361;    // ����Ʒ��ֹƽ��
int const TFBERR_ORDER_DEALING                   = -360;    // ǰһ�����������ύ��,�޷�����¶���
int const TFBERR_CLOSE_POSITION_ORDER_ERROR      = -359;    // �óֲ�ƽ�ֵ����ύ����ƽ�ֵ����ݲ���ȷ
int const TFBERR_NOT_ENOUGH_MARGIN               = -358;    // ��֤����
int const TFBERR_SUPERIOR_NOT_ENOUGH_MARGIN      = -357;    // �ϼ��˺ű�֤����
int const TFBERR_SUPERIOR_LIMIT_TRADE            = -356;    // �ϼ��ʺ��޷����׸���Ʒ
int const TFBERR_FUTURES_USER_WRONG_COMMODITY    = -355;    // ������û��޷������ڻ�Ʒ��
int const TFBERR_NOBLEMETAL_USER_WRONG_COMMODITY = -354;    // �ڻ��û��޷����׹����Ʒ��
int const TFBERR_NOBLEMETAL_WRONG_COMMODITYCODE  = -353;    // �����Ʒ��û���ҵ���Ӧ�ڻ�Ʒ�ֱ���
int const TFBERR_NO_MAIN_CONTRACT                = -352;    // �����Ʒ�ֶ�Ӧ���ڻ�Ʒ��������Լû������
int const TFBERR_TOO_MANY_MAIN_CONTRACT          = -351;    // �����Ʒ�ֶ�Ӧ���ڻ�Ʒ��������Լ���ڶ��
int const TFBERR_APIUSER_FOR_MONITOR_ONLY        = -350;    // VIP�û���������ֻ���ܹ�̨�˺ſ���

int const  TFBERR_UNKNOW                         = -2000;       // δ֪�Ĵ���

// ��¼״̬
int const TFB_UNLOGIN  = 0;          // δ��¼
int const TFB_LOGINING = 1;          // ��¼��
int const TFB_ALREADY_LOGIN  = 2;    // �ѵ�½

// �µ�ʱ�Ķ�������
int const ORD_LIMIT    = 0;          // �ҵ�
int const ORD_STOP	   = 1;          // ��ʱ�ɽ�
int const ORD_MONI     = 2;          // ֻ��ģ�ⵥ
int const ORD_SUPERIOR = 3;          // ֻ�����ֵ�

// ֹ������
int const ST_NODEFINE  = 0;          // ��ֹ��
int const ST_LOSS      = 'L';        // �޼�ֹ��
int const ST_MARKET    = 'M';        // �м�ֹ��

// ����״̬
int const ORDSTATE_WORKING     = 1;     // ������
int const ORDSTATE_INACTIVE    = 2;     // ��Ч
int const ORDSTATE_PENDING     = 3;     // ����
int const ORDSTATE_ADDING      = 4;     // ������
int const ORDSTATE_CHANGING    = 5;     // �޸���
int const ORDSTATE_DELETING    = 6;     // ɾ����
int const ORDSTATE_INACTING    = 7;     // ��Ч��
int const ORDSTATE_PARTTRD_WRK = 8;     // �����ѳɽ����һ��ڹ�����
int const ORDSTATE_TRADED      = 9;     // �ѳɽ�
int const ORDSTATE_DELETED     = 10;    // ��ɾ��
int const ORDSTATE_APPROVEWAIT = 18;    // �ȴ���׼
int const ORDSTATE_TRADEDREP   = 20;    // traded & reported
int const ORDSTATE_DELETEDREP  = 21;    // deleted & reported
int const ORDSTATE_RESYNC_ABN  = 24;    // resync abnormal
int const ORDSTATE_PARTTRD_DEL = 28;    // partial traded & deleted
int const ORDSTATE_PARTTRD_REP = 29;    // partial traded & reported (deleted)
int const ORDSTATE_TIME_OUT    = 30;    // ��������Ч,���ڵ�

// �û�״̬
int const USER_STATUS_LOGIN     = 0x1;		//��ֹ��¼
int const USER_STATUS_STOP_PC   = 0x2;		//��ֹƽ��
int const USER_STATUS_STOP_JC   = 0x4;		//��ֹ����

int const INTEREST_LOAN         = 0x1;      //���ö����Ϣ
    
#define ERRPSZ_CANT_CONNECT     "����ʧ��"                  // ���ӷ�����ʧ�ܷ��ش����ַ���
#define ERRPSZ_MSG_OVERTIME     "������ʱ,��Ϊ�Ͽ�����"     // ���������ӳ�ʱ
#define ERRPSZ_MSG_OUTUSER      "�û��ڱ𴦵�½"            // �û��ڱ𴦵�¼
// ��������
enum ORD_TYPE
{
    OT_USERORDER    = 0,      // �û�����
    OT_API_ORDER    = 6       // ���򻯶���
};
// �ɽ�����
enum ORD_DEAL
{
    OD_PENDING      = 0,        // �ҵ�
    OD_REALTIME     = 1         // ��ʱ�ɽ�
};
// �ͻ�������
enum CLIENT_TYPE
{
    CT_FUTURES      = 0,        // �츻���ڻ�
    CT_NEW_ZEALAND  = 2,        // �������ڻ�
    CT_NOBLE_METAL  = 3         // ������ͻ���
};
// �۸�䶯����
enum QUOTE_TYPE
{
	QT_FIVE   = 0,   // �嵵���۱䶯
	QT_PRICE  = 1    // ��Ʒ�۸�䶯
};
// ����Ϊ�ӿ�Ҫʹ�õ������ݽṹ
// LoginRespond�ṹ�����õ�,��Ʒ������
struct TFBApiMerp
{
	STR16  pszMPCode;			    // ���ױ���
	int    nMpPrecision;			// С����󾫶�
	double dMppicstep;				// ��С���۲�*
    double dMargin;                 // ��֤��
    double dCost;                   // ������
	STR16  pszProductCode;			// ��Ʒ����
	STR16  pszProductName;			// ��Ʒ����
    STR64  pszForcedClose;			// ����ʱ��
    STR64  pszOverTime;				// ����ʱ��
    double dNowPrice;               // ��ǰ�ּ�
    STR64  pszPriceTime;            // �۸����ʱ��
};
// ��¼����
struct TFBApiLoginInfo
{
    STR64   pszIP;
    int     nPort;
    STR128  pszUserName;
    STR128  pszPassWord;
    int     nLoginType;
    bool    bAutoRelogin;
    STR128  pszClientVer;
};

//���û�ģʽ�£��ص������д����û��ṹ��
struct AdminUserRsp_Trade
{
	int				m_nUserID;				// �û�ID
	STR64			m_strUserName;			// �û���
	STR64			m_strPwd;				// �û�����
	int				m_nType;				// 0:�츻���ͻ��� 2:�������츻���ͻ��� 3:������츻���ͻ���
	int				m_bAutoRelogin;			// �Ƿ��Զ�����
	STR64			m_strClientVer;			// �ͻ��˰汾��
	STR64			m_strIP;				// ���ӵķ�����IP
	int				m_nPort;	            // ���ӵķ������˿�
	bool			m_bConnected;			// �Ƿ��Ѿ�����Զ�˻���
	STR128			m_strOpUserFlag;		// �û������ʶ���ַ�����ʽ��Ϊ"�û���,IP,�˿�"��ϵ��ַ��������ŷָ�
};

struct TFBServerInfo
{
    STR64   pszIP;
    int     nPort;
};
// ��¼����EX
struct TFBApiLoginInfoEX
{
    TFBServerInfo* tServer;
    int     nServerCount;
    STR128  pszUserName;
    STR128  pszPassWord;
    int     nLoginType;
    bool    bAutoRelogin;
    STR128  pszClientVer;
};
// ��¼�Ļ�Ӧ��Ϣ
struct TFBApiLoginRespond
{
	bool    bResult;        // ��¼�Ƿ�ɹ�
	STR128  pszReason;      // ʧ��ԭ��
	STR64   pszTime;        // ������ʱ��
	int     nUserId;        // �û�ID
    int     nRetCode;       // ��Ӧ����
    int     nStates;        // �û�״̬
    int     iInterest;      // ��Ϣ��ȡ��־λ

	int         nSizeOfMerp;// �ɽ���Ʒ�ָ���
	TFBApiMerp* pMerp;      // �ɽ���Ʒ��
};
// �ֲֵ�����,��User_InforRespond�ṹ�����õ�
struct TFBApiPosition
{
	int     nUserID;			// �û�ID
	int     nID;				// �ֲ�ID
	bool    bIsBuy;				// �������� true��  false��
	STR16   pszTPmcode;			// ��Ʒ��
	double  dPrice;				// �ɽ�����
	double  dNumber;			// �ֲ�����
	STR64   pszTime;			// ����ʱ��
	double  dMargin;			// �ֲֺͶ�����֤��,���ڹ����ڻ���ѯ
	STR32   pszMPName;			// ��Ʒ����
	int     nMPAmount;			// ÿ�ֵ���
	double  dMPxchange;			// ����
	STR16   pszCurrency;		// ��Ʒ����
	double  dTPNewLossP;        // ֹ��۸�
	double  dTPNewProfitP;      // ֹӯ�۸�
	double  dTPInterest;        // �ֲ���Ϣ
	STR16   pszPCode;	        // ��Ʒ��
	STR16   pszBindCode;        // �󶨱���
};
// ��������,��User_InforRespond�ṹ�����õ�
struct TFBApiOrder
{
	int		nUserID;			// �û�ID
	int		nOrderID;			// �������
	double	dPrice;				// �۸�		
	STR16 	pszMCode;			// ��Ʒ��
	STR32 	pszName;			// ��Ʒ����
	STR64   pszTime;			// �µ�ʱ��
	bool	bIsBuy;				// �������� true:�� false:��
	double	dNumber;			// ��������
	double	dOddNumber;			// δ�ɽ���
	bool	bAdverse;			// 0:���� 1:ƽ��
	int		nModeType;			// ����״̬
	int		nStopType;			// ֹ������
	double	dLossPrice;         // ֹ��۸�
	double	dMargin;			// �ֲֺͶ�����֤��,���ڹ����ڻ���ѯ
	STR16   pszPCode;	        // ��Ʒ��
	STR16   pszBindCode;        // �󶨱���
    int		nArbitrageId;       // ������������ID
    int		nTimePlus;          // ׷��ʱ��(����)
    double	nPricePlus;         // ׷����λ
    double	nPriceDiff;         // ���������ύʱ��ļ۲�
    STR32   pszRefId;           // ����ID
};
// ��������  ��ʹ��֮ǰ����memset��ʼ��,����汾�����������
struct TFBApiArbitrage
{
    int     iId;                //����ID
    int     iUserId;            //�����û�ID
    STR128  pszStrategyName;    //��������
    int     iStrategyStatus;    //����״̬
    STR32   pszFirstProduct;    //��һ�Ⱥ�Լ
    int     iFirstRatio;        //��һ�ȱ���
    STR32   pszSecondProduct;   //�ڶ��Ⱥ�Լ
    int     iSecondRatio;       //�ڶ��ȱ���
    int     iShowPrecision;	    //��ʾ��Сλ
    int     iBuySellRatio;      //����������
};
// ��Ʒ��Ϣ
struct TFBApiInstrument
{
    int     nTpID;     // ��ƷID
    STR32   pszTpCode; // ��Ʒ����
    STR32   pszTpName; // ��������
    STR32   pszMtCode; // ����������
    STR32   pszTcCode; // ���ִ���
};
// ��Լ��Ϣ
struct TFBApiProduct
{
    int      nMPId;             // ��ԼID
    STR32    pszMPCode;         // ��Լ����
    STR32    pszMPName;         // ��������
    STR32    pszTpCode;         // ��Ʒ����
    int      nMPAmount;         // ��Լֵ
    int      nMPPrecision;      // ����,С��λ��
    double   fMPPicStep;        // ��Լ��������
    int      nMPIsMain;         // �Ƿ�Ϊ������Լ
};
// ��ȡ�û���Ϣ�Ļ�Ӧ��Ϣ
struct TFBApiUserInforRespond
{
	int    nUserID;									//�û�ID
	STR64  pszName;									//�û�����
	double dNowFunds;								//�ʻ��ʽ�
	double dLoan;						            //�û����
	double dOutFreezingFunds;						//���𶳽��ʽ�
	double dOrderFreezingFunds;						//���������ʽ�
	double dPositionsFreezingFunds;					//�ֲֶ����ʽ�
	STR64  pszLocalTime;							//����������ʱ��
	int    nLoanMultiple;                           //�û�����

	int       nSizeOfPosition;                      // �ֲ���Ϣ
	TFBApiPosition* pPosition;
	int       nSizeOfOrder;                         // ������Ϣ
	TFBApiOrder*    pOrder;
    int       nSizeofArditrage;                     // ����������Ϣ
    TFBApiArbitrage* pArditrage;
};

// CArray<CArbitrageDTO, CArbitrageDTO&>	m_arrayArbitrageDTO;	

// ���½�����Ϣ�Ļ�Ӧ��Ϣ,����Ϣ�����ɽ�ʱ��������������,
struct TFBApiUpDateTrade
{
	int    nOrderId;				//����ID
	double dPrice;					//�ɽ��۸�
	double dNumber;					//�ɽ�����
	STR64  pszTime;					//�ɽ�ʱ��
	STR16  pszFillId;               //�ɽ����
    STR32  pszRefId;                //����ID
    STR32  pszInstrument;           //
    STR32  pszProduct;              //��Լ����
    int    nIsBuy;                  //��������  0��1��
    int    nUserID;                 //�û�ID

    int    nAdverse;                //��ƽ������,0:����,1:ƽ��
    int    nPositionId;             //�ֲ�ID
    double dProfit;                 //ӯ��
    double dCost;                   //������
    double dNowFunds;               //����
};
// ���¶�����Ϣ�Ļ�Ӧ��Ϣ,����Ϣ����״̬�ı�ʱ��������������
struct TFBApiUpdateOrder
{
	int    nUserId;				// �û�ID
	STR32  pszRefId;			// ����ID
	int    nOrderId;			// ����ID
	int    nOrderState;			// ����״̬	0:��ʼ״̬,��0:����״̬
	int    nType;				// ��������	0:����,1:ɾ������
	double dNumber;				// ����������
	double dOddNumber;			// δ�ɽ�����
	double dMargin;				// ������֤��
};

struct TFBApiLoadOrder
{
	int		Doid;			    // ����
	int		Douid;			    // �û�ID
	STR32   Domcode;		    // ��Ʒ����
	STR64   Dotime;			    // �ɽ�ʱ��
	int		Dotype;			    // 1:��0:��
	double  Doprice;		    // �ɽ��۸�
	double  Donumber;		    // ����������
	double  Dooddnum;		    // δ�ɽ�����
	int     DoAdverse;		    // 1:ƽ��,0����
	int     DOIsMatch;		    // 1:��������
	int     ModeType;		    // ���ֶ���״̬
	int     MakerType;		    // ����״̬
	int     UDType;			    // 0 ����  1 ����
	double  DoLossP;		    // ֹ��۸�
	double  DoProfitP;		    // ֹӯ�۸�
	double  DOBTPrice;		    // �ҵ�ʱ�۸�
	double  DOUpPrice;		    // ���޼۸�
	double  DODownPrice;	    // ���޼۸�
	int     DOIsInvalid;	    // ƽ�ֶ�Ӧ�ĳֲ�ID
	int     DOhSpId;		    // ����ID
	STR32   DOSPOrderId;	    // SP����ID��
	STR32   DOSPTradeId;	    // SP�ɽ����
	STR32   DOAttachId;		    // ����������
	STR32   DORefId;		    // �Զ��ο�ID
};
// ���ض�����Ϣ�Ļ�Ӧ��Ϣ
struct TFBApiLoadOrderRespond
{
	int nSizeofOrderItem;
	TFBApiLoadOrder* pOrderItem;
};

struct TFBApiLoadTrade
{
	int		oheId;			    // ����
	int		ohedoid;			// ����ID		
	int		oheuiid;			// �û�ID		
	STR16   ohemcode;		    // ��Ʒ����			
	STR64   ohedealtime;		// �ɽ�ʱ��		
	int		ohetype;			// 1:��0:��		
	double  ohenumber;		    // �ɽ�����			
	double  oheprice;		    // �ɽ��۸�			
	double  oheoddnum;		    // δ�ɽ�����,����ʱ�ֲ־���
	double  ohedealcost;	    // ������			
	double  oheProfit;		    // ӯ��				
	int     oheAdverse;		    // 1:ƽ��,0����,2:����
	double  oheNBalance;	    // ����				
	int     oheIsMatch;		    // �Ƿ���			
	int     ModeType;			// ���ֶ���״̬	
	int     MakerType;		    // ����״̬			
	int     UDType;			    // 0 ����  1 ����	
	double  oheLossP;		    // ��֤��			
	double  oheProfitP;	        // ����ӯ��
	double  oheBTPrice;	        // �ҵ�ʱ�۸�
	int     oheoid;			    // �ֲ�ID
	int     ohectype;			// ��̨�µ�����
	STR16   infocheck;	        // ���ֳɽ���¼��
	int     oheSpId;			// ����ID		
	int     oheState;			// ���˻�����ID	
	STR32   oheSPOrderId;		// SP����ID��	
	double  oheExchange;		// ����
	double  oheFatherCost;	    // �ϼ��ʺ�������
	STR32   oheRefId;			// �Զ��ο�ID
	int	    oheStopType;	    // ����ֹ������
	double  oheOrderPrice;		// ������
	double  oheStopPrice;		// ͻ�Ƽ�
	double  oheNewLossP;	    // ֹ��۸�
	double  oheNewProfitP;		// ֹӯ�۸�
};                                 
// ���سɽ���ʷʱ�Ļ�Ӧ��Ϣ
struct TFBApiLoadTradeRespond
{
	int nSizeofTradeItem;
	TFBApiLoadTrade* pTradeItem;
};
// �µ��ӿ�,�Ľṹ��ʹ��֮ǰ����memset��ʼ��,����汾������ɲ���Ҫ�ķ���
struct TFBApiAddOrder
{
    STR16     pszProdcode;        // ��Ʒ����
    bool      bIsBuy;             // ��������
    int       nNumberOfHand;      // ��������
    ORD_DEAL  nOrderType;         // �ɽ�����
    int       nStopType;          // ��ֹ��ST_NODEFINE ���� �޼�ֹ��ST_LOSS
    int       nPID;               // ƽ�ֵ��Ķ���ID,��ƽ�ֵ�ֻ����0
    ORD_TYPE  nType;              // ��������
    double    fPrice;             // �����۸�
    double    fStopLevel;         // ֹ��۸�
    int		  m_nArbitrageId;     // ������������ID
    int		  m_nTimePlus;		  // ׷��ʱ��(����)
    double	  m_nPricePlus;		  // ׷����λ
    double	  m_nPriceDiff;		  // ���������ύʱ��ļ۲�
    STR32     pszRefId;			  // �Զ��ο�ID
};
//2017-04-18 add data begin----
struct tPriceData {
    double mBuyPrice[5];     //�嵵���
    double mSellPrice[5];    //�嵵����
    double mBuyVolumn[5];    //�嵵����
    double mSellVolumn[5];   //�嵵����
    double mCurPrice;        //���±���/����
    double mClose;           //���̼�
    double mOpen;            //���̼�
    double mHigh;            //��߼�
    double mLow;             //��ͼ�
    double mVolumn;          //�ɽ���
    double mAmount;          //�ɽ���
    STR16  mProdCode;        //��Ʒcode
    STR64  mProdName;        //��ƷName
	int    mPriceType;       //�۸�䶯����
    long   mDate;            //���ݸ���ʱ��
};
//2017-04-18 add data end----
#define TFBDLLCALL __stdcall
//���󷽷�
typedef int (TFBDLLCALL *p_TFBAPI_Initialize)(const bool vInitQuote);
typedef int (TFBDLLCALL *p_TFBAPI_Uninitialize)();
typedef const char* (TFBDLLCALL *p_TFBAPI_GetUserFlag)(const char* strUserName, const char* strIP, int nPort);
typedef int (TFBDLLCALL *p_TFBAPI_Login)(const char* strOpUserFlag, TFBApiLoginInfo& tLoginInfo);
typedef int (TFBDLLCALL *p_TFBAPI_AddOrder)(const char* strOpUserFlag, const TFBApiAddOrder* pOrder);
typedef int (TFBDLLCALL *p_TFBAPI_DeleteOrder)(const char* strOpUserFlag, int nOrderID);
typedef int (TFBDLLCALL *p_TFBAPI_LoadOrderReport)(const char* strOpUserFlag);
typedef int (TFBDLLCALL *p_TFBAPI_LoadTradeReport)(const char* strOpUserFlag);
typedef int (TFBDLLCALL *p_TFBAPI_GetUserInfo)(const char* strOpUserFlag);
typedef int (TFBDLLCALL *p_TFBAPI_Logout)(const char* strOpUserFlag);
typedef int (TFBDLLCALL *p_TFBAPI_ChangePosition)(const char* strOpUserFlag, int nPosID,double fLossPrice,double fProfitPrice);
typedef int (TFBDLLCALL *p_TFBAPI_ChangeLoan)  (const char* strOpUserFlag, int nLoanMultiple);
typedef int (TFBDLLCALL *p_TFBAPI_ChangePassword)(const char* strOpUserFlag, const char* pszOldPassword,const char* pszNewPassword);
typedef int (TFBDLLCALL *p_TFBAPI_MerInfo)(const char* strOpUserFlag, const char* pszMerCode);
typedef int (TFBDLLCALL *p_TFBAPI_SetArbitrage)(const char* strOpUserFlag, int nCount, const TFBApiArbitrage* pArtrage);
typedef int (TFBDLLCALL *p_TFBAPI_SubscribePrice)(const char* strOpUserFlag, const char * prod_code, const int mode);   //���ġ�ȡ����������
typedef int (TFBDLLCALL *p_TFBAPI_GetPriceCount)(const char* strOpUserFlag);    //��ȡ���ĵ���������
typedef int (TFBDLLCALL *p_TFBAPI_LoginEX)(const char* strOpUserFlag, TFBApiLoginInfoEX& tLoginInfo);
typedef int (TFBDLLCALL *p_TFBAPI_SetSourceAddress)( char* pszSourceIP );

//��ȡ������Ѷ��Ϣ֮ǰ�����ȵ���p_TFBAPI_SubscribePrice���ĸ����顣
//��ȡ������Ѷ��Ϣ,price�贫��һ��������ռ�Ľṹ�������磺tPriceData price; ����&price
typedef int (TFBDLLCALL *p_TFBAPI_GetPriceByCode)(const char* strOpUserFlag, const char *prod_code, tPriceData *price);
typedef int   (TFBDLLCALL *p_TFBAPI_SetLogDir)(const char *pszLogDir);
typedef const char* (TFBDLLCALL *p_TFBAPI_GetLogDir)();

typedef int (TFBDLLCALL *p_TFBAPI_LoadInstrumentList)();
typedef int (TFBDLLCALL *p_TFBAPI_GetInstrumentCount)();
typedef int (TFBDLLCALL *p_TFBAPI_GetInstrument)(int nSerial,TFBApiInstrument* pInstrument);
typedef int (TFBDLLCALL *p_TFBAPI_GetInstrumentByCode)(const char* pszCode,TFBApiInstrument* pInstrument);

typedef int (TFBDLLCALL *p_TFBAPI_LoadProductInfoListByCode)(const char* pszInstrumentCode);
typedef int (TFBDLLCALL *p_TFBAPI_GetProductCount)(const char* pszInstrumentCode);
typedef int (TFBDLLCALL *p_TFBAPI_GetProduct)(const char* pszInstrumentCode,int nSerial,TFBApiProduct* pProduct);
typedef int (TFBDLLCALL *p_TFBAPI_GetProductByCode)(const char* pszProductCode,TFBApiProduct* pProduct);
// ע��ص�
typedef void (TFBDLLCALL *LoginReplyAddr)				(AdminUserRsp_Trade* pUserRsp, TFBApiLoginRespond* Respond);
typedef void (TFBDLLCALL *UserInfoReplyAddr)			(AdminUserRsp_Trade* pUserRsp, TFBApiUserInforRespond* Respond);
typedef void (TFBDLLCALL *AddOrderReplyAddr)			(AdminUserRsp_Trade* pUserRsp, int nRetCode,int nOrderID,char* pszMsg,char* pszRefId);
typedef void (TFBDLLCALL *DelOrderReplyAddr)			(AdminUserRsp_Trade* pUserRsp, int nRetCode,int nOrderID,char* pszMsg);
typedef void (TFBDLLCALL *UpdateTradeAddr)				(AdminUserRsp_Trade* pUserRsp, TFBApiUpDateTrade* Respond);
typedef void (TFBDLLCALL *UpdateOrderAddr)				(AdminUserRsp_Trade* pUserRsp, TFBApiUpdateOrder* Respond);
typedef void (TFBDLLCALL *LoadOrderReplyAddr)			(AdminUserRsp_Trade* pUserRsp, TFBApiLoadOrderRespond* Respond);
typedef void (TFBDLLCALL *LoadTradeReplyAddr)			(AdminUserRsp_Trade* pUserRsp, TFBApiLoadTradeRespond* Respond);
typedef void (TFBDLLCALL *ChangePositionReplyAddr)		(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg);
typedef void (TFBDLLCALL *ChangeLoanReplyAddr)			(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg);
typedef void (TFBDLLCALL *ChangePassWordReplyAddr)		(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg);
typedef void (TFBDLLCALL *LogoutReplyAddr)				(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg);
typedef void (TFBDLLCALL *ChangeLoginStateAddr)			(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg);
typedef void (TFBDLLCALL *MerInfoAddr)					(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg,const TFBApiMerp* Respond);
typedef void (TFBDLLCALL *ArbitrageAddr)				(AdminUserRsp_Trade* pUserRsp, int nRetCode,char* pszMsg);
typedef void (TFBDLLCALL *ApiPriceUpdateAddr )			(const tPriceData *price);
typedef void (TFBDLLCALL *InstrumentListReplyAddr)		(int nRetCode,const char* pszMsg);
typedef void (TFBDLLCALL *ProductListByCodeReplyAddr)	(const char* pszProductCode,int nRetCode,const char* pszMsg);

typedef void (TFBDLLCALL *p_TFBAPI_RegisterLoginReply)    (LoginReplyAddr    LoginReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterUserInfoReply) (UserInfoReplyAddr UserInfoReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterAddOrderReply) (AddOrderReplyAddr AddOrderReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterDelOrderReply) (DelOrderReplyAddr DelOrderReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterUpdateTradeReply)   (UpdateTradeAddr UpdateTrade);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterUpdateOrderReply)   (UpdateOrderAddr UpdateOrder);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterLoadOrderReport)    (LoadOrderReplyAddr      LoadOrderReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterLoadTradeReport)    (LoadTradeReplyAddr      LoadTradeReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterChangePositionReply)(ChangePositionReplyAddr ChangePositionReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterChangeLoanReply)    (ChangeLoanReplyAddr ChangeLoanReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterChangePassWordReply)(ChangePassWordReplyAddr ChangePassWordReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterLogoutReply)        (LogoutReplyAddr         LogoutReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterChangeLoginState)   (ChangeLoginStateAddr    ChangeLoginState);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterMerInfoReply)       (MerInfoAddr   MerInfo);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterArbitrageReply)     (ArbitrageAddr Artrage);
//2017-04-18 add ----  �Ѷ�������������������
typedef void (TFBDLLCALL *p_TFBAPI_RegisterApiPriceUpdate)      (ApiPriceUpdateAddr ApiPriceUpdate);

typedef void (TFBDLLCALL *p_TFBAPI_RegisterProductListReply)    (ProductListByCodeReplyAddr ProductListByCodeReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterInstrumentListReply) (InstrumentListReplyAddr    InstrumentListReply);

///****************************�ӿں���������:***********************************/
//// ���󷽷�
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_Initialize();
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_Uninitialize();
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_SetLoginInfo(const char* pszIP,int nPort,const char* pszUserName,const char* pszPassWord,int nLoginType);
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_Login(bool bAutoRelogin);
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_ChangePassword(const char*pszOldPassword,const char* pszNewPassword);
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_AddOrder(const TFBApiAddOrder* pOrder);
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_DeleteOrder(int nOrderID);
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_LoadOrderReport();
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_LoadTradeReport();
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_GetUserInfo();
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_Logout();
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_ChangePosition(int nPosID,double fLossPrice,double fProfitPrice);
//TFBTRADEAPI_API int TFBDLLCALL TFBAPI_MerInfo(const char* pszMerCode);
//// ע��ص�
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterLoginReply   (LoginReplyAddr LoginReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterUserInfoReply(UserInfoReplyAddr UserInfoReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterAddOrderReply(AddOrderReplyAddr AddOrderReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterDelOrderReply(DelOrderReplyAddr DelOrderReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterUpdateTradeReply (UpdateTradeAddr UpdateTrade);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterUpdateOrderReply (UpdateOrderAddr UpdateOrder);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterLoadOrderReport    (LoadOrderReplyAddr LoadOrderReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterLoadTradeReport    (LoadTradeReplyAddr LoadOrderReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterChangePositionReply(ChangePositionReplyAddr ChangePositionReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterChangePassWordReply(ChangePassWordReplyAddr ChangePassWordReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterLogoutReply        (LogoutReplyAddr LogoutReply);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterChangeLoginState   (ChangeLoginStateAddr ChangeLoginState);
//TFBTRADEAPI_API void TFBDLLCALL TFBAPI_RegisterMerInfoReply       (MerInfoAddr MerInfo);





