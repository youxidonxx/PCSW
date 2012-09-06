// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7EDBC88F_9325_4F4A_AF20_457263F890BC__INCLUDED_)
#define AFX_MAINFRM_H__7EDBC88F_9325_4F4A_AF20_457263F890BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mybar.h"
#include "CSerial.h"
#include "PCSWDoc.h"
#include "SplitterWnd.h"
#include "spstruct.h"

typedef	struct	_tagCOMM_EVENT
{
	CWnd*	pMainframe;
	CSerial*	pSerial;
	CString		strSetting;
	unsigned	char*	pRadioInfo;//序列，机型，版本，频率==16+8+2+4+4+4==38==>界面版本
	unsigned	char*	pRadioSetting;//TOT,静噪,VOX,提示音,背光,遥弊,呼叫时间===1+1+4(tot)+1+1+4(vox)+1+1+1+6(tone)+5==(26) +4+12==(16) ===42
	unsigned	char*	pEmergencySetting;//报警设置==16+12==>(28)
	unsigned	char*	pMenuSetting;//菜单开启/关闭设置===25
	unsigned	char*	pKeyFunctionSetting;//按键设置==11
	
	unsigned	char*	pZoneInfo;	//区域信息
	unsigned	char*	pChannelInfo;//信道信息相关

	unsigned	char*	pScanInfo;//扫描相关

	unsigned	char*	pContactInfo;//联系人信息

	unsigned	char*	pGroupList;//组呼列表

	unsigned	char*	pShortText;//快捷文本内容

	bool	bCancel;
	BOOL	bRead;
	int		nRet;
	bool	bZoneExist[16];
	bool	bChannelExist[16];
	int		percent;
	int		nNewComm;
	int		nPsWrong;
	BYTE	szPara[40];
}COMM_EVENT;

// typedef 	struct	tagCommInfo
// {
// 	bool		bHasInfo;
// 	unsigned	char	pHead[0x40];
// 	unsigned	char	pRadioInfo[0x100];//序列，机型，版本，频率==16+8+2+4+4+4==38==>界面版本
// 	unsigned	char	pRadioSetting[0x100];//TOT,静噪,VOX,提示音,背光,遥弊,呼叫时间===1+1+4(tot)+1+1+4(vox)+1+1+1+6(tone)+5==(26) +4+12==(16) ===42
// 	unsigned	char	pEmergencySetting[0x100];//报警设置==16+12==>(28)
// 	unsigned	char	pMenuSetting[0x100];//菜单开启/关闭设置===25
// 	unsigned	char	pKeyFunctionSetting[0x100];//按键设置==11
// 
// 	unsigned	char	pZoneInfo[0x1000];	//区域信息
// 	unsigned	char	pChannelInfo[0x4000];//信道信息相关
// 
// 	unsigned	char	pScanInfo[0x1000];//扫描相关
// 
// 	unsigned	char	pContactInfo[0x2000];//联系人信息
// 
// 	unsigned	char	pGroupList[0x2000];//组呼列表
// 
// 	unsigned	char	pShortText[0x2000];//快捷文本内容
// }CommInfo,*pCommInfo;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
//	void	InitData();
// Attributes
	void	TransferCommData();
protected:
	CPCSWDoc*	GetDocument();

public:
// 	CommInfo	m_CommInfo;

    mybar m_CtrlBar;
	int		m_nPaud;//波特率
	int		m_nComm;
	bool	m_bReadyComm;// 串口是否正确选择
	CSerial	m_SerialPort;//串口
	CWinThread*	m_pThread;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	void	SwitchView(int nIndex);
	virtual ~CMainFrame();
	void	UpdateAllViews(int nFlag);
	void	UpdateViewData();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg LRESULT ShowChildWindow(WPARAM wParam,LPARAM lParam);

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CSplitterWndEx	m_wndSplit;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnReadParameter();
	afx_msg void OnCommSet();
	afx_msg void OnUpdateReadParameter(CCmdUI* pCmdUI);
	afx_msg void OnWriteParameter();
	afx_msg void OnUpdateWriteParameter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7EDBC88F_9325_4F4A_AF20_457263F890BC__INCLUDED_)
