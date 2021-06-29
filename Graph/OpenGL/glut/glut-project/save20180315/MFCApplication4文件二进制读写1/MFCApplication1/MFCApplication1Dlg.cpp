
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

	DDX_Control(pDX, IDC_EDIT1, m_TextShow);
	DDX_Control(pDX, IDC_EDIT_PATH, m_EditPath);
	DDX_Control(pDX, IDC_EDIT_JUMP, m_EditJump);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(ID_AO, &CMFCApplication1Dlg::OnBnClickedAo)
	ON_WM_KEYDOWN()
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
	a = 0;
	i_pos = flength = 0;

	
	

	
	
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





void CMFCApplication1Dlg::OnBnClickedAo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	CString a, b;
	a = b = "";
	path = "E:\\GOChessBlack.tga";
	if (m_tgawr.LoadTGA(&texture[0], path))
	{
		//a.Format(_T("%d"), m_tgawr.tgaheader.Header[2]);
		//a = "读取成功！";
		//MessageBox(a);
	}
	//else
	{
		//a = "读取失败！";
		//MessageBox(a);
	}

	for (int i = 0;i < 6;i++)
	{
		//b.Format(_T("%d"), m_tgawr.tga.header[i]);
		b.Format(_T("%d"), m_tgawr.tga.Bpp);
		//b.Format(_T("%d"), m_tgawr.tgaheader.Header[i]);
		a += b;
		a += " ";
	}
	//a.Format(_T("%d"), m_tgawr.tga.header[3]);
	//GLubyte rt[7] = { 1,2,3,4,5,6,7 };
	//int ei = *rt;
	//a.Format(_T("%d"), *(rt+2));
	MessageBox(a);

	//Readbinary();
	
}


void CMFCApplication1Dlg::Readbinary()
{
	CString tex, temp, path, str_jumppos;
	int max;
	unsigned long uli_jmp;
	tex = " ";
	temp = " ";

	uli_jmp = 0;


	CFile cfile;
	m_EditPath.GetWindowTextW(path);
	m_EditJump.GetWindowTextW(str_jumppos);

	path.Replace(_T("\\"), _T("\\\\"));
	//m_EditPath.SetWindowTextW(path);

	cfile.Open(path, CFile::modeRead | CFile::typeBinary, NULL);

	

	max = 1000;
	short Buf[1000] = { 0 };

	uli_jmp = _ttoi(str_jumppos);

	uli_jmp = (unsigned long)uli_jmp;
	//temp.Format(_T("%uld"), uli_jmp);
	//MessageBox(temp);
	///*
	flength = cfile.GetLength();
	//余数
	int remainder = 0;
	if (uli_jmp <= flength)
	{
		i_pos = uli_jmp;
	}
	else
	{
		i_pos = flength - 1000;
		str_jumppos.Format(_T("%uld"), flength);
		m_EditJump.SetWindowTextW(str_jumppos);
	}
	if (i_pos < flength)
	{
		//余数
		remainder = flength - i_pos;
		if (remainder >= max)
			for (int j = 0; j < max;j++)
			{
				cfile.Seek(i_pos, CFile::begin);
				cfile.Read((Buf + j), 1);
				i_pos++;

			}
		else

		{
			for (int j = 0; j < remainder;j++)
			{
				cfile.Seek(i_pos, CFile::begin);
				cfile.Read((Buf + j), 1);
				i_pos++;
			}
		}


		for (int j = 0;j < max;j++)
		{
			temp.Format(_T("%d"), (int)Buf[j]);
			if (j == 0) tex = temp;
			else tex += temp;
			tex += " ";

			if (j > 0 && (j % 30) == 0)
			{
				tex += _T("\r\n");
			}
			Buf[j] = 0;
		}

		cfile.Close();
		m_TextShow.SetWindowTextW(tex);
		//EditAddtoText(tex);
		Invalidate();
		//cfile.Seek((flength - 2), CFile::begin);
		//cfile.SeekToEnd();
		//cfile.Read((Buf), 1);
		//temp.Format(_T("%d"), Buf[0]);
		//MessageBox(temp);
		//temp.Format(_T("%uld"), flength);


	}
}

void CMFCApplication1Dlg::EditAddtoText(CString add)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	int nLength = pEdit->GetWindowTextLength();

	//选定当前文本的末端  
	pEdit->SetSel(nLength, nLength);
	//l追加文本  
	pEdit->ReplaceSel(add);
}

void CMFCApplication1Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nChar==VK_UP) MessageBox(_T("keyup"));
	if (nChar == VK_LEFT) MessageBox(_T("keyuleft"));
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
