// EnemyPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "EnemyPropertiesDlg.h"
#include "afxdialogex.h"


// CEnemyPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CEnemyPropertiesDlg, CDialogEx)

CEnemyPropertiesDlg::CEnemyPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnemyPropertiesDlg::IDD, pParent)
	, autoID(1)
{

}

CEnemyPropertiesDlg::~CEnemyPropertiesDlg()
{
}

void CEnemyPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EPLIST, m_epLst);
	DDX_Control(pDX, IDC_EDITCELL, m_wndEdit);
	//  DDX_Control(pDX, IDC_EDITCOMBO, m_wndCombo);
	DDX_Control(pDX, IDC_COMBOCELL, m_wndCombo);
}


BEGIN_MESSAGE_MAP(CEnemyPropertiesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADDEP, &CEnemyPropertiesDlg::OnBnClickedAddep)
	ON_BN_CLICKED(IDC_DELEP, &CEnemyPropertiesDlg::OnClickedDelep)
//	ON_COMMAND(IDC_ADDTP, &CEnemyPropertiesDlg::OnAddtp)
END_MESSAGE_MAP()


// CEnemyPropertiesDlg message handlers


void CEnemyPropertiesDlg::FillListBox(void)
{
	if (!m_epLstData) return;
	m_epLst.Reset();
	AddColumns();
	m_epLstData->BeginTravel();
	int i=0;
	while (!m_epLstData->IsEndOfTravel()) {
		int key;
		EnemyProperties *tmp = m_epLstData->Travel(key);
		if (key > autoID) autoID = key+1;
		CString str;
		str.Format("%d", key);
		m_epLst.InsertItem(i, str);
		str.Format("%d", tmp->mHP);
		m_epLst.SetItemText(i, 1, str);
		str.Format("%d", tmp->mArmor);
		m_epLst.SetItemText(i, 2, str);
		str.Format("%d", tmp->mSpeed);
		m_epLst.SetItemText(i, 3, str);
		str.Format("%d", tmp->mCost);
		m_epLst.SetItemText(i, 4, str);
		str.Format("%d", tmp->mModelID);
		m_epLst.SetItemText(i, 5, str);
		str.Format(tmp->mAlias);
		m_epLst.SetItemText(i, 6, str);
		i++;
	}
}


void CEnemyPropertiesDlg::AddColumns(void)
{
	m_epLst.InsertColumn(0, "Enemy ID", LVCFMT_LEFT, 70);
	m_epLst.InsertColumn(1, "HP", LVCFMT_LEFT, 50);
	m_epLst.InsertColumn(2, "Armor", LVCFMT_LEFT, 50);
	m_epLst.InsertColumn(3, "Speed", LVCFMT_LEFT, 50);
	m_epLst.InsertColumn(4, "Cost", LVCFMT_LEFT, 50);
	m_epLst.InsertColumn(5, "Model ID", LVCFMT_LEFT, 70);
	m_epLst.InsertColumn(6, "Alias Name", LVCFMT_LEFT, 70);
	m_epLst.SetColumnReadOnly(0);
	m_epLst.SetDefaultEditor(NULL, &CEnemyPropertiesDlg::EndEditCell, &m_wndEdit);
	m_epLst.SetColumnEditor(5, &CEnemyPropertiesDlg::InitEditor,&CEnemyPropertiesDlg::EndEditCell, &m_wndCombo);
}


void CEnemyPropertiesDlg::OnBnClickedAddep()
{
	// TODO: Add your control notification handler code here
	int hp=100, armor=10, speed=5, cost=7;
	m_epLstData->AddItem(autoID++, new EnemyProperties(hp,armor,speed,cost));
	FillListBox();
}


void CEnemyPropertiesDlg::OnClickedDelep()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_epLst.GetFirstSelectedItemPosition();
	if (pos) {
		int sel = (int)pos-1;
		CString str = m_epLst.GetItemText(sel,0);
		int key;
		sscanf(str,"%d", &key);

		m_epLstData->RemoveItem(key);
		FillListBox();

		m_epLst.SetFocus();
		m_epLst.SetItemState(sel, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	}
}


BOOL CEnemyPropertiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	FillListBox();
	m_epLst.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CEnemyPropertiesDlg::InitEditor(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	switch (nColumn) {
	case 5:
		{
			CListCtrlEx* lst = (CListCtrlEx*)pThis;
			CComboBox* comboBox = (CComboBox*)*pWnd;
			comboBox->ResetContent();
			CEnemyPropertiesDlg* dlg = (CEnemyPropertiesDlg*)(lst->GetParent());

			GameTutor::CLutI<ModelProperties*> *m_mpLstData = dlg->m_mpLstData;
			m_mpLstData->BeginTravel();
			while (!m_mpLstData->IsEndOfTravel()) {
				int key;
				m_mpLstData->Travel(key);
				CString str;
				str.Format("%x",key);
				comboBox->AddString(str);
			}
			comboBox->SelectString(0, strSubItemText);
		}
		break;
	}
	return 1;
}

BOOL CEnemyPropertiesDlg::EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	CListCtrlEx* lst = (CListCtrlEx*)pThis;
	CEnemyPropertiesDlg* dlg = (CEnemyPropertiesDlg*)(lst->GetParent());
	CEdit* editBox = (CEdit*)*pWnd;

	dlg->UpdateData(TRUE);
	CString str;
	editBox->GetWindowTextA(str);
	if (nColumn == 6) {
		if (str.GetLength() >= MAX_LENGTH_ALIASNAME) {
			CString error;
			error.Format("Alias name is too long. %d/MAX=%d",str.GetLength(), MAX_LENGTH_ALIASNAME-1);
			dlg->MessageBox(error);
			return 0;
		}
	}
	strSubItemText = str;
	int key;
	//TODO
	CString keydata = lst->GetItemText(nRow, 0);
	sscanf(keydata, "%d", &key);

	EnemyProperties *tmp;
	dlg->m_epLstData->GetElement(key, tmp);

	switch (nColumn) {
	case 6:
		{
			memcpy((int*)tmp+5, strSubItemText.GetBuffer(0), MAX_LENGTH_ALIASNAME);
		}
		break;
	default:
		int newValue;
		sscanf(strSubItemText, "%d", &newValue );
		memcpy((int*)tmp+nColumn-1, &newValue, sizeof(int));
	}
	return 1;
}


//void CEnemyPropertiesDlg::OnAddtp()
//{
//	// TODO: Add your command handler code here
//}
