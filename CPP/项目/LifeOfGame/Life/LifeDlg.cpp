
// LifeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Life.h"
#include "LifeDlg.h"
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
//	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_PAINT()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_TIMER()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLifeDlg 对话框



CLifeDlg::CLifeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIFE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLifeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLifeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_BUTTON_SETTING, &CLifeDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(ID_BUTTON_START, &CLifeDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(ID_BUTTON_PAUSE, &CLifeDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(ID_BUTTON_OVER, &CLifeDlg::OnBnClickedButtonOver)
	ON_BN_CLICKED(ID_BUTTON_ADD, &CLifeDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(ID_BUTTON_MINUS, &CLifeDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(ID_BUTTON_QUIT, &CLifeDlg::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// CLifeDlg 消息处理程序

BOOL CLifeDlg::OnInitDialog()
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

//	ShowWindow(SW_MAXIMIZE);

//	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	//设置对话框初始大小
	CRect temprect(0, 0, 850, 640);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER |
	SWP_NOMOVE);



	//初始化变量
	//m_plbt = (0, 0);
	m_bpause = false;
	tempSpeed=m_ispeed = 27;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLifeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLifeDlg::OnPaint()
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
HCURSOR CLifeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLifeDlg::DrawBoard(CDC* pDC)
{

	//画网格

	//获得客户窗口矩形
	CRect rect;
	GetClientRect(&rect);

	//设置背景
	//CRect rect(500, 0, 880, 500);

	pDC->FillSolidRect(rect, RGB(0, 255, 0));//背景颜色填充

	//定义画笔
	// 生成画笔
	CPen PenBlackLine1(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *poldpenline1;
	poldpenline1 = pDC->SelectObject(&PenBlackLine1);

	//单位长度
	int unit=15;
	int unitLength=40;
	for (int i = 0; i<unitLength; i++)
	{
		pDC->MoveTo(unit + i * unit, 0);
		pDC->LineTo(unit + i * unit, unit*unitLength);
		pDC->MoveTo(0, unit + i * unit);
		pDC->LineTo(unit*unitLength, unit + i * unit);

	}
	//释放画笔
	pDC->SelectObject(poldpenline1);

}


void CLifeDlg::DrawInformation(CDC* pDC)
{


	//设置背景
	CRect rect(601, 0, 835, 600);

	pDC->FillSolidRect(rect, RGB(128, 128, 128));//背景颜色填充

	//定义画笔
	//生成画笔
	CPen PenBlackLine1(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *poldpenline1;
	poldpenline1 = pDC->SelectObject(&PenBlackLine1);

	//释放画笔
	pDC->SelectObject(poldpenline1);


	CFont font;
	CFont *poldfont;
	poldfont = pDC->SelectObject(&font);
	font.CreateFont(
		16,                                                  //   nHeight  
		8,                                                   //   nWidth  
		0,                                                   //   nEscapement
		0,                                                   //   nOrientation  
		20,                                   //   nWeight  
		FALSE,                                           //   bItalic  
		FALSE,                                           //   bUnderline  
		0,                                                   //   cStrikeOut  
		ANSI_CHARSET,                             //   nCharSet  
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision  
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision  
		DEFAULT_QUALITY,                       //   nQuality  
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("楷体"));

	//数据转换
	CString blacktaking, whitetaking, step, blacktime, whitetime, steptime, informationtemp, currentplayer;
	//释放字体
	pDC->SelectObject(poldfont);
}


void CLifeDlg::DrawDiamonds(CDC* pDC)
{
	//画棋盘坐标信息

	CBrush fillbrush;
	CBrush *oldbrush;
	fillbrush.CreateSolidBrush(RGB(255, 0, 0));
	oldbrush = pDC->SelectObject(&fillbrush);

	CPoint p;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j <40; j++)
		{
			//pDC->Ellipse(p.x,p.y,p.x+5,p.y+5);
			if (m_dp.LifeArray[i][j] == 1)
			{
				p.x = i * 15.0;
				p.y = j * 15.0;
				pDC->Rectangle(p.x, p.y, p.x + 15, p.y + 15);
			}
			
		}
	}

	//释放画刷
	pDC->SelectObject(oldbrush);
}


void CLifeDlg::SettingPut(CPoint point)
{
	//边界检测：如果超过边界返回
	if (point.x > 600 || point.y > 600) return;

	//坐标
	int coordinateX = -1;
	int coordinateY = -1;

	//距离
	int distanceX, distanceY;

	coordinateX = point.x / 15;
	coordinateY = point.y  / 15;
	
	m_dp.InitSetting(coordinateX, coordinateY, TRUE);
	distanceX = coordinateX * 15;
	distanceY = coordinateX * 15;
	CRect rect(distanceX, distanceY, distanceX + 15, distanceY + 15);
	InvalidateRect(rect, TRUE);
	
}



void CLifeDlg::SettingCancel(CPoint point)
{
	//边界检测：如果超过边界返回
	if (point.x > 600 || point.y > 600) return;

	//坐标
	int coordinateX = -1;
	int coordinateY = -1;

	//距离
	float distanceX, distanceY;

	
	coordinateX = point.x / 15;
	coordinateY = point.y / 15;

	m_dp.InitSetting(coordinateX, coordinateY, FALSE);
	
}


void CLifeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bset) SettingPut(point);

	//Invalidate();
	CRect rect(point.x - 15, point.y - 15, point.x + 15, point.y + 15);
	InvalidateRect(rect, TRUE);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CLifeDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bset) SettingCancel(point);

	//Invalidate();
	CRect rect(point.x - 15, point.y - 15, point.x + 15, point.y + 15);
	InvalidateRect(rect, TRUE);
	CDialogEx::OnRButtonDown(nFlags, point);
}


BOOL CLifeDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//双缓冲技术
	CRect ClientRect;
	GetClientRect(&ClientRect); //获取客户区大小
	//int nWidth = (nImgWidth * m_fExpand> ClientRect.Width()) ? int(nImgWidth*m_fExpand) : ClientRect.Width();
	//此处：宽高取屏幕与滚动条长度的最大值，不然放大缩小时，不能完全刷去上一次的图，
	//会有残余，nImgWidth nImgHeight 图像的宽与高  m_fExpand对图像放大缩小比例，不缩放则为1

	//int nHeight = (nImgHeight * m_fExpand> ClientRect.Height()) ? int(nImgHeight*m_fExpand) : ClientRect.Height();


	//创建兼容DC
	CDC MemDC;
	//建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(pDC);
	CDC* pMDC;
	pMDC = &MemDC;
	CBitmap bmp;//定义一个位图对象 
	//建立一个与屏幕显示兼容的位图
	bmp.CreateCompatibleBitmap(pDC, ClientRect.Width(), ClientRect.Height());
	MemDC.SelectObject(&bmp); //将位图选入到内存显示设备中
							  //先用背景色将位图清除干净，这里我用的是白色作为背景 
	MemDC.FillSolidRect(0, 0, ClientRect.Width(), ClientRect.Height(), RGB(255, 255, 255));






	//网格线
	DrawBoard(pMDC);

	//信息
	DrawInformation(pMDC);

	//画方格
	DrawDiamonds(pMDC);


	pDC->BitBlt(0, 0, 850, 600, &MemDC, 0, 0, SRCCOPY);

	//结束了 画图不要忘记释放资源，DC是有限的
	bmp.DeleteObject();
	MemDC.DeleteDC();

	return TRUE;
	//去掉背景刷新
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CLifeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (tempSpeed != 0)
	{
		tempSpeed--;
	}
	else
	{
		m_dp.Evolution();
		tempSpeed=m_ispeed;
	}


	CRect rect(0, 0, 600, 600);
	InvalidateRect(rect, TRUE);
	//Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}


void CLifeDlg::OnBnClickedButtonSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bset = true;
	m_dp.Reset();
	KillTimer(1);
	Invalidate();
}


void CLifeDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bset = false;
	SetTimer(1, 10, NULL);
}


void CLifeDlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bpause)
	{
		KillTimer(1);
		m_bpause = false;
	}
	else
	{
		SetTimer(1, 10, NULL);
		m_bpause = true;
	}
}


void CLifeDlg::OnBnClickedButtonOver()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}


void CLifeDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_ispeed > 3)m_ispeed -=3;
}


void CLifeDlg::OnBnClickedButtonMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ispeed +=3;
}


void CLifeDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_QUIT, 0, 0);//最常用

	//::SendMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);//最常用
	//::PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);//最常用
	//ExitProcess(0); 注意使用时先释放分配的内存, 以免造成内存泄露

	//exit(0) 正常终止程序; exit(非0）非正常终止程序

	//void CMainFrame::OnClose()
	//{
		// TODO: Add your message handler code here and/or call default
	//	if (MessageBox("确定要退出吗？", "提示", MB_YESNO | MB_DEFBUTTON2) == IDYES)
	//	{
	//		CFrameWnd::OnClose();
	//	}
	//}
}


