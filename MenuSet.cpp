// MenuSet.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "MenuSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuSet

IMPLEMENT_DYNCREATE(CMenuSet, CFormView)

CMenuSet::CMenuSet()
	: CFormView(CMenuSet::IDD)
{
	//{{AFX_DATA_INIT(CMenuSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CheckMenuIDArray[0] = IDC_CHECK_POWERLVL;
	CheckMenuIDArray[1] = IDC_CHECK_KEYPADLOCK;
	CheckMenuIDArray[2] = IDC_CHECK_LANGUAGE;
	CheckMenuIDArray[3] = IDC_CHECK_BGLIGHT;
	CheckMenuIDArray[4] = IDC_CHECK_LED_LIGHT_MENU;
	CheckMenuIDArray[5] = IDC_CHECK_TONE;
	CheckMenuIDArray[6] = IDC_CHECK_BRIGHT;
	CheckMenuIDArray[7] = IDC_CHECK_SMS;
	CheckMenuIDArray[8] = IDC_CHECK_NOISELVL;
	CheckMenuIDArray[9] = IDC_CHECK_CONTACT_DELE;
	CheckMenuIDArray[10] = IDC_CHECK_SCAN;
	CheckMenuIDArray[11] = IDC_CHECK_SCANCHECK;
	CheckMenuIDArray[12] = IDC_CHECK_SCAN_TEMP_ADD;
	CheckMenuIDArray[13] = IDC_CHECK_SCAN_TEMP_DELE;
	CheckMenuIDArray[14] = IDC_CHECK_SCAN_ADD_CH;
	CheckMenuIDArray[15] = IDC_CHECK_SCAN_DELE_CH;
	CheckMenuIDArray[16] = IDC_CHECK_VOX;
	CheckMenuIDArray[17] = IDC_CHECK_WHISPER;
	CheckMenuIDArray[18] = IDC_CHECK_VIBRATE_MENU;
	CheckMenuIDArray[19] = IDC_CHECK_DATE_MENU;
	CheckMenuIDArray[20] = IDC_CHECK_MAINFRAME;
	CheckMenuIDArray[21] = IDC_CHECK_POWERSAVE;
	CheckMenuIDArray[22] = IDC_CHECK_TALKAROUND;
	CheckMenuIDArray[23] = IDC_CHECK_ENHANCE_SPEECH_MENU;
	CheckMenuIDArray[24] = IDC_CHECK_VOICE_ENCRYPT_MENU;
 
}

CMenuSet::~CMenuSet()
{
}

void CMenuSet::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
 	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMenuSet, CFormView)
	//{{AFX_MSG_MAP(CMenuSet)
	ON_WM_CLOSE()
 	ON_WM_DESTROY()
// 	ON_MESSAGE(WM_UPDATE_ALLDATA,OnUpdate)
	ON_BN_CLICKED(IDC_CHECK_SCAN, OnCheckScan)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHECK_TALKAROUND,IDC_CHECK_VOICE_ENCRYPT_MENU,OnClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuSet diagnostics

#ifdef _DEBUG
void CMenuSet::AssertValid() const
{
	CFormView::AssertValid();
}

void CMenuSet::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMenuSet message handlers
void	CMenuSet::LoadData()
{
	BOOL bMenu;//[0x18] = {-1};
	for(int i=0;i<0x18;i++)
	{
		bMenu  = ((CPCSWDoc*)GetDocument())->GetMenuEnable(MenuPowerLvl+i);
		((CButton*)GetDlgItem(CheckMenuIDArray[i]))->SetCheck(bMenu);
	}
		bMenu  = ((CPCSWDoc*)GetDocument())->GetMenuKill(MenuAllowKill);
		((CButton*)GetDlgItem(IDC_CHECK_ALLOW_KILL))->SetCheck(bMenu);
 		bMenu  = ((CPCSWDoc*)GetDocument())->GetmenuActive(MenuAllowActive);
		((CButton*)GetDlgItem(IDC_CHECK_ALLOW_UNKILL))->SetCheck(bMenu);
}
// LRESULT CMenuSet::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
// {
// 	// TODO: Add your specialized code here and/or call the base class
// // 	LoadData();
// //	UpdateData(FALSE);
// 	return 0;	
// }

void CMenuSet::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CMDIChildWnd* pForm;
	pForm = (CMDIChildWnd*)GetParentFrame();
	CRect rect1;
	pForm->GetWindowRect(&rect1);
	pForm->ScreenToClient(&rect1);
	rect1.OffsetRect(5,30);
// 	pForm->MoveWindow(rect1);/**/
// 	LoadData();
	
}

void CMenuSet::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
 //	CFormView::OnClose();
}

void CMenuSet::OnDestroy() 
{
//	CFormView::OnDestroy();
// #ifndef SPLIT_TEST
// 
// 	ShowWindow(SW_HIDE);
// 	if(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(1)!=NULL)
// 		((CPCSWApp*)AfxGetApp())->m_Frame.SetAt(1,NULL);
// 
// #endif	
	// TODO: Add your message handler code here
	
}

void CMenuSet::OnCheckScan() 
{
	// TODO: Add your control notification handler code here
	int bPressed = ((CButton*)GetDlgItem(IDC_CHECK_SCAN))->GetCheck();
	if (bPressed == 1)//若是按下的
	{
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_ADD_CH))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SCANCHECK))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_DELE_CH))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_TEMP_ADD))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_TEMP_DELE))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_ADD_CH))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SCANCHECK))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_DELE_CH))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_TEMP_ADD))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SCAN_TEMP_DELE))->SetCheck(FALSE);
	}
}
void	CMenuSet::OnClick(UINT uID)
{
	int	bPressed = ((CButton*)GetDlgItem(uID))->GetCheck();
//	if (bPressed)
	{
		((CPCSWDoc*)GetDocument())->SetAllMenuValue(uID,bPressed);
	}
}
