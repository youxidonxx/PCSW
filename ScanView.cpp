// ScanView.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "ScanView.h"
#include "ZoneInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static	CString	strASS[] = {"未配置","已配置"};
static	CString	strMODE[] = {"时间模式","载波模式"};
static	CString	strTXMODE[] = {"当前信道","最后活动信道","最后使用信道","指定信道"};
static	CString	strCALLBACK[]={"关闭","开启"};
/////////////////////////////////////////////////////////////////////////////
// CScanView

IMPLEMENT_DYNCREATE(CScanView, CFormView)

CScanView::CScanView()
	: CFormView(CScanView::IDD)
{
	//{{AFX_DATA_INIT(CScanView)
	//}}AFX_DATA_INIT
	m_CurrentList = 1;
	m_ListCount = 1;
	m_bCallback = false;
}

CScanView::~CScanView()
{
}

void CScanView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanView)
	DDX_Control(pDX, IDC_COMBO_SCAN_CALLBACK, m_cbScanCallback);
	DDX_Control(pDX, IDC_COMBO_SCANMODE, m_cbScanMode);
	DDX_Control(pDX, IDC_COMBO_SCAN_TXMODE, m_cbScanTxMode);
	DDX_Control(pDX, IDC_COMBO_SCAN_TXCHANNEL, m_cbScanTcCh);
	DDX_Control(pDX, IDC_COMBO_SCAN_SENDDELAY, m_cbScanSendDelay);
	DDX_Control(pDX, IDC_COMBO_SCAN_RCVDELAY, m_cbScanRcvDelay);
	DDX_Control(pDX, IDC_COMBO_SCAN_ON_TIME, m_cbScanTime);
	DDX_Control(pDX, IDC_EDIT_SCANLIST_NAME, m_editScanName);
	DDX_Control(pDX, IDC_LIST_USED_CHANNEL, m_ListUsedCh);
	DDX_Control(pDX, IDC_LIST_AVAIBLE_CHANNEL, m_ListAvaibleCh);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanView, CFormView)
	//{{AFX_MSG_MAP(CScanView)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnButtonPrev)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_ON_TIME, OnSelchangeComboScanOnTime)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_RCVDELAY, OnSelchangeComboScanRcvdelay)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_SENDDELAY, OnSelchangeComboScanSenddelay)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_TXCHANNEL, OnSelchangeComboScanTxchannel)
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_TXMODE, OnSelchangeComboScanTxmode)
	ON_CBN_SELCHANGE(IDC_COMBO_SCANMODE, OnSelchangeComboScanmode)
	ON_BN_CLICKED(IDC_RADIO_CALLBACK, OnRadioCallback)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_SCAN_CALLBACK,OnCbnSelchangeComboScanCallback)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanView diagnostics

#ifdef _DEBUG
void CScanView::AssertValid() const
{
	CFormView::AssertValid();
}

void CScanView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScanView message handlers

void CScanView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
 

	m_editScanName.SetLimitText(16);
	LoadData();
}

void CScanView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
// 	LoadData();
}
void	CScanView::LoadData()
{
	m_ListAvaibleCh.ResetContent();
	m_ListUsedCh.ResetContent();
	m_cbScanTcCh.ResetContent();
	m_cbScanCallback.ResetContent();
	m_cbScanMode.ResetContent();
	m_cbScanTxMode.ResetContent();
 	m_cbScanSendDelay.ResetContent();
	m_cbScanRcvDelay.ResetContent();
	m_cbScanTime.ResetContent();
	ComboAddString();

	m_ListCount = ((CPCSWApp*)AfxGetApp())->GetScanlistCount();
		//GetScanlistCount();
		//((CPCSWDoc*)GetDocument())->GetTotalList();
	CString	str = ((CPCSWApp*)AfxGetApp())->GetScanlistName(SCAN_NAME,SCAN_NAMEBYTE,m_CurrentList);
		//((CPCSWDoc*)GetDocument())->GetScanListName(SCAN_NAME,SCAN_NAMEBYTE,m_CurrentList);
	m_editScanName.SetWindowText(str);
	//按键状态
// 	EnableButton();
//下拉列表初始化——除去跳转信道
//  	SetDefaultTime(false);
	//两个列表框初始化
	ScanlistAllShow();
	EnableButton();
	int nVal = GetScanlistInfo(SCAN_TXMODE,m_CurrentList);
	m_cbScanTxMode.SetCurSel(nVal);
		//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_TXMODE,m_CurrentList);
	if ((nVal<3))//不是跳转信道
	{//指定信道列表
		m_cbScanTcCh.EnableWindow(FALSE);
	}
	else
		m_cbScanTcCh.EnableWindow(TRUE);
	 nVal=	GetScanlistInfo(SCAN_CALLBACK,m_CurrentList);
		 //((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_CALLBACK,m_CurrentList);
 	((CButton*)GetDlgItem(IDC_RADIO_CALLBACK))->SetCheck(nVal);
	m_cbScanCallback.SetCurSel(nVal);
	nVal = GetScanlistInfo(SCAN_MODE,m_CurrentList);
 	m_cbScanMode.SetCurSel(nVal);
	//时间保持数需要递减
	nVal = GetScanlistInfo(SCAN_RCVDELAY,m_CurrentList);
	nVal-=2;
	m_cbScanRcvDelay.SetCurSel(nVal);
	nVal = GetScanlistInfo(SCAN_SENDDELAY,m_CurrentList);
	nVal-=2;
	m_cbScanSendDelay.SetCurSel(nVal);
	nVal = GetScanlistInfo(SCAN_ONTIME,m_CurrentList);
	nVal-=2;
	m_cbScanTime.SetCurSel(nVal);
	
}
void	CScanView::ComboAddString()
{
	int i=0;
	CString	str;
 	for (i=1;i<40;i++)
	{
		str.Format("%.1f",(i+1)*0.5);
		m_cbScanSendDelay.AddString(str);
		m_cbScanRcvDelay.AddString(str);
		m_cbScanTime.AddString(str);
	}
	for(i=0;i<4;i++)
	{
		if (i<2)
		{
			m_cbScanCallback.AddString(strCALLBACK[i]);
			m_cbScanMode.AddString(strMODE[i]);
		}
		m_cbScanTxMode.AddString(strTXMODE[i]);
	}
 }

int		CScanView::GetScanlistInfo(int nFlag,int nList)
{
	BYTE*	pScan = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
	int nRet = pScan[0x00+2+nFlag+(nList-1)*60];
	return nRet;
}
void	CScanView::SetScanCommmonValues(int nFlag,int nList,int nVal,int nLen /* = 1 */)
{
	BYTE*	pScan = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
	pScan[0x00+2+nFlag+(nList-1)*60] = nVal;
}
void	CScanView::SetScanName(int nFlag,int nList,int nLen,CString& str)
{
	BYTE *ptr,*pScan;
	pScan = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
	BYTE *szTemp  = new BYTE [nLen*2];
	memset(szTemp,0x00,nLen*2);
	ptr = &pScan[0x00+2+nFlag+(nList-1)*60];
	memset(ptr,0x00,nLen);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)szTemp,nLen);
	memcpy(ptr,szTemp,nLen);
	delete	szTemp;
}
void		CScanView::SetScanChFlag(int nFlag,int nVal,int nList,int nRound,bool bCh /* = true */)
{
	BYTE*	pScan = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
	if(bCh)
		pScan[0x00+2+nFlag+(nList-1)*60+(nRound-1)*2+1] = nVal;
	else
		pScan[0x00+2+nFlag+(nList-1)*60+(nRound-1)*2]= nVal;
}
void	CScanView::SetScanChannelCount(int nFlag,int nList,int nVal)
{
	BYTE*	pScan = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
	pScan[0x00+2+nFlag+(nList-1)*60] = nVal;
}
CString	CScanView::GetChannelName(int ByteLen,int nFlag,int nZone,//所要获取的区域号
								  int nChannel,					//所要获取的信道号
								  int nStep1 /*= 736*/,int nStep2 /*= 46*/,bool	bCh /* = true*/)
{
	BYTE*	ptr,*info;
	BYTE* szTemp = new BYTE[ByteLen*2];
	if(bCh)
	{
		info = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
		ptr = info+(nZone-1)*nStep1+(nChannel-1)*nStep2; 
			//	pChannelInfo+nFlag+(nZone-1)*nStep1+(nChannel-1)*nStep2;
	}
	else
	{
		info = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
		ptr = info+(nZone-1)*nStep1+(nChannel-1)*nStep2; 
			//pZoneInfo+nFlag+(nZone-1)*nStep1+(nChannel-1)*nStep2;
	}
	memcpy(szTemp,ptr,ByteLen);
	szTemp[ByteLen] = szTemp[ByteLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(ByteLen),ByteLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTemp;
	return str;
}

int	CScanView::GetScanlistChInfo(int nFlag,int nLen,int nListnum,int nChnum,bool bChOrZone /* = true */)
{
	BYTE*	ptr = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pScanInfo;
	int nCh = ptr[0x00+2+nFlag+(nListnum-1)*60+(nChnum-1)*2+1];
	int nZone = ptr[0x00+2+nFlag+(nListnum-1)*60+(nChnum-1)*2];
	if(nCh>16)
		nCh = 0xff;
	else
		nCh+=1;
	if(nZone>16)
		nZone = 0xff;
	else
		nZone+=1;
	if(bChOrZone)//默认为信道号
		return nCh;
	else
		return nZone;
}
//////////////////////////////////////////////////////////////////////////
///////////////////////////设置写入操作时的数据///////////////////////////////////////////////
void	CScanView::SetWriteMsg()
{
	SetScanCommmonValues(SCAN_CALLBACK,((CButton*)GetDlgItem(IDC_RADIO_CALLBACK))->GetCheck(),m_CurrentList);
	SetScanCommmonValues(SCAN_MODE,m_cbScanMode.GetCurSel(),m_CurrentList);
	SetScanCommmonValues(SCAN_RCVDELAY,m_cbScanRcvDelay.GetCurSel(),m_CurrentList);
	SetScanCommmonValues(SCAN_SENDDELAY,m_cbScanSendDelay.GetCurSel(),m_CurrentList);
	SetScanCommmonValues(SCAN_TXCHANNEL,m_cbScanTcCh.GetCurSel(),m_CurrentList);
	SetScanCommmonValues(SCAN_ONTIME,m_cbScanTime.GetCurSel(),m_CurrentList);
	SetScanCommmonValues(SCAN_TXMODE,m_cbScanTxMode.GetCurSel(),m_CurrentList);

// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_CALLBACK,((CButton*)GetDlgItem(IDC_RADIO_CALLBACK))->GetCheck(),m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_MODE,m_cbScanMode.GetCurSel(),m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_RCVDELAY,m_cbScanRcvDelay.GetCurSel(),m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_SENDDELAY,m_cbScanSendDelay.GetCurSel(),m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_TXCHANNEL,m_cbScanTcCh.GetCurSel(),m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_ONTIME,m_cbScanTime.GetCurSel(),m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_TXMODE,m_cbScanTxMode.GetCurSel(),m_CurrentList);

	CString	str;
	m_editScanName.GetWindowText(str.GetBuffer(16),16);
	str.ReleaseBuffer();
	SetScanName(SCAN_NAME,m_CurrentList,SCAN_NAMEBYTE,str);
// 	((CPCSWDoc*)GetDocument())->SetScanname(SCAN_NAME,SCAN_NAMEBYTE,m_CurrentList,str);
	//准备写入列表内容
	int nCnt = m_ListUsedCh.GetCount();
	for (int i=0;i<nCnt;i++)
	{
		m_ListUsedCh.GetText(i,str);
		//对字符串进行处理，并写入doc中
		HandleStr(str,i);
		str.Empty();
	}
}
bool	CScanView::HandleStr(const CString& str,int nRound)
{
	if(str.GetLength()<=0)
		return false;
	CString	strTmp = str;
	int pos=0;
	pos = strTmp.Find(":");
	if (pos>0)
	{
		CString	strZone = strTmp.Mid(0,pos);
		CString	strCh = strTmp.Mid(pos+1,str.GetLength());
		int nTotal = strZone.GetLength();
		int nLen = lstrlen("区域");
		char nval ;
		strZone = (strZone.Mid(nLen, nTotal));
		nval =_ttoi(strZone);
		//取出数字后还要将取得数字-1，在数据中区域1从0开始
//  		((CPCSWDoc*)GetDocument())->SetChFlag(SCAN_CHANNELFLAG+2,nval-1,m_CurrentList,nRound,FALSE);
		SetScanChFlag(SCAN_CHANNELFLAG+2,nval-1,m_CurrentList,nRound,FALSE);
		nLen = lstrlen("信道");
		nTotal = strCh.GetLength();
		strCh = strCh.Mid(nLen,nTotal);
		nval = _ttoi(strCh);
		SetScanChFlag(SCAN_CHANNELFLAG+2,nval-1,m_CurrentList,nRound);
// 		((CPCSWDoc*)GetDocument())->SetChFlag(SCAN_CHANNELFLAG+2,nval-1,m_CurrentList,nRound);

	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void	CScanView::ScanlistAllShow(void)
{
	mapAllChannel.clear();
	mapUsedChannel.clear();
	//清除原有数据
	int i,j;
 	CString	strZone,strCh;
	int nCh,nZone;
	m_cbScanTcCh.AddString("当前信道");
	for (i=0;i<16;i++)
	{
		//将各个信道别名与其区域字符串显示在列表中		
		//获取各个区域信道数----共16个区域
		for (j=0;j<16;j++)
		{
			//获取当前区域别名
			strZone = ((CPCSWApp*)AfxGetApp())->GetName(i+1,j+1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,18,0,false);
				//((CPCSWDoc*)GetDocument())->GetChannelName(CZoneInfo::ZONE_CHANNEL_NAME_BYTE,CZoneInfo::ZONE_NAME,i,j,18,0,false);
			strCh = ((CPCSWApp*)AfxGetApp())->GetName(i+1,j+1,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE);
				//((CPCSWDoc*)GetDocument())->GetChannelName(CZoneInfo::ZONE_CHANNEL_NAME_BYTE,CZoneInfo::CHANNEL_CHANNAME,i,j);
			if(!(strCh.IsEmpty() ||strZone.IsEmpty()))
			{
				m_ListAvaibleCh.AddString(strZone+":"+strCh);
 				nCh = DWORD(j)&0x00ff;
				nZone = (DWORD(i)<<8)&0xff00;
				mapAllChannel.insert(pair<int,DWORD>(i*16+j,nZone|nCh));
				m_cbScanTcCh.AddString(strZone+":"+strCh);
			}
		}
	}
	//查找发射信道的显示值
	nCh = GetScanlistChInfo(SCAN_CHANNELFLAG,1,m_CurrentList,1);
	nZone = GetScanlistChInfo(SCAN_CHANNELFLAG,1,m_CurrentList,1,false);
	nCh = DWORD(nCh-1)&0x00ff;
	nZone = (DWORD(nZone-1)<<8)&0xff00;
	map_it = find_if(mapAllChannel.begin(),mapAllChannel.end(),map_value_finder(nZone|nCh));
	if (map_it == mapAllChannel.end())
	{//说明未找到
	}
	else
		m_cbScanTcCh.SetCurSel(map_it->first);


		//扫描列表中信道数量
		int nChCnt = GetScanlistInfo(SCAN_CHANNELNUM,m_CurrentList);
			//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_CHANNELNUM,m_CurrentList);
		//获取当前区域上的信道列表
		if (nChCnt==0xff)
		{
			nChCnt = 0;
			m_ListUsedCh.AddString("无信道");
		}
		for(i=0;i<nChCnt;i++)
		{
			nCh =	GetScanlistChInfo(SCAN_CHANNELFLAG,1,m_CurrentList,i+1);
				//((CPCSWDoc*)GetDocument())->GetScanlistInfo(SCAN_CHANNELFLAG,1,m_CurrentList,i+1);
			nZone =	 GetScanlistChInfo(SCAN_CHANNELFLAG,1,m_CurrentList,i+1,false);
				//((CPCSWDoc*)GetDocument())->GetScanlistInfo(SCAN_CHANNELFLAG,1,m_CurrentList,i+1,false);
			if (nCh!=0xff && nZone!=0xff)
			{
				strCh = ((CPCSWApp*)AfxGetApp())->GetName(nZone,nCh,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE);
					//GetChannelName(ZONE_CHANNEL_NAME_BYTE,CHANNEL_CHANNAME,nZone,nCh);
					//((CPCSWDoc*)GetDocument())->GetChannelName(CZoneInfo::ZONE_CHANNEL_NAME_BYTE,CZoneInfo::CHANNEL_CHANNAME,nZone,nCh);
 				strZone = ((CPCSWApp*)AfxGetApp())->GetName(nZone,nCh,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,18,0,false);
					//GetChannelName(ZONE_CHANNEL_NAME_BYTE,ZONE_NAME,nZone,nCh,18,0,false);
					//((CPCSWDoc*)GetDocument())->GetChannelName(CZoneInfo::ZONE_CHANNEL_NAME_BYTE,CZoneInfo::ZONE_NAME,nZone,nCh,18,0,false);
 				m_ListUsedCh.AddString(strZone+":"+strCh);
				nCh = DWORD(nCh-1)&0x00ff;
				nZone = (DWORD(nZone-1)<<8)&0xff00;
				mapUsedChannel.insert(pair<int,DWORD>(i,nZone|nCh));
			}

		}
		

		m_ListCount =	((CPCSWApp*)AfxGetApp())->GetScanlistCount();
			//((CPCSWDoc*)GetDocument())->GetTotalList();
}
void	CScanView::SetDefaultTime(bool	bRead /* = true*/)//是否是新建列表时的数据
{
	m_cbScanTime.ResetContent();
	m_cbScanRcvDelay.ResetContent();
	m_cbScanSendDelay.ResetContent();
	m_cbScanTxMode.ResetContent();
	m_cbScanMode.ResetContent();
	CString	str;
	int i=0;
	int nStart = 1;
	double nTotal;
 	while ((nTotal =nStart+i*0.5)<=20)
	{
		str.Format("%.1f",nTotal);
		m_cbScanTime.AddString(str);
		m_cbScanRcvDelay.AddString(str);
		m_cbScanSendDelay.AddString(str);
		if (i<4)
		{
			m_cbScanTxMode.AddString(strTXMODE[i]);
			if(i<2)
			{	
				m_cbScanCallback.AddString(strCALLBACK[i]);
				m_cbScanMode.AddString(strMODE[i]);
			}
		}
		i++;
	}
	if (bRead)
	{
		m_cbScanTime.SetCurSel(10);
		m_cbScanRcvDelay.SetCurSel(10);
		m_cbScanSendDelay.SetCurSel(10);
		m_cbScanTxMode.SetCurSel(0);
		m_cbScanMode.SetCurSel(0);
		m_cbScanCallback.SetCurSel(0);
	}
	else
	{
		int nRet = GetScanlistInfo(SCAN_ONTIME,m_CurrentList);
			//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_ONTIME,m_CurrentList);
		m_cbScanTime.SetCurSel( GetScanlistInfo(SCAN_ONTIME,m_CurrentList));
			//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_ONTIME,m_CurrentList));
		m_cbScanRcvDelay.SetCurSel( GetScanlistInfo(SCAN_RCVDELAY,m_CurrentList));
			//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_RCVDELAY,m_CurrentList));
		m_cbScanSendDelay.SetCurSel(GetScanlistInfo(SCAN_SENDDELAY,m_CurrentList));
			//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_SENDDELAY,m_CurrentList));
		m_cbScanTxMode.SetCurSel( GetScanlistInfo(SCAN_TXMODE,m_CurrentList));
		//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_TXMODE,m_CurrentList));
		m_cbScanMode.SetCurSel( GetScanlistInfo(SCAN_MODE,m_CurrentList));
		//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_MODE,m_CurrentList));
		m_cbScanCallback.SetCurSel(GetScanlistInfo(SCAN_CALLBACK,m_CurrentList));
		//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_CALLBACK,m_CurrentList));
	}

//	
}

//////////////////////按钮点击函数////////////////////////////////////////////////////
void CScanView::EnableButton()
{
	if(m_CurrentList>m_ListCount)
		m_CurrentList=m_ListCount;
	if(m_CurrentList==1)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
	}

	if(m_CurrentList==m_ListCount)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
	}
	
	CString strList;
	strList.Format("列表 %d/%d",m_CurrentList,m_ListCount);
	((CButton*)GetDlgItem(IDC_STATIC_SCANLIST))->SetWindowText(strList);
}
//添加信道列表中的信道
void CScanView::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here

 	//多选
	int nMultiSel = m_ListAvaibleCh.GetSelCount();
	if (nMultiSel == 0)
	{
		MessageBox("请在左边边框中选择要添加项目","提示");
		return;
	}
	//右边已有数目
	int	nUsedCnt = m_ListUsedCh.GetCount();
	if (nUsedCnt == 16)
	{
		MessageBox("当前扫描列表包含信道数已满，若要继续添加，请先删除","提示");
		return;
	}
	if(nMultiSel+nUsedCnt>16)
	{
		MessageBox("所选项目超出信道列表最大范围，请重新选择","提示");
		return;
	}
	int i=0;
	CArray<int,int>	arrSel;
	arrSel.SetSize(nMultiSel);
	int nIndex;
	DWORD	dwInfo;
	int		nCh,nZone;	
	m_ListAvaibleCh.GetSelItems(nMultiSel,arrSel.GetData());
	//一个个进行添加
	for (i=0;i<nMultiSel;i++)
	{
		nIndex = arrSel.GetAt(i);//获取所选的第一行开始，其在list中的行号
		dwInfo = mapAllChannel[nIndex];
		
		//检查该行的值是否在listused中，若在则提示不添加，否则添加
		map_it = find_if(mapUsedChannel.begin(),mapUsedChannel.end(),map_value_finder(dwInfo));
		if (map_it == mapUsedChannel.end())//最后，即未找到,可进行添加,往末尾添加
		{
			 mapUsedChannel.insert(pair<int,DWORD>(mapUsedChannel.size(),dwInfo));
		}
		else
		{
			MessageBox("所选值已存在当前信道列表中，请勿重复选择","提示");
// 			return;
		}
	}
	//将当前的usedlist中的value添加到chflag中
	int nCnt = mapUsedChannel.size();//列表总数
	SetScanChannelCount(SCAN_CHANNELNUM,m_CurrentList,nCnt);
	int n=1;
	for (map_it= mapUsedChannel.begin();map_it != mapUsedChannel.end();map_it++)
	{
		dwInfo = map_it->second;
		nCh = (int)(dwInfo&0x00ff);
		nZone = (int)(dwInfo>>8);
		SetScanChFlag(SCAN_CHANNELFLAG,nCh,m_CurrentList,n,true);
		SetScanChFlag(SCAN_CHANNELFLAG,nZone,m_CurrentList,n,FALSE);
		n++;
	}

	SetDefaultTime(true);
	LoadData();
}

void CScanView::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int nMultiSel = m_ListUsedCh.GetSelCount();
	if (nMultiSel == 0)
	{
		MessageBox("请在右边边框中选择要删除项目","提示");
		return;
	}
	CArray<int,int>	arrSel;
	arrSel.SetSize(nMultiSel);
	m_ListUsedCh.GetSelItems(nMultiSel,arrSel.GetData());
	int nIndex,i;
	DWORD	dwInfo;
	int		nCh,nZone;	
	for (i=0;i<nMultiSel;i++)
	{
		//一次删除一个，并写入内存
		nIndex = arrSel.GetAt(i);
		dwInfo = mapUsedChannel[nIndex];
		map_it = find_if(mapUsedChannel.begin(),mapUsedChannel.end(),map_value_finder(dwInfo));
		if (map_it == mapUsedChannel.end())
		{
			MessageBox("所选信道出现未知错误，请查看原始数据","提示");
			return;
		}
		mapUsedChannel.erase(map_it);
		//更新列表总数
		int nCnt = mapUsedChannel.size();//列表总数
		SetScanChannelCount(SCAN_CHANNELNUM,m_CurrentList,nCnt);
		int n=1;
		for (map_it= mapUsedChannel.begin();map_it != mapUsedChannel.end();map_it++)
		{
			dwInfo = map_it->second;
			nCh = (int)(dwInfo&0x00ff);
			nZone = (int)(dwInfo>>8);
			SetScanChFlag(SCAN_CHANNELFLAG,nCh,m_CurrentList,n,true);
			SetScanChFlag(SCAN_CHANNELFLAG,nZone,m_CurrentList,n,FALSE);
			n++;
		}
	}
	LoadData();
}

void CScanView::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	m_CurrentList = 1;
	LoadData();
}

void CScanView::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	m_CurrentList = m_ListCount;
	LoadData();
}

void CScanView::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	m_CurrentList++;
	LoadData();
}

void CScanView::OnButtonPrev() 
{
	// TODO: Add your control notification handler code here
	m_CurrentList--;
	LoadData();
}
//////////////////////////////////////////////////////////////////////////

/////////////////////////列表控件函数/////////////////////////////////////////////////
void CScanView::OnSelchangeComboScanOnTime() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbScanTime.GetCurSel();
	SetScanCommmonValues(SCAN_ONTIME,nSel,m_CurrentList);
//	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_ONTIME,nSel,m_CurrentList);
}

void CScanView::OnSelchangeComboScanRcvdelay() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbScanRcvDelay.GetCurSel();
	SetScanCommmonValues(SCAN_RCVDELAY,nSel,m_CurrentList);
//	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_RCVDELAY,nSel,m_CurrentList);
	
}

void CScanView::OnSelchangeComboScanSenddelay() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbScanSendDelay.GetCurSel();
	SetScanCommmonValues(SCAN_SENDDELAY,nSel,m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_SENDDELAY,nSel,m_CurrentList);
	
}

void CScanView::OnSelchangeComboScanTxchannel() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbScanTcCh.GetCurSel();
	SetScanCommmonValues(SCAN_TXCHANNEL,nSel,m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_TXCHANNEL,nSel,m_CurrentList);
	
}

void CScanView::OnSelchangeComboScanTxmode() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbScanTxMode.GetCurSel();
	SetScanCommmonValues(SCAN_TXMODE,nSel,m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_TXMODE,nSel,m_CurrentList);
	if (nSel == 3)//跳转信道
	{
		m_cbScanTcCh.EnableWindow(TRUE);
	}
	else
		m_cbScanTcCh.EnableWindow(FALSE);
	if (nSel ==1||nSel == 2)
	{
		m_cbScanCallback.SetCurSel(1);
		m_cbScanCallback.EnableWindow(FALSE);
		SetScanCommmonValues(SCAN_CALLBACK,1,m_CurrentList);
// 		((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_CALLBACK,1,m_CurrentList);
	}
	else
	{	
		m_cbScanCallback.EnableWindow(TRUE);
		m_cbScanCallback.SetCurSel(GetScanlistInfo(SCAN_CALLBACK,m_CurrentList));
			//((CPCSWDoc*)GetDocument())->GetScanInfo(SCAN_CALLBACK,m_CurrentList));
	}
}

void CScanView::OnSelchangeComboScanmode() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbScanMode.GetCurSel();
	SetScanCommmonValues(SCAN_MODE,nSel,m_CurrentList);
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_MODE,nSel,m_CurrentList);
}

void CScanView::OnRadioCallback() 
{
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetCommonValue(SCAN_CALLBACK,((CButton*)GetDlgItem(IDC_RADIO_CALLBACK))->GetCheck(),m_CurrentList);
}
//////////////////////////////////////////////////////////////////////////

void CScanView::OnCbnSelchangeComboScanCallback()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel = m_cbScanMode.GetCurSel();
	SetScanCommmonValues(SCAN_CALLBACK,nSel,m_CurrentList);
}
