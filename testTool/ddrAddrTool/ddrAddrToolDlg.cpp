
// ddrAddrToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ddrAddrTool.h"
#include "ddrAddrToolDlg.h"
#include "afxdialogex.h"
#include <string>
#include <Windows.h>
#include <afxwin.h>
#include "tool.h"

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


// CddrAddrToolDlg �Ի���



CddrAddrToolDlg::CddrAddrToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DDRADDRTOOL_DIALOG, pParent)
    , groupId(_T(""))
    , columnNum(_T(""))
    , rowNum(_T(""))
    , bankNum(_T(""))
    , uartAddr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CddrAddrToolDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, groupId);
    DDX_Text(pDX, IDC_EDIT2, columnNum);
    DDX_Text(pDX, IDC_EDIT3, rowNum);
    DDX_Text(pDX, IDC_EDIT4, bankNum);
    DDX_Text(pDX, IDC_EDIT5, uartAddr);
    DDV_MaxChars(pDX, groupId, 10);
    DDV_MaxChars(pDX, uartAddr, 8);
    DDX_Control(pDX, IDC_EDIT5, uartAddrShow);
}

BEGIN_MESSAGE_MAP(CddrAddrToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON6, &CddrAddrToolDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CddrAddrToolDlg ��Ϣ�������

BOOL CddrAddrToolDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CddrAddrToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CddrAddrToolDlg::OnPaint()
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
HCURSOR CddrAddrToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CddrAddrToolDlg::OnBnClickedButton6()
{
    unsigned int addrValueTmp = 0;
    UpdateData(TRUE);

    std::string tmpStr;
    tmpStr = groupId;
    groupIdData = hexStringToUint(tmpStr);

    tmpStr = columnNum;
    columnNumData = hexStringToUint(tmpStr);

    tmpStr = rowNum;
    rowNumData = hexStringToUint(tmpStr);

    tmpStr = bankNum;
    bankNumData = hexStringToUint(tmpStr);

    unsigned int tmpUartAddr = 0;
    unsigned char tmp = 0;

    tmp = groupIdData & 0x7;
    tmpUartAddr |= (tmp << 1);

    tmp = (columnNumData >> 1) & 0x1;
    tmpUartAddr |= (tmp);

    tmp = (columnNumData >> 2) & 0xf;
    tmpUartAddr |= (tmp << 23);

    tmp = (columnNumData >> 6) & 0x1;
    tmpUartAddr |= (tmp << 8);

    tmp = (rowNumData & 0x3FFF);
    tmpUartAddr |= (tmp << 9);

    tmp = (bankNumData & 0x3);
    tmpUartAddr |= (tmp << 6);

    tmp = ((bankNumData >> 2) & 0x3);
    tmpUartAddr |= (tmp << 4);

    
    uartAddr.Format(_T("%x"), tmpUartAddr);
    uartAddrShow.SetWindowText(uartAddr);
}
