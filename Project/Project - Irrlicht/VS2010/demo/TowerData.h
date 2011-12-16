#ifndef __TOWERDATA_H__
#define __TOWERDATA_H__

#include <string.h>
#include "ModelData.h"

enum ETowerType 
{
	E_TOWER_ATTACK, 
	E_TOWER_BUFF,
};

struct STowerData
{
	//logic attributes
	char TowerName[50];
	int Damage;
	int Range;
	int AttackSpeed;
	int Cost;
	ETowerType TowerType;
	STowerData* UpgradeTowerList[5];

	//graphic attributes
	SModelData ModelData;
	
	//sound attributes
	int SoundID;

	STowerData(char* TowerName, int Damage, int Range, int AttackSpeed, int Cost, ETowerType TowerType, STowerData** upgradeList, SModelData ModelData, int SoundID)
	{
		strcpy(this->TowerName, TowerName);
		this->Damage = Damage;
		this->Range = Range;
		this->AttackSpeed = AttackSpeed;
		this->Cost = Cost;
		this->TowerType = TowerType;
		for (int i=0;i<5;i++)
			this->UpgradeTowerList[i] = upgradeList[i];
		this->ModelData = ModelData;
		this->SoundID = SoundID;		
	}
};

#endif