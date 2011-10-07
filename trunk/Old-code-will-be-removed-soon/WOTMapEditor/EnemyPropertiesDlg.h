#pragma once


// CEnemyPropertiesDlg dialog
#include "WOTMapfile.h"
#include "ListCtrlEx.h"
#include "CLookupTableI.h"

class CEnemyPropertiesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnemyPropertiesDlg)

public:
	CEnemyPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEnemyPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_ENEMYPROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrlEx m_epLst;
	GameTutor::CLutI<EnemyProperties*> *m_epLstData;
	GameTutor::CLutI<ModelProperties*> *m_mpLstData;

	void FillListBox(void);
	void AddColumns(void);

		static BOOL InitEditor(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	static BOOL EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	CEdit m_wndEdit;
	afx_msg void OnBnClickedAddep();
	afx_msg void OnClickedDelep();
	virtual BOOL OnInitDialog();
private:
	int autoID;
public:
//	afx_msg void OnAddtp();
//	CComboBox m_wndCombo;
	CComboBox m_wndCombo;
};
