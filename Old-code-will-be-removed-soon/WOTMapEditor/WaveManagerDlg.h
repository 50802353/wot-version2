#pragma once


// CWaveManagerDlg dialog
#include "WOTMapfile.h"
#include "ListCtrlEx.h"
#include "CList.h"

class CWaveManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWaveManagerDlg)

public:
	CWaveManagerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaveManagerDlg();

// Dialog Data
	enum { IDD = IDD_WAVEMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	GameTutor::CList<Wave*> *m_waveLstData;
	GameTutor::CLutI<EnemyProperties*> *m_epLstData;
	GameTutor::CLutI<Way*> *m_wayLstData;
	CEdit m_wndEdit;
	afx_msg void OnBnClickedAddwave();
	afx_msg void OnBnClickedDelwave();
	virtual BOOL OnInitDialog();
	CListCtrlEx m_waveLst;
	void FillListBox(void);
	void AddColumns(void);
	static BOOL InitEditor(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	static BOOL EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	CComboBox m_wndCombo;
	afx_msg void OnCbnSelchangeCombocell();
};
