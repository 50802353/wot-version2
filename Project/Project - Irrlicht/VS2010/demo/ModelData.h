#ifndef __MODELDATA_H__
#define __MODELDATA_H__

#include "gametutor.h"

struct SModelData {
	char modelname[50];
	char skinname[50];
	char avatarname[50];
	core::vector3df scale;
	core::vector3df rotate;
	float speed;	

	SModelData(char* md2, char* skin, char* avatarname, core::vector3df scale, core::vector3df rotate, float speed)
	{
		strcpy(this->modelname, md2);
		strcpy(this->skinname, skin);
		strcpy(this->avatarname, avatarname);
		this->scale = scale;
		this->rotate = rotate;
		this->speed  = speed;
	}


	SModelData():scale(),rotate(),speed(0)
	{
		memset(modelname,0, sizeof(char)*50);
		memset(skinname,0, sizeof(char)*50);
	}
};
#endif