#include "stdafx.h"
#include "XJPlatformManager.h"
#include "../protocol/XJIPlatformApi.h"

//构造一个CTP平台对象
//CCTPPlatform& g_ctp_platform = CCTPPlatform::TheCTPPlatform(CQuantTradingPlatformDlg::PushPlatformDataProc);
//构造一个天富宝平台对象
//CTfbPlatform& g_tfb_platform = CTfbPlatform::TheCTfbPlatform(CQuantTradingPlatformDlg::PushPlatformDataProc);

map<PLATFORM_TYPE, string> CPlatformManager::m_vecPlatfromName;
typedef IPlatformApi* (*PFNGETPLATFORMAPI)(PFNPLATFORMDATAPROC);
PFNPLATFORMDATAPROC CPlatformManager::m_pFnPushPlatformDataProc = NULL;

CPlatformManager::CPlatformManager(PFNPLATFORMDATAPROC pFnPushPlatformDataProc)
{
	m_pFnPushPlatformDataProc = pFnPushPlatformDataProc;
	m_vecPlatfromName[PLATFORM_TYPE::PF_CTP] = "CTP";
	m_vecPlatfromName[PLATFORM_TYPE::PF_Esunny] = "易盛";
	m_vecPlatfromName[PLATFORM_TYPE::PF_TFB] = "天富宝";
}


CPlatformManager::~CPlatformManager()
{
	for (auto &pair : m_ContractInfo_map)
	{
		for (auto &pair1 : pair.second)
		{
			for (auto &ve : pair1.second)
			{
				delete ve;
			}
		}
	}
}

IPlatformApi* CPlatformManager::GetPlatform(PLATFORM_TYPE pfType)
{
	IPlatformApi *pPlatformApi = NULL;
	map<PLATFORM_TYPE, IPlatformApi*>::iterator it = m_PlatformInterface_Map.find(pfType);
	if (it != m_PlatformInterface_Map.cend())
	{
		pPlatformApi = (*it).second;
	}

	return pPlatformApi;
}

void CPlatformManager::InitPlatformManager()
{
	IPlatformApi *pPlatformApi = NULL;
	pPlatformApi = LoadPlatformApi("XJTFBPlatformLib");
	if (NULL != pPlatformApi)
	{
		pPlatformApi->InitializePlatform();
		m_PlatformInterface_Map[PLATFORM_TYPE::PF_TFB] = pPlatformApi;
	}
}

IPlatformApi* CPlatformManager::LoadPlatformApi(Cstring strPlatformLib)
{
	IPlatformApi *pPlatformApi = NULL;
	HMODULE hModule = ::LoadLibrary(strPlatformLib);
	if (NULL != hModule)
	{
		PFNGETPLATFORMAPI pfnGetPlatformApi = (PFNGETPLATFORMAPI)::GetProcAddress(hModule, "GetPlatformApi");
		if (NULL != pfnGetPlatformApi)
		{
			pPlatformApi = pfnGetPlatformApi(m_pFnPushPlatformDataProc);
		}
	}
	return pPlatformApi; 
}

//增加一条合约信息
void CPlatformManager::AddContractInfo(XJRspContractInfo* pContractInfo)
{
	map<string, map<string, vector<XJRspContractInfo*>>>::iterator it = m_ContractInfo_map.find(pContractInfo->strExchangeNo);
	if (it != m_ContractInfo_map.cend())
	{
		map<string, vector<XJRspContractInfo*>>& vecCon = (it->second);
		vecCon[pContractInfo->strProductID].emplace_back(pContractInfo);
	}
	else
	{
		map<string, vector<XJRspContractInfo*>> vecCon;
		vecCon[pContractInfo->strProductID].emplace_back(pContractInfo);

		m_ContractInfo_map[pContractInfo->strExchangeNo] = vecCon;
	}	
}

//获取所有的合约信息
map<string, map<string, vector<XJRspContractInfo*>>>& CPlatformManager::GetContractInfos()
{
	return m_ContractInfo_map;
}

map<PLATFORM_TYPE, string> CPlatformManager::GetPlatformNames()
{
	return m_vecPlatfromName;
}