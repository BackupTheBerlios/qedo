# Microsoft Developer Studio Project File - Name="AssemblyFactory" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AssemblyFactory - Win32 Debug_mico
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AssemblyFactory.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AssemblyFactory.mak" CFG="AssemblyFactory - Win32 Debug_mico"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AssemblyFactory - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AssemblyFactory - Win32 Debug_orbacus" (based on "Win32 (x86) Console Application")
!MESSAGE "AssemblyFactory - Win32 Debug_tao" (based on "Win32 (x86) Console Application")
!MESSAGE "AssemblyFactory - Win32 Release_orbacus" (based on "Win32 (x86) Console Application")
!MESSAGE "AssemblyFactory - Win32 Debug_mico" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AssemblyFactory - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "AssemblyFactory - Win32 Debug_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AssemblyFactory___Win32_Debug_orbacus"
# PROP BASE Intermediate_Dir "AssemblyFactory___Win32_Debug_orbacus"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AssemblyFactory___Win32_Debug_orbacus"
# PROP Intermediate_Dir "AssemblyFactory___Win32_Debug_orbacus"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ZLIB)" /I "$(XERCES)\include" /I "$(ORBACUS)\include\OB" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xerces-c_2D.lib zlib.lib jtcd.lib CosNamingd.lib obd.lib shell32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/AssemblyFactory.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib" /libpath:"$(XERCES)\lib" /libpath:"$(ZLIB)\dll32"

!ELSEIF  "$(CFG)" == "AssemblyFactory - Win32 Debug_tao"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AssemblyFactory___Win32_Debug_tao"
# PROP BASE Intermediate_Dir "AssemblyFactory___Win32_Debug_tao"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AssemblyFactory___Win32_Debug_tao"
# PROP Intermediate_Dir "AssemblyFactory___Win32_Debug_tao"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "AssemblyFactory - Win32 Release_orbacus"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AssemblyFactory___Win32_Release_orbacus"
# PROP BASE Intermediate_Dir "AssemblyFactory___Win32_Release_orbacus"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AssemblyFactory___Win32_Release_orbacus"
# PROP Intermediate_Dir "AssemblyFactory___Win32_Release_orbacus"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ZLIB)" /I "$(XERCES)\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /I "../ComponentIDL" /I "../ComponentContainer" /I "../ComponentInstaller" /I "$(ORBACUS)\include" /I "$(ZLIB)" /I "$(XERCES)\include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 xerces-c_1D.lib zlib.lib jtcd.lib CosNamingd.lib obd.lib shell32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/AssemblyFactory.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib" /libpath:"$(XERCES)\lib" /libpath:"$(ZLIB)\dll32"
# ADD LINK32 xerces-c_1D.lib zlib.lib jtcd.lib CosNamingd.lib obd.lib shell32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../../Runtime/AssemblyFactory.exe" /pdbtype:sept /libpath:"$(ORBACUS)\lib" /libpath:"$(XERCES)\lib" /libpath:"$(ZLIB)\dll32"

!ELSEIF  "$(CFG)" == "AssemblyFactory - Win32 Debug_mico"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AssemblyFactory___Win32_Debug_mico"
# PROP BASE Intermediate_Dir "AssemblyFactory___Win32_Debug_mico"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AssemblyFactory___Win32_Debug_mico"
# PROP Intermediate_Dir "AssemblyFactory___Win32_Debug_mico"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AssemblyFactory - Win32 Release"
# Name "AssemblyFactory - Win32 Debug_orbacus"
# Name "AssemblyFactory - Win32 Debug_tao"
# Name "AssemblyFactory - Win32 Release_orbacus"
# Name "AssemblyFactory - Win32 Debug_mico"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Assembly.cpp
# End Source File
# Begin Source File

SOURCE=.\AssemblyFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\CatalogResolver.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\DOMTreeErrorReporter.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\DOMXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\NameServiceBase.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\Package.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\PlatformBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Properties.cpp
# End Source File
# Begin Source File

SOURCE=.\StandardConfigurator.cpp
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\XMLCatalog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Assembly.h
# End Source File
# Begin Source File

SOURCE=.\AssemblyFactory.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\CatalogResolver.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\DOMTreeErrorReporter.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\DOMXMLParser.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\NameServiceBase.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\Package.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\PlatformBase.h
# End Source File
# Begin Source File

SOURCE=.\Properties.h
# End Source File
# Begin Source File

SOURCE=.\StandardConfigurator.h
# End Source File
# Begin Source File

SOURCE=..\ComponentInstaller\XMLCatalog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
