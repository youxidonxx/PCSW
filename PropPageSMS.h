#if !defined(AFX_PROPPAGESMS_H__F978C628_5893_41A1_8F66_165D4198132F__INCLUDED_)
#define AFX_PROPPAGESMS_H__F978C628_5893_41A1_8F66_165D4198132F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPageSMS.h : header file
//
#include "GridEdit.h"
#include "GridCtrl.h"
#include "PCSWDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPropPageSMS dialog

class CPropPageSMS : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageSMS)

// Construction
public:
	CPropPageSMS();
	~CPropPageSMS();
	void	LoadData();
	void	LoadRowInfo(int nRow,int nCol);
	CString	GetSmsCont(int nGrp,int nLen);
// 	int		GetSmsInfo(int nGrp,int nFlag);
// Dialog Data
	//{{AFX_DATA(CPropPageSMS)
	enum { IDD = IDD_PROPPAGE_SMS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	CGridCtrl	m_gridCtrl;
	CGridEdit	m_gridEdit;
	//}}AFX_DATA
	int			m_nGridCnt;
	byte*		m_pSms;

 // Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageSMS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageSMS)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnGridEdit(NMHDR*	pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonAdd();
public:
	afx_msg void OnBnClickedButtonDel();
public:
	afx_msg void OnEnKillfocusEditSms();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGESMS_H__F978C628_5893_41A1_8F66_165D4198132F__INCLUDED_)
