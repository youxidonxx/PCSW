#if !defined(AFX_PROPPAGECONTACT_H__34D71A74_9EB0_4F16_B9FD_71C2406275C9__INCLUDED_)
#define AFX_PROPPAGECONTACT_H__34D71A74_9EB0_4F16_B9FD_71C2406275C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPageContact.h : header file
//
#include "GridCtrl.h"
#include "PCSWDoc.h"
#include "GridEdit.h"
#include "AddBox.h"

/////////////////////////////////////////////////////////////////////////////
// CPropPageContact dialog

class CPropPageContact : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageContact)

// Construction
public:
	CPropPageContact();
	~CPropPageContact();

	int		m_Cnt;
	CCellID		m_focusCell;
	byte*	m_pCont;
	void	LoadData();
// 	CString	GetContName(int nGrp,int nLen);
// 	CString	GetContID(int nGrp,int nLen);
	void	LoadRowInfo(int nRow,int nCol);
public:
// Dialog Data
	//{{AFX_DATA(CPropPageContact)
	enum { IDD = IDD_PROPPAGE_CONTACT };
	CAddBox		m_cbContent;
	CGridEdit	m_editContent;
	CGridCtrl	m_gridCtrl;
	//}}AFX_DATA



	virtual	void	GetOriginalRect(CRect *pRect);
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageContact)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageContact)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnGridEdit(NMHDR * pNMHDR, LRESULT * pResult);
		//GV_DISPINFO* pInfo, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonContAdd();
public:
	afx_msg void OnBnClickedButtonContDel();
public:
	afx_msg void OnCbnSelchangeComboType();
public:
	afx_msg void OnEnKillfocusEditContent();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGECONTACT_H__34D71A74_9EB0_4F16_B9FD_71C2406275C9__INCLUDED_)
