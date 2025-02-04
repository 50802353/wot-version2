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
	void Update(int delta_time);
	void Render();
	void Destroy();

	Position position;
	LogicPosition logicposition;
	SObstacleData *data;

	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//chua nghi ra
	//TODO------------------------------------------------------------------------------
};

#endif