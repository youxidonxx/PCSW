// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PCSW.h"

#include "MainFrm.h"
#include "spstruct.h"
#include "COMSET.h"
#include "PCSWView.h"
#include "PCSWDoc.h"
#include "MenuSet.h"
#include "RadioSetView.h"
#include "ScanView.h"
#include "ZoneInfo.h"
#include "DpmrView.h"
#include "mybar.h"
#include "MyTree1.h"
#include "MenuKeyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern	CPCSWApp	theApp;
 /////////////////////////////////////////////////////////////////////////////
// CMainFrame

COMM_EVENT	iCommEvent;
SpPcConnect_S* connectreq = new SpPcConnect_S;	
SpPckeyReq_S*	keyreq = new SpPckeyReq_S;
SpPckeyReq_S*	keyWriteReq = new SpPckeyReq_S;
SpPcWriteSysSet_S*	WriteSyssetReq = new SpPcWriteSysSet_S;
SpPcWriteZone_S*	WriteZoneReq = new SpPcWriteZone_S;
SpPcWriteChannl_S*	WriteChReq = new SpPcWriteChannl_S;
SpPcWriteScan_S*	WriteScanReq = new SpPcWriteScan_S;
SpPcWriteContct_S*	WriteContactReq = new SpPcWriteContct_S;
SpPcWriteGrp_S*		WriteGroupReq = new SpPcWriteGrp_S;
SpPcWriteTxt_S*		WriteTextReq = new SpPcWriteTxt_S;

SpPcEffect_S*	effectreq = new SpPcEffect_S;
SpPcRead_S*	readreq = new SpPcRead_S;
SpPcReadSyssetCnf_S*	syssetcnf = new SpPcReadSyssetCnf_S;
SpPcReadZoneCnf_S*		zonecnf = new SpPcReadZoneCnf_S;
SpPckeyCnf_S*		keyCnf = new SpPckeyCnf_S;
int		WriteParameter(byte* szBuff,COMM_EVENT*	pEvent);
UINT	ThraedComm(LPVOID	lpParam);

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_READ_PARAMETER, OnReadParameter)
	ON_COMMAND(ID_COMM_SET, OnCommSet)
	ON_UPDATE_COMMAND_UI(ID_READ_PARAMETER, OnUpdateReadParameter)
	ON_COMMAND(ID_WRITE_PARAMETER, OnWriteParameter)
	ON_UPDATE_COMMAND_UI(ID_WRITE_PARAMETER, OnUpdateWriteParameter)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_MESSAGE(WM_SHOW_WINDOW,ShowChildWindow)
	ON_MESSAGE(WM_UPDATE,OnUpdateViews)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nComm = 0;
	m_nPaud = 0;
	m_nPaud = 115200;
	m_nViewIndex = 1;
	m_bReadyComm = false;
// 	m_CommInfo.bHasInfo = false;
}

CMainFrame::~CMainFrame()
{
	if(m_SerialPort.IsOpen())
		m_SerialPort.CloseComm();
//	__PCTrace(0x20,"\n.................~CMainFrame.........\n");
}
long	swapData(long data,int len)
{
	long	tmp = 0;
	if (len == 4)//0x0000类型
	{
		tmp = (data <<8)|(data>>8);
		return tmp;
	}
	else if (len == 8)//0x0000 0000
	{
		int rightTmp = (int)(data>>16);
		int leftTmp = (int)(data );
		rightTmp = (rightTmp<<8)|(rightTmp>>8);
		leftTmp = (leftTmp<<8)|(leftTmp>>8);
		
		tmp = (long)rightTmp<<16 |(long)leftTmp;
		return tmp;
	}
	return 0;
}
void	InitData()//根据写频接口规范
{
	//参数生效请求
	effectreq->ReceiverMID	= swapData(SYS_MODULE_SP,4  );
	effectreq->SenderMID	=swapData(SYS_MODULE_PCSW,4 );
	effectreq->MsgTYPE		=MAINTAINANCE;
	effectreq->MsgID		=PC_SP_EFFECT_REQ;
	effectreq->MsgLen		=0x0004;
	effectreq->reset		=0x12201220;
	effectreq->CRC			=0x55aa;
	//连接请求
   connectreq->ReceiverMID = swapData(SYS_MODULE_SP,4  );
   connectreq->SenderMID = swapData(SYS_MODULE_PCSW,4 );
   connectreq->MsgTYPE = MAINTAINANCE; 
   connectreq->MsgID =PC_SP_CONNECT_REQ; 
   connectreq->MsgLen = 0x0004; 
   connectreq->connect = 0x09260926; 
   connectreq->CRC = 0xffff;
	//密码请求
	keyreq->ReceiverMID = swapData(SYS_MODULE_SP,4  );
	keyreq->SenderMID	= swapData(SYS_MODULE_PCSW,4 );
	keyreq->MsgTYPE		= MAINTAINANCE;
	keyreq->MsgID		= PC_SP_KEY_REQ;
	keyreq->MsgLen		= 0x0002;
	keyreq->keytype		= 0x0000;
	keyreq->CRC			= 0xffff;
	//写频密码请求 keyWriteReq
	keyWriteReq->ReceiverMID = swapData(SYS_MODULE_SP,4  );
	keyWriteReq->SenderMID	= swapData(SYS_MODULE_PCSW,4 );
	keyWriteReq->MsgTYPE		= MAINTAINANCE;
	keyWriteReq->MsgID		= PC_SP_KEY_REQ	;
	keyWriteReq->MsgLen		= 0x0002;
	keyWriteReq->keytype		= 0x0001;//写频
	keyWriteReq->CRC			= 0xffff;

	//读请求
	readreq->ReceiverMID	= swapData(SYS_MODULE_SP,4  );
	readreq->SenderMID		= swapData(SYS_MODULE_PCSW,4 );
	readreq->MsgTYPE		=MAINTAINANCE;
	readreq->MsgID			= PC_SP_READ_REQ;
	readreq->MsgLen			= 0x0008;
	readreq->readkey		= 0x0000;//需要修改		
	readreq->modul			= 0x00000000;//需要改动
	readreq->CRC			= 0xffff;
	//写系统参数请求
	ZeroMemory(WriteSyssetReq,sizeof(SpPcWriteSysSet_S));
	WriteSyssetReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteSyssetReq->SenderMID	=swapData(SYS_MODULE_PCSW,4 );
	WriteSyssetReq->MsgTYPE		=MAINTAINANCE;
	WriteSyssetReq->MsgID		=PC_SP_WTSYSSET_REQ;
	WriteSyssetReq->MsgLen		=0x0094;
	WriteSyssetReq->CRC			=0xffff;

	//写区域请求
	ZeroMemory(WriteZoneReq,sizeof(SpPcWriteZone_S));
	WriteZoneReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteZoneReq->SenderMID	=swapData(SYS_MODULE_PCSW,4 );
	WriteZoneReq->MsgTYPE		=MAINTAINANCE;
	WriteZoneReq->MsgID		=PC_SP_WTZONE_REQ;
	WriteZoneReq->MsgLen		=0x0124;
	WriteZoneReq->CRC			=0xffff;
	//写信道消息请求
	ZeroMemory(WriteChReq,sizeof(SpPcWriteCnf_S));
	WriteChReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteChReq->SenderMID	=swapData(SYS_MODULE_PCSW,4 );
	WriteChReq->MsgTYPE		=MAINTAINANCE;
	WriteChReq->MsgID		=PC_SP_WTCHANNEL_REQ;
	WriteChReq->MsgLen		=0x02e6;
	WriteChReq->CRC			=0xffff;

	//写扫描信息请求
	ZeroMemory(WriteScanReq,sizeof(SpPcWriteScan_S));
	WriteScanReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteScanReq->SenderMID		=swapData(SYS_MODULE_PCSW,4 );
	WriteScanReq->MsgTYPE		=MAINTAINANCE;
	WriteScanReq->MsgID			=PC_SP_WTSCAN_REQ;
	WriteScanReq->MsgLen		=0x0786;
//	WriteScanReq->CRC			=0xffff;

	//写联系人请求
	ZeroMemory(WriteContactReq,sizeof(SpPcWriteContct_S));
	WriteContactReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteContactReq->SenderMID		=swapData(SYS_MODULE_PCSW,4 );
	WriteContactReq->MsgTYPE		=MAINTAINANCE;
	WriteContactReq->MsgID			=PC_SP_WTCONTACT_REQ;
	WriteContactReq->MsgLen			=0x1136;
//	WriteContactReq->CRC			=0xffff;

	//组呼列表请求
	ZeroMemory(WriteGroupReq,sizeof(SpPcWriteGrp_S));
	WriteGroupReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteGroupReq->SenderMID		=swapData(SYS_MODULE_PCSW,4 );
	WriteGroupReq->MsgTYPE		=MAINTAINANCE;
	WriteGroupReq->MsgID			=PC_SP_WTGROUP_REQ;
	WriteGroupReq->MsgLen			=0x0446;
 //	WriteGroupReq->CRC			=0xffff;

	//文本内容请求
	ZeroMemory(WriteTextReq,sizeof(SpPcWriteTxt_S));
	WriteTextReq->ReceiverMID	=swapData(SYS_MODULE_SP,4  );
	WriteTextReq->SenderMID		=swapData(SYS_MODULE_PCSW,4 );
	WriteTextReq->MsgTYPE		=MAINTAINANCE;
	WriteTextReq->MsgID			=PC_SP_WTTEXT_REQ;
	WriteTextReq->MsgLen			=0x1faa;
 //	WriteGroupReq->CRC			=0xffff;

}

void	CMainFrame::TransferCommData()
{
	theApp.m_CommInfo.bHasInfo = true;
	memcpy(&theApp.m_CommInfo.pRadioInfo,iCommEvent.pRadioInfo,sizeof(theApp.m_CommInfo.pRadioInfo));
	memcpy(&theApp.m_CommInfo.pRadioSetting,iCommEvent.pRadioSetting,sizeof(theApp.m_CommInfo.pRadioSetting));
	memcpy(&theApp.m_CommInfo.pEmergencySetting,iCommEvent.pEmergencySetting,sizeof(theApp.m_CommInfo.pEmergencySetting));
	memcpy(&theApp.m_CommInfo.pRadioInfo,iCommEvent.pRadioInfo,sizeof(theApp.m_CommInfo.pRadioInfo));
	memcpy(&theApp.m_CommInfo.pRadioSetting,iCommEvent.pRadioSetting,sizeof(theApp.m_CommInfo.pRadioSetting));
	memcpy(&theApp.m_CommInfo.pEmergencySetting,iCommEvent.pEmergencySetting,sizeof(theApp.m_CommInfo.pEmergencySetting));
	memcpy(&theApp.m_CommInfo.pMenuSetting,iCommEvent.pMenuSetting,sizeof(theApp.m_CommInfo.pMenuSetting));
	memcpy(&theApp.m_CommInfo.pKeyFunctionSetting,iCommEvent.pKeyFunctionSetting,sizeof(theApp.m_CommInfo.pKeyFunctionSetting));
	memcpy(&theApp.m_CommInfo.pZoneInfo,iCommEvent.pZoneInfo,sizeof(theApp.m_CommInfo.pZoneInfo));
	memcpy(&theApp.m_CommInfo.pChannelInfo,iCommEvent.pChannelInfo,sizeof(theApp.m_CommInfo.pChannelInfo));
	memcpy(&theApp.m_CommInfo.pScanInfo,iCommEvent.pScanInfo,sizeof(theApp.m_CommInfo.pScanInfo));
	memcpy(&theApp.m_CommInfo.pContactInfo,iCommEvent.pContactInfo,sizeof(theApp.m_CommInfo.pContactInfo));
	memcpy(&theApp.m_CommInfo.pGroupList,iCommEvent.pGroupList,sizeof(theApp.m_CommInfo.pGroupList));
	memcpy(&theApp.m_CommInfo.pShortText,iCommEvent.pShortText,sizeof(theApp.m_CommInfo.pShortText));

// 	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
// 	((CPCSWApp*)AfxGetApp())->UpdateActiveView();
}
LRESULT	CMainFrame::OnUpdateViews(WPARAM wparam,LPARAM lparam)
{
	((CPCSWApp*)AfxGetApp())->UpdateActiveView();
	CView*	pView = (CView*)m_wndSplit.GetPane(0,1);
	CRect	rectView,rectFrm;
	pView->GetClientRect(&rectView);
	GetClientRect(&rectFrm);
	int nIndex = m_nViewIndex;
	switch(nIndex)
	{
	case 1:
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CPCSWView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CPCSWView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CPCSWView)pView->LoadData();
			}
		}
		break;
	case 2:
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CMenuKeyView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CMenuKeyView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CMenuKeyView*)pView->LoadData();
			}
		}
		break;
	case 3:
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CRadioSetView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CRadioSetView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CRadioSetView*)pView->LoadData();
			}
		}
		break;
	case 4:
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CScanView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CScanView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CScanView*)pView->LoadData();
			}
		}
		break;
	case 5:
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CZoneInfo)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CZoneInfo),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CZoneInfo*)pView->LoadData();
			}
		}
		break;
	case 6:
		{
			if (pView->IsKindOf(RUNTIME_CLASS(CDpmrView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CDpmrView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CDpmrView*)pView->LoadData();
			}
		}
		break;
	default:
		{
			if (!pView->IsKindOf(RUNTIME_CLASS(CPCSWView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CRadioSetView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				// 				(CPCSWView*)pView->LoadData();
			}
		}
		break;
	}
	return true;
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

#ifndef SPLIT_TEST
	if(!m_CtrlBar.Create("LT1000B写频软件",this, CSize(200,200),TRUE,123))
	{
		TRACE0("Failed to create mybar\n");
		return -1;
		// fail to create
	}
	m_CtrlBar.SetBarStyle(m_CtrlBar.GetBarStyle()|
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_CtrlBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_CtrlBar,AFX_IDW_DOCKBAR_LEFT);
#endif


	InitData();
//	m_pSWView = new CPCSWView;
//	m_pSWView->ShowWindow(SW_HIDE);
#ifdef _DEBUG
//	AllocConsole();
//	SetConsoleCtrlHandler(NULL,TRUE);
#endif	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void	CMainFrame::UpdateAllViews(int nFlag)
{
// 	POSITION	pos;
// 	CPCSWDoc*	pDoc = GetDocument();
// 	pos = ((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetFirstDocPosition();
// 	pDoc = (CPCSWDoc*)((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetNextDoc(pos);
// 	if(nFlag==1)
// 	{
//  //	pDoc->pRadioInfo	= iCommEvent.pRadioInfo;
// 	memcpy(&pDoc->pRadioInfo,iCommEvent.pRadioInfo,sizeof(pDoc->pRadioInfo));
// //	pDoc->pRadioSetting = iCommEvent.pRadioSetting;
// 	memcpy(&pDoc->pRadioSetting,iCommEvent.pRadioSetting,sizeof(pDoc->pRadioSetting));
// //	pDoc->pEmerSetting	= iCommEvent.pEmergencySetting;
// 	memcpy(&pDoc->pEmerSetting,iCommEvent.pEmergencySetting,sizeof(pDoc->pEmerSetting));
// //	pDoc->pMenuSetting	= iCommEvent.pMenuSetting;
// 	memcpy(&pDoc->pMenuSetting,iCommEvent.pMenuSetting,sizeof(pDoc->pMenuSetting));
// //	pDoc->pKeySetting	= iCommEvent.pKeyFunctionSetting;
// 	memcpy(&pDoc->pKeySetting,iCommEvent.pKeyFunctionSetting,sizeof(pDoc->pKeySetting));
// //	pDoc->pZoneInfo		= iCommEvent.pZoneInfo;
// 	memcpy(&pDoc->pZoneInfo,iCommEvent.pZoneInfo,sizeof(pDoc->pZoneInfo));
// //	pDoc->pChannelInfo	= iCommEvent.pChannelInfo;
// 	memcpy(&pDoc->pChannelInfo,iCommEvent.pChannelInfo,sizeof(pDoc->pChannelInfo));
// //	pDoc->pScanInfo		= iCommEvent.pScanInfo;
// 	memcpy(&pDoc->pScanInfo,iCommEvent.pScanInfo,sizeof(pDoc->pScanInfo));
// //	pDoc->pContact		= iCommEvent.pContactInfo;
// 	memcpy(&pDoc->pContact,iCommEvent.pContactInfo,sizeof(pDoc->pContact));
// //	pDoc->pGrouplist	= iCommEvent.pGroupList;
// 	memcpy(&pDoc->pGrouplist,iCommEvent.pGroupList,sizeof(pDoc->pGrouplist));
// //	pDoc->pShortText	= iCommEvent.pShortText;
// 	memcpy(&pDoc->pShortText,iCommEvent.pShortText,sizeof(pDoc->pShortText));
// 	}
// /**/	MessageBox("界面已更新","读频",MB_OK|MB_ICONINFORMATION|MB_TOPMOST);
// 
// //	pDoc = (CPCSWDoc*)((((CFrameWnd*)((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(0)))->GetActiveDocument());
// 	if(nFlag==1)
// 		UpdateViewData();//pDoc->UpdateAllViews(NULL);
// //	else

//	pDoc->NotifyUpdateMsg();
}
void	CMainFrame::UpdateViewData()
{
	POSITION	pos;
	CPCSWDoc*	pDoc = GetDocument();
	pos = ((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetFirstDocPosition();
	pDoc = (CPCSWDoc*)((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetNextDoc(pos);
        CDocument   *pclsDoc = NULL;
        CView       *pclsView  = NULL;
        POSITION    posV;

		while(pos)
		{
			posV = pDoc->GetFirstViewPosition();
			pclsView = pDoc->GetNextView(posV);
  //          ASSERT(pclsView->IsKindOf(RUNTIME_CLASS(CLTraceView)));
			pclsView->PostMessage(WM_COMMAND,WM_UPDATE_ALLDATA,0);
		}
	
}
void CMainFrame::OnReadParameter() 
{
	// TODO: Add your command handler code here
	if (m_nComm == 0||m_nComm == 1)
	{
		AfxMessageBox("请先选择串口！");
		return;
	}
	if(!m_bReadyComm)
		return;
	m_SerialPort.m_nPort = m_nComm;
	m_SerialPort.m_nPaud = m_nPaud;
	if (!m_SerialPort.IsOpen())
	{
		if(!m_SerialPort.OpenComm(m_nComm,m_nPaud))
		{	
			MessageBox("串口错误，请检查串口","端口选择",MB_ICONERROR|MB_OK);
			return;
		}
	}
 	iCommEvent.pMainframe =  (CMainFrame*)AfxGetMainWnd();
	iCommEvent.bRead = TRUE;
	iCommEvent.pSerial = &m_SerialPort;
	iCommEvent.hWnd = m_hWnd;

	iCommEvent.pRadioInfo = theApp.m_CommInfo.pRadioInfo;
		//GetDocument()->pRadioInfo;
	iCommEvent.pRadioSetting = theApp.m_CommInfo.pRadioSetting;
		//GetDocument()->pRadioSetting;
	iCommEvent.pMenuSetting = theApp.m_CommInfo.pMenuSetting;
		//GetDocument()->pMenuSetting;
	iCommEvent.pEmergencySetting = theApp.m_CommInfo.pEmergencySetting;
		//GetDocument()->pEmerSetting;
	iCommEvent.pKeyFunctionSetting = theApp.m_CommInfo.pKeyFunctionSetting;
		//GetDocument()->pKeySetting;


	iCommEvent.pZoneInfo =theApp.m_CommInfo.pZoneInfo;
		//GetDocument()->pZoneInfo;
	iCommEvent.pChannelInfo = theApp.m_CommInfo.pChannelInfo;
		//GetDocument()->pChannelInfo;
	iCommEvent.pScanInfo = theApp.m_CommInfo.pScanInfo;
		//GetDocument()->pScanInfo;
	iCommEvent.pContactInfo = theApp.m_CommInfo.pContactInfo;
		//GetDocument()->pContact;
	iCommEvent.pGroupList = theApp.m_CommInfo.pGroupList;
		//GetDocument()->pGrouplist;
	iCommEvent.pShortText = theApp.m_CommInfo.pShortText;
		//GetDocument()->pShortText;

	ZeroMemory(iCommEvent.bChannelExist,16);//防止有信道没有被设置
	ZeroMemory(iCommEvent.bZoneExist,16);	//防止有区域没有被设置

	iCommEvent.szPara[0] = iCommEvent.szPara[1] = 0x5f;
	iCommEvent.szPara[2] = 0x10;iCommEvent.szPara[3] = 0x00;
	iCommEvent.szPara[20] = 0x55;iCommEvent.szPara[21]= 0xaa;
	memcpy(iCommEvent.szPara+4,effectreq,sizeof(SpPcEffect_S));

	m_pThread = AfxBeginThread(ThraedComm,&iCommEvent);

}
UINT	ThraedComm(LPVOID lpParam)
{
	COMM_EVENT*	pEvent = (COMM_EVENT*)lpParam;
	CWaitCursor	wc;

	int	i,len = 22;
	BYTE	szBuff[0x2000];
	int		nRcvChar;

	if (!pEvent->pSerial->IsOpen())
	{
		pEvent->pSerial->OpenComm(pEvent->pSerial->m_nPort,pEvent->pSerial->m_nPaud);
	}
	Sleep(100);
//	for (i=1;i<300;i++)
	{
		//发送3次请求并检测传输数据，只要有一次建立即可继续运行
		for (int k=0;k<3;k++)
		{
			//打开串口之后，一直等待串口数据传出来，有数据之后，才继续往下运行
// 			while(pEvent->pSerial->ReadCommData(0)>=0);
 				
			//小端模式，无法直接赋值，需要对数值改形式
			//建立连接请求
			//5F 5F 10 00 00 03 00 2B 02 00 8F 11 04 00 26 09 26 09 FF FF 55 AA==22byte
			szBuff[0] = szBuff[1] = 0x5f;
			szBuff[2] = 0x10;szBuff[3] = 0x00;
			szBuff[20] = 0x55; szBuff[21] = 0xaa;
			memcpy(szBuff+4,connectreq,sizeof(SpPcConnect_S));
			int returnNum = pEvent->pSerial->WriteCommData(szBuff,22,1,0);

			//接收下位机数据，应该为建立连接响应SpConnectCnF
			//当结构变化后，灵活转换
			if (len!= sizeof(SpPcConCnf_S)+6)
			{
				 len = sizeof(SpPcConCnf_S)+6;
			}
			//返回的数据
			//5F 5F 10 00 00 2B 00 03 02 00 90 11 04 00 01 00 00 00 FF FF 55 AA
			nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
			SpPcConCnf_S*	spReadCnf = (SpPcConCnf_S*)(szBuff+4);
			//判断返回值是否连接成功
			if((nRcvChar == 22)&&(spReadCnf->ready == 0x01))
				break;
			if (pEvent->bCancel)
			{
				pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
				AfxMessageBox("连接失败");
				
				wc.Restore();

				return 0;
			}
		}//end for k<3
	}//end for i==300	
		if (pEvent->bRead)
		{//读频处理
 			AfxMessageBox("准备读频");
			//密码请求
			// 5F 5F 0E 00 00 03 00 2B 02 00 91 11 02 00 00 00 FF FF 55 AA 
			szBuff[0] = szBuff[1] = 0x5f;
			szBuff[2] = 0x0e;szBuff[3] = 0x00;
			szBuff[18] = 0x55; szBuff[19] = 0xaa;
			memcpy(szBuff+4,keyreq,sizeof(SpPckeyReq_S));
			pEvent->pSerial->WriteCommData(szBuff,20,1,0);
			if (len!= sizeof(SpPckeyCnf_S)+6)
			{
				 len = sizeof(SpPckeyCnf_S)+6;//26
			}
			//26 byte
			//5F 5F 14 00 00 2B 00 03 02 00 92 11 08 00 00 00 00 00 FF FF FF FF FF FF 55 AA 
			nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
			if (nRcvChar == 26)
			{//若读频密码是打开的，且与对讲机密码不一致，则提示出错
				if (szBuff[16] == 0x01)
				{
					byte* code = new byte[4];
					memcpy(code,(pEvent->pRadioSetting+0x01),4);
					if (memcmp(szBuff+18,code,4)<0)
					{
						AfxMessageBox("密码错误");
						wc.Restore();
						return 0;
					}
				}
			}
			else
			{//发送参数生效请求
				pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
				return 0;
			}
			if(pEvent->bCancel)
			{
				wc.Restore();
				return 0;
			}

			byte	szPwd[6];
			memcpy(szPwd,szBuff+18,4);
			for(i=1;i<=22;i++)
			{//每一轮数据获取，都需要先发送读取请求，故采用循环
				//1、系统参数;2、区域信息;3-18、区域1-16的信道信息;19、扫描列表;20、联系人;
				//21、组呼列表;22、快捷文本
				Sleep(10);
				pEvent->percent =(int)(i*9/2);
				if(pEvent->bCancel)
					return 0;
				if (i==22)
				{
					Sleep(100);
					pEvent->percent = 100;
				}
				//读请求
				//5F 5F 14 00 00 03 00 2B 02 00 9F 11 08 00 FF FF FF FF 01 00 00 00 FF FF 55 AA
				szBuff[0] = szBuff[1] = 0x5f;
				szBuff[2] = 0x14;szBuff[3] = 0x00;
				szBuff[24] = 0x55; szBuff[25] = 0xaa;
				memcpy(szBuff+4,readreq,sizeof(SpPcRead_S));
				szBuff[18] = i;
				memcpy(szBuff+14,szPwd,4);
				pEvent->pSerial->WriteCommData(szBuff,26,50);

				switch(i)
				{
				case 1://SP_PC_RDSYSSET_CNF SpPcReadSyssetCnf_S
					{
						szBuff[164] = 0x55;szBuff[165] = 0xaa;
						if (len!= sizeof(SpPcReadSyssetCnf_S)+6)
						{
							 len = sizeof(SpPcReadSyssetCnf_S)+6;//164
						}
						len = 166;//V1.3版本
						nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
						if (nRcvChar == 166 && szBuff[14] == 0x01)
						{
							memcpy(pEvent->pRadioInfo,szBuff+18,38);
							memcpy(pEvent->pRadioSetting,szBuff+56,42);
							memcpy(pEvent->pEmergencySetting,szBuff+98,28);
							memcpy(pEvent->pMenuSetting,szBuff+126,25);
							memcpy(pEvent->pKeyFunctionSetting,szBuff+151,11);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							wc.Restore();
							return 0;
						}
					}
					break;
				case 2:
					{//SP_ PC_RDZONE_CNF	SpPcReadZoneCnf_S
						if (len!= sizeof(SpPcReadZoneCnf_S)+6)
						{
							 len = sizeof(SpPcReadZoneCnf_S)+6;//26
						}
						nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
						if (nRcvChar == 310 && szBuff[14] == 0x01)
						{
							memcpy(pEvent->pZoneInfo,szBuff+18,288);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							wc.Restore();
							return 0;
						}
					}//end case
					break;
				case 3://SP_PC_RDCHANNEL_CNF
				case 4:
				case 5:
 				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
					{
						if (len!= sizeof(SpPcReadChanCnf_S)+6)
						{
							 len = sizeof(SpPcReadChanCnf_S)+6;//760
						}
						nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
						if (nRcvChar == 760 && szBuff[14] == 0x01)
						{
							memcpy(pEvent->pChannelInfo+(i-3)*736,szBuff+20,736);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							wc.Restore();
							return 0;
						}

					}
					break;
				case 19://0X 00 13
					{//SP_PC_RDSCAN_CNF
						int nZoneNum ; 
						pEvent->pSerial->ReadCommData(szBuff,20,100);
						nZoneNum = szBuff[18];//获取有效的扫描列表数
						int nTotal = 60*nZoneNum;//有效列表对应的字节数，scanlist
						*pEvent->pScanInfo = (WORD)nZoneNum;
						nRcvChar = pEvent->pSerial->ReadCommData(szBuff+20,nTotal+4,500);
						if ((nRcvChar == nTotal+4)&&(szBuff[14]==0x01))
						{
							memcpy(pEvent->pScanInfo+0x02,szBuff+20,nTotal);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							return 0;
						}
					}
					break;
				case 20://0x00 14
					{//SP_PC_RDCONTACT_CNF
						int nZoneNum ; 
						//先读取前20字节数据
						pEvent->pSerial->ReadCommData(szBuff,20,500);
						nZoneNum = szBuff[18];//获取有效的联系人数
						int nTotal = 22*nZoneNum;//有效对应的字节数，contact
						pEvent->pContactInfo[0x00] = (WORD)nTotal;
						pEvent->pContactInfo[0x01] = (WORD)nTotal>>8;
						nRcvChar = pEvent->pSerial->ReadCommData(szBuff+20,nTotal+4,500);
						if ((nRcvChar == nTotal+4)&&(szBuff[14]==0x01))
						{
							memcpy(pEvent->pContactInfo+0x02,szBuff+20,nTotal);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							return 0;
						}

					}
					break;
				case 21://0x00 15
					{//SP_PC_RDGROUP_CNF
						int nZoneNum ; 
						//先读取前20字节数据
						pEvent->pSerial->ReadCommData(szBuff,20,50);
						nZoneNum = szBuff[18];//获取有效的组呼列表
						int nTotal = 34*nZoneNum;//有效对应的字节数，contact
						pEvent->pGroupList[0x00] = (WORD)nTotal;
						pEvent->pGroupList[0x01] = (WORD)nTotal>>8;

						nRcvChar = pEvent->pSerial->ReadCommData(szBuff+20,nTotal+4,500);
						if ((nRcvChar == nTotal+4)&&(szBuff[14]==0x01))
						{
							memcpy(pEvent->pGroupList+0x02,szBuff+20,nTotal);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							return 0;
						}

					}
					break;
				case 22://0x00 16
					{//SP_PC_RDTEXT_CNF
						int nZoneNum ; 
						//先读取前20字节数据
						pEvent->pSerial->ReadCommData(szBuff,20,50);
						nZoneNum = szBuff[18];//获取有效的组呼列表
						int nTotal = 162*nZoneNum;//有效对应的字节数，contact
						pEvent->pShortText[0x00] = (WORD)nTotal;
						pEvent->pShortText[0x01] = (WORD)nTotal>>8;

						nRcvChar = pEvent->pSerial->ReadCommData(szBuff+20,nTotal+4,500);
						if ((nRcvChar == nTotal+4)&&(szBuff[14]==0x01))
						{
							memcpy(pEvent->pShortText+0x02,szBuff+20,nTotal);
						}
						else
						{
							pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
							return 0;
						}

					}
					break;
				default:
					break;
				}//end switch


			}//end for i<22
			AfxMessageBox("读取完毕");
//			return 1;
		}//end bRead
 		else//进行写频
		{
 			WriteParameter(szBuff,pEvent);
			AfxMessageBox("写频完毕");
		}
		if (!pEvent->bRead)
		{
			Sleep(5000);
		}
		/////////接下来是令参数生效////////////////////
		//5F 5F 10 00 00 03 00 2B 02 00 95 11 04 00 20 12 20 12 FF FF 55 AA
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);

		nRcvChar = pEvent->pSerial->ReadCommData(szBuff,22,5000);
		if ((nRcvChar!=22)||(szBuff[14]!=0x01))//连接失败
		{
			return 0;
		}
		wc.Restore();
 	AfxMessageBox("操作完成");

	if (pEvent->bRead)
	{
// 			((CMainFrame*)pEvent->pMainframe)->UpdateAllViews(1);
			((CMainFrame*)pEvent->pMainframe)->TransferCommData();
			SendMessage(pEvent->hWnd,WM_UPDATE,0,0);
// 			((CMainFrame*)pEvent->hWnd)->TransferCommData();
//			CView*	pView = (CView*)((CMainFrame*)pEvent->pMainframe)->m_wndSplit.GetPane(0,1);
/*			POSITION	pos;
			CPCSWDoc*	pDoc = (CFrameWnd*)GetDocument();
			pos = ((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetFirstDocPosition();
			pDoc = (CPCSWDoc*)((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetNextDoc(pos);
			pDoc->UpdateAllViews(NULL);
*/	}
	pEvent->pSerial->CloseComm();
 	return 1;
}
int	WriteParameter(byte* szBuff,COMM_EVENT* pEvent)
{
	AfxMessageBox("准备写频");
	//1、密码类型判断 SP_PC_KEY_CNF
	int len = sizeof(SpPckeyReq_S);
	int	nRcvChar;
	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0x0e;szBuff[3] = 0x00;
	szBuff[18] = 0x55;szBuff[19] = 0xaa;
	memcpy(szBuff+4,keyWriteReq,len);

	pEvent->pSerial->WriteCommData(szBuff,20,1);
	//2、收到密码确认 SP_PC_KEY_CNF
	if (len !=sizeof(SpPckeyCnf_S)+6)
	{
		len = sizeof(SpPckeyCnf_S)+6;
	}
	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
	if (nRcvChar == 26)
	{
		if (szBuff[16]= 0x01)
		{
			byte* code = new byte[4];
			memcpy(code,(pEvent->pRadioSetting+0x06),4);
			if (memcmp(szBuff+18,code,4)<0)
			{
				AfxMessageBox("密码错误");
				return 0;
			}

		}
	}
	else
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;
	//3、准备写入系统参数 SpPcWriteSysSet_S
	byte	szPwd[6];
	memcpy(szPwd,szBuff+18,4);

	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0xa0;szBuff[3] = 0x00;
	szBuff[164] = 0x55;szBuff[165] = 0xaa;
		szBuff[4] = 0x00 ;        //0x00
		szBuff[5] = 0x03 ;      //0x03
		szBuff[6] = 0x00 ;        //0x00
		szBuff[7] = 0x2B;      //0x2B
	memcpy(szBuff+4,WriteSyssetReq,sizeof(SpPcWriteSysSet_S));
		
	memcpy(szBuff+14,szPwd,4);
	memcpy(szBuff+18,pEvent->pRadioInfo,38);
	memcpy(szBuff+56,pEvent->pRadioSetting,42);
	memcpy(szBuff+98,pEvent->pEmergencySetting,28);
	memcpy(szBuff+126,pEvent->pMenuSetting,25);
	memcpy(szBuff+151,pEvent->pKeyFunctionSetting,11);

	pEvent->pSerial->WriteCommData(szBuff,166,500);
	
	// SP_PC_WRITE_CNF 写入确认		////////////
	if (len !=sizeof(SpPcWriteCnf_S)+6)
	{
		len = sizeof(SpPcWriteCnf_S)+6;
	}

	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,500);
	if (nRcvChar!=22 ||(szBuff[14]!=0x01)||(szBuff[16]!=0x01))
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;
	//4、PC_SP_WTZONE_REQ 区域写入请求
	if (len !=sizeof(SpPcWriteZone_S)+6)
	{
		len = sizeof(SpPcWriteZone_S)+6;
	}
	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0x30;szBuff[3] = 0x01;
	szBuff[308] = 0x55;szBuff[309] = 0xaa;
	memcpy(szBuff+4,WriteZoneReq,sizeof(SpPcWriteZone_S));
	memcpy(szBuff+14,szPwd,4);
	memcpy(szBuff+18,pEvent->pZoneInfo,288);
	pEvent->pSerial->WriteCommData(szBuff,len,100);

	// SP_PC_WRITE_CNF 写入确认		////////////
	if (len !=sizeof(SpPcWriteCnf_S)+6)
	{
		len = sizeof(SpPcWriteCnf_S)+6;
	}
	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,100);
	if (nRcvChar!=22 ||(szBuff[14]!=0x02)||(szBuff[16]!=0x01))
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;

	//5、信道信息
	for (int i=0;i<=15;i++)
	{
		Sleep(100);
		szBuff[0] = szBuff[1] = 0x5f;
		szBuff[2] = 0xf2;szBuff[3] = 0x02;
		memcpy(szBuff+4,WriteChReq,sizeof(SpPcWriteChannl_S));
		memcpy(szBuff+14,szPwd,4);
		szBuff[18] = i;
		szBuff[19] = 0x00;
		memcpy(szBuff+20,pEvent->pChannelInfo+736*i,736);
		szBuff[758] = 0x55;szBuff[759] = 0xaa;
		pEvent->pSerial->WriteCommData(szBuff,760,100);

		nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,100);
		if (nRcvChar!=22 ||(szBuff[14]!=i+3)||(szBuff[16]!=0x01))
		{
			pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
			return 0;
		}
		if(pEvent->bCancel)
			return 0;
	}

	//6、扫描列表
	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0x92;szBuff[3] = 0x07;
	szBuff[1942] = 0x55;szBuff[1943] = 0xaa;
	memcpy(szBuff+4,WriteScanReq,sizeof(SpPcWriteScan_S));
	memcpy(szBuff+14,szPwd,4);
	szBuff[18] = 0x20;szBuff[19] = 0x00;
	memcpy(szBuff+20,pEvent->pScanInfo+0x02,1920);
	pEvent->pSerial->WriteCommData(szBuff,1944,100);

	// SP_PC_WRITE_CNF 写入确认		////////////
	if (len !=sizeof(SpPcWriteCnf_S)+6)
	{
		len = sizeof(SpPcWriteCnf_S)+6;
	}
	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,100);
	if (nRcvChar!=22 ||(szBuff[14]!=0x19)||(szBuff[16]!=0x01))
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;

	//7、 联系人
	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0x42;szBuff[3] = 0x11;
	szBuff[4422] = 0x55;szBuff[4423] = 0xaa;
	memcpy(szBuff+4,WriteContactReq,sizeof(SpPcWriteContct_S));
	memcpy(szBuff+14,szPwd,4);
	szBuff[18] = 0xc8;szBuff[19] = 0x00;
	memcpy(szBuff+20,pEvent->pContactInfo+0x02,4400);
	pEvent->pSerial->WriteCommData(szBuff,4424,100);

	// SP_PC_WRITE_CNF 写入确认		////////////
	if (len !=sizeof(SpPcWriteCnf_S)+6)
	{
		len = sizeof(SpPcWriteCnf_S)+6;
	}
	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,100);
	if (nRcvChar!=22 ||(szBuff[14]!=0x20)||(szBuff[16]!=0x01))
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;

	//8、组呼列表

	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0x58;szBuff[3] = 0x04;
	szBuff[1110] = 0x55;szBuff[1111] = 0xaa;
	memcpy(szBuff+4,WriteGroupReq,sizeof(SpPcWriteGrp_S));
	memcpy(szBuff+14,szPwd,4);
	szBuff[18] = 0x20;szBuff[19] = 0x00;
	memcpy(szBuff+20,pEvent->pGroupList+0x02,1088);
	pEvent->pSerial->WriteCommData(szBuff,1112,100);

	// SP_PC_WRITE_CNF 写入确认		////////////
	if (len !=sizeof(SpPcWriteCnf_S)+6)
	{
		len = sizeof(SpPcWriteCnf_S)+6;
	}
	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,100);
	if (nRcvChar!=22 ||(szBuff[14]!=0x21)||(szBuff[16]!=0x01))
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;

	//9、文本内容
	szBuff[0] = szBuff[1] = 0x5f;
	szBuff[2] = 0xb6;szBuff[3] = 0x1f;
	szBuff[8122] = 0x55;szBuff[8123] = 0xaa;
	memcpy(szBuff+4,WriteTextReq,sizeof(SpPcWriteTxt_S));
	memcpy(szBuff+14,szPwd,4);
	szBuff[18] = 0x32;szBuff[19] = 0x00;
	memcpy(szBuff+20,pEvent->pShortText+0x02,8100);
	pEvent->pSerial->WriteCommData(szBuff,8124,100);

	// SP_PC_WRITE_CNF 写入确认		////////////
	if (len !=sizeof(SpPcWriteCnf_S)+6)
	{
		len = sizeof(SpPcWriteCnf_S)+6;
	}
	nRcvChar = pEvent->pSerial->ReadCommData(szBuff,len,100);
	if (nRcvChar!=22 ||(szBuff[14]!=0x22)||(szBuff[16]!=0x01))
	{
		pEvent->pSerial->WriteCommData(pEvent->szPara,22,1);
		return 0;
	}
	if(pEvent->bCancel)
		return 0;
	
	return 1;
}
void CMainFrame::OnCommSet() 
{
	// TODO: Add your command handler code here
	CCOMSET	dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_nComm = dlg.m_nPortNum;
	}
	if (m_nComm == 0||m_nComm == 1)
	{
		m_bReadyComm = false;
	}
	else
		m_bReadyComm = true;
	return;
}
 


void CMainFrame::OnUpdateReadParameter(CCmdUI* pCmdUI) 
{
	if (m_bReadyComm)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	// TODO: Add your command update UI handler code here
	
}
CPCSWDoc*	CMainFrame::GetDocument()
{
	POSITION pos;
	pos=((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetFirstDocPosition();
	return((CPCSWDoc*)(((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template[0])->GetNextDoc(pos)));
}
 

 void CMainFrame::OnWriteParameter() 
{
	// TODO: Add your command handler code here
	if (m_nComm == 0||m_nComm == 1)
	{
		AfxMessageBox("请先选择串口！");
		return;
	}
	if(!m_bReadyComm)
		return;
	m_SerialPort.m_nPort = m_nComm;
	m_SerialPort.m_nPaud = m_nPaud;
	if (!m_SerialPort.IsOpen())
	{
		if(!m_SerialPort.OpenComm(m_nComm,m_nPaud))
		{	
			MessageBox("串口错误，请检查串口","端口选择",MB_ICONERROR|MB_OK);
			return;
		}
	}
	iCommEvent.bRead = FALSE;		//要么读取，要么写入
	iCommEvent.pSerial = &m_SerialPort;

	iCommEvent.pRadioInfo = theApp.m_CommInfo.pRadioInfo;
		//GetDocument()->pRadioInfo;
	iCommEvent.pRadioSetting =theApp.m_CommInfo.pRadioSetting;
		//GetDocument()->pRadioSetting;
	iCommEvent.pMenuSetting =theApp.m_CommInfo.pMenuSetting;
	// GetDocument()->pMenuSetting;
	iCommEvent.pEmergencySetting = theApp.m_CommInfo.pEmergencySetting;
	//GetDocument()->pEmerSetting;
	iCommEvent.pKeyFunctionSetting = theApp.m_CommInfo.pKeyFunctionSetting;
	//GetDocument()->pKeySetting;


	iCommEvent.pZoneInfo = theApp.m_CommInfo.pZoneInfo;
	//GetDocument()->pZoneInfo;
	iCommEvent.pChannelInfo =theApp.m_CommInfo.pChannelInfo;
	//GetDocument()->pChannelInfo;
	iCommEvent.pScanInfo = theApp.m_CommInfo.pScanInfo;
	//GetDocument()->pScanInfo;
	iCommEvent.pContactInfo = theApp.m_CommInfo.pContactInfo;
	//GetDocument()->pContact;
	iCommEvent.pGroupList = theApp.m_CommInfo.pGroupList;
	//GetDocument()->pGrouplist;
	iCommEvent.pShortText = theApp.m_CommInfo.pShortText;
	//GetDocument()->pShortText;

	ZeroMemory(iCommEvent.bChannelExist,16);//防止有信道没有被设置
	ZeroMemory(iCommEvent.bZoneExist,16);	//防止有区域没有被设置

	iCommEvent.szPara[0] = iCommEvent.szPara[1] = 0x5f;
	iCommEvent.szPara[2] = 0x10;iCommEvent.szPara[3] = 0x00;
	iCommEvent.szPara[20] = 0x55;iCommEvent.szPara[21]= 0xaa;
	memcpy(iCommEvent.szPara+4,effectreq,sizeof(SpPcEffect_S));

	m_pThread = AfxBeginThread(ThraedComm,&iCommEvent);	
}

void CMainFrame::OnUpdateWriteParameter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_bReadyComm)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	
}
void	CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI)
{

}
LRESULT 	CMainFrame::ShowChildWindow(WPARAM wParam,LPARAM lParam)
{
	int i=int(wParam);//LOWORD(lParam);
	if(i==0||i>2)
		return 0;
	POSITION	pos;
	CPCSWDoc*	pDoc;
	CDocTemplate*	pTmp ;
	pTmp = (CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template.GetAt(i-1);//[];
	pos = (pTmp)->GetFirstDocPosition();
	pDoc = (CPCSWDoc*)(((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template.GetAt(i-1))->GetNextDoc(pos));
	//当视图已经被创建之后
 
	CFrameWnd* pWnd = ((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)));
	if(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)!=NULL)
	{
		//激活框架,若缺少则无法进行视图切换
		((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)))->ActivateFrame();

		switch (i)
		{
		case 1:
			{
				//因为对讲机基本信息窗口不是关闭，只是隐藏，所以这里重新加载数据
				CPCSWView* pView = new CPCSWView;
				pView=(CPCSWView*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(0)))->GetActiveView());
//  				pView->OnUpdate(NULL,0,NULL);
				//	pView->LoadData();
			}
			break;
		case 2:
			{
 				CMenuSet* pView = new CMenuSet;
				pView=(CMenuSet*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)))->GetActiveView());
 				pView->LoadData();
			}
			break;
/*
		case 3:
			{
 				CRadioSetView* pView = new CRadioSetView;
				pView=(CRadioSetView*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)))->GetActiveView());
 				pView->LoadData();
			}
			break;
		case 4:
			{
 				CZoneInfo* pView = new CZoneInfo;
				pView=(CZoneInfo*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)))->GetActiveView());
 				pView->LoadData();
			}
			break;
		case 5:
			{
 				CScanView* pView = new CScanView;
				pView=(CScanView*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)))->GetActiveView());
 				pView->LoadData();
			}
			break;
		case 6:
			{
 				CDpmrView* pView = new CDpmrView;
				pView=(CDpmrView*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(i-1)))->GetActiveView());
 				pView->LoadData();
			}
			break;*/

		default:
			break;
		}
/*	此部分采用switch方式激活窗口
		//如果打开的窗口是对讲机基本信息的话
		if(i==1)
		{
			//因为对讲机基本信息窗口不是关闭，只是隐藏，所以这里重新加载数据
			CPCSWView* pView = new CPCSWView;
			pView=(CPCSWView*)(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(0)))->GetActiveView());
//			(((CFrameWnd*)(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(0)))->SetActiveView(pView));
			pView->LoadData();
		}
*/
  		return 0;
	}
	CDocTemplate* pTemplate=(CDocTemplate*)(((CPCSWApp*)AfxGetApp())->m_template.GetAt(i-1));
	ASSERT_VALID(pTemplate);

	CFrameWnd* pFrame=pTemplate->CreateNewFrame(pDoc,NULL);
	if(pFrame==NULL)
	{
		TRACE0("Warning:failed to create new frame\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		return 0;
	}
	//
	pTemplate->InitialUpdateFrame(pFrame,pDoc);	
	//定位切换到该新视图
	((CPCSWApp*)AfxGetApp())->m_Frame.SetAt(i-1,pFrame);
	return 1;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_wndSplit.CreateStatic(this,1,2);
	m_wndSplit.CreateView(0,0,RUNTIME_CLASS(CMyTree),CSize(100,100),NULL);
	m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CPCSWView),CSize(100,100),NULL);

	return TRUE;
//	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}
void	CMainFrame::SwitchView(int nIndex)
{
	CView*	pView = (CView*)m_wndSplit.GetPane(0,1);
	CRect	rectView,rectFrm;
	pView->GetClientRect(&rectView);
	GetClientRect(&rectFrm);
	switch (nIndex)
	{
	case 1:
		{
			if (!pView->IsKindOf(RUNTIME_CLASS(CPCSWView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CPCSWView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				m_nViewIndex = 1;
			}
		}
		break;
	case 2:
		{
 			if (!pView->IsKindOf(RUNTIME_CLASS(CMenuKeyView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CMenuKeyView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				m_nViewIndex = 2;
			}
		}
		break;
	case 3:
		{
 			if (!pView->IsKindOf(RUNTIME_CLASS(CRadioSetView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CRadioSetView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				m_nViewIndex = 3;
			}
		}
		break;
	case 4:
		{
 			if (!pView->IsKindOf(RUNTIME_CLASS(CScanView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CScanView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				m_nViewIndex = 4;
			}
		}
		break;
	case 5:
		{
 			if (!pView->IsKindOf(RUNTIME_CLASS(CZoneInfo)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CZoneInfo),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				m_nViewIndex = 5;
			}
		}
		break;
	case 6:
		{
			if (!pView->IsKindOf(RUNTIME_CLASS(CDpmrView)))
			{
				m_wndSplit.DeleteView(0,1);
				m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CDpmrView),CSize(rectView.Width(),rectView.Height()),NULL);
				m_wndSplit.RecalcLayout();
				m_nViewIndex = 6;
			}
		}
		break;
	default:
		break;
	}
}