
// mdbDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "mdb.h"
#include "mdbDlg.h"
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


// CmdbDlg 对话框



CmdbDlg::CmdbDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MDB_DIALOG, pParent)
	, m_editID(_T(""))
	, m_editEncode(_T(""))
	, m_editEntry(_T(""))
	, m_editSort(_T(""))
	, m_editSetTop(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmdbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lcTable);
	DDX_Text(pDX, IDC_EDIT_ID, m_editID);
	DDX_Text(pDX, IDC_EDIT_ENCODE, m_editEncode);
	DDX_Text(pDX, IDC_EDIT_ENTRY, m_editEntry);
	DDX_Text(pDX, IDC_EDIT_SORT, m_editSort);
	DDX_Text(pDX, IDC_EDIT_SETTOP, m_editSetTop);
	DDX_Control(pDX, IDC_COMBO_CLASSIFY, m_comboClassify);
}

BEGIN_MESSAGE_MAP(CmdbDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_DISPLAY, &CmdbDlg::OnBnClickedDisplay)
	ON_BN_CLICKED(ID_CLEAR, &CmdbDlg::OnBnClickedClear)
	ON_BN_CLICKED(ID_RESET, &CmdbDlg::OnBnClickedReset)
	ON_BN_CLICKED(ID_ADD, &CmdbDlg::OnBnClickedAdd)
	ON_BN_CLICKED(ID_DELETE, &CmdbDlg::OnBnClickedDelete)
	ON_BN_CLICKED(ID_SEARCH, &CmdbDlg::OnBnClickedSearch)
	ON_BN_CLICKED(ID_EXPORT, &CmdbDlg::OnBnClickedExport)
END_MESSAGE_MAP()


// CmdbDlg 消息处理程序

BOOL CmdbDlg::OnInitDialog()
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
	m_Menu.LoadMenu(IDR_MENU1);  //IDR_MENU1为菜单栏ID号
	SetMenu(&m_Menu);
	m_comboClassify.AddString(_T("系统词库"));
	m_comboClassify.AddString(_T("用户词库"));
	m_comboClassify.AddString(_T("高频词库"));
	m_comboClassify.AddString(_T("系统词库"));



	GetDlgItem(ID_DISPLAY)->EnableWindow(0);
	GetDlgItem(ID_CLEAR)->EnableWindow(0);
	GetDlgItem(ID_RESET)->EnableWindow(0);
	GetDlgItem(ID_ADD)->EnableWindow(0);
	GetDlgItem(ID_DELETE)->EnableWindow(0);
	GetDlgItem(ID_SEARCH)->EnableWindow(0);
	GetDlgItem(ID_DISPLAY)->EnableWindow(0);
	GetDlgItem(ID_DISPLAY)->EnableWindow(0);

	SetStaticContrlText(IDC_STATIC_TABLE, _T(""));
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("请连接数据库"));
	ConnectDb();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmdbDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmdbDlg::OnPaint()
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
HCURSOR CmdbDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmdbDlg::ConnectDb()
{
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("请连接数据库"));
	//Query.CreateDatabase();
	GetDlgItem(ID_DISPLAY)->EnableWindow(1);
	GetDlgItem(ID_CLEAR)->EnableWindow(1);
	GetDlgItem(ID_RESET)->EnableWindow(1);
	GetDlgItem(ID_ADD)->EnableWindow(1);
	GetDlgItem(ID_DELETE)->EnableWindow(1);
	GetDlgItem(ID_SEARCH)->EnableWindow(1);
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("数据库已连接"));

}


void CmdbDlg::OnBnClickedDisplay()
{
	// TODO: 在此添加控件通知处理程序代码
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("正在查询..."));
	GetDlgItem(ID_DISPLAY)->EnableWindow(0);

	SetStaticContrlText(IDC_STATIC_TABLE, _T("table user data"));
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("查询成功"), ShowListContrl(Query.GetAllData()));
	GetDlgItem(ID_DISPLAY)->EnableWindow(1);
	Query.GetAllData();

}


void CmdbDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("清空数据..."));
	SetStaticContrlText(IDC_STATIC_TABLE, _T(""));
	GetDlgItem(ID_CLEAR)->EnableWindow(0);
	ShowListContrl(_T(""));
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("数据已清空"));
	GetDlgItem(ID_CLEAR)->EnableWindow(1);
}


void CmdbDlg::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("重置数据中..."));
	//	SetStaticContrlText(IDC_STATIC_TABLE, _T("table user data"));
	//	ShowListContrl(_T("fasdfasdf"));
	GetDlgItem(ID_RESET)->EnableWindow(0);
	Query.SetData();
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("重置成功"));
	GetDlgItem(ID_RESET)->EnableWindow(1);
}


void CmdbDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("添加数据中..."));
	GetDlgItem(ID_ADD)->EnableWindow(0);
	Query.Insert(100, _T("ccdd"), _T("啊啊啊啊"), 10, 10);

	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("添加成功"), ShowListContrl(Query.GetAllData()));
	GetDlgItem(ID_ADD)->EnableWindow(1);
}


void CmdbDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("删除数据中..."));
	GetDlgItem(ID_DELETE)->EnableWindow(0);
	//Query.Insert(110, _T("na110"), 111);

	if (Query.Delete(100))
		SetStaticContrlText(IDC_STATIC_INFORMATION, _T("删除成功"), ShowListContrl(Query.Search(10)));
	else
		SetStaticContrlText(IDC_STATIC_INFORMATION, _T("删除失败"), ShowListContrl(Query.Search(10)));
	GetDlgItem(ID_DELETE)->EnableWindow(1);
}


void CmdbDlg::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("查询数据中..."));
	GetDlgItem(ID_SEARCH)->EnableWindow(0);
	//Query.Insert(110, _T("na110"), 111);
	if (ShowListContrl(Query.Search(100)))
		SetStaticContrlText(IDC_STATIC_INFORMATION, _T("查询成功"), ShowListContrl(Query.Search(10)));
	else
		SetStaticContrlText(IDC_STATIC_INFORMATION, _T("查询无结果"));
	GetDlgItem(ID_SEARCH)->EnableWindow(1);
}

void CmdbDlg::OnBnClickedExport()
{
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("导出数据中..."));
	GetDlgItem(ID_EXPORT)->EnableWindow(0);
	CString tabledata = Query.GetAllData();

	CString csCodeTableExport;
	csCodeTableExport = _T("");

	csCodeTableExport += _T("编号"); csCodeTableExport += _T("   ");
	csCodeTableExport += _T("编码"); csCodeTableExport += _T("   ");
	csCodeTableExport += _T("词条"); csCodeTableExport += _T("   ");
	csCodeTableExport += _T("词库分类"); csCodeTableExport += _T("   ");
	csCodeTableExport += _T("排序"); csCodeTableExport += _T("   ");
	csCodeTableExport += _T("固顶"); csCodeTableExport += _T("   ");

	csCodeTableExport += _T("\r");

	int count = 0;
	int pos = 0;
	int base = 0;
	while (pos < tabledata.GetLength())
	{
		pos = tabledata.Find(_T(" "), pos);
		if (pos == 0)
		{
			pos++;
			continue;
		}
		if (pos == -1)pos = tabledata.GetLength();
		csCodeTableExport += tabledata.Mid(base, pos - base);
		csCodeTableExport += _T("   ");
		base = pos;
		pos++;
		count++;
		if (count > 5)
		{
			count = 0;
			csCodeTableExport += _T("\r");
		}

	}
	frw.FileWriteCodeTableExport(csCodeTableExport);

	//frw.FileReadCodeTableExport();
	SetStaticContrlText(IDC_STATIC_INFORMATION, _T("数据已成功导出"));
	GetDlgItem(ID_EXPORT)->EnableWindow(1);
}

int CmdbDlg::ShowListContrl(CString tabledata)
{
	// 为列表视图控件添加全行选中和栅格风格   
	m_lcTable.SetExtendedStyle(m_lcTable.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//清空表格数据和格式
	m_lcTable.DeleteAllItems();
	while (m_lcTable.DeleteColumn(0));

	//AfxMessageBox(tabledata);

	if (tabledata.GetLength() <= 0) return 0;

	m_lcTable.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 100, 0);
	m_lcTable.InsertColumn(1, _T("编码"), LVCFMT_CENTER, 100, 1);
	m_lcTable.InsertColumn(2, _T("词条"), LVCFMT_CENTER, 100, 2);
	m_lcTable.InsertColumn(3, _T("词库分类"), LVCFMT_CENTER, 100, 3);
	m_lcTable.InsertColumn(4, _T("排序"), LVCFMT_CENTER, 100, 4);
	m_lcTable.InsertColumn(5, _T("固顶"), LVCFMT_CENTER, 100, 5);

	/*m_lcTable.InsertItem(0, _T("a0"));
	m_lcTable.SetItemText(0, 1, _T("b0"));
	m_lcTable.SetItemText(0, 2, _T("c0"));*/

	int line = 0;
	int count = 0;
	int pos = 0;
	int base = 0;

	while (pos < tabledata.GetLength())
	{
		pos = tabledata.Find(_T(" "), pos);
		if (pos == 0)
		{
			pos++;
			continue;
		}
		if (pos == -1)pos = tabledata.GetLength();
		//AfxMessageBox(tabledata);
		if (count == 0)m_lcTable.InsertItem(line, tabledata.Mid(base, pos - base));
		else m_lcTable.SetItemText(line, count, tabledata.Mid(base, pos - base));
		base = pos;
		pos++;
		count++;
		if (count > 5)
		{
			count = 0;
			line++;
		}
	}
	return line;
}

void CmdbDlg::SetStaticContrlText(int idc, CString text, int line)
{
	CFont font;
	font.CreatePointFont(100, _T("宋体"));

	CString count;
	count.Format(_T("%d"), line);
	if (line != 0)
	{
		text += _T("，共计：");
		text += count;
		text += _T(" 条");
	}

	GetDlgItem(idc)->SetFont(&font);
	GetDlgItem(idc)->SetWindowTextW(text);

}



