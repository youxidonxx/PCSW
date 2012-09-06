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

	int nGrpID = GetIDorNum(GRP_NUM,m_nCurrentGrp);//列表序号
	int nGrpCnt = GetIDorNum(GRP_MEMBER_NUM,m_nCurrentGrp);//列表成员数
	CString		strName;
	strName = ((CPCSWApp*)AfxGetApp())->GetGrplistName(m_nCurrentGrp,NAME_BYTE_LEN);
	m_editName.SetWindowText(strName);
	SetStaticName();
	ListDataShow(nGrpID,nGrpCnt);
}
void	CPropPageGrp::SetStaticName()
{
	CString		str;
	str.Format("列表 %d/%d",m_nCurrentGrp,m_nGrp);
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
	for (;i<m_nTotalContact;i++)//以所有联系人个数为循环条件
	{	
		nContType = ((CPCSWApp*)AfxGetApp())->GetContInfo(CONTACT_TYPE,i+1);	
		if (nContType==2 || nContType==3)//组呼/全呼类型
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
		m_listUsedMember.AddString("无成员");
}
int	CPropPageGrp::GetIDorNum(int nFlag,int nGrp)
{
	int nRet = m_pGrp[0x00+2+nFlag+(nGrp-1)*34];
	return nRet;
}

void CPropPageGrp::OnBnClickedButtonNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurrentGrp<m_nGrp)
	{
		m_nCurrentGrp++;
	}
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_nCurrentGrp>1)
	{
		m_nCurrentGrp--;
	}
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCurrentGrp = 1;
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCurrentGrp = m_nGrp;
	LoadData();
}



void CPropPageGrp::OnBnClickedButtonDeleteGrplist()
{
	// TODO: 在此添加控件通知处理程序代码
	int nGrpnum =	GetIDorNum(GRP_NUM,m_nCurrentGrp);
	if (nGrpnum>0)
	{
		int nRest = m_nGrp - nGrpnum;
		int	n=0;
		//将该组呼列表内容清空
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(m_nCurrentGrp-1)*GRP_LIST_STRUCT_LEN],
				0x00,GRP_LIST_STRUCT_LEN);
		//将后面的循环往前搬移
		while (nRest>0)//除掉最后一个列表数据，其余搬移
		{
			//nRest 代表剩余组数，nGrpnum代表最初的组号+i(i<nrest)就可以循环覆盖前面数据
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_nGrp<32)//最大32组
	{
		m_nGrp++;
		((CPCSWApp*)AfxGetApp())->SetGrplistCount(m_nGrp*GRP_LIST_STRUCT_LEN);//有效列表数写入
		memset(&((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList[0x00+2+(m_nGrp-1)*GRP_LIST_STRUCT_LEN],
			0x00,GRP_LIST_STRUCT_LEN);
		((CPCSWApp*)AfxGetApp())->SetGrplistInfo(GRP_NUM,m_nGrp,m_nGrp);//列表序号
	}
	else
	{
		MessageBox("已达到最大列表数，若要添加请先删除","提示");
	}
	m_nCurrentGrp = m_nGrp;
	LoadData();
}

void CPropPageGrp::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	int	nSel = m_listAllMember.GetSelCount();
	if (nSel == 0)
	{
		MessageBox("请在左边边框中选择要添加项目","提示");
		return;
	}
	//右边已有数目
	int	nUsedCnt = m_listUsedMember.GetCount();
	if (nUsedCnt == 16)
	{
		MessageBox("当前列表已满，若要继续添加，请先删除","提示");
		return;
	}
	if(nSel+nUsedCnt>16)
	{
		MessageBox("所选项目超出列表最大范围，请重新选择","提示");
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
				nIndex = arrSel.GetAt(i);//所选取的在列表中的索引号
// 				map_it = mapAllGrp.find(nIndex);//此处错误
				m_listAllMember.GetText(nIndex,str);
// 				str.Format("%s",string(map_it->second).c_str());
				nIndex = m_listUsedMember.FindString(-1,str);
				if(nIndex==-1)//未包含在已有列表中
				{
					ConvertCString2String(str,s);
					map_it = find_if(mapAllGrp.begin(),mapAllGrp.end(),map_value_finder_string(s));
// 					if (map_it==mapUsedGrp.end())//未找到
						// 				if(nIndex!=-1)//未找到
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
	// TODO: 在此添加控件通知处理程序代码
}

void CPropPageGrp::OnEnKillfocusEditName()
{
	// TODO: 在此添加控件通知处理程序代码
	CString		str;
	m_editName.GetWindowText(str);
	CString		strGrp;//检验是否有重复名字
	int		nGrplistCount = *(WORD*)((CPCSWApp*)AfxGetApp())->m_CommInfo.pGroupList;
	nGrplistCount/= GRP_LIST_STRUCT_LEN;
	int i;
	for (i=0;i<nGrplistCount;i++)
	{
		strGrp = ((CPCSWApp*)AfxGetApp())->GetGrplistName(i+1,NAME_BYTE_LEN);
		if (str.CompareNoCase(strGrp)!=0)//字符串一样
		{
			MessageBox("该名称已存在，请重新输入","提示");
			m_editName.SetFocus();
			break;
		}
	}
	if (i <nGrplistCount)//全部不一样,无重复名称
	{
		((CPCSWApp*)AfxGetApp())->SetGrplistName(GRP_NAME,m_nCurrentGrp,str,NAME_BYTE_LEN);
	}
	
}
