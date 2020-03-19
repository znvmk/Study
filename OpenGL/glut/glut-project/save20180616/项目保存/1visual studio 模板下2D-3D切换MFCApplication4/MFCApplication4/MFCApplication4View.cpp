
// MFCApplication4View.cpp : CMFCApplication4View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication4.h"
#endif

#include "MFCApplication4Doc.h"
#include "MFCApplication4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication4View

IMPLEMENT_DYNCREATE(CMFCApplication4View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication4View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication4View::OnFilePrintPreview)

	/*自定义菜单消息*/
	ON_COMMAND(ID_APP_CONTROL , &CMFCApplication4View::OnDrawControl)
	ON_COMMAND(ID_APP_2D , &CMFCApplication4View::OnViewSelect2D)
	ON_COMMAND(ID_APP_3D , &CMFCApplication4View::OnViewSelect3D)

	ON_WM_CONTEXTMENU()

	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_TIMER()


	
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CMFCApplication4View 构造/析构

CMFCApplication4View::CMFCApplication4View()
{
	// TODO: 在此处添加构造代码
	m_pDC = NULL;
	m_nDrawSelect = 0;
	//m_DlgCtrlBoard = NULL;
	//CreateControlBoard();

	m_bWelcomePage = 1;
	timeTemp = 0;
}

CMFCApplication4View::~CMFCApplication4View()
{
	//if (m_DlgCtrlBoard != NULL)
	{
		//删除非模态对话框
	//	delete m_DlgCtrlBoard;
	//	m_DlgCtrlBoard = NULL;
	}
}

BOOL CMFCApplication4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	//cs.cx = m_oglf.m_WindowWidth;
	//cs.cy = m_oglf.m_WindowHeight;
	//cs.x = 700;
	//cs.y = 700;

	return CView::PreCreateWindow(cs);
}

// CMFCApplication4View 绘制

void CMFCApplication4View::OnDraw(CDC* pDC)
{
	CMFCApplication4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码


	if (m_bWelcomePage)
	{
		//m_wcp.DrawWelcomePage(pDC);
	}
	else
	{
		//if (m_DlgCtrlBoard != NULL)m_nDrawSelect = m_DlgCtrlBoard->m_nNumber;
		m_oglf.GLDraw(m_nDrawSelect);
		//m_oglf.GLDrawTest();
		//ShowControlBoard();

	}

	/*
	CString ao,bo;
	int ud, lr;
	ud = m_oglf.a;
	lr = m_oglf.b;
	ao.Format(_T("%d"), ud);
	bo.Format(_T("%d"), lr);
	pDC->TextOutW(185, 205, ao);
	pDC->TextOutW(400, 205, bo);
	*/
}


// CMFCApplication4View 打印


void CMFCApplication4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplication4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication4View 诊断

#ifdef _DEBUG
void CMFCApplication4View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication4Doc* CMFCApplication4View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication4Doc)));
	return (CMFCApplication4Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication4View 消息处理程序


int CMFCApplication4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	m_pDC = new CClientDC(this);

	GetClientRect(&m_oldRect);

	m_oglf.GLInit(m_pDC);

	SetTimer(1 , 50 , NULL);
	return 0;
}


BOOL CMFCApplication4View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CMFCApplication4View::OnKeyDown(UINT nChar , UINT nRepCnt , UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
		//case VK_DOWN: m_DlgCtrlBoard->OnBnClickedAdd();break;
		//case VK_UP:if (m_DlgCtrlBoard->m_nNumber > 0)m_DlgCtrlBoard->OnBnClickedMinus();;break;
	case 'A':m_oglf.PfmTranslate(0);break;
	case 'O':m_oglf.PfmTranslate(1);break;
	case 'E':m_oglf.PfmTranslate(2);break;
	case 'I':m_oglf.PfmTranslate(3);break;


	case 'J':m_oglf.PfmTranslate(4);break;

	case 'K':m_oglf.PfmTranslate(5);break;


	case 'R':m_oglf.PfmRotate(0);break;

	case 'T':m_oglf.PfmRotate(1);break;
	case 'N':m_oglf.PfmRotate(2);break;
	case 'S':m_oglf.PfmRotate(3);break;
	case 'M':m_oglf.PfmRotate(4);break;
	case 'W':m_oglf.PfmRotate(5);break;



		//case VK_UP: MessageBox(_T("keyup"));break;
		//case VK_DOWN: MessageBox(_T("keydown"));break;
		//case VK_LEFT: MessageBox(_T("keyleft"));break;
		//case VK_RIGHT: MessageBox(_T("keyright"));break;
	case VK_UP: m_oglf.m_keyup = 1;break;
	case VK_DOWN:m_oglf.m_keydown = 1;break;
	case VK_LEFT:m_oglf.m_keyleft = 1;break;
	case VK_RIGHT:m_oglf.m_keyright = 1;break;
	case VK_SHIFT:m_oglf.m_keyshift = 1;break;
	case 33:m_oglf.m_keypageup = 1;break;
	case 34:m_oglf.m_keypagedown = 1;break;

	}
	UpdateData();

	//Invalidate();
	CView::OnKeyDown(nChar , nRepCnt , nFlags);
}


void CMFCApplication4View::OnKeyUp(UINT nChar , UINT nRepCnt , UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP: m_oglf.m_keyup = 0;break;
	case VK_DOWN:m_oglf.m_keydown = 0;break;
	case VK_LEFT:m_oglf.m_keyleft = 0;break;
	case VK_RIGHT:m_oglf.m_keyright = 0;break;
	case VK_SHIFT:m_oglf.m_keyshift = 0;break;
	case 33:m_oglf.m_keypageup = 0;break;
	case 34:m_oglf.m_keypagedown = 0;break;

	}
	UpdateData();
	CView::OnKeyUp(nChar , nRepCnt , nFlags);
}


void CMFCApplication4View::OnLButtonDblClk(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDblClk(nFlags , point);
}


void CMFCApplication4View::OnLButtonDown(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bWelcomePage = 0;
	m_oglf.LButtonDown(nFlags , point);

	CView::OnLButtonDown(nFlags , point);
}


void CMFCApplication4View::OnLButtonUp(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CView::OnLButtonUp(nFlags , point);
}


void CMFCApplication4View::OnMouseMove(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags , point);
}


BOOL CMFCApplication4View::OnMouseWheel(UINT nFlags , short zDelta , CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CView::OnMouseWheel(nFlags , zDelta , pt);
}


void CMFCApplication4View::OnSize(UINT nType , int cx , int cy)
{
	CView::OnSize(nType , cx , cy);

	m_oglf.GLSize(nType , cx , cy , m_oldRect);
	//m_oglf.GLSize(nType , 2000 , 2000 , m_oldRect);

	// TODO: 在此处添加消息处理程序代码
}


void CMFCApplication4View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent == 1)
	{
		if (m_bWelcomePage == 1)
		{
			timeTemp++;
			//if (timeTemp == 50)m_bWelcomePage = 0;
		}
	}



	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CMFCApplication4View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//HGLRC hrc;
	//hrc = ::wglGetCurrentContext();
	//if (hrc)::wglDeleteContext(hrc);
	//if (m_pDC)delete m_pDC;
	m_oglf.GLDestroy(m_pDC);
}


/*
void COpenGL3DView::CreateControlBoard()
{
	if (m_DlgCtrlBoard == NULL)
	{
		m_DlgCtrlBoard = new CDialogControlBoard();
		m_DlgCtrlBoard->Create(IDD_DIALOG_CONTROL);
	}
}
*/


void CMFCApplication4View::OnViewSelect2D()
{
	m_oglf.m_nViewSelect = 2;

}


void CMFCApplication4View::OnViewSelect3D()
{
	m_oglf.m_nViewSelect = 3;

}

void CMFCApplication4View::OnDrawControl()
{
	/*

	//用于保存DoModel对话框的返回值
	//INT_PTR nRes;
	//创建DoModel对话框的实例
	//CDialogControl m_DlgCtrl=new CDialogControl();
	/*初始化*/
	//m_DlgCtrl.m_nNumber = m_nDrawSelect;

	//弹出对话框
	//nRes = m_DlgCtrl.DoModal();
	//m_DlgCtrl->Create(IDD_DIALOG_CONTROL);
	//nRes = m_DlgCtrl->ShowWindow(TRUE);
	//判断对话框的返回值是否为CANCEL,如果是则返回return，否则继续向下执行
	//if (nRes == IDCANCEL)
	//return;

/*
	if (m_DlgCtrlBoard != NULL)m_DlgCtrlBoard->ShowWindow(SW_SHOW);
	m_DlgCtrlBoard->m_bShow = true;

	//将控件中的变量值保存到相应的变量中

	m_nDrawSelect = m_DlgCtrlBoard->m_nNumber;
	//UpdateData();
	//更新控件中变量的值
	//UpdateData(FALSE);
	*/
}
/*

void COpenGL3DView::ShowControlBoard()
{
	if (m_DlgCtrlBoard != NULL)
	{
		m_bShowControlBoard = m_DlgCtrlBoard->m_bShow;
		if (m_bShowControlBoard == false)
		{
			m_DlgCtrlBoard->ShowWindow(SW_HIDE);
		}
	}

}
*/