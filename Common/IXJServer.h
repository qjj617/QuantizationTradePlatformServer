#pragma once

#include "IXJUnknown.h"

// {6869C111-BA96-49DD-A4BA-13B6B92BB261}
static const GUID MID_XJServerLib =
{ 0x6869c111, 0xba96, 0x49dd,{ 0xa4, 0xba, 0x13, 0xb6, 0xb9, 0x2b, 0xb2, 0x61 } };

// {26A247FE-34D4-4EE7-8F21-68DD5CFFF7F3}
static const GUID IID_IXJServer =
{ 0x26a247fe, 0x34d4, 0x4ee7,{ 0x8f, 0x21, 0x68, 0xdd, 0x5c, 0xff, 0xf7, 0xf3 } };


extern "C" DLL_PORT IXJUnknown* CreateXJObject(GUID GMID, GUID GCID);

class DLL_PORT IXJServer : public IXJUnknown
{
public:
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void Stop() = 0;
	virtual bool IsRunning() = 0;
	virtual bool Clean() = 0;	
};