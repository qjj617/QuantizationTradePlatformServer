// XJTFBPlatformLib.h : XJTFBPlatformLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXJTFBPlatformLibApp
// �йش���ʵ�ֵ���Ϣ������� XJTFBPlatformLib.cpp
//

class CXJTFBPlatformLibApp : public CWinApp
{
public:
	CXJTFBPlatformLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
