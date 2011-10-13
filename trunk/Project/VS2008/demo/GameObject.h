#pragma once
#include "GameData.h"

class CGameObject
{
public:
	CGameObject(void);
	virtual ~CGameObject(void);

	EGameObject ObjectType;
	int ObjectID;

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

};
