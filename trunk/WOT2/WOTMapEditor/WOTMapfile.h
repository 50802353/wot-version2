// WOTMapfile.h: interface for the CWOTMapfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WOTMAPFILE_H__E9E31BEF_2B22_4E0C_8A82_5A9BD24615D0__INCLUDED_)
#define AFX_WOTMAPFILE_H__E9E31BEF_2B22_4E0C_8A82_5A9BD24615D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CList.h"
#include "CLookupTableI.h"
#include "GameProperties.h"
using namespace GameTutor;


class CWOTMapfile  
{
public:
	int width, height;
	int nWays;
	int nObjects;
	int nTowerProperties;
	int nEnemyProperties;
	int nWaves;
	int nModels;

	GameTutor::CList<GameObjectType*> *m_lstTower;
	GameTutor::CList<GameObjectType*> *m_lstNature;
	GameTutor::CLutI<Way*> *m_lstWay;
	GameTutor::CLutI<TowerProperties*> *m_lstTowerProperties;
	GameTutor::CLutI<EnemyProperties*> *m_lstEnemyProperties;
	GameTutor::CList<Wave*> *m_lstWave;
	GameTutor::CLutI<ModelProperties*> *m_lstModelProperties;

	char background[MAX_LENGTH_FILENAME];

	int InitMoney;
	
	CWOTMapfile();
	virtual ~CWOTMapfile();
	void init();
	bool loadfromFile(char* filename);
	void writetoFile(char* filename);
	void syncfromArray(int *data);
	void synctoArray(int *&data);
	void printInfo();
	void Clear();
	void buildTowerTree(void);
};

#endif // !defined(AFX_WOTMAPFILE_H__E9E31BEF_2B22_4E0C_8A82_5A9BD24615D0__INCLUDED_)
