
// MFCApplication3.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCApplication3App: 
// �йش����ʵ�֣������ MFCApplication3.cpp
//

class CMFCApplication3App : public CWinApp
{
public:
	CMFCApplication3App();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication3App theApp;