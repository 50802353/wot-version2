// WayManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "WayManagerDlg.h"
#include "afxdialogex.h"


// CWayManagerDlg dialog

IMPLEMENT_DYNAMIC(CWayManagerDlg, CDialog)

CWayManagerDlg::CWayManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWayManagerDlg::IDD, pParent)
	, autoID(SOURCE)
{
	m_data = NULL;
	m_tile = NULL;
	m_wayLstData = NULL;
}

CWayManagerDlg::~CWayManagerDlg()
{
}

void CWayManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAYLIST, m_wayLst);
	DDX_Control(pDX, IDC_EDITCELL, m_wndEdit);
}


BEGIN_MESSAGE_MAP(CWayManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_ADDWAY, &CWayManagerDlg::OnBnClickedAddway)
	ON_BN_CLICKED(IDC_DELWAY, &CWayManagerDlg::OnBnClickedDelway)
END_MESSAGE_MAP()


// CWayManagerDlg message handlers


void CWayManagerDlg::FillListBox(void)
{
	if (!m_wayLstData) return;
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
	m_wayLst.SetDefaultEditor(NULL, &CWayManagerDlg::EndEditCell, &m_wndEdit);
}


void CWayManagerDlg::AddColumns(void)
{
	m_wayLst.InsertColumn(0, "Way ID", LVCFMT_LEFT, 70);
	m_wayLst.InsertColumn(1, "iStart", LVCFMT_LEFT, 50);
	m_wayLst.InsertColumn(2, "jStart", LVCFMT_LEFT, 50);
	m_wayLst.InsertColumn(3, "iEnd", LVCFMT_LEFT, 50);
	m_wayLst.InsertColumn(4, "jEnd", LVCFMT_LEFT, 50);

	m_wayLst.SetColumnReadOnly(0);
}


BOOL CWayManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	FillListBox();
	m_wayLst.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CWayManagerDlg::OnBnClickedAddway()
{
	// TODO: Add your control notification handler code here
	int ID;
	int dfi=10,dfj=10;
	m_wayLstData->AddItem(autoID++, new Way(0, 0, dfi, dfi));
	FillListBox();
	Refresh();
}


void CWayManagerDlg::OnBnClickedDelway()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_wayLst.GetFirstSelectedItemPosition();
	if (pos) {
		int sel = (int)pos-1;
		CString str = m_wayLst.GetItemText(sel,0);
		int key;
		sscanf(str,"%x", &key);
		Way *tmp;
		m_wayLstData->GetElement(key, tmp);
		
		m_data[tmp->si*width + tmp->sj] = 0;
		m_tile[tmp->si*width + tmp->sj].SetColor(BLACK, GREEN);
		m_tile[tmp->si*width + tmp->sj].SetWindowTextA("0");

		m_data[tmp->di*width + tmp->dj] = 0;
		m_tile[tmp->di*width + tmp->dj].SetColor(BLACK, GREEN);
		m_tile[tmp->di*width + tmp->dj].SetWindowTextA("0");

		m_wayLstData->RemoveItem(key);
		FillListBox();
		Refresh();

		m_wayLst.SetFocus();
		m_wayLst.SetItemState(sel, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	}
}


void CWayManagerDlg::Refresh(void)
{
	m_wayLstData->BeginTravel();
	while (!m_wayLstData->IsEndOfTravel()) {
		int key;
		Way* tmp = m_wayLstData->Travel(key);
		m_data[tmp->si * width + tmp->sj] = key;
		m_data[tmp->di * width + tmp->dj] = key+0x10000000;
		m_tile[tmp->si * width + tmp->sj].SetBGColor(RED,true);
		m_tile[tmp->di * width + tmp->dj].SetBGColor(MAGENTA,true);

		CString bf;
		bf.Format("S%u",key&0x0FFFFFFF);
		m_tile[tmp->si * width + tmp->sj].SetWindowTextA(bf);

		bf.Format("D%u",key&0x0FFFFFFF);
		m_tile[tmp->di * width + tmp->dj].SetWindowTextA(bf);
	}
}

BOOL CWayManagerDlg::EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	CListCtrlEx* lst = (CListCtrlEx*)pThis;
	CWayManagerDlg* dlg = (CWayManagerDlg*)(lst->GetParent());
	CEdit* editBox = (CEdit*)*pWnd;
	CString str;

	dlg->UpdateData(TRUE);
	editBox->GetWindowTextA(str);
	int newValue;
	sscanf(str, "%d", &newValue );

	switch (nColumn) {
	case 1:
	case 3:
		if (newValue > dlg->height || newValue < 0)
			return 0;
		break;
	case 2:
	case 4:
		if (newValue > dlg->width || newValue <0)
			return 0;
		break;
	}
	
	int key;
	CString keydata = lst->GetItemText(nRow, 0);
	sscanf(keydata, "%x", &key);

	Way *tmp;
	dlg->m_wayLstData->GetElement(key, tmp);

	switch (nColumn) {
	case 1:
	case 2:
		dlg->m_data[tmp->si*dlg->width + tmp->sj] = 0;
		dlg->m_tile[tmp->si*dlg->width + tmp->sj].SetColor(BLACK, GREEN);
		dlg->m_tile[tmp->si*dlg->width + tmp->sj].SetWindowTextA("0");
		break;
	case 3:
	case 4:
		dlg->m_data[tmp->di*dlg->width + tmp->dj] = 0;
		dlg->m_tile[tmp->di*dlg->width + tmp->dj].SetColor(BLACK, GREEN);
		dlg->m_tile[tmp->di*dlg->width + tmp->dj].SetWindowTextA("0");
		break;
	}

	memcpy((int*)tmp+nColumn-1, &newValue, sizeof(int));
	strSubItemText = str;
	dlg->Refresh();
	return 1;
}