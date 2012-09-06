/*******************************************************************************
*   File Name: SizingControlBar.cpp

*   Description: implementation file

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
#include "stdafx.h"
#include "afxpriv.h"    // for CDockContext
#include "sizecbar.h"
//#include "afximpl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar

CSizingControlBar::CSizingControlBar()
{
    m_sizeMin = CSize(32, 32);
    m_sizeHorz = CSize(200, 200);
    m_sizeVert = CSize(200, 200);
    m_sizeFloat = CSize(200, 200);
    m_bTracking = FALSE;
    m_bInRecalcNC = FALSE;
    m_cxEdge = 5;
	m_bDragShowContent = FALSE;
}

CSizingControlBar::~CSizingControlBar()
{
}

BEGIN_MESSAGE_MAP(CSizingControlBar, CControlBar)
    //{{AFX_MSG_MAP(CSizingControlBar)
    ON_WM_PAINT()
    ON_WM_NCPAINT()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_NCCALCSIZE()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
    ON_WM_CAPTURECHANGED()
    ON_WM_NCHITTEST()
    ON_WM_SETCURSOR()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEMOVE()
    ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar message handlers

BOOL CSizingControlBar::Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
                               CSize sizeDefault, BOOL bHasGripper,
                               UINT nID, DWORD dwStyle)
{
    ASSERT_VALID(pParentWnd);   // must have a parent
    ASSERT (!((dwStyle & CBRS_SIZE_FIXED)
        && (dwStyle & CBRS_SIZE_DYNAMIC)));

    // save the style
    SetBarStyle(dwStyle & CBRS_ALL);

    CString wndclass = ::AfxRegisterWndClass(CS_DBLCLKS,
        ::LoadCursor(NULL, IDC_ARROW),
        ::GetSysColorBrush(COLOR_BTNFACE), 0);

    dwStyle &= ~CBRS_ALL;
    dwStyle &= WS_VISIBLE | WS_CHILD;
    if (!CWnd::Create(wndclass, lpszWindowName, dwStyle, CRect(0,0,0,0),
        pParentWnd, nID))
        return FALSE;

    m_sizeHorz = sizeDefault;
    m_sizeVert = sizeDefault;
    m_sizeFloat = sizeDefault;

    m_bHasGripper = bHasGripper;
    m_cyGripper = m_bHasGripper ? 12 : 0;

	//允许ToolTips
	EnableToolTips(TRUE);

    return TRUE;
}

BOOL CSizingControlBar::IsHorzDocked() const
{
    return (m_nDockBarID == AFX_IDW_DOCKBAR_TOP ||
        m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);
}

BOOL CSizingControlBar::IsVertDocked() const
{
    return (m_nDockBarID == AFX_IDW_DOCKBAR_LEFT ||
        m_nDockBarID == AFX_IDW_DOCKBAR_RIGHT);
}

CSize CSizingControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
    CRect rc;

    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rc);
    int nHorzDockBarWidth = bStretch ? 32767 : rc.Width() + 4;
    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc);
    int nVertDockBarHeight = bStretch ? 32767 : rc.Height() + 4;

    if (bHorz)
        return CSize(nHorzDockBarWidth, m_sizeHorz.cy);
    else
        return CSize(m_sizeVert.cx, nVertDockBarHeight);
}

CSize CSizingControlBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
    if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
    {
        if (nLength == -1)
            GetDockingFrame()->DelayRecalcLayout();
        return CControlBar::CalcDynamicLayout(nLength,dwMode);
    }

    if (dwMode & LM_MRUWIDTH)
        return m_sizeFloat;

    if (dwMode & LM_COMMIT)
    {
        m_sizeFloat.cx = nLength;
        return m_sizeFloat;
    }

    if (dwMode & LM_LENGTHY)
        return CSize(m_sizeFloat.cx,
            m_sizeFloat.cy = max(m_sizeMin.cy, nLength));
    else
        return CSize(max(m_sizeMin.cx, nLength), m_sizeFloat.cy);
}

void CSizingControlBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CControlBar::OnWindowPosChanged(lpwndpos);

    // Find on which side are we docked
    m_nDockBarID = GetParent()->GetDlgCtrlID();

    if (!m_bInRecalcNC)
    {
        m_bInRecalcNC = TRUE;

        // Force recalc the non-client area
        SetWindowPos(NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE |
            SWP_NOACTIVATE | SWP_NOZORDER |
            SWP_FRAMECHANGED);

        m_bInRecalcNC = FALSE;
    }
}

// cache of last needed cursor
AFX_STATIC_DATA HCURSOR _afx_hcurLast = NULL;
AFX_STATIC_DATA HCURSOR _afx_hcurDestroy = NULL;
AFX_STATIC_DATA UINT _afx_idcPrimaryLast = 0; // store the primary IDC

BOOL CSizingControlBar::OnSetCursor(CWnd* pWnd, UINT nHitTest,
                                    UINT message) 
{
  /*if((nHitTest == HTSYSMENU) && !IsFloating())
	{
	//	MessageBox("aa");
		TOOLTIPTEXT m_psttt;
        m_psttt.hdr.hwndFrom=m_hWnd;
        m_psttt.hdr.idFrom=pWnd->GetDlgCtrlID();
        m_psttt.hdr.code=TTN_NEEDTEXT;   
		m_psttt.uFlags= TTF_IDISHWND;
		SetStatusText(ID_DIALAGBAR_FLOAT);
 //     SendMessage(WM_NOTIFY); 

	}
   else if ((nHitTest == HTMINBUTTON) && !IsFloating())
		MessageBox("bb");
*/
	if ((nHitTest != HTSIZE) || m_bTracking)
        return CControlBar::OnSetCursor(pWnd, nHitTest, message);

	UINT idcPrimary;        // app supplied cursor
	LPCTSTR idcSecondary;    // system supplied cursor (MAKEINTRESOURCE)

    /*if (IsHorzDocked())
        ::SetCursor(::LoadCursor(NULL, IDC_SIZENS));
    else
        ::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));*/
	// ------- change by syx
	if(IsHorzDocked())
	{
		idcPrimary = AFX_IDC_VSPLITBAR;
		idcSecondary = IDC_SIZENS;
	}
	else
	{
		idcPrimary = AFX_IDC_HSPLITBAR;
		idcSecondary = IDC_SIZEWE;
	}
	HCURSOR hcurToDestroy = NULL;
	if(idcPrimary != _afx_idcPrimaryLast)
	{
		HINSTANCE hInst = AfxFindResourceHandle(
			MAKEINTRESOURCE(idcPrimary), RT_GROUP_CURSOR);
		
		// load in another cursor
		hcurToDestroy = _afx_hcurDestroy;
		
		// Note: If this LoadCursor call fails, it is likely that
		//  _AFX_NO_SPLITTER_RESOURCES is defined in your .RC file.
		// To correct the situation, remove the following line from your
		//  resource script:
		//      #define _AFX_NO_SPLITTER_RESOURCES
		// This should be done using the Resource.Set Includes... command.
		
		if((_afx_hcurDestroy = _afx_hcurLast =
			::LoadCursor(hInst, MAKEINTRESOURCE(idcPrimary))) == NULL)
		{
			// will not look as good
			TRACE0("Warning: Could not find splitter cursor - using system provided alternative.\n");
			
			ASSERT(_afx_hcurDestroy == NULL);    // will not get destroyed
			_afx_hcurLast = ::LoadCursor(NULL, idcSecondary);
			ASSERT(_afx_hcurLast != NULL);
		}
		_afx_idcPrimaryLast = idcPrimary;
	}
	ASSERT(_afx_hcurLast != NULL);
	::SetCursor(_afx_hcurLast);
	ASSERT(_afx_hcurLast != hcurToDestroy);
	if (hcurToDestroy != NULL)
		::DestroyCursor(hcurToDestroy); // destroy after being set
	// ------- change by syx

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// Mouse Handling
//数控件标题栏被单击响应函数
void CSizingControlBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (m_pDockBar != NULL)
    {
        // start the drag
        ASSERT(m_pDockContext != NULL);
        ClientToScreen(&point);
        m_pDockContext->StartDrag(point);
    }
    else
        CWnd::OnLButtonDown(nFlags, point);
}
//数控件标题栏被单击响应函数
void CSizingControlBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    if (m_pDockBar != NULL)
    {
        // toggle docking
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->ToggleDocking();
    }
    else
        CWnd::OnLButtonDblClk(nFlags, point);
}
//数控件侧栏被单击响应函数
void CSizingControlBar::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
    CWindowDC dc(this);
    if (m_bTracking) return;

	if((nHitTest == HTSYSMENU) && !IsFloating())
	{
		dc.DrawEdge(m_rectClose,EDGE_SUNKEN,BF_RECT);
	}
    else if ((nHitTest == HTMINBUTTON) && !IsFloating())
		dc.DrawEdge(m_rectUndock,EDGE_SUNKEN,BF_RECT);
    else if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
		CControlBar::OnNcLButtonDown(nHitTest, point);

}
//数控件侧栏被单击松开响应函数
void CSizingControlBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
        StopTracking(TRUE);

    CControlBar::OnLButtonUp(nFlags, point);
}
//数控件标题栏被右键点击响应函数
void CSizingControlBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
        StopTracking(FALSE);
	
	CControlBar::OnRButtonDown(nFlags, point);
}
//鼠标在标题栏移动时响应函数
void CSizingControlBar::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
    {
		ASSERT (!IsFloating());
		CPoint pt = point;
		ClientToScreen(&pt);

		OnTrackUpdateSize(pt);
    }

    CControlBar::OnMouseMove(nFlags, point);
}
//当捕捉到数控界面变化后响应函数
//当数控件被拖离原来位置鼠标松开后响应函数
void CSizingControlBar::OnCaptureChanged(CWnd *pWnd) 
{
    if (m_bTracking && pWnd != this)
        StopTracking(FALSE); // cancel tracking

    CControlBar::OnCaptureChanged(pWnd);
}
//
void CSizingControlBar::OnNcCalcSize(BOOL bCalcValidRects,
                                     NCCALCSIZE_PARAMS FAR* lpncsp) 
{
    // Compute the rectangle of the mobile edge
    GetWindowRect(m_rectBorder);
    m_rectBorder.OffsetRect(-m_rectBorder.left, -m_rectBorder.top);
    m_rectBorder.DeflateRect(1, 1);
    
    m_rectGripper = m_rectBorder;
    m_rectGripper.DeflateRect(5, 5);
    m_rectGripper.right -= m_cxEdge;
    m_rectGripper.bottom -= m_cxEdge;
    CRect rc = lpncsp->rgrc[0];

    DWORD dwBorderStyle = m_dwStyle | CBRS_BORDER_ANY;

    switch(m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        dwBorderStyle &= ~CBRS_BORDER_BOTTOM;
        rc.DeflateRect(m_cyGripper + 2, 2, 2, m_cxEdge + 2);
        m_rectBorder.top = m_rectBorder.bottom - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        dwBorderStyle &= ~CBRS_BORDER_TOP;
        rc.DeflateRect(m_cyGripper + 2, m_cxEdge + 2, 2, 2);
        m_rectBorder.bottom = m_rectBorder.top + m_cxEdge;
        m_rectGripper.OffsetRect(0, m_cxEdge);
        break;
    case AFX_IDW_DOCKBAR_LEFT:
        dwBorderStyle &= ~CBRS_BORDER_RIGHT;
        rc.DeflateRect(2, m_cyGripper + 2, m_cxEdge + 2, 6);
        m_rectBorder.left = m_rectBorder.right - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_RIGHT:
        dwBorderStyle &= ~CBRS_BORDER_LEFT;
        rc.DeflateRect(m_cxEdge + 2, m_cyGripper + 2, 2, 6);
        m_rectBorder.right = m_rectBorder.left + m_cxEdge;
        m_rectGripper.OffsetRect(m_cxEdge, 0);
        break;
    default:
        m_rectBorder.SetRectEmpty();
        break;
    }

    lpncsp->rgrc[0] = rc;

    SetBarStyle(dwBorderStyle);
}

void CSizingControlBar::OnNcPaint() 
{
    // get window DC that is clipped to the non-client area
    CWindowDC dc(this);
    CRect rectClient;
    GetClientRect(rectClient);
    CRect rectWindow;
    GetWindowRect(rectWindow);
    ScreenToClient(rectWindow);
    rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
    dc.ExcludeClipRect(rectClient);

    // draw borders in non-client area
    rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
    DrawBorders(&dc, rectWindow);

    // erase parts not drawn
    dc.IntersectClipRect(rectWindow);

    // erase NC background the hard way
    HBRUSH hbr = (HBRUSH)GetClassLong(m_hWnd, GCL_HBRBACKGROUND);
    ::FillRect(dc.m_hDC, rectWindow, hbr);

    // paint the mobile edge
    dc.Draw3dRect(m_rectBorder, ::GetSysColor(COLOR_BTNHIGHLIGHT),
        ::GetSysColor(COLOR_BTNSHADOW));

    if (m_bHasGripper)
    {
        // paint the gripper
 //       CRect gripper = m_rectGripper;
    	CRect gripper;
		GetWindowRect( gripper );
		ScreenToClient( gripper );
		gripper.OffsetRect( -gripper.left, -gripper.top );
    
        if (IsHorzDocked())
        {
            // gripper at left
     /*       gripper.right = gripper.left + 3;
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
            gripper.OffsetRect(3, 0);
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));

		// gripper at left
		m_rectGripper.top		= gripper.top + 40;
		m_rectGripper.bottom	= gripper.bottom;
		m_rectGripper.left		= gripper.left;
		m_rectGripper.right	= gripper.left + 20;
	*/
		// draw close box
		m_rectClose.left = gripper.left + 3;
		m_rectClose.right = m_rectClose.left + 12;
		m_rectClose.top = gripper.top + 10;
		m_rectClose.bottom = m_rectClose.top + 12;
		dc.DrawFrameControl(m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);

		// draw docking toggle box
		m_rectUndock = m_rectClose;
		m_rectUndock.OffsetRect(0,13);
		dc.DrawFrameControl(m_rectUndock, DFC_CAPTION, DFCS_CAPTIONMAX);

		gripper.top += 38;
		gripper.bottom -= 10;
		gripper.left += 5;
		gripper.right = gripper.left+3;
        dc.Draw3dRect( gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW) );
		
		gripper.OffsetRect(4, 0);
        dc.Draw3dRect( gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));        
		}
        else if (IsVertDocked())
        {
            // gripper at top
     /*      gripper.bottom = gripper.top + 3;
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
            gripper.OffsetRect(0, 3);
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
        */
		// gripper at top
/*		m_rectGripper.top		= gripper.top;
		m_rectGripper.bottom	= gripper.top + 20;
		m_rectGripper.left		= gripper.left;
		m_rectGripper.right		= gripper.right - 24;
*/
		// draw close box
		m_rectClose.right = gripper.right - 10;
		m_rectClose.left = m_rectClose.right - 11;
		m_rectClose.top = gripper.top+3;//+ 7
		m_rectClose.bottom = m_rectClose.top + 11;
		dc.DrawFrameControl(m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);


		// draw docking toggle box
		m_rectUndock = m_rectClose;
		m_rectUndock.OffsetRect(-13,0);
		dc.DrawFrameControl(m_rectUndock, DFC_CAPTION, DFCS_CAPTIONMAX);

		gripper.right -= 38;
		gripper.left += 10;
		gripper.top += 5;
		gripper.bottom = gripper.top + 3;
		dc.Draw3dRect( gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW) );
		
		gripper.OffsetRect(0, 4);
        dc.Draw3dRect( gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW) );

		}
    }

    ReleaseDC(&dc);
}

void CSizingControlBar::OnPaint() 
{
    // overridden to skip border painting based on clientrect
    CPaintDC dc(this);
}

LRESULT CSizingControlBar::OnNcHitTest(CPoint point) 
{
    if (IsFloating())
        return CControlBar::OnNcHitTest(point);

    CRect rc;
    GetWindowRect(rc);
    point.Offset(-rc.left, -rc.top);
	if(m_rectClose.PtInRect(point))
		return HTSYSMENU;
	else if (m_rectUndock.PtInRect(point))
		return HTMINBUTTON;
/*	else if (m_rectGripper.PtInRect(point))
		return HTCAPTION;
    else if (m_rectBorder.PtInRect(point))
        return HTSIZE;
    else
        return CControlBar::OnNcHitTest(point);
*/
    if (m_rectBorder.PtInRect(point))
        return HTSIZE;
    else
        return HTCLIENT;
}

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar implementation helpers

void CSizingControlBar::StartTracking()
{
    SetCapture();

    // make sure no updates are pending
    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
	
	m_bDragShowContent = QueryDragFullWindows();
	
	if (!m_bDragShowContent)
	    m_pDockSite->LockWindowUpdate();

	m_sizeOld = IsHorzDocked() ? m_sizeHorz : m_sizeVert;

	CRect rect;
	GetWindowRect(&rect);
    m_ptOld = m_rectBorder.CenterPoint() + rect.TopLeft();

	m_sizeMax = CalcMaxSize();
    m_bTracking = TRUE;
    
	if (!m_bDragShowContent)
	    OnTrackInvertTracker();
}

void CSizingControlBar::StopTracking(BOOL bAccept)
{
	if (!m_bDragShowContent)
	{
		OnTrackInvertTracker();
	    m_pDockSite->UnlockWindowUpdate();
	}

    m_bTracking = FALSE;
    ReleaseCapture();
    
    if (!bAccept) // resize canceled?
	{
		// restore old size
		if (IsHorzDocked())
	        m_sizeHorz = m_sizeOld;
		else
			m_sizeVert = m_sizeOld;
	}

    m_pDockSite->DelayRecalcLayout();
}

void CSizingControlBar::OnTrackUpdateSize(CPoint& point)
{
	BOOL bHorz = IsHorzDocked();

    CSize sizeNew = m_sizeOld;
	
    if ((m_nDockBarID == AFX_IDW_DOCKBAR_TOP) ||
		(m_nDockBarID == AFX_IDW_DOCKBAR_LEFT))
        sizeNew += point - m_ptOld;
	else
        sizeNew -= point - m_ptOld;

	// check limits
  	sizeNew.cx = max(m_sizeMin.cx, sizeNew.cx);
  	sizeNew.cy = max(m_sizeMin.cy, sizeNew.cy);
  	sizeNew.cx = min(m_sizeMax.cx, sizeNew.cx);
  	sizeNew.cy = min(m_sizeMax.cy, sizeNew.cy);

    if ((sizeNew.cy == m_sizeHorz.cy) && bHorz ||
		(sizeNew.cx == m_sizeVert.cx) && !bHorz)
		return; // no size change

	if (!m_bDragShowContent)
		OnTrackInvertTracker();

    if (bHorz)
		m_sizeHorz = sizeNew;
	else
		m_sizeVert = sizeNew;

	if (!m_bDragShowContent)
		OnTrackInvertTracker();
	else
	    m_pDockSite->DelayRecalcLayout();
}

CSize CSizingControlBar::CalcMaxSize()
{
	// the control bar cannot grow with more than the size of 
	// remaining client area of the frame
	CRect rect;
	m_pDockSite->GetClientRect(&rect);
	CSize size = rect.Size();
	CWnd* pBar;
	if (IsHorzDocked())
	{
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_BOTTOM))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_STATUS_BAR))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
	}
	else
	{
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_RIGHT))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
	}
	
	size -= CSize(4, 4);
    size += IsHorzDocked() ? m_sizeHorz : m_sizeVert;

	return size;
}

void CSizingControlBar::OnTrackInvertTracker()
{
    ASSERT_VALID(this);
    ASSERT(m_bTracking);

	CRect rect = m_rectBorder;
    CRect rectBar, rectFrame;
    GetWindowRect(rectBar);
    rect.OffsetRect(rectBar.TopLeft());
    m_pDockSite->GetWindowRect(rectFrame);
    rect.OffsetRect(-rectFrame.left, -rectFrame.top);

	switch (m_nDockBarID)
	{
	case AFX_IDW_DOCKBAR_TOP:
		rect.OffsetRect(0, m_sizeHorz.cy - m_sizeOld.cy); break;
	case AFX_IDW_DOCKBAR_BOTTOM:
		rect.OffsetRect(0, m_sizeOld.cy - m_sizeHorz.cy); break;
	case AFX_IDW_DOCKBAR_LEFT:
		rect.OffsetRect(m_sizeVert.cx - m_sizeOld.cx, 0); break;
	case AFX_IDW_DOCKBAR_RIGHT:
		rect.OffsetRect(m_sizeOld.cx - m_sizeVert.cx, 0); break;
	}
	if (IsVertDocked())
	    rect.bottom -= 4;
    rect.DeflateRect(1, 1);

    CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);

    CBrush* pBrush = CDC::GetHalftoneBrush();
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL)
        hOldBrush = (HBRUSH)::SelectObject(pDC->m_hDC, pBrush->m_hObject);

    pDC->PatBlt(rect.left, rect.top,
		rect.Width(), rect.Height(), PATINVERT);

    if (hOldBrush != NULL)
        ::SelectObject(pDC->m_hDC, hOldBrush);

    m_pDockSite->ReleaseDC(pDC);
}

BOOL CSizingControlBar::QueryDragFullWindows() const
{
	TCHAR sDragfullWindows[2];
	DWORD cbDragfullWindows = sizeof(DWORD);
	DWORD dwType;
	HKEY hKey;
	BOOL bRet = FALSE;

	RegOpenKeyEx(HKEY_CURRENT_USER, _T("Control Panel\\desktop"),
		0, KEY_QUERY_VALUE, &hKey);

	if (!FAILED(RegQueryValueEx(hKey, _T("DragfullWindows"),
		NULL, &dwType, (LPBYTE)&sDragfullWindows, &cbDragfullWindows)))
		if (!_tcscmp(sDragfullWindows, _T("1")))
			bRet = TRUE;

	RegCloseKey(hKey);

	return bRet;
}

void CSizingControlBar::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*    if (m_bTracking) return;

    if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
        CControlBar::OnNcLButtonDown(nHitTest, point);
*/
    if (m_bTracking) return;

	if((nHitTest == HTSYSMENU) && !IsFloating())
	{
//		CFrameWnd::ShowControlBar((CControlBar*),((GetStyle() & WS_VISIBLE)==0),FALSE);		
		ShowWindow(SW_HIDE);
		m_pDockContext->ToggleDocking();
	}
    else if ((nHitTest == HTMINBUTTON) && !IsFloating())
        m_pDockContext->ToggleDocking();
	else if ((nHitTest == HTCAPTION) && !IsFloating() && (m_pDockBar != NULL))
    {
        // start the drag
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->StartDrag(point);
    }
    else if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
     //   CControlBar::OnNcLButtonDown(nHitTest, point);	
		CControlBar::OnNcLButtonUp(nHitTest, point);
}

void CSizingControlBar::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CWindowDC dc(this);
	if(!(m_rectClose.PtInRect(point)) && !IsFloating())
		dc.DrawEdge(m_rectClose,EDGE_RAISED,BF_RECT);
    if(!(m_rectUndock.PtInRect(point)) && !IsFloating())
		dc.DrawEdge(m_rectUndock,EDGE_RAISED,BF_RECT);

	CControlBar::OnNcMouseMove(nHitTest, point);
}

void CSizingControlBar::ShowContrl(BOOL m_show)
{
	if(m_show)
		ShowWindow(SW_SHOWNORMAL);
	else
		ShowWindow(SW_HIDE);
}
void CSizingControlBar::SetStatusText(UINT nID)
{  
	if(nID==0)//HTSYSMENU
        nID=AFX_IDS_IDLEMESSAGE;
    CWnd *pWnd=AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR);
    if(pWnd)  
	{     
		AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING ,nID);
	    pWnd->SendMessage(WM_IDLEUPDATECMDUI);
        pWnd->UpdateWindow();
    }
}
BOOL CSizingControlBar::OnTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{

	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR; 
	UINT nID =pNMHDR->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND)
    {
        nID = ::GetDlgCtrlID((HWND)nID);  
		if(nID)
        {
			CString szFullText;
			CString StrTipText;
			szFullText.LoadString(nID);
			AfxExtractSubString(StrTipText,szFullText,1,'\n');   
			if(!StrTipText.IsEmpty())
// 				  strcpy(pTTT->lpszText,StrTipText);
				strcpy_s(pTTT->lpszText,StrTipText.GetLength(),StrTipText);
			pTTT->hinst = AfxGetResourceHandle(); 
				return(TRUE);
        }  
	}   
	return FALSE;
}
