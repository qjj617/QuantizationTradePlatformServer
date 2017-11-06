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

// 错误码
int const TFBERR_MISS_LOGININFO                  = -401;    // 登录缺少必要的信息
int const TFBERR_MEM_USEOUT                      = -402;    // 内存错误(严重)
int const TFBERR_ERR_PARAM                       = -403;    // 参数错误
int const TFBERR_UNLOGIN                         = -404;    // 尚未登录
int const TFBERR_CONN_MISS                       = -405;    // 失去连接(远端断连)
int const TFBERR_CONN_BREAK                      = -406;    // 断开连接(主动断开)
int const TFBERR_CONN_UNSUCC                     = -407;    // 连接失败
int const TFBERR_CONN_USEROUT                    = -408;    // 登录用户被挤下线
int const TFBERR_LOGIN_FAILD                     = -409;    // 登录失败
int const TFBERR_OPERATION_FAILD                 = -410;    // 操作失败
int const TFBERR_OVERAGE_LOGIN                   = -411;    // 已经登录后再次登录
int const TFBERR_MERPINFO_FAIL                   = -412;    // 获取商品信息失败
int const TFBERR_CREATEDIR_FAIL                  = -413;    // 创建目录失败
int const TFBERR_QUOTE_UNCONNECTED               = -414;    // 还未连接上行情报价服务器，稍后才能进行订阅

int const TFBERR_API_WRONG_PORT                  = -400;    // VIP帐号下单端口错误
int const TFBERR_USER_WRONG_PORT                 = -399;    // 普通帐号下单端口错误
int const TFBERR_API_ADD_ORDER                   = -398;    // VIP用户无法单独下单
int const TFBERR_API_WRONG_USER                  = -397;    // 没有找到合适下单的VIP用户
int const TFBERR_NO_COMMODITY                    = -396;    // 合约没有对应的商品
int const TFBERR_NO_START_TIME                   = -395;    // 开盘时间为空
int const TFBERR_NO_END_TIME                     = -394;    // 收盘时间为空
int const TFBERR_NO_MCODE                        = -393;    // 合约码为空
int const TFBERR_WRONG_ACCOUNT                   = -392;    // 下单用户没找到
int const TFBERR_NO_ACCOUNT                      = -391;    // 下单用户为空
int const TFBERR_SERVER_ERROR                    = -390;    // 服务器内存不足
int const TFBERR_SIMULATE_WRONG_USER             = -389;    // 模拟盘期货实盘用户无法下单
int const TFBERR_WRONG_TIME                      = -388;    // 非开市时间无法下单
int const TFBERR_WRONG_BUY_PRICE                 = -387;    // 买入止损单,执行价应该大于止损价,止损价应该大于最新价
int const TFBERR_WRONG_SELL_PRICE                = -386;    // 卖出止损单,执行价应该小于止损价,止损价应该小于最新价
int const TFBERR_REAL_WRONG_USER                 = -385;    // 实盘期货模拟用户无法下单
int const TFBERR_WRONG_USERTYPE                  = -384;    // 用户类型不正确
int const TFBERR_PARENTS_ORDER                   = -383;    // 账户存在子账户,无法下单
int const TFBERR_WRONG_ORDER_DIRECTION           = -382;    // 下单买卖格式错误
int const TFBERR_WRONG_ORDER_NUMBER              = -381;    // 下单手数错误
int const TFBERR_UNVERIFY_COMMODITY              = -380;    // 当前商品未审核,无法操作
int const TFBERR_COMMODITY_NOPRICE               = -379;    // 当前商品没有价格,无法操作
int const TFBERR_BROKER_DETAILS                  = -378;    // 商品佣金组明细缺失,无法操作
int const TFBERR_WRONG_STEP                      = -377;    // 步长不正确
int const TFBERR_WRONG_CONTRACT_SIZE             = -376;    // 合约值不正确
int const TFBERR_WRONG_CURRENCY                  = -375;    // 币种不正确
int const TFBERR_WRONG_ACCURACY                  = -374;    // 精度不正确
int const TFBERR_WRONG_SUPERIORCODE              = -373;    // 商品上手编码不正确
int const TFBERR_LIMIT_COMMODITY                 = -372;    // 用户无权限交易该商品
int const TFBERR_WRONG_ORDERTYPE                 = -371;    // 订单类型不正确
int const TFBERR_WRONG_LIMIT_ORDER_PRICE         = -370;    // 限价单价格不能为负数
int const TFBERR_WRONG_STOP_ORDERTYPE            = -369;    // 止损标志不正确
int const TFBERR_WRONG_STOP_ORDER_PRICE          = -368;    // 止损单止损价格不能为负数
int const TFBERR_WRONG_LIMIT_ORDER_GAP           = -367;    // 限价价差不正确
int const TFBERR_WRONG_STOP_ORDER_GAP            = -366;    // 止损价价差不正确
int const TFBERR_WRONG_COMMISSION                = -365;    // 手续费不正确
int const TFBERR_WRONG_MARGIN_DETAILS            = -364;    // 用户保证金明细不正确
int const TFBERR_USER_LIMITED                    = -363;    // 用户禁止交易
int const TFBERR_COMMODITY_OPEN_POSITION_LIMIT   = -362;    // 该商品禁止建仓
int const TFBERR_COMMODITY_CLOSE_POSITION_LIMIT  = -361;    // 该商品禁止平仓
int const TFBERR_ORDER_DEALING                   = -360;    // 前一个订单正在提交中,无法添加新订单
int const TFBERR_CLOSE_POSITION_ORDER_ERROR      = -359;    // 该持仓平仓单已提交或者平仓单数据不正确
int const TFBERR_NOT_ENOUGH_MARGIN               = -358;    // 保证金不足
int const TFBERR_SUPERIOR_NOT_ENOUGH_MARGIN      = -357;    // 上级账号保证金不足
int const TFBERR_SUPERIOR_LIMIT_TRADE            = -356;    // 上级帐号无法交易该商品
int const TFBERR_FUTURES_USER_WRONG_COMMODITY    = -355;    // 贵金属用户无法交易期货品种
int const TFBERR_NOBLEMETAL_USER_WRONG_COMMODITY = -354;    // 期货用户无法交易贵金属品种
int const TFBERR_NOBLEMETAL_WRONG_COMMODITYCODE  = -353;    // 贵金属品种没有找到对应期货品种编码
int const TFBERR_NO_MAIN_CONTRACT                = -352;    // 贵金属品种对应的期货品种主力合约没有设置
int const TFBERR_TOO_MANY_MAIN_CONTRACT          = -351;    // 贵金属品种对应的期货品种主力合约存在多个
int const TFBERR_APIUSER_FOR_MONITOR_ONLY        = -350;    // VIP用户单独交易只对总柜台账号开放

int const  TFBERR_UNKNOW                         = -2000;       // 未知的错误

// 登录状态
int const TFB_UNLOGIN  = 0;          // 未登录
int const TFB_LOGINING = 1;          // 登录中
int const TFB_ALREADY_LOGIN  = 2;    // 已登陆

// 下单时的订单类型
int const ORD_LIMIT    = 0;          // 挂单
int const ORD_STOP	   = 1;          // 即时成交
int const ORD_MONI     = 2;          // 只下模拟单
int const ORD_SUPERIOR = 3;          // 只下上手单

// 止损类型
int const ST_NODEFINE  = 0;          // 非止损单
int const ST_LOSS      = 'L';        // 限价止损
int const ST_MARKET    = 'M';        // 市价止损

// 订单状态
int const ORDSTATE_WORKING     = 1;     // 工作中
int const ORDSTATE_INACTIVE    = 2;     // 无效
int const ORDSTATE_PENDING     = 3;     // 待定
int const ORDSTATE_ADDING      = 4;     // 增加中
int const ORDSTATE_CHANGING    = 5;     // 修改中
int const ORDSTATE_DELETING    = 6;     // 删除中
int const ORDSTATE_INACTING    = 7;     // 无效中
int const ORDSTATE_PARTTRD_WRK = 8;     // 部分已成交并且还在工作中
int const ORDSTATE_TRADED      = 9;     // 已成交
int const ORDSTATE_DELETED     = 10;    // 已删除
int const ORDSTATE_APPROVEWAIT = 18;    // 等待批准
int const ORDSTATE_TRADEDREP   = 20;    // traded & reported
int const ORDSTATE_DELETEDREP  = 21;    // deleted & reported
int const ORDSTATE_RESYNC_ABN  = 24;    // resync abnormal
int const ORDSTATE_PARTTRD_DEL = 28;    // partial traded & deleted
int const ORDSTATE_PARTTRD_REP = 29;    // partial traded & reported (deleted)
int const ORDSTATE_TIME_OUT    = 30;    // 交易所无效,过期单

// 用户状态
int const USER_STATUS_LOGIN     = 0x1;		//禁止登录
int const USER_STATUS_STOP_PC   = 0x2;		//禁止平仓
int const USER_STATUS_STOP_JC   = 0x4;		//禁止建仓

int const INTEREST_LOAN         = 0x1;      //信用额度利息
    
#define ERRPSZ_CANT_CONNECT     "连接失败"                  // 连接服务器失败返回错误字符串
#define ERRPSZ_MSG_OVERTIME     "心跳超时,认为断开连接"     // 服务器连接超时
#define ERRPSZ_MSG_OUTUSER      "用户在别处登陆"            // 用户在别处登录
// 订单类型
enum ORD_TYPE
{
    OT_USERORDER    = 0,      // 用户订单
    OT_API_ORDER    = 6       // 程序化订单
};
// 成交类型
enum ORD_DEAL
{
    OD_PENDING      = 0,        // 挂单
    OD_REALTIME     = 1         // 即时成交
};
// 客户端类型
enum CLIENT_TYPE
{
    CT_FUTURES      = 0,        // 天富宝期货
    CT_NEW_ZEALAND  = 2,        // 新西兰期货
    CT_NOBLE_METAL  = 3         // 贵金属客户端
};
// 价格变动类型
enum QUOTE_TYPE
{
	QT_FIVE   = 0,   // 五档报价变动
	QT_PRICE  = 1    // 商品价格变动
};
// 以下为接口要使用到的数据结构
// LoginRespond结构体中用到,商品的数据
struct TFBApiMerp
{
	STR16  pszMPCode;			    // 交易编码
	int    nMpPrecision;			// 小数点后精度
	double dMppicstep;				// 最小报价差*
    double dMargin;                 // 保证金
    double dCost;                   // 手续费
	STR16  pszProductCode;			// 商品编码
	STR16  pszProductName;			// 商品名字
    STR64  pszForcedClose;			// 收市时间
    STR64  pszOverTime;				// 到期时间
    double dNowPrice;               // 当前现价
    STR64  pszPriceTime;            // 价格更新时间
};
// 登录参数
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

//多用户模式下，回调函数中带的用户结构体
struct AdminUserRsp_Trade
{
	int				m_nUserID;				// 用户ID
	STR64			m_strUserName;			// 用户名
	STR64			m_strPwd;				// 用户密码
	int				m_nType;				// 0:天富宝客户端 2:新西兰天富宝客户端 3:贵金属天富宝客户端
	int				m_bAutoRelogin;			// 是否自动重连
	STR64			m_strClientVer;			// 客户端版本号
	STR64			m_strIP;				// 连接的服务器IP
	int				m_nPort;	            // 连接的服务器端口
	bool			m_bConnected;			// 是否已经连接远端机器
	STR128			m_strOpUserFlag;		// 用户区别标识，字符串形式，为"用户名,IP,端口"组合的字符串，逗号分隔
};

struct TFBServerInfo
{
    STR64   pszIP;
    int     nPort;
};
// 登录参数EX
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
// 登录的回应消息
struct TFBApiLoginRespond
{
	bool    bResult;        // 登录是否成功
	STR128  pszReason;      // 失败原因
	STR64   pszTime;        // 服务器时间
	int     nUserId;        // 用户ID
    int     nRetCode;       // 回应编码
    int     nStates;        // 用户状态
    int     iInterest;      // 利息收取标志位

	int         nSizeOfMerp;// 可交易品种个数
	TFBApiMerp* pMerp;      // 可交易品种
};
// 持仓的数据,在User_InforRespond结构体中用到
struct TFBApiPosition
{
	int     nUserID;			// 用户ID
	int     nID;				// 持仓ID
	bool    bIsBuy;				// 买卖类型 true买  false卖
	STR16   pszTPmcode;			// 商品码
	double  dPrice;				// 成交均价
	double  dNumber;			// 持仓手数
	STR64   pszTime;			// 建仓时间
	double  dMargin;			// 持仓和订单保证金,用于国际期货查询
	STR32   pszMPName;			// 商品名称
	int     nMPAmount;			// 每手的量
	double  dMPxchange;			// 汇率
	STR16   pszCurrency;		// 商品币种
	double  dTPNewLossP;        // 止损价格
	double  dTPNewProfitP;      // 止盈价格
	double  dTPInterest;        // 持仓利息
	STR16   pszPCode;	        // 产品码
	STR16   pszBindCode;        // 绑定编码
};
// 订单数据,在User_InforRespond结构体中用到
struct TFBApiOrder
{
	int		nUserID;			// 用户ID
	int		nOrderID;			// 订单编号
	double	dPrice;				// 价格		
	STR16 	pszMCode;			// 商品码
	STR32 	pszName;			// 商品名称
	STR64   pszTime;			// 下单时间
	bool	bIsBuy;				// 订单类型 true:买 false:卖
	double	dNumber;			// 订立手数
	double	dOddNumber;			// 未成交量
	bool	bAdverse;			// 0:建仓 1:平仓
	int		nModeType;			// 订单状态
	int		nStopType;			// 止损类型
	double	dLossPrice;         // 止损价格
	double	dMargin;			// 持仓和订单保证金,用于国际期货查询
	STR16   pszPCode;	        // 产品码
	STR16   pszBindCode;        // 绑定编码
    int		nArbitrageId;       // 套利策略索引ID
    int		nTimePlus;          // 追单时间(毫秒)
    double	nPricePlus;         // 追单点位
    double	nPriceDiff;         // 套利订单提交时候的价差
    STR32   pszRefId;           // 引用ID
};
// 套利策略  在使用之前请先memset初始化,以免版本更替带来问题
struct TFBApiArbitrage
{
    int     iId;                //索引ID
    int     iUserId;            //策略用户ID
    STR128  pszStrategyName;    //策略名称
    int     iStrategyStatus;    //策略状态
    STR32   pszFirstProduct;    //第一腿合约
    int     iFirstRatio;        //第一腿比例
    STR32   pszSecondProduct;   //第二腿合约
    int     iSecondRatio;       //第二腿比例
    int     iShowPrecision;	    //显示最小位
    int     iBuySellRatio;      //买卖量比例
};
// 商品信息
struct TFBApiInstrument
{
    int     nTpID;     // 商品ID
    STR32   pszTpCode; // 商品代码
    STR32   pszTpName; // 简体名称
    STR32   pszMtCode; // 交易所代码
    STR32   pszTcCode; // 币种代码
};
// 合约信息
struct TFBApiProduct
{
    int      nMPId;             // 合约ID
    STR32    pszMPCode;         // 合约代码
    STR32    pszMPName;         // 简体名称
    STR32    pszTpCode;         // 商品代码
    int      nMPAmount;         // 合约值
    int      nMPPrecision;      // 精度,小数位数
    double   fMPPicStep;        // 合约步长基数
    int      nMPIsMain;         // 是否为主力合约
};
// 获取用户信息的回应消息
struct TFBApiUserInforRespond
{
	int    nUserID;									//用户ID
	STR64  pszName;									//用户名称
	double dNowFunds;								//帐户资金
	double dLoan;						            //用户借款
	double dOutFreezingFunds;						//出金冻结资金
	double dOrderFreezingFunds;						//订单冻结资金
	double dPositionsFreezingFunds;					//持仓冻结资金
	STR64  pszLocalTime;							//服务器本地时间
	int    nLoanMultiple;                           //用户借款倍数

	int       nSizeOfPosition;                      // 持仓信息
	TFBApiPosition* pPosition;
	int       nSizeOfOrder;                         // 订单信息
	TFBApiOrder*    pOrder;
    int       nSizeofArditrage;                     // 套利策略信息
    TFBApiArbitrage* pArditrage;
};

// CArray<CArbitrageDTO, CArbitrageDTO&>	m_arrayArbitrageDTO;	

// 更新交易信息的回应消息,该消息订单成交时服务器主动推送,
struct TFBApiUpDateTrade
{
	int    nOrderId;				//订单ID
	double dPrice;					//成交价格
	double dNumber;					//成交手数
	STR64  pszTime;					//成交时间
	STR16  pszFillId;               //成交编号
    STR32  pszRefId;                //引用ID
    STR32  pszInstrument;           //
    STR32  pszProduct;              //合约代码
    int    nIsBuy;                  //买卖方向  0卖1买
    int    nUserID;                 //用户ID

    int    nAdverse;                //建平仓类型,0:建仓,1:平仓
    int    nPositionId;             //持仓ID
    double dProfit;                 //盈亏
    double dCost;                   //手续费
    double dNowFunds;               //结余
};
// 更新订单信息的回应消息,该消息订单状态改变时服务器主动推送
struct TFBApiUpdateOrder
{
	int    nUserId;				// 用户ID
	STR32  pszRefId;			// 引用ID
	int    nOrderId;			// 订单ID
	int    nOrderState;			// 订单状态	0:初始状态,非0:其他状态
	int    nType;				// 操作类型	0:更新,1:删除订单
	double dNumber;				// 订单总手数
	double dOddNumber;			// 未成交数量
	double dMargin;				// 订单保证金
};

struct TFBApiLoadOrder
{
	int		Doid;			    // 订单
	int		Douid;			    // 用户ID
	STR32   Domcode;		    // 商品编码
	STR64   Dotime;			    // 成交时间
	int		Dotype;			    // 1:买0:卖
	double  Doprice;		    // 成交价格
	double  Donumber;		    // 订单总手数
	double  Dooddnum;		    // 未成交数量
	int     DoAdverse;		    // 1:平仓,0建仓
	int     DOIsMatch;		    // 1:附属订单
	int     ModeType;		    // 上手订单状态
	int     MakerType;		    // 订单状态
	int     UDType;			    // 0 向下  1 向上
	double  DoLossP;		    // 止损价格
	double  DoProfitP;		    // 止盈价格
	double  DOBTPrice;		    // 挂单时价格
	double  DOUpPrice;		    // 上限价格
	double  DODownPrice;	    // 下限价格
	int     DOIsInvalid;	    // 平仓对应的持仓ID
	int     DOhSpId;		    // 上手ID
	STR32   DOSPOrderId;	    // SP订单ID号
	STR32   DOSPTradeId;	    // SP成交编号
	STR32   DOAttachId;		    // 附属订单号
	STR32   DORefId;		    // 自定参考ID
};
// 加载订单信息的回应消息
struct TFBApiLoadOrderRespond
{
	int nSizeofOrderItem;
	TFBApiLoadOrder* pOrderItem;
};

struct TFBApiLoadTrade
{
	int		oheId;			    // 订单
	int		ohedoid;			// 订单ID		
	int		oheuiid;			// 用户ID		
	STR16   ohemcode;		    // 商品编码			
	STR64   ohedealtime;		// 成交时间		
	int		ohetype;			// 1:买0:卖		
	double  ohenumber;		    // 成交数量			
	double  oheprice;		    // 成交价格			
	double  oheoddnum;		    // 未成交数量,结算时持仓均价
	double  ohedealcost;	    // 手续费			
	double  oheProfit;		    // 盈亏				
	int     oheAdverse;		    // 1:平仓,0建仓,2:结算
	double  oheNBalance;	    // 结余				
	int     oheIsMatch;		    // 是否撮合			
	int     ModeType;			// 上手订单状态	
	int     MakerType;		    // 订单状态			
	int     UDType;			    // 0 向下  1 向上	
	double  oheLossP;		    // 保证金			
	double  oheProfitP;	        // 开市盈亏
	double  oheBTPrice;	        // 挂单时价格
	int     oheoid;			    // 持仓ID
	int     ohectype;			// 后台下单类型
	STR16   infocheck;	        // 上手成交记录号
	int     oheSpId;			// 上手ID		
	int     oheState;			// 子账户订单ID	
	STR32   oheSPOrderId;		// SP订单ID号	
	double  oheExchange;		// 汇率
	double  oheFatherCost;	    // 上级帐号手续费
	STR32   oheRefId;			// 自定参考ID
	int	    oheStopType;	    // 订单止损类型
	double  oheOrderPrice;		// 订单价
	double  oheStopPrice;		// 突破价
	double  oheNewLossP;	    // 止损价格
	double  oheNewProfitP;		// 止盈价格
};                                 
// 加载成交历史时的回应消息
struct TFBApiLoadTradeRespond
{
	int nSizeofTradeItem;
	TFBApiLoadTrade* pTradeItem;
};
// 下单接口,改结构体使用之前请先memset初始化,以免版本更替造成不必要的烦恼
struct TFBApiAddOrder
{
    STR16     pszProdcode;        // 商品编码
    bool      bIsBuy;             // 买卖方向
    int       nNumberOfHand;      // 购买手数
    ORD_DEAL  nOrderType;         // 成交类型
    int       nStopType;          // 非止损ST_NODEFINE 或者 限价止损ST_LOSS
    int       nPID;               // 平仓单的订单ID,非平仓单只能填0
    ORD_TYPE  nType;              // 订单类型
    double    fPrice;             // 订单价格
    double    fStopLevel;         // 止损价格
    int		  m_nArbitrageId;     // 套利策略索引ID
    int		  m_nTimePlus;		  // 追单时间(毫秒)
    double	  m_nPricePlus;		  // 追单点位
    double	  m_nPriceDiff;		  // 套利订单提交时候的价差
    STR32     pszRefId;			  // 自定参考ID
};
//2017-04-18 add data begin----
struct tPriceData {
    double mBuyPrice[5];     //五档买价
    double mSellPrice[5];    //五档卖价
    double mBuyVolumn[5];    //五档买量
    double mSellVolumn[5];   //五档卖量
    double mCurPrice;        //最新报价/卖价
    double mClose;           //收盘价
    double mOpen;            //开盘价
    double mHigh;            //最高价
    double mLow;             //最低价
    double mVolumn;          //成交量
    double mAmount;          //成交额
    STR16  mProdCode;        //商品code
    STR64  mProdName;        //商品Name
	int    mPriceType;       //价格变动类型
    long   mDate;            //数据更新时间
};
//2017-04-18 add data end----
#define TFBDLLCALL __stdcall
//请求方法
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
typedef int (TFBDLLCALL *p_TFBAPI_SubscribePrice)(const char* strOpUserFlag, const char * prod_code, const int mode);   //订阅、取消订阅行情
typedef int (TFBDLLCALL *p_TFBAPI_GetPriceCount)(const char* strOpUserFlag);    //获取订阅的行情数量
typedef int (TFBDLLCALL *p_TFBAPI_LoginEX)(const char* strOpUserFlag, TFBApiLoginInfoEX& tLoginInfo);
typedef int (TFBDLLCALL *p_TFBAPI_SetSourceAddress)( char* pszSourceIP );

//获取行情资讯信息之前必须先调用p_TFBAPI_SubscribePrice订阅该行情。
//获取行情资讯信息,price需传入一个已申请空间的结构对象，例如：tPriceData price; 传入&price
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
// 注册回调
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
//2017-04-18 add ----  已订阅行情数据主动推送
typedef void (TFBDLLCALL *p_TFBAPI_RegisterApiPriceUpdate)      (ApiPriceUpdateAddr ApiPriceUpdate);

typedef void (TFBDLLCALL *p_TFBAPI_RegisterProductListReply)    (ProductListByCodeReplyAddr ProductListByCodeReply);
typedef void (TFBDLLCALL *p_TFBAPI_RegisterInstrumentListReply) (InstrumentListReplyAddr    InstrumentListReply);

///****************************接口函数的声明:***********************************/
//// 请求方法
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
//// 注册回调
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





