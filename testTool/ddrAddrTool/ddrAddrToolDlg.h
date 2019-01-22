
// ddrAddrToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CddrAddrToolDlg �Ի���
class CddrAddrToolDlg : public CDialogEx
{
// ����
public:
	CddrAddrToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DDRADDRTOOL_DIALOG };
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
    CString groupId;
    unsigned char groupIdData;
    CString columnNum;
    unsigned char columnNumData;
    CString rowNum;
    unsigned char rowNumData;
    CString bankNum;
    unsigned char bankNumData;
    CString uartAddr;
    unsigned int uartAddrData;
    afx_msg void OnBnClickedButton6();
    CEdit uartAddrShow;
};
