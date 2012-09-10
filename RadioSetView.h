#if !defined(AFX_RADIOSETVIEW_H__AF0DE3F9_6452_45A4_B6D4_4E0D4E232CFC__INCLUDED_)
#define AFX_RADIOSETVIEW_H__AF0DE3F9_6452_45A4_B6D4_4E0D4E232CFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadioSetView.h : header file
//
#include "PCSWDoc.h"
#include "SpanEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CRadioSetView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#define CHECK_NUM_SETTING	30		//checkbox的个数
#define SPINEDIT_SUM_SETTING	14	//spinedit的个数--至少
typedef	struct	tagCtrlInfo
{
	int	nCtrlID[CHECK_NUM_SETTING];
	int	nOffset[CHECK_NUM_SETTING];
}CtrlInfo;
typedef	struct	_tagSpinCtrlInfo
{
	int	nCtrlID[SPINEDIT_SUM_SETTING];
	int	nOffset[SPINEDIT_SUM_SETTING];
	int	nOverleap[SPINEDIT_SUM_SETTING];
	int nStep[SPINEDIT_SUM_SETTING];
}tagSpinCtrlInfo;

class	map_value_finder;

 class CRadioSetView : public CFormView
{
public:
	CRadioSetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRadioSetView)


	void	EnableComboBoxes();
	void	LoadComboString();
	void	LoadAlarmCh();
	int		GetSettingValue(int nFlag);
	int		GetEmerSettingValues(int nFlag);
	void	SetSettingValues(int nFlag,int nVal);
	void	SetEmerSettingValues(int nFlag,int nVal);
	CString	GetIDStr(int nGrp,int nFlag);//nGrp:0==>Emer;1==>RadioSetting
	CString	GetAlarmName(int nFlag,int nLen);

// Form Data
public:
	map<int,DWORD>	mapChannel;
	map<int,DWORD>::iterator	it;
public:
	//{{AFX_DATA(CRadioSetView)
	enum { IDD = IDD_SETTING_FORM };
	CEdit	m_editALARMName;
	CEdit	m_editALARMID;
	CSpanEdit	m_editAlarmCallTime;
	CSpanEdit	m_editAlarmTime;
	CSpanEdit	m_editBKLightDelay;
	CSpanEdit	m_editVoxTime;
	CSpanEdit	m_Treset;
	CSpanEdit	m_Trekey;
	CSpanEdit	m_editTpretot;
	CSpanEdit	m_editTcomm;
	CSpanEdit	m_editPeerHoldTime;
	CSpanEdit	m_editRcvHoldTime;
	CSpanEdit	m_editMicHoldTime;
	CSpanEdit	m_editKeylockDelay;
	CSpanEdit	m_editGrpHoldTime;
	CSpanEdit	m_editPreTxDelay;
	CComboBox	m_cbVoxLvl;
	CComboBox	m_cbTone;
	CComboBox	m_cbPowerSaveLvl;
	CComboBox	m_cbNoiseLvl;
	CComboBox	m_cbCallOutTone;
	CComboBox	m_cbCallInTone;
	CComboBox	m_cbBGLight;
	CComboBox	m_cbAlarmCh;
	CComboBox	m_cbAlarmMode;
	CComboBox	m_cbAlarmType;
	CComboBox	m_cbIdleDisp;
	CEdit	m_editID;
	BOOL	m_bChannelLock;
	BOOL	m_bDateShow;
	BOOL	m_bPowerSaveLvl;
	BOOL	m_bVoxForbidWhileRx;
	BOOL	m_bVoxCancel;
	BOOL	m_bWhisper;
	BOOL	m_bDecodeKillActive;
	//}}AFX_DATA

// Attributes
public:
	void	LoadData();

inline	CPCSWDoc* GetDocument()
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
		return (CPCSWDoc*)m_pDocument;
	}
	
// Operations
protected:
	CtrlInfo		CheckIDArray;
	tagSpinCtrlInfo	SpinIDArray;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadioSetView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRadioSetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRadioSetView)
	afx_msg void OnDeltaposSpinPreTxDelay(NMHDR* pNMHDR, LRESULT* pResult);
 	afx_msg void OnDeltaposSpinGroupcallHoldTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSignalcallHoldTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinKeylockDelay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinVoxDelay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinBglightDelay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTotSelChange(UINT	nID);
	afx_msg void OnEmerSelChange(UINT	nID);
	afx_msg void OnSelchangeComboTone();
	afx_msg void OnSelchangeComboAlarmType();
 	afx_msg void OnSelchangeComboAlarmMode();
	afx_msg void OnSelchangeComboMainStyle();
	afx_msg void OnSelchangeComboBkLight();
	afx_msg void OnSelchangeComboPowerLvl();
	afx_msg void OnCheckPowerLvl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboAlarmChannel();
public:
	afx_msg void OnEnKillfocusEditID();
	afx_msg void OnEnKillfocusEditAlarmID();
public:
	afx_msg void OnEnKillfocusEditAlarmName();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADIOSETVIEW_H__AF0DE3F9_6452_45A4_B6D4_4E0D4E232CFC__INCLUDED_)
