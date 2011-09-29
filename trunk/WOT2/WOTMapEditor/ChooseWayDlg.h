#if !defined(AFX_CHOOSEWAYDLG_H__94A4DCF1_183B_4C95_B767_D96FD727097E__INCLUDED_)
#define AFX_CHOOSEWAYDLG_H__94A4DCF1_183B_4C95_B767_D96FD727097E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseWayDlg.h : header file
//

#include "listctrlex.h"
#include "CList.h"
#include "WOTMapfile.h"

/////////////////////////////////////////////////////////////////////////////
// CChooseWayDlg dialog

class CChooseWayDlg : public CDialog
{
// Construction
public:
	CChooseWayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseWayDlg)
	enum { IDD = IDD_CHOOSEWAY };
	int		m_iDes;
	int		m_iSrc;
	int		m_jDes;
	int		m_jSrc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseWayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseWayDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnUpdateWayList(CCmdUI* );
	afx_msg void OnUpdateManualPosition(CCmdUI* );
	afx_msg void OnKickIdle();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	CListCtrlEx m_wayLst;
	void FillListBox(void);
	// Init Column Header for List
	void AddColumns(void);
	virtual BOOL OnInitDialog();
	GameTutor::CLutI<Way*>* m_wayLstData;
	BOOL m_useWay;
	Way* m_selectedWay;
	afx_msg void OnBnClickedOk();
//	afx_msg void OnBnClickedCheckuseway();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnBnClickedSelect();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEWAYDLG_H__94A4DCF1_183B_4C95_B767_D96FD727097E__INCLUDED_)
