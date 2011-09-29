// ChooseWayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "ChooseWayDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseWayDlg dialog


CChooseWayDlg::CChooseWayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseWayDlg::IDD, pParent)
	, m_wayLstData(NULL)
{
	//{{AFX_DATA_INIT(CChooseWayDlg)
	m_iDes = 0;
	m_iSrc = 0;
	m_jDes = 0;
	m_jSrc = 0;
	m_useWay = true;
	//}}AFX_DATA_INIT
}


void CChooseWayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseWayDlg)
	DDX_Text(pDX, IDC_EDITIDES, m_iDes);
	DDX_Text(pDX, IDC_EDITISRC, m_iSrc);
	DDX_Text(pDX, IDC_EDITJDES, m_jDes);
	DDX_Text(pDX, IDC_EDITJSRC, m_jSrc);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_WAYLIST, m_wayLst);
	DDX_Check(pDX, IDC_CHECKUSEWAY, m_useWay);
}


BEGIN_MESSAGE_MAP(CChooseWayDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseWayDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_WAYLIST, OnUpdateWayList)

	ON_UPDATE_COMMAND_UI(IDC_EDITISRC, OnUpdateManualPosition)
	ON_UPDATE_COMMAND_UI(IDC_EDITJSRC, OnUpdateManualPosition)
	ON_UPDATE_COMMAND_UI(IDC_EDITIDES, OnUpdateManualPosition)
	ON_UPDATE_COMMAND_UI(IDC_EDITJDES, OnUpdateManualPosition)


	ON_MESSAGE_VOID(WM_KICKIDLE, OnKickIdle)
	ON_BN_CLICKED(IDOK, &CChooseWayDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDC_CHECKUSEWAY, &CChooseWayDlg::OnBnClickedCheckuseway)
	ON_WM_CREATE()
//	ON_BN_CLICKED(ID_SELECT, &CChooseWayDlg::OnBnClickedSelect)
END_MESSAGE_MAP()

// Fill List Box with Data


void CChooseWayDlg::FillListBox(void)
{
	m_wayLst.Reset();
	AddColumns();
	m_wayLstData->BeginTravel();
	int i=0;
	while (!m_wayLstData->IsEndOfTravel()) {
		int key;
		Way *tmp = m_wayLstData->Travel(key);
		CString str;
		str.Format("%x", key);
		m_wayLst.InsertItem(i, str);
		str.Format("%d", tmp->si);
		m_wayLst.SetItemText(i, 1, str);
		str.Format("%d", tmp->sj);
		m_wayLst.SetItemText(i, 2, str);
		str.Format("%d", tmp->di);
		m_wayLst.SetItemText(i, 3, str);
		str.Format("%d", tmp->dj);
		m_wayLst.SetItemText(i, 4, str);
		i++;
	}
}


// Init Column Header for List
void CChooseWayDlg::AddColumns(void)
{
	m_wayLst.InsertColumn(0, "Way ID", LVCFMT_LEFT, 70);
	m_wayLst.InsertColumn(1, "iStart", LVCFMT_LEFT, 50);
	m_wayLst.InsertColumn(2, "jStart", LVCFMT_LEFT, 50);
	m_wayLst.InsertColumn(3, "iEnd", LVCFMT_LEFT, 50);
	m_wayLst.InsertColumn(4, "jEnd", LVCFMT_LEFT, 50);
}


BOOL CChooseWayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	FillListBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseWayDlg::OnUpdateWayList(CCmdUI* pCmdUI) {
	UpdateData(TRUE);
	pCmdUI->Enable(this->m_useWay);
	UpdateData(FALSE);
}

void CChooseWayDlg::OnKickIdle()
{
	UpdateDialogControls(this, FALSE);
}

void CChooseWayDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (m_useWay) {
		POSITION pos = m_wayLst.GetFirstSelectedItemPosition();
		if (pos) {
			CString str = m_wayLst.GetItemText((int)pos-1,0);
			int key;
			sscanf(str,"%x", &key);
			m_wayLstData->GetElement(key, this->m_selectedWay);
		}
		else {
			MessageBox("No Way");
			return;
		}
	}
	CDialog::OnOK();
}


int CChooseWayDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	return 0;
}

void CChooseWayDlg::OnUpdateManualPosition(CCmdUI* pCmdUI) {
	UpdateData(TRUE);
	pCmdUI->Enable(!this->m_useWay);
	UpdateData(FALSE);
}