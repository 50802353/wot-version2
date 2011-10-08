#pragma once

struct SObstacleData
{
	//logic attributes
	char ObstacleName[50];

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SObstacleData(char* ObstacleName, int ModelID, int SoundID)
	{
		strcpy(this->ObstacleName, ObstacleName);
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}
};