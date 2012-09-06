
/*******************************************************************************
File Name: sysmsgdef.h

Description: This file contains the message definition.

Copyright:
    Copyright(c) 2011 LinkTop technologies Co., LTD. All rights reserved.

Change History:
2011-03-25  wangjl    v0.0.0.1  Create
2011-05-06  wangjl    v0.0.1.0  Check and release after function test
2011-09-05  wangjl    v1.0.0.1  modify to follow the function defintion of V1.1
2012-02-15  wengt     v1.1.0.1  modify to follow the function defintion of V1.2
*******************************************************************************/
#ifndef _MESSAGEDEF_H
#define _MESSAGEDEF_H

/**************************************************************************
 *                        Signaling Message ID                         *
 **************************************************************************/

/*******OSE TIMER****************/
#define     EV_TIMER1EVENT          200
#define     EV_TIMER2EVENT          201
#define     EV_TIMER3EVENT          202
#define     EV_TIMER4EVENT          203
#define     EV_TIMER5EVENT          204
#define     EV_TIMER6EVENT          205
#define     EV_TIMER7EVENT          206
#define     EV_TIMER8EVENT          207
#define     EV_TIMER9EVENT          208
#define     EV_TIMER10EVENT         209
#define     EV_TIMER11EVENT         210
#define     EV_TIMER12EVENT         211
#define     EV_TIMER13EVENT         212
#define     EV_TIMER14EVENT         213
#define     EV_TIMER15EVENT         214
#define     EV_TIMER16EVENT         215

/*******MMI&SP****************/
#define     MMI_SP_VOICE_REQ                        260
#define     SP_MMI_VOICE_IND                        261

#define     MMI_SP_DISCONNECT_REQ                   262
#define     SP_MMI_DISCONNECT_IND                   263

#define     MMI_SP_SMS_REQ                          264
#define     MMI_SP_FM_REQ                           265
#define     SP_MMI_DATA_IND                         266

#define     MMI_SP_STATUS_REQ                       267
#define     SP_MMI_STATUS_CNF                       268

#define     MMI_SP_RC_REQ                           269
#define     SP_MMI_RC_CNF                           270
#define     SP_MMI_RC_IND                           271

#define     MMI_SP_ALARM_REQ                        272
#define     SP_MMI_ALARM_IND                        273

#define     SP_MMI_HOLD_IND                         274
#define     MMI_SP_HOLD_CANCEL_REQ                  275

#define     SP_MMI_TOTNOTE_IND                      276

#define     MMI_SP_BACK_REQ                         277

/*******SP&CCL****************/
#define     SP_CCL_SETUP_REQ                        320
#define     CCL_SP_SETUP_IND                        321
#define     CCL_SP_DATA_IND                         322
#define     CCL_SP_STATUS_CNF                       323

#define     SP_CCL_END_REQ                          324
#define     CCL_SP_BREAK_CNF                        325

#define     SP_CCL_RC_REQ                           326
#define     CCL_SP_RC_CNF                           327
#define     CCL_SP_RC_IND                           328

#define     SP_CCL_ALARM_REQ                        329
#define     CCL_SP_ALARM_IND                        330
#define     SP_CCL_ALARM_CANCEL_REQ                 331

#define     CCL_SP_HOLD_IND                         332
#define     SP_CCL_HOLD_CANCEL_REQ                  333

#define     CCL_SP_TOTNOTE_IND                      334

#define     SP_CCL_BACK_REQ                         335
#define     CCL_SP_SERVICE_IND                      336
#define     CCL_SP_SEND_OVER_IND                    337

/*******CCL&DLL****************/
#define     CCL_DLL_SETUP_REQ                       375
#define     CCL_DLL_SETUP_RSP                       376
#define     CCL_DLL_STATUS_RSP                      377

#define     CCL_DLL_START_REQ                       378
#define     CCL_DLL_STOP_REQ                        379

#define     CCL_DLL_HEAD_REQ                        380
#define     DLL_CCL_HFRAME_IND                      381

#define     CCL_DLL_VOICE_REQ                       382
#define     DLL_CCL_FCCH_IND                        383
#define     DLL_CCL_CCCH_IND                        384

#define     CCL_DLL_DATA1_REQ                       385
#define     CCL_DLL_DATA2_REQ                       386
#define     DLL_CCL_FCCHD_IND                       387
#define     DLL_CCL_CCCHD_IND                       388

#define     CCL_DLL_HD3_REQ                         389
#define     DLL_CCL_HD3_IND                         390
#define     CCL_DLL_DATA3_REQ                       391
#define     DLL_CCL_DATA3_IND                       392
#define     CCL_DLL_DATA_RSP                        393
#define     CCL_DLL_BREAK_REQ                       394
#define     CCL_DLL_END_REQ                         395
#define     DLL_CCL_EFRAME_IND                      396

#define     DLL_CCL_MSG_CNF                         397

/*******CCL&PL****************/
#define     CCL_PL_ACALL_SETUP_REQ                  445
#define     CCL_PL_ACALL_END_REQ                    446

#define     PL_CCL_ACALL_CONNECT_IND                447
#define     PL_CCL_TAIL_VOICE_IND                   448

#define     CCL_PL_DTMF_VALUE_IND                   449
#define     PL_CCL_DTMF_VALUE_IND                   450

#define     PL_CCL_SEND_OVER_IND                    451
#define     CCL_PL_STOP_REQ                         452

/*******DLL&PL****************/
#define     DLL_PL_FRAME_REQ                        490
#define     PL_DLL_HFRAME_IND                       491
#define     PL_DLL_EFRAME_IND                       492
#define     PL_DLL_FCCH_IND                         493
#define     PL_DLL_CCCH_IND                         494
#define     PL_DLL_DATA3_IND                        495
#define     PL_DLL_HD3_IND                          496

/**************************************************************************
 *                        O&M Message ID                                  *
 **************************************************************************/

/*******MMI&SP****************/
#define     SP_MMI_INIT_REQ                         4100
#define     MMI_SP_INIT_CNF                         4101

#define     SP_MMI_POWEROFF_REQ                     4102
#define     MMI_SP_POWEROFF_CNF                     4103

#define     MMI_SP_CHCHG_REQ                        4104
#define     SP_MMI_CHCHG_IND                        4105

#define     MMI_SP_SCAN_REQ                         4106
#define     MMI_SP_SCAN_CANCEL_REQ                  4107
#define     MMI_SP_SCAN_OPT_REQ                     4108
#define     SP_MMI_SCAN_IND                         4109
#define     SP_MMI_FAIL_IND                         4110

#define     MMI_SP_AUDIO_REQ                        4111
#define     SP_MMI_AUDIO_IND                        4112

#define     MMI_SP_VOL_REQ                          4113
#define     SP_MMI_VOL_IND                          4114

#define     MMI_SP_MAXPW_REQ                        4115
#define     MMI_SP_NOISE_REQ                        4116
#define     MMI_SP_WHISPER_REQ                      4117
#define     MMI_SP_PWSON_REQ                        4118

#define     SP_MMI_RSSI_IND                         4119
#define     SP_MMI_BUSY_IND                         4120
#define     SP_MMI_BTL_IND                          4121
#define     SP_MMI_MIC_IND                          4122
#define     SP_MMI_CHARGE_IND                       4123

#define     SP_MMI_SWCONNET_IND                     4124

#define     MMI_SP_RESETCH_REQ                      4125
#define     SP_MMI_RESETCH_CNF                      4126

#define     MMI_SP_RESETSYS_REQ                     4127

#define     SP_MMI_EXIT_REQ                         4128
#define     MMI_SP_EXIT_CNF                         4129

#define     MMI_SP_SLEEP_REQ                        4130
#define     SP_MMI_WK_IND                           4131

#define     SP_MMI_STATE_REQ                        4132
#define     MMI_SP_STATE_CNF                        4133

#define     MMI_SP_SPEECHEN_REQ                     4134
#define     SP_MMI_SPEECHEN_CNF                     4135

#define     MMI_SP_VOCKEY_REQ                       4136
#define     SP_MMI_VOCKEY_CNF                       4137

/*******SP&CCL****************/
#define     SP_CCL_INIT_REQ                         4176
#define     CCL_SP_INIT_CNF                         4177

#define     SP_CCL_POWEROFF_REQ                     4178
#define     CCL_SP_POWEROFF_CNF                     4179

#define     SP_CCL_STOP_REQ                         4180
#define     CCL_SP_STOP_CNF                         4181

#define     SP_CCL_RXSTART_REQ                      4182
#define     CCL_SP_RXSTART_IND                      4183
#define     SP_CCL_RXSTOP_REQ                       4184
  
#define     SP_CCL_STATE_REQ                        4185
#define     CCL_SP_STATE_CNF                        4186

#define     SP_CCL_PWSON_REQ                        4187

#define     SP_CCL_NOISE_REQ                        4188

#define     SP_CCL_PCCONNECT_REQ                    4189

#define     CCL_SP_SEND_IND                         4190

/*******SP&DLL****************/
#define     SP_DLL_INIT_REQ                         4235
#define     DLL_SP_INIT_CNF                         4236

/*******SP&PL****************/
#define     SP_PL_INIT_REQ                          4285
#define     PL_SP_INIT_CNF                          4286

/*******SP&SCH****************/
#define     SP_SCH_INIT_REQ                         4335
#define     SCH_SP_INIT_CNF                         4336

#define     SP_SCH_POWEROFF_REQ                     4337
#define     SCH_SP_POWEROFF_CNF                     4338

#define     SP_SCH_CHCHG_REQ                        4339
#define     SCH_SP_CHCHG_CNF                        4340

#define     SP_SCH_SLEEP_REQ                        4341
#define     SCH_SP_SLEEP_CNF                        4342

#define     SP_SCH_AUDIO_REQ                        4343
#define     SCH_SP_AUDIO_IND                        4344

#define     SP_SCH_MAXPW_REQ                        4345
#define     SP_SCH_VOL_REQ                          4346
#define     SP_SCH_PWSON_REQ                        4347

#define     SP_SCH_MIC_IND                          4348
#define     SP_SCH_MICGAIN_REQ                      4349
#define     SP_SCH_ANASIGSET_REQ                    4350

#define     SP_SCH_RXSTART_REQ                      4351
#define     SP_SCH_RXSTOP_REQ                       4352

#define     SP_SCH_RXRFOPEN_REQ                     4353
#define     SCH_SP_RXRFOPEN_CNF                     4354

#define     SP_SCH_SPEECHEN_REQ                     4355
#define     SCH_SP_SPEECHEN_CNF                     4356

#define     SP_SCH_VOCKEY_REQ                       4357
#define     SCH_SP_VOCKEY_CNF                       4358

/*******SP&ZSPDD****************/
#define     SP_ZSPDD_INIT_REQ                       4395
#define     ZSPDD_SP_INIT_CNF                       4396

/*******SP&ARMDD****************/
#define     ARMDD_SP_FEEDDOG_REQ                    4445
#define     ARMDD_SP_STARTUP_REQ                    4446
#define     ARMDD_SP_SET_TIMER5                     4447
#define     ARMDD_SP_POWEROFF_REQ                   4448
#define     ARMDD_SP_EXIT_REQ                       4449

/*******SP&PC****************/
#define     PC_SP_CONNECT_REQ                       4495
#define     SP_PC_CONNECT_CNF                       4496

#define     PC_SP_KEY_REQ                           4497
#define     SP_PC_KEY_CNF                           4498

#define     PC_SP_UPDATEKEY_REQ                     4499
#define     SP_PC_UPDATEKEY_CNF                     4500

#define     PC_SP_EFFECT_REQ                        4501
#define     SP_PC_EFFECT_CNF                        4502

#define     PC_SP_WTSYSSET_REQ                      4503
#define     PC_SP_WTZONE_REQ                        4504
#define     PC_SP_WTCHANNEL_REQ                     4505
#define     PC_SP_WTSCAN_REQ                        4506
#define     PC_SP_WTCONTACT_REQ                     4507
#define     PC_SP_WTGROUP_REQ                       4508
#define     PC_SP_WTTEXT_REQ                        4509
#define     SP_PC_WRITE_CNF                         4510

#define     PC_SP_READ_REQ                          4511
#define     SP_PC_RDSYSSET_CNF                      4512
#define     SP_PC_RDZONE_CNF                        4513
#define     SP_PC_RDCHANNEL_CNF                     4514
#define     SP_PC_RDSCAN_CNF                        4515
#define     SP_PC_RDCONTACT_CNF                     4516
#define     SP_PC_RDGROUP_CNF                       4517
#define     SP_PC_RDTEXT_CNF                        4518

/*******SP&MT****************/
#define     MT_SP_CONNECT_REQ                       4550
#define     SP_MT_CONNECT_CNF                       4551

#define     MT_SP_READ_REQ                          4552
#define     SP_MT_READ_CNF                          4553

#define     MT_SP_WRITE_REQ                         4554
#define     SP_MT_WRITE_CNF                         4555

#define     MT_SP_ADCAL_REQ                         4556
#define     SP_MT_ADCAL_IND                         4557

#define     MT_SP_MAXVOL_REQ                        4558

#define     MT_SP_EFFECT_REQ                        4559
#define     SP_MT_EFFECT_CNF                        4560

/*******SCH&MT****************/
#define     MT_SCH_ANA_FREQCAL_REQ                  4600
#define     MT_SCH_ANA_FREQCAL_STOP                 4601

#define     MT_SCH_ANA_RXCAL_REQ                    4602
#define     MT_SCH_ANA_RXCAL_STOP                   4603

#define     MT_SCH_DIG_TXCAL_REQ                    4604
#define     MT_SCH_DIG_TXCAL_STOP                   4605

#define     MT_SCH_ANA_TXCAL_REQ                    4606
#define     MT_SCH_ANA_TXCAL_STOP                   4607

#define     MT_SCH_DIG_RXCAL_REQ                    4608
#define     MT_SCH_DIG_RXCAL_STOP                   4609
#define     SCH_MT_DIG_RXCAL_RSP                    4610

/*******MMI&PC****************/
#define     PC_MMI_CHCHG_REQ                        6000
#define     MMI_PC_CHCHG_CNF                        6001

#define     PC_MMI_PTT_REQ                          6002
#define     MMI_PC_PTT_CNF                          6003

/**************************************************************************
 *                        Test Message ID                                  *
 **************************************************************************/
/*******SP&DEBUG****************/
#define      DEBUG_SP_TEST_REQ                      8200
#define      SP_DEBUG_GLB_REQ                       8201

#define      DEBUG_SP_RDGLB_REQ                     8202
#define      SP_DEBUG_RDSYSGLB_CNF                  8203
#define      SP_DEBUG_RDCHLCALGLB_CNF               8204


#define      DEBUG_SP_WTSYSGLB_REQ                  8205
#define      DEBUG_SP_WTCHLCALGLB_REQ               8206
#define      SP_DEBUG_WTGLB_CNF                     8207


/*******CCL&DEBUG****************/
#define     DEBUG_CCL_TEST_REQ                      8250
#define     CCL_DEBUG_STAT_IND                      8251
#define     CCL_DEBUG_CALL_IND                      8252
#define     CCL_DEBUG_SYSMSG_IND                    8253

/*******DLL&DEBUG****************/
#define     DEBUG_DLL_TEST_REQ                      8300
#define     DLL_DEBUG_GLOBALVAR_IND                 8301
#define     DLL_DEBUG_DATAGET_IND                   8302

/*******PL&DEBUG****************/
#define     DEBUG_PL_TEST_REQ                       8350
#define     PL_DEBUG_TEST1_IND                      8351
#define     PL_DEBUG_TEST2_IND                      8352


/*******SCH&DEBUG****************/
#define     DEBUG_SCH_TEST_REQ                      8450
#define     SCH_DEBUG_TEST_INFO                     8451

#define     DEBUG_SCH_CPU_RATE_SET                  8452
#define     DEBUG_SCH_CPU_RATE_REQ                  8453
#define     SCH_DEBUG_CPU_RATE_RSP                  8454

#define     DEBUG_SCH_MEM_STA_REQ                   8455
#define     SCH_DEBUG_MEM_STA_RSP                   8456


/*******ZSPDD&DEBUG****************/
#define     DEBUG_ZSPDD_DUMP_REQ                    8505
#define     ZSPDD_DEBUG_DUMP_IND                    8506

#define     DEBUG_ZSPDD_TEST_REQ                    8507
#define     ZSPDD_DEBUG_TEST_DATA                   8508


/*******ARMDD&DEBUG****************/
#define     DEBUG_ARMDD_READREG_REQ                 8560
#define     ARMDD_DEBUG_READREG_RSP                 8561

/*******OSE&DEBUG****************/
#define     DEBUG_OSE_TEST_REQ                      8570

/*******ZSPDD&ARMDD****************/
#define     ZSPDD_ARMDD_MSG_FAIL_IND                8600

/**************************************************************************
 *                        MODULE ID                        *
 **************************************************************************/

#define SYS_MODULE_ARMDD             1
#define SYS_MODULE_OSE               2
#define SYS_MODULE_SP                3
#define SYS_MODULE_MMI               4
#define SYS_MODULE_CCL               5
#define SYS_MODULE_ZSPDD             21
#define SYS_MODULE_SCH               22
#define SYS_MODULE_PL                23
#define SYS_MODULE_DLL               24
#define SYS_MODULE_VOCODER           25
#define SYS_MODULE_MTSW              41
#define SYS_MODULE_DEBUGSW           42
#define SYS_MODULE_PCSW              43

/**************************************************************************
 *                        Message Type                        *
 **************************************************************************/
#define SIGNALING         1
#define MAINTAINANCE      2
#define TESTING           3


#endif
