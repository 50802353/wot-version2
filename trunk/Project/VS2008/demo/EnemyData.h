#ifndef __ENEMYDATA_H__
#define __ENEMYDATA_H__

struct SEnemyData
{
	//logic attributes
	char EnemyName[50];
	int MaxHP;
	int MoveSpeed;

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SEnemyData(char* EnemyName, int MaxHP, int MoveSpeed, int ModelID, int SoundID)
	{
		strcpy(this->EnemyName,EnemyName);
		this->MaxHP = MaxHP;
		this->MoveSpeed = MoveSpeed;
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}
};

#endif