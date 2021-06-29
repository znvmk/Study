
// MFCApplication3View.cpp : CMFCApplication3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCApplication3View 构造/析构

CMFCApplication3View::CMFCApplication3View()
{
	// TODO: 在此处添加构造代码

	m_bShowWelcomePage = 1;
	m_nTimeShowWelcomePage = 0;

}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 绘制

void CMFCApplication3View::OnDraw(CDC* pDC)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	if (m_bShowWelcomePage)
	{
		m_wcp.DrawWelcomePage(pDC);
		
	}
	else
	{
		pDC->MoveTo(0 , 0);
		pDC->LineTo(1024 , 700);
	}
		
		
	

}


// CMFCApplication3View 打印

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication3View 诊断

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 消息处理程序


int CMFCApplication3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	/*   //创建透明字体//
	//如果创建的是单文档程序，在视图类的OnCreate函数最后添加：
	//	SetClassLong(m_hWnd , GCL_HBRBACKGROUND , (LONG)GetStockObject(NULL_BRUSH));//改变背景刷
	//NULL_BRUSH为透明背景，BLACK_BRUSH为黑色背景，可将(LONG)GetStockObject(NULL_BRUSH）改为：
	//(long)::CreateSolidBrush(RGB(255 , 255 , 0))，改变RGB宏括号里的数字即可将背景改为不同的颜色。

	//在视图的OnDraw函数中添加：SetTextColor(*pDC , RGB(255 , 0 , 0));//设置文字颜色
	//pDC->TextOut(100 , 100 , "显示文字");//显示文字
	*/


	SetClassLong(m_hWnd , GCL_HBRBACKGROUND , (LONG)GetStockObject(NULL_BRUSH));//改变背景刷
	

	SetTimer(1 , 50 , NULL);

	return 0;
}


void CMFCApplication3View::OnKeyDown(UINT nChar , UINT nRepCnt , UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nChar)
	{
	//case VK_UP:m_bShowWelcomePage = 0;
	}



	Invalidate();

	CView::OnKeyDown(nChar , nRepCnt , nFlags);
}


void CMFCApplication3View::OnKeyUp(UINT nChar , UINT nRepCnt , UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	

	CView::OnKeyUp(nChar , nRepCnt , nFlags);
}


void CMFCApplication3View::OnLButtonDown(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_bShowWelcomePage==1)
		m_bShowWelcomePage = 0;
	else
		if (m_bShowWelcomePage == 0)
			m_bShowWelcomePage = 1;
	
	Invalidate();

	CView::OnLButtonDown(nFlags , point);
}


void CMFCApplication3View::OnLButtonUp(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	

	CView::OnLButtonUp(nFlags , point);
}


void CMFCApplication3View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//定时器在OnCreate()中声明SetTimer(0,50,NULL);
	switch (nIDEvent)
	{
	case 1 :
		if (m_bShowWelcomePage)
		{
			m_nTimeShowWelcomePage++;
			if (m_nTimeShowWelcomePage == 200)
			{
				m_bShowWelcomePage = 0;
				m_nTimeShowWelcomePage = 0;
				Invalidate();
			}
		}

	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}
