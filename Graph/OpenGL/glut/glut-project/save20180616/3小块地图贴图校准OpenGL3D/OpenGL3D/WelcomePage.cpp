#include "stdafx.h"
#include "WelcomePage.h"


CWelcomePage::CWelcomePage()
{
	m_bmpWelcomePage.LoadBitmapW(IDB_BITMAP_WELCOMEPAGE);
}


CWelcomePage::~CWelcomePage()
{
}


void CWelcomePage::DrawWelcomePage(CDC* pDC)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(NULL);
	CDC* pMDC;
	pMDC = &MemDC;




	DrawPicture(pMDC);

	DrawMyText(pMDC);



	// 完成绘制
	//pDC->BitBlt(0 , 0 , 1024 , 628 , &MemDC , 0 , 0 , SRCCOPY);
	//BOOL StretchBlt(int x , int y , int nWidth , int nHeight , CDC* pSrcDC , int xSrc , int ySrc , int nSrcWidth , int nSrcHeight , DWORD dwRop);
	pDC->StretchBlt(0 , 0 , 1024 , 700 , &MemDC , 0 , 0 , 1024 , 628 , SRCCOPY);
}


void CWelcomePage::DrawPicture(CDC* pDC)
{
	pDC->SelectObject(m_bmpWelcomePage);
	
}



void CWelcomePage::DrawMyText(CDC* pDC)
{
	int nOldDC = pDC->SaveDC();
	//定义画笔
	CPen PenBlue(PS_SOLID , 1 , RGB(255 , 0 , 0));
	CPen *poldpen;
	poldpen = pDC->SelectObject(&PenBlue);

	pDC->SetROP2(R2_NOTXORPEN);

	//获得某一点的颜色的RGB
	COLORREF clr;
	int R , G , B;

	clr = ::GetPixel(pDC->m_hDC , 24 , 42);
	R = GetRValue(clr);
	G = GetGValue(clr);
	B = GetBValue(clr);
	//pDC->FillSolidRect(&crossrange0 , RGB(R , G , B));//背景颜色填充

	//设置字体
	CFont font;
	CFont *poldfont;
	poldfont = pDC->SelectObject(&font);
	font.CreateFont(
		30 ,                                                  //   nHeight  
		25 ,                                                   //   nWidth  
		0 ,                                                   //   nEscapement
		0 ,                                                   //   nOrientation  
		20 ,                                   //   nWeight  
		TRUE ,                                           //   bItalic  
		FALSE ,                                           //   bUnderline  
		0 ,                                                   //   cStrikeOut  
		ANSI_CHARSET ,                             //   nCharSet  
		OUT_DEFAULT_PRECIS ,                 //   nOutPrecision  
		CLIP_DEFAULT_PRECIS ,               //   nClipPrecision  
		DEFAULT_QUALITY ,                       //   nQuality  
		DEFAULT_PITCH | FF_SWISS ,     //   nPitchAndFamily     
		_T("楷体"));

	pDC->SelectObject(&font);
	
	//设置文字颜色，文字背景为透明 
	SetTextColor(*pDC , RGB(255 , 170 , 0));
	SetBkMode(*pDC , TRANSPARENT);

	pDC->TextOutW(300,100, _T("三维城市管网系统"));

	//释放字体
	pDC->SelectObject(poldfont);


	
	CFont font1;
	CFont *poldfont1;
	poldfont1 = pDC->SelectObject(&font1);
	font1.CreateFont(
		16 ,                                                  //   nHeight  
		8 ,                                                   //   nWidth  
		0 ,                                                   //   nEscapement
		0 ,                                                   //   nOrientation  
		20 ,                                   //   nWeight  
		FALSE ,                                           //   bItalic  
		FALSE ,                                           //   bUnderline  
		0 ,                                                   //   cStrikeOut  
		ANSI_CHARSET ,                             //   nCharSet  
		OUT_DEFAULT_PRECIS ,                 //   nOutPrecision  
		CLIP_DEFAULT_PRECIS ,               //   nClipPrecision  
		DEFAULT_QUALITY ,                       //   nQuality  
		DEFAULT_PITCH | FF_SWISS ,     //   nPitchAndFamily     
		_T("楷体"));

	pDC->SelectObject(&font1);

	

	//输出文字
	
	pDC->TextOutW(750 , 480 , _T("制作人：张玉年"));
	
	pDC->TextOutW(750 , 500 , _T("学号：1403070217"));
	
	pDC->TextOutW(780 , 520 , _T("2017.5.4"));

	//释放字体
	pDC->SelectObject(poldfont1);
}