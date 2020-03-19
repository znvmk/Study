void CDb001Dlg::OnButtonCratedb() 
{
	// TODO: Add your control notification handler code here
	TCHAR szPathName[MAX_PATH];
	GetModuleFileName(NULL,szPathName,MAX_PATH);
	CString strPathName=szPathName;

	int nPos;
	nPos=strPathName.ReverseFind(_T('\\'));
	strPathName =strPathName.Left(nPos);
	strPathName +=_T("\\student.mdb");

	CFileFind ff;
	if(!ff.FindFile(strPathName))
	{
		m_db.Create(strPathName);
		CString strSql=_T("CREATE TABLE StudentInfo(student_id varchar(20) NOT NULL,\
			student_name varchar(20) NOT NULL,score int)");
		m_db.Execute(strSql);
        
	}
}