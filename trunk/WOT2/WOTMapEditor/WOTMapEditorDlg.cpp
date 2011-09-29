// WOTMapEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "WOTMapEditorDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWOTMapEditorDlg dialog

CWOTMapEditorDlg::CWOTMapEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWOTMapEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWOTMapEditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWOTMapEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWOTMapEditorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWOTMapEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CWOTMapEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_CONTROL_RANGE(BN_CLICKED,BASE_TILE,MAX_TILE,OnIncreaseTile)
	ON_COMMAND(ID_GRASS, OnGrass)
	ON_UPDATE_COMMAND_UI(ID_GRASS, OnUpdateGrass)
	ON_COMMAND(ID_BLACKHOLE, OnBlackhole)
	ON_UPDATE_COMMAND_UI(ID_BLACKHOLE, OnUpdateBlackhole)
	ON_COMMAND(ID_RIVER, OnRiver)
	ON_UPDATE_COMMAND_UI(ID_RIVER, OnUpdateRiver)
	ON_COMMAND(ID_TREE, OnTree)
	ON_UPDATE_COMMAND_UI(ID_TREE, OnUpdateTree)
	ON_COMMAND(ID_FINDSHORTEST, OnFindshortest)
	ON_COMMAND(ID_RESETSHORTEST, OnResetshortest)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_MOUTAIN, OnMoutain)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MAP_WAYMANAGER, &CWOTMapEditorDlg::OnMapWaymanager)
	ON_MESSAGE_VOID(WM_KICKIDLE, OnKickIdle)
	ON_UPDATE_COMMAND_UI(ID_MOUTAIN, &CWOTMapEditorDlg::OnUpdateMoutain)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEAS, &CWOTMapEditorDlg::OnUpdateFileSaveas)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CWOTMapEditorDlg::OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_MAP_WAYMANAGER, &CWOTMapEditorDlg::OnUpdateMapWaymanager)
	ON_COMMAND(ID_MAP_ENEMYPROPERTIES, &CWOTMapEditorDlg::OnMapEnemyproperties)
	ON_UPDATE_COMMAND_UI(ID_MAP_ENEMYPROPERTIES, &CWOTMapEditorDlg::OnUpdateMapEnemyproperties)
	ON_COMMAND(ID_MAP_TOWERPROPERTIES, &CWOTMapEditorDlg::OnMapTowerproperties)
	ON_UPDATE_COMMAND_UI(ID_MAP_TOWERPROPERTIES, &CWOTMapEditorDlg::OnUpdateMapTowerproperties)
	ON_COMMAND(ID_MAP_WAVEMANAGER, &CWOTMapEditorDlg::OnMapWavemanager)
	ON_UPDATE_COMMAND_UI(ID_MAP_WAVEMANAGER, &CWOTMapEditorDlg::OnUpdateMapWavemanager)
	ON_COMMAND(ID_MAP_MODELMANAGER, &CWOTMapEditorDlg::OnMapModelmanager)
	ON_UPDATE_COMMAND_UI(ID_MAP_MODELMANAGER, &CWOTMapEditorDlg::OnUpdateMapModelmanager)
	ON_COMMAND(ID_BANANA, &CWOTMapEditorDlg::OnBanana)
	ON_UPDATE_COMMAND_UI(ID_BANANA, &CWOTMapEditorDlg::OnUpdateBanana)
	ON_COMMAND(ID_COCONUT, &CWOTMapEditorDlg::OnCoconut)
	ON_UPDATE_COMMAND_UI(ID_COCONUT, &CWOTMapEditorDlg::OnUpdateCoconut)
	ON_COMMAND(ID_MAP_GENERALSETTING, &CWOTMapEditorDlg::OnMapGeneralsetting)
	ON_UPDATE_COMMAND_UI(ID_MAP_GENERALSETTING, &CWOTMapEditorDlg::OnUpdateMapGeneralsetting)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWOTMapEditorDlg message handlers

BOOL CWOTMapEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// Create toolbar at the top of the dialog window
	if (m_toolBar.Create(this))
	{
		//m_toolBar.LoadBitmap(m_nIDBitmap);
		//m_toolBar.SetButtons(m_lpaIDToolBar, m_cIDToolBar);
		m_toolBar.LoadToolBar(IDR_TOOLBAR1);
	}

	m_toolBar.SetBarStyle(m_toolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
				   0, reposQuery, rcClientNow);

	// Now move all the controls so they are in the same relative
	// position within the remaining client area as they would be
	// with no control bars.
	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
					rcClientNow.top - rcClientStart.top);


	// Adjust the dialog window dimensions
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);

	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	// Finally, center the dialog on the screen
	CenterWindow();
	return TRUE;
}

void CWOTMapEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWOTMapEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWOTMapEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CWOTMapEditorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	StartupConfig();
	return 0;
}

void CWOTMapEditorDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CWOTMapEditorDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	OnOK();
}

void CWOTMapEditorDlg::OnIncreaseTile(UINT nID) {
	
	UpdateData(TRUE);
	int pos = nID - BASE_TILE;
	if ((m_data[pos] & 0xF0000000) ==  TILE_BANANA || m_data[pos] == TILE_GRASS)  {
		m_data[pos] = m_toPlace;
		switch (m_toPlace) {
		case TILE_GRASS:
			m_tile[pos].SetColor(BLACK, GREEN);
			break;
		case TILE_BANANA:
		case TILE_COCONUT:
		case TILE_TREE:
			m_tile[pos].SetColor(BLACK, DKGREEN);
			break;
		case TILE_MOUTAIN:
			m_tile[pos].SetColor(BLACK, BROWN);
			break;
		case TILE_RIVER:
			m_tile[pos].SetColor(BLACK, BLUE);
			break;
		default:
			m_tile[pos].SetColor(BLACK, BLACK);
			break;
		}
		/*char buffer[50];
		itoa(m_data[pos],buffer,10);*/
		CString buffer;
		buffer.Format("%d",m_data[pos]&0x0FFFFFFF);
		m_tile[pos].SetWindowText(buffer);
	}
	UpdateData(FALSE);
}

void CWOTMapEditorDlg::OnGrass() 
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_GRASS;
}

void CWOTMapEditorDlg::OnUpdateGrass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_GRASS);
}

void CWOTMapEditorDlg::OnBlackhole() 
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_BLACKHOLE;
}

void CWOTMapEditorDlg::OnUpdateBlackhole(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_BLACKHOLE);
}

void CWOTMapEditorDlg::OnRiver() 
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_RIVER;
}

void CWOTMapEditorDlg::OnUpdateRiver(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_RIVER);
}

void CWOTMapEditorDlg::OnTree() 
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_TREE;
}

void CWOTMapEditorDlg::OnUpdateTree(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_TREE);
}

void CWOTMapEditorDlg::OnMoutain() 
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_MOUTAIN;
}

void CWOTMapEditorDlg::OnUpdateMoutain(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_MOUTAIN);
}


void CWOTMapEditorDlg::OnFindshortest() 
{
	// TODO: Add your command handler code here
	/*if (!haveDes || !haveSrc) {
		MessageBox("Missing source or destination definition");
		return;
	}*/
	if (m_chooseWayDlg->DoModal() == IDOK) {
		bool res;
		if (m_chooseWayDlg->m_useWay) {
			//if (m_chooseWayDlg->m_selectedWay)
				res = astar->pathFinder(false, m_list, m_chooseWayDlg->m_selectedWay->si, m_chooseWayDlg->m_selectedWay->sj, 
									m_chooseWayDlg->m_selectedWay->di, m_chooseWayDlg->m_selectedWay->dj);
			//else {
				//MessageBox("There 's no Way");
				//return;
			//}
		}
		else {
			if (!astar) return;
			res = astar->pathFinder(false, m_list, m_chooseWayDlg->m_iSrc, m_chooseWayDlg->m_jSrc, 
									m_chooseWayDlg->m_iDes, m_chooseWayDlg->m_jDes);
		}
		if (res) {
			m_list->BeginTravel();
			while(!m_list->IsEndOfTravel()) {
				cell t = m_list->Travel();
				m_tile[t.i*m_mapfile->width+t.j].SetFGColor(YELLOW,true);
			}
		}
		else
			MessageBox("There is no shortest path");
	}
}

void CWOTMapEditorDlg::OnResetshortest() 
{
	// TODO: Add your command handler code here
	//TODO: uncolor path
	m_list->BeginTravel();
	while(!m_list->IsEndOfTravel()) {
		cell t = m_list->Travel();
		m_tile[t.i*m_mapfile->width+t.j].SetFGColor(BLACK,true);
	}
	m_list->Clear();
}

void CWOTMapEditorDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	char strFilter[] = { "World of Tower Map Files (*.wotmap)|*.wotmap|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(TRUE, ".wotmap", NULL, 0, strFilter);

	if( FileDlg.DoModal() == IDOK )
	{
		filename=FileDlg.GetPathName();
		m_mapfile = new CWOTMapfile();
		if (m_mapfile->loadfromFile(filename.GetBuffer(0))) {
			int width = m_mapfile->width;
			int height =  m_mapfile->height;
			m_mapfile->synctoArray(m_data);

			Init(false);

			int i,j;
			for (i=0;i<height;i++)
				for (j=0;j<width;j++) {
					int pos = i*width+j;
					int IDC = BASE_TILE + i*width+j;

					//char buffer[50];
					//itoa(m_data[pos],buffer,50);
					COLORREF bg = GREEN;
					CString buffer;
					switch (m_data[pos] & 0xF0000000) {
					case SOURCE:
						buffer.Format("S%u",m_data[pos] & 0x0FFFFFFF);
						bg = RED;
						break;
					case DESTINATION:
						buffer.Format("D%u",m_data[pos] & 0x0FFFFFFF);
						bg = MAGENTA;
						break;
					case TILE_GRASS:
						buffer.Format("%u",m_data[pos]);
						break;
					case TILE_BANANA:
						{
							switch (m_data[pos]) {
								case TILE_BANANA:
								case TILE_COCONUT:
								case TILE_TREE:
									buffer.Format("%u",m_data[pos] & 0x0FFFFFFF);
									bg = DKGREEN;
									break;
								case TILE_MOUTAIN:
									buffer.Format("%u",m_data[pos] & 0x0FFFFFFF);
									bg = BROWN;
									break;
								case TILE_RIVER:
									buffer.Format("%u",m_data[pos]& 0x0FFFFFFF);
									bg = BLUE;
									break;
								case TILE_BLACKHOLE:
									buffer.Format("%u",m_data[pos]& 0x0FFFFFFF);
									bg = BLACK;
									break;
							}
						}
						break;
					default:
						buffer.Format("%u",m_data[pos]);
					}

					m_tile[pos].Create(buffer,WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, CRect(0+30*j, 0+30*i, 30+30*j, 30+30*i), this, IDC);
					m_tile[pos].SetColor(BLACK, bg);
				}
		}
		else {
			delete m_mapfile;
			m_mapfile = NULL;
		}
		arrangeToolbar();
	}
	else
		return;

}

void CWOTMapEditorDlg::OnFileNew() 
{
	// TODO: Add your command handler code here
	if (m_newMapDlg.DoModal() == IDOK) {
		m_mapfile = new CWOTMapfile();
		m_mapfile->width = m_newMapDlg.m_column;
		m_mapfile->height = m_newMapDlg.m_row;
		Init();
	}
}

void CWOTMapEditorDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if (filename == "")
		OnFileSaveas();
	else {
		//TODO: save only changes
	}
}

void CWOTMapEditorDlg::OnFileSaveas() 
{
	// TODO: Add your command handler code here
	//chan k cho save neu k co src hoac des
	//TODO: find at least path from src to deadth
	if (m_mapfile->m_lstWay->GetCount() == 0) {
		MessageBox("Missing source or destination definition");
		return;
	}

	char strFilter[] = { "World of Tower Map Files (*.wotmap)|*.wotmap|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(FALSE, ".wotmap", NULL, 0, strFilter);

	if( FileDlg.DoModal() == IDOK )
	{
		filename=FileDlg.GetPathName();
		m_mapfile->syncfromArray(m_data);
		m_mapfile->writetoFile(filename.GetBuffer(0));
	}	
}

void CWOTMapEditorDlg::Init(bool isCreatingFile)
{
	this->Clear();
	int width = m_mapfile->width;
	int height = m_mapfile->height;

	m_tile = new CColorButton[width*height];
	if (isCreatingFile) {
		m_data = new int[width*height];
		int i,j;
		for (i=0;i<height;i++)
			for (j=0;j<width;j++)
				m_data[i*width+j] = 0;
			for (i=0;i<height;i++)
				for (j=0;j<width;j++) {
					int ID = BASE_TILE + i*width+j;
					CString buffer;
					buffer.Format("%d",m_data[i*width+j]);
					m_tile[i*width+j].Create(buffer,WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, CRect(0+30*j, 0+30*i, 30+30*j, 30+30*i), this, ID);
					m_tile[i*width+j].SetColor(BLACK, GREEN);
				}
				//m_mapfile->m_lstWay->AddItem(SOURCE, new Way(0,0,height-1,width-1));
				m_mapfile->m_lstEnemyProperties->AddItem(0,new EnemyProperties(50,1,5,7));
	}
	arrangeToolbar();

	astar = new AStar(width, height, m_data);

	//pass all lists in file to dialogs
	m_chooseWayDlg->m_wayLstData = m_wayManagerDlg->m_wayLstData 
									= m_mapfile->m_lstWay;
	//Thong so cho Enemy Properties
	m_enemyPropertiesDlg->m_epLstData = m_mapfile->m_lstEnemyProperties;
	m_enemyPropertiesDlg->m_mpLstData = m_mapfile->m_lstModelProperties;
	//Thong so cho Tower Properties
	m_towerPropertiesDlg->m_tpLstData = m_mapfile->m_lstTowerProperties;
	m_towerPropertiesDlg->m_mpLstData = m_mapfile->m_lstModelProperties;
	//Thong so cho WAVE
	m_waveManagerDlg->m_waveLstData = m_mapfile->m_lstWave;
	m_waveManagerDlg->m_epLstData = m_mapfile->m_lstEnemyProperties;
	m_waveManagerDlg->m_wayLstData = m_mapfile->m_lstWay;
	//Thong so cho WayManagerDlg
	m_wayManagerDlg->width = width;
	m_wayManagerDlg->height = height;
	m_wayManagerDlg->m_data = m_data;
	m_wayManagerDlg->m_tile = m_tile;
	//Thong so cho Model Dlg
	m_modelManagerDlg->m_mpLstData = m_mapfile->m_lstModelProperties;
}

void CWOTMapEditorDlg::Clear()
{
	if (m_tile) {
		delete []m_tile;
		m_tile = NULL;
	}
	if (astar) {
		delete astar;
		astar = NULL;
	}
	//if (m_data) {
	//	delete []m_data;
	//	m_data = NULL;
	//}
	//if (m_mapfile) {
	//	delete m_mapfile;
	//	m_data = NULL;
	//}
}

void CWOTMapEditorDlg::OnMapWaymanager()
{
	// TODO: Add your command handler code here
	m_wayManagerDlg->DoModal() == IDOK;
}


void CWOTMapEditorDlg::StartupConfig(void)
{
	m_toPlace = 0;

	m_tile = NULL;
	m_data = NULL;
	astar = NULL;
	m_mapfile = NULL;
	filename = "";
	m_chooseWayDlg = new CChooseWayDlg();
	m_wayManagerDlg = new CWayManagerDlg();
	m_enemyPropertiesDlg = new CEnemyPropertiesDlg();
	m_towerPropertiesDlg = new CTowerPropertiesDlg();
	m_waveManagerDlg = new CWaveManagerDlg();
	m_modelManagerDlg = new CModelManagerDlg();
	m_generalSettingDlg = new CGeneralSettingDlg();
	m_list = new GameTutor::CList<cell>();
}

void CWOTMapEditorDlg::OnKickIdle() {
	UpdateDialogControls(this, FALSE);
	m_toolBar.SendMessage(WM_IDLEUPDATECMDUI);

	CMenu* pMainMenu = GetMenu();
	CCmdUI cmdUI;
	for (UINT n = 0; n < pMainMenu->GetMenuItemCount(); ++n)
	{
	CMenu* pSubMenu = pMainMenu->GetSubMenu(n);
	cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
	for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
	{
	cmdUI.m_nIndex = i;
	cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
	cmdUI.m_pMenu = pSubMenu;
	cmdUI.DoUpdate(this, FALSE);
	}
	}
}



void CWOTMapEditorDlg::OnUpdateFileSaveas(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::OnUpdateMapWaymanager(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::arrangeToolbar(void)
{
		// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
				   0, reposQuery, rcClientNow);

	// Now move all the controls so they are in the same relative
	// position within the remaining client area as they would be
	// with no control bars.
	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
					rcClientNow.top - rcClientStart.top);



	CRect  rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}

	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	Invalidate();
}


void CWOTMapEditorDlg::OnMapEnemyproperties()
{
	// TODO: Add your command handler code here
	m_enemyPropertiesDlg->DoModal();
}


void CWOTMapEditorDlg::OnUpdateMapEnemyproperties(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::OnMapTowerproperties()
{
	// TODO: Add your command handler code here
	m_towerPropertiesDlg->DoModal();
}


void CWOTMapEditorDlg::OnUpdateMapTowerproperties(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::OnMapWavemanager()
{
	// TODO: Add your command handler code here
	m_waveManagerDlg->DoModal();
}


void CWOTMapEditorDlg::OnUpdateMapWavemanager(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::OnMapModelmanager()
{
	// TODO: Add your command handler code here
	m_modelManagerDlg->DoModal();
}


void CWOTMapEditorDlg::OnUpdateMapModelmanager(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}


void CWOTMapEditorDlg::OnBanana()
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_BANANA;
}


void CWOTMapEditorDlg::OnUpdateBanana(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_BANANA);
}


void CWOTMapEditorDlg::OnCoconut()
{
	// TODO: Add your command handler code here
	m_toPlace = TILE_COCONUT;
}


void CWOTMapEditorDlg::OnUpdateCoconut(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_toPlace == TILE_COCONUT);
}


void CWOTMapEditorDlg::OnMapGeneralsetting()
{
	// TODO: Add your command handler code here
	m_generalSettingDlg->m_initMoney = m_mapfile->InitMoney;
	m_generalSettingDlg->m_bg.Format(m_mapfile->background);
	if (m_generalSettingDlg->DoModal() == IDOK) {
		m_mapfile->InitMoney = m_generalSettingDlg->m_initMoney;
		strcpy(m_mapfile->background, m_generalSettingDlg->m_bg.GetBuffer(0));
	}
}


void CWOTMapEditorDlg::OnUpdateMapGeneralsetting(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_mapfile != NULL);
}
