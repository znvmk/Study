
// OpenGL3DView.h : COpenGL3DView 类的接口
//

#pragma once
#include "DialogControlBoard.h"
#include"OpenGLFrame.h"
#include "WelcomePage.h"




class COpenGL3DView : public CView
{
protected: // 仅从序列化创建
	COpenGL3DView();
	DECLARE_DYNCREATE(COpenGL3DView)

// 特性
public:
	COpenGL3DDoc* GetDocument() const;

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
	virtual ~COpenGL3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:


	//afx_msg void OnFilePrintPreview();
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	afx_msg void OnDrawControl();
	afx_msg void OnViewSelect2D();
	afx_msg void OnViewSelect3D();


	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()



	// 特性
protected:
	CPoint m_pMouseMove;


	bool m_bWelcomePage;
	int timeTemp;
	// 特性
public:
	CClientDC* m_pDC;
	CRect m_oldRect;
	/*显示控制台*/
	int m_nDrawSelect;
	bool m_bShowControlBoard;



	CWelcomePage m_wcp;

public:

	/*OpenGL基本操作*/
	COpenGLFrame m_oglf;
	CDialogControlBoard* m_DlgCtrlBoard;


	// 操作
protected:
	/*创建控制台*/
	void CreateControlBoard();
	/*显示控制台*/
	void ShowControlBoard();

};

#ifndef _DEBUG  // OpenGL3DView.cpp 中的调试版本
inline COpenGL3DDoc* COpenGL3DView::GetDocument() const
   { return reinterpret_cast<COpenGL3DDoc*>(m_pDocument); }
#endif

