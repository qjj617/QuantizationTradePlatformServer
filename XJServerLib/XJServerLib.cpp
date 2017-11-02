// XJServerLib.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "XJServerLib.h"
#include "XJServer.h"

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

// CXJServerLibApp

BEGIN_MESSAGE_MAP(CXJServerLibApp, CWinApp)
END_MESSAGE_MAP()


// CXJServerLibApp ����

CXJServerLibApp::CXJServerLibApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CXJServerLibApp ����

CXJServerLibApp theApp;


// CXJServerLibApp ��ʼ��

BOOL CXJServerLibApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" DLL_PORT IXJUnknown* CreateXJObject(GUID GMID, GUID GCID)
{
	if (MID_XJServerLib == GMID)
	{
		if (IID_IXJServer == GCID)
		{
			return new CXJServer();
		}
	}

	return NULL;
}