// PropPageContact.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "PropPageContact.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageContact property page
#define		CONTENT_COLUMN_NUM	4
static	CString	strTitle[] = {"���","���б���","��������","���к���"};
static	CString	strType[] = {"����ϵ��","����","���","ȫ��"};

IMPLEMENT_DYNCREATE(CPropPageContact, CPropertyPage)

CPropPageContact::CPropPageContact() : CPropertyPage(CPropPageContact::IDD)
{
	//{{AFX_DATA_INIT(CPropPageContact)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCont = new byte[0x2000];
	m_Cnt = 0;
}

CPropPageContact::~CPropPageContact()
{
}

void CPropPageContact::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageContact)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbContent);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_editContent);
	//}}AFX_DATA_MAP
	DDX_Control(pDX,IDC_GRID_CONTACT_2,m_gridCtrl);
}


BEGIN_MESSAGE_MAP(CPropPageContact, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageContact)
	//}}AFX_MSG_MAP
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_CONTACT_2, OnGridEdit)

	ON_BN_CLICKED(IDC_BUTTON_CONT_ADD, &CPropPageContact::OnBnClickedButtonContAdd)
	ON_BN_CLICKED(IDC_BUTTON_CONT_DEL, &CPropPageContact::OnBnClickedButtonContDel)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CPropPageContact::OnCbnSelchangeComboType)
	ON_EN_KILLFOCUS(IDC_EDIT_CONTENT, &CPropPageContact::OnEnKillfocusEditContent)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageContact message handlers

BOOL CPropPageContact::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(m_pCont!=NULL)
		m_Cnt = m_pCont[0x00];
  
	m_gridCtrl.SetRowCount(m_Cnt+1);
	m_gridCtrl.SetColumnCount(CONTENT_COLUMN_NUM);
 	m_gridCtrl.SetFixedRowCount();

	LoadData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//LRESULT	CPropPageContact::OnGridEdit(GV_DISPINFO* pInfo, LRESULT* pResult)
void	CPropPageContact::OnGridEdit(NMHDR * pNMHDR, LRESULT * pResult)
{
	GV_DISPINFO* pInfo = (GV_DISPINFO*)pNMHDR;
	CRect	rect(pInfo->rect);
	ScreenToClient(&rect);
	m_cbContent.ResetContent();
	int i;
	if(pInfo->item.col>=0 && pInfo->item.col<4)
		m_gridCtrl.SetEditState(TRUE);
	switch(m_gridCtrl.GetFocusCell().col)
	{
	case 0://���
		{
			m_editContent.Initialize(CGridEdit::Name,2,pInfo->item.szText,&rect);
		}
		break;
	case 1://����
		{
			m_editContent.Initialize(CGridEdit::Name,16,pInfo->item.szText,&rect);
		}
		break;
	case 2://����
		{
			for(i=0;i<ArraySize(strType);i++)
				m_cbContent.AddString(strType[i]);
			m_cbContent.Init(rect,pInfo->item.szText);
		}
		break;
	case 3://����
		{
			m_editContent.Initialize(CGridEdit::Name,7,pInfo->item.szText,&rect);
		}
		break;
	default:
		break;
	}
			m_gridCtrl.SetRedraw(TRUE,TRUE);//�����������
	return  ;
}
//��ţ����֣����ͣ�����
void	CPropPageContact::LoadData()
{
// 	if(m_pCont!=NULL)
		m_Cnt =*(WORD*)((CPCSWApp*)AfxGetApp())->m_CommInfo.pContactInfo;//��ȡ��ϵ�˸���
		m_Cnt/=CONTACT_STRUCT_LEN;
	if (m_Cnt>200 || m_Cnt<1)
	{
		m_Cnt = 1;
	}
	if (m_Cnt!=m_gridCtrl.GetRowCount()-1)
	{
		m_gridCtrl.SetRowCount(m_Cnt+1);
		m_gridCtrl.SetColumnCount(CONTENT_COLUMN_NUM);
 		m_gridCtrl.SetFixedRowCount();
	}
		int	nColumn[] = {50,80,80,120};
	
		GV_ITEM	item;
		for(item.col = 0;item.col < sizeof(nColumn)/sizeof(nColumn[0]);item.col++)
			m_gridCtrl.SetColumnWidth(item.col,nColumn[item.col]);
		for(item.row = 0;item.row < m_Cnt+1;item.row++)
			m_gridCtrl.SetRowHeight(item.row,20);
		if (m_Cnt>0)
		{
			m_gridCtrl.SetGridResize(FALSE,TRUE);	//��͸߶��Ƿ�ɸ���
			m_gridCtrl.EnableSelection(FALSE);
			item.mask	= GVIF_TEXT	| GVIF_FORMAT;
			item.nFormat= DT_CENTER | DT_VCENTER | DT_SINGLELINE;
			item.row=0;
			//ÿһ�еı��⣬����һ�д�������
			int nColumn  = sizeof(strTitle)/sizeof(strTitle[0]);
			for (item.col = 0;item.col<nColumn;item.col++)
			{
				item.szText = strTitle[item.col];
				m_gridCtrl.SetItem(&item);
			}
			//�༭ÿ�е���ֵ
			for (item.row = 1;item.row<=m_Cnt;item.row++)
			{
				LoadRowInfo(item.row,CONTENT_COLUMN_NUM);
			}
			m_gridCtrl.SetRedraw(TRUE,TRUE);//�����������
		}
}


void	CPropPageContact::LoadRowInfo(int nRow,int nCol)
{
	if(nRow==0)
		return;
 	int nCntnum = ((CPCSWApp*)AfxGetApp())->GetContInfo(CONTACT_NUM,nRow);//m_pCont[0x00+2+CONTACT_NUM+(nRow-1)*22];
	int	nType = ((CPCSWApp*)AfxGetApp())->GetContInfo(CONTACT_TYPE,nRow);;//m_pCont[0x00+2+CONTACT_TYPE+(nRow-1)*22];
	CString	name = ((CPCSWApp*)AfxGetApp())->GetContName(nRow,NAME_BYTE_LEN);
	CString	id = ((CPCSWApp*)AfxGetApp())->GetContID(nRow,ID_BYTE_LEN);
	if (nCntnum>0)//����δ����
	{
		GV_ITEM	item;
		item.row = nRow;
		item.mask = GVIF_TEXT|GVIF_FORMAT ;
		item.nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;	
		CString	str=_T("");
		//��Ϊ�����ʱ��ֱ����������
		item.col = 0;
		str.Format("%d",nCntnum);
		item.szText = str;
		m_gridCtrl.SetItem(&item);
		//����
		item.col++;
 		item.szText =name;
		m_gridCtrl.SetItem(&item);
		//������
		item.col++;
		if (nType<=3 && nType>=0)
		{
			item.szText = strType[nType];
			m_gridCtrl.SetItem(&item);
		}
		else
		{
			str.Format("������ֵ���󣬱���ֵ����Ϊ%d,����0-3�ķ�Χ",nType);
			item.szText = str;
			m_gridCtrl.SetItem(&item);
		}
		//����
		item.col++;
		item.szText = id;
		m_gridCtrl.SetItem(&item);

	}
	else
	{
		m_gridCtrl.SetFixedRowCount(nRow);
	}
}
void	CPropPageContact::GetOriginalRect(CRect *pRect)
{
	DLGTEMPLATE* pTmp = NULL;

	pRect->SetRectEmpty();

	if(m_hDialogTemplate)
		pTmp = (DLGTEMPLATE*)m_hDialogTemplate;
	else if (m_lpDialogTemplate)
		pTmp = (DLGTEMPLATE*)m_lpDialogTemplate;

	// Found it, Set the Rectangle
	if (pTmp)
	{
		pRect->SetRect(0, 0, pTmp->cx, pTmp->cy);

		//It's in Dialog units so convert
		MapDialogRect(pRect);
	}
}

void CPropPageContact::OnBnClickedButtonContAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Cnt<=200)
	{
		 m_Cnt++;
// 		 ((CPCSWApp*)AfxGetApp())->m_CommInfo.pContactInfo[0x00] = (WORD)(m_Cnt*CONTACT_STRUCT_LEN);
// 		 ((CPCSWApp*)AfxGetApp())->m_CommInfo.pContactInfo[0x01] = (WORD)(m_Cnt*CONTACT_STRUCT_LEN)>>8;
		 ((CPCSWApp*)AfxGetApp())->SetContCount(m_Cnt*CONTACT_STRUCT_LEN);
		 ((CPCSWApp*)AfxGetApp())->SetContInfo(CONTACT_NUM,m_Cnt,m_Cnt);
	}
	LoadData();
}

void CPropPageContact::OnBnClickedButtonContDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CPropPageContact::OnCbnSelchangeComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_gridCtrl.SetEditState(FALSE);
	CCellID		cell = m_gridCtrl.GetFocusCell();
	if (cell.col == 2)//��������
	{
		int nSel = m_cbContent.GetCurSel();
		((CPCSWApp*)AfxGetApp())->SetContInfo(CONTACT_TYPE,cell.row,nSel);
	}
	m_cbContent.End();
	LoadData();
}

void CPropPageContact::OnEnKillfocusEditContent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_gridCtrl.SetEditState(FALSE);
	CCellID		cell = m_gridCtrl.GetFocusCell();
	CString		str ;
	m_editContent.GetWindowText(str);
	CString		strTmp;
	if (cell.col == 1)//����
	{
		//�Ƿ����������Ƴ�ͻ
		int i=1;
		for (;i<m_gridCtrl.GetRowCount();i++)
		{
			if(i!=cell.row)
			{
				strTmp = ((CPCSWApp*)AfxGetApp())->GetContName(cell.row,NAME_BYTE_LEN);
				if (strTmp.CompareNoCase(str)!=-1)
				{
					break;
				}
			}
		}
		if (i == m_gridCtrl.GetRowCount())//���ظ�����д��
		{
			((CPCSWApp*)AfxGetApp())->SetContName(CONTACT_NAME,cell.row,str,NAME_BYTE_LEN);
 		}
	}
	else if (cell.col == 3)//����
	{
		((CPCSWApp*)AfxGetApp())->SetContID(CONTACT_ID,cell.row,str);
	}
	m_editContent.HideWindow();
	LoadData();
}
