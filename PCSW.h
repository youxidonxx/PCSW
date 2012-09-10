// PCSW.h : main header file for the PCSW application
//

#if !defined(AFX_PCSW_H__7C800AF9_C460_4921_97F5_B7CCD19C3F7A__INCLUDED_)
#define AFX_PCSW_H__7C800AF9_C460_4921_97F5_B7CCD19C3F7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


/************************************************************************/
/* �깦��: ����ˢ��ʱ��ˢ��ָ���ؼ�����Ŀհ�����;����Ч���ⴰ����˸
/* ʹ����: WM_ERASEBKGND ��Ϣ������ OnEraseBkgnd(); 
/************************************************************************/
// #define ERASE_BKGND_BEGIN  
// 	{
// 		CRect bgRect; 
// 		GetWindowRect(&bgRect); 
// 		CRgn bgRgn; 
// 		bgRgn.CreateRectRgnIndirect(bgRect);
// 	}
// #define ADD_NOERASE_CONTROL(IDC) 
// 	{ 
// 		CRect controlRect; 
// 		GetDlgItem(IDC)->GetWindowRect(&controlRect); 
// 		CRgn controlRgn; 
// 		controlRgn.CreateRectRgnIndirect(controlRect); 
// 		if(bgRgn.CombineRgn(&bgRgn, &controlRgn, RGN_XOR)==ERROR) 
// 			return false; 
// 	}
// #define ADD_NOERASE_RECT(noEraseRect) 
// 	{ 
// 		CRgn noEraseRgn; 
// 		noEraseRgn.CreateRectRgnIndirect(noEraseRect); 
// 		if(bgRgn.CombineRgn(&bgRgn, &noEraseRgn, RGN_XOR)==ERROR) 
// 			return false; 
// 	}
// 	// Marco parameter 'pDC' is a kind of (CDC *) type.
// 	// Marco parameter 'clBrushColor' specifies the color to brush the area.
// #define ERASE_BKGND_END(pDC, clBrushColor) 
// 	{
// 		CBrush brush; 
// 		brush.CreateSolidBrush(clBrushColor); 
// 		CPoint saveOrg = (pDC)->GetWindowOrg(); 
// 		(pDC)->SetWindowOrg(bgRect.TopLeft()); 
// 		(pDC)->FillRgn(&bgRgn, &brush); 
// 		(pDC)->SetWindowOrg(saveOrg); 
// 		brush.DeleteObject(); 
// 	}
// 		//#define ERASE_BKGND_END

extern	CString		ConvertStrintToStrhex(CString&	strInt);

extern	void	ConvertCString2String(CString&	strSrc,std::string&	strDes);
//nLen��ͬʱ������Ϊ���÷��ĳ��Ȳο�,ֻ��ת��freqƵ�㣬
extern	BYTE*	ConvertStrToIntArray(CString	str,int& nLen);
//����ֻ���ڴ洢7λID����
extern	BYTE*	ConvertStrTo7ID(CString str,int nLen);

extern	void	AddStrTailZero(CString&	str,int nDesiredLen);

/////////////////////////////////////////////////////////////////////////////
// CPCSWApp:
// See PCSW.cpp for the implementation of this class
//
typedef 	struct	tagCommInfo
{
	bool		bHasInfo;
	unsigned	char	pHead[64];
	unsigned	char	pRadioInfo[0x100];//���У����ͣ��汾��Ƶ��==16+8+2+4+4+4==38==>����汾
	unsigned	char	pRadioSetting[0x100];//TOT,����,VOX,��ʾ��,����,ң��,����ʱ��===1+1+4(tot)+1+1+4(vox)+1+1+1+6(tone)+5==(26) +4+12==(16) ===42
	unsigned	char	pEmergencySetting[0x100];//��������==16+12==>(28)
	unsigned	char	pMenuSetting[0x100];//�˵�����/�ر�����===25
	unsigned	char	pKeyFunctionSetting[0x100];//��������==11

	unsigned	char	pZoneInfo[0x1000];	//������Ϣ
	unsigned	char	pChannelInfo[0x4000];//�ŵ���Ϣ���

	unsigned	char	pScanInfo[0x1000];//ɨ�����

	unsigned	char	pContactInfo[0x2000];//��ϵ����Ϣ

	unsigned	char	pGroupList[0x2000];//����б�

	unsigned	char	pShortText[0x2000];//����ı�����
}CommInfo,*pCommInfo;
class map_value_finder
{
public:
	map_value_finder(const DWORD &cmp_info):m_s_cmp_info(cmp_info){}
	bool operator ()(const map<int,DWORD>::value_type &pair)
	{
		return pair.second == m_s_cmp_info;
	}
private:
	const DWORD &m_s_cmp_info; 
};

class CPCSWApp : public CWinApp
{
public:
	CPCSWApp();
	CPtrArray	m_template;
	CPtrArray	m_Frame;

	CommInfo	m_CommInfo;
public:
	void		UpdateActiveView();
public:
	//
	void		SetFreqScope(int nRange);
	int			GetFreqScope();
	int			GetFreqBoundry(bool bMax = true);//��ȡƵ�ʱ߽�ֵ
	void		SetAlarmName(int nFlag,CString& str,int nLen);
	//CONTACT��ϵ��
	CString		GetContName(int nGrp,int	nLen);
	CString		GetContID(int nGrp,int nLen);
	int			GetContInfo(int nFlag,int nGrp);
	void		SetContInfo(int nFlag,int nGrp,int nVal);
	void		SetContName(int nFlag,int nGrp,CString&	str,int nLen);
	void		SetContID(int nFlag,int nGrp,CString&	str);
	void		SetContCount(int nVal);
	//GRPLIST ����б�
	CString		GetGrplistName(int nGrp,int nLen);
	int			GetGrplistInfo(int nFlag,int nGrp,int nLen);
	int			GetGrplistCount();
	void		SetGrplistInfo(int nFlag,int nGrp,int nVal);
	void		SetGrplistContnum(int nFlag,int nGrp,int nRound,int nVal);
	void		SetGrplistCount(int nVal);
	void		SetGrplistName(int nFlag,int nGrp,CString&	str,int nLen);
	//SMS ��������
	void		SetSmsCount(int nVal);
	void		SetSmsContent(int nFlag,int nGrp,CString&	str,int	nLen);
	void		SetSmsInfo(int nFlag,int nGrp,int nVal);
	int			GetSmsInfo(int nGrp,int nFlag);
	//SCANLIST ɨ���б�
	CString		GetScanlistName(int nFlag,int nLen,int nList);
	CString		GetName(int nZone,int nCh,int nFlag,int nLen,
		int nStep1  = 736 ,int nStep2  = 46 ,bool bCh  = true );
	int			GetScanlistCount();
	//ZONE/CHANNEL	������Ϣ/�ŵ���Ϣ
	void		SetFreq(int nZone,int nCh,int nFlag,CString&	str,bool bRx = true);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSWApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPCSWApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCSW_H__7C800AF9_C460_4921_97F5_B7CCD19C3F7A__INCLUDED_)
