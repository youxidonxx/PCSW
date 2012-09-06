#if !defined(AFX_COMSET_H__06A0FDD4_269F_44BB_900B_3758754C2396__INCLUDED_)
#define AFX_COMSET_H__06A0FDD4_269F_44BB_900B_3758754C2396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// COMSET.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCOMSET dialog

class CCOMSET : public CDialog
{
// Construction
public:
	CCOMSET(CWnd* pParent = NULL);   // standard constructor
	void	ScanPort();
 	INT_PTR	GetSerialPort(CStringArray &arrCom); //遍历计算机中有哪些串口
	int	m_nPortNum;
 
// Dialog Data
	//{{AFX_DATA(CCOMSET)
	enum { IDD = IDD_DIALOG_COMSET };
	CComboBox	m_cbPortSel;
	int		m_nComIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCOMSET)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCOMSET)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMSET_H__06A0FDD4_269F_44BB_900B_3758754C2396__INCLUDED_)
