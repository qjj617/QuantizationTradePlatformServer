#include "stdafx.h"
#include "XJWorkProc.h"

PFNSEND CXJWorkProc::m_pFnSend = NULL;

CXJWorkProc::CXJWorkProc()
{
}


CXJWorkProc::~CXJWorkProc()
{
}

void CXJWorkProc::Init(const PFNSEND *pFnSend)
{
	m_pFnSend = *pFnSend;
}

void CXJWorkProc::Run(const SOCKET sSocket, const char* pszMessage, const int nSize)
{

}

void CXJWorkProc::AddRef()
{

}

void CXJWorkProc::Release()
{

}

void CXJWorkProc::QueryInterface(GUID GIID, void **pInterface)
{

}
