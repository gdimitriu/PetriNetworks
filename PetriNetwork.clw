; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPetriNetworkDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PetriNetwork.h"
LastPage=0

ClassCount=15
Class1=CPetriNetworkApp
Class2=CPetriNetworkDoc
Class3=CPetriNetworkView
Class4=CMainFrame

ResourceCount=18
Resource1=IDD_minmax
Resource2=IDD_VALUE (English (Australia))
Resource3=IDD_INJUMP
Resource4=IDD_ABOUTBOX
Resource5=IDR_PETRINTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource6=IDD_ASK
Class7=CValue
Class8=CControl
Class9=COperation
Class10=CMarked
Resource7=IDD_INJUMP (English (Australia))
Resource8=IDR_MAINFRAME (English (U.S.))
Resource9=IDD_VALUE1
Resource10=IDR_PETRINTYPE (English (Australia))
Resource11=IDD_VALUE
Class11=CInJump
Resource12=IDR_MAINFRAME
Class12=CValue1
Class13=CDigraph
Resource13=IDD_VALUE1 (English (Australia))
Class14=CAsk
Resource14=IDR_CONTEXTMENU
Resource15=IDD_ABOUTBOX (English (U.S.))
Resource16=IDR_MAINFRAME (English (Australia))
Resource17=IDD_ASK (English (Australia))
Class15=CMinMax
Resource18=IDR_CONTEXTMENU (English (Australia))

[CLS:CPetriNetworkApp]
Type=0
HeaderFile=PetriNetwork.h
ImplementationFile=PetriNetwork.cpp
Filter=N
LastObject=ID_APP_ABOUT
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CPetriNetworkDoc]
Type=0
HeaderFile=PetriNetworkDoc.h
ImplementationFile=PetriNetworkDoc.cpp
Filter=N
LastObject=ID_redone
BaseClass=CDocument
VirtualFilter=DC

[CLS:CPetriNetworkView]
Type=0
HeaderFile=PetriNetworkView.h
ImplementationFile=PetriNetworkView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_LOAD


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_HELP_INDEX
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=PetriNetwork.cpp
ImplementationFile=PetriNetwork.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
Command9=ID_HELP_INDEX
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_PETRINTYPE]
Type=1
Class=CPetriNetworkView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_LOAD
Command4=ID_FILE_CLOSE
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_GENERATE
Command13=ID_START
Command14=ID_STOP
Command15=ID_CONTINUE
Command16=ID_SEXIT
Command17=ID_PN
Command18=ID_GRAPH
Command19=ID_DIGRAPH
Command20=ID_mPN
Command21=ID_mJPN
Command22=ID_mTPN
Command23=ID_CNX
Command24=ID_CICLICITY
Command25=ID_EULER
Command26=ID_MIN_COST
Command27=ID_EDIT_UNDO
Command28=ID_EDIT_CUT
Command29=ID_EDIT_COPY
Command30=ID_EDIT_PASTE
Command31=ID_VIEW_TOOLBAR
Command32=ID_VIEW_STATUS_BAR
Command33=ID_WINDOW_NEW
Command34=ID_WINDOW_CASCADE
Command35=ID_WINDOW_TILE_HORZ
Command36=ID_WINDOW_ARRANGE
Command37=ID_APP_ABOUT
Command38=ID_HELP_INDEX
CommandCount=38

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_HELP
Command10=ID_HELP_INDEX
Command11=ID_CONTEXT_HELP
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[MNU:IDR_CONTEXTMENU]
Type=1
Class=CPetriNetworkView
Command1=ID_TRANSITION
Command2=ID_LOCATION
Command3=ID_ARC
Command4=ID_ARC_2P
Command5=ID_ARC_4P
Command6=ID_MARK
Command7=ID_UNMARK
Command8=ID_MOVE_TRAN
Command9=ID_MOVE_LOCATION
Command10=ID_DELETE_TRAN
Command11=ID_DELETE_LOCATION
Command12=ID_DELETE_ARC
Command13=ID_JUMP
Command14=ID_PAN
Command15=ID_ZOOM_IN
Command16=ID_ZOOM_OUT
CommandCount=16

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_HELP
Command10=ID_HELP_INDEX
Command11=ID_CONTEXT_HELP
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VALUE]
Type=1
Class=CValue
ControlCount=6
Control1=IDC_VALUE,edit,1350631552
Control2=IDC_DELAY,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_Info,edit,1350633600
Control6=IDC_Info2,edit,1350633600

[CLS:CValue]
Type=0
HeaderFile=Value.h
ImplementationFile=Value.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CValue

[CLS:CControl]
Type=0
HeaderFile=Control.h
ImplementationFile=Control.cpp
BaseClass=CDialog
Filter=D
LastObject=CControl
VirtualFilter=dWC

[CLS:COperation]
Type=0
HeaderFile=Operation.h
ImplementationFile=Operation.cpp
BaseClass=CWinThread
Filter=N
LastObject=COperation

[CLS:CMarked]
Type=0
HeaderFile=Marked.h
ImplementationFile=Marked.cpp
BaseClass=CWinThread
Filter=N
VirtualFilter=TC
LastObject=CMarked

[DLG:IDD_VALUE (English (Australia))]
Type=1
Class=CValue
ControlCount=6
Control1=IDC_VALUE,edit,1350631552
Control2=IDC_DELAY,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_Info,edit,1350633600
Control6=IDC_Info2,edit,1350633600

[MNU:IDR_PETRINTYPE (English (Australia))]
Type=1
Class=CPetriNetworkView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_LOAD
Command4=ID_FILE_CLOSE
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_GENERATE
Command13=ID_START
Command14=ID_STOP
Command15=ID_CONTINUE
Command16=ID_SEXIT
Command17=ID_PN
Command18=ID_GRAPH
Command19=ID_DIGRAPH
Command20=ID_mPN
Command21=ID_mJPN
Command22=ID_mTPN
Command23=ID_CNX
Command24=ID_CICLICITY
Command25=ID_EULER
Command26=ID_MIN_COST
Command27=ID_KRUSKAL
Command28=ID_PRIM
Command29=ID_BK
Command30=ID_EDIT_UNDO
Command31=ID_EDIT_CUT
Command32=ID_EDIT_COPY
Command33=ID_EDIT_PASTE
Command34=ID_VIEW_TOOLBAR
Command35=ID_VIEW_STATUS_BAR
Command36=ID_WINDOW_NEW
Command37=ID_WINDOW_CASCADE
Command38=ID_WINDOW_TILE_HORZ
Command39=ID_WINDOW_ARRANGE
Command40=ID_APP_ABOUT
Command41=ID_HELP_INDEX
CommandCount=41

[MNU:IDR_CONTEXTMENU (English (Australia))]
Type=1
Class=CPetriNetworkView
Command1=ID_select
Command2=ID_redone
Command3=ID_LOCATION
Command4=ID_TRANSITION
Command5=ID_ARC_2P
Command6=ID_MARK
Command7=ID_MOVE_LOCATION
Command8=ID_MOVE_TRAN
Command9=ID_DELETE_LOCATION
Command10=ID_DELETE_TRAN
Command11=ID_UNMARK
Command12=ID_DELETE_ARC
Command13=ID_ARC_4P
Command14=ID_ARC
Command15=ID_JUMP
Command16=ID_PAN
Command17=ID_ZOOM_IN
Command18=ID_ZOOM_OUT
CommandCount=18

[TB:IDR_MAINFRAME (English (Australia))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (Australia))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
Command9=ID_HELP_INDEX
CommandCount=9

[CLS:CInJump]
Type=0
HeaderFile=InJump.h
ImplementationFile=InJump.cpp
BaseClass=CDialog
Filter=D
LastObject=CInJump
VirtualFilter=dWC

[DLG:IDD_INJUMP]
Type=1
Class=CInJump
ControlCount=7
Control1=IDC_IN,edit,1350631552
Control2=IDC_OUT,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_Message,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_VALUE1]
Type=1
Class=CValue1
ControlCount=4
Control1=IDC_VALUE,edit,1350631552
Control2=IDOK_Value1,button,1342242817
Control3=IDCANCEL_Value1,button,1342242816
Control4=IDC_Info,edit,1350633600

[CLS:CValue1]
Type=0
HeaderFile=Value1.h
ImplementationFile=Value1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDCANCEL_Value1

[CLS:CDigraph]
Type=0
HeaderFile=Digraph.h
ImplementationFile=Digraph.cpp
BaseClass=CWinThread
Filter=N

[DLG:IDD_ASK]
Type=1
Class=CAsk
ControlCount=3
Control1=ID_YES,button,1342242817
Control2=ID_NO,button,1342242816
Control3=IDC_Info,edit,1350633600

[CLS:CAsk]
Type=0
HeaderFile=Ask.h
ImplementationFile=Ask.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAsk

[DLG:IDD_INJUMP (English (Australia))]
Type=1
Class=CInJump
ControlCount=7
Control1=IDC_IN,edit,1350631552
Control2=IDC_OUT,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_Message,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_VALUE1 (English (Australia))]
Type=1
Class=CValue1
ControlCount=4
Control1=IDC_VALUE,edit,1350631552
Control2=IDOK_Value1,button,1342242817
Control3=IDCANCEL_Value1,button,1342242816
Control4=IDC_Info,edit,1350633600

[DLG:IDD_ASK (English (Australia))]
Type=1
Class=CAsk
ControlCount=3
Control1=ID_YES,button,1342242817
Control2=ID_NO,button,1342242816
Control3=IDC_Info,edit,1350633600

[DLG:IDD_minmax]
Type=1
Class=CMinMax
ControlCount=9
Control1=IDC_OK,button,1342242817
Control2=IDC_CANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_start,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_end,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_min,button,1342177289
Control9=IDC_max,button,1342177289

[CLS:CMinMax]
Type=0
HeaderFile=MinMax.h
ImplementationFile=MinMax.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_OK
VirtualFilter=dWC

