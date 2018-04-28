
// gddrToolDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CgddrToolDlg 对话框



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


// CgddrToolDlg 消息处理程序

BOOL CgddrToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

    SetDlgItemText(serialCtrlButton.GetDlgCtrlID(), _T("打开串口"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgddrToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgddrToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgddrToolDlg::OnBnClickedButtonSerial()
{
    // TODO: 打开串口或者 关闭串口
    CString s;
    GetDlgItemText(serialCtrlButton.GetDlgCtrlID(), s);
    
    if (s == _T("打开串口"))
    {
        if (serialM.Open(comName) != ERROR_SUCCESS)
        {
            AfxMessageBox(_T("Unable to open COM-port"), MB_ICONSTOP | MB_OK);
            return;
        }
        serialM.Setup(CSerial::EBaudrate(comBoardrate));
        writeToLog(_T("打开串口"));
        SetDlgItemText(serialCtrlButton.GetDlgCtrlID(), _T("关闭串口"));
    }
    else if(s == _T("关闭串口"))
    {
        serialM.Close();
        writeToLog(_T("关闭串口"));
        SetDlgItemText(serialCtrlButton.GetDlgCtrlID(), _T("打开串口"));
    }
}


void CgddrToolDlg::OnCbnSelchangeCombo()
{
    // TODO: 选择串口端口
    CString portNum;
    serialPortNum.UpdateData();
    serialPortNum.GetLBText(serialPortNum.GetCurSel(), portNum);

    comName = portNum;
}


void CgddrToolDlg::OnCbnSelchangeComboBoard()
{
    // TODO: 选择串口波特率
    CString boardrateTmp;
    serialBoardrate.UpdateData();
    serialBoardrate.GetLBText(serialBoardrate.GetCurSel(), boardrateTmp);
    
    comBoardrate = atoi(boardrateTmp);
}


void CgddrToolDlg::OnBnClickedButtonInit()
{
    // TODO: 初始化ddr控制器
}


void CgddrToolDlg::OnBnClickedButtonWritereg()
{
    // TODO: 写ddr寄存器的值
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
    // TODO: 读ddr寄存器的值
    //读取数据显示
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
    // TODO: 读取ddr中的数据
}

void CgddrToolDlg::OnBnClickedButtonWrite()
{
    // TODO: 将数据写到ddr
}

BOOL CgddrToolDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
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
