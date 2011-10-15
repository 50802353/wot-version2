#ifndef __OBSTACLEOBJECT_H__
#define __OBSTACLEOBJECT_H__

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

	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//chua nghi ra
	//TODO------------------------------------------------------------------------------
};

#endif