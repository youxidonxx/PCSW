#if !defined(AFX_PROPPAGEGRP_H__289C6B6B_C167_4813_813D_7C55A8A559B1__INCLUDED_)
#define AFX_PROPPAGEGRP_H__289C6B6B_C167_4813_813D_7C55A8A559B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPageGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageGrp dialog
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
class map_value_finder_string
{
public:
	map_value_finder_string(const std::string &cmp_string):m_s_cmp_string(cmp_string){}
	bool operator ()(const std::map<int, std::string>::value_type &pair)
	{
		if (string(pair.second).compare(m_s_cmp_string)==-1)
		{
			return FALSE;
		}
		else
 			return   TRUE;
		//return pair.second == m_s_cmp_string;
	}
private:
	const std::string &m_s_cmp_string;                    
};


class CPropPageGrp : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPageGrp)

// Construction
public:
	CPropPageGrp();
	~CPropPageGrp();

	map<int , std::string>	mapAllGrp;
	map<int , std::string>	mapUsedGrp;
	map<int , std::string>::iterator	map_it;

public:
	int		GetIDorNum(int nFlag,int nGrp);
	void	LoadData();	
	void	ListDataShow(int nNum,int nMember);
	void	SetStaticName();
// Dialog Data
	//{{AFX_DATA(CPropPageGrp)
	enum { IDD = IDD_PROPPAGE_GROUPLIST };
	CEdit	m_editName;
	CListBox	m_listUsedMember;
	CListBox	m_listAllMember;
	//}}AFX_DATA

	byte*	m_pGrp;
	int		m_nGrp;	//有效组呼列表
	int		m_nCurrentGrp;	//当前所在列表
	int		m_nTotalContact;	//有效联系人总数，来自contact表
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPageGrp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPageGrp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonNext();
public:
	afx_msg void OnBnClickedButtonPrev();
public:
	afx_msg void OnBnClickedButtonFirst();
public:
	afx_msg void OnBnClickedButtonLast();
 public:
	afx_msg void OnBnClickedButtonDeleteGrplist();
public:
	afx_msg void OnBnClickedButtonAddGrplist();
public:
	afx_msg void OnBnClickedButtonAdd();
public:
	afx_msg void OnBnClickedButtonDelete();
public:
	afx_msg void OnEnKillfocusEditName();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEGRP_H__289C6B6B_C167_4813_813D_7C55A8A559B1__INCLUDED_)
