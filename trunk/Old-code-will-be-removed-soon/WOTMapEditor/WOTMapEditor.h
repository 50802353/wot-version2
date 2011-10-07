// WOTMapEditor.h : main header file for the WOTMAPEDITOR application
//

#if !defined(AFX_WOTMAPEDITOR_H__134332A8_7F4D_48C7_8867_3ACFD3E67233__INCLUDED_)
#define AFX_WOTMAPEDITOR_H__134332A8_7F4D_48C7_8867_3ACFD3E67233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWOTMapEditorApp:
// See WOTMapEditor.cpp for the implementation of this class
//

class CWOTMapEditorApp : public CWinApp
{
public:
	CWOTMapEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWOTMapEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWOTMapEditorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WOTMAPEDITOR_H__134332A8_7F4D_48C7_8867_3ACFD3E67233__INCLUDED_)
