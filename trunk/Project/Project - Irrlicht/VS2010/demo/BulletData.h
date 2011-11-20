#ifndef __BULLETDATA_H__
#define __BULLETDATA_H__

#include <string.h>

struct SBulletData
{
	//logic attributes
	char BulletName[50];
	int MoveSpeed;
	int Damage;

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SBulletData(char* BulletName, int MoveSpeed, int Damage, int ModelID, int SoundID)
	{
		strcpy(this->BulletName, BulletName);
		this->MoveSpeed = MoveSpeed;
		this->Damage = Damage;
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}
};

#endif