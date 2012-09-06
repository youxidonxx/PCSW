// DpmrView.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "DpmrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static	CString	strTitle[] = {"联系人","快捷短信","组呼列表"};

/////////////////////////////////////////////////////////////////////////////
// CDpmrView

IMPLEMENT_DYNCREATE(CDpmrView, CFormView)

CDpmrView::CDpmrView()
	: CFormView(CDpmrView::IDD)
{
	//{{AFX_DATA_INIT(CDpmrView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDpmrView::~CDpmrView()
{
}

void CDpmrView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDpmrView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDpmrView, CFormView)
	//{{AFX_MSG_MAP(CDpmrView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDpmrView diagnostics

#ifdef _DEBUG
void CDpmrView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDpmrView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDpmrView message handlers

void CDpmrView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRect	rect;
	((CStatic*)GetDlgItem(IDC_STATIC_SHEET))->GetWindowRect(&rect);
  		ScreenToClient(&rect);
	m_sheet.MoveWindow(&rect,true);
	LoadData();

}
void	CDpmrView::LoadData()
{

}

 

int CDpmrView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_sheet.AddPage(&m_pageCont);
	m_sheet.AddPage(&m_pageSms);
 	m_sheet.AddPage(&m_pageGrp);

	m_sheet.Create(this,WS_CHILD|WS_VISIBLE,WS_EX_CONTROLPARENT);
 	CTabCtrl*	pTabCtrl =m_sheet.GetTabControl();
	int i=0;
	TC_ITEM   tcItem; 
	CString   sCaption ;
	while(i<ArraySize(strTitle))
	{
		sCaption=  strTitle[i];
		tcItem.mask   =   TCIF_TEXT; 
		tcItem.pszText   =   (LPTSTR)((LPCTSTR)sCaption); 
		pTabCtrl-> SetItem(i,   &tcItem   ); 
		i++;
	}
	//错误的写法
//  	pTabCtrl->GetItem(0,&item);
// 	item.mask|=TCIF_TEXT;
// 	int cnt = 	pTabCtrl->GetItemCount();
// 	for (int i=0;i<cnt;i++)
// 	{
// 		int len = strTitle[i].GetLength();
// //		memcpy(item.pszText,strTitle[i].GetBuffer(len),len);
// 		item.pszText = strTitle[i].GetBuffer(len);
// 		strTitle[i].ReleaseBuffer();
// 		pTabCtrl->SetItem(i,&item);
// 	}
 
	return 0;
}

BOOL CDpmrView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	static BOOL bEntered = FALSE;		// watch for re-entry from property sheet call to views PreTranslateMessage
	if (!bEntered) 
	{
		BOOL	bRet;
		bEntered = TRUE;
		bRet = m_sheet.PreTranslateMessage(pMsg);
		bEntered = FALSE;
		if (bRet)
			return TRUE;
	}
	return CFormView::PreTranslateMessage(pMsg);
}

 