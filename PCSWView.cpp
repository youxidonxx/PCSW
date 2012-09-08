// PCSWView.cpp : implementation of the CPCSWView class
//

#include "stdafx.h"
#include "PCSW.h"
#include "MainFrm.h"
#include "PCSWDoc.h"
#include "PCSWView.h"
#include "COMSET.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	CPCSWApp	theApp;
static	CString	strFreqScole[] = {"136M-150M","150M-174M","400M-470M","400M-425M"};
/////////////////////////////////////////////////////////////////////////////
// CPCSWView

IMPLEMENT_DYNCREATE(CPCSWView, CFormView)

BEGIN_MESSAGE_MAP(CPCSWView, CFormView)
	//{{AFX_MSG_MAP(CPCSWView)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_FREQ_RANGE, OnSelchangeComboFreqRange)
// 	ON_COMMAND(WM_UPDATE_ALLDATA,OnUpdate)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCSWView construction/destruction

CPCSWView::CPCSWView()
	: CFormView(CPCSWView::IDD)
{
	//{{AFX_DATA_INIT(CPCSWView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CPCSWView::~CPCSWView()
{
}

void CPCSWView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPCSWView)
	DDX_Control(pDX, IDC_COMBO_FREQ_RANGE, m_cbFreqScope);
	DDX_Control(pDX, IDC_EDIT_DATA_VERSION, m_editDATAVer);
	DDX_Control(pDX, IDC_EDIT_VISION_VERSION, m_editVIVer);
	DDX_Control(pDX, IDC_EDIT_SW_VERSION, m_editSWVer);
	DDX_Control(pDX, IDC_EDIT_MACHINE_TYPE, m_editProtype);
	DDX_Control(pDX, IDC_EDIT_SERIALNUM, m_editSerialNum);
	//}}AFX_DATA_MAP
}

BOOL CPCSWView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	HBRUSH	hBrush = CreateSolidBrush(RGB(200,200,192));
	LPCSTR	lpMyClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_OWNDC,
					0,hBrush);

	cs.lpszClass = lpMyClass;

	cs.style &= ~WS_SYSMENU; 
	return TRUE;//return CFormView::PreCreateWindow(cs);
}

void CPCSWView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
//	ResizeParentToFit();
// 	((CPCSWApp*)AfxGetApp())->m_Frame.SetAt(0,GetParentFrame()); //保存第一个窗口
// 	CMDIChildWnd* pForm;
// 	pForm = (CMDIChildWnd*)GetParentFrame();
// 	CRect rect1;
// 	pForm->GetWindowRect(&rect1);
// 	pForm->ScreenToClient(&rect1);
// 	rect1.OffsetRect(5,30);
// 	pForm->MoveWindow(rect1);
// 
	m_cbFreqScope.ResetContent();
	m_editSerialNum.SetLimitText(16);
	m_editProtype.SetLimitText(8);
	m_editDATAVer.SetLimitText(7);
	m_editSWVer.SetLimitText(7);
	m_editVIVer.SetLimitText(7);
	for(int i=0;i<sizeof(strFreqScole)/sizeof(strFreqScole[0]);i++)
		m_cbFreqScope.AddString(strFreqScole[i]);
	m_cbFreqScope.SetCurSel(0);
  	LoadData();
}

/////////////////////////////////////////////////////////////////////////////
// CPCSWView diagnostics

#ifdef _DEBUG
void CPCSWView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPCSWView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPCSWDoc* CPCSWView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSWDoc)));
	return (CPCSWDoc*)m_pDocument;
}
#endif //_DEBUG
void	CPCSWView::UpdateWindow()
{
	LoadData();
}
/////////////////////////////////////////////////////////////////////////////
// CPCSWView message handlers
 
void	CPCSWView::LoadData()
{
// 	CMainFrame*	pFrame = (CMainFrame*)AfxGetMainWnd();
	if (theApp.m_CommInfo.bHasInfo)
	{
		CString		str;
		str = GetAllVersion(Swver,SwverBytes);
		m_editSWVer.SetWindowText(str);
		str = GetAllVersion(Dataver,DataBytes);
		m_editDATAVer.SetWindowText(str);
		str = GetAllVersion(Appver,AppverBytes);
		m_editVIVer.SetWindowText(str);
		str = GetProtypeOrSerial(Protype,ProtypeBytes);
		m_editProtype.SetWindowText(str);
		str = GetProtypeOrSerial(Serialnum,SerialnumBytes);
		m_editSerialNum.SetWindowText(str);

		int nFreq  = GetFreqScope();
		if(nFreq>=0 && nFreq<=3)
			m_cbFreqScope.SetCurSel(nFreq);
		else
			m_cbFreqScope.SetCurSel(-1);
	}
#if 0
		CPCSWDoc*	pDoc = (CPCSWDoc*)GetDocument();
			CString strTemp  = pDoc->GetSerialNumber();
			if(!strTemp.IsEmpty() && (strTemp.GetLength()==8))
			{
				CString str;
				str.Format("%d.%d.%d.%d",atoi(strTemp.Left(2)),atoi(strTemp.Mid(2,2)),atoi(strTemp.Mid(4,2)),atoi(strTemp.Right(2)));
				strTemp = str;
			}
			m_editSerialNum.SetWindowText(strTemp);
		
			strTemp = pDoc->GetProtype();
			m_editProtype.SetWindowText(strTemp);
		
			strTemp = pDoc->GetSWVer();
			if(!strTemp.IsEmpty() && (strTemp.GetLength()==8))
			{
				CString str;
				str.Format("%d.%d.%d.%d",atoi(strTemp.Left(2)),atoi(strTemp.Mid(2,2)),atoi(strTemp.Mid(4,2)),atoi(strTemp.Right(2)));
				strTemp = str;
			}
			m_editSWVer.SetWindowText(strTemp);
		
			strTemp = pDoc->GetDataVer();
			if(!strTemp.IsEmpty() && (strTemp.GetLength()==8))
			{
				CString str;
				str.Format("%d.%d.%d.%d",atoi(strTemp.Left(2)),atoi(strTemp.Mid(2,2)),atoi(strTemp.Mid(4,2)),atoi(strTemp.Right(2)));
				strTemp = str;
			}
			m_editDATAVer.SetWindowText(strTemp);
		
			strTemp = pDoc->GetAppVer();
			if(!strTemp.IsEmpty() && (strTemp.GetLength()==8))
			{
				CString str;
				str.Format("%d.%d.%d.%d",atoi(strTemp.Left(2)),atoi(strTemp.Mid(2,2)),atoi(strTemp.Mid(4,2)),atoi(strTemp.Right(2)));
				strTemp = str;
			}
			m_editVIVer.SetWindowText(strTemp);
		
			int sel = pDoc->GetFreqScope();
			m_cbFreqScope.SetCurSel(sel);
			return;	
#endif

}
// void CPCSWView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
// {
// 	// TODO: Add your specialized code here and/or call the base class
// 	
// //	LoadData();
//  	return;
// }
int CPCSWView::GetFreqScope()
{
	int	nRet = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[Freqscope]+((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[Freqscope+1]*256;
	return (nRet-1);
}
CString		CPCSWView::GetProtypeOrSerial(int nFlag,int nLen)
{
	CString	str = _T("");
	if (memcmp(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[0x00+nFlag],"\x00",1)!=0)
	{
		str.Format("%s",&((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[0x00+nFlag]);
	}
	if(str.GetLength()>nLen)
		str = str.Left(nLen);
	return str;
}
CString	CPCSWView::GetAllVersion(int nFlag,int nLen)
{
	CString	str = _T("");
	byte	data[10];
	for(int i=0;i<nLen;i++)
		data[i] = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[0x00+nFlag+nLen-i-1];//pRadioInfo[Swver+SwverBytes-i-1];
	str.Format("%d.%d.%d.%x",data[0],data[1],data[2],data[3]);
	return str;
	
}
void CPCSWView::OnDestroy() 
{
//	CFormView::OnDestroy();
/*	this->ShowWindow(SW_HIDE);
	if(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(0)!=NULL)
		((CPCSWApp*)AfxGetApp())->m_Frame.SetAt(0,NULL);
	CDocTemplate*	pTmp ;
	pTmp = (CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0];
		POSITION	pos;
	pos = pTmp->GetFirstDocPosition();
	if (pos == NULL)
	{
		pTmp->AddDocument(GetDocument());
	}
	// TODO: Add your message handler code here
*/	
}

void CPCSWView::OnSelchangeComboFreqRange() 
{
	// TODO: Add your control notification handler code here
	int nSel = ((CPCSWApp*)AfxGetApp())->GetFreqScope();
		//GetDocument()->GetFreqScope();
	if (nSel == m_cbFreqScope.GetCurSel())
	{
		return;
	}
	else
	{
		if (MessageBox("确认要重新输入数据，并将删除当前保存的所有数据！","提示",MB_OKCANCEL|MB_ICONEXCLAMATION) == IDOK)
		{
			((CPCSWApp*)AfxGetApp())->SetFreqScope(m_cbFreqScope.GetCurSel()+1);
// 			GetDocument()->SetFreqScope(nSel+1);
// 			GetDocument()->UpdateAllViews(NULL);
		}
		else
			m_cbFreqScope.SetCurSel(nSel);
	}
}
 

void CPCSWView::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
 	CFormView::OnClose();
}

//void CPCSWView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	LoadData();
//}
