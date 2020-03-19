// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// IpFrame.cpp : CInPlaceFrame 类的实现
//

#include "stdafx.h"
#include "MFCApplication1.h"

#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWndEx)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CInPlaceFrame 构造/析构

CInPlaceFrame::CInPlaceFrame()
{
	EnableActiveAccessibility();
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar 实现就地调整大小。
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // 未能创建
	}

	// 默认情况下，最好注册一个与框架窗口
	//  无关的放置目标。  这将防止
	//  拖放对象“错过”支持拖放的容器中。
	m_dropTarget.Register(this);

	return 0;
}

// 框架将调用 OnCreateControlBars 以便在
//  容器应用程序的窗口上创建控件条。  pWndFrame 是容器的顶级框架窗口，
//  并且始终不为 NULL。  pWndDoc 是文档级框架窗口，
//  并且在容器是 SDI 应用程序时为 NULL。
//  服务器应用程序可以将 MFC 控件条放在这两个窗口中的任何一个上。
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// 如果使用 pWndDoc，则将此移除
	UNREFERENCED_PARAMETER(pWndDoc);

	// 设置此窗口的所有者，以便将消息发送到正确的应用程序
	m_wndToolBar.SetOwner(this);

	if (!COleIPFrameWndEx::OnCreateControlBars(pWndFrame, pWndDoc))
	{
		return FALSE;
	}

	COleCntrFrameWndEx* pNewFrame = DYNAMIC_DOWNCAST(COleCntrFrameWndEx, m_pMainFrame);
	ASSERT_VALID(pNewFrame);

	// 在客户端的框架窗口上创建工具栏
	if (!m_wndToolBar.CreateEx(pNewFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pNewFrame->EnableDocking(CBRS_ALIGN_ANY);
	pNewFrame->DockPane(&m_wndToolBar);

	// TODO: 如果不需要工具提示，则将此移除
	m_wndToolBar.SetControlBarStyle(m_wndToolBar.GetPaneStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式

	return COleIPFrameWndEx::PreCreateWindow(cs);
}


// CInPlaceFrame 诊断

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleIPFrameWndEx::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CInPlaceFrame 命令

