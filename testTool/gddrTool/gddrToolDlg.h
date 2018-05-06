
// gddrToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Serial.h"

// CgddrToolDlg 对话框
class CgddrToolDlg : public CDialogEx
{
// 构造
public:
	CgddrToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GDDRTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    CSerial serialM;
    //Communication com;
    CString comName;
    unsigned int comBoardrate;

    unsigned int regBaseAddr;
    unsigned int regOffsetAddr;
    unsigned int regDataValue;
    unsigned int gaddrAddr;

    // 显示通讯过程日志
    CEdit recvDataLog;
    // 控制串口开关
    CButton serialCtrlButton;
    // 串口端口号
    CComboBox serialPortNum;
    // 串口波特率选择
    CComboBox serialBoardrate;
    // 奇偶校验位
    CComboBox serialCheck;
    // 数据位
    CComboBox serialDataBit;
    // 停止位
    CComboBox serialStopbit;
    // 编码
    CComboBox serialCode;

    afx_msg void OnBnClickedButtonSerial();
    afx_msg void OnCbnSelchangeCombo();
    afx_msg void OnCbnSelchangeComboBoard();
    // 写进内存的数据
    CEdit ddrData;
    afx_msg void OnBnClickedButtonWrite();
    afx_msg void OnBnClickedButtonInit();
    afx_msg void OnBnClickedButtonWritereg();
    afx_msg void OnBnClickedButtonReaddata();
    CString regBaseAddrStr;
    CString regOffsetAddrStr;
    CString regValueStr;
    CString gaddrAddrStr;
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    void writeToLog(CString log);
    afx_msg void OnBnClickedButtonReadreg();
    LRESULT OnSerialMsg(WPARAM wParam, LPARAM /*lParam*/);
    afx_msg void OnCbnSelchangeComboCheck();
    afx_msg void OnCbnSelchangeComboDataBit();
    afx_msg void OnCbnSelchangeComboStopBit();
    afx_msg void OnCbnSelchangeComboCode();
    // //背景而已没什么作用
    CStatic gddrDataBack;
};
