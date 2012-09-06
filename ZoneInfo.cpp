// ZoneInfo.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "ZoneInfo.h"
#include "GridCtrl.h"
#include "GridEdit.h"
#include "spmsgid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	CHANNEL_STRUCT_INFO	sizeof(gCHANNEL_S)
enum	COLUMNLEN
{
	COLUMN_NARROW = 60,
	COLUMN_NORMAL = 120,
	COLUMN_WIDE	  = 200
};
static	CString	strChannelInfo[] = {"信道号",
		"信道配置标识","扫描列表","信道工作模式","信道工作状态","信道别名","发射频点","接收频点",
		"发射功率","信道间隔","语音增强等级","亚音频尾音消除相位变化","繁忙锁定","发射模拟信令类型",
		"发射模拟信令号","接收模拟信令类型","接收模拟信令号","接收组列表","发射默认联系人","礼貌方式",
		"语音加密","语音加密密钥"
};
static	CString	strCHASS[] = {"未配置","数字信道","模拟信道","自适应信道"};
static	CString	strSCANLIST[] = {"未配置扫描列表","扫描列表"};
static	CString	strMODE[] = {"直通模式","中转模式"};
static	CString	strSTATUS[] = {"不脱网","脱网"};
static	CString	strPOWER[] = {"低","高"};
static	CString	strINTERVAL[] = {"6.25KHz","12.5KHz","20KHz","25KHz"};
static	CString	strBUSYLOCK[] = {"繁忙时不锁定","繁忙锁定"};
static	CString	strSIGNALTYPE[] = {"无","CTCSS","CDCSS","反向CDCSS"};
static	CString	strPOLITE[] = {"任何情况允许发射","信道空闲时允许发射"};
static	CString	strCTCPHASE[] = {"180","120"};
static	CString	strSpeechEnhLev[] = {"关闭","1","2","3","4"};
/////////////////////////////////////////////////////////////////////////////
// CZoneInfo

IMPLEMENT_DYNCREATE(CZoneInfo, CFormView)

CZoneInfo::CZoneInfo()
	: CFormView(CZoneInfo::IDD)
{
	//{{AFX_DATA_INIT(CZoneInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(m_nZonechalnum,0x00,sizeof(16));
	m_nZonenum = 1;
	m_nCurrentZone = 1;
	m_nZonechalnum[m_nCurrentZone-1] = 16;

	int n=0;
	m_nChannelAddr[n++] = CHANNEL_CHASS;
	m_nChannelAddr[n++] = CHANNEL_SCANLIST;
	m_nChannelAddr[n++] = CHANNEL_MODE;
	m_nChannelAddr[n++] = CHANNEL_STATUS;
	m_nChannelAddr[n++] = CHANNEL_CHANNAME;
	m_nChannelAddr[n++] = CHANNEL_TX_FREQ;
	m_nChannelAddr[n++] = CHANNEL_RX_FREQ;
	m_nChannelAddr[n++] = CHANNEL_POWER_LEVEL;
	m_nChannelAddr[n++] = CHANNEL_INTERVAL;
	m_nChannelAddr[n++] = CHANNEL_SPEECH_ENHANCE_LEVEL;
	m_nChannelAddr[n++] = CHANNEL_CTC_PHASE;
	m_nChannelAddr[n++] = CHANNEL_BUSYLOCK;
	m_nChannelAddr[n++] = CHANNEL_TX_ANALOG_SIG_TYPE;
	m_nChannelAddr[n++] = CHANNEL_TX_ANALOG_SIG_NUM;
	m_nChannelAddr[n++] = CHANNEL_RX_ANALOG_SIG_TYPE;
	m_nChannelAddr[n++] = CHANNEL_RX_ANALOG_SIG_NUM;
	m_nChannelAddr[n++] = CHANNEL_DIGIT_RX_GROUP;
	m_nChannelAddr[n++] = CHANNEL_DIGIT_SEND_ID;
	m_nChannelAddr[n++] = CHANNEL_DIGIT_POLITE;
	m_nChannelAddr[n++] = CHANNEL_DIGIT_VOICEKEY_EN;
	m_nChannelAddr[n++] = CHANNEL_DIGIT_VOICEKEY;

/*
// 	{
// 				,CHANNEL_SCANLIST,CHANNEL_MODE,
// 				CHANNEL_STATUS,CHANNEL_CHANNAME,CHANNEL_TX_FREQ,
// 				CHANNEL_RX_FREQ,CHANNEL_POWER_LEVEL,CHANNEL_INTERVAL,
// 				CHANNEL_SPEECH_ENHANCE_LEVEL,CHANNEL_CTC_PHASE,CHANNEL_BUSYLOCK,
// 				CHANNEL_TX_ANALOG_SIG_TYPE,CHANNEL_TX_ANALOG_SIG_NUM,
// 				CHANNEL_RX_ANALOG_SIG_TYPE,CHANNEL_RX_ANALOG_SIG_NUM,
// 				CHANNEL_DIGIT_RX_GROUP,CHANNEL_DIGIT_SEND_ID,CHANNEL_DIGIT_POLITE,
// 				CHANNEL_DIGIT_VOICEKEY_EN,CHANNEL_DIGIT_VOICEKEY
// 	};
*/
	//m_nChannelAddr[21] = { 12,12};

}

CZoneInfo::~CZoneInfo()
{
}

void CZoneInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoneInfo)
	DDX_Control(pDX, IDC_EDIT_ZONENAME, m_editZonename);
  	DDX_Control(pDX, IDC_COMBO_ZONELIST, m_GridComboZone);
	DDX_Control(pDX, IDC_EDIT_ZONE, m_GridEditZone);
	//}}AFX_DATA_MAP
//	DDX_GridControl(pDX,IDC_GRID_ZONEINFO,m_GridCtrl);
	DDX_GridControl(pDX,IDC_GRID_ZONE,m_GridCtrl);
}


BEGIN_MESSAGE_MAP(CZoneInfo, CFormView)
	//{{AFX_MSG_MAP(CZoneInfo)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_CBN_KILLFOCUS(IDC_COMBO_ZONELIST, OnKillfocusComboZonelist)
	ON_CBN_SELCHANGE(IDC_COMBO_ZONELIST, OnSelchangeComboZonelist)
	//}}AFX_MSG_MAP
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_ZONE, OnEditGrid)
//  	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_ZONEINFO, OnEditGrid)

	ON_EN_KILLFOCUS(IDC_EDIT_ZONE, &CZoneInfo::OnEnKillfocusEditZone)
	ON_WM_ERASEBKGND()
	ON_EN_KILLFOCUS(IDC_EDIT_ZONENAME, &CZoneInfo::OnEnKillfocusEditZonename)
 END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoneInfo diagnostics

#ifdef _DEBUG
void CZoneInfo::AssertValid() const
{
	CFormView::AssertValid();
}

void CZoneInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZoneInfo message handlers

void CZoneInfo::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	//获取到每个区域的有效信道数
	m_nZonenum = 0;
	for (int i=1;i<=16;i++)
	{
		m_nZonechalnum[i-1] = GetChancountsInZone(i,ZONE_CHANNEL_NUM);
			//((CPCSWDoc*)GetDocument())->GetValidChannuumInZone(i,ZONE_CHANNEL_NUM);
		if(m_nZonechalnum[i-1]>0 && i>1)//超过1个以上区域含有信道信息
			m_nZonenum++;
	}
	LoadData();
	((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	
}
void	CZoneInfo::SetZonename()
{
	CString	str;
	str = GetName(m_nCurrentZone,1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,18,0,false);
	//	 ((CPCSWDoc*)GetDocument())->GetChannelName(ZONE_CHANNEL_NAME_BYTE,ZONE_NAME,m_nCurrentZone,1,18,0,false);
	m_editZonename.SetWindowText(str);
}
void	CZoneInfo::SetName(int nZone,int nCh,int nFlag,int nLen,CString& str,
						   int nStep1 /* = 736 */,int nStep2 /* = 46 */,bool bCh /* = true */)
{
	BYTE *ptr,*pName;
	if (bCh)
	{
		pName = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
	}
	else
		pName = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo;
	BYTE *szTemp  = new BYTE [nLen*2];
	memset(szTemp,0x00,nLen*2);
	ptr = &pName[0x00+nFlag+(nZone-1)*nStep1+(nCh-1)*nStep2];
	memset(ptr,0x00,nLen);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)szTemp,nLen);
	memcpy(ptr,szTemp,nLen);
	delete	szTemp;
}
void	CZoneInfo::SetCStaticZoneNum()
{
//	CString	strWndText;
//	((CStatic*)GetDlgItem(IDC_STATIC_ZONENUM))->GetWindowText(strWndText);
	CString	str;
	str.Format("区域%d/%d",m_nCurrentZone,m_nZonenum);
//	strWndText+=str;
	((CStatic*)GetDlgItem(IDC_STATIC_ZONENUM))->SetWindowText(str);

}
int		CZoneInfo::GetFreqScope()
{
	int	nRet = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[Freqscope]+((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioInfo[Freqscope+1]*256;
	return (nRet-1);
}
int		CZoneInfo::GetChancountsInZone(int nZone,int nFlag)
{
	BYTE*	pZone = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo;
	int nRet = pZone[0x00 + nFlag +(nZone-1)*18];
	return nRet;
}
int		CZoneInfo::GetChaninfoInChannel(int nZone,int nCh,int nFlag)
{
	BYTE*	pChannel = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
	int nRet = pChannel[0x00+nFlag+(nZone-1)*736 + (nCh-1)*46];
	return nRet;
}
CString	CZoneInfo::GetName(int nZone,int nCh,int nFlag,int nLen,int nStep1 /*= 736*/,int nStep2 /*= 46*/,bool	bCh /* = true*/)
{
	BYTE *ptr,*pInfo;
	BYTE* szTemp = new BYTE[nLen*2];
	if(bCh)
	{
		pInfo = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
		ptr = pInfo+nFlag+(nZone-1)*nStep1+(nCh-1)*nStep2;
	}
	else
	{
		pInfo = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo;
		ptr = pInfo+nFlag+(nZone-1)*nStep1+(nCh-1)*nStep2;
	}
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
// 	delete	szTemp;
	return str;
}
CString	CZoneInfo::GetChanFreq(int nFlag,int nZone,int nChannel)
{
	BYTE*	ptr,*pCh;
	pCh = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
	ptr = &pCh[0x00+nFlag+(nZone-1)*736+(nChannel-1)*46];
	CString	str;
	str.Format("%02x%02x%02x%02x",*(ptr+3),*(ptr+2),*(ptr+1),*ptr);
	long	int	nFreq;
	sscanf_s(str,"%x",&nFreq);
	str.Format("%3d.%.6d",nFreq/1000000,nFreq%1000000);
	return str;
}
CString	CZoneInfo::GetVoiceEncryptCode(int nFlag,int nZone,int nChannel)
{
	char str[20];
	BYTE ch,*ptr;
	int i;
	int j=0;
	ptr = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
	for(i=7;i>=0;i--)
	{
		if(i%2==0)
			ch = *(ptr+nFlag+(nZone-1)*736+(nChannel-1)*46+i/2)&0x0F;		
		else
			ch = *(ptr+nFlag+(nZone-1)*736+(nChannel-1)*46+i/2)>>4;			
		if(ch<10)
			str[7-i-j]=ch+'0';
		else
			j++;
	}
	str[8-j]=0;
	return(CString(str));}
/************************************************************************/
/* LoadData:主要包括，1、检测当前区域中包含有效信道数；2、设置行列；
	3、为首行首列增加标题； 4、加载当前区域下的信道信息；5、对加载的数据进行判断，检测有效性——未实现
                                                                     */
/************************************************************************/
void	CZoneInfo::LoadData()
{
	m_GridCtrl.DeleteAllItems();
	m_nZonenum = 0;
	for (int i=1;i<=16;i++)
	{
		m_nZonechalnum[i-1] = GetChancountsInZone(i,ZONE_CHANNEL_NUM);
			//((CPCSWDoc*)GetDocument())->GetValidChannuumInZone(i,ZONE_CHANNEL_NUM);
		if(m_nZonechalnum[i-1]>0 && i>0)//超过1个以上区域含有信道信息
			m_nZonenum++;
	}
	SetCStaticZoneNum();

	//构架grid窗口行列数目
	GV_ITEM	item;
	//当前页面，当前显示区域包含的信道数
	if (m_nCurrentZone>16)
	{
		MessageBox("超出区域设置范围","错误提示",MB_ICONERROR|MB_ERR_INVALID_CHARS);
		return;
	}
	int nChnum = m_nZonechalnum[m_nCurrentZone-1];
	int nLen = 21;//CHANNEL_STRUCT_INFO;
	if (m_GridCtrl.GetRowCount()!=nChnum)
	{
		TRY 
		{
			m_GridCtrl.SetRowCount(nChnum+1);//首行作为标题栏
			m_GridCtrl.SetColumnCount(nLen+1);//首列作为信道号
			m_GridCtrl.SetFixedColumnCount(1);
			m_GridCtrl.SetFixedRowCount(1);
		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			e->Delete();
			return;
		}
		END_CATCH

		m_GridCtrl.SetGridResize(FALSE,TRUE);	//宽和高度是否可更改
		m_GridCtrl.EnableSelection(FALSE);

		int nColumnWidth[] = {COLUMN_NARROW,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,
							COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NARROW,
							COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,
							COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,COLUMN_NORMAL,
							COLUMN_NORMAL,COLUMN_WIDE};
		for(item.col = 0;item.col < sizeof(nColumnWidth)/sizeof(nColumnWidth[0]);item.col++)
			m_GridCtrl.SetColumnWidth(item.col,nColumnWidth[item.col]);
		for(item.row = 0;item.row < nChnum;item.row++)
			m_GridCtrl.SetRowHeight(item.row,20);


	}//end if ！= nchnum
	if (nChnum > 0)
	{
//		m_GridCtrl.SetRedraw(FALSE);
		//加载行列标题内容
		item.mask	= GVIF_TEXT	| GVIF_FORMAT;
		item.nFormat= DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		item.row=0;
		//每一列的标题，即第一行处标题栏
		int nColumn  = sizeof(strChannelInfo)/sizeof(strChannelInfo[0]);
		for (item.col = 0;item.col<nColumn;item.col++)
		{
			item.szText = strChannelInfo[item.col];
			m_GridCtrl.SetItem(&item);
		}
		//计算有多少行
		item.col = 0;
		CString	strRow = _T("");
		for (item.row = 1;item.row<=nChnum;item.row++)
		{
			strRow.Format("信道%d",item.row);
			item.szText = strRow;
			m_GridCtrl.SetItem(&item);
		}

		for (item.row = 1;item.row<=nChnum;item.row++)
		{
			LoadRowInfo(item.row,nColumn);
			EnableDigitOrAnalog(item.row);
		}
		SetZonename();
		m_GridCtrl.SetRedraw(TRUE,TRUE);//令滚动条出现

	}
	EnableButtons();
}
/************************************************************************/
/* 加载行消息内容 :第几行相当于第几信道  ==>nRow
	列数==>nMaxCol，一般来说属于定值	                               */
/************************************************************************/
void	CZoneInfo::LoadRowInfo(int nRow,int nMaxCol)
{
	if(nRow==0)
		return;

	//从第一列开始填充数据
	//当前行
	GV_ITEM	item;
	item.row = nRow;
	item.mask = GVIF_TEXT|GVIF_FORMAT ;
	item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
	int temp = -1;
	CString	str=_T("");
	for (item.col = 1;item.col<nMaxCol;item.col++)
	{
		//获取每个字段值
		int nFlag = m_nChannelAddr[item.col-1];
		//除去几个特殊字段，其他均为单值
		if((nFlag==CHANNEL_CHANNAME) || (nFlag==CHANNEL_TX_FREQ) ||(nFlag==CHANNEL_RX_FREQ)
			||(nFlag==CHANNEL_SPEECH_ENHANCE_LEVEL)||(nFlag==CHANNEL_DIGIT_VOICEKEY)||
			(nFlag == CHANNEL_RX_ANALOG_SIG_NUM)||(nFlag == CHANNEL_TX_ANALOG_SIG_NUM))
		{	
			//对特别字段的特殊处理
			str = GetSpecialInfo(nFlag,nRow,m_nCurrentZone);
		}
		else
		{
			temp = GetChaninfoInChannel(m_nCurrentZone,nRow,nFlag);
			//	((CPCSWDoc*)GetDocument())->GetByteValuesInCh(nFlag,m_nCurrentZone,nRow);
			str.Format("%d",temp);
			//根据返回值与当前字段，进行分别字符输入
			str = GetByteInfo(temp,nFlag);
		}
		item.szText = str;
		m_GridCtrl.SetItem(&item);
 		EnableOtherGrids(nRow,item.col);
	}

}
//扫描列表显示
void	CZoneInfo::LoadScanlist()
{
	m_GridComboZone.ResetContent();
	m_GridComboZone.AddString("未配置");
 	int nScanList = ((CPCSWApp*)AfxGetApp())->GetScanlistCount();
	int i;
	CString		strName;
	for (i=0;i<nScanList;i++)
	{
		strName = ((CPCSWApp*)AfxGetApp())->GetScanlistName(SCAN_NAME,SCAN_NAMEBYTE,i+1);
		m_GridComboZone.AddString(strName);
	}
}
void	CZoneInfo::LoadContactlist()
{
	m_GridComboZone.ResetContent();
	m_GridComboZone.AddString("未配置");
	//所有的联系人
	int nContCnt = *(WORD*)((CPCSWApp*)AfxGetApp())->m_CommInfo.pContactInfo;
	nContCnt/=CONTACT_STRUCT_LEN;
	int i,nContType;
	CString		strList;
	for (i=0;i<nContCnt;i++)
	{
		nContType  = ((CPCSWApp*)AfxGetApp())->GetContInfo(CONTACT_TYPE,i+1);
		if (nContType>0)
		{
			strList = ((CPCSWApp*)AfxGetApp())->GetContName(i+1,NAME_BYTE_LEN);
			m_GridComboZone.AddString(strList);
		}
	}
}
void	CZoneInfo::LoadGrplist()
{
	m_GridComboZone.ResetContent();
	m_GridComboZone.AddString("未配置");
	int nGrplistCnt = ((CPCSWApp*)AfxGetApp())->GetGrplistCount();
	nGrplistCnt/=CONTACT_STRUCT_LEN;
	int nGrpnum;
	CString		strList;
	int i=0;
	for (i=0;i<nGrplistCnt;i++)
	{
		nGrpnum = ((CPCSWApp*)AfxGetApp())->GetGrplistInfo(GRP_NUM,i+1,1);
		if (nGrpnum>0)
		{
			strList = ((CPCSWApp*)AfxGetApp())->GetGrplistName(i+1,NAME_BYTE_LEN);
			m_GridComboZone.AddString(strList);
		}
	}
}
void CZoneInfo::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//获取到每个区域的有效信道数
// 	m_nZonenum = 0;
// 	for (int i=1;i<=16;i++)
// 	{
// 		m_nZonechalnum[i-1] = ((CPCSWDoc*)GetDocument())->GetValidChannuumInZone(i,ZONE_CHANNEL_NUM);
// 		if(m_nZonechalnum[i-1]>0 && i>1)//超过1个以上区域含有信道信息
// 			m_nZonenum++;
// 	}
	LoadData();
}
// LRESULT CZoneInfo::OnEditGrid(GV_DISPINFO* pInfo, LRESULT* pResult)
void CZoneInfo::OnEditGrid(NMHDR * pNMHDR, LRESULT* pResult)
{
	GV_DISPINFO* pInfo = (GV_DISPINFO*)pNMHDR;
	CRect	rect(pInfo->rect);
	ScreenToClient(&rect);
	int i;
	if((pInfo->item.col >0) && (pInfo->item.col <sizeof(strChannelInfo)/sizeof(strChannelInfo[0])))
			m_GridCtrl.SetEditState(TRUE);

	m_GridComboZone.ResetContent();
	switch (pInfo->item.col)
	{
	case 1://第一列 配置情况
	case 2:// 扫描列表
	case 3://信道工作模式
	case 4://信道状态
		{
			if(pInfo->item.col == 1)
			{
				for(i=0;i<sizeof(strCHASS)/sizeof(strCHASS[0]);i++)
					m_GridComboZone.AddString(strCHASS[i]);
			}
			else if (pInfo->item.col == 2)//需要修改
			{
// 				for(i=0;i<sizeof(strSCANLIST)/sizeof(strSCANLIST[0]);i++)
// 					m_GridComboZone.AddString(strSCANLIST[i]);
				LoadScanlist();
			}
			else if (pInfo->item.col == 3)
			{
				for(i=0;i<sizeof(strMODE)/sizeof(strMODE[0]);i++)
					m_GridComboZone.AddString(strMODE[i]);
			}
			else if (pInfo->item.col == 4)
			{				
				for(i=0;i<sizeof(strSTATUS)/sizeof(strSTATUS[0]);i++)
					m_GridComboZone.AddString(strSTATUS[i]);
			}
			m_GridComboZone.Init(rect,pInfo->item.szText);
		}
		break;
	case 5:	//信道别名
	case 6:	//发射频点
	case 7:	//接收频点
		{
			if (pInfo->item.col == 5)
			{
				m_GridEditZone.Initialize(CGridEdit::Name,4,pInfo->item.szText,&rect);
			}
			else if (pInfo->item.col == 6 ||pInfo->item.col == 7 )
			{
				m_GridEditZone.Initialize(CGridEdit::Freq,10,pInfo->item.szText,&rect);
			}
		}
		break;
	case 8://发射功率
		for (i =0;i<2;i++)
		{
			m_GridComboZone.AddString(strPOWER[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 9://信道间隔
		for (i=0;i<ArraySize(strINTERVAL);i++)
		{
			m_GridComboZone.AddString(strINTERVAL[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 10://语音增强等级
		for (i=0;i<ArraySize(strSpeechEnhLev);i++)
		{
			m_GridComboZone.AddString(strSpeechEnhLev[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 11://尾音消除相位
		for (i=0;i<ArraySize(strCTCPHASE);i++)
		{
			m_GridComboZone.AddString(strCTCPHASE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 12://繁忙锁定
		for (i=0;i<ArraySize(strBUSYLOCK);i++)
		{
			m_GridComboZone.AddString(strBUSYLOCK[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 13://发射信令类型
		for (i=0;i<ArraySize(strSIGNALTYPE);i++)
		{
			m_GridComboZone.AddString(strSIGNALTYPE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 14://发射信令号
		{
			int nType = GetChaninfoInChannel(m_nCurrentZone,pInfo->item.row,CHANNEL_TX_ANALOG_SIG_TYPE);
			DcsCtcData(nType);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 15://接收信令类型
		for (i=0;i<ArraySize(strSIGNALTYPE);i++)
		{
			m_GridComboZone.AddString(strSIGNALTYPE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 16://接收信令号
		{
			int nType = GetChaninfoInChannel(m_nCurrentZone,pInfo->item.row,CHANNEL_RX_ANALOG_SIG_TYPE);
			DcsCtcData(nType);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 17://接收组列表
		{
			LoadGrplist();
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 18://发射联系人
		{
			LoadContactlist();
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 19://礼貌方式
		for (i=0;i<ArraySize(strPOLITE);i++)
		{
			m_GridComboZone.AddString(strPOLITE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 20://语音加密
 		{
			m_GridComboZone.AddString("关闭");
			m_GridComboZone.AddString("开启");
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 21://语音加密密码
		{
	//				DcsCtcData(1);
			m_GridEditZone.Initialize(CGridEdit::Freq,8,pInfo->item.szText,&rect);
		}
		break;
	}
	return  ;
//	m_GridCtrl.SetRedraw(TRUE,TRUE);
}
void	CZoneInfo::SetDefaultData()
{
	CString		str;
	int i=0;
	int	nFreq = ((CPCSWApp*)AfxGetApp())->GetFreqBoundry(FALSE);
	for (i=0;i<16;i++)
	{
		str.Format("信道%d",i+1);
		SetName(m_nCurrentZone,i+1,CHANNEL_CHANNAME,NAME_BYTE_LEN,str);
		str.Format("%d",nFreq);
		((CPCSWApp*)AfxGetApp())->SetFreq(m_nCurrentZone,i+1,CHANNEL_TX_FREQ,str);
		((CPCSWApp*)AfxGetApp())->SetFreq(m_nCurrentZone,i+1,CHANNEL_RX_FREQ,str);
	}
}

/************************************************************************/
/* 根据当前信道，令数字/模拟信息窗口失效
1、未配置：全部失效；2、数字信道：。。。；3、模拟信道：。。。；
                                                                     */
/************************************************************************/
void	CZoneInfo::SetInfo(int nZone,int nCh,int nFlag,int nVal,int nStep1 /* = 736 */,int nStep2 /* = 46 */,bool bCh /* = true */)
{
	byte*	ptr;
	if (bCh)
	{
		ptr = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo;
		ptr[0x00+nFlag+(nZone-1)*nStep1+(nCh-1)*nStep2] = nVal;
	}
	else
	{
		ptr = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo;
		ptr[0x00+nFlag+(nZone-1)*nStep1] = nVal;
	}
}
void	CZoneInfo::SetReadonlyGrid(int nRow,int nCol,bool bRead)
{
	GV_ITEM item;
	item.col = nCol;
	item.row = nRow;
	item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
	item.szText = m_GridCtrl.GetItemText(nRow,nCol);
	if(bRead)
	{
		item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
		m_GridCtrl.SetItemBkColour(nRow,item.col,RGB(125,125,125));//GetSysColor(COLOR_3DFACE));
		m_GridCtrl.SetItemFgColour(nRow,item.col,RGB(225,225,225));//GetSysColor(COLOR_GRAYTEXT));
	}
	else
		item.mask = GVIF_TEXT|GVIF_FORMAT;
	m_GridCtrl.SetItem(&item);

}
void	CZoneInfo::EnableButtons()
{
	if(m_nCurrentZone == m_nZonenum)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(FALSE);
	}
	else if (m_nCurrentZone == 1)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);	
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);	
	}

}
bool	CZoneInfo::EnableOtherGrids(int nRow,int nCol)
{
 	switch (nCol)
	{
	case 3://信道工作模式
		{
			int nSel = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_MODE);
			if (nSel==0)//直通
			{
				SetReadonlyGrid(nRow,nCol+1,FALSE);
 			}
			else if (nSel == 1)//中转
			{
				SetReadonlyGrid(nRow,nCol+1,TRUE);
 			}
		}
		break;
	case 13://发射信令类型
		{
			int nSel = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_TX_ANALOG_SIG_TYPE);
			if (nSel == 0)
			{
				SetReadonlyGrid(nRow,nCol+1,true);
			}
			else
				SetReadonlyGrid(nRow,nCol+1,false);
		}
		break;
	case 15://接收信令类型
		{
			int nSel = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_RX_ANALOG_SIG_TYPE);
			if (nSel == 0)
			{
				SetReadonlyGrid(nRow,nCol+1,true);
			}
			else
				SetReadonlyGrid(nRow,nCol+1,false);
		}
		break;
	case 20://语音加密开启
		{
			int nSel = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_DIGIT_VOICEKEY_EN);
			if (nSel==0)//直通
			{
				SetReadonlyGrid(nRow,nCol+1,TRUE);
			}
			else if (nSel == 1)//中转
			{
				SetReadonlyGrid(nRow,nCol+1,FALSE);
			}
		}
		break;
	default:
		break;
	}
	return true;
}
BOOL	CZoneInfo::EnableDigitOrAnalog(int nRow)
{
	GV_ITEM item;
	item.col = 1;//信道配置列
	//获取配置列的当前值
	int	temp = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_CHASS);
		//((CPCSWDoc*)GetDocument())->GetByteValuesInCh(CHANNEL_CHASS,m_nCurrentZone,nRow);
	item.row = nRow;
	int nCol = sizeof(strChannelInfo)/sizeof(strChannelInfo[0]);
	if (temp == 0)//未配置
	{
		for (item.col = 2;item.col<nCol;item.col++)
		{
			item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
			item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
			item.szText = m_GridCtrl.GetItemText(nRow,item.col);
			//背景框颜色设置
			m_GridCtrl.SetItemBkColour(nRow,item.col,RGB(125,125,125));//GetSysColor(COLOR_3DFACE));
			m_GridCtrl.SetItemFgColour(nRow,item.col,RGB(225,225,225));//GetSysColor(COLOR_GRAYTEXT));
			m_GridCtrl.SetItem(&item);
		}
		return TRUE;
	}
	else if(temp == 1)//数字信道
	{
		for (item.col = 2;item.col<nCol;item.col++)
		{
			switch (item.col)
			{
				case 17://接收组列表
				case 18://发射联系人
				case 19://礼貌方式
				case 20://语音加密
				case 21://语音加密密码
					{
						item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
						item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
						item.szText = m_GridCtrl.GetItemText(nRow,item.col);
						//背景框颜色设置
						m_GridCtrl.SetItemBkColour(nRow,item.col,RGB(125,125,125));//GetSysColor(COLOR_3DFACE));
						m_GridCtrl.SetItemFgColour(nRow,item.col,RGB(225,225,225));//GetSysColor(COLOR_GRAYTEXT));
						m_GridCtrl.SetItem(&item);
					}
					break;
				default:
					{
						item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
						item.mask = GVIF_TEXT|GVIF_FORMAT;
						item.szText = m_GridCtrl.GetItemText(nRow,item.col);
						m_GridCtrl.SetItem(&item);
					}
					break;
			}
		}
		return TRUE;
	}
	else if (temp == 2)//模拟信道
	{
		for (item.col = 2;item.col<nCol;item.col++)
		{
			switch (item.col)
			{
			case 11://尾音消除相位
			case 12://繁忙锁定
			case 13://发射信令类型
			case 14://发射信令号
			case 15://接收信令类型
			case 16://接收信令号
				{
					item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
					item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
					item.szText = m_GridCtrl.GetItemText(nRow,item.col);
					//背景框颜色设置
					m_GridCtrl.SetItemBkColour(nRow,item.col,RGB(125,125,125));//GetSysColor(COLOR_3DFACE));
					m_GridCtrl.SetItemFgColour(nRow,item.col,RGB(225,225,225));//GetSysColor(COLOR_GRAYTEXT));
					m_GridCtrl.SetItem(&item);
				}
				break;
			default:
				{
					item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
					item.mask = GVIF_TEXT|GVIF_FORMAT;
					item.szText = m_GridCtrl.GetItemText(nRow,item.col);
					m_GridCtrl.SetItem(&item);
				}
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}
//将信令号输入到combo框中
void	CZoneInfo::DcsCtcData(int nSelType)
{
	HRSRC	hSrc;
 	HGLOBAL	hGlobal;
 	char*	lp;
	int i;
	m_GridComboZone.ResetContent();
	switch(nSelType)
	{
	case 1:
		hSrc	= FindResource(NULL,MAKEINTRESOURCE(IDR_CTC50),_T("BINARYDATA"));
		hGlobal	= LoadResource(NULL,hSrc);
		lp		=(char*)LockResource(hGlobal);
		for(i=0;i<50;i++)
			m_GridComboZone.AddString(lp+i*8);
		FreeResource(hGlobal);
		break;
	case 2:
	case 3:
		hSrc	= FindResource(NULL,MAKEINTRESOURCE(IDR_DCS),_T("BINARYDATA"));
		hGlobal	= LoadResource(NULL,hSrc);
		lp		=(char*)LockResource(hGlobal);
		for(i=0;i<104;i++)
			m_GridComboZone.AddString(lp+i*8);
		FreeResource(hGlobal);
		break;
	default:
		break;
	}
}
void CZoneInfo::OnDestroy() 
{
//	CFormView::OnDestroy();
/*	ShowWindow(SW_HIDE);
	if(((CPCSWApp*)AfxGetApp())->m_Frame.GetAt(3)!=NULL)
		((CPCSWApp*)AfxGetApp())->m_Frame.SetAt(3,NULL);	
*/	// TODO: Add your message handler code here
	
}

void CZoneInfo::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if(m_nCurrentZone<m_nZonenum)
		m_nCurrentZone++;
	LoadData();
	if(m_nCurrentZone == m_nZonenum)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	}
}

void CZoneInfo::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	m_nCurrentZone = 1;
	LoadData();	
	if(m_nCurrentZone == 1)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	}
}

void CZoneInfo::OnButtonPrev() 
{
	// TODO: Add your control notification handler code here
	if(m_nCurrentZone<=m_nZonenum && m_nCurrentZone>0)
		m_nCurrentZone--;
	LoadData();	
	if(m_nCurrentZone == 1)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	}
}

void CZoneInfo::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	m_nCurrentZone = m_nZonenum;
	LoadData();	
	if(m_nCurrentZone == m_nZonenum)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BUTTON_FIRST))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_PREV))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_NEXT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_LAST))->EnableWindow(TRUE);
	}
}

void CZoneInfo::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(m_nZonenum<16)//在最后一个区域后增加
	{
		m_nZonenum++;
		m_nCurrentZone = m_nZonenum;
		//写入数值,并将数据后移
		int i,nChanCnt = 16;//区域支持信道数
		SetInfo(m_nCurrentZone,0,ZONE_CHANNEL_NUM,nChanCnt,18,0,false);
// 		//从后往前开始后移
// 		for(i=0;i<m_nZonenum-m_nCurrentZone;i++)
// 		{
// 			memcpy(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00+(m_nZonenum-i)*736],
// 				&((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00+(m_nZonenum-1-i)*736],736);		
// 		}
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00+(m_nZonenum-1)*736],0x00,736);//将当前赋0
		((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00] = m_nZonenum;
		CString		str;
		str.Format("区域%d",m_nZonenum);
		SetName(m_nZonenum,1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,str,18,0,false);//区域别名		
		//然后编辑序号
		SetDefaultData();
	}
	LoadData();
}

/************************************************************************/
/* 不提供插入功能                                                                     */
/************************************************************************/
void CZoneInfo::OnButtonInsert() 
{
	// TODO: Add your control notification handler code here
	m_nZonenum++;
	m_nCurrentZone++;
	LoadData();
}

void CZoneInfo::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if(m_nZonenum>1)//至少保留一个区域
	{
		m_nZonenum--;
		int i=m_nCurrentZone;
//		m_nCurrentZone = m_nZonenum;
		//先将区域名与区域支持信道数等信息往前移动
		while(i>0)
		{
			memcpy(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo[0x00+(m_nZonenum-1-i)*18],
				&((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo[0x00+(m_nZonenum-i)*18],18);
			SetInfo(m_nZonenum-1-i,1,ZONE_RESERVE,0xff,18,0,false);//保留位设置
			i--;
		}
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo[0x00+(m_nZonenum-1)*18],
			0x00,18);
		SetInfo(m_nCurrentZone,1,ZONE_CHANNEL_NUM,0x00,18,0,false);
		SetInfo(m_nCurrentZone,1,ZONE_RESERVE,0xff,18,0,false);
	}
	else if (m_nZonenum == 1)
	{
		MessageBox("无法继续删除，请至少保留一个区域信息用于通信","提示");
	}
	LoadData();
}
/************************************************************************/
/*获取各个值的函数 
                                                                     */
/************************************************************************/
CString	CZoneInfo::GetSpecialInfo(int nAddr,int nChnum,int nZonenum)
{
	CString	str;
	m_GridComboZone.ResetContent();
	if(nAddr<0)
	{
		str.Format("地址错误:%d",nAddr);
			return 	(str);
	}
	switch (nAddr)
	{
	case CHANNEL_CHANNAME://信道别名
		{
			str = GetName(nZonenum,nChnum,nAddr,ZONE_CHANNEL_NAME_BYTE);
			//	((CPCSWDoc*)GetDocument())->GetChannelName(ZONE_CHANNEL_NAME_BYTE,nAddr,nZonenum,nChnum);
		}
		break;
	case CHANNEL_TX_FREQ://发射频点
		{
			str = GetChanFreq(CHANNEL_TX_FREQ,nZonenum,nChnum);
			//	((CPCSWDoc*)GetDocument())->GetChannelFreq(CHANNEL_TX_FREQ,nZonenum,nChnum);
		}
		break;
	case CHANNEL_RX_FREQ://接收频点
		{
			str = GetChanFreq(CHANNEL_RX_FREQ,nZonenum,nChnum);
			//	((CPCSWDoc*)GetDocument())->GetChannelFreq(CHANNEL_RX_FREQ,nZonenum,nChnum);
		}
		break;

	case CHANNEL_SPEECH_ENHANCE_LEVEL://语音增强
		{
			int temp,i;
			temp =	GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_SPEECH_ENHANCE_LEVEL);
			for (i=0;i<ArraySize(strSpeechEnhLev);i++)
			{
				m_GridComboZone.AddString(strSpeechEnhLev[i]);
			}
				//((CPCSWDoc*)GetDocument())->GetByteValuesInCh(CHANNEL_SPEECH_ENHANCE_LEVEL,nZonenum,nChnum);
// 			str.Format("关闭%d",temp);

			m_GridComboZone.GetLBText(temp,str);
		}
		break;
	case CHANNEL_DIGIT_VOICEKEY://语音密码
		{
			str = GetVoiceEncryptCode(CHANNEL_DIGIT_VOICEKEY,nZonenum,nChnum);
				//((CPCSWDoc*)GetDocument())->GetVoiceEncryptCode(CHANNEL_DIGIT_VOICEKEY,nZonenum,nChnum);
		}
		break;
	case CHANNEL_RX_ANALOG_SIG_NUM:
		{
			int nType = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_RX_ANALOG_SIG_TYPE);//信令类型
			int nTmp = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_RX_ANALOG_SIG_NUM);
			//若为cdcss，则为1，否则为2、3
			if (nType>0&& nType<=3)
			{
				DcsCtcData(nType);
				m_GridComboZone.GetLBText(nTmp,str);
			}
			else if (nType == 0)//类型为无时
			{
				str = _T("未配置");
			}
 			else
				str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_TX_ANALOG_SIG_NUM:
		{
			int nType = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_TX_ANALOG_SIG_TYPE);//信令类型
			int nTmp = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_TX_ANALOG_SIG_NUM);
			//若为cdcss，则为1，否则为2、3
			if (nType>0&& nType<=3)
			{
				DcsCtcData(nType);
				if(nTmp <m_GridComboZone.GetCount())
				{
					m_GridComboZone.GetLBText(nTmp,str);
				}
				else
					str.Format("取值错误:%d",nTmp);
			}
			else if (nType == 0)//类型为无时
			{
				str = _T("未配置");
			}
			else
				str.Format("取值错误:%d",nTmp);
		}
		break;
	}
	return str;
}
CString	CZoneInfo::GetByteInfo(int nTmp,int nAddr)
{
	CString	str;
	if(nAddr<0)
	{
		(str.Format("地址错误:%d",nAddr));
		return str;
	}
	switch (nAddr)
	{
	case CHANNEL_CHASS://信道配置
		{
			 if (nTmp>=0 && nTmp<4)//取值范围0-3
			 {
				 str = strCHASS[nTmp];
			 }
			 else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_SCANLIST:
		{
			LoadScanlist();
			if(nTmp < m_GridComboZone.GetCount())
			{
				m_GridComboZone.GetLBText(nTmp,str);
			}
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_MODE:
		{
			if(nTmp==0 || nTmp == 1)
				str = strMODE[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_STATUS:
		{
			if(nTmp == 0 || nTmp == 1)
				str = strSTATUS[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_POWER_LEVEL:
		{
			if(nTmp == 0 || nTmp == 1)
				str = strPOWER[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_INTERVAL:
		{
			if(nTmp >= 0 && nTmp <=3 )
				str = strINTERVAL[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_CTC_PHASE:
		{
			if(nTmp == 0 ||nTmp == 1 )
				str = strCTCPHASE[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_BUSYLOCK:
		{
			if(nTmp == 0 || nTmp == 1)
				str = strBUSYLOCK[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_TX_ANALOG_SIG_TYPE://发射模拟信令类型
		{
			 if (nTmp>=0 && nTmp<4)//取值范围0-3
			 {
				 str = strSIGNALTYPE[nTmp];
			 }
			 else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_RX_ANALOG_SIG_TYPE:
		{
			 if (nTmp>=0 && nTmp<4)//取值范围0-3
			 {
				 str = strSIGNALTYPE[nTmp];
			 }
			 else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_RX_GROUP://接收组列表
		{
			if(nTmp >=0 && nTmp<=32 )
			{
				LoadGrplist();
				m_GridComboZone.GetLBText(nTmp,str);
			}	
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_SEND_ID://默认发射联系人
		{
			if(nTmp >=0 && nTmp<=200 )
			{
				LoadContactlist();
				m_GridComboZone.GetLBText(nTmp,str);
			}
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_POLITE://礼貌方式
		{
			if(nTmp == 0 || nTmp == 1)
				str = strPOLITE[nTmp];
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_VOICEKEY_EN:
		{
			if(nTmp == 0 )
				str = _T("关闭");
			else if( nTmp == 1)
				str = _T("开启");
			else
				 str.Format("取值错误:%d",nTmp);
		}
		break;
	}
	return str;
}

void CZoneInfo::OnKillfocusComboZonelist() 
{
	// TODO: Add your control notification handler code here
	m_GridCtrl.SetEditState(FALSE);
	m_GridComboZone.End();
}

void CZoneInfo::OnSelchangeComboZonelist() 
{
	// TODO: Add your control notification handler code here
	m_GridCtrl.SetEditState(FALSE);
	CCellID		cell = m_GridCtrl.GetFocusCell();
	CString		str;
// 	int		nSel;
// 	nSel = m_GridComboZone.GetCurSel();
	switch(cell.col)
	{
	case 1://信道配置
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_CHASS,nSel);
		}
		break;
	case 2:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_SCANLIST,nSel);
		}
		break;
	case 3:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_MODE,nSel);
		}
		break;
	case 4:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_STATUS,nSel);
		}
		break;
	case 8:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_POWER_LEVEL,nSel);
		}
		break;
	case 9:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_INTERVAL,nSel);
		}
		break;
	case 10://语音增强需要注意
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_SPEECH_ENHANCE_LEVEL,nSel);
		}
		break;
	case 11:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_CTC_PHASE,nSel);
		}
		break;
	case 12:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_BUSYLOCK,nSel);
		}
		break;
	case 13:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_TX_ANALOG_SIG_TYPE,nSel);
		}
		break;
	case 14:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_TX_ANALOG_SIG_NUM,nSel);
		}
		break;
	case 15:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_RX_ANALOG_SIG_TYPE,nSel);
		}
		break;
	case 16:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_RX_ANALOG_SIG_NUM,nSel);
		}
		break;
	case 17:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_DIGIT_RX_GROUP,nSel);
		}
		break;
	case 18:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_DIGIT_SEND_ID,nSel);
		}
		break;
	case 19:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_DIGIT_POLITE,nSel);
		}
		break;
	case 20:
		{
			int nSel = m_GridComboZone.GetCurSel();
			SetInfo(m_nCurrentZone,cell.row,CHANNEL_DIGIT_VOICEKEY_EN,nSel);
		}
		break;
	}
	m_GridComboZone.End();
	LoadData();
}

void CZoneInfo::OnEnKillfocusEditZone()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GridCtrl.SetEditState(FALSE);
	CCellID		cell = m_GridCtrl.GetFocusCell();
	CString		str;
	m_GridEditZone.GetWindowText(str);
	switch (cell.col)
	{
	case 5://信道别名
		{
			if (str.IsEmpty())//空别名
			{
				MessageBox("请输入信道别名","提示");
				return;
			}
			//接下来查看该别名是否重复,只在本区域内
			CString		strName;
			int i;
			for(i=1;i<m_GridCtrl.GetRowCount()-1;i++)
			{
				if(i!=cell.row)//不与本信道别名比较
				{
					strName = GetName(m_nCurrentZone,i,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE);
					if (strName.CompareNoCase(str)!=-1)
					{
						break;
					}
				}
			}
			if (i == m_GridCtrl.GetRowCount())//无重复，则写入
			{
				SetName(m_nCurrentZone,cell.row,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE,str);
			}
		}
		break;
	case 6:
	case 7://频点写入
		{
			int nFreqScope = GetFreqScope();
			switch(nFreqScope)
			{
			case 0://136-150
				{
// 					long	lFerq = strtoul(str.GetBuffer(str.GetLength()),,10)
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
			break;
	}
	m_GridEditZone.HideWindow();
}

BOOL CZoneInfo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 	ERASE_BKGND_BEGIN;
// 	ADD_NOERASE_RGN(IDC_GRID_ZONE);
// 	ADD_NOERASE_RGN(IDC_BUTTON1);
// 	ADD_NOERASE_RGN(IDC_LIST_STAT);
// 	ERASE_BKGND_END(pDC, GetSysColor(COLOR_3DFACE));
// 	return false;
	return CFormView::OnEraseBkgnd(pDC);
}

void CZoneInfo::OnEnKillfocusEditZonename()
{
	// TODO: 在此添加控件通知处理程序代码
	CString		str;
	m_editZonename.GetWindowText(str);
	CString		strZone;
	int i=0;
	for (;i<m_nZonenum;i++)
	{
		strZone = GetName(i+1,1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,18,0,false);
		if (i!=m_nCurrentZone)
		{
			if (strZone.CompareNoCase(str)!=0)
			{
				break;
			}
		}
	}
	if (i<m_nZonenum)//遍历未找到相同名称，则写入区域名
	{
		SetName(m_nCurrentZone,1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,str,18,0,false);
	}
	LoadData();
}

