#pragma once
#include "gameobject.h"

class CObstacleObject :
	public CGameObject
{
public:
	CObstacleObject(SObstacleData *data, LogicPosition position);
	~CObstacleObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	Position position;
	SObstacleData *data;
};
