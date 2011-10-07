#pragma once
#include <string.h>

struct SMapData
{
	//logic attributes
	char MapName[50];
	int Width;
	int Height;

	//graphic attributes
	int ModelID;
	
	//sound attributes
	int SoundID;

	SMapData(char* MapName, int Width, int Height, int ModelID, int SoundID)
	{
		strcpy(this->MapName, MapName);
		this->Width = Width;
		this->Height = Height;
		this->ModelID = ModelID;
		this->SoundID = SoundID;
	}

};