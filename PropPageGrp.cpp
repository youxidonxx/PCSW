// PropPageGrp.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "PropPageGrp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageGrp property page

IMPLEMENT_DYNCREATE(CPropPageGrp, CPropertyPage)

CPropPageGrp::CPropPageGrp() : CPropertyPage(CPropPageGrp::IDD)
{
	//{{AFX_DATA_INIT(CPropPageGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pGrp = new byte[0x2000];
	m_nCurrentGrp = 1;
	m_nGrp = 0;
	m_nTotalContact = 0;
}

CPropPageGrp::~CPropPageGrp()
{
}

void CPropPageGrp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageGrp)
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_LIST_USED_MEMBER, m_listUsedMember);
	DDX_Control(pDX, IDC_LIST_ALL_MEMBER, m_listAllMember);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageGrp, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageGrp)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CPropPageGrp::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CPropPageGrp::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CPropPageGrp::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CPropPageGrp::OnBnClickedButtonLast)
 	ON_BN_CLICKED(IDC_BUTTON_DELETE_GRPLIST, &CPropPageGrp::OnBnClickedButtonDeleteGrplist)
	ON_BN_CLICKED(IDC_BUTTON_ADD_GRPLIST, &CPropPageGrp::OnBnClickedButtonAddGrplist)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPropPageGrp::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPropPageGrp::OnBnClickedButtonDelete)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CPropPageGrp::OnEnKillfocusEditName)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageGrp message handlers

BOOL CPropPageGrp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_editName.SetLimitText(16);
	CRect	rect;
	GetClientRect(&rect);
	rect.right = rect.left+rect.Width()/2;
 	LoadData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void	CPropPageGrp::LoadData()
{
	m_pGrp = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList;
	if (m_pGrp!=NULL)
	{
		m_nGrp = *(WORD*)m_pGrp;
		m_nGrp/=34;
	}
	mapAllGrp.clear();

	int nGrpID = GetIDorNum(GRP_NUM,m_nCurrentGrp);//�б����
	int nGrpCnt = GetIDorNum(GRP_MEMBER_NUM,m_nCurrentGrp);//�б��Ա��
	CString		strName;
	strName = ((CPCSWApp*)AfxGetApp())->GetGrplistName(m_nCurrentGrp,NAME_BYTE_LEN);
	m_editName.SetWindowText(strName);
	SetStaticName();
	ListDataShow(nGrpID,nGrpCnt);
}
void	CPropPageGrp::SetStaticName()
{
	CString		str;
	str.Format("�б� %d/%d",m_nCurrentGrp,m_nGrp);
	((CStatic*)GetDlgItem(IDC_STATIC_GRP))->SetWindowText(str);
}
void	CPropPageGrp::ListDataShow(int nNum,int nMember)
{
 	m_listUsedMember.ResetContent();
  	m_listAllMember.ResetContent();

// 	if(nMember ==0)
// 		return;
	int i=0;
	int nContType,nContNum;
	CString		strID,strName;
	std::string	s;
	m_nTotalContact = *(WORD*)((CPCSWApp*)AfxGetApp())->m_CommInfo.pContactInfo;
	m_nTotalContact/=CONTACT_STRUCT_LEN;
	if (m_nTotalContact<=0)
	{
		return;
	}
	for (;i<m_nTotalContact;i++)//��������ϵ�˸���Ϊѭ������
	{	
		nContType = ((CPCSWApp*)AfxGetApp())->GetContInfo(CONTACT_TYPE,i+1);	
		if (nContType==2 || nContType==3)//���/ȫ������
		{
			nContNum = ((CPCSWApp*)AfxGetApp())->GetContInfo(CONTACT_NUM,i+1);
 			strID = ((CPCSWApp*)AfxGetApp())->GetContID(i+1,ID_BYTE_LEN);
			strName = ((CPCSWApp*)AfxGetApp())->GetContName(i+1,NAME_BYTE_LEN);
			strName = strName+":"+strID;
			m_listAllMember.AddString(strName);
			ConvertCString2String(strName,s);
			mapAllGrp.insert(pair<int ,std::string>(nContNum,s));
		}			
	}
	if(nMember>0)
	{
		int nIndex;
		for (i=0;i<nMember;i++)
		{
			nContNum = (WORD)m_pGrp[0x00+2+GRP_CONTACT_NUM+(nNum-1)*34+i];
			map_it = mapAllGrp.find(nContNum);
			if(map_it!=mapAllGrp.end())
			{
				strName.Format("%s",string(map_it->second).c_str());
				nIndex = m_listAllMember.FindString(-1,strName);
				m_listAllMember.GetText(nIndex,strID);
				m_listUsedMember.AddString(strID);
				ConvertCString2String(strName,s);
				mapUsedGrp.insert(pair<int,std::string>(int(map_it->first),s));
			}
		}
	}
	else
		m_listUsedMember.AddString("�޳�Ա");
}
int	CPropPageGrp::GetIDorNum(int nFlag,int nGrp)
{
	int nRet = m_pGrp[0x00+2+nFlag+(nGrp-1)*34];
	return nRet;
}

void CPropPageGrp::OnBnClickedButtonNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_nCurrentGrp<m_nGrp)
	{
		m_nCurrentGrp++;
	}
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonPrev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_nCurrentGrp>1)
	{
		m_nCurrentGrp--;
	}
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonFirst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurrentGrp = 1;
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurrentGrp = m_nGrp;
	LoadData();
}



void CPropPageGrp::OnBnClickedButtonDeleteGrplist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nGrpnum =	GetIDorNum(GRP_NUM,m_nCurrentGrp);
	if (nGrpnum>0)
	{
		int nRest = m_nGrp - nGrpnum;
		int	n=0;
		//��������б��������
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(m_nCurrentGrp-1)*GRP_LIST_STRUCT_LEN],
				0x00,GRP_LIST_STRUCT_LEN);
		//�������ѭ����ǰ����
		while (nRest>0)//�������һ���б����ݣ��������
		{
			//nRest ����ʣ��������nGrpnum������������+i(i<nrest)�Ϳ���ѭ������ǰ������
			memcpy(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(nGrpnum-1+n)*GRP_LIST_STRUCT_LEN],
				&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(nGrpnum+n)*GRP_LIST_STRUCT_LEN],
				GRP_LIST_STRUCT_LEN);
			nRest--;
			n++;
// 			m_nCurrentGrp++;
		}
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(nGrpnum+n-1)*GRP_LIST_STRUCT_LEN],
			0x00,GRP_LIST_STRUCT_LEN);
		m_nGrp--;
		((CPCSWApp*)AfxGetApp())->SetGrplistCount(m_nGrp*GRP_LIST_STRUCT_LEN);
	}
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonAddGrplist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_nGrp<32)//���32��
	{
		m_nGrp++;
		((CPCSWApp*)AfxGetApp())->SetGrplistCount(m_nGrp*GRP_LIST_STRUCT_LEN);//��Ч�б���д��
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(m_nGrp-1)*GRP_LIST_STRUCT_LEN],
			0x00,GRP_LIST_STRUCT_LEN);
		((CPCSWApp*)AfxGetApp())->SetGrplistInfo(GRP_NUM,m_nGrp,m_nGrp);//�б����
	}
	else
	{
		MessageBox("�Ѵﵽ����б�������Ҫ�������ɾ��","��ʾ");
	}
	m_nCurrentGrp = m_nGrp;
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int	nSel = m_listAllMember.GetSelCount();
	if (nSel == 0)
	{
		MessageBox("������߱߿���ѡ��Ҫ�����Ŀ","��ʾ");
		return;
	}
	//�ұ�������Ŀ
	int	nUsedCnt = m_listUsedMember.GetCount();
	if (nUsedCnt == 16)
	{
		MessageBox("��ǰ�б���������Ҫ������ӣ�����ɾ��","��ʾ");
		return;
	}
	if(nSel+nUsedCnt>16)
	{
		MessageBox("��ѡ��Ŀ�����б����Χ��������ѡ��","��ʾ");
		return;
	}
	if (nSel>0)
	{
		CArray<int,int>	arrSel;
		arrSel.SetSize(nSel);
		m_listAllMember.GetSelItems(nSel,arrSel.GetData());

		int i=0,nIndex,nContnum;
		int	nCnt = m_listUsedMember.GetCount();
		CString		str;
		string		s;
		TRY 
		{
			for(i=0;i<nSel;i++)
			{
				nIndex = arrSel.GetAt(i);//��ѡȡ�����б��е�������
// 				map_it = mapAllGrp.find(nIndex);//�˴�����
				m_listAllMember.GetText(nIndex,str);
// 				str.Format("%s",string(map_it->second).c_str());
				nIndex = m_listUsedMember.FindString(-1,str);
				if(nIndex==-1)//δ�����������б���
				{
					ConvertCString2String(str,s);
					map_it = find_if(mapAllGrp.begin(),mapAllGrp.end(),map_value_finder_string(s));
// 					if (map_it==mapUsedGrp.end())//δ�ҵ�
						// 				if(nIndex!=-1)//δ�ҵ�
					{
						((CPCSWApp*)AfxGetApp())->SetGrplistContnum(GRP_CONTACT_NUM,m_nCurrentGrp,i+1+nCnt,int(map_it->first));
						nContnum = GetIDorNum(GRP_MEMBER_NUM,m_nCurrentGrp);
						((CPCSWApp*)AfxGetApp())->SetGrplistInfo(GRP_MEMBER_NUM,m_nCurrentGrp,nContnum+1);
					}
				}
			}
		}
		CATCH (CMemoryException, e)
		{
			e->ReportError();
			delete	e;
		}
		END_CATCH	
	}
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CPropPageGrp::OnEnKillfocusEditName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString		str;
	m_editName.GetWindowText(str);
	CString		strGrp;//�����Ƿ����ظ�����
	int		nGrplistCount = *(WORD*)((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList;
	nGrplistCount/= GRP_LIST_STRUCT_LEN;
	int i;
	for (i=0;i<nGrplistCount;i++)
	{
		strGrp = ((CPCSWApp*)AfxGetApp())->GetGrplistName(i+1,NAME_BYTE_LEN);
		if (str.CompareNoCase(strGrp)!=0)//�ַ���һ��
		{
			MessageBox("�������Ѵ��ڣ�����������","��ʾ");
			m_editName.SetFocus();
			break;
		}
	}
	if (i <nGrplistCount)//ȫ����һ��,���ظ�����
	{
		((CPCSWApp*)AfxGetApp())->SetGrplistName(GRP_NAME,m_nCurrentGrp,str,NAME_BYTE_LEN);
	}
	
}
