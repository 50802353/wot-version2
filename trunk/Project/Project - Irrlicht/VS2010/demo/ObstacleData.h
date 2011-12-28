#ifndef __OBSTACLEDATA_H__
#define __OBSTACLEDATA_H__

struct SObstacleData
{
	//logic attributes
	char ObstacleName[50];

	//graphic attributes
	SModelData ModelData;
	
	//sound attributes
	int SoundID;

	SObstacleData(char* ObstacleName, SModelData ModelData, int SoundID)
	{
		strcpy(this->ObstacleName, ObstacleName);
		this->ModelData = ModelData;
		this->SoundID = SoundID;
	}
};

#endif