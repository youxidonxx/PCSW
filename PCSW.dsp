# Microsoft Developer Studio Project File - Name="PCSW" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PCSW - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PCSW.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PCSW.mak" CFG="PCSW - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PCSW - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PCSW - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PCSW - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /map /debug /machine:I386

!ELSEIF  "$(CFG)" == "PCSW - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PCSW - Win32 Release"
# Name "PCSW - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddBox.cpp
# End Source File
# Begin Source File

SOURCE=.\AddBox.h
# End Source File
# Begin Source File

SOURCE=.\CELLRANGE.H
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\COMSET.cpp
# End Source File
# Begin Source File

SOURCE=.\COMSET.h
# End Source File
# Begin Source File

SOURCE=.\CSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\CSerial.h
# End Source File
# Begin Source File

SOURCE=.\DpmrView.cpp
# End Source File
# Begin Source File

SOURCE=.\DpmrView.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GridEdit.h
# End Source File
# Begin Source File

SOURCE=.\GridView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MenuKeyView.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuSet.h
# End Source File
# Begin Source File

SOURCE=.\mybar.cpp
# End Source File
# Begin Source File

SOURCE=.\mybar.h
# End Source File
# Begin Source File

SOURCE=.\MyPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\MyTree1.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTree1.h
# End Source File
# Begin Source File

SOURCE=.\PCSW.cpp
# End Source File
# Begin Source File

SOURCE=.\PCSW.h
# End Source File
# Begin Source File

SOURCE=.\PCSW.rc
# End Source File
# Begin Source File

SOURCE=.\PCSWDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PCSWDoc.h
# End Source File
# Begin Source File

SOURCE=.\PCSWView.cpp
# End Source File
# Begin Source File

SOURCE=.\PCSWView.h
# End Source File
# Begin Source File

SOURCE=.\PropPageContact.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPageContact.h
# End Source File
# Begin Source File

SOURCE=.\PropPageGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPageGrp.h
# End Source File
# Begin Source File

SOURCE=.\PropPageSMS.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPageSMS.h
# End Source File
# Begin Source File

SOURCE=.\RadioSetView.cpp
# End Source File
# Begin Source File

SOURCE=.\RadioSetView.h
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScanView.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanView.h
# End Source File
# Begin Source File

SOURCE=.\SIZECBAR.CPP
# End Source File
# Begin Source File

SOURCE=.\SIZECBAR.H
# End Source File
# Begin Source File

SOURCE=.\SpanEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SpanEdit.h
# End Source File
# Begin Source File

SOURCE=.\SplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\spmsgid.h
# End Source File
# Begin Source File

SOURCE=.\spstruct.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\sysmsgdef.h
# End Source File
# Begin Source File

SOURCE=.\typedef.h
# End Source File
# Begin Source File

SOURCE=.\ZoneInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneInfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\binaryda.bin
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cds.bin
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\PCSW.ico
# End Source File
# Begin Source File

SOURCE=.\res\PCSW.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PCSWDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\GridView.h
# End Source File
# Begin Source File

SOURCE=.\MenuKeyView.h
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
