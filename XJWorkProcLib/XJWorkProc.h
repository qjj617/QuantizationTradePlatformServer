#pragma once
#include "../Common/IXJWorkProc.h"

class CXJWorkProc :	public IXJWorkProc
{
public:
	CXJWorkProc();
	~CXJWorkProc();

	virtual void Init(const PFNSEND *pFnSend);
	virtual void Run(const SOCKET sSocket, const char* pszMessage, const int nSize);
	virtual void AddRef();
	virtual void Release();
	virtual void QueryInterface(GUID GIID, void **pInterface);

private:
	static PFNSEND m_pFnSend;
};

