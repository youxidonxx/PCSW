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
	void	UpdateData();//更新数据
	void	NotifyUpdateMsg();//通知更新消息
	void	SetDefault();	//所有参数设置默认值
//若使用new指针，当未赋值之前，指针未定义，初始化会出错
	byte	pHead[64];

	byte	pRadioInfo[0x100];
	byte	pRadioSetting[0x100];//省电设置(2)、TOT(4)、耳语(1)、静噪(1)、VOX(4)、(3)、提示音(6)、灯(3)、(6+3)、
								//保持时间(2)、遥毙激活(3) 权限(4) ==42
 	byte	pEmerSetting[0x100];//系统别名(16)、类型+模式(2)、跳转信道(2)、次数(2)、时间(2)、默认报警联系人(4)==28
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
	//基本信息部分
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
	//序列号
	CString	GetSerialNumber();
	void	SetSerialNumber(CString	&str);
	//机型
	CString	GetProtype();
	void	SetProtype(CString&	str);
	//数据版本
	CString	GetDataVer();
	void	SetDataVer(CString&	str);
	//程序版本
	CString	GetSWVer();
	void	SetSWVer(CString& str);
	//界面版本
	CString	GetAppVer();
	void	SetAppVer(CString&	str);
	//频率范围
	int		GetFreqScope();
	void	SetFreqScope(int nRange);
public:
	//菜单视图部分
	int 	GetKeyFunc(int nIndex);
	void	SetKeyFunc(int nFlag,int nVal);


	//菜单功能的字节数
	enum MenuByte
	{
		MenuByteLen = 1
	};
	//获取所有菜单开关信息
	BOOL	GetMenuEnable(int nIndex);

	//遥毙激活允许菜单
	BOOL	GetMenuKill(int nIndex);
	BOOL	GetmenuActive(int nIndex);

	//设置MENU菜单的所有取值
	void	SetAllMenuValue(int nID, int val);
	void	SetMenuValue(int nID,int val);
public:
	//对讲机设置部分
	//获取复选框的值的函数
	int 	GetSettingCheckValue(int nFlag);
	//省电比例--复选框
	int*	GetPowerSaveScale(int nFlag,int nLen);
 	

	//发射预载波时间
	void	SetPreTxDelay(int nFlag);
	//设置多值类型数据
	void	SetSpinValues(int nOffset,int nFlag);
	//获取本机ID/报警号码
	CString	GetMSID(int nFlag);
	CString	GetAlarmID(int nFlag);
	//设置本机ID号
	void	SetMSID(CString&	strID);
	//报警名称
	CString	GetAlarmName(int nFlag,int FlagLen);
	//获取
	int	   GetSettingMultiValues(int nFlag,int nMaxValue);
public:
	////////////////////////区域信道部分//////////////////////////////////////////////////
	//获取当前区域中的有效信道数
	int	GetValidChannuumInZone(int nZoneNum,int nFlag);
	//获取信道中的单字节有效值
	int GetByteValuesInCh(int nFlag,int nZone,int nChannel);
	//可获取信道别名与区域别名
	CString	GetChannelName(int ByteLen,int nFlag,int nZone,int nChannel,int nStep1 = 736,int nStep2 = 46,bool	bCh = true);
	//获取频点
	CString	GetChannelFreq(int nFlag,int nZone,int nChannel);
	//获取语音加密密码
	CString	GetVoiceEncryptCode(int nFlag,int nZone,int nChannel);
	//获取区域别名
	
public:
	////////////////////////扫描列表部分//////////////////////////////////////////////////
	//获取所有有效列表数
	int		GetTotalList();
	//获取时间——停留时间、延迟时间
	int		GetScanTime(int nFlag,int nListnum);
	//获取别名
	CString	GetScanListName(int nFlag,int nLen,int nListnum);
	void	SetScanname(int nFlag,int nLen,int nListnum,const CString& str);
	//其他信息
	int		GetScanInfo(int nFlag,int nListnum);
	//扫描列表中的信道/区域号
	int	GetScanlistInfo(int nFlag,int nLen,int nListnum,int nChnum,bool bChOrZone = true);

 	void	SetCommonValue(int nFlag,int nVal,int nListnum,int nLen = 1);
	void	SetChFlag(int nFlag,int nVal,int nListnum,int nRound,bool	bCh = true);

public:
	///////////////////////短信部分内容///////////////////////////////////////////////////
	//获取非短信内容字段值
	int	GetSmsInfo(int nFlag,int nGroup);
	//获取短信内容
	CString	GetSmsContent(int nFlag,int nLen,int nGroup);
	//设置非短信内容字段
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
