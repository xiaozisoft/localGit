
// ddrAddrTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CddrAddrToolApp: 
// �йش����ʵ�֣������ ddrAddrTool.cpp
//

class CddrAddrToolApp : public CWinApp
{
public:
	CddrAddrToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CddrAddrToolApp theApp;