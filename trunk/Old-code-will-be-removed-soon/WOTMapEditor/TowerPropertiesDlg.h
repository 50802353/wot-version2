#pragma once


// CTowerPropertiesDlg dialog
#include "WOTMapfile.h"
#include "ListCtrlEx.h"
#include "CLookupTableI.h"

class CTowerPropertiesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTowerPropertiesDlg)

public:
	CTowerPropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTowerPropertiesDlg();

// Dialog Data
	enum { IDD = IDD_TOWERPROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrlEx m_tpLst;
	GameTutor::CLutI<TowerProperties*> *m_tpLstData;
	GameTutor::CLutI<ModelProperties*> *m_mpLstData;

	void FillListBox(void);
	void AddColumns(void);
	static BOOL InitEditor(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	static BOOL EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
//	CEdit m_wndEdit;
	afx_msg void OnClickedAddtp();
	afx_msg void OnClickedDeltp();
private:
	int autoID;
public:
	virtual BOOL OnInitDialog();
	CListCtrlEx m_tpLst;
	CEdit m_wndEdit;
	CComboBox m_wndCombo;
};
