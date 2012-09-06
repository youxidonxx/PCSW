#if !defined(AFX_MENUSET_H__97F09AB6_34B6_46CF_8C43_9DA61F76A0FD__INCLUDED_)
#define AFX_MENUSET_H__97F09AB6_34B6_46CF_8C43_9DA61F76A0FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuSet.h : header file
//
#include "PCSWDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CMenuSet form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMenuSet : public CFormView
{
public:
	CMenuSet();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMenuSet)

// Form Data
public:
	//{{AFX_DATA(CMenuSet)
	enum { IDD = IDD_MENU_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
/**/		enum MenuAddress
	{
		MenuPowerLvl=0x00,
		MenuKeyLock=0x01,
		MenuLanguage=0x02,
		MenuBackLight=0x03,
		MenuLed=0x04,
		MenuTone=0x05,
		MenuLuminance=0x06,
		MenuSMS=0x07,
		MenuNoise=0x08,
		MenuDeleteItemOfContact=0x09,
		MenuScan=0x0A,
		MenuScanCheckCh=0x0B,
		MenuScanAddTempCh=0x0C,
		MenuScanDelTempCh=0x0D,
		MenuScanAddCh=0x0E,
		MenuScanDelCh=0x0F,
		MenuVox=0x10,
		MenuWhisper=0x11,
		MenuVibration=0x12,
		MenuDate=0x13,
		MenuMainMenu=0x14,
		MenuPowerSave=0x15,
		MenuTalkAround=0x16,
		MenuSpeechEnhance = 0x17,
		MenuVoiceKey = 0x18,
		MenuAllowKill=0x20,			//允许遥弊,在radiosetting中位置
		MenuAllowActive=0x21		//允许激活

	};
	void	LoadData();
inline	CPCSWDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
		return (CPCSWDoc*)m_pDocument;
	}
protected:
	int		CheckMenuIDArray[0x18];
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuSet)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMenuSet();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMenuSet)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnCheckScan();
// 	afx_msg LRESULT OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_MSG
	afx_msg	 void	OnClick(UINT	uID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUSET_H__97F09AB6_34B6_46CF_8C43_9DA61F76A0FD__INCLUDED_)
