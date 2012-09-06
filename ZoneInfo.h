#if !defined(AFX_ZONEINFO_H__819991EC_9D17_4137_8DBD_FA7A81670B5D__INCLUDED_)
#define AFX_ZONEINFO_H__819991EC_9D17_4137_8DBD_FA7A81670B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoneInfo.h : header file
//
#include "GridCtrl.h"
#include "GridEdit.h"
#include "PCSWDoc.h"
#include "AddBox.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CZoneInfo form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CZoneInfo : public CFormView
{
public:
	CZoneInfo();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CZoneInfo)

// Form Data
public:
	int		m_nChannelAddr[21];
 	//{{AFX_DATA(CZoneInfo)
	enum { IDD = IDD_ZONE_FORM };
	CEdit	m_editZonename;
	CAddBox		m_GridComboZone;
	CGridEdit	m_GridEditZone;
	CGridCtrl	m_GridCtrl;
	//}}AFX_DATA

	int	m_nZonechalnum[32];	//记录每个区域包含多少个有效信道数
	int	m_nZonenum;		//总共区域
	int	m_nCurrentZone;	//当前区域
// Attributes
public:
	int		GetFreqScope();
	int		GetChancountsInZone(int nZone,int nFlag);
	int		GetChaninfoInChannel(int nZone,int nCh,int nFlag);
	CString	GetChanFreq(int nFlag,int nZone,int nChannel);
	CString	GetVoiceEncryptCode(int nFlag,int nZone,int nChannel);
	//默认获取信道名称，否则获取区域名称
	CString	GetName(int nZone,int nCh,int nFlag,int nLen,int nStep1 = 736,int nStep2 = 46,bool	bCh = true);
	void	SetCStaticZoneNum();
	void	SetZonename();
	void	SetName(int nZone,int nCh,int nFlag,int nLen,CString&	str,
				int nStep1 = 736,int nStep2 = 46,bool	bCh = true);
	void	SetInfo(int nZone,int nCh,int nFlag,int nVal,int nStep1 = 736,int nStep2 = 46,bool bCh = true);
	void	SetDefaultData();
	void	LoadRowInfo(int nRow,int nMaxCol);
	void	LoadData();
	void	LoadScanlist();
	void	LoadContactlist();
	void	LoadGrplist();
	CString	GetByteInfo(int nTmp,int nAddr);
	CString	GetSpecialInfo(int nAddr,int nChnum,int nZonenum);
	//使能数字/模拟模式信息
	BOOL	EnableDigitOrAnalog(int nRow);
	bool	EnableOtherGrids(int nRow,int nCol);
	void	EnableButtons();
	void	SetReadonlyGrid(int nRow,int nCol,bool bRead);
	//DCS/CTC50初始化
	void	DcsCtcData(int nSelType);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoneInfo)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
inline	CPCSWDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
		return (CPCSWDoc*)m_pDocument;
	}
	virtual ~CZoneInfo();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CZoneInfo)
	afx_msg void OnDestroy();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonPrev();
	afx_msg void OnButtonLast();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonDelete();
	afx_msg void OnKillfocusComboZonelist();
	afx_msg void OnSelchangeComboZonelist();
	//}}AFX_MSG
//	afx_msg LRESULT OnEditGrid(GV_DISPINFO* pInfo, LRESULT* pResult);
	afx_msg void OnEditGrid(NMHDR * pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnKillfocusEditZone();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnEnKillfocusEditZonename();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZONEINFO_H__819991EC_9D17_4137_8DBD_FA7A81670B5D__INCLUDED_)
