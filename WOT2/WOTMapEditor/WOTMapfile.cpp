// WOTMapfile.cpp: implementation of the CWOTMapfile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WOTMapEditor.h"
#include "WOTMapfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWOTMapfile::CWOTMapfile()
{
	m_lstTower = new GameTutor::CList<GameObjectType*>();
	m_lstNature = new GameTutor::CList<GameObjectType*>();
	m_lstWay = new GameTutor::CLutI<Way*>();
	m_lstTowerProperties = new GameTutor::CLutI<TowerProperties*>();
	m_lstEnemyProperties = new GameTutor::CLutI<EnemyProperties*>();
	m_lstWave = new GameTutor::CList<Wave*>();
	m_lstModelProperties = new GameTutor::CLutI<ModelProperties*>();
	init();
}

CWOTMapfile::~CWOTMapfile()
{
	m_lstTower->DeallocateElementPointer();
	m_lstNature->DeallocateElementPointer();
	m_lstWay->DeallocateElementPointer();
	m_lstTowerProperties->DeallocateElementPointer();
	m_lstEnemyProperties->DeallocateElementPointer();
	m_lstWave->DeallocateElementPointer();
}

void CWOTMapfile::init() {
	
}
bool CWOTMapfile:: loadfromFile(char* filename) {
	this->Clear();

	FILE *fp = NULL;
	fp=fopen(filename, "rb");
	fread(&width, sizeof(width), 8, fp);
	
	int i;
	for (i=0;i<nWays;i++) {
		int key;
		fread(&key, sizeof(key), 1, fp);
		Way *tmp = new Way();
		fread(tmp, sizeof(Way), 1, fp);
		m_lstWay->AddItem(key,tmp);
	}

	for (i=0;i<nObjects;i++) {
		GameObjectType *tmp = new GameObjectType();
		fread(tmp, sizeof(GameObjectType), 1, fp);
		if ((tmp->ID & 0xF0000000) == TILE_BANANA)
			m_lstNature->AddItem(tmp);
		else if ((tmp->ID & 0xF0000000) == TOWER_GUN)
			m_lstTower->AddItem(tmp);
	}

	for (i=0;i<nTowerProperties;i++) {
		int key;
		fread(&key, sizeof(key), 1, fp);
		TowerProperties *tmp = new TowerProperties();
		fread(tmp, sizeof(TowerProperties) - sizeof(GameTutor::CList<__INT32> *), 1, fp);
		m_lstTowerProperties->AddItem(key, tmp);
	}

	for (i=0;i<nEnemyProperties;i++) {
		int key;
		fread(&key, sizeof(key), 1, fp);
		EnemyProperties *tmp = new EnemyProperties();
		fread(tmp, sizeof(EnemyProperties), 1, fp);
		m_lstEnemyProperties->AddItem(key, tmp);
	}

	for (i=0;i<nWaves;i++) {
		Wave* tmp = new Wave();
		fread(tmp, sizeof(Wave), 1, fp);
		m_lstWave->AddItem(tmp);
	}

	for (i=0;i<nModels;i++) {
		int key;
		fread(&key, sizeof(key), 1, fp);
		ModelProperties* tmp = new ModelProperties();
		fread(tmp, sizeof(ModelProperties), 1, fp);
		m_lstModelProperties->AddItem(key, tmp);
	}

	fread(background,sizeof(char),MAX_LENGTH_FILENAME,fp);
	fread(&InitMoney,sizeof(int),1,fp);

	this->buildTowerTree();
	fclose(fp);
	return true;
}
void CWOTMapfile:: writetoFile(char* filename) {
	FILE *fp;
	fp=fopen(filename, "wb");
	printf("C%d\n",this);
	printf("C%d\n",&width);
	nWays = m_lstWay->GetCount();
	nTowerProperties = m_lstTowerProperties->GetCount();
	nEnemyProperties = m_lstEnemyProperties->GetCount();
	nWaves = m_lstWave->GetCount();
	nModels = m_lstModelProperties->GetCount();
	fwrite(&width, sizeof(width), 8, fp);

	m_lstWay->BeginTravel();
	while(!m_lstWay->IsEndOfTravel()) {
		int key;
		Way *tmp = m_lstWay->Travel(key);
		fwrite(&key, sizeof(key), 1, fp);
		fwrite(tmp, sizeof(Way), 1, fp);
	}

	m_lstTower->BeginTravel();
	while(!m_lstTower->IsEndOfTravel()) {
		fwrite(m_lstTower->Travel(), sizeof(GameObjectType), 1, fp);
	}

	m_lstNature->BeginTravel();
	while(!m_lstNature->IsEndOfTravel()) {
		fwrite(m_lstNature->Travel(), sizeof(GameObjectType), 1, fp);
	}

	m_lstTowerProperties->BeginTravel();
	while(!m_lstTowerProperties->IsEndOfTravel()) {
		int key;
		TowerProperties* tmp = m_lstTowerProperties->Travel(key);
		fwrite(&key, sizeof(key), 1, fp);
		fwrite(tmp, sizeof(TowerProperties) - sizeof(GameTutor::CList<__INT32> *), 1, fp);
	}

	m_lstEnemyProperties->BeginTravel();
	while(!m_lstEnemyProperties->IsEndOfTravel()) {
		int key;
		EnemyProperties* tmp = m_lstEnemyProperties->Travel(key);
		fwrite(&key, sizeof(key), 1, fp);
		fwrite(tmp, sizeof(EnemyProperties), 1, fp);
	}

	m_lstWave->BeginTravel();
	while (!m_lstWave->IsEndOfTravel()) {
		fwrite(m_lstWave->Travel(), sizeof(Wave), 1, fp);
	}

	m_lstModelProperties->BeginTravel();
	while(!m_lstModelProperties->IsEndOfTravel()) {
		int key;
		ModelProperties* tmp = m_lstModelProperties->Travel(key);
		fwrite(&key, sizeof(key), 1, fp);
		fwrite(tmp, sizeof(ModelProperties), 1, fp);
	}

	fwrite(background, sizeof(char), MAX_LENGTH_FILENAME, fp);
	fwrite(&InitMoney, sizeof(int), 1, fp);

	fclose(fp);
}
void CWOTMapfile:: printInfo() {
//	printf("Width = %d\nHeight = %d\nSX = %d; SY = %d\nDX = %d; DY = %d\nnObj = %d\n-----\n\n",
//		width, height, sourceX, sourceY, desX, desY, nObjects
//	);
}

void CWOTMapfile::Clear() {
	m_lstTower->DeallocateElementPointer();
	m_lstNature->DeallocateElementPointer();
	m_lstTowerProperties->DeallocateElementPointer();
	m_lstEnemyProperties->DeallocateElementPointer();
	m_lstWay->DeallocateElementPointer();
	m_lstWave->DeallocateElementPointer();
	m_lstModelProperties->DeallocateElementPointer();
	nObjects = nWays = nWaves = nTowerProperties = nEnemyProperties = nModels =  0;
}

void CWOTMapfile::syncfromArray(int *data) {
	int n = width*height;
	for (int i=0;i<height;i++) 
		for (int j=0;j<width;j++) {
			int pos = i*width+j;
			if ((data[pos] & 0xF0000000) == TILE_BANANA) {
				m_lstNature->AddItem(new GameObjectType(data[pos], i, j));
				
			}
			else if ((data[pos] & 0xF0000000) == TOWER_GUN) {
				m_lstTower->AddItem(new GameObjectType(data[pos], i, j));
			}
		}
	nObjects = m_lstNature->GetCount() + m_lstTower->GetCount();
}

void CWOTMapfile::synctoArray(int *&data) {
	if (data) {
		delete []data;
		data = NULL;
	}
	data = new int[width*height];
	int n = width*height;
	for (int i=0;i<n;i++)
		data[i] = TILE_GRASS;
	m_lstTower->BeginTravel();
	while(!m_lstTower->IsEndOfTravel()) {
		GameObjectType* tmp = m_lstTower->Travel();
		data[tmp->i*width + tmp->j] = tmp->ID;
	}

	m_lstNature->BeginTravel();
	while(!m_lstNature->IsEndOfTravel()) {
		GameObjectType* tmp = m_lstNature->Travel();
		data[tmp->i*width + tmp->j] = tmp->ID;
	}

	m_lstWay->BeginTravel();
	while(!m_lstWay->IsEndOfTravel()) {
		int key;
		Way* tmp = m_lstWay->Travel(key);
		data[tmp->si*width + tmp->sj] = key;
		data[tmp->di*width + tmp->dj] = key + 0x10000000;
	}
}

void CWOTMapfile::buildTowerTree(void)
{
	m_lstTowerProperties->BeginTravel();
	while(!m_lstTowerProperties->IsEndOfTravel()) {
		int childKey;
		TowerProperties *parent, *child = m_lstTowerProperties->Travel(childKey);
		if (child->mParentID != childKey) {
			m_lstTowerProperties->GetElement(child->mParentID, parent);
			parent->mLstChildren->AddItem(childKey);
		}
	}
}
