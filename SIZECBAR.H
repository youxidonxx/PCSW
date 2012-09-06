/*******************************************************************************
*   File Name: Sizecbar.cpp 

*   Description: Defines the class behaviors for the application.

*   Copyright:
      Copyright (c) 2010 LinkTop, Incorporated and its licensors. All Rights 
    Reserved. LinkTop Proprietary. Export of this technology or software is 
    regulated by the P.R.C Government. Diversion contrary to P.R.C law 
    prohibited.

*   Change History:
*   Date                 Author        Release       Description
  2011/04                Qiang jianlong      
*******************************************************************************/

/*******************************************************************************
                                Include Files
*******************************************************************************/

#if !defined(SIZECBAR_H_INCLUDED)
#define SIZECBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// sizecbar1.h : header file
//

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar control bar
#include < afxpriv.h > 
#include < afxres.h >

class CSizingControlBar : public CControlBar
{
public:
    CSizingControlBar();

// Attributes
public:
    CSize m_sizeHorz;
    CSize m_sizeVert;
    CSize m_sizeFloat;
    BOOL IsHorzDocked() const;
    BOOL IsVertDocked() const;

// Operations
public:

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSizingControlBar)
	public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, BOOL bHasGripper, UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void ShowContrl(BOOL m_show=TRUE);
    virtual ~CSizingControlBar();
    
protected:
    // implementation helpers
    void StartTracking();
    void StopTracking(BOOL bAccept);
	void OnTrackUpdateSize(CPoint& point);
    void OnTrackInvertTracker();

	void SetStatusText(UINT nID=AFX_IDW_STATUS_BAR);
	virtual CSize CalcMaxSize();
	virtual BOOL QueryDragFullWindows() const;

protected:
	// used for resizing
    CSize	m_sizeMin;
    CSize   m_sizeMax;
	CPoint	m_ptOld;
    CRect   m_rectBorder;
    BOOL    m_bTracking;
	BOOL	m_bDragShowContent;
	CSize	m_sizeOld;

    BOOL    m_bInRecalcNC;
    UINT    m_nDockBarID;
    int     m_cxEdge;
    BOOL    m_bHasGripper;
    int     m_cyGripper;
    CRect   m_rectGripper;
	CRect		m_rectUndock;
	CRect		m_rectClose;

// Generated message map functions
protected:
    //{{AFX_MSG(CSizingControlBar)
    afx_msg void OnPaint();
    afx_msg void OnNcPaint();
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd *pWnd);
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult );

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(SIZECBAR_H_INCLUDED)

