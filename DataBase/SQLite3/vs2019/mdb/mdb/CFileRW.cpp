#include "pch.h"
#include "CFileRW.h"
#include < atlenc.h >

CFileRW::CFileRW()
{
	
}

CFileRW::~CFileRW()
{

}

void CFileRW::FileWriteCodeTableExport(CString CodeTableExport)
{
	CFile mhtFile;
	try
	{
		//创建mht文件，并写入数据
		mhtFile.Open(_T("export1.txt"), CFile::modeCreate | CFile::modeWrite); 	//mhtFile为CFile类型，filePath为文件路径CString类型
		//-------以下是将Unicode字符转为utf-8字符，这样才能正常显示中文
		DWORD dwFileLen = mhtFile.GetLength();
		if (0 == dwFileLen)
		{
			const unsigned char LeadBytes[] = { 0xEF, 0xBB, 0xBF };
			mhtFile.Write(LeadBytes, sizeof(LeadBytes));
		}
		int nSrcLen = (int)wcslen(CodeTableExport);//content为要写入的文本
		CStringA utf8String(CodeTableExport);
		int nBufLen = (nSrcLen + 1) * 6;
		LPSTR buffer = utf8String.GetBufferSetLength(nBufLen);
		int nLen = AtlUnicodeToUTF8(CodeTableExport, nSrcLen, buffer, nBufLen);
		//上面的函数AtlUnicodeToUTF8()需头文件：<atlenc.h>
		//功能：将unicode转换成utf-8
		buffer[nLen] = 0;
		utf8String.ReleaseBuffer();
		mhtFile.SeekToEnd();
		//将转码后的内容写入mht文件
		mhtFile.Write(utf8String.GetBuffer(), nLen);
		mhtFile.Write("\r\n", 2);
		mhtFile.Close();
	}
	catch (CFileException* e)
	{
		CString errInfo;
		errInfo.Format(_T("%s"), e->ReportError());
		AfxMessageBox(_T("文件创建失败！") + errInfo);
	}
}

void CFileRW::FileReadCodeTableExport()
{
	CString strText = _T("");
	CString szLine = _T("");
	//打开文件
	CStdioFile file;
	file.Open(_T("export1.txt"), CFile::modeRead);
	//逐行读取字符串
	while (file.ReadString(szLine))
	{
		strText += szLine;
	}
	AfxMessageBox(strText);
	//关闭文件
	file.Close();
}