#if !defined(AFX_MYTREE1_H__AC66097A_D496_4544_99A0_D9D262B42963__INCLUDED_)
#define AFX_MYTREE1_H__AC66097A_D496_4544_99A0_D9D262B42963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTree1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTree view

class CMyTree : public CTreeView
{
protected:
	CMyTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyTree)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTree)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTree)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREE1_H__AC66097A_D496_4544_99A0_D9D262B42963__INCLUDED_)
