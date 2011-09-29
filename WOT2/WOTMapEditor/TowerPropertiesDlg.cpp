// TowerPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "TowerPropertiesDlg.h"
#include "afxdialogex.h"


// CTowerPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CTowerPropertiesDlg, CDialogEx)

CTowerPropertiesDlg::CTowerPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTowerPropertiesDlg::IDD, pParent)
	, autoID(TOWER_GUN)
{

}

CTowerPropertiesDlg::~CTowerPropertiesDlg()
{
}

void CTowerPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TPLIST, m_tpLst);
	DDX_Control(pDX, IDC_EDITCELL, m_wndEdit);
	DDX_Control(pDX, IDC_COMBOCELL, m_wndCombo);
}


BEGIN_MESSAGE_MAP(CTowerPropertiesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DELTP, &CTowerPropertiesDlg::OnClickedDeltp)
	ON_BN_CLICKED(IDC_ADDTP, &CTowerPropertiesDlg::OnClickedAddtp)
END_MESSAGE_MAP()


// CTowerPropertiesDlg message handlers

void CTowerPropertiesDlg::OnClickedAddtp()
{
	// TODO: Add your control notification handler code here
	int BaseDamage = 10,
		SpeedAttack = 1,
		Value = 10,
		Range = 2,
		Critical = 5;
	m_tpLstData->AddItem(autoID++, new TowerProperties(BaseDamage, SpeedAttack, Value, Range, Critical));
	FillListBox();
}


void CTowerPropertiesDlg::OnClickedDeltp()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_tpLst.GetFirstSelectedItemPosition();
	if (pos) {
		int sel = (int)pos-1;
		CString str = m_tpLst.GetItemText(sel,0);
		int key;
		sscanf(str,"%x", &key);

		m_tpLstData->RemoveItem(key);
		FillListBox();

		m_tpLst.SetFocus();
		m_tpLst.SetItemState(sel, LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	}
}

void CTowerPropertiesDlg::FillListBox(void)
{
	if (!m_tpLstData) return;
	m_tpLst.Reset();
	AddColumns();
	m_tpLstData->BeginTravel();
	int i=0;
	while (!m_tpLstData->IsEndOfTravel()) {
		int key;
		TowerProperties *tmp = m_tpLstData->Travel(key);
		if (key > autoID) autoID = key+1;
		CString str;
		str.Format("%x", key);
		m_tpLst.InsertItem(i, str);
		str.Format("%d", tmp->mBaseDamage);
		m_tpLst.SetItemText(i, 1, str);
		str.Format("%d", tmp->mSpeedAttack);
		m_tpLst.SetItemText(i, 2, str);
		str.Format("%d", tmp->mValue);
		m_tpLst.SetItemText(i, 3, str);
		str.Format("%d", tmp->mRange);
		m_tpLst.SetItemText(i, 4, str);
		str.Format("%d", tmp->mCritical);
		m_tpLst.SetItemText(i, 5, str);

		str.Format("%d", tmp->mPoison);
		m_tpLst.SetItemText(i, 6, str);

		str.Format("%d", tmp->mBaseDamage);
		m_tpLst.SetItemText(i, 7, str);
		str.Format("%d", tmp->mBoostSpeed);
		m_tpLst.SetItemText(i, 8, str);
		str.Format("%d", tmp->mCritical);
		m_tpLst.SetItemText(i, 9, str);

		str.Format("%x", tmp->mModelID);
		m_tpLst.SetItemText(i, 10, str);
		str.Format("%x", tmp->mParentID);
		m_tpLst.SetItemText(i, 11, str);

		str.Format("%d", tmp->mSkillID);
		m_tpLst.SetItemText(i, 12, str);

		str.Format(tmp->mAlias);
		m_tpLst.SetItemText(i, 13, str);
		i++;
	}
}


void CTowerPropertiesDlg::AddColumns(void)
{
	m_tpLst.InsertColumn(0, "Tower ID", LVCFMT_LEFT, 70);
	m_tpLst.InsertColumn(1, "Base Damage", LVCFMT_LEFT, 80);
	m_tpLst.InsertColumn(2, "Speed Attack", LVCFMT_LEFT, 90);
	m_tpLst.InsertColumn(3, "Value", LVCFMT_LEFT, 50);
	m_tpLst.InsertColumn(4, "Range", LVCFMT_LEFT, 50);
	m_tpLst.InsertColumn(5, "Critical", LVCFMT_LEFT, 50);

	m_tpLst.InsertColumn(6, "Poison", LVCFMT_LEFT, 70);

	m_tpLst.InsertColumn(7, "Boost Damage", LVCFMT_LEFT, 85);
	m_tpLst.InsertColumn(8, "Boost Speed", LVCFMT_LEFT, 75);
	m_tpLst.InsertColumn(9, "Boost Critical", LVCFMT_LEFT, 75);


	m_tpLst.InsertColumn(10, "Model ID", LVCFMT_LEFT, 70);
	m_tpLst.InsertColumn(11, "Parent Tower", LVCFMT_LEFT, 80);
	m_tpLst.InsertColumn(12, "Skill ID", LVCFMT_LEFT, 70);
	m_tpLst.InsertColumn(13, "Alias Name", LVCFMT_LEFT, 70);
	m_tpLst.SetColumnReadOnly(0);
	m_tpLst.SetDefaultEditor(NULL, &CTowerPropertiesDlg::EndEditCell, &m_wndEdit);
	m_tpLst.SetColumnEditor(10, &CTowerPropertiesDlg::InitEditor,&CTowerPropertiesDlg::EndEditCell, &m_wndCombo);
	m_tpLst.SetColumnEditor(11, &CTowerPropertiesDlg::InitEditor,&CTowerPropertiesDlg::EndEditCell, &m_wndCombo);
}

BOOL CTowerPropertiesDlg::InitEditor(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	switch (nColumn) {
	case 10:
		{
			CListCtrlEx* lst = (CListCtrlEx*)pThis;
			CComboBox* comboBox = (CComboBox*)*pWnd;
			comboBox->ResetContent();
			CTowerPropertiesDlg* dlg = (CTowerPropertiesDlg*)(lst->GetParent());

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
	case 11:
		{
			CListCtrlEx* lst = (CListCtrlEx*)pThis;
			CComboBox* comboBox = (CComboBox*)*pWnd;
			comboBox->ResetContent();
			CTowerPropertiesDlg* dlg = (CTowerPropertiesDlg*)(lst->GetParent());

			GameTutor::CLutI<TowerProperties*> *m_tpLstData = dlg->m_tpLstData;
			m_tpLstData->BeginTravel();
			while (!m_tpLstData->IsEndOfTravel()) {
				int key;
				m_tpLstData->Travel(key);
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
BOOL CTowerPropertiesDlg::EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate) {
	CListCtrlEx* lst = (CListCtrlEx*)pThis;
	CTowerPropertiesDlg* dlg = (CTowerPropertiesDlg*)(lst->GetParent());
	CEdit* editBox = (CEdit*)*pWnd;

	dlg->UpdateData(TRUE);

	CString str;
	editBox->GetWindowTextA(str);
	if (nColumn == 13) {
		if (str.GetLength() >= MAX_LENGTH_ALIASNAME) {
			CString error;
			error.Format("Alias name is too long. %d/MAX=%d",str.GetLength(), MAX_LENGTH_ALIASNAME-1);
			dlg->MessageBox(error);
			return 0;
		}
	}

	strSubItemText = str;
	int key;
	CString keydata = lst->GetItemText(nRow, 0);
	sscanf(keydata, "%x", &key);
	TowerProperties *tmp;
	dlg->m_tpLstData->GetElement(key, tmp);

	switch (nColumn) {
	case 11:
		{
			int newValue;
			sscanf(strSubItemText, "%x", &newValue );
			memcpy((int*)tmp+nColumn-1, &newValue, sizeof(int));
		}
		break;
	case 13:
		{
			memcpy((int*)tmp+12, strSubItemText.GetBuffer(0), MAX_LENGTH_ALIASNAME);
		}
		break;
	default:
		int newValue;
		sscanf(strSubItemText, "%d", &newValue );
		memcpy((int*)tmp+nColumn-1, &newValue, sizeof(int));
	}

	return 1;
}

BOOL CTowerPropertiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	FillListBox();
	m_tpLst.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
