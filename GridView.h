#if !defined(AFX_GRIDVIEW_H__EE6FF42D_E451_4C01_AFD9_050FE2B516B8__INCLUDED_)
#define AFX_GRIDVIEW_H__EE6FF42D_E451_4C01_AFD9_050FE2B516B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GridView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGridView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CGridView : public CFormView
{
protected:
	CGridView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGridView)

// Form Data
public:
	//{{AFX_DATA(CGridView)
	enum { IDD = IDD_GRID_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGridView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGridView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEW_H__EE6FF42D_E451_4C01_AFD9_050FE2B516B8__INCLUDED_)
