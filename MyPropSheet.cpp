// MyPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "MyPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define		WM_ADJUST		WM_USER+110
/////////////////////////////////////////////////////////////////////////////
// CMyPropSheet
IMPLEMENT_DYNAMIC(CMyPropSheet, CPropertySheet)

CMyPropSheet::CMyPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMyPropSheet::CMyPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}
CMyPropSheet::CMyPropSheet()
{
/*
	AddPage(&m_pageCont);
	AddPage(&m_pageSMS);
*/
	m_pCont = new byte[0x2000];
	m_pSms = new byte[0x2000];
	m_pGrpList = new byte[0x2000];
}

CMyPropSheet::~CMyPropSheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMyPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADJUST, OnAdjust)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPropSheet message handlers

BOOL CMyPropSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
/*
	TCITEM	item;
	CTabCtrl*	pTabCtrl =GetTabControl();

	CSize	size;
	CRect	rect;
	pTabCtrl->GetItemRect(0,&rect);
	size.cx = rect.Width()+5;
	size.cy = rect.Height()+10;
	pTabCtrl->SetItemSize(size);
	pTabCtrl->GetItem(0,&item);
	item.mask|=TCIF_TEXT;
	int cnt = 	pTabCtrl->GetItemCount();
	for (int i=0;i<cnt;i++)
	{
		int len = strTitle[i].GetLength();
//		memcpy(item.pszText,strTitle[i].GetBuffer(len),len);
		item.pszText = strTitle[i].GetBuffer(len);
		strTitle[i].ReleaseBuffer();
		pTabCtrl->SetItem(i,&item);
	}
//	Invalidate(true);
*/
	return bResult;
}
void	CMyPropSheet::LoadData()
{
//	m_pageCont.LoadData();
//	m_pageSMS.LoadData();
}

BOOL CMyPropSheet::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
// 	if ((pMsg->message == WM_SYSKEYDOWN) && (pMsg->wParam > 32)) 
// 	{
// 		CTabCtrl *pTab = GetTabControl();
// 		int n = pTab->GetItemCount();
// 
// 		char buf[80], shortcut[3];
// 		TC_ITEM tcItem;
// 		tcItem.mask = TCIF_TEXT;
// 		tcItem.pszText = buf;
// 		shortcut[0] = '&';
// 		shortcut[2] = '\0';
// 		for (int i = 0; i < n; i++ ) {
// 			tcItem.cchTextMax = sizeof(buf)-1;
// 			pTab->GetItem(i, &tcItem);
// 			shortcut[1] = (char)pMsg->wParam;
// 			if (strstr(buf, shortcut)) {
//  					SetActivePage(i);
// 				return TRUE;
// 			}
// 			else {
// 				shortcut[1] = (char)(isupper(pMsg->wParam) ? tolower : toupper)(pMsg->wParam);
// 				if (strstr(buf, shortcut)) {
//  						SetActivePage(i);
// 					return TRUE;
// 				}
// 			}
// 		}
// 	}
// 
// 	// allow view to pre-translate for hotkeys
// 	CView	*pView = (CView*)GetParent();
// 	if (pView->PreTranslateMessage(pMsg))
// 		return TRUE;
// 		
	return CPropertySheet::PreTranslateMessage(pMsg);
}

BOOL CMyPropSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
// 	NMHDR*	pnmh = (LPNMHDR)lParam;
// 	if(pnmh->code == TCN_SELCHANGING)
// 		m_nActive = GetActiveIndex();
// 	else if (pnmh->code == TCN_SELCHANGE)
// 	{
// 			CView	*pView = (CView*)GetParent();
// 			static NMHDR	nmh = *pnmh;
// 			pView->PostMessage(WM_NOTIFY, wParam, (LPARAM)&nmh);
// 	}
	return CPropertySheet::OnNotify(wParam, lParam, pResult);
}
LRESULT CMyPropSheet::OnAdjust(WPARAM wParam, LPARAM lParam)
{
// 	AdjustPages();
	return 0;
}
void CMyPropSheet::AdjustPages()
{
/*
	CRect rect;
	
	GetClientRect(&rect);

	CTabCtrl* pTab = GetTabControl();

	if (pTab)	{
		pTab->Invalidate(FALSE);
		pTab->MoveWindow(rect, FALSE);		// Resize the TabsCtrl to new size but don't draw now
		pTab->AdjustRect(FALSE, &rect);		// Get the display area below the Tabs
 
		int iTabHeight = rect.top;				// Save the Tab Height

		// Which Page is being adjusted?
		CPropertyPage* pPage = GetActivePage();
		if (pPage->IsKindOf(RUNTIME_CLASS(CPropPageContact))) {
			CRect pageRect;

			//Going to be moving things without redrawing
			pPage->Invalidate(FALSE); 

			// Return to Original Dialog Size
 			((CPropPageContact*)pPage)->GetOriginalRect(&pageRect);

			pPage->MoveWindow(pageRect, FALSE); //Move but don't draw
		
 
			// Adjust for tab height
			pPage->GetWindowRect(&pageRect);
			ScreenToClient(&pageRect);
			pageRect.OffsetRect(0,iTabHeight);
			
			pageRect.IntersectRect(pageRect,rect);		// restrict to the display area
 
			// Fit Page to the new size
			pPage->MoveWindow(pageRect); 
		}
		else if (pPage->IsKindOf(RUNTIME_CLASS(CPropPageSMS)))
		{
		}
	}*/
}
