#pragma once
#include "../protocol/XJIPlatformApi.h"
#include "../Common/Cstring.h"
#include "../Common/Common.h"
#include <map>
#include <vector>
using namespace std;

class CPlatformManager
{
private:
	CPlatformManager(PFNPLATFORMDATAPROC pFnPushPlatformDataProc);
	CPlatformManager(const CPlatformManager&);
	CPlatformManager& operator =(const CPlatformManager&);
public:
	~CPlatformManager();

	//创建一个平台管理实例，属于单列模式
	static CPlatformManager& GetPlatformManager(PFNPLATFORMDATAPROC pFnPushPlatformDataProc)
	{
		static CPlatformManager obj(pFnPushPlatformDataProc);
		return obj;
	}

	//根据平台类型获取相对应的平台接口
	IPlatformApi* GetPlatform(PLATFORM_TYPE pfType);
	//增加一条合约信息
	void AddContractInfo(XJRspContractInfo* pContractInfo);
	//获取所有的合约信息
	map<string, map<string, vector<XJRspContractInfo*>>>& GetContractInfos();

	void InitPlatformManager();
	//根据平台类型获取平台名称
	static map<PLATFORM_TYPE, string> GetPlatformNames();

private:	
	IPlatformApi* LoadPlatformApi(Cstring strPlatformLib);

private:
	//平台接口容器，平台类型对应平台接口
	map<PLATFORM_TYPE, IPlatformApi*> m_PlatformInterface_Map;
	//合约容器，交易所-<产品-合约>
	map<string, map<string, vector<XJRspContractInfo*>>> m_ContractInfo_map;

	static map<PLATFORM_TYPE, string> m_vecPlatfromName;

	static PFNPLATFORMDATAPROC m_pFnPushPlatformDataProc;
};

