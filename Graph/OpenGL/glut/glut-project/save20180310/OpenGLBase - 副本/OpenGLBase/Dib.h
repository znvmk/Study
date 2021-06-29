#pragma once
#include "afx.h"
class CDib :
	public CObject
{
public:
	CDib();
	virtual~CDib();

protected:
	LPBITMAPFILEHEADER m_pBmFileHeader;
	LPBITMAPINFO m_pBmInfo;
	LPBITMAPINFOHEADER m_pBmInfoHeader;
	RGBQUAD* m_pRGBTable;
	BYTE* m_pDibBits;
	UINT m_numColors;

public:
	BYTE* GetDibBitsPtr();
	LPBITMAPINFO GetDibInfoPtr();
	LPBITMAPINFOHEADER GetDibInfoHeaderPtr();
	UINT GetDibHeight();
	UINT GetDibWidth();
	DWORD GetDibSizeImage();

public:
	/*重载构造函数*/
	CDib(const CString fileName);

protected:
	void LoadBitmapFile(const CString fileName);
};

