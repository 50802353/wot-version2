// WaveManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "WaveManagerDlg.h"
#include "afxdialogex.h"


// CWaveManagerDlg dialog

IMPLEMENT_DYNAMIC(CWaveManagerDlg, CDialogEx)

CWaveManagerDlg::CWaveManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWaveManagerDlg::IDD, pParent)
{

}

CWaveManagerDlg::~CWaveManagerDlg()
{
}

void CWaveManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITCELL, m_wndEdit);
	DDX_Control(pDX, IDC_WAVELST, m_waveLst);
	DDX_Control(pDX, IDC_COMBOCELL, m_wndCombo);
}


BEGIN_MESSAGE_MAP(CWaveManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADDWAVE, &CWaveManagerDlg::OnBnClickedAddwave)
	ON_BN_CLICKED(IDC_DELWAVE, &CWaveManagerDlg::OnBnClickedDelwave)
	ON_CBN_SELCHANGE(IDC_COMBOCELL, &CWaveManagerDlg::OnCbnSelchangeCombocell)
END_MESSAGE_MAP()


// CWaveManagerDlg message handlers


void CWaveManagerDlg::OnBnClickedAddwave()
{
	// TODO: Add your control notification handler code here
	int enemyType = 0,
		amount = 10,
		wayID = 0x20000000;
	m_waveLstData->AddItem(new Wave(enemyType, amount, wayID));
	FillListBox();
}


void CWaveManagerDlg::OnBnClickedDelwave()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_waveLst.GetFirstSelectedItemPosition();
	if (pos) {
		int sel = (int)pos-1;
		Wave *tmp = m_waveLstData->GetElement(sel);
		m_waveLstData->RemoveItem(tmp);
		FillListBox();

		m_waveLst.SetFocus();
		m_waveLst.SetItemState(sel, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	}
}


BOOL CWaveManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	FillListBox();



	m_waveLst.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CWaveManagerDlg::FillListBox(void)
{
if (!m_waveLstData) return;
	m_waveLst.Reset();
	AddColumns();
	m_waveLstData->BeginTravel();
	int i=0;
	while (!m_waveLstData->IsEndOfTravel()) {
		Wave *tmp = m_waveLstData->Travel();
		CString str;
		str.Format("%x", i);
		m_waveLst.InsertItem(i, str);
		str.Format("%d", tmp->enemyType);
		m_waveLst.SetItemText(i, 1, str);
		str.Format("%d", tmp->amount);
		m_waveLst.SetItemText(i, 2, str);
		str.Format("%x", tmp->wayID);
		m_waveLst.SetItemText(i, 3, str);
		i++;
	}
}


void CWaveManagerDlg::AddColumns(void)
{
	m_waveLst.InsertColumn(0, "Order", LVCFMT_LEFT, 70);
	m_waveLst.InsertColumn(1, "Enemy ID", LVCFMT_LEFT, 70);
	m_waveLst.InsertColumn(2, "amount", LVCFMT_LEFT, 50);
	m_waveLst.InsertColumn(3, "wayID", LVCFMT_LEFT, 70);
	m_waveLst.SetColumnReadOnly(0);
	m_waveLst.SetDefaultEditor(NULL, &CWaveManagerDlg::EndEditCell, &m_wndEdit);
	m_waveLst.SetColumnEditor(1, &CWaveManagerDlg::InitEditor,  &CWaveManagerDlg::EndEditCell,&m_wndCombo);
	m_waveLst.SetColumnEditor(3, &CWaveManagerDlg::InitEditor,  &CWaveManagerDlg::EndEditCell,&m_wndCombo);
}

BOOL CWaveManagerDlg::InitEditor(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	switch (nColumn) {
	case 1:
		{
			CListCtrlEx* lst = (CListCtrlEx*)pThis;
			CComboBox* comboBox = (CComboBox*)*pWnd;
			comboBox->ResetContent();
			CWaveManagerDlg* dlg = (CWaveManagerDlg*)(lst->GetParent());
			GameTutor::CLutI<EnemyProperties*> *m_epLstData = dlg->m_epLstData;
			m_epLstData->BeginTravel();
			while (!m_epLstData->IsEndOfTravel()) {
				int key;
				m_epLstData->Travel(key);
				CString str;
				str.Format("%d",key);
				comboBox->AddString(str);
			}
			comboBox->SelectString(0, strSubItemText);
		}
		break;
	case 2:
		break;
	case 3:
		{
			CListCtrlEx* lst = (CListCtrlEx*)pThis;
			CComboBox* comboBox = (CComboBox*)*pWnd;
			comboBox->ResetContent();
			CWaveManagerDlg* dlg = (CWaveManagerDlg*)(lst->GetParent());
			GameTutor::CLutI<Way*> *m_wayLstData = dlg->m_wayLstData;
			m_wayLstData->BeginTravel();
			while (!m_wayLstData->IsEndOfTravel()) {
				int key;
				m_wayLstData->Travel(key);
				CString str;
				str.Format("%x",key);
				comboBox->AddString(str);
			}
			comboBox->SelectString(1, strSubItemText);
		}
		break;
	}
	return 1;
}

BOOL CWaveManagerDlg::EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	CListCtrlEx* lst = (CListCtrlEx*)pThis;
	CWaveManagerDlg* dlg = (CWaveManagerDlg*)(lst->GetParent());
	int newValue;
	switch (nColumn) {
	case 1:
		{
			CComboBox* comboBox = (CComboBox*)*pWnd;
			int index = comboBox->GetCurSel();
			if(index >= 0) comboBox->GetLBText(index, strSubItemText);
			sscanf(strSubItemText, "%x", &newValue );
		}
		break;
	case 2:
		{
			CEdit* editBox = (CEdit*)*pWnd;
			editBox->GetWindowTextA(strSubItemText);
			sscanf(strSubItemText, "%d", &newValue );
		}
		break;
	case 3:
		{
			CComboBox* comboBox = (CComboBox*)*pWnd;
			int index = comboBox->GetCurSel();
			if(index >= 0) comboBox->GetLBText(index, strSubItemText);
			sscanf(strSubItemText, "%x", &newValue );
		}
		break;
	}

	Wave *tmp = dlg->m_waveLstData->GetElement(nRow);
	memcpy((int*)tmp+nColumn-1, &newValue, sizeof(int));

	return 1;
}

void CWaveManagerDlg::OnCbnSelchangeCombocell()
{
	// TODO: Add your control notification handler code here
}
