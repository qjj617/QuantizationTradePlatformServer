#pragma once
#include "IXJUnknown.h"

// {82261402-47E0-4BEF-98B6-3E8EC32044FB}
static const GUID MID_XJWorkProcLib =
{ 0x82261402, 0x47e0, 0x4bef,{ 0x98, 0xb6, 0x3e, 0x8e, 0xc3, 0x20, 0x44, 0xfb } };

// {E5E8E40E-F897-4002-A187-93748971C54B}
static const GUID IID_IXJWorkProc =
{ 0xe5e8e40e, 0xf897, 0x4002,{ 0xa1, 0x87, 0x93, 0x74, 0x89, 0x71, 0xc5, 0x4b } };

extern "C" DLL_PORT IXJUnknown* CreateXJObject(GUID GMID, GUID GCID);
typedef int(*PFNSEND)(SOCKET, const char *, const int);

class IXJWorkProc : public IXJUnknown
{
public:
	virtual void Init(const PFNSEND *pFnSend) = 0;
	virtual void Run(const SOCKET sSocket, const char* pszMessage, const int nSize) = 0;
};