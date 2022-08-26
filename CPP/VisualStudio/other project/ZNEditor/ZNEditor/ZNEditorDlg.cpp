
// ZNEditorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ZNEditor.h"
#include "ZNEditorDlg.h"
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
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZNEditorDlg 对话框



CZNEditorDlg::CZNEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZNEDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZNEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT1, mEdit1);
	//DDX_Control(pDX, IDC_TREE1, mCTreeCtrl);
}

BEGIN_MESSAGE_MAP(CZNEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, &CZNEditorDlg::OnHelpAbout)
	ON_COMMAND(ID_MENU_EXIT, &CZNEditorDlg::OnMenuExit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CZNEditorDlg 消息处理程序

BOOL CZNEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	//设置窗口初始化大小
	SetWindowPos(0, 0, 0, 880, 540, SWP_NOZORDER | SWP_NOMOVE);
	//菜单
	m_Menu.LoadMenu(IDR_MENU);
	SetMenu(&m_Menu);

	//工具栏
	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("Failed to Create Dialog Toolbar\n ");
		EndDialog(IDCANCEL);
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); //千万别忘了这句，好多教程都把这个忘了导致最后工具栏不显示
	

    //状态栏
	CTime time;
	time = time.GetCurrentTime();
	CString sTime;
	sTime = time.Format("%y-%m-%d %H:%M:%S");
	// 添加状态栏
	UINT array[3] = { 0,1,2 };
	m_Statusbar.Create(this);
	m_Statusbar.SetIndicators(array, sizeof(array) / sizeof(UINT));

	//显示状态栏
	CRect rect;
	GetWindowRect(rect);

	m_Statusbar.SetPaneInfo(0, array[0], 0, rect.Width() / 5);
	m_Statusbar.SetPaneText(0, sTime);

	m_Statusbar.SetPaneInfo(1, array[1], 0, rect.Width() / 5 * 2);
	m_Statusbar.SetPaneText(1, _T("行： 列： 字符："));

	m_Statusbar.SetPaneInfo(2, array[2], 0, rect.Width() / 5 * 3);
	m_Statusbar.SetPaneText(2, _T("文本编辑器2222222222222222222222222222222"));

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);


	CRect   getRect;
	//GetWindowRect(&getRect);//得到所处窗口的绝对坐标;    
	GetClientRect(&getRect);//得到相对坐标
	//创建树形控件
	//控件位置大小矩形
	//CRect treeRect(150, 37, 800, 500);
	CRect treeRect(0, 37, 140, 300);

	m_tree.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER |
		TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES |
		TVS_DISABLEDRAGDROP | TVS_NOTOOLTIPS | TVS_EDITLABELS,
		treeRect, this, IDC_TREE1);
	m_tree.DestroyWindow();

	//创建编辑控件
	//控件位置大小矩形
	//CRect editRect(150, 37, 800, 500);
	//CRect editRect(0, 37, 800, 500);
	CRect editRect;
	editRect.left = getRect.left;
	editRect.top =getRect.top + 37;
	editRect.right = getRect.right - 50;
	editRect.bottom = getRect.bottom - 50;
	m_edit.Create(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN |
		WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER | TVS_HASBUTTONS |
		TVS_LINESATROOT | TVS_HASLINES |
		TVS_DISABLEDRAGDROP | TVS_NOTOOLTIPS | TVS_EDITLABELS,
		editRect, this, IDC_EDIT1);



	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_EDIT1);    //获取控件指针，IDC_BUTTON1为控件ID号

	m_editFont.CreatePointFont(300, _T("楷体"), NULL);
	m_edit.SetFont(&m_editFont);
	m_edit.SetWindowTextW(_T("字体测试"));

	//	m_CEdit.DestroyWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZNEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZNEditorDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZNEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZNEditorDlg::OnHelpAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CZNEditorDlg::OnMenuExit()
{
	// TODO: 在此添加命令处理程序代码
	//	exit(0);
	// 
	//使用此方法退出程序，不可禁用IDCANCEL IDOK，否则失效。
	SendMessage(WM_CLOSE);
	//AfxGetMainWnd()->SendMessage(WM_CLOSE);
	//AfxGetMainWnd()->CloseWindow();
}


HBRUSH CZNEditorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)// IDC_Display为所选文本框ID    
	{

		pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色

		pDC->SetBkColor(RGB(0, 5, 0));//设置背景颜色

		//pDC->SetBkMode(TRANSPARENT);//设置背景透明  

	
	}
		// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
