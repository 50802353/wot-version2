#pragma once
#include <string.h>

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
};

struct SMapData
{
	//logic attributes
	char MapName[50];
	int Width;
	int Height;
	LogicPosition SourcePosition;
	LogicPosition DestinationPosition;

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SMapData(char* MapName, int Width, int Height, LogicPosition SourcePosition, LogicPosition DestinationPosition, int ModelID, int SoundID)
	{
		strcpy(this->MapName, MapName);
		this->Width = Width;
		this->Height = Height;
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}

};