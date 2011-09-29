#pragma once


// CModelManagerDlg dialog
#include "WOTMapfile.h"
#include "ListCtrlEx.h"
#include "CLookupTableI.h"

class CModelManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelManagerDlg)

public:
	CModelManagerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModelManagerDlg();

// Dialog Data
	enum { IDD = IDD_MODELMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_wndEdit;
	CListCtrlEx m_mpLst;

	GameTutor::CLutI<ModelProperties*> *m_mpLstData;

	void FillListBox(void);
	void AddColumns(void);

	static BOOL EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
	virtual BOOL OnInitDialog();
	int autoID;
	afx_msg void OnBnClickedAddmp();
	afx_msg void OnBnClickedDelmp();
};
