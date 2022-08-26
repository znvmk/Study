#include "stdafx.h"
#include "MFCApplication4.h"
#include "MFCApplication4Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void CMFCApplication4Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString tex, temp, path, str_jumppos;
	int max;
	unsigned long uli_jmp;
	tex = " ";
	temp = " ";

	uli_jmp = 0;


	CFile cfile;
	//m_EditPath.GetWindowTextW(path);
	//m_EditJump.GetWindowTextW(str_jumppos);

	//path.Replace(_T("\\"), _T("\\\\"));
	//m_EditPath.SetWindowTextW(path);
	int flength = 0;
	path = _T("E:\\\\1.jpg");
	CFile write;
	cfile.Open(path, CFile::modeRead | CFile::typeBinary, NULL);
	write.Open(_T("E:\\\\2.jpg"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, NULL);
	//write.Write(_T("askdjf;lajsdfj"), strlen("askdjf;lajsdfj"));
	//write.Close();
	max = 50000;
	short Buf[50000] = { 0 };

	uli_jmp = _ttoi(str_jumppos);
	flength = cfile.GetLength();
	CString a;
	a.Format(_T("%d"), flength);
	AfxMessageBox(a);
	uli_jmp = (unsigned long)uli_jmp;
	//temp.Format(_T("%uld"), uli_jmp);
	//MessageBox(temp);
	///*
	cfile.SeekToBegin();
		for (int j = 0; j < flength; j++)
		{
			if (j < 50000) {
				//cfile.Seek(i_pos, CFile::begin);
				
				cfile.Read((Buf + j), 1);
				//i_pos++;
			}
				

		}
		cfile.Close();
		//write.Write(Buf, flength);
		//write.Close();
		write.SeekToBegin();
		for (int j = 0; j < flength; j++)
		{
			write.Write( Buf+j, 1);
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
		write.Close();

		AfxMessageBox(tex);
		//m_TextShow.SetWindowTextW(tex);
		//EditAddtoText(tex);
		Invalidate();
		//cfile.Seek((flength - 2), CFile::begin);
		//cfile.SeekToEnd();
		//cfile.Read((Buf), 1);
		//temp.Format(_T("%d"), Buf[0]);
		//MessageBox(temp);
		//temp.Format(_T("%uld"), flength);


	
}










#include<iostream>
#pragma warning(disable:4996);
using namespace std;

int main()
{
	//保存输入图像文件名和输出图像文件名
//	char InImgName[10];
//	char OutImgName[10];
	const char* InImgName = "1.bmp";
	const char* OutImgName = "x.bmp";
	//图像数据长度
	int length;
	//文件指针
	FILE* fp;
	//输入要读取的图像名
//	cout << "Enter Image name:";
//	cin >> InImgName;
	//以二进制方式打开图像
	if ((fp = fopen(InImgName, "rb")) == NULL)
	{
		cout << "Open image failed!" << endl;
		exit(0);
	}
	//获取图像数据总长度
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);
	//根据图像数据长度分配内存buffer
	char* ImgBuffer = (char*)malloc(length * sizeof(char));
	//将图像数据读入buffer
	fread(ImgBuffer, length, 1, fp);
	
	for (int i = 0; i < strlen(ImgBuffer); i++)
	{
		cout << *(ImgBuffer + i)<<" ";
	}
	fclose(fp);
	//输入要保存的文件名
//	cout << "Enter the name you wanna to save:";
//	cin >> OutImgName;
	//以二进制写入方式
	if ((fp = fopen(OutImgName, "wb")) == NULL)
	{
		cout << "Open File failed!" << endl;
		exit(0);
	}
	//从buffer中写数据到fp指向的文件中
	fwrite(ImgBuffer, length, 1, fp);
	cout << "Done!" << endl;
	//关闭文件指针，释放buffer内存
	fclose(fp);
	free(ImgBuffer);

	system("pause");
	return 0;
}

CFile mhtFile;
try
{
	//创建mht文件，并写入数据
	mhtFile.Open(FilePath, CFile::modeCreate | CFile::modeWrite); // mhtFile为CFile类型，filePath为文件路径CString类型
	//-------以下是将Unicode字符转为utf-8字符，这样才能正常显示中文
	DWORD dwFileLen = mhtFile.GetLength();
	if (0 == dwFileLen)
	{
		const unsigned char LeadBytes[] = {0xEF, 0xBB, 0xBF};
		mhtFile.Write(LeadBytes, sizeof(LeadBytes));
	}
	int nSrcLen = (int)wcslen(csCodeTableExport); // content为要写入的文本
	CStringA utf8String(csCodeTableExport);
	int nBufLen = (nSrcLen + 1) * 6;
	LPSTR buffer = utf8String.GetBufferSetLength(nBufLen);
	int nLen = AtlUnicodeToUTF8(csCodeTableExport, nSrcLen, buffer, nBufLen);
	//上面的函数AtlUnicodeToUTF8()需头文件：<atlenc.h>
	//功能：将unicode转换成utf-8
	buffer[nLen] = 0;
	utf8String.ReleaseBuffer();
	mhtFile.SeekToEnd();
	//将转码后的内容写入mht文件
	mhtFile.Write(utf8String.GetBuffer(), nLen);
	//	mhtFile.Write("\r\n", 2);
	mhtFile.Close();
}
catch (CFileException *e)
{
	CString errInfo;
	errInfo.Format(_T("%s"), e->ReportError());
	AfxMessageBox(_T("文件创建失败！") + errInfo);
}