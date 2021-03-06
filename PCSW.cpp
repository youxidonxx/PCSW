// PCSW.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PCSW.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "PCSWDoc.h"
#include "PCSWView.h"
#include "MenuSet.h"
#include "RadioSetView.h"
#include "ZoneInfo.h"
#include "ScanView.h"
#include "DpmrView.h"
#include "MenuKeyView.h"
#include "GridView.h"

#ifdef _DEBUG
#pragma comment(lib,"Hook.lib")
#include "Hook.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#ifdef DLL_IMPORT
HHOOK g_hMouse = NULL;
HHOOK g_hKeyboard = NULL;
HWND g_hWnd = NULL;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCSWApp
#ifdef _DEBUG
#ifdef _CONSOLE
HANDLE	hConsoleHandle;
DWORD	dwPreLength,dwActualLength;
#endif // _CONSOLE
#endif // _DEBUG

extern	 	CString		strFreqScole;

BEGIN_MESSAGE_MAP(CPCSWApp, CWinApp)
	//{{AFX_MSG_MAP(CPCSWApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
// 	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)OnFileOpen
ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
ON_COMMAND(ID_FILE_SAVE,OnFileSave)
END_MESSAGE_MAP()

CString		AddStringTailZero(CString&	str,int nDesiredLen)
{
	if(str.IsEmpty())
		return str;
	int len = str.GetLength();
	if(len>nDesiredLen)
		return str;
	int i=0;
	for (i=0;i<nDesiredLen-len;i++)
	{
		str.Insert(len+i,'0');
	}
	return str;
}
CString		ConvertStrintToStrhex(CString&	strInt)
{
	if(strInt.IsEmpty())
		return strInt;
	CString	strHex,str;
	str = strInt;
	if(strInt.Find('.') < 0)
		str += ".000000";		//未输入小数部分
	else
		str += "000000";		//小数部分位数不足
	int nIndex = str.Find('.');
	str.Insert(nIndex+7,'.');
	str.Delete(nIndex);
	long	lTmp1 = _ttoi(LPCTSTR(str));
	long	lTmp2 = ((lTmp1+75)/12500)*12500;
	if(lTmp1/100 == lTmp2/100)
		lTmp1 = lTmp2;
	else
		lTmp1 = (lTmp1/12500)*12500;
	str.Format("%X",lTmp1);
	return str;
}
void	ConvertCString2String(CString&	strSrc,std::string&	strDes)
{
#ifndef UNICODE
	strDes = strSrc;
#else
	USES_CONVERSION
		strDes = W2A(strSrc.LockBuffer());
	strSrc.UnlockBuffer();
#endif
}

BYTE*	ConvertStrToIntArray(CString	str,int& nLen)//nLen还同时返回作为调用方的长度参考
{
	BYTE*	data = new BYTE[nLen];
	ZeroMemory(data,nLen);
	if(str.IsEmpty())
		return data;
	int nPos = str.Find('.');
	if(nPos>=0)
		str.Delete(nPos);
	int	len = str.GetLength();
	BYTE	ch;
	int i;
	if(len >nLen*2)//需要有最大长度
		len = nLen*2;
	else if (len<nLen*2)
	{
		for (i=nLen*2-len-1;i>=0;i--)
		{
			str.Insert(nLen*2-i,'0');
		}
		len = nLen*2;
	}
	str.MakeUpper();
	str = str.Left(len);
	for (i=len-1;i>=0;i--)
	{
		ch = str.GetAt(i);
		if(ch>='0'&&ch<='9')
			ch = ch-'0';
		else if((ch>='A')&&(ch<='F'))
			ch=ch-'A'+10;
		else
			break;
		if(i%2==0)
			data[(len-i)/2-1] = (data[(len-i)/2-1]&0x0f)|ch<<4;
		else
			data[(len-i)/2] = (data[(len-i)/2]&0xf0)|ch;
	}
	nLen = len;
	return data;
}
BYTE*	ConvertStrTo7ID(CString str,int nLen)
{
	BYTE*	data ;
	if(nLen%2==1)
		data = new BYTE[nLen/2+1];
	else
		data = new BYTE[nLen/2];
	ZeroMemory(data,sizeof(data));
	if(str.IsEmpty())
		return data;
	int nPos = str.Find('.');
	if(nPos>=0)
		str.Delete(nPos);
	str = str.Left(nLen);
	char	ch;
	int i;
	for (i=nLen-1;i>=0;i--)
	{
		ch = str.GetAt(i);//from low addr to high addr
		ch = ch-'0';
		if(i%2 ==0)//even array 
			data[(nLen-1-i)/2] = ch|data[(nLen-i-1)/2]&0xf0;
		else
			data[(nLen-1-i)/2] = (ch<<4)|(data[(nLen-1-i)/2]&0x0f);
	}
	data[(nLen-1)/2] = (data[(nLen-1)/2]&0x0f)|0xf0;

	return data;
}
void	AddStrTailZero(CString&	str,int nDesiredLen)
{
	int len = str.GetLength();
	if(len>nDesiredLen)
		return;
	int i=0;
	for (i=0;i<nDesiredLen-len;i++)
	{
		str.Insert(len+i,'0');
	}
	return;
}

#ifdef	DLL_IMPORT
LRESULT CALLBACK MouseProc(int nCode,
						   WPARAM wParam,
						   LPARAM lParam
						   )
{
	return 1;
}
LRESULT CALLBACK KeyboardProc(int code,
							  WPARAM wParam,
							  LPARAM lParam
							  )
{
	if (VK_F2 == wParam)
	{
		SendMessage(g_hWnd,WM_CLOSE,0,0);
		UnhookWindowsHookEx(g_hMouse);
		UnhookWindowsHookEx(g_hKeyboard);
	}
	return 1;
}
void SetHook(HWND hwnd)
{
	g_hWnd = hwnd;
	g_hMouse = SetWindowsHookEx(WH_MOUSE,MouseProc,GetModuleHandle("Hook"),0);
	//	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,GetModuleHandle("Hook"),0);
}
void	StopHook()
{
	if(g_hMouse != NULL)
		UnhookWindowsHookEx(g_hMouse);
	g_hMouse = NULL;
	if(g_hKeyboard!=NULL)
		UnhookWindowsHookEx(g_hKeyboard);
	g_hKeyboard = NULL;
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CPCSWApp construction
CPCSWApp::CPCSWApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPCSWApp object

CPCSWApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPCSWApp initialization

BOOL CPCSWApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
#if _MSC_VER<=1200
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
	INITCOMMONCONTROLSEX InitCtrls;  
	InitCtrls.dwSize = sizeof(InitCtrls);  
	InitCtrls.dwICC = ICC_WIN95_CLASSES;  
	InitCommonControlsEx(&InitCtrls);  
	CWinApp::InitInstance();  
	if (!AfxOleInit())  
	{           AfxMessageBox(IDP_OLE_INIT_FAILED);  
	return FALSE;  
	}  
	AfxEnableControlContainer(); 
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	//这里当做单文档使用，多视图嵌入
	int n=0;
// 	CMultiDocTemplate* pDocTemplate;
// 	pDocTemplate = new CMultiDocTemplate(
// 		IDR_PCSWTYPE,
// 		RUNTIME_CLASS(CPCSWDoc),
// 		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
// 		RUNTIME_CLASS(CPCSWView));
// 	AddDocTemplate(pDocTemplate);

// 	m_template.Add(pDocTemplate);
 // 	m_Frame.Add(NULL);
// 	CDocTemplate*	pTmp1 = (CDocTemplate*)m_template.GetAt(0);

/*
	pDocTemplate = new CMultiDocTemplate(
		IDR_PCSWTYPE,
		RUNTIME_CLASS(CPCSWDoc),
		RUNTIME_CLASS(CChildFrame),
// 		RUNTIME_CLASS(CMenuSet));
		RUNTIME_CLASS(CMenuKeyView));
		m_template.Add(pDocTemplate);
 	m_Frame.Add(NULL);
*/

/*
	pDocTemplate = new CMultiDocTemplate(
		IDR_PCSWTYPE,
		RUNTIME_CLASS(CPCSWDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CRadioSetView));
	m_template.Add(pDocTemplate);
      	m_Frame.Add(NULL);
	
 	pDocTemplate = new CMultiDocTemplate(
		IDR_PCSWTYPE,
		RUNTIME_CLASS(CPCSWDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CZoneInfo));
	n = m_template.Add(pDocTemplate);
    	m_Frame.Add(NULL);
 
 	pDocTemplate = new CMultiDocTemplate(
		IDR_PCSWTYPE,
		RUNTIME_CLASS(CPCSWDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CScanView));
	n = m_template.Add(pDocTemplate);
    	m_Frame.Add(NULL);

 	pDocTemplate = new CMultiDocTemplate(
		IDR_PCSWTYPE,
		RUNTIME_CLASS(CPCSWDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CDpmrView));
	n = m_template.Add(pDocTemplate);
    	m_Frame.Add(NULL);
*/

// 	CDocTemplate*	pTmp = (CDocTemplate*)m_template.GetAt(0);
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
 	ParseCommandLine(cmdInfo);
	//若无这句，则无法进入程序，导致winmdi.cpp line 531错误
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
#ifdef _DEBUG
#ifdef _CONSOLE
	AllocConsole();
	hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif // _CONSOLE
#endif // _DEBUG
// 	pMainFrame->UpdateAllViews(0);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPCSWApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPCSWApp message handlers

 

int CPCSWApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	int n = m_template.GetUpperBound();
	for(i=1;i<=m_template.GetUpperBound();i++)
	{
		CMultiDocTemplate* pTemplate=(CMultiDocTemplate*)(m_template[i]);
		delete pTemplate;
	}
	m_template.RemoveAll();
	m_Frame.RemoveAll();
	return CWinApp::ExitInstance();
}

CDocument* CPCSWApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::OpenDocumentFile(lpszFileName);
}

void CPCSWApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	LPCTSTR szFilter = _T("DAT文件(*.dat)|*.dat|所有文件(*.*)|*.*||");
	CFileDialog	fileDlg(TRUE,_T(".dat"),_T("*.*"),
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,szFilter,NULL);
	CString	newName;
	if( fileDlg.DoModal() == IDOK )
    {
        POSITION pos = fileDlg.GetStartPosition();	
        newName = fileDlg.GetNextPathName(pos);
    }
	else
		return;
	SetHook(m_pMainWnd->m_hWnd);
	CFile	file;
	CFileException	ce;
 	if(!file.Open(newName,CFile::modeRead,&ce))
	{
		ce.ReportError();
		return;
	}

	m_CommInfo.bHasInfo = true;
	file.Read(m_CommInfo.pHead,sizeof(m_CommInfo.pHead));
	file.Read(m_CommInfo.pRadioInfo,sizeof(m_CommInfo.pRadioInfo));
	file.Read(m_CommInfo.pRadioSetting,sizeof(m_CommInfo.pRadioSetting));
	file.Read(m_CommInfo.pEmergencySetting,sizeof(m_CommInfo.pEmergencySetting));
	file.Read(m_CommInfo.pMenuSetting,sizeof(m_CommInfo.pMenuSetting));
	file.Read(m_CommInfo.pKeyFunctionSetting,sizeof(m_CommInfo.pKeyFunctionSetting));
	file.Read(m_CommInfo.pZoneInfo,sizeof(m_CommInfo.pZoneInfo));
	file.Read(m_CommInfo.pChannelInfo,sizeof(m_CommInfo.pChannelInfo));
	file.Read(m_CommInfo.pScanInfo,sizeof(m_CommInfo.pScanInfo));
	file.Read(m_CommInfo.pContactInfo,sizeof(m_CommInfo.pContactInfo));
	file.Read(m_CommInfo.pGroupList,sizeof(m_CommInfo.pGroupList));
	file.Read(m_CommInfo.pShortText,sizeof(m_CommInfo.pShortText));

// 	 	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
// // 	 	CView*	pView = (CView*)pFrame->m_wndSplit.GetPane(0,1);
// 		UINT	style = pFrame->m_wndToolBar.GetButtonStyle(4);
// 		int		nRowCnt = pFrame->m_wndSplit.GetRowCount();
			//(ID_APP_ABOUT);
// 		pView->UpdateWindow();
// 	file.Close();
// 		UpdateActiveView();
	StopHook();
}
void	CPCSWApp::UpdateActiveView()
{
	CMainFrame*	pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
// 	}
}
void	CPCSWApp::OnFileSave()
{
	LPCTSTR szFilter = _T("DAT文件(*.dat)|*.dat|所有文件(*.*)|*.*||");
	CFileDialog	fileDlg(FALSE,_T(".dat"),_T("*.dat"),
		 OFN_HIDEREADONLY|OFN_EXTENSIONDIFFERENT| OFN_OVERWRITEPROMPT,szFilter,NULL);
	CString	newName;
	if( fileDlg.DoModal() == IDOK )
	{
		POSITION pos = fileDlg.GetStartPosition();	
		newName = fileDlg.GetNextPathName(pos);
	}
	else
		return;
	CFile	file;
	CFileException	ce;
	if(!file.Open(newName,CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate,&ce))
	{
		ce.ReportError();
		return;
	}
	file.Write(m_CommInfo.pHead,sizeof(m_CommInfo.pHead));
	file.Write(m_CommInfo.pRadioInfo,sizeof(m_CommInfo.pRadioInfo));
	file.Write(m_CommInfo.pRadioSetting,sizeof(m_CommInfo.pRadioSetting));
	file.Write(m_CommInfo.pEmergencySetting,sizeof(m_CommInfo.pEmergencySetting));
	file.Write(m_CommInfo.pMenuSetting,sizeof(m_CommInfo.pMenuSetting));
	file.Write(m_CommInfo.pKeyFunctionSetting,sizeof(m_CommInfo.pKeyFunctionSetting));
	file.Write(m_CommInfo.pZoneInfo,sizeof(m_CommInfo.pZoneInfo));
	file.Write(m_CommInfo.pChannelInfo,sizeof(m_CommInfo.pChannelInfo));
	file.Write(m_CommInfo.pScanInfo,sizeof(m_CommInfo.pScanInfo));
	file.Write(m_CommInfo.pContactInfo,sizeof(m_CommInfo.pContactInfo));
	file.Write(m_CommInfo.pGroupList,sizeof(m_CommInfo.pGroupList));
	file.Write(m_CommInfo.pShortText,sizeof(m_CommInfo.pShortText));

	file.Close();
}
int	CPCSWApp::GetFreqScope()
{
	int	nRet = m_CommInfo.pRadioInfo[Freqscope]+m_CommInfo.pRadioInfo[Freqscope+1]*256;
	return (nRet-1);
}
void	CPCSWApp::SetFreqScope(int nRange)
{
	if (nRange>0 || nRange <=ArraySize(strFreqScole))
	{
		m_CommInfo.pRadioInfo[0x00+Freqscope] = nRange%256;//16bits 0xff
		m_CommInfo.pRadioInfo[0x00+Freqscope+1] = nRange/256;
	}
}
int  CPCSWApp::GetFreqBoundry(bool bMax /* = true */)
{
	int nType = GetFreqScope()+1;//m_CommInfo.pRadioInfo[0x00+Freqscope];
	int	nBoundry;
	if(bMax)
	{
		switch (nType)
		{
		case 1:
#ifdef _CHANGED
	nBoundry =174;
#else
	nBoundry = 150;
#endif			
			break;
		case 2:
			nBoundry = 174;
			break;
		case 3:
			nBoundry = 470;
			break;
		case 4:
			nBoundry = 425;
			break;
		default:
			nBoundry = 400;
		break;		
		}
	}
	else
	{
		switch (nType)
		{
		case 4:
			nBoundry = 400;
			break;
		case 1:
			nBoundry = 136;
			break;
		case 2:
			nBoundry = 150;
			break;
		case 3:
			nBoundry = 400;
			break;
		default:
			nBoundry = 400;
			break;		
		}
	}
	return nBoundry;
}
void	CPCSWApp::SetAlarmName(int nFlag,CString& str,int nLen)
{
	BYTE*	ptr = &m_CommInfo.pEmergencySetting[0x00+nFlag];
	BYTE *szTemp  = new BYTE [nLen*2];
	memset(szTemp,0x00,nLen*2);
	memset(ptr,0x00,nLen);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)szTemp,nLen);
	memcpy(ptr,szTemp,nLen);
	delete	szTemp;

}
/************************************************************************/
/* scan 扫描
*/
/************************************************************************/
CString		CPCSWApp::GetName(int nZone,int nCh,int nFlag,int nLen,
							  int nStep1 /* = 736 */,int nStep2 /* = 46 */,bool bCh /* = true */)
{
	BYTE *ptr,*pInfo;
	BYTE* szTemp = new BYTE[nLen*2];
	if(bCh)
	{
		pInfo = m_CommInfo.pChannelInfo;
		ptr = pInfo+nFlag+(nZone-1)*nStep1+(nCh-1)*nStep2;
	}
	else
	{
		pInfo = m_CommInfo.pZoneInfo;
		ptr = pInfo+nFlag+(nZone-1)*nStep1+(nCh-1)*nStep2;
	}
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	return str;
}
int		CPCSWApp::GetScanlistCount()
{
	int nRet = *(WORD*)m_CommInfo.pScanInfo;
// 	if( nRet<1 || nRet>32)
// 		nRet =1;
	return nRet;
}
CString		CPCSWApp::GetScanlistName(int nFlag,int nLen,int nList)
{
	BYTE*	ptr,*pScan;
	pScan =  m_CommInfo.pScanInfo;
	BYTE	*szTmp = new BYTE	[nLen*2];
	ptr = &pScan[0x00+2+nFlag+(nList-1)*60];
	memcpy(szTmp,ptr,nLen);
	szTmp[nLen] = szTmp[nLen+1] = 0x00;
	CString	str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTmp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTmp;
	return str;
}
/************************************************************************/
/* 联系人相关设置提取

*/
/************************************************************************/
int		CPCSWApp::GetContInfo(int nFlag,int nGrp)
{
	int nRet = m_CommInfo.pContactInfo[0x00+2+nFlag+(nGrp-1)*22];
	return nRet;
}

CString		CPCSWApp::GetContName(int nGrp,int	nLen)
{
	BYTE *ptr,*m_pCont;
	m_pCont = m_CommInfo.pContactInfo;
	BYTE *szTemp = new BYTE [nLen*2];
	ptr = &m_pCont[0x00+2+CONTACT_NAME+(nGrp-1)*22];
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTemp;
	return str;

}
CString	 CPCSWApp::GetContID(int nGrp,int nLen)
{
	char str[20];
	BYTE ch;
	int i;
	int nLength = nLen*2-1;//此项由于从下标0开始,所以是呼叫ID的长度减去1
	int j=0;
	for(i=nLength;i>=0;i--)
	{
		if(i%2==0)
			ch = *(m_CommInfo.pContactInfo+2+CONTACT_ID+(nGrp-1)*22+i/2)&0x0F;		
		else
			ch = *(m_CommInfo.pContactInfo+2+CONTACT_ID+(nGrp-1)*22+i/2)>>4;			
		if(ch<10)
			str[7-i-j]=ch+'0';
		else
			j++;
	}
	str[8-j]=0;
	return(CString(str));
}
void	CPCSWApp::SetContInfo(int nFlag,int nGrp,int nVal)
{
	m_CommInfo.pContactInfo[0x00+2+nFlag+(nGrp-1)*22] = nVal;
}
void	CPCSWApp::SetContName(int nFlag,int nGrp,CString& str,int nLen)
{
	BYTE*	ptr = &m_CommInfo.pContactInfo[0x00+2+nFlag+(nGrp-1)*22];
	BYTE *szTemp  = new BYTE [nLen*2];
	memset(szTemp,0x00,nLen*2);
	memset(ptr,0x00,nLen);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)szTemp,nLen);
	memcpy(ptr,szTemp,nLen);
	delete	szTemp;

}
//有问题——不在使用
void	CPCSWApp::SetContID(int nFlag,int nGrp,CString& str)
{
	int nTotalLen = 7;
	int	nLessLen = 6;
	char ch;
	int i;
	BYTE *byData;
	CString strTemp = str;
	byData = ConvertStrTo7ID(strTemp,7);
	
// 	int length=strTemp.GetLength();
// 	if(length>nTotalLen)
// 		length=nTotalLen;
// 	else if(length<nTotalLen)
// 	{
// 		for(i=0;i<nTotalLen-length;i++)
// 			strTemp.Insert(i,'0');
// 	}
// 
// 	for(i=nLessLen;i>=0;i--)
// 	{
// 		ch=strTemp.GetAt(i);
// 		if((ch>='0') && (ch<='9'))
// 			byData=ch-'0';
// 		else
// 			break;
// 		if(i%2==0)
// 			*(m_CommInfo.pContactInfo+2+nFlag+(nGrp-1)*22+(nLessLen-i)/2) = 
// 			(*(m_CommInfo.pContactInfo+2+nFlag+(nGrp-1)*22+(nLessLen-i)/2)&0x0F) | byData;
// 		else
// 			*(m_CommInfo.pContactInfo+2+nFlag+(nGrp-1)*22+(nLessLen-i)/2) = 
// 			(*(m_CommInfo.pContactInfo+2+nFlag+(nGrp-1)*22+(nLessLen-i)/2)&0xF0) | (byData<<4);
// 	}
// 	*(m_CommInfo.pContactInfo+2+nFlag+(nGrp-1)*22+3)|=0x0F;
}
void	CPCSWApp::SetContCount(int nVal)
{
	m_CommInfo.pContactInfo[0x00] = nVal;
	m_CommInfo.pContactInfo[0x01] = (WORD)nVal>>8;
}

/************************************************************************/
/* 组呼列表                                                                     */
/************************************************************************/
CString		CPCSWApp::GetGrplistName(int nGrp,int nLen)
{
	BYTE*	ptr ,*m_pGrp;
 	m_pGrp = m_CommInfo.pGroupList;
	BYTE *szTemp = new BYTE [nLen*2];
	ptr = &m_pGrp[0x00+2+GRP_NAME+(nGrp-1)*34];
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTemp;
	return str;
}
int		CPCSWApp::GetGrplistCount()
{
	int	nRet= *(WORD*)m_CommInfo.pGroupList;
	return nRet;
}
int		CPCSWApp::GetGrplistInfo(int nFlag,int nGrp,int nLen)
{
	int nRet = m_CommInfo.pGroupList[0x00+2+nFlag+(nGrp-1)*GRP_LIST_STRUCT_LEN];
	return nRet;
}
void	CPCSWApp::SetGrplistName(int nFlag,int nGrp,CString& str,int nLen)
{
	BYTE*	ptr = &m_CommInfo.pGroupList[0x00+2+nFlag+(nGrp-1)*GRP_LIST_STRUCT_LEN];
	BYTE *szTemp  = new BYTE [nLen*2];
	memset(szTemp,0x00,nLen*2);
	memset(ptr,0x00,nLen);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)szTemp,nLen);
	memcpy(ptr,szTemp,nLen);
	delete	szTemp;
}
void	CPCSWApp::SetGrplistInfo(int nFlag,int nGrp,int nVal)
{
	m_CommInfo.pGroupList[0x00+2+nFlag+(nGrp-1)*34] = nVal;
}
//设置联系人序列号
void	CPCSWApp::SetGrplistContnum(int nFlag,int nGrp,int nRound,int nVal)
{
	m_CommInfo.pGroupList[0x00+2+nFlag+(nGrp-1)*34+nRound-1] = nVal;
}
void	CPCSWApp::SetGrplistCount(int nVal)
{
	m_CommInfo.pGroupList[0x00] = nVal;
	m_CommInfo.pGroupList[0x01] = (WORD)nVal>>8;
}
/************************************************************************/
/* SMS短信内容
*/
/************************************************************************/
void	CPCSWApp::SetSmsCount(int nVal)
{
	m_CommInfo.pShortText[0x00] = nVal;
	m_CommInfo.pShortText[0x01] = (WORD)nVal>>8;
}
int		CPCSWApp::GetSmsInfo(int nGrp,int nFlag)
{
	int nRet = m_CommInfo.pShortText[0x00+2+nFlag+(nGrp-1)*SHORTTEXT_STRUCT_LEN];
	return nRet;
}

void	CPCSWApp::SetSmsContent(int nFlag,int nGrp,CString& str,int nLen)
{
	memset(&m_CommInfo.pShortText[0x00+2+nFlag+(nGrp-1)*SHORTTEXT_STRUCT_LEN],0x00,SHORTTEXT_STRUCT_LEN-2);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)(&m_CommInfo.pShortText[0x00+2+nFlag+(nGrp-1)*SHORTTEXT_STRUCT_LEN]),160);

	//如果该序号不为零，代表该序号有数据
// 	SetSmsInfo(SMS_TXTNUM,nGrp,nGrp);
	int nSmsnum = GetSmsInfo(nGrp,SMS_TXTNUM);
	int	nLeng = GetSmsInfo(nGrp,SMS_TXTLEN);
	if(nSmsnum !=0 && nLeng!=0)
	{
		int nUnicodeLength = 0;

		//共160个byte，成对出现
		for(int i=0;i<160;i+=2)
		{
			//如果第1个Byte和第2个Byte的数据都为0的时候,跳出循环.否则UNICODE的长度增加(2个byte)
			if((m_CommInfo.pShortText[0x00+2+nFlag+(nGrp-1)*SHORTTEXT_STRUCT_LEN+i])==0x00
				&&	(m_CommInfo.pShortText[0x00+2+nFlag+(nGrp-1)*SHORTTEXT_STRUCT_LEN+i+1])==0x00)
				break;
			else
				nUnicodeLength+=2;
		}
		//设置文本长度
		if(str.IsEmpty())
			SetSmsInfo(SMS_TXTLEN,nGrp,0x00);
		else
			SetSmsInfo(SMS_TXTLEN,nGrp,nUnicodeLength);
	}
}
void	CPCSWApp::SetSmsInfo(int nFlag,int nGrp,int nVal)
{
	m_CommInfo.pShortText[0x00+2+nFlag+(nGrp-1)*SHORTTEXT_STRUCT_LEN] = nVal;
}
/************************************************************************/
/*信道信息设置 
*/
/************************************************************************/
void	CPCSWApp::SetFreq(int nZone,int nCh,int nFlag,CString& str,bool bRx /* = true */)
{
	BYTE*	ptr;
	ptr = &m_CommInfo.pChannelInfo[0x00+nFlag+(nZone-1)*736+(nCh-1)*46];
	if(str.IsEmpty())
	{
		*ptr++ = 0xff;
		*ptr++ = 0xff;
		*ptr++ = 0xff;
		*ptr = 0xff;
	}
	else
	{
		int nIndex;
		long	lTmp1,lTmp2;
		CString		strTmp = str;
		if (str.Find('.')<0)
		{
			strTmp+=".000000";
		}
		else
			strTmp+="000000";
		nIndex = strTmp.Find('.');
		strTmp.Insert(nIndex+7,'.');
		strTmp.Delete(nIndex);
		lTmp1 = _ttol(strTmp.GetBuffer());
		strTmp.ReleaseBuffer();
		lTmp2 = ((lTmp1+75)/12500*12500);
		if((lTmp1/100)==(lTmp2/100))
			lTmp1 = lTmp2;
		else
			lTmp1 = (lTmp1/12500)*12500;
		strTmp.Format("%x",lTmp1);
		char	ch;
		BYTE	byData;
		int i=0,nLength = strTmp.GetLength()-1;
		for (i=nLength;i>=0;i--)
		{
			ch = strTmp.GetAt(nLength-i);
			if (ch<='9'&& ch>='0')
			{
				byData = ch-'0';
			}
			else if(ch>='a'&& ch<='f')
				byData = ch-'a'+10;
			else
				break;
			if(i%2==0)
				*(ptr+i/2) = (*(ptr+i/2)&0xf0)|byData;
			else
				*(ptr+i/2) = (*(ptr+i/2)&0x0f)|(byData<<4);
		}
	}

}