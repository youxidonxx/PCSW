// PCSWView.h : interface of the CPCSWView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCSWVIEW_H__70096F54_FFC6_4F47_96D8_C4389B8026B1__INCLUDED_)
#define AFX_PCSWVIEW_H__70096F54_FFC6_4F47_96D8_C4389B8026B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPCSWView : public CFormView
{
public: // create from serialization only
	CPCSWView();
	DECLARE_DYNCREATE(CPCSWView)

public:
	//{{AFX_DATA(CPCSWView)
	enum { IDD = IDD_PCSW_FORM };
	CComboBox	m_cbFreqScope;
	CEdit	m_editDATAVer;
	CEdit	m_editVIVer;
	CEdit	m_editSWVer;
	CEdit	m_editProtype;
	CEdit	m_editSerialNum;
	//}}AFX_DATA

// Attributes
public:
	virtual		void		UpdateWindow();
	CPCSWDoc* GetDocument();
	void		LoadData();
	CString		GetAllVersion(int nFlag,int nLen);
	CString		GetProtypeOrSerial(int nFlag,int nLen);
	int			GetFreqScope(void);
 // Operations
public:
// 	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSWView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPCSWView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPCSWView)
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboFreqRange();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in PCSWView.cpp
inline CPCSWDoc* CPCSWView::GetDocument()
   { return (CPCSWDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCSWVIEW_H__70096F54_FFC6_4F47_96D8_C4389B8026B1__INCLUDED_)
