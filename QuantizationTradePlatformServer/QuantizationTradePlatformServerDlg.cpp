
// QuantizationTradePlatformServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QuantizationTradePlatformServer.h"
#include "QuantizationTradePlatformServerDlg.h"
#include "afxdialogex.h"

#include "../Common/XJLoadDll.h"
#pragma comment(lib, "XJLoadLibraryLib.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQuantizationTradePlatformServerDlg �Ի���



CQuantizationTradePlatformServerDlg::CQuantizationTradePlatformServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QUANTIZATIONTRADEPLATFORMSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pIXJServer = NULL;
}

void CQuantizationTradePlatformServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQuantizationTradePlatformServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNSTART, &CQuantizationTradePlatformServerDlg::OnBnClickedBtnstart)
	ON_BN_CLICKED(IDC_BTNCLOSE, &CQuantizationTradePlatformServerDlg::OnBnClickedBtnclose)
	ON_BN_CLICKED(IDC_BTNSET, &CQuantizationTradePlatformServerDlg::OnBnClickedBtnset)
END_MESSAGE_MAP()


// CQuantizationTradePlatformServerDlg ��Ϣ�������

BOOL CQuantizationTradePlatformServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	InitLoadLibrary();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQuantizationTradePlatformServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQuantizationTradePlatformServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}   
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQuantizationTradePlatformServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CQuantizationTradePlatformServerDlg::OnBnClickedBtnstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_pIXJServer)
	{
		IXJUnknown *pXJSer = NULL;
		pXJSer = CreateComObject("XJServerLib", MID_XJServerLib, IID_IXJServer);
		if (NULL != pXJSer)
		{
			pXJSer->QueryInterface(IID_IXJServer, (void **)&m_pIXJServer);
			if (NULL == m_pIXJServer)
			{
				AfxMessageBox(L"IXJServer�ӿڻ�ȡʧ��", MB_OK);
				return;
			}
		}
		else
		{
			AfxMessageBox(L"XJServerLib�����ʧ��", MB_OK);
			return;
		}
	}
	
	if (!m_pIXJServer->IsRunning())
	{
		if (m_pIXJServer->Init())
		{
			m_pIXJServer->Run();
		}		
	}	
}


void CQuantizationTradePlatformServerDlg::OnBnClickedBtnclose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL != m_pIXJServer)
	{
		m_pIXJServer->Stop();
		m_pIXJServer->Release();
		m_pIXJServer = NULL;
	}	
	UnLoadLibrary(MID_XJServerLib);
}


void CQuantizationTradePlatformServerDlg::OnBnClickedBtnset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
