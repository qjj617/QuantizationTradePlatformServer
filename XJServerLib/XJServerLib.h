// XJServerLib.h : XJServerLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXJServerLibApp
// �йش���ʵ�ֵ���Ϣ������� XJServerLib.cpp
//

class CXJServerLibApp : public CWinApp
{
public:
	CXJServerLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
