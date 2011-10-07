#pragma once

struct SObstacleData
{
	//logic attributes
	char ObstacleName[50];
	enum TowerType	{E_TOWER_ATTACK, E_TOWER_BUFF};

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;
};