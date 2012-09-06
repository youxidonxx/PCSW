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
static	CString	strChannelInfo[] = {"�ŵ���",
		"�ŵ����ñ�ʶ","ɨ���б�","�ŵ�����ģʽ","�ŵ�����״̬","�ŵ�����","����Ƶ��","����Ƶ��",
		"���书��","�ŵ����","������ǿ�ȼ�","����Ƶβ��������λ�仯","��æ����","����ģ����������",
		"����ģ�������","����ģ����������","����ģ�������","�������б�","����Ĭ����ϵ��","��ò��ʽ",
		"��������","����������Կ"
};
static	CString	strCHASS[] = {"δ����","�����ŵ�","ģ���ŵ�","����Ӧ�ŵ�"};
static	CString	strSCANLIST[] = {"δ����ɨ���б�","ɨ���б�"};
static	CString	strMODE[] = {"ֱͨģʽ","��תģʽ"};
static	CString	strSTATUS[] = {"������","����"};
static	CString	strPOWER[] = {"��","��"};
static	CString	strINTERVAL[] = {"6.25KHz","12.5KHz","20KHz","25KHz"};
static	CString	strBUSYLOCK[] = {"��æʱ������","��æ����"};
static	CString	strSIGNALTYPE[] = {"��","CTCSS","CDCSS","����CDCSS"};
static	CString	strPOLITE[] = {"�κ����������","�ŵ�����ʱ������"};
static	CString	strCTCPHASE[] = {"180","120"};
static	CString	strSpeechEnhLev[] = {"�ر�","1","2","3","4"};
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
	//��ȡ��ÿ���������Ч�ŵ���
	m_nZonenum = 0;
	for (int i=1;i<=16;i++)
	{
		m_nZonechalnum[i-1] = GetChancountsInZone(i,ZONE_CHANNEL_NUM);
			//((CPCSWDoc*)GetDocument())->GetValidChannuumInZone(i,ZONE_CHANNEL_NUM);
		if(m_nZonechalnum[i-1]>0 && i>1)//����1�������������ŵ���Ϣ
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
	str.Format("����%d/%d",m_nCurrentZone,m_nZonenum);
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
/* LoadData:��Ҫ������1����⵱ǰ�����а�����Ч�ŵ�����2���������У�
	3��Ϊ�����������ӱ��⣻ 4�����ص�ǰ�����µ��ŵ���Ϣ��5���Լ��ص����ݽ����жϣ������Ч�ԡ���δʵ��
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
		if(m_nZonechalnum[i-1]>0 && i>0)//����1�������������ŵ���Ϣ
			m_nZonenum++;
	}
	SetCStaticZoneNum();

	//����grid����������Ŀ
	GV_ITEM	item;
	//��ǰҳ�棬��ǰ��ʾ����������ŵ���
	if (m_nCurrentZone>16)
	{
		MessageBox("�����������÷�Χ","������ʾ",MB_ICONERROR|MB_ERR_INVALID_CHARS);
		return;
	}
	int nChnum = m_nZonechalnum[m_nCurrentZone-1];
	int nLen = 21;//CHANNEL_STRUCT_INFO;
	if (m_GridCtrl.GetRowCount()!=nChnum)
	{
		TRY 
		{
			m_GridCtrl.SetRowCount(nChnum+1);//������Ϊ������
			m_GridCtrl.SetColumnCount(nLen+1);//������Ϊ�ŵ���
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

		m_GridCtrl.SetGridResize(FALSE,TRUE);	//��͸߶��Ƿ�ɸ���
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


	}//end if ��= nchnum
	if (nChnum > 0)
	{
//		m_GridCtrl.SetRedraw(FALSE);
		//�������б�������
		item.mask	= GVIF_TEXT	| GVIF_FORMAT;
		item.nFormat= DT_CENTER | DT_VCENTER | DT_SINGLELINE;
		item.row=0;
		//ÿһ�еı��⣬����һ�д�������
		int nColumn  = sizeof(strChannelInfo)/sizeof(strChannelInfo[0]);
		for (item.col = 0;item.col<nColumn;item.col++)
		{
			item.szText = strChannelInfo[item.col];
			m_GridCtrl.SetItem(&item);
		}
		//�����ж�����
		item.col = 0;
		CString	strRow = _T("");
		for (item.row = 1;item.row<=nChnum;item.row++)
		{
			strRow.Format("�ŵ�%d",item.row);
			item.szText = strRow;
			m_GridCtrl.SetItem(&item);
		}

		for (item.row = 1;item.row<=nChnum;item.row++)
		{
			LoadRowInfo(item.row,nColumn);
			EnableDigitOrAnalog(item.row);
		}
		SetZonename();
		m_GridCtrl.SetRedraw(TRUE,TRUE);//�����������

	}
	EnableButtons();
}
/************************************************************************/
/* ��������Ϣ���� :�ڼ����൱�ڵڼ��ŵ�  ==>nRow
	����==>nMaxCol��һ����˵���ڶ�ֵ	                               */
/************************************************************************/
void	CZoneInfo::LoadRowInfo(int nRow,int nMaxCol)
{
	if(nRow==0)
		return;

	//�ӵ�һ�п�ʼ�������
	//��ǰ��
	GV_ITEM	item;
	item.row = nRow;
	item.mask = GVIF_TEXT|GVIF_FORMAT ;
	item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
	int temp = -1;
	CString	str=_T("");
	for (item.col = 1;item.col<nMaxCol;item.col++)
	{
		//��ȡÿ���ֶ�ֵ
		int nFlag = m_nChannelAddr[item.col-1];
		//��ȥ���������ֶΣ�������Ϊ��ֵ
		if((nFlag==CHANNEL_CHANNAME) || (nFlag==CHANNEL_TX_FREQ) ||(nFlag==CHANNEL_RX_FREQ)
			||(nFlag==CHANNEL_SPEECH_ENHANCE_LEVEL)||(nFlag==CHANNEL_DIGIT_VOICEKEY)||
			(nFlag == CHANNEL_RX_ANALOG_SIG_NUM)||(nFlag == CHANNEL_TX_ANALOG_SIG_NUM))
		{	
			//���ر��ֶε����⴦��
			str = GetSpecialInfo(nFlag,nRow,m_nCurrentZone);
		}
		else
		{
			temp = GetChaninfoInChannel(m_nCurrentZone,nRow,nFlag);
			//	((CPCSWDoc*)GetDocument())->GetByteValuesInCh(nFlag,m_nCurrentZone,nRow);
			str.Format("%d",temp);
			//���ݷ���ֵ�뵱ǰ�ֶΣ����зֱ��ַ�����
			str = GetByteInfo(temp,nFlag);
		}
		item.szText = str;
		m_GridCtrl.SetItem(&item);
 		EnableOtherGrids(nRow,item.col);
	}

}
//ɨ���б���ʾ
void	CZoneInfo::LoadScanlist()
{
	m_GridComboZone.ResetContent();
	m_GridComboZone.AddString("δ����");
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
	m_GridComboZone.AddString("δ����");
	//���е���ϵ��
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
	m_GridComboZone.AddString("δ����");
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
	
	//��ȡ��ÿ���������Ч�ŵ���
// 	m_nZonenum = 0;
// 	for (int i=1;i<=16;i++)
// 	{
// 		m_nZonechalnum[i-1] = ((CPCSWDoc*)GetDocument())->GetValidChannuumInZone(i,ZONE_CHANNEL_NUM);
// 		if(m_nZonechalnum[i-1]>0 && i>1)//����1�������������ŵ���Ϣ
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
	case 1://��һ�� �������
	case 2:// ɨ���б�
	case 3://�ŵ�����ģʽ
	case 4://�ŵ�״̬
		{
			if(pInfo->item.col == 1)
			{
				for(i=0;i<sizeof(strCHASS)/sizeof(strCHASS[0]);i++)
					m_GridComboZone.AddString(strCHASS[i]);
			}
			else if (pInfo->item.col == 2)//��Ҫ�޸�
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
	case 5:	//�ŵ�����
	case 6:	//����Ƶ��
	case 7:	//����Ƶ��
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
	case 8://���书��
		for (i =0;i<2;i++)
		{
			m_GridComboZone.AddString(strPOWER[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 9://�ŵ����
		for (i=0;i<ArraySize(strINTERVAL);i++)
		{
			m_GridComboZone.AddString(strINTERVAL[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 10://������ǿ�ȼ�
		for (i=0;i<ArraySize(strSpeechEnhLev);i++)
		{
			m_GridComboZone.AddString(strSpeechEnhLev[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 11://β��������λ
		for (i=0;i<ArraySize(strCTCPHASE);i++)
		{
			m_GridComboZone.AddString(strCTCPHASE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 12://��æ����
		for (i=0;i<ArraySize(strBUSYLOCK);i++)
		{
			m_GridComboZone.AddString(strBUSYLOCK[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 13://������������
		for (i=0;i<ArraySize(strSIGNALTYPE);i++)
		{
			m_GridComboZone.AddString(strSIGNALTYPE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 14://���������
		{
			int nType = GetChaninfoInChannel(m_nCurrentZone,pInfo->item.row,CHANNEL_TX_ANALOG_SIG_TYPE);
			DcsCtcData(nType);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 15://������������
		for (i=0;i<ArraySize(strSIGNALTYPE);i++)
		{
			m_GridComboZone.AddString(strSIGNALTYPE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 16://���������
		{
			int nType = GetChaninfoInChannel(m_nCurrentZone,pInfo->item.row,CHANNEL_RX_ANALOG_SIG_TYPE);
			DcsCtcData(nType);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 17://�������б�
		{
			LoadGrplist();
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 18://������ϵ��
		{
			LoadContactlist();
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 19://��ò��ʽ
		for (i=0;i<ArraySize(strPOLITE);i++)
		{
			m_GridComboZone.AddString(strPOLITE[i]);
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 20://��������
 		{
			m_GridComboZone.AddString("�ر�");
			m_GridComboZone.AddString("����");
		}
		m_GridComboZone.Init(rect,pInfo->item.szText);
		break;
	case 21://������������
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
		str.Format("�ŵ�%d",i+1);
		SetName(m_nCurrentZone,i+1,CHANNEL_CHANNAME,NAME_BYTE_LEN,str);
		str.Format("%d",nFreq);
		((CPCSWApp*)AfxGetApp())->SetFreq(m_nCurrentZone,i+1,CHANNEL_TX_FREQ,str);
		((CPCSWApp*)AfxGetApp())->SetFreq(m_nCurrentZone,i+1,CHANNEL_RX_FREQ,str);
	}
}

/************************************************************************/
/* ���ݵ�ǰ�ŵ���������/ģ����Ϣ����ʧЧ
1��δ���ã�ȫ��ʧЧ��2�������ŵ�����������3��ģ���ŵ�����������
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
	case 3://�ŵ�����ģʽ
		{
			int nSel = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_MODE);
			if (nSel==0)//ֱͨ
			{
				SetReadonlyGrid(nRow,nCol+1,FALSE);
 			}
			else if (nSel == 1)//��ת
			{
				SetReadonlyGrid(nRow,nCol+1,TRUE);
 			}
		}
		break;
	case 13://������������
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
	case 15://������������
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
	case 20://�������ܿ���
		{
			int nSel = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_DIGIT_VOICEKEY_EN);
			if (nSel==0)//ֱͨ
			{
				SetReadonlyGrid(nRow,nCol+1,TRUE);
			}
			else if (nSel == 1)//��ת
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
	item.col = 1;//�ŵ�������
	//��ȡ�����еĵ�ǰֵ
	int	temp = GetChaninfoInChannel(m_nCurrentZone,nRow,CHANNEL_CHASS);
		//((CPCSWDoc*)GetDocument())->GetByteValuesInCh(CHANNEL_CHASS,m_nCurrentZone,nRow);
	item.row = nRow;
	int nCol = sizeof(strChannelInfo)/sizeof(strChannelInfo[0]);
	if (temp == 0)//δ����
	{
		for (item.col = 2;item.col<nCol;item.col++)
		{
			item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
			item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
			item.szText = m_GridCtrl.GetItemText(nRow,item.col);
			//��������ɫ����
			m_GridCtrl.SetItemBkColour(nRow,item.col,RGB(125,125,125));//GetSysColor(COLOR_3DFACE));
			m_GridCtrl.SetItemFgColour(nRow,item.col,RGB(225,225,225));//GetSysColor(COLOR_GRAYTEXT));
			m_GridCtrl.SetItem(&item);
		}
		return TRUE;
	}
	else if(temp == 1)//�����ŵ�
	{
		for (item.col = 2;item.col<nCol;item.col++)
		{
			switch (item.col)
			{
				case 17://�������б�
				case 18://������ϵ��
				case 19://��ò��ʽ
				case 20://��������
				case 21://������������
					{
						item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
						item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
						item.szText = m_GridCtrl.GetItemText(nRow,item.col);
						//��������ɫ����
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
	else if (temp == 2)//ģ���ŵ�
	{
		for (item.col = 2;item.col<nCol;item.col++)
		{
			switch (item.col)
			{
			case 11://β��������λ
			case 12://��æ����
			case 13://������������
			case 14://���������
			case 15://������������
			case 16://���������
				{
					item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
					item.mask = GVIF_TEXT|GVIF_FORMAT|GVIS_READONLY;
					item.szText = m_GridCtrl.GetItemText(nRow,item.col);
					//��������ɫ����
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
//����������뵽combo����
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
	if(m_nZonenum<16)//�����һ�����������
	{
		m_nZonenum++;
		m_nCurrentZone = m_nZonenum;
		//д����ֵ,�������ݺ���
		int i,nChanCnt = 16;//����֧���ŵ���
		SetInfo(m_nCurrentZone,0,ZONE_CHANNEL_NUM,nChanCnt,18,0,false);
// 		//�Ӻ���ǰ��ʼ����
// 		for(i=0;i<m_nZonenum-m_nCurrentZone;i++)
// 		{
// 			memcpy(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00+(m_nZonenum-i)*736],
// 				&((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00+(m_nZonenum-1-i)*736],736);		
// 		}
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00+(m_nZonenum-1)*736],0x00,736);//����ǰ��0
		((CPCSWApp*)AfxGetApp())->m_CommInfo.pChannelInfo[0x00] = m_nZonenum;
		CString		str;
		str.Format("����%d",m_nZonenum);
		SetName(m_nZonenum,1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,str,18,0,false);//�������		
		//Ȼ��༭���
		SetDefaultData();
	}
	LoadData();
}

/************************************************************************/
/* ���ṩ���빦��                                                                     */
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
	if(m_nZonenum>1)//���ٱ���һ������
	{
		m_nZonenum--;
		int i=m_nCurrentZone;
//		m_nCurrentZone = m_nZonenum;
		//�Ƚ�������������֧���ŵ�������Ϣ��ǰ�ƶ�
		while(i>0)
		{
			memcpy(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo[0x00+(m_nZonenum-1-i)*18],
				&((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo[0x00+(m_nZonenum-i)*18],18);
			SetInfo(m_nZonenum-1-i,1,ZONE_RESERVE,0xff,18,0,false);//����λ����
			i--;
		}
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pZoneInfo[0x00+(m_nZonenum-1)*18],
			0x00,18);
		SetInfo(m_nCurrentZone,1,ZONE_CHANNEL_NUM,0x00,18,0,false);
		SetInfo(m_nCurrentZone,1,ZONE_RESERVE,0xff,18,0,false);
	}
	else if (m_nZonenum == 1)
	{
		MessageBox("�޷�����ɾ���������ٱ���һ��������Ϣ����ͨ��","��ʾ");
	}
	LoadData();
}
/************************************************************************/
/*��ȡ����ֵ�ĺ��� 
                                                                     */
/************************************************************************/
CString	CZoneInfo::GetSpecialInfo(int nAddr,int nChnum,int nZonenum)
{
	CString	str;
	m_GridComboZone.ResetContent();
	if(nAddr<0)
	{
		str.Format("��ַ����:%d",nAddr);
			return 	(str);
	}
	switch (nAddr)
	{
	case CHANNEL_CHANNAME://�ŵ�����
		{
			str = GetName(nZonenum,nChnum,nAddr,ZONE_CHANNEL_NAME_BYTE);
			//	((CPCSWDoc*)GetDocument())->GetChannelName(ZONE_CHANNEL_NAME_BYTE,nAddr,nZonenum,nChnum);
		}
		break;
	case CHANNEL_TX_FREQ://����Ƶ��
		{
			str = GetChanFreq(CHANNEL_TX_FREQ,nZonenum,nChnum);
			//	((CPCSWDoc*)GetDocument())->GetChannelFreq(CHANNEL_TX_FREQ,nZonenum,nChnum);
		}
		break;
	case CHANNEL_RX_FREQ://����Ƶ��
		{
			str = GetChanFreq(CHANNEL_RX_FREQ,nZonenum,nChnum);
			//	((CPCSWDoc*)GetDocument())->GetChannelFreq(CHANNEL_RX_FREQ,nZonenum,nChnum);
		}
		break;

	case CHANNEL_SPEECH_ENHANCE_LEVEL://������ǿ
		{
			int temp,i;
			temp =	GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_SPEECH_ENHANCE_LEVEL);
			for (i=0;i<ArraySize(strSpeechEnhLev);i++)
			{
				m_GridComboZone.AddString(strSpeechEnhLev[i]);
			}
				//((CPCSWDoc*)GetDocument())->GetByteValuesInCh(CHANNEL_SPEECH_ENHANCE_LEVEL,nZonenum,nChnum);
// 			str.Format("�ر�%d",temp);

			m_GridComboZone.GetLBText(temp,str);
		}
		break;
	case CHANNEL_DIGIT_VOICEKEY://��������
		{
			str = GetVoiceEncryptCode(CHANNEL_DIGIT_VOICEKEY,nZonenum,nChnum);
				//((CPCSWDoc*)GetDocument())->GetVoiceEncryptCode(CHANNEL_DIGIT_VOICEKEY,nZonenum,nChnum);
		}
		break;
	case CHANNEL_RX_ANALOG_SIG_NUM:
		{
			int nType = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_RX_ANALOG_SIG_TYPE);//��������
			int nTmp = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_RX_ANALOG_SIG_NUM);
			//��Ϊcdcss����Ϊ1������Ϊ2��3
			if (nType>0&& nType<=3)
			{
				DcsCtcData(nType);
				m_GridComboZone.GetLBText(nTmp,str);
			}
			else if (nType == 0)//����Ϊ��ʱ
			{
				str = _T("δ����");
			}
 			else
				str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_TX_ANALOG_SIG_NUM:
		{
			int nType = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_TX_ANALOG_SIG_TYPE);//��������
			int nTmp = GetChaninfoInChannel(nZonenum,nChnum,CHANNEL_TX_ANALOG_SIG_NUM);
			//��Ϊcdcss����Ϊ1������Ϊ2��3
			if (nType>0&& nType<=3)
			{
				DcsCtcData(nType);
				if(nTmp <m_GridComboZone.GetCount())
				{
					m_GridComboZone.GetLBText(nTmp,str);
				}
				else
					str.Format("ȡֵ����:%d",nTmp);
			}
			else if (nType == 0)//����Ϊ��ʱ
			{
				str = _T("δ����");
			}
			else
				str.Format("ȡֵ����:%d",nTmp);
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
		(str.Format("��ַ����:%d",nAddr));
		return str;
	}
	switch (nAddr)
	{
	case CHANNEL_CHASS://�ŵ�����
		{
			 if (nTmp>=0 && nTmp<4)//ȡֵ��Χ0-3
			 {
				 str = strCHASS[nTmp];
			 }
			 else
				 str.Format("ȡֵ����:%d",nTmp);
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
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_MODE:
		{
			if(nTmp==0 || nTmp == 1)
				str = strMODE[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_STATUS:
		{
			if(nTmp == 0 || nTmp == 1)
				str = strSTATUS[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_POWER_LEVEL:
		{
			if(nTmp == 0 || nTmp == 1)
				str = strPOWER[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_INTERVAL:
		{
			if(nTmp >= 0 && nTmp <=3 )
				str = strINTERVAL[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_CTC_PHASE:
		{
			if(nTmp == 0 ||nTmp == 1 )
				str = strCTCPHASE[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_BUSYLOCK:
		{
			if(nTmp == 0 || nTmp == 1)
				str = strBUSYLOCK[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_TX_ANALOG_SIG_TYPE://����ģ����������
		{
			 if (nTmp>=0 && nTmp<4)//ȡֵ��Χ0-3
			 {
				 str = strSIGNALTYPE[nTmp];
			 }
			 else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_RX_ANALOG_SIG_TYPE:
		{
			 if (nTmp>=0 && nTmp<4)//ȡֵ��Χ0-3
			 {
				 str = strSIGNALTYPE[nTmp];
			 }
			 else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_RX_GROUP://�������б�
		{
			if(nTmp >=0 && nTmp<=32 )
			{
				LoadGrplist();
				m_GridComboZone.GetLBText(nTmp,str);
			}	
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_SEND_ID://Ĭ�Ϸ�����ϵ��
		{
			if(nTmp >=0 && nTmp<=200 )
			{
				LoadContactlist();
				m_GridComboZone.GetLBText(nTmp,str);
			}
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_POLITE://��ò��ʽ
		{
			if(nTmp == 0 || nTmp == 1)
				str = strPOLITE[nTmp];
			else
				 str.Format("ȡֵ����:%d",nTmp);
		}
		break;
	case CHANNEL_DIGIT_VOICEKEY_EN:
		{
			if(nTmp == 0 )
				str = _T("�ر�");
			else if( nTmp == 1)
				str = _T("����");
			else
				 str.Format("ȡֵ����:%d",nTmp);
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
	case 1://�ŵ�����
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
	case 10://������ǿ��Ҫע��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_GridCtrl.SetEditState(FALSE);
	CCellID		cell = m_GridCtrl.GetFocusCell();
	CString		str;
	m_GridEditZone.GetWindowText(str);
	switch (cell.col)
	{
	case 5://�ŵ�����
		{
			if (str.IsEmpty())//�ձ���
			{
				MessageBox("�������ŵ�����","��ʾ");
				return;
			}
			//�������鿴�ñ����Ƿ��ظ�,ֻ�ڱ�������
			CString		strName;
			int i;
			for(i=1;i<m_GridCtrl.GetRowCount()-1;i++)
			{
				if(i!=cell.row)//���뱾�ŵ������Ƚ�
				{
					strName = GetName(m_nCurrentZone,i,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE);
					if (strName.CompareNoCase(str)!=-1)
					{
						break;
					}
				}
			}
			if (i == m_GridCtrl.GetRowCount())//���ظ�����д��
			{
				SetName(m_nCurrentZone,cell.row,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE,str);
			}
		}
		break;
	case 6:
	case 7://Ƶ��д��
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if (i<m_nZonenum)//����δ�ҵ���ͬ���ƣ���д��������
	{
		SetName(m_nCurrentZone,1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,str,18,0,false);
	}
	LoadData();
}

