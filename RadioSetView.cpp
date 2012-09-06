// RadioSetView.cpp : implementation file
//

#include "stdafx.h"
#include "PCSW.h"
#include "RadioSetView.h"
#include "PCSWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadioSetView
static	CString	strIdleDisp[] = {"信道号",
					"信道名称",
					"信道接收频率",
					"区域号",
					"区域别名",
					"信道号和区域号",
					"信道名称和区域号",
					"信道接收频率和区域号",
					"信道号和区域别名",
					"信道名称和区域别名",
					"信道接收频率和区域别名"};
static	CString	strLevel[] = {"0","1","2","3","4","5","6","7","8","9"};
static	CString	strToneEn[] = {"不静音","静音"};
static	CString	strToneOption[] = {"禁止","数字信道允许","模拟信道允许","所有信道允许"};
static	CString	strBKLight[] = {"关闭","常开","定时"};
static	CString	strOpenClose[] = {"关闭","打开"};
static	CString	strEnableDisable[] = {"不支持","支持"};
static	CString	strEmerType[] = {	"无",		"仅鸣笛",		"常规",		"秘密不接收语音",		"秘密并接收语音" };
static	CString	strEmerMode[] = {	"紧急警报","紧急警报+紧急呼叫","紧急警报+背景音发送"	};
static	CString	strPowerLvl[] = {"无","1:1","1:2","1:4"};
	
	IMPLEMENT_DYNCREATE(CRadioSetView, CFormView)

CRadioSetView::CRadioSetView()
	: CFormView(CRadioSetView::IDD)
{
	//{{AFX_DATA_INIT(CRadioSetView)
	m_bChannelLock = FALSE;
	m_bDateShow = FALSE;
	m_bPowerSaveLvl = FALSE;
	m_bVoxForbidWhileRx = FALSE;
	m_bVoxCancel = FALSE;
	m_bWhisper = FALSE;
	m_bDecodeKillActive = FALSE;
	//}}AFX_DATA_INIT

	CheckIDArray.nCtrlID[0] = IDC_CHECK_POWERSAVELVL;            CheckIDArray.nOffset[0]  = SETTING_POWERSAVE_EN    ; 
	CheckIDArray.nCtrlID[1] = IDC_CHECK_WHISPER_EN;              CheckIDArray.nOffset[1]  =  SETTING_WHISPER_EN   ; 
	CheckIDArray.nCtrlID[2] = IDC_CHECK_VOX_CANCEL;              CheckIDArray.nOffset[2]  =  SETTING_VOX_CANCEL   ; 
	CheckIDArray.nCtrlID[3] = IDC_CHECK_VOX_FORBID;              CheckIDArray.nOffset[3]  =  SETTING_VOX_FORBID   ; 
	CheckIDArray.nCtrlID[4] = IDC_CHECK_CH_LOCK;                 CheckIDArray.nOffset[4]  =   SETTING_CHANNELLOCK  ; 
	CheckIDArray.nCtrlID[5] = IDC_CHECK_VIBRATE_NOTE;            CheckIDArray.nOffset[5]  =  SETTING_VIBRATE_EN   ; 
	CheckIDArray.nCtrlID[6] = IDC_CHECK_SMS_TONE;                CheckIDArray.nOffset[6]  =   SETTING_SMS_TONE  ; 
	CheckIDArray.nCtrlID[7] = IDC_CHECK_LOWPOWER_TONE ;          CheckIDArray.nOffset[7]  =  SETTING_LOWBATTORY_TONE   ; 
	CheckIDArray.nCtrlID[8] = IDC_CHECK_KEY_TONE;                CheckIDArray.nOffset[8]  =  SETTING_KEY_TONE   ; 
	CheckIDArray.nCtrlID[9] = IDC_CHECK_LIGHT_NOTE;              CheckIDArray.nOffset[9]  =  SETTING_LIGHT_NOTE   ; 
	CheckIDArray.nCtrlID[10] = IDC_CHECK_DATE_SHOW;              CheckIDArray.nOffset[10] =  SETTING_DATE_EN   ; 
	CheckIDArray.nCtrlID[11] = IDC_CHECK_WILDCARD;               CheckIDArray.nOffset[11] =   SETTING_WILDCARD_EN  ; 
	CheckIDArray.nCtrlID[12] = IDC_CHECK_MANUAL_DIAL;            CheckIDArray.nOffset[12] =   SETTING_MANUALDIAL_EN  ; 
	CheckIDArray.nCtrlID[13] = IDC_CHECK_DECODE_KILLANDACTIVE;   CheckIDArray.nOffset[13] =   SETTING_DECODE_EN  ;
	CheckIDArray.nCtrlID[14] = IDC_CHECK_ALLOW_CALLALL;          CheckIDArray.nOffset[14] =   SETTING_CALLALL_EN  ;
	CheckIDArray.nCtrlID[15] = IDC_CHECK_ALLOW_GROUPCALL;        CheckIDArray.nOffset[15] =   SETTING_CALLGRP_EN  ;
	CheckIDArray.nCtrlID[16] = IDC_CHECK_ALLOW_ADD_CONTACT;      CheckIDArray.nOffset[16] =  SETTING_CREATE_CONTENT_EN   ;
	CheckIDArray.nCtrlID[17] = IDC_CHECK_ALLOW_WRITE_SMS;        CheckIDArray.nOffset[17] =  SETTING_EDIT_SMS_EN   ;
 	
	
	CheckIDArray.nCtrlID[18] = IDC_COMBO_POWER_LVL;		CheckIDArray.nOffset[18]  = SETTING_POWERSAVE_SCALE    ; 
	CheckIDArray.nCtrlID[19] = IDC_COMBO_NOISE_LVL;		CheckIDArray.nOffset[19]  = SETTING_NOISE_SCALE    ; 
	CheckIDArray.nCtrlID[20] = IDC_COMBO_VOX_LVL;		CheckIDArray.nOffset[20]  = SETTING_VOX_LEVEL    ; 
	CheckIDArray.nCtrlID[21] = IDC_COMBO_TONE;			CheckIDArray.nOffset[21]  = SETTING_TONE_EN    ; 
	CheckIDArray.nCtrlID[22] = IDC_COMBO_OUT_TONE;		CheckIDArray.nOffset[22]  = SETTING_CALLOUT_TONE    ; 
	CheckIDArray.nCtrlID[23] = IDC_COMBO_IN_TONE;		CheckIDArray.nOffset[23]  = SETTING_CALLIN_TONE    ; 
	CheckIDArray.nCtrlID[24] = IDC_COMBO_BGLIGHT;		CheckIDArray.nOffset[24]  = SETTING_BACKLIGHT_NOTE    ; 
	CheckIDArray.nCtrlID[25] = IDC_COMBO_MAINFRAME_STYLE;CheckIDArray.nOffset[25]  = SETTING_IDLE_DISPLAY    ; 
	CheckIDArray.nCtrlID[26] = IDC_COMBO_ALARM_TYPE;	CheckIDArray.nOffset[26]  = SETTING_ALARM_TYPE    ; 
	CheckIDArray.nCtrlID[27] = IDC_COMBO_ALARM_MODE;	CheckIDArray.nOffset[27]  = SETTING_ALARM_MODE    ; 
	CheckIDArray.nCtrlID[28] = IDC_COMBO_ALARM_CHANNEL;	CheckIDArray.nOffset[28]  = SETTING_ALARM_CHANNEL    ; 

	int n=0;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_TCOMM		;		SpinIDArray.nOffset[n] = SETTING_TCOMM_TIME		;	
	SpinIDArray.nOverleap[n] = 60;SpinIDArray.nStep[n] = 10;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_TPRETOT		;		SpinIDArray.nOffset[n] = SETTING_TPRETOT_TIME		;
	SpinIDArray.nOverleap[n] = 60;SpinIDArray.nStep[n] = 1;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_TREKEY		;		SpinIDArray.nOffset[n] = SETTING_TREKEY_TIME		;
	SpinIDArray.nOverleap[n] = 60;SpinIDArray.nStep[n] = 1;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_TRESET		;		SpinIDArray.nOffset[n] = SETTING_TRESET_TIME		;
	SpinIDArray.nOverleap[n] = 30;SpinIDArray.nStep[n] = 1;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_VOX_DELAY		;		SpinIDArray.nOffset[n] = SETTING_VOX_DELAY_TIME		;
	SpinIDArray.nOverleap[n] = 30;SpinIDArray.nStep[n] = 100;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_KEYLOCK_DELAY		;		SpinIDArray.nOffset[n] = SETTING_KEYLOCK		;
	SpinIDArray.nOverleap[n] = 6; SpinIDArray.nStep[n] = 5; n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_BGLIGHT_DELAY		;		SpinIDArray.nOffset[n] = SETTING_BACKLIGHT_DELAYTIME		;
	SpinIDArray.nOverleap[n] = 60;SpinIDArray.nStep[n] = 1;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_PRE_TX_DELAY		;		SpinIDArray.nOffset[n] = SETTING_PRETXDELAY_TIME		;	
	SpinIDArray.nOverleap[n] =250; SpinIDArray.nStep[n] = 10; n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_GROUPCALL_HOLD_TIME		;		SpinIDArray.nOffset[n] = SETTING_GRPHOLD_TIME		;
	SpinIDArray.nOverleap[n] = 20; SpinIDArray.nStep[n] = 250*2; n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_SIGNALCALL_HOLD_TIME		;		SpinIDArray.nOffset[n] = SETTING_PEERHOLD_TIME		;
	SpinIDArray.nOverleap[n] = 20; SpinIDArray.nStep[n] = 250*2; n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_ALARM_CALL_TIME		;		SpinIDArray.nOffset[n] = SETTING_ALARM_TIME		;
	SpinIDArray.nOverleap[n] = 255;SpinIDArray.nStep[n] = 1;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_ALAMR_TIME		;		SpinIDArray.nOffset[n] = SETTING_ALARM_CALL_TIME		;
	SpinIDArray.nOverleap[n] = 255; SpinIDArray.nStep[n] = 1; n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_MIC_HOLD_TIME		;		SpinIDArray.nOffset[n] = SETTING_ALARM_MICHOLD_TIME		;
	SpinIDArray.nOverleap[n] = 12;SpinIDArray.nStep[n] = 10;  n++;
	SpinIDArray.nCtrlID[n] = IDC_EDIT_RCV_HOLE_TIME		;		SpinIDArray.nOffset[n] = SETTING_ALARM_RCVHOLD_TIME		;
	SpinIDArray.nOverleap[n] = 12; SpinIDArray.nStep[n] = 10; n++;
	 
//	CheckIDArray.nCtrlID[29] = IDC_COMBO_ALARM_TYPE;
/* */
}

CRadioSetView::~CRadioSetView()
{
}

void CRadioSetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadioSetView)
	DDX_Control(pDX, IDC_EDIT_ALARM_NAME, m_editALARMName);
	DDX_Control(pDX, IDC_EDIT_ALARM_EMEID, m_editALARMID);
	DDX_Control(pDX, IDC_EDIT_ALARM_CALL_TIME, m_editAlarmCallTime);
	DDX_Control(pDX, IDC_EDIT_ALAMR_TIME, m_editAlarmTime);
	DDX_Control(pDX, IDC_EDIT_BGLIGHT_DELAY, m_editBKLightDelay);
	DDX_Control(pDX, IDC_EDIT_VOX_DELAY, m_editVoxTime);
	DDX_Control(pDX, IDC_EDIT_TRESET, m_Treset);
	DDX_Control(pDX, IDC_EDIT_TREKEY, m_Trekey);
	DDX_Control(pDX, IDC_EDIT_TPRETOT, m_editTpretot);
	DDX_Control(pDX, IDC_EDIT_TCOMM, m_editTcomm);
	DDX_Control(pDX, IDC_EDIT_SIGNALCALL_HOLD_TIME, m_editPeerHoldTime);
	DDX_Control(pDX, IDC_EDIT_RCV_HOLE_TIME, m_editRcvHoldTime);
	DDX_Control(pDX, IDC_EDIT_MIC_HOLD_TIME, m_editMicHoldTime);
	DDX_Control(pDX, IDC_EDIT_KEYLOCK_DELAY, m_editKeylockDelay);
	DDX_Control(pDX, IDC_EDIT_GROUPCALL_HOLD_TIME, m_editGrpHoldTime);
	DDX_Control(pDX, IDC_EDIT_PRE_TX_DELAY, m_editPreTxDelay);
	DDX_Control(pDX, IDC_COMBO_VOX_LVL, m_cbVoxLvl);
	DDX_Control(pDX, IDC_COMBO_TONE, m_cbTone);
	DDX_Control(pDX, IDC_COMBO_POWER_LVL, m_cbPowerSaveLvl);
	DDX_Control(pDX, IDC_COMBO_NOISE_LVL, m_cbNoiseLvl);
	DDX_Control(pDX, IDC_COMBO_OUT_TONE, m_cbCallOutTone);
	DDX_Control(pDX, IDC_COMBO_IN_TONE, m_cbCallInTone);
	DDX_Control(pDX, IDC_COMBO_BGLIGHT, m_cbBGLight);
	DDX_Control(pDX, IDC_COMBO_ALARM_CHANNEL, m_cbAlarmCh);
	DDX_Control(pDX, IDC_COMBO_ALARM_MODE, m_cbAlarmMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_TYPE, m_cbAlarmType);
	DDX_Control(pDX, IDC_COMBO_MAINFRAME_STYLE, m_cbIdleDisp);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Check(pDX, IDC_CHECK_CH_LOCK, m_bChannelLock);
	DDX_Check(pDX, IDC_CHECK_DATE_SHOW, m_bDateShow);
	DDX_Check(pDX, IDC_CHECK_POWERSAVELVL, m_bPowerSaveLvl);
	DDX_Check(pDX, IDC_CHECK_VOX_FORBID, m_bVoxForbidWhileRx);
	DDX_Check(pDX, IDC_CHECK_VOX_CANCEL, m_bVoxCancel);
	DDX_Check(pDX, IDC_CHECK_WHISPER_EN, m_bWhisper);
	DDX_Check(pDX, IDC_CHECK_WILDCARD, m_bDecodeKillActive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadioSetView, CFormView)
	//{{AFX_MSG_MAP(CRadioSetView)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRE_TX_DELAY, OnDeltaposSpinPreTxDelay)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GROUPCALL_HOLD_TIME, OnDeltaposSpinGroupcallHoldTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGNALCALL_HOLD_TIME, OnDeltaposSpinSignalcallHoldTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_KEYLOCK_DELAY, OnDeltaposSpinKeylockDelay)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VOX_DELAY, OnDeltaposSpinVoxDelay)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BGLIGHT_DELAY, OnDeltaposSpinBglightDelay)
	ON_CBN_SELCHANGE(IDC_COMBO_TONE, OnSelchangeComboTone)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_MODE, OnSelchangeComboAlarmMode)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_TYPE, OnSelchangeComboAlarmType)
	ON_CBN_SELCHANGE(IDC_COMBO_MAINFRAME_STYLE, OnSelchangeComboMainStyle)
	ON_CBN_SELCHANGE(IDC_COMBO_BGLIGHT, OnSelchangeComboBkLight)
	ON_CBN_SELCHANGE(IDC_COMBO_POWER_LVL, OnSelchangeComboPowerLvl)
	ON_BN_CLICKED(IDC_CHECK_POWERSAVELVL, OnCheckPowerLvl)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(CBN_SELCHANGE,IDC_COMBO_TOT_1,IDC_COMBO_TOT_4,OnTotSelChange)
	ON_CONTROL_RANGE(CBN_SELCHANGE,IDC_COMBO_EMER_1,IDC_COMBO_EMER_4,OnEmerSelChange)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_CHANNEL, &CRadioSetView::OnCbnSelchangeComboAlarmChannel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadioSetView diagnostics

#ifdef _DEBUG
void CRadioSetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRadioSetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRadioSetView message handlers
void	CRadioSetView::LoadData()
{
	LoadComboString();
	CString str  = GetIDStr(1,SETTING_MSID);//((CPCSWDoc*)GetDocument())->GetMSID(SETTING_MSID);
	m_editID.SetWindowText(str);
	str.Empty();
	str = GetIDStr(0,SETTING_ALARM_EMEID);//(CPCSWDoc*)GetDocument())->GetAlarmID(SETTING_ALARM_EMEID);
	m_editALARMID.SetWindowText(str);
	str.Empty();
	str = GetAlarmName(SETTING_ALARM_NAME,SETTING_DBDBDWORD_LEN);
		//((CPCSWDoc*)GetDocument())->GetAlarmName(SETTING_ALARM_NAME,SETTING_DBDBDWORD_LEN);
	m_editALARMName.SetWindowText(str);
	str.Empty();
	int num = sizeof(CheckIDArray);
	int nRet=-1;
	CString	strInput;
	//对于单选类型
	int i=0;
	for (;i<18;i++)
	{
		nRet = GetSettingValue(CheckIDArray.nOffset[i]);
		//(CPCSWDoc*)GetDocument())->GetSettingCheckValue(CheckIDArray.nOffset[i]);
		if(nRet!=0)
			nRet = 1;
		((CButton*)GetDlgItem(CheckIDArray.nCtrlID[i]))->SetCheck(nRet);
	}
	for(i=18;i<26;i++)
	{	
		nRet = GetSettingValue(CheckIDArray.nOffset[i]);
			//((CPCSWDoc*)GetDocument())->GetSettingCheckValue(CheckIDArray.nOffset[i]);
		if(CheckIDArray.nCtrlID[i] == IDC_COMBO_MAINFRAME_STYLE)
			nRet--;
 		((CComboBox*)GetDlgItem(CheckIDArray.nCtrlID[i]))->SetCurSel(nRet);
	}
	for (i=26;i<28;i++)
	{
		nRet = GetEmerSettingValues(CheckIDArray.nOffset[i]);
		((CComboBox*)GetDlgItem(CheckIDArray.nCtrlID[i]))->SetCurSel(nRet);
	}
	if (i == 28)//报警跳转信道
	{
		int nCh = GetEmerSettingValues(CheckIDArray.nOffset[i]);
		int	nZone = GetEmerSettingValues(CheckIDArray.nOffset[i]+1);
		if (nCh == 0xff)//当前信道
		{
			((CComboBox*)GetDlgItem(CheckIDArray.nCtrlID[i]))->SetCurSel(0);
		}
		else if(nCh <=16 && nZone <=16)
		{
			DWORD nInfo = (WORD)nCh&0x00ff |((WORD)(nZone<<8)&0xff00);
			it = find_if(mapChannel.begin(),mapChannel.end(),map_value_finder(nInfo));
			if (it!=mapChannel.end())
			{
				int nSel = (int)it->first;
				((CComboBox*)GetDlgItem(CheckIDArray.nCtrlID[i]))->SetCurSel(nSel);
			}
		}
	}
	for (i=0;i<SPINEDIT_SUM_SETTING;i++)
	{
		nRet = GetSettingValue(SpinIDArray.nOffset[i]);
			//((CPCSWDoc*)GetDocument())->GetSettingCheckValue(SpinIDArray.nOffset[i]);
		if (nRet > SpinIDArray.nOverleap[i]||nRet <1)//若是大于规定的最大值
		{
			switch(SpinIDArray.nCtrlID[i])
			{
			case IDC_EDIT_TCOMM://TOT超时 0：无限制 1-60，步进10秒
				{
					if(nRet == 0)
					{
						strInput ="无限制";
						m_editTcomm.SetSpecialValue(0,strInput);
					}
					else
						nRet = 60;
					m_editTcomm.SetInteger(nRet);
				}
				break;
			case IDC_EDIT_TPRETOT://TOT预警 0：不预警 1-60，步进1秒
			case IDC_EDIT_TREKEY://TOT再按键 0：不预警 1-60，步进1秒
				{
					if(nRet == 0)
					{	
						strInput ="不预警";
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetSpecialValue(0,strInput);
					}else
						 nRet = 60;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case IDC_EDIT_TRESET:	//TOT复位 0：不预警 1-30，步进1秒
				{
					if(nRet == 0)
					{	
						strInput ="不预警";
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetSpecialValue(0,strInput);
					}else
						 nRet = 30;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case IDC_EDIT_VOX_DELAY://VOX声控延迟 0：不延迟关闭 1-30，步进100毫秒
				{
					if(nRet == 0)
					{
						strInput ="不延迟关闭";
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetSpecialValue(0,strInput);
					} else
						 nRet = 30;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case IDC_EDIT_KEYLOCK_DELAY://键盘锁 0：关 1-6，步进5秒  
				{
					if(nRet == 0)
					{
						strInput ="关闭";
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetSpecialValue(0,strInput);
					}else
						 nRet = 6;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case IDC_EDIT_BGLIGHT_DELAY://背光延迟时间	5-60，步进1秒
				{
					
					nRet = 60;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case  IDC_EDIT_PRE_TX_DELAY:	//发射预载波时间 0-250，步进10毫秒
				{
					nRet = 250;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case IDC_EDIT_GROUPCALL_HOLD_TIME:	//组呼保持时间 0-20，步进500毫秒
			case IDC_EDIT_SIGNALCALL_HOLD_TIME:	//个呼保持时间 0-20，步进500毫秒
				{
					nRet = 20;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
				}
				break;
			case IDC_EDIT_ALARM_CALL_TIME: //紧急警报次数 1-254， 255：无限次
			case IDC_EDIT_ALAMR_TIME:		//紧急呼叫次数 1-254， 255：无限次
				{
					if(nRet == 255 || nRet == 0)
					{	nRet = 0;
						strInput ="无限次";
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetSpecialValue(0,strInput);
					}
					else
					{
						nRet = 254;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet);
					}
				}
				break;
			case IDC_EDIT_MIC_HOLD_TIME:	//热麦克持续时间 1-12，单位10秒 
			case IDC_EDIT_RCV_HOLE_TIME:	//接收持续时间 1-12，单位10秒
				{
					if(nRet <1)
						nRet = 10;
					else
						nRet = 12;
						((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet*10);
				}
				break;
			}//end switch
		}//end if
		else
		{
 			((CSpanEdit*)GetDlgItem(SpinIDArray.nCtrlID[i]))->SetInteger(nRet*SpinIDArray.nStep[i]);
		}
	
	}
	for (i=0;i<4;i++)
	{
		nRet = GetEmerSettingValues(SETTING_ALARM_TIME+i);
		((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->SetCurSel(nRet);
	}
	for (i=0;i<4;i++)
	{
		nRet = GetSettingValue(SETTING_TCOMM_TIME+i);
		((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1+i))->SetCurSel(nRet);
	}
	EnableComboBoxes();
}
void CRadioSetView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	//报警
	m_editAlarmTime.SetRange(1,254,4,1);
	m_editAlarmCallTime.SetRange(1,254,4,1);
	m_editMicHoldTime.SetRange(1,120,3,10);
	m_editRcvHoldTime.SetRange(1,120,3,10);
	
	//预载波
	m_editPreTxDelay.SetRange(0,2500,4,10);
	m_editGrpHoldTime.SetRange(0,10000,5,500);
	m_editPeerHoldTime.SetRange(0,10000,5,500);

	//TOT
	m_editTcomm.SetRange(10,600,3,10);
	m_editTpretot.SetRange(1,60,2,1);
	m_Trekey.SetRange(1,60,2,1);
	m_Treset.SetRange(1,30,2,1);

	m_editKeylockDelay.SetRange(1,30,2,5);
	m_editBKLightDelay.SetRange(5,60,2,1);
	m_editVoxTime.SetRange(1,3000,4,100);
	LoadData();
	return;	
}

void CRadioSetView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	ResizeParentToFit(FALSE);


	m_cbVoxLvl.AddString("关闭");
	int i=0;

 	m_editID.SetLimitText(8);
	LoadData();
}
void	CRadioSetView::LoadComboString()
{
	CString	str;
	int i;
	//tot和emer的清零
	for (i=0;i<4;i++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1+i))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->ResetContent();
		m_cbPowerSaveLvl.ResetContent();
	}
	for(i=0;i<4;i++)
	{
		int j=1;
		if (i==0)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1))->AddString("无限制");
			for (;j<=6;j++)
			{
				str.Format("%d",j*10);
				((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1))->AddString(str);
			}
		}
		else
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1+i))->AddString("不预警");
			if (i==3)
			{
				for(;j<=30;j++)
				{
					str.Format("%d",j);
					((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1+i))->AddString(str);
				}
			}
			else
			{
				for(;j<=60;j++)
				{
					str.Format("%d",j);
					((CComboBox*)GetDlgItem(IDC_COMBO_TOT_1+i))->AddString(str);
				}
			}
		}
		//emer设置
		if (i<2)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->AddString("无限次");
			for (j=1;j<255;j++)
			{
				str.Format("%d",j);
				((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->AddString(str);
			}
		}
		else
		{
			for(j=1;j<=12;j++)
			{
				str.Format("%d",j*10);
				((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->AddString(str);
			}
		}
	}
	m_cbTone.ResetContent();
	m_cbCallInTone.ResetContent();
	m_cbCallOutTone.ResetContent();
	m_cbBGLight.ResetContent();
	m_cbVoxLvl.ResetContent();
	m_cbNoiseLvl.ResetContent();
	for(i=0;i<sizeof(strIdleDisp)/sizeof(strIdleDisp[0]);i++)
	{	
		((CComboBox*)GetDlgItem(IDC_COMBO_MAINFRAME_STYLE))->AddString(strIdleDisp[i]);
		if(i<2)
			m_cbTone.AddString(strToneEn[i]);
		if (i<4)
		{
			m_cbCallInTone.AddString(strToneOption[i]);
			m_cbCallOutTone.AddString(strToneOption[i]);
			m_cbPowerSaveLvl.AddString(strPowerLvl[i]);
		}
		if(i<3)
		{
			m_cbAlarmMode.AddString(strEmerMode[i]);
			m_cbBGLight.AddString(strBKLight[i]);
		}
		if(i<=4)
		{
			m_cbVoxLvl.AddString(strLevel[i+1]);
			m_cbAlarmType.AddString(strEmerType[i]);
		}

		if(i<=9)
			m_cbNoiseLvl.AddString(strLevel[i]);
	}
	LoadAlarmCh();
}

void	CRadioSetView::LoadAlarmCh()
{
	CString		strCh,strZone;
	m_cbAlarmCh.ResetContent();
	m_cbAlarmCh.AddString("当前信道");
	int i=0,j=0;
	int nCh,nZone;
	for (i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			strZone = ((CPCSWApp*)AfxGetApp())->GetName(i+1,j+1,ZONE_NAME,ZONE_CHANNEL_NAME_BYTE,18,0,false);
			strCh = ((CPCSWApp*)AfxGetApp())->GetName(i+1,j+1,CHANNEL_CHANNAME,ZONE_CHANNEL_NAME_BYTE);
			if(!(strCh.IsEmpty() ||strZone.IsEmpty()))
			{
				m_cbAlarmCh.AddString(strZone+":"+strCh);
				nCh = DWORD(j)&0x00ff;
				nZone = (DWORD(i)<<8)&0xff00;
				mapChannel.insert(pair<int,DWORD>(i*16+j,nZone|nCh));
			}
		}
	}
}
void CRadioSetView::OnDeltaposSpinPreTxDelay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetPreTxDelay(m_editPreTxDelay.DeltaInteger(-pNMUpDown->iDelta));
	SetSettingValues(SETTING_PRETXDELAY_TIME,m_editPreTxDelay.DeltaInteger(-pNMUpDown->iDelta));
	*pResult = 0;
}


void CRadioSetView::OnDeltaposSpinGroupcallHoldTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_GRPHOLD_TIME,m_editGrpHoldTime.DeltaInteger(-pNMUpDown->iDelta));
	SetSettingValues(SETTING_GRPHOLD_TIME,m_editGrpHoldTime.DeltaInteger(-pNMUpDown->iDelta));
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinSignalcallHoldTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_PEERHOLD_TIME,m_editPeerHoldTime.DeltaInteger(-pNMUpDown->iDelta));
	SetSettingValues(SETTING_PEERHOLD_TIME,m_editPeerHoldTime.DeltaInteger(-pNMUpDown->iDelta));
	*pResult = 0;
}

// void CRadioSetView::OnDeltaposSpinMicHoldTime(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
// 	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_ALARM_MICHOLD_TIME,m_editMicHoldTime.DeltaInteger(-pNMUpDown->iDelta));
// 	
// 	*pResult = 0;
// }
// 
// void CRadioSetView::OnDeltaposSpinRcvHoldTime(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
// 	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_ALARM_RCVHOLD_TIME,m_editRcvHoldTime.DeltaInteger(-pNMUpDown->iDelta));
// 	
// 	*pResult = 0;
// }
// 
void CRadioSetView::OnDeltaposSpinKeylockDelay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_KEYLOCK,m_editKeylockDelay.DeltaInteger(-pNMUpDown->iDelta));
	SetSettingValues(SETTING_KEYLOCK,m_editKeylockDelay.DeltaInteger(-pNMUpDown->iDelta));
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinVoxDelay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_VOX_DELAY_TIME,m_editVoxTime.DeltaInteger(-pNMUpDown->iDelta));
	SetSettingValues(SETTING_VOX_DELAY_TIME,m_editVoxTime.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinBglightDelay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_BACKLIGHT_DELAYTIME,m_editBKLightDelay.DeltaInteger(-pNMUpDown->iDelta));
	SetSettingValues(SETTING_BACKLIGHT_DELAYTIME,m_editBKLightDelay.DeltaInteger(-pNMUpDown->iDelta));
	*pResult = 0;
}

/*
void CRadioSetView::OnDeltaposSpinTcomm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_TCOMM_TIME,m_editTcomm.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinTpretot(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_TPRETOT_TIME,m_editTpretot.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinTrekey(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_TREKEY_TIME,m_Trekey.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinTreset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_TRESET_TIME,m_Treset.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinAlarmCallTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_ALARM_CALL_TIME,m_Treset.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

void CRadioSetView::OnDeltaposSpinAlarmTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	((CPCSWDoc*)GetDocument())->SetSpinValues(SETTING_ALARM_TIME,m_Treset.DeltaInteger(-pNMUpDown->iDelta));
	
	*pResult = 0;
}

*/
/*
BOOL CRadioSetView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::OnScroll(nScrollCode, nPos, bDoScroll);
}
*/
void	CRadioSetView::OnTotSelChange(UINT nID)
{
	int nSel = ((CComboBox*)GetDlgItem(nID))->GetCurSel();
	int nIndex = nID<IDC_COMBO_TOT_4?(nID - IDC_COMBO_TOT_1):-1;
	SetSettingValues(SETTING_TCOMM_TIME+nIndex,nSel);
}
void	CRadioSetView::OnEmerSelChange(UINT nID)
{
	int nSel = ((CComboBox*)GetDlgItem(nID))->GetCurSel();
	int nIndex = nID<IDC_COMBO_EMER_4?(nID - IDC_COMBO_EMER_1):-1;
	//呼叫次数为无限次，选项为0，但记录值为255
	if (nSel == 0 &&(nID == IDC_COMBO_EMER_1||nID == IDC_COMBO_EMER_2))
	{
		nSel = 0xff;
	}
	else if (nID == IDC_COMBO_EMER_3 || nID == IDC_COMBO_EMER_4)
	{
		nSel++;
	}
	SetEmerSettingValues(SETTING_ALARM_TIME+nIndex,nSel);
}

int		CRadioSetView::GetSettingValue(int nFlag)
{
	int nRet = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioSetting[0x00+nFlag];
	return nRet;
}
int		CRadioSetView::GetEmerSettingValues(int nFlag)
{
	int nRet = ((CPCSWApp*)AfxGetApp())->m_CommInfo.pEmergencySetting[0x00+nFlag];
	return nRet;
}
void	CRadioSetView::SetSettingValues(int nFlag,int nVal)
{
	((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioSetting[0x00+nFlag] = nVal;
}
void	CRadioSetView::SetEmerSettingValues(int nFlag,int nVal)
{
	((CPCSWApp*)AfxGetApp())->m_CommInfo.pEmergencySetting[0x00+nFlag] = nVal;
}
CString	CRadioSetView::GetIDStr(int nGrp,int nFlag)
{
	char str[20];
	BYTE ch;
	int i;
	int nLength = 4*2-1;//此项由于从下标0开始,所以是本机ID的长度减去1
	int j=0;
	if(nGrp == 0)
	{
		for(i=nLength;i>=0;i--)
		{
			if(i%2==0)
				ch = *(((CPCSWApp*)AfxGetApp())->m_CommInfo.pEmergencySetting+nFlag+i/2)&0x0F;	
			else
				ch = *(((CPCSWApp*)AfxGetApp())->m_CommInfo.pEmergencySetting+nFlag+i/2)>>4;
			if(ch<10)
				str[nLength-i-j]=ch+'0';
			else
				j++;
		}
	}
	else if (nGrp == 1)
	{
		for(i=nLength;i>=0;i--)
		{
			if(i%2==0)
				ch = *(((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioSetting+nFlag+i/2)&0x0F;	
			else
				ch = *(((CPCSWApp*)AfxGetApp())->m_CommInfo.pRadioSetting+nFlag+i/2)>>4;
			if(ch<10)
				str[nLength-i-j]=ch+'0';
			else
				j++;
		}	}
	str[nLength]=0;   //由于只显示7位数字,估计str[7]=0表示结束符
	return CString(str);
}
CString	CRadioSetView::GetAlarmName(int nFlag,int nLen)
{
	BYTE *ptr;
	BYTE szTemp[32];
	ptr = &((CPCSWApp*)AfxGetApp())->m_CommInfo.pEmergencySetting[0x00+nFlag];
	memcpy(szTemp,ptr,nLen);
	szTemp[nLen] = szTemp[nLen+1] = 0x00;
	CString str;
	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)szTemp,-1,str.GetBuffer(nLen),nLen,NULL,NULL);
	str.ReleaseBuffer();
	return str;
}
void	CRadioSetView::EnableComboBoxes()
{
	//报警按钮
	int	nSel = m_cbAlarmType.GetCurSel();
	int i;
	if (nSel == 0 ||nSel == 1)//无功能  仅鸣笛
	{
		m_cbAlarmMode.EnableWindow(FALSE);
		m_cbAlarmCh.EnableWindow(FALSE);
		for (i=0;i<4;i++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(FALSE);
		}
	}
	else  
	{
		m_cbAlarmMode.EnableWindow(TRUE);
		m_cbAlarmCh.EnableWindow(TRUE);
		int nRet = m_cbAlarmMode.GetCurSel();
		if (nRet != 2)//背景音
		{
			for (i=0;i<4;i++)
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(FALSE);
			}
		}
		else
		{
			for (i=0;i<4;i++)
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(TRUE);
			}
		}
	}
	//提示音
	nSel = m_cbTone.GetCurSel();
	if (nSel == 1)
	{
		m_cbCallInTone.EnableWindow(FALSE);
		m_cbCallOutTone.EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_KEY_TONE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_LOWPOWER_TONE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SMS_TONE))->EnableWindow(FALSE);
	}
	else
	{
		m_cbCallInTone.EnableWindow(TRUE);
		m_cbCallOutTone.EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_KEY_TONE))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_LOWPOWER_TONE))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SMS_TONE))->EnableWindow(TRUE);
	}
	//背光灯
	nSel = m_cbBGLight.GetCurSel();
	if (nSel == 1)//定时
	{
		m_editBKLightDelay.EnableWindow(TRUE);
	}
	else
		m_editBKLightDelay.EnableWindow(FALSE);
}
void CRadioSetView::OnSelchangeComboTone() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbTone.GetCurSel();
	if (nSel == 1)//不静音
	{
		m_cbCallInTone.EnableWindow(FALSE);
		m_cbCallOutTone.EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_KEY_TONE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_LOWPOWER_TONE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_SMS_TONE))->EnableWindow(FALSE);
	}
	else
	{
		m_cbCallInTone.EnableWindow(TRUE);
		m_cbCallOutTone.EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_KEY_TONE))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_LOWPOWER_TONE))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_SMS_TONE))->EnableWindow(TRUE);
	}
	SetSettingValues(SETTING_TONE_EN,nSel);
}

void CRadioSetView::OnSelchangeComboAlarmMode() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cbAlarmMode.GetCurSel();
	int i=0;
	if (nSel !=2)//背景音发送
	{
		for (;i<4;i++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(FALSE);
		}
	}
	else
	{
		for (;i<4;i++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(TRUE);
		}
	}
	SetEmerSettingValues(SETTING_ALARM_MODE,nSel);
}
void	CRadioSetView::OnSelchangeComboAlarmType()
{
	int	nSel = m_cbAlarmType.GetCurSel();
	int i;
	if (nSel == 0 ||nSel == 1)//无功能  仅鸣笛
	{
		m_cbAlarmMode.EnableWindow(FALSE);
		m_cbAlarmCh.EnableWindow(FALSE);
		for (i=0;i<4;i++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(FALSE);
		}
	}
	else  
	{
		m_cbAlarmMode.EnableWindow(TRUE);
		m_cbAlarmCh.EnableWindow(TRUE);
		int nRet = m_cbAlarmMode.GetCurSel();
		if (nRet != 2)//背景音
		{
			for (i=0;i<4;i++)
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(FALSE);
			}
		}
		else
		{
			for (i=0;i<4;i++)
			{
				((CComboBox*)GetDlgItem(IDC_COMBO_EMER_1+i))->EnableWindow(TRUE);
			}
		}
	}
	SetEmerSettingValues(SETTING_ALARM_TYPE,nSel);
}
void	CRadioSetView::OnSelchangeComboMainStyle()
{
	int nSel = m_cbIdleDisp.GetCurSel();
	nSel++;
	SetSettingValues(SETTING_IDLE_DISPLAY,nSel);
}
void	CRadioSetView::OnSelchangeComboBkLight()
{
	int nSel = m_cbBGLight.GetCurSel();
	if (nSel == 1)//定时
	{
		m_editBKLightDelay.EnableWindow(TRUE);
	}
	else
		m_editBKLightDelay.EnableWindow(FALSE);
	SetSettingValues(SETTING_BACKLIGHT_NOTE,nSel);
}
void	CRadioSetView::OnSelchangeComboPowerLvl()
{
	int nSel = m_cbPowerSaveLvl.GetCurSel();
	SetSettingValues(SETTING_POWERSAVE_SCALE,nSel);
}
void	CRadioSetView::OnCheckPowerLvl()
{
	int nCheck = ((CButton*)GetDlgItem(IDC_CHECK_POWERSAVELVL))->GetCheck();
	if (nCheck)
	{
		m_cbPowerSaveLvl.EnableWindow(TRUE);
	}
	else
		m_cbPowerSaveLvl.EnableWindow(FALSE);
	SetSettingValues(SETTING_POWERSAVE_EN,nCheck);
}
void CRadioSetView::OnCbnSelchangeComboAlarmChannel()
{
	// TODO: 在此添加控件通知处理程序代码
	int	nSel = m_cbAlarmCh.GetCurSel();
	DWORD	dwInfo ;
	if(nSel > 0)
	{
		it = mapChannel.find(nSel-1);
		dwInfo = (DWORD)it->second;
		int nCh,nZone;
		nCh = dwInfo&0x00ff;
		nZone = dwInfo>>8;
		SetEmerSettingValues(SETTING_ALARM_CHANNEL,nCh+1);
		SetEmerSettingValues(SETTING_ALARM_CHANNEL+1,nZone);
	}
	else if (nSel == 0)
	{
		SetEmerSettingValues(SETTING_ALARM_CHANNEL,0x00);
		SetEmerSettingValues(SETTING_ALARM_CHANNEL+1,0xff);
	}
}
