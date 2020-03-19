
// GODlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GO.h"
#include "GODlg.h"
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


// CGODlg 对话框



CGODlg::CGODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()

	ON_BN_CLICKED(IDOK, &CGODlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGODlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_BUTTON_GAMESTART, &CGODlg::OnBnClickedGamestart)
	ON_BN_CLICKED(ID_BUTTON_RESIGNS, &CGODlg::OnBnClickedButtonResigns)
	ON_BN_CLICKED(ID_BUTTON_PAUSE, &CGODlg::OnBnClickedButtonPause)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGODlg 消息处理程序

BOOL CGODlg::OnInitDialog()
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

	//设置窗口初始化大小
	SetWindowPos(0, 0, 0, 880, 540, SWP_NOZORDER | SWP_NOMOVE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGODlg::OnPaint()
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
HCURSOR CGODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGODlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CGODlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
BOOL CGODlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CBitmap bmpBoard, bmpChessWhite, bmpChessBlack, bmpChessWhite1, bmpChessBlack1;
	CDC memdc;

	//棋盘木板
	memdc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapBoard = memdc.SelectObject(&bmpBoard);
	bmpBoard.LoadBitmap(IDB_BITMAP_GOBOARD0);
	memdc.SelectObject(&bmpBoard);

	pDC->StretchBlt(0, 0, 500, 500, &memdc, 0, 0, 1000, 1000, SRCCOPY);

	//棋盘线
	DrawGOBoard(pDC);

	//棋盘标注
	DrawGOInformation(pDC);

	//黑子
	CBitmap* pOldBitmapChessBlack = memdc.SelectObject(&bmpChessBlack);
	bmpChessBlack.LoadBitmap(IDB_BITMAP_GOCHESSBLACK);
	memdc.SelectObject(&bmpChessBlack);

	for (int i = 0;i<19;i++)
		for (int j = 0;j < 19;j++)
		{
			if (m_gop.GOMap[i][j] == 1) pDC->StretchBlt(40 + i * 22, 40 + j * 22, 20, 20, &memdc, 0, 0, 150, 150, SRCCOPY);

		}

	//白子
	CBitmap* pOldBitmapChessWhite = memdc.SelectObject(&bmpChessWhite);
	bmpChessWhite.LoadBitmap(IDB_BITMAP_GOCHESSWHITE);
	memdc.SelectObject(&bmpChessWhite);

	for (int i = 0;i<19;i++)
		for (int j = 0;j < 19;j++)
		{
			if (m_gop.GOMap[i][j] == 2) pDC->StretchBlt(40 + i * 22, 40 + j * 22, 20, 20, &memdc, 0, 0, 150, 150, SRCCOPY);

		}

	

	//当前手红三角标注

	//校正后的点:Rectificatory 矫正的
	CPoint RectificatoryPoint;

	RectificatoryPoint.x = 50 + m_gop.coordinateX2 * 22;
	RectificatoryPoint.y = 50 + m_gop.coordinateY2 * 22;

	//RectificatoryPoint.x = 100;
	//RectificatoryPoint.y = 100;


	//红色画刷
	CBrush br(RGB(255, 0, 0));
	//多边形
	CRgn rgn;
	CPoint arrpt[3];
	arrpt[0] = arrpt[1] = arrpt[2] = RectificatoryPoint;
	arrpt[1].y = arrpt[0].y + 10;
	arrpt[2].x = arrpt[0].x + 10;
	if (m_gop.step>0)
	{
		if (rgn.CreatePolygonRgn(arrpt, 3, ALTERNATE) && arrpt[0].x > 0 && arrpt[0].y > 0)
		{
			pDC->FillRgn(&rgn, &br);
			pDC->MoveTo(arrpt[0]);
			pDC->LineTo(arrpt[1]);
			pDC->LineTo(arrpt[2]);
			pDC->LineTo(arrpt[0]);
		}
	}
	br.DeleteObject();
	rgn.DeleteObject();





	//画信息板块黑方
	CBitmap* pOldBitmapChessBlack1 = memdc.SelectObject(&bmpChessBlack1);
	bmpChessBlack1.LoadBitmap(IDB_BITMAP_GOCHESSBLACK1);
	memdc.SelectObject(&bmpChessBlack1);

	pDC->StretchBlt(560, 20, 70, 70, &memdc, 0, 0, 150, 150, SRCCOPY);


	//画信息板块白方
	CBitmap* pOldBitmapChessWhite1 = memdc.SelectObject(&bmpChessWhite1);
	bmpChessWhite1.LoadBitmap(IDB_BITMAP_GOCHESSWHITE1);
	memdc.SelectObject(&bmpChessWhite1);

	pDC->StretchBlt(750, 20, 70, 70, &memdc, 0, 0, 150, 150, SRCCOPY);


	memdc.SelectObject(pOldBitmapChessBlack);
	memdc.SelectObject(pOldBitmapChessWhite);
	memdc.SelectObject(pOldBitmapChessBlack1);
	memdc.SelectObject(pOldBitmapChessWhite1);
	bmpChessWhite.DeleteObject();
	bmpChessBlack.DeleteObject();
	bmpChessWhite1.DeleteObject();
	bmpChessBlack1.DeleteObject();

	memdc.SelectObject(pOldBitmapBoard);
	bmpBoard.DeleteObject();
	return true;

	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CGODlg::DrawGOBoard(CDC* pDC)
{

	//画棋盘

	//定义画笔
	CRect rect;
	GetClientRect(&rect);
	//生成画笔
	CPen PenBlackLine1(PS_SOLID, 2, RGB(0, 0, 0));
	CPen *poldpenline1;
	poldpenline1 = pDC->SelectObject(&PenBlackLine1);

	pDC->MoveTo(50, 50);
	pDC->LineTo(446, 50);
	pDC->LineTo(446, 446);
	pDC->LineTo(50, 446);
	pDC->LineTo(50, 50);



	//释放画笔
	pDC->SelectObject(poldpenline1);

	// 生成画笔
	CPen PenBlackLine2(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *poldpenline2;
	poldpenline2 = pDC->SelectObject(&PenBlackLine2);

	for (int i = 0;i<17;i++)
	{
		pDC->MoveTo(50, i * 22 + 72);
		pDC->LineTo(50 + 18 * 22, i * 22 + 72);
		pDC->MoveTo(i * 22 + 72, 50);
		pDC->LineTo(i * 22 + 72, 50 + 18 * 22);

	}
	//释放画笔
	pDC->SelectObject(poldpenline2);

	//画棋盘坐标信息

	CBrush fillbrush;
	CBrush *oldbrush;
	fillbrush.CreateSolidBrush(RGB(0, 0, 0));
	oldbrush = pDC->SelectObject(&fillbrush);
	int r = 4;
	for (int i = 0;i <= 2;i++)
	{
		for (int j = 0;j <= 2;j++)
		{
			pDC->Ellipse(50 + 22 * 3 + i * 6 * 22 - r, 50 + 22 * 3 + j * 6 * 22 - r, 50 + 22 * 3 + i * 6 * 22 + r, 50 + 22 * 3 + j * 6 * 22 + r);
		}
	}

	//释放画刷
	pDC->SelectObject(oldbrush);



	//标注

	//获得某一点的颜色的RGB
	COLORREF clr;
	int R, G, B;

	clr = ::GetPixel(pDC->m_hDC, 24, 42);
	R = GetRValue(clr);
	G = GetGValue(clr);
	B = GetBValue(clr);

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

	pDC->SelectObject(&font);
	//pDC->SetTextColor(RGB(0, 0, 0));


	//int originx = 46;
	//int originy = 32;

	int originx = 46;
	int originy = 24;

	//横向
	int add = 0;

	CRect crossrange0(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange0, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("1"));

	add = 1;
	CRect crossrange1(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange1, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("2"));

	add = 2;
	CRect crossrange2(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange2, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("3"));

	add = 3;
	CRect crossrange3(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange3, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("4"));

	add = 4;
	CRect crossrange4(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange4, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("5"));

	add = 5;
	CRect crossrange5(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange5, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("6"));

	add = 6;
	CRect crossrange6(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange6, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("7"));

	add = 7;
	CRect crossrange7(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange7, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("8"));

	add = 8;
	CRect crossrange8(originx + 22 * add, originy, originx + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange8, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx + 22 * add, originy, _T("9"));


	//原点2
	int origin1x = 42;

	add = 9;
	CRect crossrange9(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange9, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("10"));


	add = 10;
	CRect crossrange10(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange10, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("11"));


	add = 11;
	CRect crossrange11(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange11, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("12"));

	add = 12;
	CRect crossrange12(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange12, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("13"));

	add = 13;
	CRect crossrange13(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange13, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("14"));

	add = 14;
	CRect crossrange14(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange14, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("15"));

	add = 15;
	CRect crossrange15(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 58);
	pDC->FillSolidRect(&crossrange15, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("16"));

	add = 16;
	CRect crossrange16(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange16, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("17"));

	add = 17;
	CRect crossrange17(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange17, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("18"));

	add = 18;
	CRect crossrange18(origin1x + 22 * add, originy, origin1x + 22 * add, originy + 5);
	pDC->FillSolidRect(&crossrange18, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin1x + 22 * add, originy, _T("19"));

	//释放字体
	pDC->SelectObject(poldfont);



	//纵向
	CFont font1;
	CFont *poldfont1;
	poldfont1 = pDC->SelectObject(&font1);
	font1.CreateFont(
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

	pDC->SelectObject(&font1);



	//originx = 24;
	originx = 16;
	originy = 42;
	add = 0;
	CRect lengthways0(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways0, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("一"));

	add = 1;
	CRect lengthways1(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways1, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("二"));

	add = 2;
	CRect lengthways2(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways2, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("三"));

	add = 3;
	CRect lengthways3(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways3, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("四"));

	add = 4;
	CRect lengthways4(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways4, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("五"));

	add = 5;
	CRect lengthways5(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways5, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("六"));

	add = 6;
	CRect lengthways6(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways6, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("七"));

	add = 7;
	CRect lengthways7(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways7, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("八"));

	add = 8;
	CRect lengthways8(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways8, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("九"));

	add = 9;
	CRect lengthways9(originx, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways9, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(originx, originy + 22 * add, _T("十"));


	//原点2
	//int  origin2x = 15;
	int  origin2x = 7;

	add = 10;
	CRect lengthways10(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways10, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十一"));


	add = 11;
	CRect lengthways11(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways11, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十二"));

	add = 12;
	CRect lengthways12(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways12, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十三"));

	add = 13;
	CRect lengthways13(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways13, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十四"));

	add = 14;
	CRect lengthways14(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways14, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十五"));

	add = 15;
	CRect lengthways15(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways15, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十六"));

	add = 16;
	CRect lengthways16(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways16, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十七"));

	add = 17;
	CRect lengthways17(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways17, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十八"));

	add = 18;
	CRect lengthways18(origin2x, originy + 22 * add, 30, 58 + 22 * add);
	pDC->FillSolidRect(&lengthways18, RGB(R, G, B));//背景颜色填充
	pDC->TextOutW(origin2x, originy + 22 * add, _T("十九"));

	//释放画笔
	//pDC->SelectObject(poldpentext);
	//释放字体
	pDC->SelectObject(poldfont1);

}


void CGODlg::DrawGOInformation(CDC* pDC)
{
	

	//设置背景
	CRect rect(500, 0, 880, 500);

	pDC->FillSolidRect(rect, RGB(128, 128, 128));//背景颜色填充

												 //定义画笔


												 //生成画笔
	CPen PenBlackLine1(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *poldpenline1;
	poldpenline1 = pDC->SelectObject(&PenBlackLine1);

	pDC->MoveTo(500, 170);
	pDC->LineTo(880, 170);

	pDC->MoveTo(500, 210);
	pDC->LineTo(880, 210);

	pDC->MoveTo(500, 250);
	pDC->LineTo(880, 250);

	pDC->MoveTo(520, 290);
	pDC->LineTo(850, 290);

	pDC->MoveTo(520, 390);
	pDC->LineTo(850, 390);

	pDC->MoveTo(500, 400);
	pDC->LineTo(880, 400);
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
	CString blacktaking,whitetaking,step,blacktime, whitetime, steptime,informationtemp,currentplayer;
	blacktaking.Format(_T("%d"), m_gop.BlackTaking);
	whitetaking.Format(_T("%d"), m_gop.WhiteTaking);
	step.Format(_T("%d"), m_gop.step);
	blacktime = m_gop.TimeConvert(m_gop.BlackTime);
	whitetime = m_gop.TimeConvert(m_gop.WhiteTime);
	steptime = m_gop.TimeConvert(m_gop.stepTime);

	informationtemp = "提子：";
	blacktaking = informationtemp + blacktaking;
	whitetaking = informationtemp + whitetaking;

	informationtemp = "用时：";
	blacktime = informationtemp + blacktime;
	whitetime = informationtemp + whitetime;

	informationtemp = "单步用时：";
	steptime = informationtemp + steptime;

	informationtemp = "当前手数：";
	step = informationtemp + step;


	informationtemp = "";
	informationtemp = "";
	informationtemp = "";
	informationtemp = "";
	informationtemp = "";
	informationtemp = "";
	informationtemp = "";
	informationtemp = "";
	//信息显示
	pDC->SelectObject(&font);

	pDC->TextOutW(520, 100, _T("黑方：玩家"));
	pDC->TextOutW(720, 100, _T("白方：电脑"));
	pDC->TextOutW(520, 120, blacktaking);
	pDC->TextOutW(720, 120, whitetaking);
	pDC->TextOutW(520, 140, blacktime);
	pDC->TextOutW(720, 140, whitetime);

	pDC->TextOutW(520, 180, _T("当前：黑方走"));

	pDC->TextOutW(520, 220, steptime);
	pDC->TextOutW(720, 220, step);

	pDC->TextOutW(650, 260, _T("对局信息"));

	pDC->TextOutW(520, 300, _T("比赛时间:2018-1-1"));
	pDC->TextOutW(520, 320, _T("玩家级别：1d"));
	pDC->TextOutW(520, 340, _T("电脑级别：1d"));
	pDC->TextOutW(520, 360, _T("棋盘大小：19x19"));

	pDC->TextOutW(720, 300, _T("让子数：0"));
	pDC->TextOutW(720, 320, _T("贴目：7目半"));
	pDC->TextOutW(720, 340, _T("比赛状态：正在进行"));

	//释放字体
	pDC->SelectObject(poldfont);
}


void CGODlg::DropChessPieces(CPoint point)
{
	//坐标
	int coordinateX = -1;
	int coordinateY = -1;

	//距离
	int distanceX, distanceY;

	//校正后的点:Rectificatory 矫正的
	CPoint RectificatoryPoint;
	//矫正后的矩形
	CRect RectificatoryRect;

	distanceX = (point.x - 50) % 22;
	if (distanceX <= 10)
		coordinateX = (point.x - 50) / 22;
	if (distanceX >= 12)
		coordinateX = (point.x - 50) / 22 + 1;

	distanceY = (point.y - 50) % 22;
	if (distanceY <= 10)
		coordinateY = (point.y - 50) / 22;
	if (distanceY >= 12)
		coordinateY = (point.y - 50) / 22 + 1;
	if (m_gop.flag == 1)
	{
		if (coordinateX >= 0 && coordinateX <19 && coordinateY >= 0 && coordinateY <19)
		{
			if (m_gop.GOMap[coordinateX][coordinateY] == 0)
			{
				m_gop.GOMap[coordinateX][coordinateY] = 1;
				m_gop.flag = 2;
				m_gop.stepTime = 0;
				m_gop.step++;

				//上一手棋子位置坐标
				m_gop.coordinateX1 = m_gop.coordinateX2;
				m_gop.coordinateY1 = m_gop.coordinateY2;

				//当前手的位置
				m_gop.coordinateX2 = coordinateX;
				m_gop.coordinateY2 = coordinateY;

				//刷新上一手落下棋子所在矩形
				RectificatoryPoint.x = 50 + m_gop.coordinateX1 * 22;
				RectificatoryPoint.y = 50 + m_gop.coordinateY1 * 22;

				RectificatoryRect.top = RectificatoryPoint.y - 10;
				RectificatoryRect.bottom = RectificatoryPoint.y + 10;
				RectificatoryRect.left = RectificatoryPoint.x - 10;
				RectificatoryRect.right = RectificatoryPoint.x + 10;

				InvalidateRect(RectificatoryRect);

				//刷新当前落下棋子所在矩形
				RectificatoryPoint.x = 50 + m_gop.coordinateX2 * 22;
				RectificatoryPoint.y = 50 + m_gop.coordinateY2 * 22;

				RectificatoryRect.top = RectificatoryPoint.y - 10;
				RectificatoryRect.bottom = RectificatoryPoint.y + 10;
				RectificatoryRect.left = RectificatoryPoint.x - 10;
				RectificatoryRect.right = RectificatoryPoint.x + 10;

				InvalidateRect(RectificatoryRect);

			}
		}

	}
	else
		if (m_gop.flag == 2)
		{
			if (coordinateX >= 0 && coordinateX < 19 && coordinateY >= 0 && coordinateY < 19)
			{
				if (m_gop.GOMap[coordinateX][coordinateY] == 0)
				{
					m_gop.GOMap[coordinateX][coordinateY] = 2;
					m_gop.flag = 1;
					m_gop.stepTime = 0;
					m_gop.step++;

					//上一手棋子位置坐标
					m_gop.coordinateX1 = m_gop.coordinateX2;
					m_gop.coordinateY1 = m_gop.coordinateY2;

					//当前手的位置
					m_gop.coordinateX2 = coordinateX;
					m_gop.coordinateY2 = coordinateY;

					//刷新上一手落下棋子所在矩形
					RectificatoryPoint.x = 50 + m_gop.coordinateX1 * 22;
					RectificatoryPoint.y = 50 + m_gop.coordinateY1 * 22;

					RectificatoryRect.top = RectificatoryPoint.y - 10;
					RectificatoryRect.bottom = RectificatoryPoint.y + 10;
					RectificatoryRect.left = RectificatoryPoint.x - 10;
					RectificatoryRect.right = RectificatoryPoint.x + 10;

					InvalidateRect(RectificatoryRect);

					//刷新当前落下棋子所在矩形
					RectificatoryPoint.x = 50 + m_gop.coordinateX2 * 22;
					RectificatoryPoint.y = 50 + m_gop.coordinateY2 * 22;

					RectificatoryRect.top = RectificatoryPoint.y - 10;
					RectificatoryRect.bottom = RectificatoryPoint.y + 10;
					RectificatoryRect.left = RectificatoryPoint.x - 10;
					RectificatoryRect.right = RectificatoryPoint.x + 10;

					InvalidateRect(RectificatoryRect);

				}
			}

		}

}

void CGODlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int flagchange = m_gop.flag;
	if (m_gop.flag == 1 | m_gop.flag == 2)
	{
		if (point.x >= 40 && point.x <= 478 && point.y >= 40 && point.y <= 478)
			DropChessPieces(point);

	}
	
	//刷新步数，时间等信息
	CRect rect(520, 120, 880, 260);
	InvalidateRect(rect);
	
	CDialogEx::OnLButtonDown(nFlags, point);
}



void CGODlg::OnBnClickedGamestart()
{
	// TODO: 在此添加控件通知处理程序代码

	m_gop.GameStart();
	SetTimer(1, 1000, NULL);
	Invalidate();
}


void CGODlg::OnBnClickedButtonResigns()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gop.flag = 3;
	KillTimer(1);
}

void CGODlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}


void CGODlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent)
	{
		if (m_gop.flag == 1) m_gop.BlackTime++;
		if (m_gop.flag == 2) m_gop.WhiteTime++;
		m_gop.stepTime++;
	}
	
	//刷新步数，时间等信息
	CRect rect(520, 120, 880, 260);
	InvalidateRect(rect);
	//Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}
