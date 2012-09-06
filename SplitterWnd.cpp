// SplitterWnd.cpp : implementation file
//

#include "stdafx.h"
 #include "SplitterWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx

CSplitterWndEx::CSplitterWndEx()
{
	//���ķָ����ʹ������С
	m_cxSplitter = m_cySplitter = 10;
	m_cxSplitterGap = m_cySplitterGap = 10;
}

CSplitterWndEx::~CSplitterWndEx()
{
}


BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitterWndEx)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx message handlers

void CSplitterWndEx::OnDrawSplitter(CDC *pDC, ESplitType nType, const CRect &rectArg)
{
	// if pDC == NULL, then just invalidate
	if (pDC == NULL)
	{
		RedrawWindow(rectArg, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	ASSERT_VALID(pDC);
	
	// otherwise, actually draw
	CRect rc = rectArg;
	switch(nType) 
	{ 
	case splitBorder:
		//�ػ��ָ�ڱ߽�,ʹ����Ϊ��ɫ ����Ϊ��ɫ
		pDC->Draw3dRect(rc,RGB(0,200,0),RGB(255,0,0));
		rc.InflateRect(-1,-1); 
		pDC->Draw3dRect(rc,RGB(0,200,0),RGB(255,0,0)); 
		return; 
	case splitBox:
		pDC->Draw3dRect(rc,RGB(0,0,0),RGB(0,0,0));
		rc.InflateRect(-1,-1); 
		pDC->Draw3dRect(rc,RGB(0,0,0),RGB(0,0,0));
		rc.InflateRect(-1,-1);
		pDC->FillSolidRect(rc,RGB(0,0,0)); 
		pDC->Draw3dRect(rc,RGB(0,0,0),RGB(0,0,0));
		return; 
	case splitBar: 
		//�ػ��ָ�����ʹ֮Ϊ��ɫ 
		pDC->FillSolidRect(rc,RGB(100,200,255));
		rc.InflateRect(-1,-1); 
		pDC->Draw3dRect(rc,RGB(0,0,200),RGB(0,0,200));		
		return; 
	default: 
		ASSERT(FALSE); 
	} 
	// fill the middle
	pDC->FillSolidRect(rc, RGB(0,200,0));
}

void CSplitterWndEx::OnInvertTracker(const CRect &rect)
{
	ASSERT_VALID(this);
	ASSERT(!rect.IsRectEmpty());
	ASSERT((GetStyle() & WS_CLIPCHILDREN) == 0);
	
	// pat-blt without clip children on
	CDC* pDC = GetDC();
	// invert the brush pattern (looks just like frame window sizing)
	CBrush* pBrush = CDC::GetHalftoneBrush();
	HBRUSH hOldBrush = NULL;
	if (pBrush != NULL)
		hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATINVERT);
	if (hOldBrush != NULL)
		SelectObject(pDC->m_hDC, hOldBrush);
	ReleaseDC(pDC);

}

void CSplitterWndEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CSplitterWnd::OnLButtonDown(nFlags, point);
}
