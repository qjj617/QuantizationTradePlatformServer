// XJWorkProcLib.h : XJWorkProcLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXJWorkProcLibApp
// �йش���ʵ�ֵ���Ϣ������� XJWorkProcLib.cpp
//

class CXJWorkProcLibApp : public CWinApp
{
public:
	CXJWorkProcLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
