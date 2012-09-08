#if !defined(AFX_DPMRVIEW_H__E52427AB_9C4B_463B_A8AC_A7DF24ED4BA4__INCLUDED_)
#define AFX_DPMRVIEW_H__E52427AB_9C4B_463B_A8AC_A7DF24ED4BA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DpmrView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDpmrView form view
 #include "PCSWDoc.h"
#include "MyPropSheet.h"
#include "PropPageContact.h"
#include "PropPageSMS.h"
#include "PropPageGrp.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDpmrView : public CFormView
{
public:
	CDpmrView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDpmrView)

// Form Data
public:
	//{{AFX_DATA(CDpmrView)
	enum { IDD = IDD_DPMR_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CMyPropSheet	m_sheet;
	CPropPageSMS	m_pageSms;
	CPropPageContact	m_pageCont;
	CPropPageGrp	m_pageGrp;
// Attributes
public:
	void	LoadData();
	inline	CPCSWDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
		return (CPCSWDoc*)m_pDocument;
	}
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDpmrView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDpmrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDpmrView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPMRVIEW_H__E52427AB_9C4B_463B_A8AC_A7DF24ED4BA4__INCLUDED_)
