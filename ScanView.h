#if !defined(AFX_SCANVIEW_H__C225886B_5158_4F56_AFA1_D8FE22BDF0D3__INCLUDED_)
#define AFX_SCANVIEW_H__C225886B_5158_4F56_AFA1_D8FE22BDF0D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanView.h : header file
//
#include "PCSWDoc.h"
 
/////////////////////////////////////////////////////////////////////////////
// CScanView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
class map_value_finder
{
public:
	map_value_finder(const DWORD &cmp_info):m_s_cmp_info(cmp_info){}
	bool operator ()(const map<int,DWORD>::value_type &pair)
	{
		return pair.second == m_s_cmp_info;
	}
// 	map_value_finder(const std::string &cmp_info):m_s_cmp_string(cmp_info){}
// 	bool operator ()(const map<int,std::string>::value_type &pair)
// 	{
// 		return pair.second == m_s_cmp_string;
// 	}

private:
	const DWORD &m_s_cmp_info; 
// 	const	std::string	&m_s_cmp_string;
};


class CScanView : public CFormView
{
public:
	CScanView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScanView)

// Form Data
public:
	//{{AFX_DATA(CScanView)
	enum { IDD = IDD_SCAN_FORM };
	CComboBox	m_cbScanCallback;
	CComboBox	m_cbScanMode;
	CComboBox	m_cbScanTxMode;
	CComboBox	m_cbScanTcCh;
	CComboBox	m_cbScanSendDelay;
	CComboBox	m_cbScanRcvDelay;
	CComboBox	m_cbScanTime;
	CEdit	m_editScanName;
	CListBox	m_ListUsedCh;
	CListBox	m_ListAvaibleCh;
	//}}AFX_DATA

	int m_CurrentList;
	int m_ListCount;
	bool	m_bCallback;
// Attributes
public:

	map< int , DWORD >	mapAllChannel;
	map< int , DWORD >	mapUsedChannel;
	map< int,DWORD>::iterator	map_it;
// Operations
public:
	void	SetDefaultTime(bool	bRead = true);
	void	SetWriteMsg();
	bool	HandleStr(const	CString&	str,int nRound);
	void	EnableButton();//按钮设置
	//可用列表初始化
	void	ScanlistAllShow(void);
	//已使用列表初始化

	void	LoadData();
	void	ComboAddString();
 	void	SetScanChannelCount(int nFlag,int nList,int nVal);
	void	SetScanCommmonValues(int nFlag,int nList,int nVal,int nLen = 1);
	void	SetScanName(int nFlag,int nList,int nLen,CString&	str);
	void	SetScanChFlag(int nFlag,int nVal,int nList,int nRound,bool	bCh = true);
// 	int		GetScanlistCount();
	int		GetFreqScope();
	int		GetScanlistInfo(int nFlag,int nList);
	int		GetScanlistChInfo(int nFlag,int nLen,int nListnum,int nChnum,bool bChOrZone = true);//获取扫描列表中包含的信道信息
// 	CString	GetScanlistName(int nFlag,int nLen,int nList);
	CString	GetChannelName(int ByteLen,int nFlag,int nZone,//所要获取的区域号
		int nChannel,					//所要获取的信道号
		int nStep1 = 736,int nStep2 = 46,bool	bCh  = true);
	//用于获取所有的区域和信道名称
	CString	GetName(int nZone,int nCh,int nFlag,int nLen,int nStep1 = 736,int nStep2 = 46,bool	bCh = true);
inline	CPCSWDoc* GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
	return (CPCSWDoc*)m_pDocument;
}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScanView)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonLast();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonPrev();
	afx_msg void OnSelchangeComboScanOnTime();
	afx_msg void OnSelchangeComboScanRcvdelay();
	afx_msg void OnSelchangeComboScanSenddelay();
	afx_msg void OnSelchangeComboScanTxchannel();
	afx_msg void OnSelchangeComboScanTxmode();
	afx_msg void OnSelchangeComboScanmode();
	afx_msg void OnRadioCallback();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboScanCallback();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANVIEW_H__C225886B_5158_4F56_AFA1_D8FE22BDF0D3__INCLUDED_)
