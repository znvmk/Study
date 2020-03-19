
// OpenGLBaseView.h : COpenGLBaseView 类的接口
//

#pragma once
#include"OpenGLFrame.h"
#include"DialogControlBoard.h"










class COpenGLBaseView : public CView
{
protected: // 仅从序列化创建
	COpenGLBaseView();
	DECLARE_DYNCREATE(COpenGLBaseView)

// 特性
public:
	COpenGLBaseDoc* GetDocument() const;


// 特性
public:
	CClientDC* m_pDC;
	CRect m_oldRect;
	/*显示控制台*/
	int m_nDrawSelect;
	bool m_bShowControlBoard;
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
	virtual ~COpenGLBaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


	/*生成的消息映射函数*/
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType , int cx , int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnKeyDown(UINT nChar , UINT nRepCnt , UINT nFlags);
	
	afx_msg void OnLButtonDown(UINT nFlags , CPoint point);
	
	
	
	
	
	


	/*自定义菜单消息*/
public:
	afx_msg void OnDrawControl();


	/*自定义工具栏消息*/
public:
	
	

	
};

#ifndef _DEBUG  // OpenGLBaseView.cpp 中的调试版本
inline COpenGLBaseDoc* COpenGLBaseView::GetDocument() const
   { return reinterpret_cast<COpenGLBaseDoc*>(m_pDocument); }
#endif

