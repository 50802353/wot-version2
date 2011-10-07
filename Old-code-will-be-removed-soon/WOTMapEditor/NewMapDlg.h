#if !defined(AFX_NEWMAPDLG_H__D41F8F2A_0FE6_4D55_9B3A_C3DE9F051BAF__INCLUDED_)
#define AFX_NEWMAPDLG_H__D41F8F2A_0FE6_4D55_9B3A_C3DE9F051BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewMapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewMapDlg dialog

class CNewMapDlg : public CDialog
{
// Construction
public:
	CNewMapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewMapDlg)
	enum { IDD = IDD_NEWMAP };
	int		m_row;
	int		m_column;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewMapDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWMAPDLG_H__D41F8F2A_0FE6_4D55_9B3A_C3DE9F051BAF__INCLUDED_)
