
// gddrToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gddrTool.h"
#include "gddrToolDlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <stdlib.h>
#include <afxwin.h>
#include <string>
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
public:
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


// CgddrToolDlg �Ի���



CgddrToolDlg::CgddrToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GDDRTOOL_DIALOG, pParent)
    , regBaseAddrStr(_T(""))
    , regOffsetAddrStr(_T(""))
    , regValueStr(_T(""))
    , gaddrAddrStr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgddrToolDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_DATA_LOG, recvDataLog);
    DDX_Control(pDX, IDC_BUTTON_SERIAL, serialCtrlButton);
    DDX_Control(pDX, IDC_COMBO__PORT, serialPortNum);
    DDX_Control(pDX, IDC_COMBO_BOARD, serialBoardrate);
    DDX_Control(pDX, IDC_EDIT_DDR_DATA, ddrWriteData);
    DDX_Text(pDX, IDC_EDIT_BASEADDRESS, regBaseAddrStr);
    DDV_MaxChars(pDX, regBaseAddrStr, 10);
    DDX_Text(pDX, IDC_EDIT_ADDR_OFFSET, regOffsetAddrStr);
    DDV_MaxChars(pDX, regOffsetAddrStr, 10);
    DDX_Text(pDX, IDC_EDIT_REG_DATA, regValueStr);
    DDV_MaxChars(pDX, regValueStr, 10);
    DDX_Text(pDX, IDC_EDIT_GDDR_ADDR, gaddrAddrStr);
	DDV_MaxChars(pDX, gaddrAddrStr, 10);
}

BEGIN_MESSAGE_MAP(CgddrToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_SERIAL, &CgddrToolDlg::OnBnClickedButtonSerial)
    ON_CBN_SELCHANGE(IDC_COMBO__PORT, &CgddrToolDlg::OnCbnSelchangeCombo)
    ON_CBN_SELCHANGE(IDC_COMBO_BOARD, &CgddrToolDlg::OnCbnSelchangeComboBoard)
    ON_BN_CLICKED(IDC_BUTTON_WRITE, &CgddrToolDlg::OnBnClickedButtonWrite)
    ON_BN_CLICKED(IDC_BUTTON_INIT, &CgddrToolDlg::OnBnClickedButtonInit)
    ON_BN_CLICKED(IDC_BUTTON_WRITEREG, &CgddrToolDlg::OnBnClickedButtonWritereg)
    ON_BN_CLICKED(IDC_BUTTON_ReadData, &CgddrToolDlg::OnBnClickedButtonReaddata)
    ON_BN_CLICKED(IDC_BUTTON_READREG, &CgddrToolDlg::OnBnClickedButtonReadreg)
    //ON_WM_SERIAL(OnSerialMsg)
END_MESSAGE_MAP()


// CgddrToolDlg ��Ϣ�������

BOOL CgddrToolDlg::OnInitDialog()
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

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

    SetDlgItemText(serialCtrlButton.GetDlgCtrlID(), _T("�򿪴���"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CgddrToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgddrToolDlg::OnPaint()
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
HCURSOR CgddrToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgddrToolDlg::OnBnClickedButtonSerial()
{
    // TODO: �򿪴��ڻ��� �رմ���
    CString s;
    GetDlgItemText(serialCtrlButton.GetDlgCtrlID(), s);
    
    if (s == _T("�򿪴���"))
    {
        if (serialM.Open(comName) != ERROR_SUCCESS)
        {
            AfxMessageBox(_T("Unable to open COM-port"), MB_ICONSTOP | MB_OK);
            return;
        }
        serialM.Setup(CSerial::EBaudrate(comBoardrate));
        writeToLog(_T("�򿪴���"));
        SetDlgItemText(serialCtrlButton.GetDlgCtrlID(), _T("�رմ���"));
    }
    else if(s == _T("�رմ���"))
    {
        serialM.Close();
        writeToLog(_T("�رմ���"));
        SetDlgItemText(serialCtrlButton.GetDlgCtrlID(), _T("�򿪴���"));
    }
}


void CgddrToolDlg::OnCbnSelchangeCombo()
{
    // TODO: ѡ�񴮿ڶ˿�
    CString portNum;
    serialPortNum.UpdateData();
    serialPortNum.GetLBText(serialPortNum.GetCurSel(), portNum);

    comName = portNum;
}


void CgddrToolDlg::OnCbnSelchangeComboBoard()
{
    // TODO: ѡ�񴮿ڲ�����
    CString boardrateTmp;
    serialBoardrate.UpdateData();
    serialBoardrate.GetLBText(serialBoardrate.GetCurSel(), boardrateTmp);
    
    comBoardrate = atoi(boardrateTmp);
}


void CgddrToolDlg::OnBnClickedButtonInit()
{
    // TODO: ��ʼ��ddr������
}


void CgddrToolDlg::OnBnClickedButtonWritereg()
{
    // TODO: дddr�Ĵ�����ֵ
    unsigned int addrTmp = 0;
    unsigned int addrValueTmp = 0;
    UpdateData(TRUE);

    std::string tmpStr;
    tmpStr = regOffsetAddrStr;
    regOffsetAddr = hexStringToUint(tmpStr);

    tmpStr = regBaseAddrStr;
    regBaseAddr = hexStringToUint(tmpStr);

    tmpStr = regValueStr;
    regDataValue = hexStringToUint(tmpStr);

    addrTmp = regBaseAddr + regOffsetAddr;
    addrValueTmp = regDataValue;

    CString addrStrTmp, addrValueStrTmp;
    addrStrTmp.Format(_T("%x"), addrTmp);
    addrValueStrTmp.Format(_T("%x"), addrValueTmp);

    writeToLog("addr:" + addrStrTmp + " value:" + addrValueStrTmp);
}

void CgddrToolDlg::OnBnClickedButtonReadreg()
{
    // TODO: ��ddr�Ĵ�����ֵ
    //��ȡ������ʾ
    unsigned int addrTmp = 0;
    unsigned int addrValueTmp = 0;
    UpdateData(TRUE);

    std::string tmpStr;
    tmpStr = regOffsetAddrStr;
    regOffsetAddr = hexStringToUint(tmpStr);

    tmpStr = regBaseAddrStr;
    regBaseAddr = hexStringToUint(tmpStr);

    addrTmp = regBaseAddr + regOffsetAddr;

    CString test;
    test.Format(_T("%d"), regOffsetAddr);

    writeToLog(test);

    regDataValue = 0x99;
    regValueStr.Format(_T("%x"), regDataValue);
    UpdateData(FALSE);
}


void CgddrToolDlg::OnBnClickedButtonReaddata()
{
    // TODO: ��ȡddr�е�����
}

void CgddrToolDlg::OnBnClickedButtonWrite()
{
    // TODO: ������д��ddr
}

BOOL CgddrToolDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: �ڴ����ר�ô����/����û���
    if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
    {
        //if (GetFocus() == GetDlgItem(IDC_EDIT_ADDR_OFFSET))
        //{
        //    UpdateData(TRUE);
        //    regOffsetAddr = (UINT)atoi(regBaseAddrStr);
        //    UpdateData(FALSE);
        //}
        //if (GetFocus() == GetDlgItem(IDC_EDIT_BASEADDRESS))
        //{
        //    UpdateData(TRUE);
        //    regBaseAddr = (UINT)atoi(regBaseAddrStr);
        //    UpdateData(FALSE);
        //}
        //if (GetFocus() == GetDlgItem(IDC_EDIT_REG_DATA))
        //{
        //    UpdateData(TRUE);
        //    regDataValue = (UINT)atoi(regValueStr);
        //    UpdateData(FALSE);
        //}
        //if (GetFocus() == GetDlgItem(IDC_EDIT_GDDR_ADDR))
        //{
        //    UpdateData(TRUE);
        //    gaddrAddr = (UINT)atoi(gaddrAddrStr);
        //    UpdateData(FALSE);
        //}
        return true;
    }
    return CDialogEx::PreTranslateMessage(pMsg);
}

void CgddrToolDlg::writeToLog(CString log)
{
    CString logTmp;
    int nLength = recvDataLog.SendMessage(WM_GETTEXTLENGTH);
    logTmp += log;
    logTmp += _T("\r\n");
    recvDataLog.SetSel(nLength, nLength);
    recvDataLog.ReplaceSel(logTmp);
}

LRESULT CgddrToolDlg::OnSerialMsg(WPARAM wParam, LPARAM /*lParam*/)
{
    CSerial::EEvent eEvent = CSerial::EEvent(LOWORD(wParam));
    CSerial::EError eError = CSerial::EError(HIWORD(wParam));

    //if (eError)
    //    DisplayEvent(_T("An internal error occurred."));

    //if (eEvent & CSerial::EEventBreak)
    //    DisplayEvent(_T("Break detected on input."));

    //if (eEvent & CSerial::EEventError)
    //    DisplayEvent(_T("A line-status error occurred."));

    //if (eEvent & CSerial::EEventRcvEv)
    //    DisplayEvent(_T("Event character has been received."));

    //if (eEvent & CSerial::EEventRing)
    //    DisplayEvent(_T("Ring detected"));

    //if (eEvent & CSerial::EEventSend)
    //    DisplayEvent(_T("All data is send"));

    //if (eEvent & CSerial::EEventCTS)
    //    DisplayEventSetting(_T("CTS signal change"), _T("CTS"), m_serial.GetCTS());

    //if (eEvent & CSerial::EEventDSR)
    //    DisplayEventSetting(_T("DSR signal change"), _T("DSR"), m_serial.GetDSR());

    //if (eEvent & CSerial::EEventRLSD)
    //    DisplayEventSetting(_T("RLSD signal change"), _T("RLSD"), m_serial.GetRLSD());

    if (eEvent & CSerial::EEventRecv)
    {
        // Create a clean buffer
        //DWORD dwRead;
        TCHAR szData[101];
        CString logtmp;
        const int nBuflen = sizeof(szData) - 1;
        DWORD readLeng = nBuflen;
        // Obtain the data from the serial port
        do
        {
            serialM.Read(szData, nBuflen, &readLeng);
            //com.readData(szData, &readLeng);
            szData[readLeng] = '\0';

            // Scan the string for unwanted characters
            for (DWORD dwChar = 0; dwChar<readLeng; dwChar++)
            {
                if (!isprint(szData[dwChar]) && !isspace(szData[dwChar]))
                {
                    szData[dwChar] = '.';
                }
            }

#ifdef _UNICODE
            // Convert the ANSI data to Unicode
            LPTSTR lpszData = LPTSTR(_alloca((dwRead + 1) * sizeof(TCHAR)));
            if (!::MultiByteToWideChar(CP_ACP, 0, szData, -1, lpszData, dwRead + 1))
                return 0;

            // Display the fetched string
            DisplayData(lpszData);
#else
            // Display the fetched string
            //DisplayData(szData);
#endif
        } while (readLeng == nBuflen);
        logtmp.Format(_T("%s"), szData);
        writeToLog(logtmp);
    }

    return 0;
}
