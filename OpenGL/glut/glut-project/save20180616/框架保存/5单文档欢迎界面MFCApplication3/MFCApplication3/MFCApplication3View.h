
// MFCApplication3View.h : CMFCApplication3View 类的接口
//

#pragma once

#include "WelcomePage.h"




class CMFCApplication3View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

// 特性
public:
	CMFCApplication3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

	//特性
protected:

	//特性
public:
	bool m_bShowWelcomePage;
	int m_nTimeShowWelcomePage;

	//特性
protected:
	CWelcomePage m_wcp;

	//操作
protected:

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar , UINT nRepCnt , UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar , UINT nRepCnt , UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags , CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags , CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCApplication3View.cpp 中的调试版本
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

