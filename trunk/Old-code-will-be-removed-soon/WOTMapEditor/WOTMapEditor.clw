; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CListCtrlEx
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WOTMapEditor.h"

ClassCount=6
Class1=CWOTMapEditorApp
Class2=CWOTMapEditorDlg
Class3=CAboutDlg

ResourceCount=13
Resource1=IDD_NEWMAP (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_CHOOSEWAY
Resource4=IDR_TOOLBAR1 (English (U.S.))
Resource5=IDD_WOTMAPEDITOR_DIALOG (English (U.S.))
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDD_WAYMANAGER
Resource8=IDR_MENU_MAIN
Resource9=IDD_WOTMAPEDITOR_DIALOG
Class4=CNewMapDlg
Resource10=IDD_ABOUTBOX
Resource11=IDD_NEWMAP
Resource12=IDR_TOOLBAR1
Class5=CChooseWayDlg
Class6=CListCtrlEx
Resource13=IDR_MENU_MAIN (Vietnamese)

[CLS:CWOTMapEditorApp]
Type=0
HeaderFile=WOTMapEditor.h
ImplementationFile=WOTMapEditor.cpp
Filter=N

[CLS:CWOTMapEditorDlg]
Type=0
HeaderFile=WOTMapEditorDlg.h
ImplementationFile=WOTMapEditorDlg.cpp
Filter=D
LastObject=ID_HELP_ABOUT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=WOTMapEditorDlg.h
ImplementationFile=WOTMapEditorDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WOTMAPEDITOR_DIALOG]
Type=1
Class=CWOTMapEditorDlg
ControlCount=0

[DLG:IDD_WOTMAPEDITOR_DIALOG (English (U.S.))]
Type=1
Class=CWOTMapEditorDlg
ControlCount=0

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVEAS
Command5=ID_FILE_EXIT
Command6=ID_EDIT_REMOVE
Command7=ID_INSERT_GUNTOWER
Command8=ID_INSERT_CANONTOWER
Command9=ID_INSERT_ROCKETTOWER_1
Command10=ID_INSERT_ROCKETTOWER_2
Command11=ID_INSERT_ROCKETTOWER_3
Command12=ID_INSERT_BOMBARDTOWER_1
Command13=ID_INSERT_BOMBARDTOWER_2
Command14=ID_INSERT_BOMBARDTOWER_3
Command15=ID_INSERT_MACHINETOWER_1
Command16=ID_INSERT_MACHINETOWER_2
Command17=ID_INSERT_MACHINETOWER_3
Command18=ID_INSERT_LASERTOWER_1
Command19=ID_INSERT_LASERTOWER_2
Command20=ID_INSERT_DEADTOWER
Command21=ID_INSERT_BOOSTTOWER
Command22=ID_INSERT_NUCLEARTOWER_1
Command23=ID_INSERT_NUCLEARTOWER_2
Command24=ID_INSERT_NUCLEARTOWER_3
Command25=ID_INSERT_ELECTRIC_1
Command26=ID_INSERT_ELECTRIC_2
Command27=ID_INSERT_ELECTRIC_3
Command28=ID_INSERT_CHEMICAL_1
Command29=ID_INSERT_CHEMICAL_2
Command30=ID_INSERT_CHEMICAL_3
Command31=ID_INSERT_MAGICTOWER
Command32=ID_INSERT_POISONTOWER_1
Command33=ID_INSERT_POISONTOWER_2
Command34=ID_INSERT_POISONTOWER_3
Command35=ID_INSERT_SLOWTOWER_1
Command36=ID_INSERT_SLOWTOWER_2
Command37=ID_INSERT_SLOWTOWER_3
Command38=ID_HELP_ABOUT
CommandCount=38

[MNU:IDR_MENU_MAIN (Vietnamese)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVEAS
Command5=ID_FILE_EXIT
Command6=ID_EDIT_REMOVE
Command7=ID_INSERT_GUNTOWER
Command8=ID_INSERT_CANONTOWER
Command9=ID_INSERT_ROCKETTOWER_1
Command10=ID_INSERT_ROCKETTOWER_2
Command11=ID_INSERT_ROCKETTOWER_3
Command12=ID_INSERT_BOMBARDTOWER_1
Command13=ID_INSERT_BOMBARDTOWER_2
Command14=ID_INSERT_BOMBARDTOWER_3
Command15=ID_INSERT_MACHINETOWER_1
Command16=ID_INSERT_MACHINETOWER_2
Command17=ID_INSERT_MACHINETOWER_3
Command18=ID_INSERT_LASERTOWER_1
Command19=ID_INSERT_LASERTOWER_2
Command20=ID_INSERT_DEADTOWER
Command21=ID_INSERT_BOOSTTOWER
Command22=ID_INSERT_NUCLEARTOWER_1
Command23=ID_INSERT_NUCLEARTOWER_2
Command24=ID_INSERT_NUCLEARTOWER_3
Command25=ID_INSERT_ELECTRIC_1
Command26=ID_INSERT_ELECTRIC_2
Command27=ID_INSERT_ELECTRIC_3
Command28=ID_INSERT_CHEMICAL_1
Command29=ID_INSERT_CHEMICAL_2
Command30=ID_INSERT_CHEMICAL_3
Command31=ID_INSERT_MAGICTOWER
Command32=ID_INSERT_POISONTOWER_1
Command33=ID_INSERT_POISONTOWER_2
Command34=ID_INSERT_POISONTOWER_3
Command35=ID_INSERT_SLOWTOWER_1
Command36=ID_INSERT_SLOWTOWER_2
Command37=ID_INSERT_SLOWTOWER_3
Command38=ID_HELP_ABOUT
Command39=ID_HELP_ABOUT
CommandCount=39

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_GRASS
Command2=ID_SOURCE
Command3=ID_DESTINATION
Command4=ID_TREE
Command5=ID_MOUTAIN
Command6=ID_RIVER
Command7=ID_BLACKHOLE
Command8=ID_FINDSHORTEST
Command9=ID_RESETSHORTEST
CommandCount=9

[TB:IDR_TOOLBAR1 (English (U.S.))]
Type=1
Class=?
Command1=ID_GRASS
Command2=ID_SOURCE
Command3=ID_DESTINATION
Command4=ID_TREE
Command5=ID_MOUTAIN
Command6=ID_RIVER
Command7=ID_BLACKHOLE
Command8=ID_FINDSHORTEST
Command9=ID_RESETSHORTEST
CommandCount=9

[DLG:IDD_NEWMAP]
Type=1
Class=CNewMapDlg
ControlCount=7
Control1=IDC_EDITROW,edit,1350631552
Control2=IDC_EDITCOLUMN,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CNewMapDlg]
Type=0
HeaderFile=NewMapDlg.h
ImplementationFile=NewMapDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CNewMapDlg
VirtualFilter=dWC

[DLG:IDD_NEWMAP (English (U.S.))]
Type=1
Class=CNewMapDlg
ControlCount=7
Control1=IDC_EDITROW,edit,1350631552
Control2=IDC_EDITCOLUMN,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_CHOOSEWAY]
Type=1
Class=CChooseWayDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1350631437
Control4=IDC_EDITISRC,edit,1350631552
Control5=IDC_EDITJSRC,edit,1350631552
Control6=IDC_EDITIDES,edit,1350631552
Control7=IDC_EDITJDES,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352

[DLG:IDD_WAYMANAGER]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_LIST1,SysListView32,1350631449

[CLS:CChooseWayDlg]
Type=0
HeaderFile=choosewaydlg.h
ImplementationFile=choosewaydlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CChooseWayDlg

[CLS:CListCtrlEx]
Type=0
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp
BaseClass=CListCtrl
Filter=W

