
// MSerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MSer.h"
#include "MSerDlg.h"
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


// CMSerDlg 对话框



CMSerDlg::CMSerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MSER_DIALOG, pParent)
	, m_uiPort(0)
	, m_uiUserCount(0)
	, m_edit_csSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMSerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uiPort);
	DDX_Control(pDX, IDC_EDIT_LOG, m_edit_log);
	DDX_Text(pDX, IDC_STATIC_USER_COUNT, m_uiUserCount);
	DDX_Text(pDX, IDC_EDIT_SEND, m_edit_csSend);
}

BEGIN_MESSAGE_MAP(CMSerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMSerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMSerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMSerDlg 消息处理程序

BOOL CMSerDlg::OnInitDialog()
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
	m_uiPort = 8000;
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMSerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMSerDlg::OnPaint()
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
HCURSOR CMSerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMSerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	if (m_connect)
	{
		delete listenSocket;
		listenSocket = NULL;
		m_connect = false;
		SetDlgItemText(IDOK, _T("打开服务器"));
		UpdateEvent(_T("系统关闭服务器."));
		return;
	}
	//m_uiPort = m_pDP->m_uiPort;
	listenSocket = new CServerSocket();
	listenSocket->m_pMSDlg = this;// 指定对话框为主对话框，不能少了这句
	UpdateData(true);
	if (!listenSocket->Create(m_uiPort))                     // 创建服务器的套接字，IP地址默认本机IP
	{
		AfxMessageBox(_T("创建套接字错误！"));
		listenSocket->Close();
		return;
	}
	if (!listenSocket->Listen())
	{
		AfxMessageBox(_T("监听失败！"));
		listenSocket->Close();
		return;
	}
	m_connect = true;
	SetDlgItemText(IDOK, _T("关闭服务器"));
	CString csPort;
	csPort.Format(_T("%d"), m_uiPort);
	UpdateEvent(_T("系统打开服务器，端口号：")+csPort+ _T("."));
}


void CMSerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CMSerDlg::AddClient()
{
	CServerSocket* pSocket = new CServerSocket;
	pSocket->m_pMSDlg = this;
	listenSocket->Accept(*pSocket);
	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	m_DP.m_clientList.AddTail(pSocket);
	m_uiUserCount = m_DP.m_clientList.GetCount();
	UpdateData(false);
	UpdateEvent(_T("用户连接服务器."));
	//SendMSG(_T("Hello!"));
	//UpdateEvent(_T("发送消息：Hello!"));
	Broadcast();
}
void CMSerDlg::RemoveClient(CServerSocket* pSocket)

{
	POSITION nPos = m_DP.m_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;
	while (nPos)
	{
		CServerSocket* pSockItem = (CServerSocket*)m_DP.m_clientList.GetNext(nPos);
		if (pSockItem->m_hSocket == pSocket->m_hSocket)
		{
			pSockItem->Close();
			delete pSockItem;
			m_DP.m_clientList.RemoveAt(nTmpPos);
			m_uiUserCount = m_DP.m_clientList.GetCount();
			UpdateData(false);
			UpdateEvent(_T("用户离开."));
			return;
		}
		nTmpPos = nPos;
	}

}
void CMSerDlg::RecvData(CServerSocket* pSocket)

{
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char) * 1024);
	UCHAR leng = 0;
	CString str=_T("");
	leng = pSocket->Receive(pData, 1024, 0);
	str.Format(_T("%d"), leng);
	//AfxMessageBox(_T("接收信息长度：") + str);

	if (leng!= SOCKET_ERROR)
	{
		str = pData;
		//ControlPC(str);     // 依据指令控制电脑
		CString csM,csUserCount=_T("");
		csM=csUserCount=_T("");
		csUserCount.Format(_T("%d"), m_uiUserCount);
		csM += _T("你好，当前用户数量为：1234567890");//CString连接数字后，会丢失10个字节，即“1234567890”全部丢失，其中汉字字符占两个字节，数字字符占一个字节。
		csM += csUserCount;
//		AfxMessageBox(csUserCount);
		if (str == csConnectCode)
		{
			SendMSG(csM);
			//SendMSG(_T("abcdef"));
			SendMSG(csUserCount);
			SendMSG(_T("  "));//3个发送消息阻塞，下一次客户端接收，4条消息一起发送。
		}
		else
		{
			SendMSG(_T("发送成功:") + str);     // 转发数据给所有用户，包括发送数据的用户
		}
	}
	//AfxMessageBox(str);
	UpdateEvent(_T("接收消息：")+str);
	delete [] pData;
	pData = NULL;
}
void CMSerDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();
	// 用于换行显示日志
	str += _T("\r\n");

	// 获取系统当前时间
	string = _T("\r\nServer:")+ time.Format(_T("\t %Y/%m/%d %H:%M:%S\r\n") + str);
	// 格式化当前时间
	int lastLine = m_edit_log.LineIndex(m_edit_log.GetLineCount() - 1);
	//获取编辑框最后一行索引
	m_edit_log.SetSel(lastLine + 1, lastLine + 2, 0);
	//选择编辑框最后一行
	m_edit_log.ReplaceSel(string);                                                            //替换所选那一行的内容
}

void CMSerDlg::SendMSG(CString str)
{
	char* pSend = new char[str.GetLength()];
	memset(pSend, 0, str.GetLength() * sizeof(char));
	if (!m_DP.WChar2MByte(str.GetBuffer(0), pSend, str.GetLength()))
	{
		AfxMessageBox(_T("字符转换失败"));
		delete pSend;
		return;
	}
	POSITION nPos = m_DP.m_clientList.GetHeadPosition();
	while (nPos)
	{
		CServerSocket* pTemp = (CServerSocket*)m_DP.m_clientList.GetNext(nPos);
		pTemp->Send(pSend, str.GetLength());
	}
	delete pSend;
}
void CMSerDlg::ControlPC(CString AndroidControl)
{
	if (AndroidControl == "mop")             //打开播放器
	{
		ShellExecute(NULL, _T("open"), _T("C:\\Program Files (x86)\\KuGou\\KGMusic\\KuGou.exe"), NULL, NULL, SW_SHOWNORMAL);
	}
	else if (AndroidControl == "mcl")         //关闭播放器
	{
		DWORD id_num;
		HWND hWnd = ::FindWindow(_T("kugou_ui"), NULL);
		GetWindowThreadProcessId(hWnd, &id_num);
		//注意：第二个参数是进程的ID，返回值是线程的ID。
		HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id_num);
		TerminateProcess(hd, 0);
	}
	else if (AndroidControl == "mpl" || AndroidControl == "mpa")                //播放/暂停
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_F5, 0, 0, 0);
		keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}

}
BOOL CMSerDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_RETURN:
	case VK_ESCAPE:
		return true; break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMSerDlg::Broadcast()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_connect)return;                               //未连接服务器则不执行
	SendMSG(_T("Welcome come to use chat !"));

	UpdateData(true);                                     //获取界面数据
	int nErrorCode = 0;
	//	AfxMessageBox(m_strSend);
	if (m_edit_csSend != "")
	{
		UpdateEvent(_T("_send:") + m_edit_csSend);
		SendMSG(m_edit_csSend);
	}
	//m_edit_csSend = _T("");
	//UpdateData(false);
}
