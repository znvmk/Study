
// MFCApplication3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"




//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_DEPRECATE
//#pragma warning(disable:4996)

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
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 对话框



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditOutPut);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_EditLableName);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	bool pass=CMFCApplication3Dlg::login();
	if (pass == false)
	{
		this->OnCancel();
		return false;
	}
	

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
	



	/*ListCtrl控件的使用*/

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_listCtrl2.SetBkColor(RGB(0, 0, 0))
	m_ListCtrl.SetTextBkColor(RGB(255, 255, 255)); //设置文本背景颜色
	m_ListCtrl.SetTextColor(RGB(255, 0, 0)); //设置文本颜色
	m_ListCtrl.DeleteAllItems();//清空





	sprintf_s(sql.querry, "SELECT user_id,user_name,user_second_sum FROM user_infoo");
	//显示刚才插入的数据  

	m_EditLableName.SetWindowTextW(_T("                                         user_infoo"));

	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&sql.mydata, sql.querry))
	{
		sql.c += "mysql_query() select data succeed";
		sql.c += "\r\n";
		//一次性取得数据集  
		result = mysql_store_result(&sql.mydata);
		//取得并打印行数  
		int rowcount = (int)mysql_num_rows(result);

		//取得并打印各字段的名称  
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;

		sql.c += "row count:";
		CString a;
		a.Format(_T("%d"), rowcount);
		sql.c += a;
		sql.c += "\r\n";


		/*字段的名称设置*/
		for (unsigned int i = 0; i < fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			sql.c += field->name;
			sql.c += "\r\t";

			CString n;
			n = field->name;
			m_ListCtrl.InsertColumn(i, n, LVCFMT_CENTER, 100);



			//cout << field->name << "\t\t";
		}
		//cout << endl;



		/*列设置*/
		for (int i = 0;i < rowcount;i++)
		{
			CString item;
			item.Format(_T("%d"), i + 1);
			m_ListBox.AddString(item);
			m_ListCtrl.InsertItem(i, item);
		}




		//打印各行  
		/*读取显示数据*/
		MYSQL_ROW row = NULL;
		row = mysql_fetch_row(result);
		sql.c += "\r\n";
		int i = 0;
		while (NULL != row)
		{
			sql.c += "\r\n";
			for (int j = 0; j < fieldcount; j++)
			{
				//cout << row[i] << "\t\t";
				sql.c += row[j];
				sql.c += "            ";
				CString r;
				r = row[j];
				m_ListCtrl.SetItemText(i, j, r);

			}
			i++;
			row = mysql_fetch_row(result);
		}
		
	}
	else
	{
		sql.c += "mysql_query() select data failed";
		sql.c += "\r\n";
		

		mysql_close(&sql.mydata);
		return -1;
	}



	//删除刚才建的表  
	sprintf_s(sql.querry, "DROP TABLE user_info");
	/*
	if (0 == mysql_query(&mydata, querry))
	{
	//cout << "mysql_query() drop table succeed" << endl;
	m_EditOutPut.SetWindowTextW(_T("mysql_query() drop table succeed"));
	}
	else
	{
	//cout << "mysql_query() drop table failed" << endl;
	m_EditOutPut.SetWindowTextW(_T("mysql_query() drop table failed"));
	mysql_close(&mydata);
	return -1;
	}
	*/
	mysql_free_result(result);
	mysql_close(&sql.mydata);
	mysql_server_end();


	/*输出信息*/
	m_EditOutPut.SetWindowTextW(sql.c);





	/*ListBox控件的使用*/
	
	



	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication3Dlg::OnPaint()
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
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



bool CMFCApplication3Dlg::login()
{
LG0:
	lg.m_EditUser = "";
	lg.m_EditPassWord = "";


LG1:
	lg.m_EditPassWord = "";


    UpdateData(FALSE);



	INT_PTR nResponse = lg.DoModal();

	

	if (nResponse == IDOK)
	{
		

		CString user,password;
		
		password =sql.login(lg.m_EditUser);
		if(lg.m_EditUser == "" )
		{
			AfxMessageBox(_T("账号不能为空!"),MB_ICONEXCLAMATION);
			 goto LG0;
		}
		else if (lg.m_EditPassWord == "")
		{
			AfxMessageBox(_T("密码不能为空!"), MB_ICONEXCLAMATION);
			goto LG1;
		}
		else if (password == "$")
		{
			AfxMessageBox(_T("你输入的账号有误，请重新输入!"));
			goto LG0;
		}
		else if(lg.m_EditPassWord==password)
		{
			
			return true;
		}
		else
		{
			AfxMessageBox(_T("你输入的密码有误，请重新输入!"));
			
			goto LG1;
		}
		

	}
    else if (nResponse == IDCANCEL)
	{
		int nFlag = MessageBox( _T("你确定要退出吗？"), _T("温馨提示"), MB_YESNO | MB_ICONQUESTION);
		if (nFlag == 7)
		{
			goto LG0;
		}
		else return false;
		
	}
}