// PCSWDoc.h : interface of the CPCSWDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCSWDOC_H__23AE13A3_F1E6_4C9C_9720_B7E6F2603E88__INCLUDED_)
#define AFX_PCSWDOC_H__23AE13A3_F1E6_4C9C_9720_B7E6F2603E88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 

class CPCSWDoc : public CDocument
{
protected: // create from serialization only
	CPCSWDoc();
	DECLARE_DYNCREATE(CPCSWDoc)

// Attributes
public:
	void	UpdateData();//��������
	void	NotifyUpdateMsg();//֪ͨ������Ϣ
	void	SetDefault();	//���в�������Ĭ��ֵ
//��ʹ��newָ�룬��δ��ֵ֮ǰ��ָ��δ���壬��ʼ�������
	byte	pHead[64];

	byte	pRadioInfo[0x100];
	byte	pRadioSetting[0x100];//ʡ������(2)��TOT(4)������(1)������(1)��VOX(4)��(3)����ʾ��(6)����(3)��(6+3)��
								//����ʱ��(2)��ң�м���(3) Ȩ��(4) ==42
 	byte	pEmerSetting[0x100];//ϵͳ����(16)������+ģʽ(2)����ת�ŵ�(2)������(2)��ʱ��(2)��Ĭ�ϱ�����ϵ��(4)==28
	byte	pMenuSetting[256];
	byte	pKeySetting[256];

	byte	pZoneInfo[0x1000];
	byte	pChannelInfo[0x4000];
	byte	pScanInfo[0x1000];
	byte	pContact[0x2000];
	byte	pGrouplist[0x2000];
	byte	pShortText[0x2000];
// Operations
public:
	//������Ϣ����
	enum	RadioInfoAddr
	{
		Serialnum	= 0x00,
		Protype		= 0x10,
		Freqscope	= 0x18,
		Swver		= 0x1a,
		Dataver		= 0x1e,
		Appver		= 0x22
	};
	enum	RadioInfoByteNumbers
	{
		SerialnumBytes	= 16,
		ProtypeBytes	= 8,
		FreqscopeBytes	= 2,
		SwverBytes		= 4,
		DataBytes		= 4,
		AppverBytes		= 4
	};
	void	SetDefaultRadio(int nFlag,int nLen,const CString&	str);
	//���к�
	CString	GetSerialNumber();
	void	SetSerialNumber(CString	&str);
	//����
	CString	GetProtype();
	void	SetProtype(CString&	str);
	//���ݰ汾
	CString	GetDataVer();
	void	SetDataVer(CString&	str);
	//����汾
	CString	GetSWVer();
	void	SetSWVer(CString& str);
	//����汾
	CString	GetAppVer();
	void	SetAppVer(CString&	str);
	//Ƶ�ʷ�Χ
	int		GetFreqScope();
	void	SetFreqScope(int nRange);
public:
	//�˵���ͼ����
	int 	GetKeyFunc(int nIndex);
	void	SetKeyFunc(int nFlag,int nVal);


	//�˵����ܵ��ֽ���
	enum MenuByte
	{
		MenuByteLen = 1
	};
	//��ȡ���в˵�������Ϣ
	BOOL	GetMenuEnable(int nIndex);

	//ң�м�������˵�
	BOOL	GetMenuKill(int nIndex);
	BOOL	GetmenuActive(int nIndex);

	//����MENU�˵�������ȡֵ
	void	SetAllMenuValue(int nID, int val);
	void	SetMenuValue(int nID,int val);
public:
	//�Խ������ò���
	//��ȡ��ѡ���ֵ�ĺ���
	int 	GetSettingCheckValue(int nFlag);
	//ʡ�����--��ѡ��
	int*	GetPowerSaveScale(int nFlag,int nLen);
 	

	//����Ԥ�ز�ʱ��
	void	SetPreTxDelay(int nFlag);
	//���ö�ֵ��������
	void	SetSpinValues(int nOffset,int nFlag);
	//��ȡ����ID/��������
	CString	GetMSID(int nFlag);
	CString	GetAlarmID(int nFlag);
	//���ñ���ID��
	void	SetMSID(CString&	strID);
	//��������
	CString	GetAlarmName(int nFlag,int FlagLen);
	//��ȡ
	int	   GetSettingMultiValues(int nFlag,int nMaxValue);
public:
	////////////////////////�����ŵ�����//////////////////////////////////////////////////
	//��ȡ��ǰ�����е���Ч�ŵ���
	int	GetValidChannuumInZone(int nZoneNum,int nFlag);
	//��ȡ�ŵ��еĵ��ֽ���Чֵ
	int GetByteValuesInCh(int nFlag,int nZone,int nChannel);
	//�ɻ�ȡ�ŵ��������������
	CString	GetChannelName(int ByteLen,int nFlag,int nZone,int nChannel,int nStep1 = 736,int nStep2 = 46,bool	bCh = true);
	//��ȡƵ��
	CString	GetChannelFreq(int nFlag,int nZone,int nChannel);
	//��ȡ������������
	CString	GetVoiceEncryptCode(int nFlag,int nZone,int nChannel);
	//��ȡ�������
	
public:
	////////////////////////ɨ���б���//////////////////////////////////////////////////
	//��ȡ������Ч�б���
	int		GetTotalList();
	//��ȡʱ�䡪��ͣ��ʱ�䡢�ӳ�ʱ��
	int		GetScanTime(int nFlag,int nListnum);
	//��ȡ����
	CString	GetScanListName(int nFlag,int nLen,int nListnum);
	void	SetScanname(int nFlag,int nLen,int nListnum,const CString& str);
	//������Ϣ
	int		GetScanInfo(int nFlag,int nListnum);
	//ɨ���б��е��ŵ�/�����
	int	GetScanlistInfo(int nFlag,int nLen,int nListnum,int nChnum,bool bChOrZone = true);

 	void	SetCommonValue(int nFlag,int nVal,int nListnum,int nLen = 1);
	void	SetChFlag(int nFlag,int nVal,int nListnum,int nRound,bool	bCh = true);

public:
	///////////////////////���Ų�������///////////////////////////////////////////////////
	//��ȡ�Ƕ��������ֶ�ֵ
	int	GetSmsInfo(int nFlag,int nGroup);
	//��ȡ��������
	CString	GetSmsContent(int nFlag,int nLen,int nGroup);
	//���÷Ƕ��������ֶ�
	void	SetSmsInfo(int nFlag,int nGroup,int nVal);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCSWDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPCSWDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPCSWDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCSWDOC_H__23AE13A3_F1E6_4C9C_9720_B7E6F2603E88__INCLUDED_)
