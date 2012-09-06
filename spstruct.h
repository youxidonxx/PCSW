#ifndef _SPSTRUCT_H_
#define _SPSTRUCT_H_

/*******************************************************************************
File Name: spstruct.h

Description: This file contains the sp global struct definition.

Copyright:
    Copyright(c) 2011 LinkTop technologies Co., LTD. All rights reserved.

Change History:
2011-03-25  ww    v0.0.0.1  Create
2011-05-06  ww    v0.0.1.0  Check and release after function test
2011-08-31  ww    v1.0.0.1  modify to follow the function defintion of V1.1
2012-02-15  ww    v1.1.0.1  modify to follow the function defintion of V1.2
*******************************************************************************/

#include "typedef.h"
#include "spmsgid.h"
/*****************************************************************************
				 Global Struct Definitions
******************************************************************************/
#define    SP_NUM_DATA      160
#pragma pack(push) //保存对齐状态 

#pragma pack(1)//设定为1字节对齐
/*SP General Parameters */
typedef   struct
{
    uint16         sleepstep;
    uint16         LowBtlCout;
    uint8          Numbusy;
    uint8          tbusy;
    uint8          tsleep;
    uint8          tbtl;
    uint8          tvol;
    uint8          trssi;
    uint32         refrcc[16];
} SpGen_S;

/*pl calculate  param for mt*/
typedef   struct
{
    uint32         CalTxFreq;
    uint32         CalRxFreq;
    uint16         CalHighPC;
    uint16         CalLowPC;
    uint16         DigTXMod1Factor;
    uint16         DigTXMod2Factor;
    uint16   	   AnaTXMod1FactorAf;
    uint16         AnaTXMod2FactorAf;
    uint16   	   AnaTXMod1FactorCtc0;
    uint16   	   AnaTXMod2FactorCtc0;
    uint16   	   AnaTXMod1FactorCtc1;
    uint16   	   AnaTXMod2FactorCtc1;
    uint16   	   AnaTXMod1FactorCtc2;
    uint16   	   AnaTXMod2FactorCtc2;
    uint16   	   AnaTXMod1FactorCdc;
    uint16   	   AnaTXMod2FactorCdc;
    uint16         RxCalTV;
    uint16   	   RxNoise1Open;
    uint16   	   Rxnoise1Close;
    uint16   	   RxNoise9Open;
    uint16   	   Rxnoise9Close;
    uint16         Rxrssi1thrd;
    uint16         Rxrssi5thrd;
} PlCal_S;

/* zsp init param */
typedef   struct
{
    uint32         Uart2Baudrate;
    uint32         RfVcoRfin;
    uint16         RfVcoRefer;
    uint16         RfVcoPreDiv;
    uint16         RfVcoCurSet;
    uint16         RfVcoMuxOut;
    uint16         RfDelay5TOn;
    uint16         RfDelay5TOff;
    uint16         RfDelay5ROn;
    uint16         RfDelay5ROff;
    uint16         RfDelay5COn;
    uint16         RfDelay5COff;
    uint16         RfDelayTxOn;
    uint16         RfDelayTxOff;
    uint16         RfDelayRxOn;
    uint16         RfDelayRxOff;
    uint16         RfDelayPaOn;
    uint16         RfDelayPaOff;
    uint16         RfDelayPllTROn;
    uint16         RfDelayPllTROff;
    uint16         RfDelayTxVco;
    uint16         RfDelayRxVco;
    uint16         SpchDelaySpkOn;
    uint16         SpchDelaySpkOff;
    uint16         SpchDelayAmpOn;
    uint16         SpchDelayAmpOff;
    uint16         SpchDelayMicOn;
    uint16         SpchDelayMicOff;
    uint16         SpchDelayMuteOn;
    uint16         SpchDelayMuteOff;
    uint16         SpchDelaySleep;
    uint16         SpchDelayWake;
    uint16         adamp;
    uint16         affactr;
    uint16         anavolm;
    uint16         prembllen;
} ZspOwn_S;

/* ccl init param */
typedef   struct
{
    uint8          bTack;              /* T_ACK */
    uint8          btalarm;
    uint16         wTTxwait;          /* Tx_wait:
    										                        0000: 	       No Time
											                    0001:         40ms
												                0010:         80ms
												                0011:         160ms
												                0100:         320ms
												                other:        Reserve
										                      */
    uint8          bNumRep;            /*NUM_REP*/
    uint8          bNumData;           /*NUM_DATA*/
    uint8          bNumStatus;         /*NUM_STATUS*/
    uint8          bheadcnt;
    uint16         wTRsp;              /*T_RSP*/

    uint16         wTsync;              /*T_SYNC*/
    uint16         wLateAce;
} CclOwn_S;
/*SP mt  thrd Parameters */
typedef   struct
{
    uint16           BATLowThrd;
    uint16           TxVccn;
    uint16           Vox1open;
    uint16           Vox5open;
    uint16           maxvol;
    uint16           freqnum;
} SpMtTh_S;

/*SP mt  Parameters */
typedef   struct
{
    uint16           BATLowThrd;
    uint16           TxVccn;
    uint16           Vox1open;
    uint16           Vox5open;
    uint16           maxvol;
    uint16           freqnum;   /* 2-5*/
    PlCal_S          PlCal[5];
} SpMtFlh_S;

/*SP_PL_INIT_REQ*/
typedef   struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         adamplify;
    uint16         affactor;
    uint16         anavolm;
    uint16         CRC;                 /*CRC*/
} PlInitReq_S;

/*SP_DLL_INIT_REQ*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         preamblelen;
    uint16         CRC;                 /*CRC*/
} DllInitReq_S;

/*SP_SCH_INIT_REQ*/
typedef   struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         SpkGain;
    uint16         MicGain;
    uint8  	       chAss; 							/* whether is null channel */
    uint8  	       mode;  							/*0: analog  1: digital */
    uint8          ctcq;
    uint8          powerlevel;
    uint32         txfreq;
    uint32         rxfreq;
    uint32         txcc;
    uint32         rxcc;
    uint16         speechenhanen;
    uint8          interv;       /*channel interval    0:12.5KHZ  1：20KHZ    2：25KHZ      */
    uint8          voikeyon;
    uint32         voikey;
    uint8          txanatype;
    uint8          rxanatype;
    uint32         txananum;
    uint32         rxananum;
    uint16         TxVccn;
    uint16         TV;
    uint16         HighPC;
    uint16         LowPC;
    uint16         DigTXMod1Factor;
    uint16         DigTXMod2Factor;
    uint16         AnaTXMod1FactorAf;
    uint16         AnaTXMod2FactorAf;
    uint16   	   AnaTXMod1FactorCtc;
    uint16   	   AnaTXMod2FactorCtc;
    uint16   	   AnaTXMod1FactorCdc;
    uint16   	   AnaTXMod2FactorCdc;
    uint16          CRC;                 /*CRC*/
} SchInitReq_S;

/*SP_SCH_POWEROFF_REQ---null msg*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         CRC;                 /*CRC*/
} SchPowoff_S;

/*SP_SCH_AUDIO_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         repeat;
    uint16         audtype;      /*0: single audio 1:pressed audio without channel
                                          2: pressed audio with channel 3: unpressed audio 4:circle single audio*/
    /*payload:uint16 freq+ uint16 duration*/
} SchAudio_S;

/*SCH_SP_AUDIO_IND*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         optind;     /*0:play finished unnormal 1:play finished normal 2:stop unnormal*/
    uint16         CRC;
} SchIndAudio_S;

/*SP_SCH_VOL_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         SpkGain;    /* 0- 127*/
    uint16         CRC;
} SchVol_S;

/*SP_SCH_ANASIGSET_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          txanatype;
    uint8          rxanatype;
    uint32         txananum;
    uint32         rxananum;
    uint16         CRC;
} SchAnaSig_S;

/*SP_SCH_CHCHG_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8  	       chAss; 							/* whether is null channel */
    uint8  	       mode;  							/*0: analog  1: digital */
    uint8          ctcq;
    uint8          powerlevel;
    uint32         txfreq;
    uint32         rxfreq;
    uint32         txcc;
    uint32         rxcc;
    uint16         speechenhanen;
    uint8          interv;       /*channel interval    0:6.25KHZ  1:12.5KHZ  2:20KHZ  3:25KHZ      */
    uint8          voikeyon;
    uint32         voikey;
    uint8          txanatype;
    uint8          rxanatype;
    uint32         txananum;
    uint32         rxananum;
    uint16         TxVccn;
    uint16         TV;
    uint16         HighPC;
    uint16         LowPC;
    uint16         DigTXMod1Factor;
    uint16         DigTXMod2Factor;
    uint16         AnaTXMod1FactorAf;
    uint16         AnaTXMod2FactorAf;
    uint16   	   AnaTXMod1FactorCtc;
    uint16   	   AnaTXMod2FactorCtc;
    uint16   	   AnaTXMod1FactorCdc;
    uint16   	   AnaTXMod2FactorCdc;
    uint16         CRC;
} SpSchChg_S;

/*SCH_SP_CHCHG_CNF*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         chgready;       /*0:unready 1: ready*/
    uint16         CRC;
} SpSchChgCnf_S;

/*SP_SCH_MIC_IND*/
typedef   struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         operate;             /* 0: pull in   1:pull out */
    uint16         CRC;                 /*CRC*/
} SchMicInd_S;

/*SP_SCH_MICGAIN_REQ*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         micgain;                /*0-63 */
    uint16         CRC;                    /*CRC*/
} SchMicGainReq_S;

/*SCH_SP_SLEEP_CNF/SP_SCH_SLEEP_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         sleepen;       /*0:nonsleep/dis 1: sleep/en*/
    uint16         CRC;
} SpSchSleep_S;

/*SP_SCH_RXSTART_REQ/SP_SCH_RXSTOP_REQ/SP_SCH_RXRFOPEN_REQ/SCH_SP_RXRFOPEN_CNF*/
typedef struct
{
    uint16                 ReceiverMID;            /*Receiver MID*/
    uint16                 SenderMID;            /*Sender MID*/
    uint16                 MsgTYPE;           /*Msg Type*/
    uint16                 MsgID;             /*Msg ID*/
    uint16                 MsgLen;            /*Msg Length--null msg*/
    uint16                 CRC;               /*CRC*/
} SpSchRxReq_S;

/*SP_SCH_MAXPW_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         MaxPower;               /* 0: low   1: high */
    uint16         CRC;
} SchMaxPower_S;

/*SP_ZSPDD_INIT_REQ*/
typedef   struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint32         Uart2Baudrate;
    uint32         RfVcoRfin;
    uint16         RfVcoRefer;
    uint16         RfVcoPreDiv;
    uint16         RfVcoCurSet;
    uint16         RfVcoMuxOut;
    uint16         RfDelay5TOn;
    uint16         RfDelay5TOff;
    uint16         RfDelay5ROn;
    uint16         RfDelay5ROff;
    uint16         RfDelay5COn;
    uint16         RfDelay5COff;
    uint16         RfDelayTxOn;
    uint16         RfDelayTxOff;
    uint16         RfDelayRxOn;
    uint16         RfDelayRxOff;
    uint16         RfDelayPaOn;
    uint16         RfDelayPaOff;
    uint16         RfDelayPllTROn;
    uint16         RfDelayPllTROff;
    uint16         RfDelayTxVco;
    uint16         RfDelayRxVco;
    uint16         SpchDelaySpkOn;
    uint16         SpchDelaySpkOff;
    uint16         SpchDelayAmpOn;
    uint16         SpchDelayAmpOff;
    uint16         SpchDelayMicOn;
    uint16         SpchDelayMicOff;
    uint16         SpchDelayMuteOn;
    uint16         SpchDelayMuteOff;
    uint16         SpchDelaySleep;
    uint16         SpchDelayWake;
    uint16         CRC;                         /*CRC*/
} ZspInitReq_S; 												/*init param*/

/*SP_CCL_INIT_REQ*/
typedef struct
{
    uint16         ReceiverMID;              /*Receiver MID*/
    uint16         SenderMID;              /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint8          bTack;              /* T_ACK */
    uint8          btalarm;
    uint16         wTTxwait;          /* Tx_wait:
    										                        0000: 	       No Time
											                    0001:         40ms
												                0010:         80ms
												                0011:         160ms
												                0100:         320ms
												                other:        Reserve
										                      */
    uint8          bNumRep;            /*NUM_REP*/
    uint8          bNumData;           /*NUM_DATA*/
    uint8          bNumStatus;         /*NUM_STATUS*/
    uint8          bheadcnt;
    uint16         wTRsp;              /*T_RSP*/

    uint16         wTsync;              /*T_SYNC*/
    uint16         wTLateAcess;     /*T_LATEACESS*/
    uint16         CRC;                /*CRC*/
} CclInitReq_S;

/*SP_CCL_SETUP_REQ*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint32         dwCalledMsId;        /*Called Ms ID*/
    uint8          bMode;		            /* Communicaton mode:
    												               000: 	 Voice
    												               001:    Voice + slow data
    												               010:    data Type1(NO FEC),for SMS
    												               011:    data Type2(FEC)
    												               100:    data Type3(Data Package,ARQ)
    												               101:    Voice+data Type2
    												               110:    Call indicator
    												               111:    Individual Status polling
    												               others: Reserve
    									                           */
    uint8          bCallF; 	            /* 0: Reserve;1:Peer-to-peer;2:Group call 3:Call all */
    uint8          bEp;		              /* priority：0-normal call,1-emergency call*/
    uint8          textind;             /* TextInd：1-Text 2-address*/
    uint32         dwDataLength;        /*data Length*/
    /*  payload  */
} cclSetupReq_S;

/*CCL_SP_SETUP_IND */
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint32         dwcalledid;	            /*	MSID	*/
    uint32         dwcallingid;
    uint16         bSUCCIND;            /* Setup Type
    											                  0: 	  SUCC
													                 1:      fail
    										                   */
    uint8           bEp;                 /*EP*/
    uint8           bCallF;              /*0: Reserve;1:Peer-to-peer;2:Group call 3:Call all */
    uint16          CRC;                 /*CRC*/
} cclsetupInd_S;

/*SP_CCL_END_REQ*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         bEndInd;		          /* End Indication:
    								                       0: 	 Reserve
    								                       1:      Communication End
    								                    */

    uint16         CRC;                 /*CRC*/
} cclEndReq_S;

/*SP_MMI_HOLD_IND/CCL_SP_HOLD_IND/SP_CCL_ALARM_CANCEL_REQ/MMI_SP_POWEROFF_REQ/MMI_SP_SCAN_CANCEL_REQ/
/CCL_SP_POWEROFF_REQ/SCH_SP_POWEROFF_REQ/SP_MMI_EXIT_REQ/MMI_SP_EXIT_CNF/MMI_SP_HOLD_CANCEL_REQ/
SP_CCL_HOLD_CANCEL_REQ/MMI_SP_BACK_REQ/SP_CCL_BACK_REQ/SP_CCL_PCCONNECT_REQ*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         CRC;                    /*CRC*/
} SpHold_S, SpAlrmCanl_S, SpPwrOff_S, SpExit_S, SpHoldCanl_S, SpBack_S, SpScanCanl_S, CclSwOn_S;

/*CCL_SP_TOTNOTE_IND/SP_MMI_TOTNOTE_IND*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         duration;            /*pre--tot*/
    uint16         CRC;                    /*CRC*/
} SPNote_S;

/*CCL_SP_BREAK_CNF*/
typedef struct
{
    uint16         ReceiverMID;          /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint32         dwMSID;		          /* 	Calling ID	*/
    uint8          bSUCCIND;            /* Setup Type
    											                   0: 	  SUCC
													                   1:       fail
    										                 */
    uint8          bCOMMTYPE;           /* Setup Type
    												                  000: 	 Voice
    												                  001:    Voice + slow data
    												                  010:    data Type1(NO FEC),for SMS
    												                  011:    data Type2(FEC)
    												                  100:    data Type3(Data Package,ARQ)
    												                  101:    Voice+data Type2
    												                  110:    Call indicator
    												                  111:    Individual Status polling
    												                  others: Reserve
    										                 */
    uint8          bEp;
    uint8          bcause;           /*0:Reserve 1:Expire 2:Operate fail
                                        3:Busy Limit 4:Send Limit 5:Send fail
                                        6:Rec fail*/
    uint16         CRC;                   /*CRC*/
} cclBreakCnf_S;

/*CCL_SP_DATA_IND*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;          /*Sender MID*/
    uint16         MsgTYPE;           /*Msg Type*/
    uint16         MsgID;             /*Msg MID*/
    uint16         MsgLen;            /*Msg Length*/
    uint32         dwcalledID;	           /*	MSID	*/
    uint32         dwcallingID;	           /*	MSID	*/
    uint32         dwDataLength;	   /*	DATA Length	*/
    uint16         bDataType;         /*DATA TYPE*/
    /*  payload  */
} cclDataInd_S;

/*CCL_SP_SERVICE_IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         syncind;           /*0:res 1:invalid 2:valid*/
    uint16         calf;            /*0:res 1: peer-to-peer 2:group 3:call all */
    uint32         revgrp;
    uint16         CRC;              /*CRC*/
} cclServiceInd_S;

/*CCL_SP_SEND_OVER_ IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         endind;            /*0:res 1: rxopen & check 2:rxopen &rev 3:stay for next send*/
    uint16         CRC;              /*CRC*/
} cclSendOverInd_S;

/*CCL_SP_RXSATRT_IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         syncind;          /*0:res 1: unsync  2: sync (regardless callid)*/
    uint16         frameind;        /*1:service 2:preservation frame*/
    uint32         revcc;
    uint16         CRC;              /*CRC*/
} cclStartInd_S;

/*CCL_SP_INIT_CNF/CCL_SP_STOP_CNF*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;              /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;               /*Msg Length*/
    uint16         bReadyInd;             /*Ready Ind
	                                             0: NO
	                                             1: YES
	                                           */
    uint16          CRC;              /*CRC*/

} cclInitCnf_S, cclStopCnf_S;

/*SP_CCL_STOP_REQ*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;             /*Msg Length*/
    uint16         stopInd;           /*stop Ind
	                                          1: valid  others: unvalid
	                                           */
    uint16         CRC;              /*CRC*/

} cclStop_S, SpTimer_S;

/*SP_CCL_RXSTART_REQ/SP_CCL_RXSTOP_REQ*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;             /*Msg Length*/
    uint16         CRC;              /*CRC*/
} cclRxReq_S;

/*SP_CCL_PWSON_REQ --null msg */
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         CRC;              /*CRC*/
} cclPwsonReq_S;

/*SP_CCL_ALARM_REQ*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         alarmen;         /* 0: on 1: off*/
    uint16         CRC;              /*CRC*/
} CclAlarmReq_S;

/*CCL_SP_ALARM_IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint32         calledmsid;
    uint32         callingmsid;
    uint8           alarmind;       /* 0:start 1: end 2: end &make calls*/
    uint8           callind;         /* 0:called  1: calling */
    uint16         CRC;              /*CRC*/

} CclAlarmInd_S;

/*SP_CCL_WK_REQ*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         bWakeup;           /*Wakeup
	                                    0: sleep
	                                    1: wakeup
	                                  */
    uint16          CRC;              /*CRC*/
} cclWkReq_S;

/*CCL_SP_SLEEP_IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint8           bSleepInd;         /*Sleep Ind
	                                    0: NO
	                                    1: YES
	                                  */
    uint8           bSleepTime;        /*Sleep Time
											                   0: all along
												               other: sleep time (unit:10ms)
											                 */
    uint16         CRC;                /*CRC*/

} cclSleepInd_S;

/*SP_CCL_RC_REQ*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;              /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint32         dwMSID;               /*MSID */
    uint16         bOperate;             /*Operate
	                                             0: yaobi
	                                             1: activation
	                                           */
    uint16         CRC;                   /*CRC*/

} cclRcReq_S;

/*CCL_SP_RC_CNF*/
typedef struct
{
    uint16         ReceiverMID;               /*Receiver MID*/
    uint16         SenderMID;               /*Sender MID*/
    uint16         MsgTYPE;              /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;               /*Msg Length*/
    uint32         dwMSID;                /*MSID */

    uint8          bSuccind;              /*Operate
	                                        0: fail
	                                        1: success
	                                      */
    uint8          boperate;         /*0: kill 1: active*/
    uint16         CRC;                  /*CRC*/

} cclRcCnf_S;

/*CCL_SP_RC_IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         boperate;          /* 0: kill ,1: active*/
    uint16         CRC;              /*CRC*/

} cclRcInd_S;

/*SP_CCL_NOISE_REQ*/
typedef struct
{
    uint16         ReceiverMID;                    /*Receiver MID*/
    uint16         SenderMID;                    /*Sender MID*/
    uint16         MsgTYPE;                   /*Msg Type*/
    uint16         MsgID;                     /*Msg MID*/
    uint16         MsgLen;                    /*Msg Length*/
    uint16         Monitoron;               /* 0:normal */
    uint16         CRC;                       /*CRC*/

} cclNoise_S;

/*CCL_SP_STATUS_CNF*/
typedef struct
{
    uint16         ReceiverMID;                   /*Receiver MID*/
    uint16         SenderMID;                   /*Sender MID*/
    uint16         MsgTYPE;                  /*Msg Type*/
    uint16         MsgID;                    /*Msg MID*/
    uint16         MsgLen;                   /*Msg Length*/
    uint32         dwMSID;                    /*MSID */
    uint16          bAbleEn;                   /*Able En
	                                             0: NO
	                                             1: YES
	                                          */
    uint16         CRC;                      /*CRC*/

} cclStatusCnf_S;

/*SP_MMI_INIT_REQ */
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;               /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         batterylevl;
    uint16         CRC;                 /*CRC*/
} AppInitReq_S;

/*MMI_SP_VOICE_REQ*/
typedef  struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         Msid;									/* ms id */
    uint8          Type;  								/* 0:null  1:Peer-to-peer, 2: Group call 3: Call all */
    uint8          EP;    								/* priority：0-normal call,1-emergency call*/
    uint16         CRC;
} SPMakeCallReq_S;

/*SP_MMI_VOICE_IND*/
typedef  struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         calledid;                 /* called ms id */
    uint32         callingid;	          /* caling ms id */
    uint8          Type;                 /* 0:null  1:Peer-to-peer, 2: Group call 3: Call all */
    uint8          EP;                   /* priority：0-normal call,1-emergency call*/
    uint16         CRC;
} SPIncomingCallInd_S;

/*MMI_SP_DISCONNECT_REQ*/
typedef  struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          endind;                 /* end ind */
    uint8          EP;                     /* priority：0-normal call,1-emergency call*/
    uint16         CRC;
} SPDisconnectCallReq_S;

/*SP_MMI_DISCONNECT_IND*/
typedef  struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          endind;                   /*  */
    uint8          mode;
    uint8          success;
    uint8          EP;                   /* priority：0-normal call,1-emergency call*/
    uint16         failcause;       /*0:Reserve 1:Expire 2:Operate fail
                                        3:Busy Limit 4:Send Limit 5:Send fail
                                        6:Rec fail 7:lowbtl fail*/
    uint16         CRC;
} SPCallBreakReq_S;

/*MMI_SP_SMS_REQ/MMI_SP_FM_REQ*/
typedef  struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         Msid;	                                /* ms id */
    uint8          Type;                                    /* 00: Call all, Group call  01:Peer-to-peer, 10:11: Reserve */
    uint8          shortMsgLen;                    /* message length */
    uint16         ImageSMS;                       /*whether image*/
    uint32         pMsgLen;                        /*if it is image, image length*/
    uint32         pMsgdata;                       /*if it is image, image adddress*/
    uint8          shortMsgData [SP_NUM_DATA];    /* unicode sms data*/
    uint16         CRC;
} SPDataReq_S;

/*SP_MMI_DATA_IND*/
typedef  struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         calledid;                                         /* called ms id */
    uint32         callingid;						/*calling ms id */
    uint32         dwDataLength;	                 /*	DATA Length	*/
    uint16         bDataType;                       /*DATA TYPE*/
    /*  payload */
} SPDataInd_S;

/*MMI_SP_STATUS_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         Msid;	                /* ms id */
    uint16         check; 								 /*0：not check   1：check*/
    uint16         CRC;
} SpStatusReq_S;

/*SP_MMI_STATUS_CNF*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         Msid;	                /* ms id */
    uint16         status;                  /* 0: inavalible  1: avaliable*/
    uint16         CRC;
} SpStatusInd_S;

/*MMI_SP_RC_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         Msid;	               /* ms id */
    uint16         operate;              /* 0: kill     1: active */
    uint16         CRC;
} SpRcReq_S;

/*SP_MMI_RC_IND*/
typedef struct
{
    uint16 	       ReceiverMID;
    uint16 	       SenderMID;
    uint16 	       MsgTYPE;
    uint16 	       MsgID;
    uint16 	       MsgLen;
    uint16         operate;            /* 0: kill     1: active */
    uint16 	       CRC;
} SpRcInd_S;

/*SP_MMI_RC_CNF*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         Msid;	         /* ms id */
    uint8          operate;         /* 0: kill     1: active */
    uint8          success;        /* 0: fail    1: success */
    uint16         CRC;
} SpRcCnf_S;

/*MMI_SP_PWSON_REQ/SP_SCH_PWSON_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         pwson;              /*0：Off
							                           1：On
							                       */
    uint16         CRC;
} SpPowersaveOn_S;

/*MMI_SP_MAXPW_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         MaxPower;               /* 0: low   1: high */
    uint16         optind;      /*0:normal 1:power change for eme call*/
    uint16         CRC;
} SpMaxPower_S;

/*MMI_SP_NOISE_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          operate;           /* 0:monitor off 1: monitor on 2: noise thrd modify 3:noise off 4:noise on*/
    uint8          noise;               /* 0: off   1-9:level */
    uint16         CRC;
} SpNoise_S;

/*SP_MMI_CHCHG_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         oprate;       /*1:ta on 2: ta off*/
    uint16         success;     /* 0: fail  1: success */
    uint16         CRC;
} SpChChg_S;

/*MMI_SP_AUDIO_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          aduiotype;       /* 0: alarm 1: audio 2:single audio 3:circle single audio*/
    uint8          repeat;
    /*payload:uint16 freq:Hz+ uint16 duration:ms*/
} SpAudio_S;

/*SP_MMI_AUDIO_IND*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         optind;     /*0:play finished unnormal 1:play finished normal 2:stop unnormal*/
    uint16         CRC;
} SpIndAudio_S;

/*MMI_SP_CHCHG_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         tempind;     /* 0: change zone 1:change channel 2:change zone&channel 3:TA on 4:TA off*/
    uint16         destind;       /*0: reserve 1:change for call 2:change for eme*/
    uint16         zonenumber;
    uint16         channelnumber;   /* 0 - 15*/
    uint16         CRC;
} SpChChgReq_S;

/*MMI_SP_SCAN_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          operate;         /* 0: stop    1: start*/
    uint8          scanmode;    /* 1: scan all channel  2:scan in the list  */
    uint16         CRC;
} SpScanReq_S;

/*MMI_SP_SCAN_OPT_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         operate;         /* 0: delete    1: add*/
    uint16         zonenum;
    uint16         chanlnum;
    uint16         CRC;
} SpScanOptReq_S;

/*SP_MMI_SCAN_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         scanout;                 /* scan outcome */
    uint16         CRC;
} SpScanInd_S;

/*SP_MMI_ALARM_IND*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint32         msid;
    uint32         callingmsid;
    uint8          alarmind;     /*0:open 1: close 2: close & make call */
    uint8          Alarminfo;       /* 0:noneed  1:need alarm info*/
    uint16         CRC;              /*CRC*/

} SpAlarmInd_S;

/*MMI_SP_ALARM_REQ*/
typedef struct
{
    uint16         ReceiverMID;           /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;          /*Msg Type*/
    uint16         MsgID;            /*Msg MID*/
    uint16         MsgLen;           /*Msg Length*/
    uint16         alarmen;         /*0:open 1: close 2: close temporary */
    uint16         callind;            /*0: called 1:calling*/
    uint16         alarmtype;     /*0:alarm 1:audio 2:single audio 3:circle single audio*/
    /*    payload   */
} SpAlarmReq_S;

/*SP_MMI_WK_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         pws;    /*0:sleep   1: wakeup*/
    uint16         CRC;
} SpMmiWk_S;

/*MMI_SP_SLEEP_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          pws;     /*0:sleep   1: wakeup*/
    uint8          time;
    uint16         CRC;
}
SpMmiSleep_S;

/*MMI_SP_INIT_CNF*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         ready;    /* 0: no 1: yes*/
    uint32         appver;
    uint16         CRC;
} SpReady_S;

/*SP_MMI_VOL_IND/MMI_SP_VOL_REQ*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         volume;   /*0-15*/
    uint16         CRC;
} SpVol_S;

/*SP_MMI_RSSI_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         rssi;   /*0-5*/
    uint16         CRC;
} SpRssi_S;

/*SP_MMI_BUSY_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         busy;    /* 0 : not busy 1: busy*/
    uint16         CRC;
} SpBusy_S;

/*SP_MMI_BTL_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         batterylife;   /*0-4*/
    uint16         CRC;
} SpBtl_S;

/* SP_MMI_FAIL_IND*/
typedef struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          operate;     /* 0: delete 1:add 2:scan 3:audio 4:noise del*/
    uint8          failind;  	  /* 1: operate fail */
    uint16         CRC;
} SpFailInd_S;

/*SP_MMI_MIC_IND*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         operate;                /* 0: pull in   1:pull out */
    uint16         CRC;                    /*CRC*/
} MmiMicInd_S;

/*SP_MMI_CHARGE_IND*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         status;                /* 0: in the chage  1:chage finish  2: charge off*/
    uint16         CRC;                    /*CRC*/
} MmiChargeInd_S;

/*MMI_SP_WHISPER_REQ*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         whisp;                /* 0: off  1:on */
    uint16         CRC;                    /*CRC*/
} SpWhispReq_S;

/*MMI_SP_SPEECHEN_REQ/SP_SCH_SPEECHEN_REQ*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         spechenlev;          /* 0: off  1-4 */
    uint16         CRC;                    /*CRC*/
} SpSpeechEnReq_S;

/*MMI_SP_VOCKEY_REQ/SP_SCH_VOCKEY_REQ*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         voicekeyon;          /* 0: off  1:on  2:modify key*/
    uint32         voicekey;
    uint16         CRC;                    /*CRC*/
} SpVoiceKeyReq_S;

/*SP_MMI_SPEECHEN_CNF/SCH_SP_SPEECHEN_CNF /SP_MMI_VOCKEY_CNF/SCH_SP_VOCKEY_CNF*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         optind;             /* 0: fail  1:succ*/
    uint16         CRC;                    /*CRC*/
} SpSpeechEnCnf_S, SpVoiceKeyCnf_S;

/*SP_MMI_SWCONNET_IND*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         status;               /*1:connect 2:read 3: write*/
    uint16         CRC;                    /*CRC*/
} SpSwOn_S;

/*SP_MMI_STATE_REQ /CCL_SP_STATE_REQ*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         stateind;             /*0: poweroff state 1: idle state*/
    uint16         CRC;                    /*CRC*/
} SpStateReq_S;

/*MMI_SP_STATE_CNF /SP_CCL_STATE_CNF*/
typedef struct
{
    uint16         ReceiverMID;         /*Receiver MID*/
    uint16         SenderMID;           /*Sender MID*/
    uint16         MsgTYPE;             /*Msg Type*/
    uint16         MsgID;                /*Msg MID*/
    uint16         MsgLen;              /*Msg Length*/
    uint16         ready;               /*0: noready 1: ready*/
    uint16         CRC;                    /*CRC*/
} SpStateCnf_S;

/*MMI_SP_RESETCH_REQ*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         modtype;                /* 0: reserve  1:136-174 2:400-450 3:440-490 4: 420-470
                                                       5:470-520  6: 300 -340 7:360-390*/
    uint16         CRC;                    /*CRC*/
} MmiModReq_S;

/*SP_MMI_RESETCH_CNF*/
typedef struct
{
    uint16         ReceiverMID;                /*Receiver MID*/
    uint16         SenderMID;                /*Sender MID*/
    uint16         MsgTYPE;               /*Msg Type*/
    uint16         MsgID;                 /*Msg MID*/
    uint16         MsgLen;                /*Msg Length*/
    uint16         success;                /* 0:success  1:type match fail 2: para calculate fail*/
    uint16         CRC;                    /*CRC*/
} SpModCnf_S;

/*PC_SP_CONNECT_REQ/MT_SP_CONNECT_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         connect;
    uint16         CRC;
}
SpPcConnect_S, SpMtConnect_S;

/*SP_PC_CONNECT_CNF/SP_MT_CONNECT_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         ready;
    uint16         CRC;
}
SpPcConCnf_S, SpMtConCnf_S;

/*SP_PC_KEY_REQ */
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         keytype;
    uint16         CRC;
} SpPckeyReq_S;

/*PC_SP_KEY_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         keytype;
    uint16         keyon;
    uint32         key;
    uint16         CRC;
} SpPckeyCnf_S;

/*SP_PC_UPDATEKEY_REQ */
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         writekey;
    uint16         keytype;
    uint16         keyon;
    uint32         key;
    uint16         CRC;
} SpPcUpdkeyReq_S;

/*PC_SP_UPDATEKEY_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;
    uint16         keytype;
    uint16         CRC;
} SpPcUpdkeyCnf_S;

/*PC_SP_READ_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         readkey;
    uint32         modul;
    uint16         CRC;
} SpPcRead_S;

/*MT_SP_READ_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         read;
    uint16         CRC;
} SpMtRead_S;

/*MT_SP_ADCAL_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         operate;
    uint16         checkitem;
    uint16         CRC;
} SpMtAd_S;

/*SP_MT_ADCAL_IND*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         checkitem;
    uint16         result;
    uint16         CRC;
} SpMtAdInd_S;

/*MT_SP_MAXVOL_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         operate;
    uint16         volgain;
    uint16         CRC;
} SpMtMaxvol_S;

/* the audio and alarm data*/
typedef struct
{
    uint16         datalength;
    uint16         datatype;
    uint8          data[900];
} Audio_S;

/*SP_PC_RDSYSET_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;      					        /* 1: success 0: fail */
    uint32         appver;                 /*app version*/
    uint8          serialnum[16];    /*product serial number*/
    uint8          protype[8];         /*product type*/
    uint16         freqscope;         /*freqency scope
                                                       1:136-150
                                                       2:150-174
                                                       3:400-470
                                                       4:400-425
                                                   */
    uint32         swver;              /*software version*/
    uint32         dataver;           /*data version*/
    uint8          pwson;                /*whether the powersave is on  0:off 1:on*/
    uint8          pws;                   /* the powersave time scale
                                                     0:invalid
                                                     1: 1:1
                                                     2: 1:2
                                                     3: 1:4
                                                    */
    uint8          tcomm;               /*this timer timeup,call is forbidden*/
    uint8          pretot;                /*pre-alert when tcomm is close*/
    uint8          trekey;               /*this timer timeup,key can been pressed again
                                                      after call is forbidden*/
    uint8          treset;                /*this timer timeup,system is reset after call is forbidden */
    uint8          whisperen;             /*whether the whisper is on  0:off 1:on */
    uint8          noisethd;               /* noise thrd*/
    uint8          voxlel;                     /*vox function level  0:off   1-5 : 1-5*/
    uint8          voxtime;                   /*vox delay time */
    uint8          voxcancel;                /*whether the vox is canceled after call which is actived by PTT finished*/
    uint8          voxforbid;                  /*whether the vox is forbidden when receiving*/
    uint8          keylock;                     /*whether the keylock is on   0:off 1-6:5-30s*/
    uint8          chanlock;                    /*whether the channellock function is on */
    uint8          vibrate;                     /*whether vibrate is on */
    uint8          toneen;                     /*whether audio is on */
    uint8          callouttone;              /*whether audio is on when make calls*/
    uint8          callintone;                /*whether audio is on when receive call*/
    uint8          smstone;                     /*whether audio is on when receive sms*/
    uint8          lowbattone;            /*whether audio is on when battery is low-power*/
    uint8          keytone;                 /*whether audio is on when key is pressed*/
    uint8          lightnoteen;	          /*led status*/
    uint8          backlightnote;          /*backlight status*/
    uint8          backlightdelay;         /*backlight delay*/
    uint8          idledisp;                   /* idle display*/
    uint8          dateen;                    /*whether date&clock is showed */
    uint32         msid;                        /*MS ID*/
    uint8          wildcarden;              /*whether *is supported*/
    uint8          manualdialen;          /*whether manual dial is supported*/
    uint8          pretxdelay;             /*delay before tx*/
    uint8          grphold;                 /*hold time when group call*/
    uint8          peerhold;               /*hold time when peer call*/
    uint8          kilen;                     /*whether can kill others*/
    uint8          activen;                 /*whether can active others*/
    uint8          rcen;                     /*whether can be killed&actived*/
    uint8          callallen;              /*whether can call all*/
    uint8          callgrpen;             /*whether can call group*/
    uint8          crtconten;            /*whether can create new contact*/
    uint8          editsmsen;           /*whether can edit sms*/
    uint8          emename[16];       /* emegency system name*/
    uint8          emetype;              /*emegency type 0: mute 1: normal 2:secret*/
    uint8          ememode;           /*emegency mode 0:eme  code 1:code + call 2: auto call*/
    uint16         emechannel;      /*change to the channel when make emegency call*/
    uint8          alarmtime;            /*alarm time*/
    uint8          emecalltime;            /*emegency call time*/
    uint8          michold;              /*duration of autocall  when mode is 2*/
    uint8          revhold;               /*duration of receive  when call is finished*/
    uint32         emeid;                 /* eme call id*/
    uint8          powlelmenu;       /*whether powerlevel  menu is on */
    uint8          keylockmenu;       /*whether keylock  menu is on */
    uint8          laumenu;              /*whether language setting menu is on */
    uint8          backlightmenu;      /*whether backlight setting menu is on */
    uint8          ledmenu;                 /*whether led setting menu is on */
    uint8          tonemenu;                /*whether audio setting menu is on */
    uint8          lumcmenu;               /*whether luminace menu is on*/
    uint8          smsmenu;                /*whether sms menu is on */
    uint8          noisemenu;              /*whether noise setting menu is on */
    uint8          pbdelmenu;              /*whether delete contact in phone book is on */
    uint8          scanmenu;                /*whether scan menu is on*/
    uint8          scancheckmenu;              /*whether check channel in scan list menu is on */
    uint8          scanaddtmpmenu;              /*whether add channel temp in scan list menu is on */
    uint8          scandeltmpmenu;              /*whether delete channel temp in scan list menu is on */
    uint8          scanaddmenu;              /*whether add channel in scan list menu is on */
    uint8          scandelmenu;              /*whether delete channel in scan list menu is on */
    uint8          voxmenu;                    /*whether vox setting menu is on */
    uint8          whispermenu;              /*whether whisper setting menu is on */
    uint8          vibratemenu;              /*whether vibrate setting menu is on */
    uint8          datemenu;                   /*whether date setting menu is on */
    uint8          mainmenuen;              /*whether main menu setting menu is on */
    uint8          pwsmenu;                   /*whether powersave setting menu is on */
    uint8          talkaroundmenu;        /*whether talk around setting menu is on*/
    uint8          pf1funcs;             /*PF1's function when short pressed*/
    uint8          pf1funcl;             /*PF1's function when long pressed*/
    uint8          pf2funcs;             /*PF2's function when short pressed*/
    uint8          pf2funcl;             /*PF2's function when long pressed*/
    uint8          topfuncs;            /*TOP's function when short pressed*/
    uint8          topfuncl;            /*TOP's function when long pressed*/
    uint8          menufunc;         /*Menu's function when long pressed*/
    uint8          backfunc;          /*back's function when long pressed*/
    uint8          inputfuncs;         /*input's function when short pressed*/
    uint8          inputfuncl;         /*input's function when long pressed*/
    uint8          switchfunc;         /*on&off's function when short pressed*/
    uint16         CRC;
} SpPcReadSyssetCnf_S;
/*SP_PC_RDZONE_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;      					        /* 1: success 0: fail */
    gZONE_S        zone[16];
    uint16         CRC;
} SpPcReadZoneCnf_S;

/*SP_PC_RDCHANNEL_CNF*/
typedef   struct
{
    uint16                   ReceiverMID;
    uint16                   SenderMID;
    uint16                   MsgTYPE;
    uint16                   MsgID;
    uint16                   MsgLen;
    uint32                   success;      					        /* 1: success 0: fail */
    uint16                   zonenum;
    gCHANNEL_S               chann[16];
    uint16                   CRC;
} SpPcReadChanCnf_S;

/*SP_PC_RDSCAN_CNF/SP_PC_RDCONTACT_CNF/SP_PC_RDGROUP_CNF/SP_PC_RDTEXT_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;      					        /* 1: success 0: fail */
    uint16         num;
    /* payload */
} SpPcReadScanCnf_S, SpPcReadContctCnf_S, SpPcReadGrpCnf_S, SpPcReadTxtCnf_S;

/*SP_MT_READ_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;
    uint16         BATLowThrd;
    uint16         TxVccn;
    uint16         Vox1open;
    uint16         Vox5open;
    uint16         maxvol;
    uint16         freqnum;
    PlCal_S        PlCal[5];
    uint16         CRC;
} SpMtReadCnf_S;

/*PC_SP_WTSYSSET_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         writekey;
    uint8          serialnum[16];    /*product serial number*/
    uint8          protype[8];         /*product type*/
    uint16         freqscope;         /*freqency scope
                                                       1:136-150
                                                       2:150-174
                                                       3:400-470
                                                       4:400-425
                                                   */
    uint32         swver;              /*software version*/
    uint32         dataver;           /*data version*/
    uint8          pwson;                /*whether the powersave is on  0:off 1:on*/
    uint8          pws;                   /* the powersave time scale
                                                     0:invalid
                                                     1: 1:1
                                                     2: 1:2
                                                     3: 1:4
                                                    */
    uint8          tcomm;               /*this timer timeup,call is forbidden*/
    uint8          pretot;                /*pre-alert when tcomm is close*/
    uint8          trekey;               /*this timer timeup,key can been pressed again
                                                      after call is forbidden*/
    uint8          treset;                /*this timer timeup,system is reset after call is forbidden */
    uint8          whisperen;             /*whether the whisper is on  0:off 1:on */
    uint8          noisethd;               /* noise thrd*/
    uint8          voxlel;                     /*vox function level  0:off   1-5 : 1-5*/
    uint8          voxtime;                   /*vox delay time */
    uint8          voxcancel;                /*whether the vox is canceled after call which is actived by PTT finished*/
    uint8          voxforbid;                  /*whether the vox is forbidden when receiving*/
    uint8          keylock;                     /*whether the keylock is on   0:off 1-6:5-30s*/
    uint8          chanlock;                    /*whether the channellock function is on */
    uint8          vibrate;                     /*whether vibrate is on */
    uint8          toneen;                     /*whether audio is on */
    uint8          callouttone;              /*whether audio is on when make calls*/
    uint8          callintone;                /*whether audio is on when receive call*/
    uint8          smstone;                     /*whether audio is on when receive sms*/
    uint8          lowbattone;            /*whether audio is on when battery is low-power*/
    uint8          keytone;                 /*whether audio is on when key is pressed*/
    uint8          lightnoteen;	          /*led status*/
    uint8          backlightnote;          /*backlight status*/
    uint8          backlightdelay;         /*backlight delay*/
    uint8          idledisp;                   /* idle display*/
    uint8          dateen;                    /*whether date&clock is showed */
    uint32         msid;                        /*MS ID*/
    uint8          wildcarden;              /*whether *is supported*/
    uint8          manualdialen;          /*whether manual dial is supported*/
    uint8          pretxdelay;             /*delay before tx*/
    uint8          grphold;                 /*hold time when group call*/
    uint8          peerhold;               /*hold time when peer call*/
    uint8          kilen;                     /*whether can kill others*/
    uint8          activen;                 /*whether can active others*/
    uint8          rcen;                     /*whether can be killed&actived*/
    uint8          callallen;              /*whether can call all*/
    uint8          callgrpen;             /*whether can call group*/
    uint8          crtconten;            /*whether can create new contact*/
    uint8          editsmsen;           /*whether can edit sms*/
    uint8          emename[16];       /* emegency system name*/
    uint8          emetype;              /*emegency type 0: mute 1: normal 2:secret*/
    uint8          ememode;           /*emegency mode 0:eme  code 1:code + call 2: auto call*/
    uint16         emechannel;      /*change to the channel when make emegency call*/
    uint8          alarmtime;            /*alarm time*/
    uint8          emecalltime;            /*emegency call time*/
    uint8          michold;              /*duration of autocall  when mode is 2*/
    uint8          revhold;               /*duration of receive  when call is finished*/
    uint32         emeid;                 /* eme call id*/
    uint8          powlelmenu;       /*whether powerlevel  menu is on */
    uint8          keylockmenu;       /*whether keylock  menu is on */
    uint8          laumenu;              /*whether language setting menu is on */
    uint8          backlightmenu;      /*whether backlight setting menu is on */
    uint8          ledmenu;                 /*whether led setting menu is on */
    uint8          tonemenu;                /*whether audio setting menu is on */
    uint8          lumcmenu;               /*whether luminace menu is on*/
    uint8          smsmenu;                /*whether sms menu is on */
    uint8          noisemenu;              /*whether noise setting menu is on */
    uint8          pbdelmenu;              /*whether delete contact in phone book is on */
    uint8          scanmenu;                /*whether scan menu is on*/
    uint8          scancheckmenu;              /*whether check channel in scan list menu is on */
    uint8          scanaddtmpmenu;              /*whether add channel temp in scan list menu is on */
    uint8          scandeltmpmenu;              /*whether delete channel temp in scan list menu is on */
    uint8          scanaddmenu;              /*whether add channel in scan list menu is on */
    uint8          scandelmenu;              /*whether delete channel in scan list menu is on */
    uint8          voxmenu;                    /*whether vox setting menu is on */
    uint8          whispermenu;              /*whether whisper setting menu is on */
    uint8          vibratemenu;              /*whether vibrate setting menu is on */
    uint8          datemenu;                   /*whether date setting menu is on */
    uint8          mainmenuen;              /*whether main menu setting menu is on */
    uint8          pwsmenu;                   /*whether powersave setting menu is on */
    uint8          talkaroundmenu;        /*whether talk around setting menu is on*/
    uint8          pf1funcs;             /*PF1's function when short pressed*/
    uint8          pf1funcl;             /*PF1's function when long pressed*/
    uint8          pf2funcs;             /*PF2's function when short pressed*/
    uint8          pf2funcl;             /*PF2's function when long pressed*/
    uint8          topfuncs;            /*TOP's function when short pressed*/
    uint8          topfuncl;            /*TOP's function when long pressed*/
    uint8          menufunc;         /*Menu's function when long pressed*/
    uint8          backfunc;          /*back's function when long pressed*/
    uint8          inputfuncs;         /*input's function when short pressed*/
    uint8          inputfuncl;         /*input's function when long pressed*/
    uint8          switchfunc;         /*on&off's function when short pressed*/
    uint16     	   CRC;
} SpPcWriteSysSet_S;

/*PC_SP_WTZONE_REQ*/
typedef   struct
{
    uint16              ReceiverMID;
    uint16              SenderMID;
    uint16              MsgTYPE;
    uint16              MsgID;
    uint16              MsgLen;
    uint32              writekey;
    gZONE_S             zone[16];
    uint16 	            CRC;
} SpPcWriteZone_S;

/*PC_SP_WTCHANNEL_REQ*/
typedef   struct
{
    uint16              ReceiverMID;
    uint16              SenderMID;
    uint16              MsgTYPE;
    uint16              MsgID;
    uint16              MsgLen;
    uint32              writekey;
    uint16              zonenum;
    gCHANNEL_S          chann[16];
    uint16 	            CRC;
} SpPcWriteChannl_S;

/*PC_SP_WTSCAN_REQ/PC_SP_WTCONTACT_REQ/PC_SP_WTGROUP_REQ/PC_SP_WTTEXT_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         writekey;
    uint16         num;
    /*payload*/
} SpPcWriteScan_S, SpPcWriteContct_S, SpPcWriteGrp_S, SpPcWriteTxt_S;

/*MT_SP_WRITE_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         write;
    uint16         BATLowThrd;
    uint16         TxVccn;
    uint16         Vox1open;
    uint16         Vox5open;
    uint16         maxvol;
    uint16         freqnum;
    PlCal_S        PlCal[5];
    uint16         CRC;
} SpMtWrite_S;

/*SP_PC_WRITE_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         module;    /* 1:sysset 2: zone 3-18:channel 19:scan 20:contact 21:group  22: text*/
    uint16         success;
    uint16         CRC;
} SpPcWriteCnf_S;

/*SP_MT_WRITE_CNF/SP_MT_EFFECT_CNF/SP_PC_EFFECT_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;
    uint16         CRC;
} SpMtWriteCnf_S, SpEffectCnf_S;

/*PC_SP_EFFECT_REQ/MT_SP_EFFECT_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         reset;
    uint16         CRC;
}
SpPcEffect_S, SpMtEffect_S;

/*DEBUG_SP_TEST_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         testlevel;
    uint16         CRC;
} SpDebug_S;

/*SP_DEBUG_GLB_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint8          Tsleep;            /*   sleep minimum time length*/
    uint8          testlev;           /* 0-5*/
    uint16         sleepstep;
    uint32         Tbtl;             /* check batterylife timer-- timer3 */
    uint16         TVol;             /* check volume timer -- timer2*/
    uint16         TRssi;            /*check rssi&busy  timer--timer3*/
    uint8          timer7on;
    uint8          timer8on;
    uint8          timer9on;
    uint8          alaon;
    uint8          pwsOn;            /*0: powersave off 1: powersave on*/
    uint8          pws;              /* whether other modules  can sleep  */
    uint16         freetime;
    uint8          sysready;             /* whether other modules is ready*/
    uint8          exitred;              /* the print level */
    uint8          Rssi;                 /*last  rssi*/
    uint8          Btl;                  /*last batterylife*/
    uint16         Vol;                  /*last volume*/
    uint16         ChanNum;              /*current channel number : 0-15*/
    uint16         chanumback;
    uint16         chanumtep;
    uint16         chanumalive;
    uint16         chanumcall;
    uint8          ScanTime;               /*scan time : 0-16*/
    uint8          ScanOn;                 /*whether scan is on*/
    uint8          ScanCall;
    uint8          ChCalStatus;       /*whether the mt parameter of channel is caculated*/
    uint8          ChaChOn;                /*whether is wait for CCL_SP_STOP_CNF*/
    uint8          schchgon;
    uint16         busyopen[10];
    uint16         busyclose[10];
    uint16         btlTh;                   /*the low level batterylife thrd*/
    uint16         callon;
    uint16         sendchange;
    uint8          waitslp;
    uint8          RcStatus;                /*whether ms is active  0: killed 1: active*/
    uint16         CRC;
} SpGlb_S;

/*DEBUG_SP_RDGLB_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         Glbkey;
    uint16         module;
    uint16         CRC;
} DebugReadGlbReq_S;

/*SP_DEBUG_RDSYSGLB_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         success;
    uint8          Workmode;     /*system mode 0:res 1:digtal 2: analog 3:dual*/
    uint8          RCStatus;     /*whether ms is active*/
    uint8          EnKilled;     /*whether can been killed*/
    uint8          EnActived;    /*whether can been actived*/
    uint32         MtKey;        /*MT key*/
    uint8          MicGainHigh;
    uint8          MicGainLow;
    uint16         Spklev[15];
    uint8          SpkGain[16];
    uint16         BtlLev[4];
    uint16         VoxLev[5];
    uint32         TxCC[16][16];     /*channel tx color code  */
    uint32         RxCC[16][16];    /*channel rx color code  */
    uint8          ChCalStatus;
    uint8          VolLevel;
    uint8          CurZoneNum;
    uint8          CurChanNum;
    uint8          PerSZoneNum;
    uint8          PerSChanNum;
    uint8          Sreseve;
    uint16         BATLowThrd;
    uint16         TxVccn;
    uint16         Vox1open;
    uint16         Vox5open;
    uint16         maxvol;
    uint16         freqnum;
    PlCal_S        PlCal[5];
    uint16         sleepstep;
    uint8          tsleep;
    uint8          tbtl;
    uint8          tvol;
    uint8          trssi;
    uint32         refrcc[16];
    uint8          bTack;              /* T_ACK */
    uint8          btalarm;
    uint16         wTTxwait;          /* Tx_wait:
    										                        0000: 	       No Time
											                    0001:         40ms
												                0010:         80ms
												                0011:         160ms
												                0100:         320ms
												                other:        Reserve
										                      */
    uint8          bNumRep;            /*NUM_REP*/
    uint8          bNumData;           /*NUM_DATA*/
    uint8          bNumStatus;         /*NUM_STATUS*/
    uint8          bNumbusy;
    uint8          bTbusy;
    uint8          bheadcnt;
    uint16         wTRsp;              /*T_RSP*/

    uint16         wTsync;              /*T_SYNC*/
    uint32         Uart2Baudrate;
    uint32         RfVcoRfin;
    uint16         RfVcoRefer;
    uint16         RfVcoPreDiv;
    uint16         RfVcoCurSet;
    uint16         RfVcoMuxOut;
    uint16         RfDelay5TOn;
    uint16         RfDelay5TOff;
    uint16         RfDelay5ROn;
    uint16         RfDelay5ROff;
    uint16         RfDelay5COn;
    uint16         RfDelay5COff;
    uint16         RfDelayTxOn;
    uint16         RfDelayTxOff;
    uint16         RfDelayRxOn;
    uint16         RfDelayRxOff;
    uint16         RfDelayPaOn;
    uint16         RfDelayPaOff;
    uint16         RfDelayPllTROn;
    uint16         RfDelayPllTROff;
    uint16         RfDelayTxVco;
    uint16         RfDelayRxVco;
    uint16         SpchDelaySpkOn;
    uint16         SpchDelaySpkOff;
    uint16         SpchDelayAmpOn;
    uint16         SpchDelayAmpOff;
    uint16         SpchDelayMicOn;
    uint16         SpchDelayMicOff;
    uint16         SpchDelayMuteOn;
    uint16         SpchDelayMuteOff;
    uint16         SpchDelaySleep;
    uint16         SpchDelayWake;
    uint16         adamp;
    uint16         affactr;
    uint32         spechengain;
    uint8          digsegon;
    uint8          anasegon;
    uint16         prembllen;
    uint16         CRC;
} SpReadSysGlbCnf_S;

/*SP_DEBUG_RDCHCALGLB_CNF*/
typedef   struct
{
    uint16                ReceiverMID;
    uint16                SenderMID;
    uint16                MsgTYPE;
    uint16                MsgID;
    uint16                MsgLen;
    uint32                success;
    SpMtChaCalc_S         chalc[16][16];
    uint16                CRC;
} SpReadChlGlbCnf_S;

/*DEBUG_SP_WTSYSGLB_REQ*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint32         glbkey;
    uint8          Workmode;     /*system mode 0:res 1:digtal 2: analog 3:dual*/
    uint8          RCStatus;     /*whether ms is active*/
    uint8          EnKilled;     /*whether can been killed*/
    uint8          EnActived;    /*whether can been actived*/
    uint32         MtKey;        /*MT key*/
    uint8          MicGainHigh;
    uint8          MicGainLow;
    uint16         Spklev[15];
    uint8          SpkGain[16];
    uint16         BtlLev[4];
    uint16         VoxLev[5];
    uint32         TxCC[16][16];     /*channel tx color code  */
    uint32         RxCC[16][16];    /*channel rx color code  */
    uint8          ChCalStatus;
    uint8          VolLevel;
    uint8          CurZoneNum;
    uint8          CurChanNum;
    uint8          PerSZoneNum;
    uint8          PerSChanNum;
    uint8          Sreseve;
    uint16         BATLowThrd;
    uint16         TxVccn;
    uint16         Vox1open;
    uint16         Vox5open;
    uint16         maxvol;
    uint16         freqnum;
    PlCal_S        PlCal[5];
    uint16         sleepstep;
    uint8          tsleep;
    uint8          tbtl;
    uint8          tvol;
    uint8          trssi;
    uint32         refrcc[16];
    uint8          bTack;              /* T_ACK */
    uint8          btalarm;
    uint16         wTTxwait;          /* Tx_wait:
    										                        0000: 	       No Time
											                    0001:         40ms
												                0010:         80ms
												                0011:         160ms
												                0100:         320ms
												                other:        Reserve
										                      */
    uint8          bNumRep;            /*NUM_REP*/
    uint8          bNumData;           /*NUM_DATA*/
    uint8          bNumStatus;         /*NUM_STATUS*/
    uint8          bNumbusy;
    uint8          bTbusy;
    uint8          bheadcnt;
    uint16         wTRsp;              /*T_RSP*/

    uint16         wTsync;              /*T_SYNC*/
    uint32         Uart2Baudrate;
    uint32         RfVcoRfin;
    uint16         RfVcoRefer;
    uint16         RfVcoPreDiv;
    uint16         RfVcoCurSet;
    uint16         RfVcoMuxOut;
    uint16         RfDelay5TOn;
    uint16         RfDelay5TOff;
    uint16         RfDelay5ROn;
    uint16         RfDelay5ROff;
    uint16         RfDelay5COn;
    uint16         RfDelay5COff;
    uint16         RfDelayTxOn;
    uint16         RfDelayTxOff;
    uint16         RfDelayRxOn;
    uint16         RfDelayRxOff;
    uint16         RfDelayPaOn;
    uint16         RfDelayPaOff;
    uint16         RfDelayPllTROn;
    uint16         RfDelayPllTROff;
    uint16         RfDelayTxVco;
    uint16         RfDelayRxVco;
    uint16         SpchDelaySpkOn;
    uint16         SpchDelaySpkOff;
    uint16         SpchDelayAmpOn;
    uint16         SpchDelayAmpOff;
    uint16         SpchDelayMicOn;
    uint16         SpchDelayMicOff;
    uint16         SpchDelayMuteOn;
    uint16         SpchDelayMuteOff;
    uint16         SpchDelaySleep;
    uint16         SpchDelayWake;
    uint16         adamp;
    uint16         affactr;
    uint32         spechengain;
    uint8          digsegon;
    uint8          anasegon;
    uint16         prembllen;
    uint16         CRC;
} DebugWriteSysGlbReq_S;

/*DEBUG_SP_WTCHLCALGLB_REQ*/
typedef   struct
{
    uint16               ReceiverMID;
    uint16               SenderMID;
    uint16               MsgTYPE;
    uint16               MsgID;
    uint16               MsgLen;
    uint32               glbkey;
    SpMtChaCalc_S        chalc[16][16];
    uint16               CRC;
} DebugWriteChlGlbReq_S;

/*SP_DEBUG_WTGLB_CNF*/
typedef   struct
{
    uint16         ReceiverMID;
    uint16         SenderMID;
    uint16         MsgTYPE;
    uint16         MsgID;
    uint16         MsgLen;
    uint16         success;
    uint16         module;
    uint16         CRC;
} SpWriteGlbCnf_S;

/*sysglb parameter*/
typedef   struct
{
    uint8          Workmode;     /*system mode 0:res 1:digtal 2: analog 3:dual*/
    uint8          RCStatus;     /*whether ms is active*/
    uint8          EnKilled;     /*whether can been killed*/
    uint8          EnActived;    /*whether can been actived*/
    uint32         MtKey;        /*MT key*/
    uint8          MicGainHigh;
    uint8          MicGainLow;
    uint16         Spklev[15];
    uint8          SpkGain[16];
    uint16         BtlLev[4];
    uint16         VoxLev[5];
    uint32         TxCC[16][16];     /*channel tx color code  */
    uint32         RxCC[16][16];    /*channel rx color code  */
    uint8          ChCalStatus;
    uint8          VolLevel;
    uint8          CurZoneNum;
    uint8          CurChanNum;
    uint8          PerSZoneNum;
    uint8          PerSChanNum;
    uint8          Sreseve;
    uint16         BATLowThrd;
    uint16         TxVccn;
    uint16         Vox1open;
    uint16         Vox5open;
    uint16         maxvol;
    uint16         freqnum;
    PlCal_S        PlCal[5];
    uint16         sleepstep;
    uint8          tsleep;
    uint8          tbtl;
    uint8          tvol;
    uint8          trssi;
    uint32         refrcc[16];
    uint8          bTack;              /* T_ACK */
    uint8          btalarm;
    uint16         wTTxwait;          /* Tx_wait:
    										                        0000: 	       No Time
											                    0001:         40ms
												                0010:         80ms
												                0011:         160ms
												                0100:         320ms
												                other:        Reserve
										                      */
    uint8          bNumRep;            /*NUM_REP*/
    uint8          bNumData;           /*NUM_DATA*/
    uint8          bNumStatus;         /*NUM_STATUS*/
    uint8          bNumbusy;
    uint8          bTbusy;
    uint8          bheadcnt;
    uint16         wTRsp;              /*T_RSP*/

    uint16         wTsync;              /*T_SYNC*/
    uint32         Uart2Baudrate;
    uint32         RfVcoRfin;
    uint16         RfVcoRefer;
    uint16         RfVcoPreDiv;
    uint16         RfVcoCurSet;
    uint16         RfVcoMuxOut;
    uint16         RfDelay5TOn;
    uint16         RfDelay5TOff;
    uint16         RfDelay5ROn;
    uint16         RfDelay5ROff;
    uint16         RfDelay5COn;
    uint16         RfDelay5COff;
    uint16         RfDelayTxOn;
    uint16         RfDelayTxOff;
    uint16         RfDelayRxOn;
    uint16         RfDelayRxOff;
    uint16         RfDelayPaOn;
    uint16         RfDelayPaOff;
    uint16         RfDelayPllTROn;
    uint16         RfDelayPllTROff;
    uint16         RfDelayTxVco;
    uint16         RfDelayRxVco;
    uint16         SpchDelaySpkOn;
    uint16         SpchDelaySpkOff;
    uint16         SpchDelayAmpOn;
    uint16         SpchDelayAmpOff;
    uint16         SpchDelayMicOn;
    uint16         SpchDelayMicOff;
    uint16         SpchDelayMuteOn;
    uint16         SpchDelayMuteOff;
    uint16         SpchDelaySleep;
    uint16         SpchDelayWake;
    uint16         adamp;
    uint16         affactr;
    uint32         spechengain;
    uint8          digsegon;
    uint8          anasegon;
    uint16         prembllen;
} SysGlbReq_S;


/*******************************************************************************
                Function Declarations
*******************************************************************************/
extern void32 SPProcess(uint16 MsgId, void32 *pMsgBody, uint16 wMsgLen);
extern void32 SPMsgProc(uint16 MsgId, void32 *pMsgBody, uint16 wMsgLen);
extern void32 SPTestProc(uint16 MsgId, void32 *pMsgBody, uint16 wMsgLen);
extern void32 SPMaintenProc(uint16 MsgId, void32 *pMsgBody, uint16 wMsgLen);
extern void32 SPSysInit(void32);
extern void32 SPGlbInit(void32);
extern void32 SPGetAppVer(void32 *pMsg);
extern void32 SPSysExit(void32);
extern void32 SPLcdExit(void32);
extern void32 SPChannelUpd(uint8 succ);
extern void32 SPChannelChg(void32 *pMsg);
extern void32 SPChannelSet(void32 *pMsg);
extern void32 SPChannelRenew(void32 *pMsg);
extern void32 SPStop(void32);
extern void32 SPSchChg(uint8 schzone, uint8 schchan);
extern void32 SPSchScan(void32);
extern void32 SPScanSet(void32 *pMsg);
extern void32 SPScan(uint8 scantime);
extern void32 SPScanCancel(void32 *pMsg);
extern void32 SPScanOpt(void32 *pMsg);
extern void32 SPScanInd(uint8  scanind);
extern void32 SPScanChanCheck(void32);
extern void32 SPScanChanCalc(void32);
extern void32 SPGetChan(void32);
extern void32 SPFailInd(uint8 operate);
extern void32 SPVolUpd(void32);
extern void32 SPVolSet(void32 *pMsg);
extern void32 SPMaxpwSet(void32 *pMsg);
extern void32 SPNoiseSet(void32 *pMsg);
extern void32 SPWhisperReq(void32 *pMsg);
extern void32 SPSpeechEnReq(void32 *pMsg);
extern void32 SPSpeechEnCnf(void32 *pMsg);
extern void32 SPVoiceKeyReq(void32 *pMsg);
extern void32 SPVoiceKeyCnf(void32 *pMsg);
extern void32 SPPwsOnSet(void32 *pMsg);
extern void32 SPAlarmStop(void32);
extern void32 SPAlarmPlay(void32);
extern void32 SPAudioSet(void32 *pMsgBody);
extern void32 SPAudioInd(void32 *pMsg);
extern void32 SPPwsCtrl(void32 *pMsg);
extern void32 SPCclSwOnReq(void32);
extern void32 SPCclStateReq(uint16 state);
extern void32 SPMmiSwOnReq(uint16 sta);
extern void32 SPMmiStateReq(uint16 state);
extern void32 SPSleep(void32);
extern void32 SPPolite(void32);
extern void32 SPRxOpt(uint8  opt);
extern void32 SPRxReq(uint8 rxind);
extern void32 SPSleepPre(void32);
extern void32 SPStart(void32 *pMsg);
extern void32 SPclearParaProc(void32);
extern void32 SPResendCall(void32);
extern void32 SPBusyRead(void32);
extern void32 SPBusyInd(uint8 busyind);
extern void32 SPResetCh(void32 *pMsg);
extern uint8  SPResetCalc(uint16 mod);
extern void32 SPMakeCallPre(void32 *pContext);
extern void32 SPMakeCallReq(void32);
extern void32 SPDisconnectCallReq(void32 *pContext);
extern void32 SPAlarmPre(void32 *pContext, uint16 RealLength);
extern void32 SPAlarmReq(void32);
extern void32 SPCallInd(void32 *pContext);
extern void32 SPCallCnf(void32 *pContext);
extern void32 SPCallFail(uint8 mode, uint8 failcause);
extern void32 SPHoldInd(void32 *pContext);
extern void32 SPHoldCancel(void32 *pContext);
extern void32 SPBackReq(void32 *pContext);
extern void32 SPNoteInd(void32 *pContext);
extern void32 SPAlarmInd(void32 *pContext);
extern void32 SPSendSmReq(void32);
extern void32 SPSendFmReq(void32);
extern void32 SPDataInd(void32 *pContext);
extern void32 SPStatusReq(void32);
extern void32 SPStatusCnf(void32 *pMsgBody);
extern void32 SPRcReq(void32);
extern void32 SPRcCnf(void32 *pMsgBody);
extern void32 SPRcInd(void32 *pMsgBody);
extern void32 SPServiceInd(void32 *pContext);
extern uint8 SPGroupCallJudge(uint32 callid);
extern void32 SPServiceSend(void32 *pContext, uint16 RealLength, uint8 mode);
extern void32 SPSendOverInd(void32 *pContext);
extern void32 SPDebug(void32 *pMsg);
extern void32 SPPrintfGlb(void32);
extern void32 SPReadGlb(void32 *pMsgBody);
extern void32 SPWriteSysGlb(void32 *pMsgBody);
extern void32 SPWriteChlGlb(void32 *pMsgBody);
extern void32 SPWfConnect(void32 *pMsgBody);
extern void32 SPWfKey(void32 *pMsgBody);
extern void32 SPWfUptKey(void32 *pMsgBody);
extern void32 SPWfRead(void32 *pMsgBody);
extern void32 SPWfReadSysSet(uint8 keymat);
extern void32 SPWfReadZone(uint8 keymat);
extern void32 SPWfReadChan(uint8 number, uint8 keymat);
extern void32 SPWfReadScan(uint8 keymat);
extern void32 SPWfReadContct(uint8 keymat);
extern void32 SPWfReadGrp(uint8 keymat);
extern void32 SPWfReadTxt(uint8 keymat);
extern void32 SPWfWriteSysSet(void32 *pMsgBody);
extern void32 SPWfWriteZone(void32 *pMsgBody);
extern void32 SPWfWriteChan(void32 *pMsgBody);
extern void32 SPWfWriteScan(void32 *pMsgBody);
extern void32 SPWfWriteContct(void32 *pMsgBody);
extern void32 SPWfWriteGrp(void32 *pMsgBody);
extern void32 SPWfWriteTxt(void32 *pMsgBody);
extern void32 SPWfReset(void32 *pMsgBody);
extern void32 SPMmiStateCnf(void32 *pMsgBody);
extern void32 SPCclStateCnf(void32 *pMsgBody);
extern void32 SPResetCnf(uint8 ind);
extern void32 SPMTConnect(void32 *pMsgBody);
extern void32 SPMTRead(void32 *pMsgBody);
extern void32 SPMTReadAd(void32 *pMsgBody);
extern void32 SPMTVol(void32 *pMsgBody);
extern void32 SPMTWrite(void32 *pMsgBody);
extern void32 SPMTReset(void32 *pMsgBody);
extern void32 SPRssiUpd(void32);
extern uint8  SPWriteGp(void32);
extern uint8  SPWritePara(void32);
extern void32 SPChCalc(void32);
extern void32 SPBTLUpd(void32);
extern uint8  SPTXBTLUpd(void32);
extern uint16 SPBTLAvg(uint16 value);
extern void32 SPChlBusy(void32 *pMsgBody);
extern uint8  SPCalc(uint16 value, uint8 type);
extern uint8  SPGainCalc(uint8 value, uint8 type);
extern void32 ADRVReset(void32);

/*******************************************************************************
                                Global Variables
*******************************************************************************/

extern uint8     gSPTSleep;
extern uint8     gSPAlaOn;
extern uint16    gSPSleepStep;
extern uint32    gSPTbtl;
extern uint16    gSPTVol;
extern uint16    gSPTRssi;
extern uint16    gSPTBusy;
extern uint8     gSPTimer7On;
extern uint8     gSPTimer8On;
extern uint8     gSPTimer9On;
extern uint8     gSPTimer12On;
extern uint8     gSPPws;
extern uint16    gSPFree;
extern uint8     gSPSysready;
extern uint8     gSPSysExit;
extern uint8     gSPTestLev;
extern uint8     gSPRssi;
extern uint8     gSPBtl;
extern uint8     gSPTempZone;
extern uint8     gSPAliveZone;
extern uint8     gSPCallZone;
extern uint8     gSPTempChan;
extern uint8     gSPAliveChan;
extern uint8     gSPCallChan;
extern uint8     gSPScanTime;
extern uint8     gSPScanCall;
extern uint8     gSPReChgOn;
extern uint8     gSPChaChOn;
extern uint8     gSPSchChgOn;
extern uint8     gSPScanlist[SP_SCANNUM];
extern uint8     gSPScanlistnum;
extern uint8     gSPTalkArouOn;
extern uint8     gSPWaitSlp;
extern uint8     gSPCallBackCh;
extern uint16    gSPbtlTh;
extern uint16    gSPVccn;
extern uint8     gSPChlOptOn;
extern uint8     gSPSaveOn;
extern uint16    gSPPerBtl[SP_BTLNUM];
extern uint16    gSPTxlowBtl;
extern uint8     gSPLowBtlCout;
extern uint8     gSPLowBtlTime;
extern uint8     gSPLowBtlTxTime;
extern uint8     gSPTimer11On;
extern uint8     gSPState;
extern uint8     gSPMode;
extern uint8     gSPRstOn;
extern uint8     gSPSwType;
extern uint8     gSPChBusy;
extern uint8     gSPRxImdInd;
extern uint8     gSPBusyCloseNum;
extern uint8     gSPBusyNUM;
extern uint8     gSPStartInd;
extern uint8     gSPBusyNUMTh;
extern uint8     gSPTBusyIND;
extern uint8     gSPSendAllow;
extern uint8     gSPSendOverInd;
extern uint8     gSPRFOpenOn;
extern uint8     gSPRFInd;
extern uint8     gSPEP;
extern uint8     gSPMsgBuff[SP_BUFF_LENGTH];
extern uint8     gSPMsgBuffOn;
extern uint8     gSPFirstLowBtl;
extern uint16    gSPSEBackup;
extern uint8     gSPCallOn;
extern uint8     gSPVoiceKeyOnBackup;
extern uint32    gSPVoiceKeyBackup;
extern uint16    gSPCallType;
extern uint32     gSPAppVer;
#pragma pack(pop)//恢复对齐状态
#endif  /* _SPSTRUCT_H_ */

