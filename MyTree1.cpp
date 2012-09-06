// MyTree1.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "MyTree1.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static	CString	strTitle[] = {
								"LT1000B",
								"系统信息","按键设置","系统设置","扫描信息","信道信息","数字设置"
								
									};
/////////////////////////////////////////////////////////////////////////////
// CMyTree

IMPLEMENT_DYNCREATE(CMyTree, CTreeView)

CMyTree::CMyTree()
{
}

CMyTree::~CMyTree()
{
}


BEGIN_MESSAGE_MAP(CMyTree, CTreeView)
	//{{AFX_MSG_MAP(CMyTree)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTree drawing

void CMyTree::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTree diagnostics

#ifdef _DEBUG
void CMyTree::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTree message handlers

void CMyTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	CMainFrame*	pFrame = (CMainFrame*)AfxGetMainWnd();
	CTreeCtrl&	treeCtrl  = GetTreeCtrl();
	HTREEITEM	hSelItem = treeCtrl.GetSelectedItem();

	CString	str = treeCtrl.GetItemText(hSelItem);
	int i=0;
	for (;i<treeCtrl.GetCount();i++)
	{
		if(str.Find(strTitle[i])!=-1)
			break;
	}	

	int nSelected = i;
	pFrame->SwitchView(nSelected);
 	*pResult = 0;
}

void CMyTree::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	::SetWindowLong(m_hWnd,GWL_STYLE,WS_VISIBLE|WS_TABSTOP|
			WS_CHILD|WS_BORDER|TVS_HASBUTTONS|
			TVS_LINESATROOT|TVS_HASLINES);
	CTreeCtrl&	treeCtrl = GetTreeCtrl();
	treeCtrl.DeleteAllItems();
	int n=0;
	HTREEITEM root =treeCtrl.InsertItem(strTitle[n],0,0);
	treeCtrl.SetItemData(root,n);
	n++;
	HTREEITEM subroot = treeCtrl.InsertItem(strTitle[n],1,0,root);
	treeCtrl.SetItemData(subroot,n);
	n++;
	subroot = treeCtrl.InsertItem(strTitle[n],1,0,root);
	treeCtrl.SetItemData(subroot,n);
	n++;
	subroot = treeCtrl.InsertItem(strTitle[n],1,0,root);
	treeCtrl.SetItemData(subroot,n);
	n++;
	subroot = treeCtrl.InsertItem(strTitle[n],1,0,root);
	treeCtrl.SetItemData(subroot,n);
	n++;
	subroot = treeCtrl.InsertItem(strTitle[n],1,0,root);
	treeCtrl.SetItemData(subroot,n);
	n++;
	subroot = treeCtrl.InsertItem(strTitle[n],1,0,root);
	treeCtrl.SetItemData(subroot,n);
	n++;

	treeCtrl.Expand(root,TVE_EXPAND);
}
