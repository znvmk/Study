
// AdoEgDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AdoEg.h"
#include "AdoEgDlg.h"
#include "afxdialogex.h"
#include "vector"

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


// CAdoEgDlg 对话框



CAdoEgDlg::CAdoEgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADOEG_DIALOG, pParent)
	, m_strnId(_T(""))
	, m_strName(_T(""))
	, m_strScore(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdoEgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NID, m_strnId);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_strScore);
	DDX_Control(pDX, IDC_LIST1, m_StuList);
}

BEGIN_MESSAGE_MAP(CAdoEgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAdoEgDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAdoEgDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CAdoEgDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAdoEgDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAdoEgDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_QUREY, &CAdoEgDlg::OnBnClickedButtonQurey)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CAdoEgDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_SHOWALL, &CAdoEgDlg::OnBnClickedButtonShowall)
END_MESSAGE_MAP()


// CAdoEgDlg 消息处理程序

BOOL CAdoEgDlg::OnInitDialog()
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
	m_StuList.SetExtendedStyle(m_StuList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_StuList.InsertColumn(0, _T("学生学号"), LVCFMT_LEFT, 200);
	m_StuList.InsertColumn(1, _T("学生姓名"), LVCFMT_LEFT, 200);
	m_StuList.InsertColumn(2, _T("分数"), LVCFMT_LEFT, 200);
	/*
	m_StuList.InsertItem(0, _T("1"));
	m_StuList.SetItemText(0, 1, _T("1"));
	m_StuList.InsertItem(1, _T("2"));
	m_StuList.SetItemText(1, 1, _T("2"));
	*/
	//UpdateData(TRUE);
	
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAdoEgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAdoEgDlg::OnPaint()
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
HCURSOR CAdoEgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAdoEgDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	
}

void CAdoEgDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CAdoEgDlg::OnBnClickedButtonConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_AdoR.test();
	CString strSQL;
	//两种都可以
	//strSQL = _T("Provider=SQLOLEDB;Server=(local);Database=udb;UID=sa;PWD=pw123");
	strSQL = _T("Provider=SQLOLEDB;Server=CHEN-PC;Database=udb;UID=sa;PWD=pw123");
	m_AdoR.ConnectDb(strSQL);

	if (m_AdoR.IsConnectDb())
		AfxMessageBox(_T("数据库连接成功..."));
}

void CAdoEgDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSQL;
	CString Name;
	int nId,Score;
	/*
	nId = 1001;
	
	Score = 100;
	Name = _T("小明");
	strSQL.Format(_T("INSERT INTO StudentInfo(nId,Name,Score) VALUES('%d','%s','%d')"), nId, Name, Score);

	if (m_AdoR.Execute(strSQL))
		AfxMessageBox(_T("插入成功"));
		/*
	nId = 2;
	Name = _T("小刘");
	
	Score = 100;
	strSQL.Format(_T("INSERT INTO StudentInfo(nId,Name,Score) VALUES('%d','%s','%d')"), nId, Name, Score);

	if (m_AdoR.Execute(strSQL))
		AfxMessageBox(_T("插入成功"));
		*/
	/*
	for (int i = 0; i < 100; i++)
	{
		nId = i + 100001;
		Name.Format(_T("st%d"), i + 1);
		Score = rand()%50+50;
		strSQL.Format(_T("INSERT INTO StudentInfo(nId,Name,Score) VALUES('%d','%s','%d')"), nId, Name, Score);
		m_AdoR.Execute(strSQL);
	}
	AfxMessageBox(_T("suc"));
	//*/
}


void CAdoEgDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strSQL;
	if (m_strnId.IsEmpty() && m_strName.IsEmpty())
	{
		AfxMessageBox(_T("学生学号和姓名不能同时为空！"));
		return;
	}
	if (!m_strnId.IsEmpty())
	{
		strSQL.Format(_T("DELETE FROM StudentInfo WHERE nId=%s"), m_strnId);

		m_AdoR.Execute(strSQL);

		//QureyGet(strSQL);
	}
	else
	{
		//strSQL.Format(_T("SELECT * FROM StudentInfo WHERE Name='%s'"), m_strName);

		//QureyGet(strSQL);
	}
}


void CAdoEgDlg::OnBnClickedButtonQurey()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strSQL;
	if (m_strnId.IsEmpty() && m_strName.IsEmpty())
	{
		AfxMessageBox(_T("学生学号和姓名不能同时为空！"));
		return;
	}
	if (!m_strnId.IsEmpty())
	{
		strSQL.Format(_T("SELECT * FROM StudentInfo WHERE nId=%s"),m_strnId);

		QureyGet(strSQL);
	}
	else if (!m_strName.IsEmpty())
	{
		strSQL.Format(_T("SELECT * FROM StudentInfo WHERE Name='%s'"), m_strName);

		QureyGet(strSQL);
	}
	
}


void CAdoEgDlg::OnBnClickedButtonModify()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSQL;

	UpdateData(TRUE);
	if (m_strnId.IsEmpty())
	{
		AfxMessageBox(_T("学生学号不能为空！"));
		return;
	}
	if (m_strScore.IsEmpty() && m_strName.IsEmpty())
	{
		AfxMessageBox(_T("学生姓名和成绩不能同时为空！")); 
		return;
	}
	if (!m_strName.IsEmpty())
	{
		//strSQL.Format(_T("UPDATE StudentInfo SET Name='%s' WHERE nId=%s" ),m_strName,m_strnId);
		//m_AdoR.Execute(strSQL);
	}
	if(!m_strScore.IsEmpty())
	{
		//strSQL.Format(_T("UPDATE StudentInfo SET Score=%s WHERE nId=%s"), m_strName, m_strnId);
		//m_AdoR.Execute(strSQL);
	}
	
}





void CAdoEgDlg::OnBnClickedButtonShowall()
{
	// TODO: 在此添加控件通知处理程序代码

	
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM StudentInfo"));
	QureyGet(strSQL);
}
void CAdoEgDlg::QureyGet(CString strSQL)
{
	//**************************************************************
	// 数据获取分割
	
	_RecordsetPtr pRst;
	pRst = m_AdoR.Execute(strSQL);
	if (!pRst->adoBOF)
	{
		pRst->MoveFirst();
	}
	else
	{
		AfxMessageBox(_T("Data is empty !"));
	}
	CString me = _T("");
	//vector<_bstr_t> column_name;
	/*存储表的所有列名，显示表的列名*/
	for (int j = 0; j < pRst->Fields->GetCount(); j++)
	{
		me += (LPCTSTR)(pRst->Fields->GetItem(_variant_t((long)j))->Name);
		me += _T("     ");

		//column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name); 
	}   		 		/*对表进行遍历访问,显示表中每一行的内容*/
	CString set, settemp;
	for (int i = 0; !pRst->adoEOF; i++)
	{
		for (int j = 0; j < pRst->Fields->GetCount(); j++)
		{
			settemp = (LPCTSTR)(_bstr_t)(pRst->Fields->GetItem(_variant_t((long)j))->Value);
			settemp.Replace(_T(" "), NULL);

			set += settemp;
			set += _T(" ");
			//AfxMessageBox(me);
			//column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name); 
		}   		 		/*对表进行遍历访问,显示表中每一行的内容*/
		set += _T("/ ");
		pRst->MoveNext();
	}


	//AfxMessageBox(set);
	//*
	//CString s(_T("as dfg \n vbaf s dfadf \n fa fd af \n f fs"));
	CString s = set;
	int pos = 0, x = 0;
	CString dt[10000] = { _T("") };
	int count = 0;
	int b = 0;
	//*
	for (int i = 0; x != -1; i++)
	{

		x = s.Find(_T(" "), pos);
		b = x;
		if (x == -1)b = s.GetLength();
		dt[count] = s.Mid(pos, b - pos);
		pos = x + 1;

		//AfxMessageBox(dt[count]);
		count++;


	}
	/****在CString中查找是否完全包含

	bool CListCtrlEx2::strIFind(CString a,CString b)
{
	int pos,la,lb;
	pos=0;
	la=a.GetLength();
	lb=b.GetLength();

	if(la<lb) return false;

	while(pos<la)
	{
		pos=a.Find(b,pos);
		if(pos==-1) return false;

		if(b==a.Mid(pos, lb)) return true;
		pos ++;

		
	}
	return false;
}
	*/



	//**************************************************************
	//清空CListControl
	
	m_StuList.DeleteAllItems();

	//**************************************************************
	//显示SQL语句执行结果


	int d = 0;
	for (int i = 0; i < count; )//count
	{
		for (int j = 0; j < 3; j++, i++)
		{
			if (dt[i] == _T("/"))
			{
				d++;
				i++;
				CString c;
				c.Format(_T("%d"), d);
				//AfxMessageBox(c);
				break;
			}

			if (j == 0)
				m_StuList.InsertItem(d, dt[i]);
			else
				m_StuList.SetItemText(d, j, dt[i]);

		}
	}
	//*/
}