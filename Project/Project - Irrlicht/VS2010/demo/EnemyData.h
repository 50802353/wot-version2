#ifndef __ENEMYDATA_H__
#define __ENEMYDATA_H__
#include "ModelData.h"

struct SEnemyData
{
	//logic attributes
	char EnemyName[50];
	int MaxHP;
	int MoveSpeed;
	int Bounty;
	//graphic attributes
	SModelData ModelData;
	
	//sound attributes
	int SoundID;

	SEnemyData(char* EnemyName, int MaxHP, int MoveSpeed, int Bounty, SModelData ModelData, int SoundID)
	{
		strcpy(this->EnemyName,EnemyName);
		this->MaxHP = MaxHP;
		this->MoveSpeed = MoveSpeed;
		this->Bounty = Bounty;
		this->ModelData = ModelData;
		this->SoundID = SoundID;
	}
};

#endif