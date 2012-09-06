/*******************************************************************************
*   File Name: mybar.cpp 

*   Description:  implementation file

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
#include "MainFrm.h"

#include "mybar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// mybar

mybar::mybar()
{m_wnd = NULL;
}

mybar::~mybar()
{
}


BEGIN_MESSAGE_MAP(mybar, CSizingControlBar)
	//{{AFX_MSG_MAP(mybar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, ID_TREECTRL, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// mybar message handlers

void mybar::OnUpdateCmdUI(CFrameWnd *pTarget, BOOL bDisableIfNoHndler)
{
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

int mybar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_TreeCtrl.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
	//	| TVS_DISABLEDRAGDROP|TVS_EDITLABELS
	|TVS_TRACKSELECT,
		CRect(10, 10, 300, 100), this, ID_TREECTRL);//create tree control
	
	
	//	m_TreeCtrl.SetImageList(&m_images,TVSIL_NORMAL);
	// set "normal" GUI-font
	CFont *font = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
	m_TreeCtrl.SetFont(font);
	int n=0;
	HTREEITEM root = m_TreeCtrl.InsertItem("LT1000B",0,0);
    m_TreeCtrl.SetItemData(root, 0);
	m_hItem[n++] = root;
	HTREEITEM subroot1=m_TreeCtrl.InsertItem("系统信息",1,1,root);
    m_TreeCtrl.SetItemData(subroot1, 1);
	m_hItem[n++] = subroot1;
	HTREEITEM subroot2=m_TreeCtrl.InsertItem("按键设置",1,1,root);
    m_TreeCtrl.SetItemData(subroot2, 2);
	m_hItem[n++] = subroot2;
	HTREEITEM subroot3=m_TreeCtrl.InsertItem("系统设置",1,1,root);
    m_TreeCtrl.SetItemData(subroot3, 3);
	m_hItem[n++] = subroot3;
 	HTREEITEM subroot4=m_TreeCtrl.InsertItem("信道信息",1,1,root);
     m_TreeCtrl.SetItemData(subroot4, 4);
 	m_hItem[n++] = subroot4;
 	HTREEITEM subroot5=m_TreeCtrl.InsertItem("扫描列表",1,1,root);
     m_TreeCtrl.SetItemData(subroot5, 5);
 	m_hItem[n++] = subroot5;
 	HTREEITEM subroot6=m_TreeCtrl.InsertItem("DPMR内容",1,1,root);
     m_TreeCtrl.SetItemData(subroot6, 6);
 	m_hItem[n++] = subroot6;

    m_TreeCtrl.SelectItem(root);
	m_TreeCtrl.Expand(root, TVE_EXPAND);
   return 0;
}

void mybar::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControlBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	CRect rc;
	GetClientRect(&rc);
	m_TreeCtrl.MoveWindow(&rc);
}
void mybar::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	int	i;
	UINT	hFlag;
	CPoint	pt;
	GetCursorPos(&pt);

	m_TreeCtrl.ScreenToClient(&pt);
	HTREEITEM	hItem = m_TreeCtrl.HitTest(pt,&hFlag);
	if ((hItem!=NULL)&&(TVHT_ONITEM&hFlag))
	{
		for (i=0;i<100;i++)
		{
			if(hItem == m_hItem[i])
				break;
		}
	}
	else
		i=0;
//	((CMainFrame*)AfxGetMainWnd())->PostMessage(WM_SHOW_WINDOW,MAKELPARAM(this,0),MAKEWPARAM(i,0));
//	HWND	hwnd = GetSafeOwner()->m_hWnd;
//	::SendMessage(hwnd,WM_SHOW_WINDOW,MAKEWPARAM(this,0),(LPARAM)i);
 	((CMainFrame*)AfxGetMainWnd())->ShowChildWindow(0,(LPARAM)i);

}
