#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "GameData.h"

class CGameObject
{
public:
	CGameObject(void);
	virtual ~CGameObject(void);

	EGameObject ObjectType;
	int ObjectID;

	virtual void Init()=0;
	virtual void Update(int delta_time)=0;
	virtual void Render()=0;
	virtual void Destroy()=0;

};

#endif