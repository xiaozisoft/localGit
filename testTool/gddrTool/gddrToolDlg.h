
// gddrToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Serial.h"

// CgddrToolDlg �Ի���
class CgddrToolDlg : public CDialogEx
{
// ����
public:
	CgddrToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GDDRTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

    // ��ʾͨѶ������־
    CEdit recvDataLog;
    // ���ƴ��ڿ���
    CButton serialCtrlButton;
    // ���ڶ˿ں�
    CComboBox serialPortNum;
    // ���ڲ�����ѡ��
    CComboBox serialBoardrate;
    // ��żУ��λ
    CComboBox serialCheck;
    // ����λ
    CComboBox serialDataBit;
    // ֹͣλ
    CComboBox serialStopbit;
    // ����
    CComboBox serialCode;

    afx_msg void OnBnClickedButtonSerial();
    afx_msg void OnCbnSelchangeCombo();
    afx_msg void OnCbnSelchangeComboBoard();
    // д���ڴ������
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
    // //��������ûʲô����
    CStatic gddrDataBack;
};
