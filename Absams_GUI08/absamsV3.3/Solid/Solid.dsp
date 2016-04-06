# Microsoft Developer Studio Project File - Name="Solid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Solid - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Solid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Solid.mak" CFG="Solid - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Solid - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Solid - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Solid - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Solid - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "QHULL" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Solid - Win32 Release"
# Name "Solid - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\BP_C-api.cpp"
# End Source File
# Begin Source File

SOURCE=.\BP_EndpointList.cpp
# End Source File
# Begin Source File

SOURCE=.\BP_Proxy.cpp
# End Source File
# Begin Source File

SOURCE=.\BP_Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Accuracy.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_BBoxTree.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Box.cpp
# End Source File
# Begin Source File

SOURCE=".\DT_C-api.cpp"
# End Source File
# Begin Source File

SOURCE=.\DT_Complex.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Cone.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Convex.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Cylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Encounter.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Facet.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_LineSegment.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Object.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_PenDepth.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Point.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Polyhedron.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Polytope.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_RespTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\DT_Triangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Dynamic.cpp
# End Source File
# Begin Source File

SOURCE=.\Kinetic.cpp
# End Source File
# Begin Source File

SOURCE=.\RigidBody.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BP_Endpoint.h
# End Source File
# Begin Source File

SOURCE=.\BP_EndpointList.h
# End Source File
# Begin Source File

SOURCE=.\BP_Proxy.h
# End Source File
# Begin Source File

SOURCE=.\BP_ProxyList.h
# End Source File
# Begin Source File

SOURCE=.\BP_Scene.h
# End Source File
# Begin Source File

SOURCE=.\DT_Accuracy.h
# End Source File
# Begin Source File

SOURCE=.\DT_AlgoTable.h
# End Source File
# Begin Source File

SOURCE=.\DT_Array.h
# End Source File
# Begin Source File

SOURCE=.\DT_BBoxTree.h
# End Source File
# Begin Source File

SOURCE=.\DT_Box.h
# End Source File
# Begin Source File

SOURCE=.\DT_CBox.h
# End Source File
# Begin Source File

SOURCE=.\DT_Complex.h
# End Source File
# Begin Source File

SOURCE=.\DT_Cone.h
# End Source File
# Begin Source File

SOURCE=.\DT_Convex.h
# End Source File
# Begin Source File

SOURCE=.\DT_Cylinder.h
# End Source File
# Begin Source File

SOURCE=.\DT_Encounter.h
# End Source File
# Begin Source File

SOURCE=.\DT_Facet.h
# End Source File
# Begin Source File

SOURCE=.\DT_GJK.h
# End Source File
# Begin Source File

SOURCE=.\DT_Hull.h
# End Source File
# Begin Source File

SOURCE=.\DT_IndexArray.h
# End Source File
# Begin Source File

SOURCE=.\DT_LineSegment.h
# End Source File
# Begin Source File

SOURCE=.\DT_Minkowski.h
# End Source File
# Begin Source File

SOURCE=.\DT_Object.h
# End Source File
# Begin Source File

SOURCE=.\DT_PenDepth.h
# End Source File
# Begin Source File

SOURCE=.\DT_Point.h
# End Source File
# Begin Source File

SOURCE=.\DT_Polyhedron.h
# End Source File
# Begin Source File

SOURCE=.\DT_Polytope.h
# End Source File
# Begin Source File

SOURCE=.\DT_Response.h
# End Source File
# Begin Source File

SOURCE=.\DT_RespTable.h
# End Source File
# Begin Source File

SOURCE=.\DT_Scene.h
# End Source File
# Begin Source File

SOURCE=.\DT_Shape.h
# End Source File
# Begin Source File

SOURCE=.\DT_Sphere.h
# End Source File
# Begin Source File

SOURCE=.\DT_Transform.h
# End Source File
# Begin Source File

SOURCE=.\DT_Triangle.h
# End Source File
# Begin Source File

SOURCE=.\DT_VertexBase.h
# End Source File
# Begin Source File

SOURCE=.\Dynamic.h
# End Source File
# Begin Source File

SOURCE=.\Kinetic.h
# End Source File
# Begin Source File

SOURCE=.\RigidBody.h
# End Source File
# Begin Source File

SOURCE=.\Solid.hpp
# End Source File
# End Group
# End Target
# End Project
