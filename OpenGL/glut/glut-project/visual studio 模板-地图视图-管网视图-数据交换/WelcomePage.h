#pragma once

#include"resource.h"


class CWelcomePage
{
public:
	CWelcomePage();
	~CWelcomePage();


public:
	CBitmap m_bmpWelcomePage;

	/*绘制欢迎页面*/
public:
	void DrawWelcomePage(CDC* pDC , CRect rect);
	void DrawPicture(CDC* pDC);
	void DrawMyText(CDC* pDC);
};
