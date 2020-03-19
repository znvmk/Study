
// OpenGLBaseView.cpp : COpenGLBaseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGLBase.h"
#endif

#include "OpenGLBaseDoc.h"
#include "OpenGLBaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLBaseView

IMPLEMENT_DYNCREATE(COpenGLBaseView, CView)

BEGIN_MESSAGE_MAP(COpenGLBaseView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLBaseView::OnFilePrintPreview)



	/*自定义菜单消息*/
	ON_COMMAND(ID_APP_CONTROL, &COpenGLBaseView::OnDrawControl)



	/*自定义工具栏消息*/
	ON_COMMAND(ID_DRAW_CLEAR, &COpenGLBaseView::OnDrawClear)
	ON_COMMAND(ID_DRAW_POINTS,&COpenGLBaseView::OnDrawPoints)
	ON_COMMAND(ID_DRAW_LINE, &COpenGLBaseView::OnDrawLine)
	ON_COMMAND(ID_DRAW_TRAINGLES, &COpenGLBaseView::OnDrawTraingles)
	





	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()

	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// COpenGLBaseView 构造/析构

COpenGLBaseView::COpenGLBaseView()
{
	// TODO: 在此处添加构造代码
	m_pDC = NULL;
	m_nDrawSelect = 0;
	m_DlgCtrlBoard = NULL;
	CreateControlBoard();
}

COpenGLBaseView::~COpenGLBaseView()
{
	
		//如果非模态对话框已经创建则删除他
	if (m_DlgCtrlBoard != NULL)
	{
			//删除非模态对话框
			delete m_DlgCtrlBoard;
			m_DlgCtrlBoard = NULL;
	}
}

BOOL COpenGLBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

// COpenGLBaseView 绘制

void COpenGLBaseView::OnDraw(CDC* pDC)
{
	COpenGLBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (m_DlgCtrlBoard != NULL)m_nDrawSelect=m_DlgCtrlBoard->m_nNumber;
	m_oglo.GLDraw(m_nDrawSelect);
	//m_oglo.GLDrawTest();
	ShowControlBoard();
}


// COpenGLBaseView 打印


void COpenGLBaseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLBaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLBaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COpenGLBaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


void COpenGLBaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLBaseView 诊断

#ifdef _DEBUG
void COpenGLBaseView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLBaseDoc* COpenGLBaseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLBaseDoc)));
	return (COpenGLBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLBaseView 消息处理程序


BOOL COpenGLBaseView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}




int COpenGLBaseView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	//m_oglo.GLInit();


	m_pDC=new CClientDC(this);

	GetClientRect(&m_oldRect);

	m_oglo.GLInit(m_pDC);
	
	SetTimer(1, 50, NULL);

	return 0;
}


void COpenGLBaseView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	HGLRC hrc;
	hrc = ::wglGetCurrentContext();
	if (hrc)::wglDeleteContext(hrc);
	if (m_pDC)delete m_pDC;
}


void COpenGLBaseView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_oglo.GLSize(nType, cx, cy, m_oldRect); 
	//m_oglo.GLSize(nType , 2000 , 2000 , m_oldRect);
}




void COpenGLBaseView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nIDEvent == 1)
	{
		//m_oglo.m_fAngleY += 10.0f;
		//m_oglo.m_fAngleX += 1.0f;
		//m_oglo.m_fAngleZ += 5.0f;
	}
	
	Invalidate();
	CView::OnTimer(nIDEvent);
}

void COpenGLBaseView::OnKeyDown(UINT nChar , UINT nRepCnt , UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	//case VK_DOWN: m_DlgCtrlBoard->OnBnClickedAdd();break;
	//case VK_UP:if (m_DlgCtrlBoard->m_nNumber > 0)m_DlgCtrlBoard->OnBnClickedMinus();;break;
	case 'P':m_oglo.PfmTranslate(0);break;
	case 'Y':m_oglo.PfmTranslate(1);break;
	case 'F':m_oglo.PfmTranslate(2);break;
	case 'G':m_oglo.PfmTranslate(3);break;
	case 'C':m_oglo.PfmTranslate(4);break;
	case 'R':m_oglo.PfmTranslate(5);break;
		
	case 'A':m_oglo.PfmRotate(0);break;
	case 'O':m_oglo.PfmRotate(1);break;
	case 'E':m_oglo.PfmRotate(2);break;
	case 'U':m_oglo.PfmRotate(3);break;
	case 'I':m_oglo.PfmRotate(4);break;
	case 'D':m_oglo.PfmRotate(5);break;
	}
	UpdateData();

	CView::OnKeyDown(nChar , nRepCnt , nFlags);
}

void COpenGLBaseView::OnKeyUp(UINT nChar , UINT nRepCnt , UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyUp(nChar , nRepCnt , nFlags);
}

void COpenGLBaseView::OnLButtonDown(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_oglo.LButtonDown(nFlags , point);
	Invalidate();


	CView::OnLButtonDown(nFlags , point);
}

void COpenGLBaseView::OnLButtonUp(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags , point);
}


void COpenGLBaseView::OnLButtonDblClk(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDblClk(nFlags , point);
}

void COpenGLBaseView::OnMouseMove(UINT nFlags , CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags , point);
}


BOOL COpenGLBaseView::OnMouseWheel(UINT nFlags , short zDelta , CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CView::OnMouseWheel(nFlags , zDelta , pt);
}











void COpenGLBaseView::CreateControlBoard()
{
	if (m_DlgCtrlBoard == NULL)
	{
		m_DlgCtrlBoard = new CDialogControlBoard();
		m_DlgCtrlBoard->Create(IDD_DIALOG_CONTROL);
	}
}

void COpenGLBaseView::OnDrawControl()
{
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
	
	
	if(m_DlgCtrlBoard !=NULL)m_DlgCtrlBoard->ShowWindow(SW_SHOW);
	m_DlgCtrlBoard->m_bShow = true;
	
	//将控件中的变量值保存到相应的变量中

	m_nDrawSelect = m_DlgCtrlBoard->m_nNumber;
	//UpdateData();
	//更新控件中变量的值
	//UpdateData(FALSE);
}


void COpenGLBaseView::ShowControlBoard()
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


void COpenGLBaseView::OnDrawClear()
{
	m_DlgCtrlBoard->m_nNumber = 0;
	Invalidate();
}

void COpenGLBaseView::OnDrawPoints()
{
	m_DlgCtrlBoard->m_nNumber = 1;
	Invalidate();
}

void COpenGLBaseView::OnDrawLine()
{
	m_DlgCtrlBoard->m_nNumber = 2;
	Invalidate();
}

void COpenGLBaseView::OnDrawTraingles()
{
	m_DlgCtrlBoard->m_nNumber = 3;
	Invalidate();
}






