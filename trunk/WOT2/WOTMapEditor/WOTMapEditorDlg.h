// WOTMapEditorDlg.h : header file
//

#if !defined(AFX_WOTMAPEDITORDLG_H__48691B66_A256_4B97_AE58_DC10A1AF5CE5__INCLUDED_)
#define AFX_WOTMAPEDITORDLG_H__48691B66_A256_4B97_AE58_DC10A1AF5CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWOTMapEditorDlg dialog
#include "WOTMapfile.h"
#include "colorBtn.h"
#include "dlgbars.h"
#include "LibAI.h"
#include "CList.h"
#include "NewMapDlg.h"
#include "ChooseWayDlg.h"
#include "ScrollDialog.h"
#include "WayManagerDlg.h"
#include "EnemyPropertiesDlg.h"
#include "TowerPropertiesDlg.h"
#include "WaveManagerDlg.h"
#include "ModelManagerDlg.h"
#include "GeneralSettingDlg.h"
using namespace GameTutor;

#define BASE_TILE 2000
#define MAX_TILE 3000

class CWOTMapEditorDlg : public CDialog
{
// Construction
public:
	CWOTMapEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWOTMapEditorDlg)
	enum { IDD = IDD_WOTMAPEDITOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWOTMapEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CColorButton *m_tile;
	CWOTMapfile *m_mapfile;
	int *m_data;
	int iStart, jStart, iEnd, jEnd;
	int m_toPlace;
	AStar *astar;
	CString filename;

	CDlgToolBar     m_toolBar;
	GameTutor::CList<cell>* m_list;
	CNewMapDlg m_newMapDlg;
	CChooseWayDlg *m_chooseWayDlg;
	CWayManagerDlg *m_wayManagerDlg;
	CEnemyPropertiesDlg *m_enemyPropertiesDlg;
	CTowerPropertiesDlg *m_towerPropertiesDlg;
	CWaveManagerDlg *m_waveManagerDlg;
	CModelManagerDlg *m_modelManagerDlg;
	CGeneralSettingDlg *m_generalSettingDlg;
	// Generated message map functions
	//{{AFX_MSG(CWOTMapEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHelpAbout();
	afx_msg void OnFileExit();
	afx_msg void OnIncreaseTile(UINT nID);
	afx_msg void OnGrass();
	afx_msg void OnUpdateGrass(CCmdUI* pCmdUI);
	afx_msg void OnBlackhole();
	afx_msg void OnUpdateBlackhole(CCmdUI* pCmdUI);
	afx_msg void OnRiver();
	afx_msg void OnUpdateRiver(CCmdUI* pCmdUI);
	afx_msg void OnTree();
	afx_msg void OnUpdateTree(CCmdUI* pCmdUI);
	afx_msg void OnFindshortest();
	afx_msg void OnResetshortest();
	afx_msg void OnFileOpen();
	afx_msg void OnMoutain();
	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKickIdle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Clear();
	void Init(bool isCreatingFile = true);
public:
	afx_msg void OnMapWaymanager();
	void StartupConfig(void);
	afx_msg void OnUpdateMoutain(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSaveas(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMapWaymanager(CCmdUI *pCmdUI);
	void arrangeToolbar(void);
	afx_msg void OnMapEnemyproperties();
	afx_msg void OnUpdateMapEnemyproperties(CCmdUI *pCmdUI);
	afx_msg void OnMapTowerproperties();
	afx_msg void OnUpdateMapTowerproperties(CCmdUI *pCmdUI);
	afx_msg void OnMapWavemanager();
	afx_msg void OnUpdateMapWavemanager(CCmdUI *pCmdUI);
	afx_msg void OnMapModelmanager();
	afx_msg void OnUpdateMapModelmanager(CCmdUI *pCmdUI);
	afx_msg void OnBanana();
	afx_msg void OnUpdateBanana(CCmdUI *pCmdUI);
	afx_msg void OnCoconut();
	afx_msg void OnUpdateCoconut(CCmdUI *pCmdUI);
	afx_msg void OnMapGeneralsetting();
	afx_msg void OnUpdateMapGeneralsetting(CCmdUI *pCmdUI);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WOTMAPEDITORDLG_H__48691B66_A256_4B97_AE58_DC10A1AF5CE5__INCLUDED_)
