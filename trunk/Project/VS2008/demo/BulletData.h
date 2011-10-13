#pragma once
#include <string.h>

struct SBulletData
{
	//logic attributes
	char BulletName[50];
	int MoveSpeed;
	int Damage;
	void* Target;

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SBulletData(char* BulletName, int MoveSpeed, int Damage, void* Target, int ModelID, int SoundID)
	{
		strcpy(this->BulletName, BulletName);
		this->MoveSpeed = MoveSpeed;
		this->Damage = Damage;
		this->Target = Target;
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}
};