#if !defined(AFX_MYPROPSHEET_H__B04594CB_2C5B_4434_A11D_8D9A2A0C8B5E__INCLUDED_)
#define AFX_MYPROPSHEET_H__B04594CB_2C5B_4434_A11D_8D9A2A0C8B5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPropSheet.h : header file
//
#include "PropPageContact.h"
#include "PropPageSMS.h"

/////////////////////////////////////////////////////////////////////////////
// CMyPropSheet

class CMyPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropSheet)
// Construction
public:
	CMyPropSheet();
	CMyPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
 	//短信/联系人数目
	int				m_CntSms;
	int				m_CntCont;

	int				m_nActive;
	byte*			m_pCont;
	byte*			m_pSms;
	byte*			m_pGrpList;
// Operations
public:
	void	LoadData();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPropSheet)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL
	virtual void	AdjustPages();

// Implementation
public:
	virtual ~CMyPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT OnAdjust(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROPSHEET_H__B04594CB_2C5B_4434_A11D_8D9A2A0C8B5E__INCLUDED_)
