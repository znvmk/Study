
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*测试编辑框变量声明*/
	//DDX_Control(pDX, IDC_EDIT_TEST_SCROLL, m_editTestScroll);
	//DDX_Control(pDX, IDC_STATIC_LOG, m_staticLog);
	/*日志静态框变量声明*/

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEST, m_EditTest);
	DDX_Control(pDX, IDC_STATIC_LOG, m_staticLog);
}

/*映射表开始*/
BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	/*编辑框内容改变消息*/
	ON_EN_CHANGE(IDC_EDIT_TEST, OnChangeEditText)
	/*编辑框内容擦除消息*/
	ON_EN_ERRSPACE(IDC_EDIT_TEST,OnErrspaceEditText)
	/*编辑框失去焦点消息*/
	ON_EN_KILLFOCUS(IDC_EDIT_TEST,OnKillfocusEditText)
	/*编辑框内容达到最大值消息*/
	ON_EN_MAXTEXT(IDC_EDIT_TEST,OnMaxtextEditText)
	/*编辑框设置焦点消息*/
	ON_EN_SETFOCUS(IDC_EDIT_TEST,OnSetfocusEditText)
	/*编辑框内容更新消息*/
	ON_EN_UPDATE(IDC_EDIT_TEST,OnUpdateEditText)
	/*水平滚动消息*/
	ON_EN_HSCROLL(IDC_SCROLLBAR_V,OnHscrollEditTestScroll)
	/*垂直滚动消息*/
	ON_EN_VSCROLL(IDC_SCROLLBAR_H,OnVscrollEditTestScroll)
	/*获取文本消息*/
	ON_BN_CLICKED(IDC_BUTTON_GETTEXT,OnButtonGetEditText)
	/*设置文本消息*/
	ON_BN_CLICKED(IDC_BUTTON_SETTEXT,OnButtonSetEditText)
	/*获取行*/
	ON_BN_CLICKED(IDC_BUTTON_GETLINE, OnButtonGetLine)
	/*设置选择的内容*/
	ON_BN_CLICKED(IDC_BUTTON_GETSEL, OnButtonGetSel)
	/*获取选择对的内容*/
	ON_BN_CLICKED(IDC_BUTTON_SETSEL, OnButtonSetSel)
	/*文本替换*/
	ON_BN_CLICKED(IDC_BUTTON_REPLACESEL, OnButtonReplaceSel)
	/*信息提示*/
	ON_BN_CLICKED(IDC_STATIC_TEXT,OnStaticText)
	/*消息映射表结束*/

END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//设置对话框初始大小
	//函数原型：
		//BOOL SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 200, 200,600, 430, SWP_NOZORDER);


	//设置对话框固定大小，不能改变。
	DWORD dwStyle;
	dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle &= ~ WS_THICKFRAME;
	dwStyle &= ~ WS_MAXIMIZEBOX;
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		//CDialogEx::OnPaint();

		//给对话框添加背景图片
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);
		//双缓冲贴图
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP_DLGBACKGROUND);
		//IDB_BITMAP1是你自己的图对应的ID   
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		//强制改变图片大小使之适应对话框大小
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::WriteLog(CString message, CString title)
{
	m_staticLog.SetWindowTextW(title + _T("--") + message);
}



/*文本内容改变消息处理函数*/
void CMFCApplication1Dlg::OnChangeEditText()
{
	WriteLog(_T("接收到ON_EN_CHANGE消息"), _T("左边的编辑控件"));
	
}
/*文本内容擦除消息处理函数*/
void CMFCApplication1Dlg::OnErrspaceEditText()
{
	WriteLog(_T("接收到ON_EN_ERRSPACE消息"), _T("左边的编辑控件"));

}
/*失去焦点处理函数*/
void CMFCApplication1Dlg::OnKillfocusEditText()
{
	WriteLog(_T("接收到ON_EN_KILLFOCUS消息"), _T("左边的编辑控件"));

}
/*达到最大文本数消息处理函数*/
void CMFCApplication1Dlg::OnMaxtextEditText()
{
	WriteLog(_T("接收到ON_EN_MAXTEXT消息"), _T("左边的编辑控件"));

}
/*编辑框设置焦点消息*/
void CMFCApplication1Dlg::OnSetfocusEditText()
{
	WriteLog(_T("接收到ON_EN_SETFOCUS消息"), _T("左边的编辑控件"));

}
/*编辑框内容更新消息*/
void CMFCApplication1Dlg::OnUpdateEditText()
{
	WriteLog(_T("接收到ON_EN_UPDATE消息"), _T("左边的编辑控件"));

}
/*水平滚动消息*/
void CMFCApplication1Dlg::OnHscrollEditTestScroll()
{
	WriteLog(_T("接收到ON_EN_HSCROLL消息"), _T("右边的编辑控件"));

}
/*垂直滚动消息*/
void CMFCApplication1Dlg::OnVscrollEditTestScroll()
{
	WriteLog(_T("接收到ON_EN_VSCROLL消息"), _T("右边的编辑控件"));

}
/*获取文本消息*/
void CMFCApplication1Dlg::OnButtonGetEditText()
{
	CString content;
	m_EditTest.GetWindowTextW(content);
	MessageBox(content, _T("获取左边编辑框的内容"));
}

/*设置文本消息*/
void CMFCApplication1Dlg::OnButtonSetEditText()
{
	m_EditTest.SetWindowTextW(_T("您好，这是测试"));
}
/*获取行*/
void CMFCApplication1Dlg::OnButtonGetLine()
{
	TCHAR content[256];
	memset(content, 0X00, sizeof(content));
	int iCount = m_EditTest.GetLine(1, content, sizeof(content));
	if (iCount > 0)MessageBox(content, _T("GETLINE获取第二行的内容"));
	else MessageBox(_T("失败"), _T("GETLINE获取第二行的内容"));
}

/*获取选择对的内容*/
void CMFCApplication1Dlg::OnButtonGetSel()
{
	int iStart = 0, iEnd = 0;
	m_EditTest.GetSel(iStart, iEnd);
	CString log;
	log.Format(_T("选择的内容从第%d个字符到第%d个字符"), iStart, iEnd);
	MessageBox(log, _T("GetSel"));
}
//*设置选择的内容*/
void CMFCApplication1Dlg::OnButtonSetSel()
{
	m_EditTest.SetSel(5, 10, TRUE);
	MessageBox(_T("选择的内容从第6个字符到第11个字符"), _T("SetSel"));
}
/*文本替换*/
void CMFCApplication1Dlg::OnButtonReplaceSel()
{
	m_EditTest.ReplaceSel(_T("此处是最新的内容"));
}

void CMFCApplication1Dlg::OnStaticText()
{
	MessageBox(_T("如果使用SS_NOTIFY创建静态控件，\n则可以接收单击事件，\n此处就是例子。"), _T("静态控件"));
}

/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/



