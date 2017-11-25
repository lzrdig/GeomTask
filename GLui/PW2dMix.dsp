# Microsoft Developer Studio Project File - Name="PW2dMix" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PW2dMix - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PW2dMix.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PW2dMix.mak" CFG="PW2dMix - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PW2dMix - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PW2dMix - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PW2dMix - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PW2dMix - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ffts.lib opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PW2dMix - Win32 Release"
# Name "PW2dMix - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\GlobalVar.cpp
# End Source File
# Begin Source File

SOURCE=.\MAINFRM.CPP
# End Source File
# Begin Source File

SOURCE=.\PW2dMix.cpp
# End Source File
# Begin Source File

SOURCE=.\PW2dMixDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PW2dMixView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CONFIG.H
# End Source File
# Begin Source File

SOURCE=".\FFTW-INT.H"
# End Source File
# Begin Source File

SOURCE=.\FFTW.H
# End Source File
# Begin Source File

SOURCE=.\MAINFRM.H
# End Source File
# Begin Source File

SOURCE=.\NRUTIL.H
# End Source File
# Begin Source File

SOURCE=.\PW2dMix.h
# End Source File
# Begin Source File

SOURCE=.\PW2dMix.rc
# End Source File
# Begin Source File

SOURCE=.\PW2dMixDoc.h
# End Source File
# Begin Source File

SOURCE=.\PW2dMixView.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# Begin Source File

SOURCE=.\main.ico
# End Source File
# Begin Source File

SOURCE=.\res\main.ico
# End Source File
# Begin Source File

SOURCE=.\res\PW2dMix.ico
# End Source File
# Begin Source File

SOURCE=.\res\PW2dMix.rc2
# End Source File
# Begin Source File

SOURCE=.\res\sdi.ico
# End Source File
# Begin Source File

SOURCE=.\sdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\viewcon.bmp
# End Source File
# End Group
# Begin Group "GLdemo Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GLDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\Hdibapi.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGL.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGL3D.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenGL4D.cpp
# End Source File
# Begin Source File

SOURCE=.\Str.cpp
# End Source File
# End Group
# Begin Group "GLdemo Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClassArr.h
# End Source File
# Begin Source File

SOURCE=.\GLDemoView.h
# End Source File
# Begin Source File

SOURCE=.\Hdibapi.h
# End Source File
# Begin Source File

SOURCE=.\OpenGL.h
# End Source File
# Begin Source File

SOURCE=.\OpenGL3D.h
# End Source File
# Begin Source File

SOURCE=.\OpenGL4D.h
# End Source File
# Begin Source File

SOURCE=.\Str.h
# End Source File
# End Group
# Begin Group "BBopo Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BB_PROG.CPP
# End Source File
# Begin Source File

SOURCE=.\BBOPO.CPP
# End Source File
# Begin Source File

SOURCE=.\FIELDS.CPP
# End Source File
# End Group
# Begin Group "BBopo Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BB_PROG.H
# End Source File
# Begin Source File

SOURCE=.\BBOPO.H
# End Source File
# Begin Source File

SOURCE=.\DecInclude.h
# End Source File
# Begin Source File

SOURCE=.\FIELDS.H
# End Source File
# Begin Source File

SOURCE=.\GlobalVar.h
# End Source File
# End Group
# Begin Group "3dMath Source"

# PROP Default_Filter ""
# End Group
# Begin Group "3dMath Header"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
