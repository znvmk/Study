
// MFCApplication2.h : MFCApplication2 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


#include "GlobalParameterTransmit.h"


// CMFCApplication2App:
// 有关此类的实现，请参阅 MFCApplication2.cpp
//

class CMFCApplication2App : public CWinAppEx
{
public:
	CMFCApplication2App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


public:
	
	//全局文件视图类参数传递
	CGlobalParameterTransmit GPT;
	


};

extern CMFCApplication2App theApp;
