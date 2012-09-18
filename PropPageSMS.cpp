// PropPageSMS.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "PropPageSMS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageSMS property page
#define		SMS_CONTENT_LEN		160	//  根据接口文档定义消息内容的长度
static	CString	strTitle[] = {"序号","短信内容"};

IMPLEMENT_DYNCREATE(CPropPageSMS, CPropertyPage)

CPropPageSMS::CPropPageSMS() : CPropertyPage(CPropPageSMS::IDD)
{
	//{{AFX_DATA_INIT(CPropPageSMS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nGridCnt = 1;
	m_pSms = new byte[0x2000];
}

CPropPageSMS::~CPropPageSMS()
{
}

void CPropPageSMS::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageSMS)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_EDIT_SMS,m_gridEdit);
	//}}AFX_DATA_MAP
	DDX_GridControl(pDX,IDC_GRID_SMS,m_gridCtrl);
}


BEGIN_MESSAGE_MAP(CPropPageSMS, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageSMS)
	//}}AFX_MSG_MAP
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_SMS, OnGridEdit)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPropPageSMS::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CPropPageSMS::OnBnClickedButtonDel)
	ON_EN_KILLFOCUS(IDC_EDIT_SMS, &CPropPageSMS::OnEnKillfocusEditSms)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageSMS message handlers

BOOL CPropPageSMS::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
  
	m_gridCtrl.SetRowCount(m_nGridCnt+1);
	m_gridCtrl.SetColumnCount(2);//只有2列
 	m_gridCtrl.SetFixedRowCount();
	m_gridCtrl.SetFixedColumnCount();

	
	LoadData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void	CPropPageSMS::LoadData()
{
	m_pSms = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pShortText;
	if(m_pSms!=NULL)
		m_nGridCnt = *(WORD*)m_pSms;
	else
		return;
	m_nGridCnt/=SHORTTEXT_STRUCT_LEN;

	if(m_nGridCnt>50 || m_nGridCnt<1)
		m_nGridCnt = 1;
// 	if (m_nGridCnt!=m_gridCtrl.GetRowCount()-1)
	{
		m_gridCtrl.DeleteAllItems();
		m_gridCtrl.SetRowCount(m_nGridCnt+1);
		m_gridCtrl.SetColumnCount(2);//只有2列
 		m_gridCtrl.SetFixedRowCount();
		m_gridCtrl.SetFixedColumnCount();
		
	}
		m_gridCtrl.SetGridResize(FALSE,TRUE);	//宽和高度是否可更改
		m_gridCtrl.EnableSelection(FALSE);
		int nColumn[] = {50,450};
		GV_ITEM	item;
		for(item.col = 0;item.col < sizeof(nColumn)/sizeof(nColumn[0]);item.col++)
			m_gridCtrl.SetColumnWidth(item.col,nColumn[item.col]);
		for(item.row = 0;item.row < m_nGridCnt+1;item.row++)
			m_gridCtrl.SetRowHeight(item.row,20);
		if (m_nGridCnt>0)
		{
			item.mask	= GVIF_TEXT	| GVIF_FORMAT;
			item.nFormat= DT_CENTER | DT_VCENTER | DT_SINGLELINE;
			item.row=0;
			//每一列的标题，即第一行处标题栏
			int nColumn  = ArraySize(strTitle);
			for (item.col = 0;item.col<nColumn;item.col++)
			{
				item.szText = strTitle[item.col];
				m_gridCtrl.SetItem(&item);
			}
			//输入每条短信内容
			for (item.row =1;item.row<=m_nGridCnt;item.row++)
			{
				LoadRowInfo(item.row,2);
			}
			m_gridCtrl.SetRedraw(TRUE,TRUE);
		}
}
CString	CPropPageSMS::GetSmsCont(int nGrp,int nLen)
{
	//要是超过160，只截取160部分内容
	if(nLen>SMS_CONTENT_LEN)
		nLen = SMS_CONTENT_LEN;
	BYTE *ptr;
	BYTE *szTemp  = new BYTE [nLen*2];
	ptr = &m_pSms[0x00+2+SMS_TXTCONTENT+(nGrp-1)*162];
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer(nLen);
 	return str;
}
void	CPropPageSMS::LoadRowInfo(int nRow,int nCol)
{
	if(nRow==0)
		return;
 	int nSmsnum = m_pSms[0x00+2+SMS_TXTNUM+(nRow-1)*162];
	int	nSmslen = m_pSms[0x00+2+SMS_TXTLEN+(nRow-1)*162];
	CString	sms = GetSmsCont(nRow,nSmslen);
	if (nSmsnum>0)
	{
		GV_ITEM	item;
		item.row = nRow;
		item.mask = GVIF_TEXT|GVIF_FORMAT ;
		item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;	
		//序号列
		item.col = 0;
		CString	str;
		str.Format("%d",nSmsnum);
		item.szText = str;
		m_gridCtrl.SetItem(&item);
		//内容
		item.col++;
		item.szText = sms;
		m_gridCtrl.SetItem(&item);
	}
 
}
void CPropPageSMS::OnGridEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	GV_DISPINFO*	pInfo = (GV_DISPINFO*)pNMHDR;
	CRect	rect(pInfo->rect);
	ScreenToClient(&rect);
 	if(pInfo->item.col>=0 && pInfo->item.col<2)
		m_gridCtrl.SetEditState(TRUE);
	switch(pInfo->item.col)
	{
// 	case 0://序号
// 		{
// 			m_gridEdit.Initialize(CGridEdit::Name,2,pInfo->item.szText,&rect);
// 		}
// 		break;
	case 1://内容
		{
			m_gridEdit.Initialize(CGridEdit::Name,160,pInfo->item.szText,&rect);
		}
		break;
	default:
		break;
	}
	return  ;
}

BOOL CPropPageSMS::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
 	if (PSN_SETACTIVE == ((LPNMHDR)lParam)->code)
	{		// just changed tabs
		LoadData();
	}
//	return TRUE;
 	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}
void CPropPageSMS::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nGridCnt<50)
	{
		m_nGridCnt++;
		((CPCSWApp*)AfxGetApp())->SetSmsCount(m_nGridCnt*SHORTTEXT_STRUCT_LEN);//总数写入
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pShortText[0x00+2+(m_nGridCnt-1)*SHORTTEXT_STRUCT_LEN],
			0x00,SHORTTEXT_STRUCT_LEN);
		((CPCSWApp*)AfxGetApp())->SetSmsInfo(SMS_TXTNUM,m_nGridCnt,m_nGridCnt);
		((CPCSWApp*)AfxGetApp())->SetSmsInfo(SMS_TXTLEN,m_nGridCnt,0);
	}
	LoadData();
	m_gridCtrl.SetFocusCell(m_nGridCnt,1);
}

void CPropPageSMS::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	CCellID		cell = m_gridCtrl.GetFocusCell();
	if (!cell.IsValid())
	{
		MessageBox("请先选择要删除的项目","提示");
		return;
	}
	if (m_nGridCnt>0)
	{
		int nRow = cell.row;
		int	nSmsnum,nTxlen;
		while (nRow<m_nGridCnt)
		{//从后面往前搬移
// 			nSmsnum = ((CPCSWApp*)AfxGetApp())->GetSmsInfo(nRow+1,SMS_TXTNUM);
// 			nSmsnum--;
			nSmsnum = nRow;
			memcpy(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pShortText[0x00+2+(nRow-1)*SHORTTEXT_STRUCT_LEN],
				&((CPCSWApp*)AfxGetApp())->m_CommInfo.pShortText[0x00+2+nRow*SHORTTEXT_STRUCT_LEN],SHORTTEXT_STRUCT_LEN);
			//序号还得改变
			((CPCSWApp*)AfxGetApp())->SetSmsInfo(SMS_TXTNUM,nRow,nSmsnum);
			nTxlen = ((CPCSWApp*)AfxGetApp())->GetSmsInfo(nRow,SMS_TXTLEN);
			((CPCSWApp*)AfxGetApp())->SetSmsInfo(SMS_TXTLEN,nRow,nTxlen);
			nRow++;
		}
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pShortText[0x00+2+(nRow-1)*SHORTTEXT_STRUCT_LEN],
			0x00,SHORTTEXT_STRUCT_LEN);
		m_nGridCnt--;
		((CPCSWApp*)AfxGetApp())->SetSmsCount(m_nGridCnt*SHORTTEXT_STRUCT_LEN);//总数写入

 	}
	LoadData();
}

void CPropPageSMS::OnEnKillfocusEditSms()
{
	// TODO: 在此添加控件通知处理程序代码
	CCellID		cell = m_gridCtrl.GetFocusCell();
	if (cell.col==1)
	{
		CString		str;
		m_gridEdit.GetWindowText(str);
		int		nlen = str.GetLength();
		int		nRow = cell.row;
		((CPCSWApp*)AfxGetApp())->SetSmsInfo(SMS_TXTNUM,nRow,nRow);
		((CPCSWApp*)AfxGetApp())->SetSmsInfo(SMS_TXTLEN,nRow,nlen);
		((CPCSWApp*)AfxGetApp())->SetSmsContent(SMS_TXTCONTENT,nRow,str,nlen);
		GV_ITEM	item;
		item.row = nRow;
		item.mask = GVIF_TEXT|GVIF_FORMAT ;
		item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;	
		//内容
		item.col = 0;
		CString	strID;
		strID.Format("%d",nRow);
		item.szText = strID;
		m_gridCtrl.SetItem(&item);
		//内容
		item.col++;
		item.szText = str;
		m_gridCtrl.SetItem(&item);
		
	}
	m_gridEdit.HideWindow();
//	LoadData();
}
