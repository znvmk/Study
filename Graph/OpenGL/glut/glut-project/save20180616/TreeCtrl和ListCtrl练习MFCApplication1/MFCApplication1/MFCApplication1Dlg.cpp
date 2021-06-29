
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
	DDX_Control(pDX , IDC_TREE1 , m_tcTestTree);
	DDX_Control(pDX , IDC_LIST1 , m_lcTestList);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_NOTIFY(TVN_SELCHANGED , IDC_TREE1 , &CMFCApplication1Dlg::OnTvnSelchangedTree1)

	ON_NOTIFY(TVN_GETINFOTIP , IDC_TREE1 , &CMFCApplication1Dlg::OnTvnGetInfoTipTree1)
	ON_NOTIFY(NM_CLICK , IDC_LIST1 , &CMFCApplication1Dlg::OnNMClickList1)
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


	InitTreeCtrl();
	InitListCtrl();


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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCApplication1Dlg::InitTreeCtrl()
{
	HICON hIcon[3];      // 图标句柄数组   
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
	HTREEITEM hArtItem;  // 可表示任一文章节点的句柄   

						 // 加载三个图标，并将它们的句柄保存到数组   
	hIcon[0] = theApp.LoadIcon(IDI_ICON1);
	hIcon[1] = theApp.LoadIcon(IDI_ICON2);
	hIcon[2] = theApp.LoadIcon(IDI_ICON3);

	// 创建图像序列CImageList对象   
	m_imageList.Create(32 , 32 , ILC_COLOR32 , 3 , 3);
	// 将三个图标添加到图像序列   
	for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}

	// 为树形控件设置图像序列   
	m_tcTestTree.SetImageList(&m_imageList , TVSIL_NORMAL);

	// 插入根节点   
	hRoot = m_tcTestTree.InsertItem(_T("鸡啄米") , 0 , 0);
	// 在根节点下插入子节点   
	hCataItem = m_tcTestTree.InsertItem(_T("IT互联网") , 1 , 1 , hRoot , TVI_LAST);
	// 为“IT互联网”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hCataItem , 1);
	// 在“IT互联网”节点下插入子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("百度文章1") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“百度文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 2);
	// 在“IT互联网”节点下插入另一子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("谷歌文章2") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“谷歌文章2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 3);
	// 在根节点下插入第二个子节点   
	hCataItem = m_tcTestTree.InsertItem(_T("数码生活") , 1 , 1 , hRoot , TVI_LAST);
	// 为“数码生活”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hCataItem , 4);
	// 在“数码生活”节点下插入子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("智能手机文章1") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“智能手机文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 5);
	// 在“数码生活”节点下插入另一子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("平板电脑文章2") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“平板电脑文章2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 6);
	// 在根节点下插入第三个子节点   
	hCataItem = m_tcTestTree.InsertItem(_T("软件开发") , 1 , 1 , hRoot , TVI_LAST);
	// 为“软件开发”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hCataItem , 7);
	// 在“软件开发”节点下插入子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("C++编程入门系列1") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“C++编程入门系列1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 8);
	// 在“软件开发”节点下插入另一子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("VS2010/MFC编程入门2") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“VS2010/MFC编程入门2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 9);
	// 在根节点下插入第四个子节点   
	hCataItem = m_tcTestTree.InsertItem(_T("娱乐休闲") , 1 , 1 , hRoot , TVI_LAST);
	// 为“娱乐休闲”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hCataItem , 10);
	// 在“娱乐休闲”节点下插入子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("玛雅文明文章1") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“玛雅文明文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 11);
	// 在“娱乐休闲”节点下插入另一子节点   
	hArtItem = m_tcTestTree.InsertItem(_T("IT笑话2") , 2 , 2 , hCataItem , TVI_LAST);
	// 为“IT笑话2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_tcTestTree.SetItemData(hArtItem , 12);
}



void CMFCApplication1Dlg::OnTvnSelchangedTree1(NMHDR *pNMHDR , LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString strText; // 树节点的标签文本字符串   

					 // 获取当前选中节点的句柄   
	HTREEITEM hItem = m_tcTestTree.GetSelectedItem();
	// 获取选中节点的标签文本字符串   
	strText = m_tcTestTree.GetItemText(hItem);
	// 将字符串显示到编辑框中   
	SetDlgItemText(IDC_EDIT1 , strText);
}


void CMFCApplication1Dlg::OnTvnGetInfoTipTree1(NMHDR *pNMHDR , LRESULT *pResult)
{
	LPNMTVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMTVGETINFOTIP>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NMTVGETINFOTIP* pTVTipInfo = (NMTVGETINFOTIP*)pNMHDR;   // 将传入的pNMHDR转换为NMTVGETINFOTIP指针类型   
	HTREEITEM hRoot = m_tcTestTree.GetRootItem();      // 获取树的根节点   
	CString strText;     // 每个树节点的提示信息   

	if (pTVTipInfo->hItem == hRoot)
	{
		// 如果鼠标划过的节点是根节点，则提示信息为空   
		strText = _T("");
	}
	else
	{
		// 如果鼠标划过的节点不是根节点，则将该节点的附加32位数据格式化为字符串   
		strText.Format(_T("%d") , pTVTipInfo->lParam);
	}

	// 将strText字符串拷贝到pTVTipInfo结构体变量的pszText成员中，这样就能显示内容为strText的提示信息   
	wcscpy(pTVTipInfo->pszText , strText);
}


void CMFCApplication1Dlg::InitListCtrl()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_lcTestList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_lcTestList.SetExtendedStyle(m_lcTestList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	m_lcTestList.InsertColumn(0 , _T("语言") , LVCFMT_CENTER , rect.Width() / 3 , 0);
	m_lcTestList.InsertColumn(1 , _T("2012.02排名") , LVCFMT_CENTER , rect.Width() / 3 , 1);
	m_lcTestList.InsertColumn(2 , _T("2011.02排名") , LVCFMT_CENTER , rect.Width() / 3 , 2);

	// 在列表视图控件中插入列表项，并设置列表子项文本   
	m_lcTestList.InsertItem(0 , _T("Java"));
	m_lcTestList.SetItemText(0 , 1 , _T("1"));
	m_lcTestList.SetItemText(0 , 2 , _T("1"));
	m_lcTestList.InsertItem(1 , _T("C"));
	m_lcTestList.SetItemText(1 , 1 , _T("2"));
	m_lcTestList.SetItemText(1 , 2 , _T("2"));
	m_lcTestList.InsertItem(2 , _T("C#"));
	m_lcTestList.SetItemText(2 , 1 , _T("3"));
	m_lcTestList.SetItemText(2 , 2 , _T("6"));
	m_lcTestList.InsertItem(3 , _T("C++"));
	m_lcTestList.SetItemText(3 , 1 , _T("4"));
	m_lcTestList.SetItemText(3 , 2 , _T("3"));
}

void CMFCApplication1Dlg::OnNMClickList1(NMHDR *pNMHDR , LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString strLangName;    // 选择语言的名称字符串   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		strLangName = m_lcTestList.GetItemText(pNMListView->iItem , 0);
		// 将选择的语言显示与编辑框中   
		SetDlgItemText(IDC_EDIT2 , strLangName);
	}
}
