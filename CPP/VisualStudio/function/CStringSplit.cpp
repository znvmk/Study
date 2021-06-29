//分割
//替换空格为@
void CMFCApplication1Dlg::sdd(CString str)
{
	CStringArray csArr;
	int pos, base;
	pos = 0;
	base = 0;
	int len = str.GetLength();

	//if (la < lb) return false;
	int i = 0;
	while (pos < len)
	{
		pos = str.Find(_T(" "), pos);
		if (pos == -1)
		{
			csArr.Add(csAllUsers.Mid(base, csAllUsers.GetLength() - base));
			break;
		}
		csArr.Add(str.Mid(base, pos - base));
		pos++;
		base = pos;
	}
	CString mix = _T("");
	for (i = 0; i < csArr.GetSize(); i++)
	{
		mix += csArr.GetAt(i);
		mix += _T("@");
	}
	AfxMessageBox(mix);
}

在CString中查找是否完全包含
bool CListCtrlEx2::strIFind(CString a,CString b)
{
	int pos,la,lb;
	pos=0;
	la=a.GetLength();
	lb=b.GetLength();

	if(la<lb) return false;

	while(pos<la)
	{
		pos=a.Find(b,pos);
		//if(pos==-1) return false;
		if (pos == -1)pos = tabledata.GetLength();
		if(b==a.Mid(pos, lb)) return true;
		pos ++;
		
	}
	return false;
}