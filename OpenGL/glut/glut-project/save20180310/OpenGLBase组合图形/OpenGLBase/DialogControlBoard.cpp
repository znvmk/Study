// DialogControl.cpp : 实现文件
//

#include "stdafx.h"
#include "OpenGLBase.h"
#include "DialogControlBoard.h"
#include "afxdialogex.h"


// CDialogControl 对话框

IMPLEMENT_DYNAMIC(CDialogControlBoard, CDialogEx)

CDialogControlBoard::CDialogControlBoard(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CONTROL, pParent)
{
	m_nNumber = 0;
	m_sNubmer = "";
	m_bShow = false;
}

CDialogControlBoard::~CDialogControlBoard()
{

}

void CDialogControlBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EditNumber);
	DDX_Control(pDX, IDC_STATIC1, m_StaticDrawMessage);
}


BEGIN_MESSAGE_MAP(CDialogControlBoard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogControlBoard::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CDialogControlBoard::OnBnClickedMinus)
	ON_BN_CLICKED(IDOK, &CDialogControlBoard::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogControlBoard::OnBnClickedCancel)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CDialogControl 消息处理程序


void CDialogControlBoard::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nNumber++;
	m_sNubmer.Format(_T("%d"), m_nNumber);
	m_EditNumber.SetWindowTextW(m_sNubmer);

	ShowDrawMessage();
	//UpdateData(FALSE);
	
}


void CDialogControlBoard::OnBnClickedMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nNumber > 0)
	{
		m_nNumber--;
		m_sNubmer.Format(_T("%d"), m_nNumber);
		m_EditNumber.SetWindowTextW(m_sNubmer);

		ShowDrawMessage();
		
	}
	
}


void CDialogControlBoard::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditNumber.GetWindowTextW(m_sNubmer);
	int NumberTemp;
	NumberTemp =_ttoi(m_sNubmer);

	if (NumberTemp <=0)
	{
		m_nNumber=0;
		m_sNubmer.Format(_T("%d"), m_nNumber);
		m_EditNumber.SetWindowTextW(m_sNubmer);

		ShowDrawMessage();
		
	}
	else
	{
		m_nNumber = NumberTemp;
		m_sNubmer.Format(_T("%d"), m_nNumber);
		m_EditNumber.SetWindowTextW(m_sNubmer);

		ShowDrawMessage();
	}
	
	//CDialogEx::OnOK();
}


void CDialogControlBoard::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bShow = false;
	//CDialogEx::OnCancel();
}


void CDialogControlBoard::ShowDrawMessage()
{
	CString SDrawMessage;
	switch (m_nNumber)
	{
	case 0:SDrawMessage = "清空界面";break;
	case 1:SDrawMessage = "点";break;
	case 2:SDrawMessage = "线";break;
	case 3:SDrawMessage = "三角形";break;
	case 4:SDrawMessage = "三角形片";break;
	case 5:SDrawMessage = "三角形扇";break;
	case 6:SDrawMessage = "四边形";break;
	case 7:SDrawMessage = "四边形片";break;
	case 8:SDrawMessage = "凹多边形，边的可见性";break;
	case 9:SDrawMessage = "立方体";break;
	case 10:SDrawMessage = "立方体(带参数)";break;
	case 11:SDrawMessage = "平移变换";break;
	case 12:SDrawMessage = "旋转变换";break;
	case 13:SDrawMessage = "缩放变换";break;
	case 14:SDrawMessage = "剪切变换";break;
	case 15:SDrawMessage = "集成";break;
	case 16:SDrawMessage = "绘制卡车平面模型";break;
	case 17:SDrawMessage = "显示列表，管理显示列表，圆环";break;
	case 18:SDrawMessage = "画一个球";break;
	case 19:SDrawMessage = "平滑盒子";break;
	case 20:SDrawMessage = "读取图像";break;
	case 21:SDrawMessage = "纹理贴图";break;
	case 22:SDrawMessage = "Mip贴图";break;
	case 23:SDrawMessage = "融合四边形";break;
	case 24:SDrawMessage = "透明玻璃";break;
	case 25:SDrawMessage = "绘制二次曲面";break;
	case 26:SDrawMessage = "Mip自动贴图";break;
	case 27:SDrawMessage = "Berzier曲线,绘制一条拟正弦曲线";break;
	case 28:SDrawMessage = "NURBS曲线,绘制一条NURBS曲线";break;
	case 29:SDrawMessage = "Bezier曲面,绘制网格曲面";break;
	case 30:SDrawMessage = "Bezier曲面,绘制网格曲面填充";break;
	case 31:SDrawMessage = "Nurbs曲面,绘制网格曲面";break;
	case 32:SDrawMessage = "高级制作技术，掩膜";break;
	case 33:SDrawMessage = "高级制作技术，高级剪切";break;
	case 34:SDrawMessage = "交互技术,拾取物体";break;
	case 35:SDrawMessage = "";break;
	case 36:SDrawMessage = "";break;
	case 37:SDrawMessage = "";break;
	case 38:SDrawMessage = "";break;
	case 39:SDrawMessage = "";break;
	case 40:SDrawMessage = "";break;
	case 41:SDrawMessage = "";break;
	case 42:SDrawMessage = "";break;
	case 43:SDrawMessage = "";break;
	default:break;
	}

	//m_StaticDrawMessage.SetWindowTextW(SDrawMessage);
	m_StaticDrawMessage.SetWindowTextW(SDrawMessage);
	
}

void CDialogControlBoard::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nChar)
	{
	case VK_DOWN: OnBnClickedAdd();break;
	case VK_UP:if (m_nNumber > 0)OnBnClickedMinus();;break;
	}
	UpdateData();


	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
