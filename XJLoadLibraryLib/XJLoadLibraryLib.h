// XJLoadLibraryLib.h : XJLoadLibraryLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXJLoadLibraryLibApp
// �йش���ʵ�ֵ���Ϣ������� XJLoadLibraryLib.cpp
//

class CXJLoadLibraryLibApp : public CWinApp
{
public:
	CXJLoadLibraryLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
