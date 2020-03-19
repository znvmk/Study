// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CntrItem.h : CMFCApplication1CntrItem 类的接口
//

#pragma once

class CMFCApplication1Doc;
class CMFCApplication1View;

class CMFCApplication1CntrItem : public COleDocObjectItem
{
	DECLARE_SERIAL(CMFCApplication1CntrItem)

// 构造函数
public:
	CMFCApplication1CntrItem(CMFCApplication1Doc* pContainer = NULL);
		// 注意: 允许 pContainer 为 NULL 以启用 IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE 要求类具有带零
		//  参数的构造函数。  OLE 项通常是用
		//  非 NULL 文档指针构造的

// 特性
public:
	CMFCApplication1Doc* GetDocument()
		{ return reinterpret_cast<CMFCApplication1Doc*>(COleDocObjectItem::GetDocument()); }
	CMFCApplication1View* GetActiveView()
		{ return reinterpret_cast<CMFCApplication1View*>(COleDocObjectItem::GetActiveView()); }

public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();

protected:
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);
	virtual BOOL CanActivate();

// 实现
public:
	~CMFCApplication1CntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

