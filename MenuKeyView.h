#if !defined(AFX_MENUKEYVIEW_H__1271DE17_6C5C_4A36_AD66_15AF6B066CE9__INCLUDED_)
#define AFX_MENUKEYVIEW_H__1271DE17_6C5C_4A36_AD66_15AF6B066CE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuKeyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuKeyView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "PCSWDoc.h"
#include "ReportCtrl.h"
#include "AddBox.h"
#include "GridCtrl.h"
#include "afxwin.h"

class CMenuKeyView : public CFormView
{
protected:
	CMenuKeyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMenuKeyView)

// Form Data
public:
	//{{AFX_DATA(CMenuKeyView)
	enum { IDD = IDD_MENUKEY_FORM };
// 	CAddBox	m_GridComboZone;
// 	CGridCtrl	m_GridCtrl;
	CReportCtrl	m_listMenu;

	//}}AFX_DATA

// Attributes
public:

	void	LoadData();
	void	LoadMenuItem();
	void	LoadKeyFunc();
	void	SetKeyFunc(int nFlag,int nVal);
	void	SetMenuVal(int nFlag,int nVal);
	void	SetMenuKillUnkill(int nVal,bool	bKill = true);
	BOOL	bAllCheck();
	int		GetCheckValues(int nFlag);
	int		GetKillUnkill(int nFlag);
	int		GetKeyFuncValues(int nFlag);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuKeyView)
	public:
	virtual void OnInitialUpdate();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	SetStaticName();
	inline	CPCSWDoc*	GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
			return (CPCSWDoc*)m_pDocument;
	}
	virtual ~CMenuKeyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMenuKeyView)
	afx_msg void OnSelchangeComboKeyfunc(UINT	nID);
	//}}AFX_MSG
		afx_msg void OnEditGrid(GV_DISPINFO* pInfo, LRESULT* pResult);
		afx_msg		void	OnCheckBox(NMHDR * pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CButton m_CheckAll;
public:
	afx_msg void OnBnClickedCheckAll();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUKEYVIEW_H__1271DE17_6C5C_4A36_AD66_15AF6B066CE9__INCLUDED_)
