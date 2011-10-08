#pragma once
#include <string.h>

struct SBulletData
{
	//logic attributes
	char BulletName[50];
	int MoveSpeed;

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SBulletData(char* BulletName, int MoveSpeed, int ModelID, int SoundID)
	{
		strcpy(this->BulletName, BulletName);
		this->MoveSpeed = MoveSpeed;
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}
};