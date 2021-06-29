
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

	DDX_Control(pDX, IDC_EDIT1, m_EditShow);
	DDX_Control(pDX, IDC_EDIT_PATH, m_EditPath);
	DDX_Control(pDX, IDC_EDIT_JUMP, m_EditJump);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(ID_BUTTON_READJUMP, &CMFCApplication1Dlg::OnBnClickedReadJump)
	ON_BN_CLICKED(ID_BUTTON_WRITE, &CMFCApplication1Dlg::OnBnClickedWrite)
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





void CMFCApplication1Dlg::OnBnClickedReadJump()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tex, temp,path,str_jumppos;
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

	uli_jmp=_ttoi(str_jumppos);

	uli_jmp = (unsigned long)uli_jmp ;
	//temp.Format(_T("%uld"), uli_jmp);
	//MessageBox(temp);
	///*
	flength = cfile.GetLength();
	//余数
	int remainder=0;
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


		m_EditShow.SetWindowTextW(tex);
		//EditAddtoText(tex);
		Invalidate();
		//cfile.Seek((flength - 2), CFile::begin);
		//cfile.SeekToEnd();
		//cfile.Read((Buf), 1);
		//temp.Format(_T("%d"), Buf[0]);
		//MessageBox(temp);
		//temp.Format(_T("%uld"), flength);


	}
	cfile.Close();
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

void CMFCApplication1Dlg::OnBnClickedWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	CString textwrite, temp, path;
	
	int max;
	
	//textwrite = " ";
	//temp = " ";

	CFile cfile;
	m_EditPath.GetWindowTextW(path);
	m_EditShow.GetWindowTextW(textwrite);

	path.Replace(_T("\\"), _T("\\\\"));
	//m_EditPath.SetWindowTextW(path);



	/*
	CString strData = _T("123456ab?!@c");
	char cData[1024];
	char *pBuff = (char*)strData.GetBuffer(strData.GetLength());
	char one = pBuff[0];
	char two = pBuff[1];
	int i = 0;
	for (; i < strData.GetLength(); i++)
	{
		cData[i] = pBuff[i * 2];
	}
	cData[i] = '\0';
	*/


	short WriteBuf[1000] = { 0 };
	TransformStringToInt(WriteBuf, textwrite);

	cfile.Open(path, CFile::modeWrite | CFile::typeBinary, NULL);
	max = 1000;
	
	
	
	//cfile.SeekToEnd();
	for (int j = 0; j < 2;j++)
	{
		//cfile.Seek(i_pos, CFile::begin);
		cfile.SeekToEnd();
		cfile.Write((WriteBuf + j), 1);
		//cfile.Write((Buf + j), 1);

	}
	
	cfile.Close();
}


void CMFCApplication1Dlg::TransformStringToInt(short* buf, CString strData)
{
	//CString strData = _T("123456ab?!@c");



	char cData[1000];
	char *pBuff = (char*)strData.GetBuffer(strData.GetLength());
	char one = pBuff[0];
	char two = pBuff[1];
	int i = 0;
	for (; i < strData.GetLength(); i++)
	{
		cData[i] = pBuff[i * 2];
	}
	cData[i] = '\0';


	int l, r;
	l = r = 0;
	int j = 0;
	//if(i>0)j=i-1;
	while(j<i)
	{
		*buf = 0;
		
		//数位
		int numbit = 0;
		int db = 0;
		
		while (j <i && cData[j] != ' ')
		{
			j++;
		}
		r = j;
		numbit = r - l-1;
		for(;l<r;l++)
		{
			switch (cData[l])
			{
			case'0':db = 0;break;
			case'1':db = 1;break;
			case'2':db = 2;break;
			case'3':db = 3;break;
			case'4':db = 4;break;
			case'5':db = 5;break;
			case'6':db = 6;break;
			case'7':db = 7;break;
			case'8':db = 8;break;
			case'9':db = 9;break;
			default:break;
			}
			int a = 1;
			for (int i = 0;i < numbit;i++)a *= 10;
			*buf += a*db;
			numbit--;
		}
		l = r + 1;
		j++;
		buf++;
	}
}