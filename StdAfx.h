// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__EDD867B1_D364_4D81_AEB5_8BD5772F0E69__INCLUDED_)
#define AFX_STDAFX_H__EDD867B1_D364_4D81_AEB5_8BD5772F0E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define WM_SHOW_WINDOW	(WM_USER+100)
#define	WM_UPDATE_ALLDATA	(WM_USER+102)

#define		SPLIT_TEST	
#define		ArraySize(x)		(sizeof(x))/(sizeof(x[0]))

#define		GRP_LIST_STRUCT_LEN		34
#define		CONTACT_STRUCT_LEN		22
#define		SHORTTEXT_STRUCT_LEN		162
#define		ZONE_STRUCT_LEN			736
#define		CHANNEL_STRUCT_LEN		46
#define		SCAN_STRUCT_LEN			60



#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcview.h>
 
#include <iostream> 
using namespace std;
#include <map>//STL头文件，不用添加.h  用于map容器使用
#include <algorithm>//

// #pragma comment(linker,"../Debug/hook.lib")

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
/**/		enum MenuAddress
{
	MenuPowerLvl=0x00,
	MenuKeyLock=0x01,
	MenuLanguage=0x02,
	MenuBackLight=0x03,
	MenuLed=0x04,
	MenuTone=0x05,
	MenuLuminance=0x06,
	MenuSMS=0x07,
	MenuNoise=0x08,
	MenuDeleteItemOfContact=0x09,
	MenuScan=0x0A,
	MenuScanCheckCh=0x0B,
	MenuScanAddTempCh=0x0C,
	MenuScanDelTempCh=0x0D,
	MenuScanAddCh=0x0E,
	MenuScanDelCh=0x0F,
	MenuVox=0x10,
	MenuWhisper=0x11,
	MenuVibration=0x12,
	MenuDate=0x13,
	MenuMainMenu=0x14,
	MenuPowerSave=0x15,
	MenuTalkAround=0x16,
	MenuSpeechEnhance = 0x17,
	MenuVoiceKey = 0x18,
	MenuAllowKill=0x20,			//允许遥弊,在radiosetting中位置
	MenuAllowActive=0x21		//允许激活
};
//区域//信道——信息
enum	ZoneAddress
{
	ZONE_NAME = 0X00,	//区域别名 16byte
	ZONE_CHANNEL_NUM = 0X10,	//区域支持信道数
	ZONE_RESERVE = 0X11		//保留
};
enum	ChannelAddress
{
	CHANNEL_CHASS = 0X00,	//信道配置标识
	CHANNEL_SCANLIST = 0X01,	//信道扫描列表
	CHANNEL_MODE = 0X02,		//信道工作模式
	CHANNEL_STATUS = 0X03,		//信道工作状态
	CHANNEL_CHANNAME = 0X04,	//16BYTE
	CHANNEL_TX_FREQ = 0X14,		//4BYTE
	CHANNEL_RX_FREQ = 0X18,		//4BYTE
	CHANNEL_POWER_LEVEL = 0X1C,	//1
	CHANNEL_INTERVAL	= 0X1D,
	CHANNEL_SPEECH_ENHANCE_LEVEL=0X1E, //2BYTE
	CHANNEL_CTC_PHASE = 0X20,	//1
	CHANNEL_BUSYLOCK = 0X21,	//1
	CHANNEL_TX_ANALOG_SIG_TYPE = 0X22,	//1
	CHANNEL_TX_ANALOG_SIG_NUM = 0X23,	//1
	CHANNEL_RX_ANALOG_SIG_TYPE = 0X24,	//1
	CHANNEL_RX_ANALOG_SIG_NUM = 0X25,	//1
	CHANNEL_DIGIT_RX_GROUP = 0X26,		//1
	CHANNEL_DIGIT_SEND_ID	= 0X27,		//1
	CHANNEL_DIGIT_POLITE	= 0X28,	//1
	CHANNEL_DIGIT_VOICEKEY_EN = 0X29,	//1
	CHANNEL_DIGIT_VOICEKEY = 0X2A		//4
};
enum	ZoneChannelLen
{
	ZONE_CHANNEL_FREQ_BYTE = 4,
	ZONE_CHANNEL_NAME_BYTE = 16,
	CHANNEL_STRUCT_BYTE = 44,
	ZONE_STRUCT_BYTE = 18
};
enum	SMSAddr
{
		SMS_TXTNUM = 0X00,
		SMS_TXTLEN = 0X01,
		SMS_TXTCONTENT = 0X02
};

enum	SettingAddress
{
	SETTING_POWERSAVE_EN = 0x00,
	SETTING_POWERSAVE_SCALE = 0x01,
	SETTING_TCOMM_TIME	= 0x02,
	SETTING_TPRETOT_TIME = 0X03,
	SETTING_TREKEY_TIME	 = 0X04,
	SETTING_TRESET_TIME = 0X05,
	SETTING_WHISPER_EN = 0X06,
	SETTING_NOISE_SCALE = 0X07,
	SETTING_VOX_LEVEL = 0X08,
	SETTING_VOX_DELAY_TIME = 0X09,
	SETTING_VOX_CANCEL = 0X0A,
	SETTING_VOX_FORBID = 0X0B,
	SETTING_KEYLOCK = 0X0C,
	SETTING_CHANNELLOCK = 0X0D,
	SETTING_VIBRATE_EN = 0X0E,
	SETTING_TONE_EN = 0X0F,
	SETTING_CALLOUT_TONE = 0X10,
	SETTING_CALLIN_TONE = 0X11,
	SETTING_SMS_TONE = 0X12,
	SETTING_LOWBATTORY_TONE = 0X13,
	SETTING_KEY_TONE	= 0X14,
	SETTING_LIGHT_NOTE = 0X15,
	SETTING_BACKLIGHT_NOTE = 0X16,
	SETTING_BACKLIGHT_DELAYTIME = 0X17,
	SETTING_IDLE_DISPLAY	= 0X18,
	SETTING_DATE_EN = 0X19,
	SETTING_MSID = 0X1A,		//4字节
	SETTING_WILDCARD_EN = 0X1E,
	SETTING_MANUALDIAL_EN = 0X1F,
	SETTING_PRETXDELAY_TIME = 0X20,
	SETTING_GRPHOLD_TIME = 0X21,
	SETTING_PEERHOLD_TIME = 0X22,
	SETTING_KILL_EN = 0X23,
	SETTING_ACTIVE_EN = 0X24,
	SETTING_DECODE_EN = 0X25,
	SETTING_CALLALL_EN = 0X26,
	SETTING_CALLGRP_EN = 0X27,
	SETTING_CREATE_CONTENT_EN = 0X28,
	SETTING_EDIT_SMS_EN = 0X29,
};
enum	CONTAddr
{
	CONTACT_NUM = 0X00,//序号
	CONTACT_TYPE = 0X01,
	CONTACT_NAME = 0X02,	//16BYTE
	CONTACT_ID	= 0X12		//4BYTE
};
enum	CONTLEN
{
	NAME_BYTE_LEN = 16,
	ID_BYTE_LEN	 = 4
};
enum	GROUPAddr
{
	GRP_NUM = 0X00,//序号
	GRP_MEMBER_NUM = 0X01,	//列表成员 数
	GRP_NAME	 = 0X02,		//别名  16BYTE
	GRP_CONTACT_NUM = 0X12		//联系人序列号  最多16BYTE
};

enum	EmeAddress
{	
	SETTING_ALARM_NAME = 0X00,//16字节
	SETTING_ALARM_TYPE = 0X10,
	SETTING_ALARM_MODE = 0X11,
	SETTING_ALARM_CHANNEL = 0X12,//2字节
	SETTING_ALARM_TIME = 0X14,
	SETTING_ALARM_CALL_TIME = 0X15,
	SETTING_ALARM_MICHOLD_TIME = 0X16,
	SETTING_ALARM_RCVHOLD_TIME = 0X17,
	SETTING_ALARM_EMEID = 0X18	//4字节
};
enum	SettingLen
{
	SETTING_BYTE_LEN = 1,
	SETTING_WORD_LEN = 2,
	SETTING_DWORD_LEN = 4,
	SETTING_DBDWORD_LEN = 8,
	SETTING_NAME_LEN = 16
};
enum	ScanAddr
{
	SCAN_LISTNUM = 0X00,	//列表序号
	SCAN_ASS	= 0X01,		//配置标识
	SCAN_NAME	= 0X02,		//扫描别名-16字节
	SCAN_MODE	= 0X12,		//扫描模式
	SCAN_CHANNELNUM = 0X13,	//信道数量
	SCAN_CHANNELFLAG = 0X14,	//区域信道——32字节
	SCAN_ONTIME = 0X34,		//扫描停留时间
	SCAN_TXMODE = 0X35,		//扫描发射信道模式
	SCAN_TXCHANNEL = 0X36,	//扫描发射信道
	SCAN_RCVDELAY	 = 0X38,//扫描接收延迟时间
	SCAN_SENDDELAY	= 0X39,	//扫描发射延迟时间
	SCAN_CALLBACK	= 0X3A	//回讲功能
};
enum	ScanByte
{
	SCAN_BYTE = 1,
	SCAN_TX_CHBYTE = 2,
	SCAN_NAMEBYTE = 16,
	SCAN_CH_FLAGBYTE = 32
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__EDD867B1_D364_4D81_AEB5_8BD5772F0E69__INCLUDED_)
