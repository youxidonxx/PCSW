// MenuKeyView.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "MenuKeyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern	CPCSWApp	theApp;
/////////////////////////////////////////////////////////////////////////////
// CMenuKeyView
static	CString	strMenuName[] = {
			"���ʼ���",	"��������","����","�����","LED��ʾ��","��ʾ��","����",	"����",	//8
			"����ȼ�",	"��ϵ�б��е�ɾ����","ɨ��",	"ɨ���в鿴ɨ���ŵ�",				//4
			"ɨ������ʱ�����ŵ�","ɨ������ʱɾ���ŵ�",	"ɨ�������ŵ�","ɨ��ɾ���ŵ�",	//4
			"����",	"����",	"��",	"ʱ������������",		"��������ʾ","ʡ��ģʽ","����",			//7
 		    "������ǿ","��������",	"�������𼤻�","��������ң��"	//4
};
static	CString	strKeyFuncName[] = {
		"�޹���","��������","��������","��������","���ʼ������","���м�¼","����",
			"������","����������","���������ر�","����ر�/��","���뼶�����","��ϵ�б�",
			"ɨ��","�����ŵ���ʱɾ��","ң��","����","����","����","��ص�����ʾ","�����ϵ�",
			"�����µ�","����","������ǿ","��������"
};
static	CString	strKeyName[] = 
{
	"���ܼ�1�̰�����","���ܼ�1��������","���ܼ�2�̰�����","���ܼ�2��������","TOP���̰�����","TOP��������",
		"�˵�����������","���˼���������","������̰�����","�������������","���ػ����̰�����"
};

IMPLEMENT_DYNCREATE(CMenuKeyView, CFormView)

CMenuKeyView::CMenuKeyView()
	: CFormView(CMenuKeyView::IDD)
{
	//{{AFX_DATA_INIT(CMenuKeyView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMenuKeyView::~CMenuKeyView()
{
}

void CMenuKeyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuKeyView)
// 	DDX_Control(pDX, IDC_COMBO_KEYFUNC, m_GridComboZone);
	DDX_Control(pDX, IDC_LIST_MENU, m_listMenu);
	//}}AFX_DATA_MAP
// 	DDX_GridControl(pDX,IDC_CUSTOM2,m_GridCtrl);
}


BEGIN_MESSAGE_MAP(CMenuKeyView, CFormView)
	//{{AFX_MSG_MAP(CMenuKeyView)
// 	ON_CBN_SELCHANGE(IDC_COMBO_KEYFUNC, OnSelchangeComboKeyfunc)
	//}}AFX_MSG_MAP
// 	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_CUSTOM2, OnEditGrid)
// 	ON_MESSAGE(WM_ON_CHKBOX,OnCheckBox)
	ON_NOTIFY(LVN_COLUMNCLICK,IDC_LIST_MENU,OnCheckBox)
	ON_CONTROL_RANGE(CBN_SELCHANGE,IDC_COMBO_KEYFUNC_1,IDC_COMBO_KEYFUNC_11,OnSelchangeComboKeyfunc)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuKeyView diagnostics

#ifdef _DEBUG
void CMenuKeyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMenuKeyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMenuKeyView message handlers

void CMenuKeyView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
 	DWORD	style;
	style = m_listMenu.GetExtendedStyle();//GetWindowLong(m_listMenu.m_hWnd,GWL_STYLE);
	style |= LVS_EX_FULLROWSELECT;
	style |= LVS_EX_GRIDLINES;
	style |= LVS_EX_CHECKBOXES;

	m_listMenu.SetExtendedStyle(style);
	
// 	m_listMenu.SetColumnHeader(_T("�Ƿ�ѡ��, 100; �˵�����, 150"));
	srand((unsigned)time(NULL));

	m_listMenu.InsertColumn(0,_T("ѡ��"),LVCFMT_LEFT,40);
	m_listMenu.InsertColumn(1,_T("�˵�����"),LVCFMT_CENTER,200);
  	LoadMenuItem();
	SetStaticName();
	LoadKeyFunc();
// 	LoadKeyGridItem();
// 	if(GetDocument()!=NULL)
		LoadData();
 	m_listMenu.SetGridLines(TRUE); // SHow grid lines
	m_listMenu.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
	m_listMenu.SetEditable(TRUE); // Allow sub-text edit


}
void	CMenuKeyView::PreTranslateMessage(MSG* pMsg)
{
	return CFormView::PreTranslateMessage(pMsg);
}
void	CMenuKeyView::LoadMenuItem()
{
	m_listMenu.DeleteAllItems();
	for (int i = 0; i < ArraySize(strMenuName); i++)
	{
		const int IDX = m_listMenu.InsertItem(i, _T(""));//���޸þ䣬���޷��ڽ�������ʾ
		m_listMenu.SetItemText(i, 0,_T(""));
 		m_listMenu.SetItemText(i, 1,  strMenuName[i]);	
	}
}
void	CMenuKeyView::LoadKeyFunc()
{
	int i=0,j=0;
	for (;i<ArraySize(strKeyName);i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_KEYFUNC_1+i))->ResetContent();
		for(j=0;j<ArraySize(strKeyFuncName);j++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_KEYFUNC_1+i))->AddString(strKeyFuncName[j]);
		}
		((CComboBox*)GetDlgItem(IDC_COMBO_KEYFUNC_1+i))->SetCurSel(0);

	}
}
void	CMenuKeyView::LoadData()
{
	if (theApp.m_CommInfo.bHasInfo)
	{
		int nVal=-1;
		int i=0;
		//combobox��ֵ
		for (;i<ArraySize(strKeyName);i++)
		{
			nVal = GetKeyFuncValues(0x00+i);
			if (nVal>=0 && nVal<=24)
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_KEYFUNC_1+i))->SetCurSel(nVal);
			}
			else
				((CComboBox*)GetDlgItem(IDC_COMBO_KEYFUNC_1+i))->SetCurSel(-1);
		}
		//listctrl��ֵ
		for (i=0;i<m_listMenu.GetItemCount()-2;i++)
		{
			nVal = GetCheckValues(i);
			if(nVal!=1)
				nVal = 0;
			m_listMenu.SetCheck(i,nVal);
		}
		nVal = GetKillUnkill(MenuAllowKill);
		m_listMenu.SetCheck(i++,nVal);
		nVal = GetKillUnkill(MenuAllowActive);
		m_listMenu.SetCheck(i++,nVal);
	}
}
int		CMenuKeyView::GetCheckValues(int nFlag )
{
	int	nRet  = theApp.m_CommInfo.pMenuSetting[0x00+nFlag];
 	return nRet;
}
int		CMenuKeyView::GetKillUnkill(int nFlag)
{
	int	nRet  = theApp.m_CommInfo.pRadioSetting[0x00+nFlag];
	return nRet;
}
int		CMenuKeyView::GetKeyFuncValues(int nFlag)
{
	int	nRet  = theApp.m_CommInfo.pKeyFunctionSetting[0x00+nFlag];
	return nRet;
}
void	CMenuKeyView::SetStaticName()
{
	int i=0;
	for (;i<ArraySize(strKeyName);i++)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_KEYNAME_1+i))->SetWindowText(strKeyName[i]+":");
	}
}
void	CMenuKeyView::SetKeyFunc(int nFlag,int nVal)
{
	((CPCSWApp*)AfxGetApp())->m_CommInfo.pKeyFunctionSetting[0x00+nFlag] = nVal;
}
void	CMenuKeyView::OnSelchangeComboKeyfunc(UINT	nID) 
{
	// TODO: Add your control notification handler code here
	int nIndex = nID<IDC_COMBO_KEYFUNC_11?(nID - IDC_COMBO_KEYFUNC_1):-1;
	if (nIndex<0)
	{
		return;
	}
	int nVal = ((CComboBox*)GetDlgItem(nID))->GetCurSel();
	if (nVal>=0 && nVal<=24)
	{
// 		((CPCSWDoc*)GetDocument())->SetKeyFunc(nIndex,nVal);
		SetKeyFunc(nIndex,nVal);
	}
}
void	CMenuKeyView::OnCheckBox(NMHDR * pNMHDR, LRESULT* pResult)
{
	int nItem = (int*)pNMHDR;
	UINT	nMouseEvent = (UINT*)pResult;

}