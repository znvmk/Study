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
