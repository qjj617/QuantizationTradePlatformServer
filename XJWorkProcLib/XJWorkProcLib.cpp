// XJWorkProcLib.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "XJWorkProcLib.h"
#include "XJWorkProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CXJWorkProcLibApp

BEGIN_MESSAGE_MAP(CXJWorkProcLibApp, CWinApp)
END_MESSAGE_MAP()


// CXJWorkProcLibApp ����

CXJWorkProcLibApp::CXJWorkProcLibApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CXJWorkProcLibApp ����

CXJWorkProcLibApp theApp;


// CXJWorkProcLibApp ��ʼ��

BOOL CXJWorkProcLibApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" DLL_PORT IXJUnknown* CreateXJObject(GUID GMID, GUID GCID)
{
	if (MID_XJWorkProcLib == GMID)
	{
		if (IID_IXJWorkProc == GCID)
		{
			return new CXJWorkProc();
		}
	}
	return NULL;
}