
// QuantizationTradePlatformServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQuantizationTradePlatformServerApp: 
// �йش����ʵ�֣������ QuantizationTradePlatformServer.cpp
//

class CQuantizationTradePlatformServerApp : public CWinApp
{
public:
	CQuantizationTradePlatformServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQuantizationTradePlatformServerApp theApp;