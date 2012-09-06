// PCSWDoc.cpp : implementation of the CPCSWDoc class
//

#include "stdafx.h"
#include "PCSW.h"

#include "PCSWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCSWDoc
extern	CPCSWApp	theApp;
IMPLEMENT_DYNCREATE(CPCSWDoc, CDocument)

BEGIN_MESSAGE_MAP(CPCSWDoc, CDocument)
	//{{AFX_MSG_MAP(CPCSWDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCSWDoc construction/destruction

CPCSWDoc::CPCSWDoc()
{
	// TODO: add one-time construction code here
/*	pHead = new byte[64];
	pRadioInfo = new byte[0x100];
	pRadioSetting = new byte[0x100];
	pEmerSetting = new byte[0x4000];
	pMenuSetting = new byte[0x100];
	pKeySetting = new byte[0x100];//256
 
	pZoneInfo = new byte[0x4000];//16k
	pChannelInfo = new byte[0x8000];

	pScanInfo = new byte[0x4000];

	pContact = new byte[0x2000];

	pGrouplist = new byte[0x2000];

	pShortText = new byte[0x2000];
*/	ZeroMemory(pHead,sizeof(pHead));
	ZeroMemory(pRadioInfo,sizeof(pRadioInfo));
	ZeroMemory(pRadioSetting,sizeof(pRadioSetting));
	ZeroMemory(pEmerSetting,sizeof(pEmerSetting));
	ZeroMemory(pMenuSetting,sizeof(pMenuSetting));
	ZeroMemory(pKeySetting,sizeof(pKeySetting));
	ZeroMemory(pZoneInfo,sizeof(pZoneInfo));
	ZeroMemory(pChannelInfo,sizeof(pChannelInfo));
	ZeroMemory(pScanInfo,sizeof(pScanInfo));
	ZeroMemory(pContact,sizeof(pContact));
	ZeroMemory(pGrouplist,sizeof(pGrouplist));
	ZeroMemory(pShortText,sizeof(pShortText));

}

CPCSWDoc::~CPCSWDoc()
{
}

BOOL CPCSWDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPCSWDoc serialization

void CPCSWDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar.Write(pHead,sizeof(pHead));
		ar.Write(pRadioInfo,sizeof(pRadioInfo));
		ar.Write(pRadioSetting,sizeof(pRadioSetting));
		ar.Write(pEmerSetting,sizeof(pEmerSetting));
		ar.Write(pMenuSetting,sizeof(pMenuSetting));
		ar.Write(pKeySetting,sizeof(pKeySetting));
		ar.Write(pZoneInfo,sizeof(pZoneInfo));
		ar.Write(pChannelInfo,sizeof(pChannelInfo));
		ar.Write(pScanInfo,sizeof(pScanInfo));
		ar.Write(pContact,sizeof(pContact));
		ar.Write(pGrouplist,sizeof(pGrouplist));
		ar.Write(pShortText,sizeof(pShortText));
	}
	else
	{
		// TODO: add loading code here
		ar.Read(pHead,sizeof(pHead));
		ar.Read(pRadioInfo,sizeof(pRadioInfo));
		ar.Read(pRadioSetting,sizeof(pRadioSetting));
		ar.Read(pEmerSetting,sizeof(pEmerSetting));
		ar.Read(pMenuSetting,sizeof(pMenuSetting));
		ar.Read(pKeySetting,sizeof(pKeySetting));
		ar.Read(pZoneInfo,sizeof(pZoneInfo));
		ar.Read(pChannelInfo,sizeof(pChannelInfo));
		ar.Read(pScanInfo,sizeof(pScanInfo));
		ar.Read(pContact,sizeof(pContact));
		ar.Read(pGrouplist,sizeof(pGrouplist));
		ar.Read(pShortText,sizeof(pShortText));

		//为了把输入文件的数据与doctmp里面的doc数据对应上
		POSITION	pos;
		CPCSWDoc*	pDoc;
		CDocTemplate*	pTmp ;
		pTmp = (CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template.GetAt(0);//[i-1];
		pos = (pTmp)->GetFirstDocPosition();
		pDoc = (CPCSWDoc*)(((CDocTemplate*)((CPCSWApp*)AfxGetApp())->m_template.GetAt(0))->GetNextDoc(pos));
		if(pDoc!=NULL)
			memcpy(pDoc,(CPCSWDoc*)this,sizeof(CPCSWDoc));
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPCSWDoc diagnostics

#ifdef _DEBUG
void CPCSWDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPCSWDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCSWDoc commands
void	CPCSWDoc::NotifyUpdateMsg()
{
	POSITION	pos = GetFirstViewPosition();
	while(pos!=NULL)
	{
		CView*	pView = GetNextView(pos);
		pView->UpdateWindow();
	}
}
void	CPCSWDoc::UpdateData()
{
	
}
//以下信息均为只读性质，只有当频率范围更改后，其他信息均变更为默认值
CString	CPCSWDoc::GetSerialNumber()
{
	CString	str = _T("");
	if (memcmp(pRadioInfo+Serialnum,"\x00",1)!=0)
	{
		str.Format("%s",pRadioInfo+Serialnum);
	}
	if(str.GetLength()>SerialnumBytes)
		str = str.Left(SerialnumBytes);
	return str;
}
CString	CPCSWDoc::GetProtype()
{
	CString	str = _T("");
	if (memcmp(pRadioInfo+Protype,"\x00",1)!=0)
	{
		str.Format("%s",pRadioInfo+Protype);
	}
	if(str.GetLength()>ProtypeBytes)
		str = str.Left(ProtypeBytes);
 	return str;
} 
//一下三个内容获取方式不同
// 06 00 02 01  ==>1.2.0.6
CString	CPCSWDoc::GetDataVer()
{
	CString	str = _T("");
	byte	data[10];
	for(int i=0;i<DataBytes;i++)
		data[i] = pRadioInfo[Dataver+DataBytes-i-1];
 	str.Format("%d.%d.%d.%x",data[0],data[1],data[2],data[3]);
	return str;

}
CString	CPCSWDoc::GetSWVer()
{
	CString	str = _T("");
	byte	data[10];
	for(int i=0;i<SwverBytes;i++)
		data[i] = pRadioInfo[Swver+SwverBytes-i-1];
 	str.Format("%d.%d.%d.%x",data[0],data[1],data[2],data[3]);
	return str;
}
CString	CPCSWDoc::GetAppVer()
{
	CString	str = _T("");
	byte	data[10];
	for(int i=0;i<AppverBytes;i++)
		data[i] = pRadioInfo[Appver+AppverBytes-i-1];
	/*if (memcmp(pRadioInfo+Dataver,"\x00",1)!=0)
	{
		str.Format("%s",pRadioInfo+Dataver);
	}
	if(str.GetLength()>DataBytes)
		str = str.Left(DataBytes);
	*/
	str.Format("%d.%d.%d.%x",data[0],data[1],data[2],data[3]);
	return str;
}


void	CPCSWDoc::SetDefaultRadio(int nFlag,int nLen,const CString& str)
{
	if (nFlag == 0x10)
	{
		CString	tmp;
		if (tmp.IsEmpty())
		{
			memset(&pRadioInfo[0x00+nFlag],0x00,nLen);
		}
		else
		{
			tmp = str.Left(nLen);
			if(tmp.GetLength() == nLen)
				memcpy(&pRadioInfo[0x00+nFlag],LPCTSTR(tmp),tmp.GetLength());
			else
				memcpy(&pRadioInfo[0x00+nFlag],LPCTSTR(tmp),tmp.GetLength()+1);
		}
	}
	else{
		int len = str.GetLength();
		if(len == 0)
			return;
		else if(len>nLen*2)
			len = nLen*2;
		char ch;
		BYTE	data;
		for (int i = len-1;i>=0;i--)
		{
			ch = str.GetAt(i);
			if(ch >='0' && ch <= '9')
				data = ch-'0';
			else 
				break;
			if(i%2 == 0)
				pRadioInfo[0x00+nFlag+(len - 1 -i)/2] = (pRadioInfo[0x00+nFlag+(len-1-i)/2]&0x0f)|data<<4;
			else
				pRadioInfo[0x00+nFlag+(len - 1 -i)/2] = (pRadioInfo[0x00+nFlag+(len-1-i)/2]&0xf0)|data;
		}
	}
}
///////////////////////////MENU菜单开关///////////////////////////////////////////////
BOOL	CPCSWDoc::GetMenuEnable(int nIndex)
{
	byte	bMenuEnable = -1;
	bMenuEnable = pMenuSetting[0x00+nIndex];
	return bMenuEnable;
}
BOOL	CPCSWDoc::GetMenuKill(int nIndex)
{
	BOOL	bAllowKill = -1;
	bAllowKill = pRadioSetting[0x00+nIndex];
	return bAllowKill;
}
BOOL	CPCSWDoc::GetmenuActive(int nIndex)
{
	BOOL	bAllowKill = -1;
	bAllowKill = pRadioSetting[0x00+nIndex];
	return bAllowKill;
}
void	CPCSWDoc::SetAllMenuValue(int nID,int val)
{
	if (val !=0 || (val !=1))
	{
		return;
	}
	pMenuSetting[0x00+nID] = val;
}
int	CPCSWDoc::GetKeyFunc(int nIndex)
{
	int nRet = pKeySetting[0x00+nIndex];
	return nRet;
}
void	CPCSWDoc::SetKeyFunc(int nFlag,int nVal)
{
	pKeySetting[0x00+nFlag] = nVal;
}
//////////////////////////SETTING界面设置////////////////////////////////////////////////
int	CPCSWDoc::GetSettingCheckValue(int nFlag)
{
	int	nRet ;
 	nRet = pRadioSetting[0x00+nFlag];
 	return nRet;
}
//为1个字节以上字段准备
int*	CPCSWDoc::GetPowerSaveScale(int nFlag,int nLen)
{
	if(nLen>1)
		return NULL;
	int *nRet = new int[nLen];
	for (int i=0;i<nLen;i++)
	{
		nRet[i] = pRadioSetting[0x00+nFlag+i];
	}
	return nRet;
}
int CPCSWDoc::GetSettingMultiValues(int nFlag,int nMaxValue)
{
	if(nMaxValue <0)
		return -1;
	int nRet = pRadioSetting[0x00+nFlag];

	return nRet;
}

//发射预载波时间
void	CPCSWDoc::SetPreTxDelay(int nFlag)
{
	pRadioSetting[0x00+0x20] = nFlag;
}
void	CPCSWDoc::SetSpinValues(int nOffset,int nFlag)
{
	pRadioSetting[0x00+nOffset] = nFlag;
}
CString	CPCSWDoc::GetMSID(int nFlag)
{
 
 	char str[20];
	BYTE ch;
	int i;
	int nLength = 4*2-1;//此项由于从下标0开始,所以是本机ID的长度减去1
	int j=0;
	for(i=nLength;i>=0;i--)
	{
		if(i%2==0)
			ch = *(pRadioSetting+nFlag+i/2)&0x0F;	
		else
			ch = *(pRadioSetting+nFlag+i/2)>>4;
		if(ch<10)
			str[nLength-i-j]=ch+'0';
		else
			j++;
	}
	str[nLength]=0;   //由于只显示7位数字,估计str[7]=0表示结束符
	return CString(str);
}
CString	CPCSWDoc::GetAlarmID(int nFlag)
{
	char str[20];
	BYTE ch;
	int i;
	int nLength = 4*2-1;//此项由于从下标0开始,所以是本机ID的长度减去1
	int j=0;
	for(i=nLength;i>=0;i--)
	{
		if(i%2==0)
			ch = *(pEmerSetting+nFlag+i/2)&0x0F;	
		else
			ch = *(pEmerSetting+nFlag+i/2)>>4;
		if(ch<10)
			str[nLength-i-j]=ch+'0';
		else
			j++;
	}
	str[nLength]=0;   //由于只显示7位数字,估计str[7]=0表示结束符
	return CString(str);
}


CString	CPCSWDoc::GetAlarmName(int nFlag,int FlagLen)
{
	BYTE *ptr;
	BYTE szTemp[32];
	ptr = pEmerSetting+nFlag;
	memcpy(szTemp,ptr,FlagLen);
	szTemp[FlagLen] = szTemp[FlagLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(FlagLen),FlagLen,NULL,NULL);
	str.ReleaseBuffer();
	return str;

}
/************************************************************************/
/*      区域信道设置           
GetValidChannuumInZone:: 获取区域有效信道数
GetByteValuesInCh::	获取信道中1字节数值
GetChannelName::	获取指定信道别名与区域别名                                         */
/************************************************************************/
////////////////////////////区域信道设置//////////////////////////////////////////////
int CPCSWDoc::GetValidChannuumInZone(int nZoneNum,int nFlag)
{
		int nRet = pZoneInfo[0x00 + nFlag +(nZoneNum-1)*18];
		return nRet;
}
int CPCSWDoc::GetByteValuesInCh(int nFlag,int nZone,int nChannel)
{
	int nRet = pChannelInfo[0x00+nFlag+(nZone-1)*736 + (nChannel-1)*46];
	return nRet;
}
//默认获取信道别名
CString	CPCSWDoc::GetChannelName(int ByteLen,int nFlag,int nZone,//所要获取的区域号
								 int nChannel,					//所要获取的信道号
								 int nStep1 /*= 736*/,int nStep2 /*= 46*/,bool	bCh /* = true*/)
{
	BYTE *ptr;
	BYTE* szTemp = new BYTE[ByteLen*2];
	if(bCh)
		ptr = pChannelInfo+nFlag+(nZone-1)*nStep1+(nChannel-1)*nStep2;
	else
		ptr = pZoneInfo+nFlag+(nZone-1)*nStep1+(nChannel-1)*nStep2;
	memcpy(szTemp,ptr,ByteLen);
	szTemp[ByteLen] = szTemp[ByteLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(ByteLen),ByteLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTemp;
	return str;

}
CString	CPCSWDoc::GetChannelFreq(int nFlag,int nZone,int nChannel)
{
	BYTE*	ptr;
	ptr = &pChannelInfo[0x00+nFlag+(nZone-1)*736+(nChannel-1)*46];
	CString	str;
	str.Format("%02x%02x%02x%02x",*(ptr+3),*(ptr+2),*(ptr+1),*ptr);
	long	int	nFreq;
	sscanf_s(str,"%x",&nFreq);
	str.Format("%3d.%6d",nFreq/1000000,nFreq%1000000);
	return str;
}
CString	CPCSWDoc::GetVoiceEncryptCode(int nFlag,int nZone,int nChannel)
{
	char str[20];
	BYTE ch;
	int i;
	int j=0;
	for(i=7;i>=0;i--)
	{
		if(i%2==0)
			ch = *(pChannelInfo+nFlag+(nZone-1)*736+(nChannel-1)*46+i/2)&0x0F;		
		else
			ch = *(pChannelInfo+nFlag+(nZone-1)*736+(nChannel-1)*46+i/2)>>4;			
		if(ch<10)
			str[7-i-j]=ch+'0';
		else
			j++;
	}
	str[8-j]=0;
	return(CString(str));
}
/************************************************************************/
/*扫描列表部分 
pScanInfo的前2位是有效列表数，后面的才是各个
GetTotalList:获取所有有效列表数，该字段开头
GetScanTime:获取每个列表的对应时间参数
GetScanListName:获取列表别名

                                                                     */
/************************************************************************/
int CPCSWDoc::GetTotalList()
{
	int nRet = (WORD)pScanInfo[0x00];
	if( nRet<1 || nRet>32)
		nRet =1;
	return nRet;
}
int CPCSWDoc::GetScanTime(int nFlag,int nListnum)
{
	int nRet = (pScanInfo[0x00+2+nFlag+(nListnum-1)*60]);
	if((nRet < 1) || (nRet > 20))
		nRet = 10;
	return (nRet*5);
}
int CPCSWDoc::GetScanInfo(int nFlag,int nListnum)
{
	int nRet = pScanInfo[0x00+2+nFlag+(nListnum-1)*60];
	return nRet;
}
CString	CPCSWDoc::GetScanListName(int nFlag,int nLen,int nListnum)
{
	BYTE*	ptr;
	BYTE	*szTmp = new BYTE	[nLen*2];
	ptr = &pScanInfo[0x00+2+nFlag+(nListnum-1)*60];
	memcpy(szTmp,ptr,nLen);
	szTmp[nLen] = szTmp[nLen+1] = 0x00;
	CString	str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTmp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTmp;
	return str;
}
int	CPCSWDoc::GetScanlistInfo(int nFlag,int nLen,int nListnum,int nChnum,bool bChOrZone /*= true*/)
{
	int nCh = pScanInfo[0x00+2+nFlag+(nListnum-1)*60+(nChnum-1)*2+1];
	int nZone = pScanInfo[0x00+2+nFlag+(nListnum-1)*60+(nChnum-1)*2];
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
void	CPCSWDoc::SetCommonValue(int nFlag,int nVal,int nListnum,int nLen /* = 1 */)
{
	pScanInfo[0x00+2+nFlag+(nListnum-1)*60] = nVal;
}
//主要用于设置扫描列表中的包含区域信道号
void	CPCSWDoc::SetChFlag(int nFlag,int nVal,int nListnum,int nRound,bool bCh /* = true */)
{
	if(bCh)
		pScanInfo[0x00+2+nFlag+(nListnum-1)*60+(nRound-1)*2+1] = nVal;
	else
		pScanInfo[0x00+2+nFlag+(nListnum-1)*60+(nRound-1)*2]= nVal;
}
void	CPCSWDoc::SetScanname(int nFlag,int nLen,int nListnum,const CString& str)
{
	BYTE *ptr;
	BYTE *szTemp  = new BYTE [nLen*2];
	memset(szTemp,0x00,nLen*2);
	ptr = &pScanInfo[0x00+2+nFlag+(nListnum-1)*60];
	memset(ptr,0x00,nLen);
	int nLength = str.GetLength();
	if(!str.IsEmpty())
		MultiByteToWideChar(CP_ACP,0,str,nLength,(LPWSTR)szTemp,nLen);
	memcpy(ptr,szTemp,nLen);
	delete	szTemp;

}
///////////////////////////////短信部分读取///////////////////////////////////////////
int		CPCSWDoc::GetSmsInfo(int nFlag,int nGroup)//若是0，则说明是要获取有效快捷文本总数
{
	int	nRet;
	if (nGroup == 0)
	{
		nRet = pShortText[0x00+nFlag];
		return nRet;
	}
	else
	{
		nRet = pShortText[0x00+2+nFlag+(nGroup-1)*162];
		return nRet;
	}
}

CString	CPCSWDoc::GetSmsContent(int nFlag,int nLen,int nGroup)
{
	BYTE *ptr;
	BYTE *szTemp = new BYTE [nLen*2];
	ptr = &pShortText[0x00+2+nFlag+(nGroup-1)*162];
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	delete	szTemp;
	return str;
}

void	CPCSWDoc::SetSmsInfo(int nFlag,int nGroup,int nVal)
{
	if (nGroup == 0)
	{
		pShortText[0x00+nFlag] = nVal;
	}
	else
	{
		pShortText[0x00+2+nFlag+(nGroup-1)*162] = nVal;
	}
	return ;
}
//////////////////////////////////////////////////////////////////////////
void CPCSWDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
/*
	int i;
	int n = theApp.m_template.GetUpperBound();
	for(i=1;i<=theApp.m_template.GetUpperBound();i++)
	{
		CMultiDocTemplate* pTemplate=(CMultiDocTemplate*)(theApp.m_template[i]);
		delete[] pTemplate;
	}
//	theApp.m_template.RemoveAll();
//	theApp.m_Frame.RemoveAll();
*/
	
	CDocument::OnCloseDocument();
}
