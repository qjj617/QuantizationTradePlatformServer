#include "stdafx.h"
#include "../Common/XJLoadDll.h"
#include "../Common/IXJUnknown.h"
#include "../Common/Cstring.h"
#include <map>
using namespace std;

typedef IXJUnknown* (*PFNGETOBJECT)(GUID, GUID);

struct tagGUID
{
	tagGUID(GUID guid) { m_guid = guid; }
	GUID m_guid;
	bool operator <(const tagGUID &tagGuid)const
	{
		return false;
	}
};
map<tagGUID, HMODULE> DllMap;

bool InitLoadLibrary()
{
	DllMap.clear();
	return true;
}

IXJUnknown* CreateComObject(const char *pszFileName, GUID GMID, GUID GCID)
{
	map<tagGUID, HMODULE>::iterator it = DllMap.find(tagGUID(GMID));
	HMODULE hModule = NULL;
	if (it != DllMap.end())
	{
		hModule = it->second;
	}
	else
	{
		Cstring strFileName = pszFileName;
		hModule = ::LoadLibrary(strFileName);
		if (NULL != hModule)
		{
			DllMap[tagGUID(GMID)] = hModule;
		}
		else
		{
			return NULL;
		}
	}
	if (NULL != hModule)
	{
		PFNGETOBJECT pfn = NULL;
		string strFunName = "CreateXJObject";
		pfn = (PFNGETOBJECT)::GetProcAddress(hModule, strFunName.c_str());
		if (NULL != pfn)
		{
			return pfn(GMID, GCID);
		}
	}
	
	return NULL;
}

bool UnLoadLibrary()
{
	for (auto &pair : DllMap)
	{
		::FreeLibrary(pair.second);
	}
	DllMap.clear();

	return true;
}