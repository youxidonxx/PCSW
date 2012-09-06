/*******************************************************************************
*   File Name: Mybar.h 

*   Description: 

*   Copyright:
      Copyright (c) 2010 LinkTop, Incorporated and its licensors. All Rights 
    Reserved. LinkTop Proprietary. Export of this technology or software is 
    regulated by the P.R.C Government. Diversion contrary to P.R.C law 
    prohibited.

*   Change History:
*   Date                 Author        Release       Description
  2011/04                Qiang jianlong      
*******************************************************************************/

/*******************************************************************************
                                Include Files
*******************************************************************************/
#if !defined(AFX_MYBAR_H__076239B0_BC34_446B_A632_0D3EDE574BD9__INCLUDED_)
#define AFX_MYBAR_H__076239B0_BC34_446B_A632_0D3EDE574BD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mybar.h : header file
//
/*#include "MyTree.h"
#include "PCSWView.h"
#include "MenuSet.h"
#include "RadioSetView.h"
#include "ChildFrm.h"
*/
/////////////////////////////////////////////////////////////////////////////
// mybar window
#include "sizecbar.h"

#define ID_TREECTRL	2001

class mybar : public CSizingControlBar
{
// Construction
public:
	mybar();

// Attributes
public:
	HWND	m_wnd;
	CTreeCtrl m_TreeCtrl;
	HTREEITEM	m_hItem[100];
// Operations
public:
//	CChildFrame*	m_pSWView;
//	CChildFrame*	m_pMenuSetView;
//	CChildFrame*	m_pRadioSetView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(mybar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnUpdateCmdUI(CFrameWnd *pTarget, BOOL bDisableIfNoHndler);
	virtual ~mybar();

	// Generated message map functions
protected:
	//{{AFX_MSG(mybar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBAR_H__076239B0_BC34_446B_A632_0D3EDE574BD9__INCLUDED_)
