#include "stdafx.h"
#include "Dib.h"
#include"windowsX.h"

CDib::CDib()
{
	m_pBmFileHeader = NULL;
	m_pBmInfo = NULL;
	m_pBmInfoHeader = NULL;
	m_pRGBTable = 0;
	m_numColors = 0;
}

CDib::CDib(const CString fileName)
{
	/*装载位图*/
	LoadBitmapFile(fileName);
}

CDib::~CDib()
{
	GlobalFreePtr(m_pBmInfo);
}


BYTE* CDib::GetDibBitsPtr()
{
	return m_pDibBits;
}


LPBITMAPINFO CDib::GetDibInfoPtr()
{
	return m_pBmInfo;
}


LPBITMAPINFOHEADER CDib::GetDibInfoHeaderPtr()
{
	return m_pBmInfoHeader;
}


UINT CDib::GetDibHeight()
{
	return (UINT)m_pBmInfoHeader->biWidth;
}


UINT CDib::GetDibWidth()
{
	return  (UINT)m_pBmInfoHeader->biWidth;
}


DWORD CDib::GetDibSizeImage()
{
	if (m_pBmInfoHeader->biSizeImage == 0)
	{
		/*单行字节数，即宽度*/
		DWORD byteWidth =(DWORD)GetDibWidth();

		/*高度*/
		DWORD height = (DWORD)GetDibHeight();
		DWORD imageSize = byteWidth*height;
		return imageSize;
	}
	else return m_pBmInfoHeader->biSizeImage;
}






void CDib::LoadBitmapFile(const CString fileName)
{
	/*打开位图文件*/
	CFile file(fileName, CFile::modeRead);

	/*将位图头文件读入内存*/
	BITMAPFILEHEADER bmFileHeader;
	file.Read((void*)&bmFileHeader, sizeof(bmFileHeader));

	/*检查是否为位图*/
	if (bmFileHeader.bfType != 0x4d42)
	{
		AfxMessageBox(_T("Not a bitmap file!"));
		m_pBmFileHeader = 0;
		m_pBmInfo = 0;
		m_pBmInfoHeader = 0;
		m_pRGBTable = 0;
		m_pDibBits = 0;
		m_numColors = 0;
	}
	else
	{
		DWORD fileLength = file.GetLength();
		DWORD dibSize = fileLength - sizeof(bmFileHeader);

		/*分配全局内存*/
		BYTE* pDib = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, dibSize);

		pDib = new BYTE(dibSize);
		file.Read(pDib, dibSize);
		file.Close();

		/*初始化指向结构BITMAPINFO和BITMAPINFOHEADER的指针*/
		m_pBmInfo = (LPBITMAPINFO)pDib;
		m_pBmInfoHeader = (LPBITMAPINFOHEADER)pDib;

		/*获得位图大小*/
		m_pBmInfoHeader->biSizeImage = GetDibSizeImage();
		m_pDibBits = pDib + m_pBmInfoHeader->biSize;

	}
}