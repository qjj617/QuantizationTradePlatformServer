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

	//����һ��ƽ̨����ʵ�������ڵ���ģʽ
	static CPlatformManager& GetPlatformManager(PFNPLATFORMDATAPROC pFnPushPlatformDataProc)
	{
		static CPlatformManager obj(pFnPushPlatformDataProc);
		return obj;
	}

	//����ƽ̨���ͻ�ȡ���Ӧ��ƽ̨�ӿ�
	IPlatformApi* GetPlatform(PLATFORM_TYPE pfType);
	//����һ����Լ��Ϣ
	void AddContractInfo(XJRspContractInfo* pContractInfo);
	//��ȡ���еĺ�Լ��Ϣ
	map<string, map<string, vector<XJRspContractInfo*>>>& GetContractInfos();

	void InitPlatformManager();
	//����ƽ̨���ͻ�ȡƽ̨����
	static map<PLATFORM_TYPE, string> GetPlatformNames();

private:	
	IPlatformApi* LoadPlatformApi(Cstring strPlatformLib);

private:
	//ƽ̨�ӿ�������ƽ̨���Ͷ�Ӧƽ̨�ӿ�
	map<PLATFORM_TYPE, IPlatformApi*> m_PlatformInterface_Map;
	//��Լ������������-<��Ʒ-��Լ>
	map<string, map<string, vector<XJRspContractInfo*>>> m_ContractInfo_map;

	static map<PLATFORM_TYPE, string> m_vecPlatfromName;

	static PFNPLATFORMDATAPROC m_pFnPushPlatformDataProc;
};

