#ifndef __MAPDATA_H__
#define __MAPDATA_H__

#include "EnemyData.h"

struct LogicPosition
{
	int x;
	int y;

	LogicPosition()
	{
		x=y=0;
	}

	LogicPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	LogicPosition operator = (const LogicPosition pos)
	{
		x = pos.x;
		y = pos.y;
		return pos;
	}

	LogicPosition operator + (const LogicPosition pos)
	{
		return LogicPosition(x + pos.x, y + pos.y);
	}

	bool operator == (const LogicPosition pos)
	{
		return (pos.x == x) && (pos.y == y);
	}
};

#define MAX_ENEMYS_PER_WAVE 20
struct SWaveData
{
	int Quantity;
	int SpawnTime[MAX_ENEMYS_PER_WAVE];
	SEnemyData* Enemy[MAX_ENEMYS_PER_WAVE];

	SWaveData(int Quantity,int* SpawnTime,SEnemyData** Enemy)
	{
		this->Quantity = Quantity;
		memset(this->SpawnTime, 0, sizeof(SpawnTime));
		memcpy(this->SpawnTime, SpawnTime, sizeof(int)*Quantity);
		memset(this->Enemy, 0, sizeof(this->Enemy));
		memcpy(this->Enemy, Enemy, sizeof(SEnemyData*)*Quantity);
	}
};

#define MAX_WAVES_PER_MAP 20
struct SMapData
{
	//logic attributes
	char MapName[50];
	int Width;
	int Height;
	LogicPosition SourcePosition;
	LogicPosition DestinationPosition;
	int GivenLife;
	int GivenMoney;
	int NumberOfWaves;
	SWaveData* Wave[MAX_WAVES_PER_MAP];
	STowerData* BasicTowerList[5];


	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SMapData(char* MapName, int Width, int Height, LogicPosition SourcePosition, LogicPosition DestinationPosition, int GivenLife, int GivenMoney, int NumberOfWaves, SWaveData** Wave, STowerData** BasicTowerList, int ModelID, int SoundID)
	{
		strcpy(this->MapName, MapName);
		this->Width = Width;
		this->Height = Height;
		this->SourcePosition = SourcePosition;
		this->DestinationPosition = DestinationPosition;
		this->GivenLife = GivenLife;
		this->GivenMoney = GivenMoney;
		this->NumberOfWaves = NumberOfWaves;
		memset(this->Wave, 0, sizeof(this->Wave));
		memcpy(this->Wave, Wave, sizeof(SWaveData*)*NumberOfWaves);
		memcpy(this->BasicTowerList,BasicTowerList, sizeof(STowerData*)*5);
		this->ModelID = ModelID;
		this->SoundID = SoundID;		
	}

};

#endif