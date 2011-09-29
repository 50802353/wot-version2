#pragma once


// CWayManagerDlg dialog

#include "CList.h"
#include "WOTMapfile.h"
#include "ListCtrlEx.h"
#include "colorBtn.h"
#include "afxwin.h"

class CWayManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CWayManagerDlg)

public:
	CWayManagerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWayManagerDlg();

// Dialog Data
	enum { IDD = IDD_WAYMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void FillListBox(void);
	void AddColumns(void);
	CListCtrlEx m_wayLst;
	GameTutor::CLutI<Way*>* m_wayLstData;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddway();
	afx_msg void OnBnClickedDelway();

	int *m_data;
	CColorButton *m_tile;
	int width;
	int height;

	void Refresh(void);
	CEdit m_wndEdit;

	static BOOL EndEditCell(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);
private:
	int autoID;
};
