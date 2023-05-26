
// MClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MClient.h"
#include "MClientDlg.h"
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
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
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


// CMClientDlg 对话框



CMClientDlg::CMClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCLIENT_DIALOG, pParent)
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Control(pDX, IDOK, m_btnConSer);
	DDX_Text(pDX, IDC_EDIT_PORT, port);
	DDX_Control(pDX, IDC_EDIT_RECIVE, m_edit_log);
}

BEGIN_MESSAGE_MAP(CMClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SEND_MESSAGE, &CMClientDlg::OnBnClickedButtonSendMessage)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMClientDlg 消息处理程序

BOOL CMClientDlg::OnInitDialog()
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

	port = 8000;
	UpdateData(false);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMClientDlg::OnPaint()
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
HCURSOR CMClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMClientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//获取端口号
	UpdateData(true);

	if (m_connect)                             // 如果已经连接，则断开服务器
	{
		m_connect = false;
		pSock->Close();
		delete pSock;
		pSock = NULL;
		m_btnConSer.SetWindowTextW(_T("连接服务器"));
		UpdateData(false);
		return;
	}
	else                                                // 未连接，则连接服务器
	{
		pSock = new CClientSocket();
		if (!pSock->Create())         //创建套接字
		{
			AfxMessageBox(_T("创建套接字失败！"));
			return;
		}
	}
	if (!pSock->Connect(_T("127.0.0.1"), port))    //连接服务器
	{
		AfxMessageBox(_T("连接服务器失败！"));
		return;
	}
	else
	{
		m_connect = true;
		m_btnConSer.SetWindowTextW(_T("断开服务器"));
		UpdateEvent(_T("已连接服务器！"));
		
		//if (m_strRecevie != _T("")) UpdateEvent(_T("_receive:\t") + m_strRecevie);
		setReceiveMessage(nSendMessage(csConnectCode));
		UpdateData(false);
	//	SetTimer(0, 1000, NULL);
	}
}

void CMClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMClientDlg::OnBnClickedButtonSendMessage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_connect)return;                               //未连接服务器则不执行
	UpdateData(true);                                     //获取界面数据
	//	AfxMessageBox(m_strSend);
	setReceiveMessage(nSendMessage(m_strSend));
}

void CMClientDlg::UpdateEvent(CString str)
{
	CString cstr;
	CTime time = CTime::GetCurrentTime();
	// 用于换行显示日志
	str += _T("\r\n");
	
	// 获取系统当前时间
	cstr = _T("\t") + time.Format(_T("  %Y/%m/%d %H:%M:%S \r\n")) + _T("Client: ") + str;
	// 格式化当前时间
	int lastLine = m_edit_log.LineIndex(m_edit_log.GetLineCount() - 1);
	//获取编辑框最后一行索引
	m_edit_log.SetSel(lastLine + 1, lastLine + 2, 0);
	//选择编辑框最后一行
	m_edit_log.ReplaceSel(cstr);                                                             //替换所选那一行的内容
}

void CMClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 0:
		break;
	default:
		break;
	}
	if (nIDEvent == 0)
	{
		setReceiveMessage(nSendMessage(csConnectCode));
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CMClientDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if (n < nlen)return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}
int  CMClientDlg::nSendMessage(CString message)
{
	int nErrorCode = 0;
	if (message != "")
	{
		char* pBuff = new char[message.GetLength()];
		memset(pBuff, 0, message.GetLength());
		WChar2MByte(message.GetBuffer(0), pBuff, message.GetLength());

		CString csInfo(_T(""));
		csInfo.Format(_T("%s"), pBuff);
		//	AfxMessageBox(message);
		nErrorCode=pSock->SendMSG(pBuff, message.GetLength());

		if(message != csConnectCode) UpdateEvent(_T("Client Send:")+m_strSend);

		return nErrorCode;
	}
	else
		return 0;

}
void CMClientDlg::setReceiveMessage(int nErrorCode)
{
	m_strReceive=pSock->OnRecevie(nErrorCode);
	if(m_strReceive != _T("") /*&& m_strReceive != csSendCode*/) UpdateEvent(_T("Client Receive:") + m_strReceive);
	m_strReceive != _T("");

}
