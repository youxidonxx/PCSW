// COMSET.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "COMSET.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCOMSET dialog


CCOMSET::CCOMSET(CWnd* pParent /*=NULL*/)
	: CDialog(CCOMSET::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCOMSET)
	m_nComIndex = -1;
	//}}AFX_DATA_INIT
}


void CCOMSET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCOMSET)
	DDX_Control(pDX, IDC_COMBO_COMSET, m_cbPortSel);
	DDX_CBIndex(pDX, IDC_COMBO_COMSET, m_nComIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCOMSET, CDialog)
	//{{AFX_MSG_MAP(CCOMSET)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCOMSET message handlers

BOOL CCOMSET::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ScanPort();
// 	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
INT_PTR	CCOMSET::GetSerialPort(CStringArray &arrCom)
{
	arrCom.RemoveAll();
	HKEY	hkey;
	LONG32	lRes = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,_T("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
		NULL,KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS|KEY_READ,&hkey);
	if (lRes == ERROR_SUCCESS)
	{
		TCHAR	tchKey[MAX_PATH];
		TCHAR	tchValue[20];
		DWORD	dwIndex = 0;
		DWORD	dwType = REG_SZ;
		while(lRes == ERROR_SUCCESS)
		{
			DWORD	dwCnt = MAX_PATH;
			DWORD	dwVCount = 20;
			lRes = RegEnumValue(hkey,dwIndex++,tchKey,&dwCnt,NULL,
							&dwType,(LPBYTE)tchValue,&dwVCount);
			if (lRes == ERROR_SUCCESS)
			{
				if(dwVCount >0 && dwCnt >0)
					arrCom.Add(tchValue);
			}
		}
	}
	RegCloseKey(hkey);
 	return arrCom.GetSize();
}
void	CCOMSET::ScanPort()
{
	CStringArray	arrayComm;
	int i=0;
	for (;i<GetSerialPort(arrayComm);i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_COMSET))->AddString(arrayComm[i]);
	}
 	((CComboBox*)GetDlgItem(IDC_COMBO_COMSET))->SetCurSel(i-1);
}

void CCOMSET::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_nComIndex>=0)
	{
		int	selePort = m_cbPortSel.GetCurSel();
		CString	str,temp;
		m_cbPortSel.GetLBText(selePort,str);
			
		temp = str.Right(strlen(str)-3);
		m_nPortNum = atoi(temp);
			
		m_nComIndex = m_nPortNum;

	}
	CDialog::OnOK();
}