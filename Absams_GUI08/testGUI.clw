; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestGUIDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "testGUI.h"

ClassCount=5
Class1=CTestGUIApp
Class2=CTestGUIDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_EDIT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTGUI_DIALOG
Class4=CEditDlg
Resource4=IDD_ABOUTBOX
Class5=CEditSprDlg
Resource5=IDD_EDIT_DIALOG1

[CLS:CTestGUIApp]
Type=0
HeaderFile=testGUI.h
ImplementationFile=testGUI.cpp
Filter=N

[CLS:CTestGUIDlg]
Type=0
HeaderFile=testGUIDlg.h
ImplementationFile=testGUIDlg.cpp
Filter=D
LastObject=CTestGUIDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=testGUIDlg.h
ImplementationFile=testGUIDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTGUI_DIALOG]
Type=1
Class=CTestGUIDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_OPEN_BUTTON,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SAVE_BUTTON,button,1342242816
Control6=IDC_LIST1,listbox,1352728833
Control7=IDC_EDIT_BUTTON,button,1476460544
Control8=IDC_ADD_COMMAND,button,1342242816
Control9=IDC_RUN_SIMULATION,button,1476460544
Control10=IDC_SHOW_COLLISIONS,button,1476460544
Control11=IDC_EDIT_BUTTON2,button,1342251008

[DLG:IDD_EDIT_DIALOG]
Type=1
Class=CEditDlg
ControlCount=40
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MHU_SELECT_COMBO,combobox,1344339970
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NUM_MHU,edit,1342187648
Control8=IDC_TAG_SELECT,combobox,1344339970
Control9=IDC_STATIC,static,1342308352
Control10=IDC_DIMENSION_1,edit,1350631554
Control11=IDC_SPIN1,msctls_updown32,1342177312
Control12=IDC_DIMENSION_2,edit,1350631554
Control13=IDC_SPIN2,msctls_updown32,1342177312
Control14=IDC_DIMENSION_3,edit,1350631554
Control15=IDC_SPIN3,msctls_updown32,1342177312
Control16=IDC_STATIC,static,1342308352
Control17=IDC_SHAPE,edit,1342187648
Control18=IDC_DIM1,edit,1342187649
Control19=IDC_DIM2,edit,1342187649
Control20=IDC_DIM3,edit,1342187649
Control21=IDC_SEL_MHU,edit,1342187648
Control22=IDC_APPLY,button,1342242816
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_POSITION_X,edit,1350631554
Control27=IDC_SPIN4,msctls_updown32,1342177312
Control28=IDC_POSITION_Y,edit,1350631554
Control29=IDC_SPIN5,msctls_updown32,1342177312
Control30=IDC_POSITION_Z,edit,1350631554
Control31=IDC_SPIN6,msctls_updown32,1342177312
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_ORIENTATION_L,edit,1350631554
Control36=IDC_SPIN7,msctls_updown32,1342177312
Control37=IDC_ORIENTATION_M,edit,1350631554
Control38=IDC_SPIN8,msctls_updown32,1342177312
Control39=IDC_ORIENTATION_N,edit,1350631554
Control40=IDC_SPIN9,msctls_updown32,1342177312

[CLS:CEditDlg]
Type=0
HeaderFile=EditDlg.h
ImplementationFile=EditDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEditDlg
VirtualFilter=dWC

[DLG:IDD_EDIT_DIALOG1]
Type=1
Class=CEditSprDlg
ControlCount=38
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NODE_SELECT_COMBO,combobox,1344339970
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NUM_NODES,edit,1342187648
Control8=IDC_TAG_SELECT,combobox,1344339970
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SEL_NODE,edit,1342187648
Control11=IDC_APPLY,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_POSITION_U,edit,1350631554
Control16=IDC_SPIN12,msctls_updown32,1342177312
Control17=IDC_POSITION_V,edit,1350631554
Control18=IDC_SPIN13,msctls_updown32,1342177312
Control19=IDC_POSITION_W,edit,1350631554
Control20=IDC_SPIN14,msctls_updown32,1342177312
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_BEGIN_NODE,edit,1350631554
Control25=IDC_SPIN15,msctls_updown32,1342177312
Control26=IDC_END_NODE,edit,1350631554
Control27=IDC_SPIN16,msctls_updown32,1342177312
Control28=IDC_SPRING_STIFF,edit,1350631554
Control29=IDC_SPIN17,msctls_updown32,1342177312
Control30=IDC_STATIC,static,1342308352
Control31=IDC_SEL_SPRING,edit,1342187648
Control32=IDC_STATIC,static,1342308352
Control33=IDC_SPRING_DAMP,edit,1350631554
Control34=IDC_SPIN18,msctls_updown32,1342177312
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_NUM_SPRINGS,edit,1342187648
Control38=IDC_ASSOC_MHU,edit,1342187648

[CLS:CEditSprDlg]
Type=0
HeaderFile=EditSprDlg.h
ImplementationFile=EditSprDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NUM_NODES
VirtualFilter=dWC

