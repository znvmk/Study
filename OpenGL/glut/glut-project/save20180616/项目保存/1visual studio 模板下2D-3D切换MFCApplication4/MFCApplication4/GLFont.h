#pragma once
#include "stdafx.h"


class CGLFont  
{
public:
	void entext(float x,float y, LPCTSTR str,HFONT hFont,float r,float g,float b);
	void c3dtext(LPCTSTR str,HFONT hFont,float z);
	void Printfc3d(CString strText,HFONT hFont,float z=0.05f);
	void Printftext(int x, int y, LPCTSTR lpszText,HFONT hFont);
	void settext(float x,float y,CString str,HFONT Font,float r,float g,float b);
	CGLFont();
	virtual ~CGLFont();
protected:
	HFONT hFont; //×ÖÌå¾ä±ú
};

