#ifndef __OBSTACLEOBJECT_H__
#define __OBSTACLEOBJECT_H__

#include "gameobject.h"

class CObstacleObject :
	public CGameObject
{
public:
	CObstacleObject(SObstacleData *data, int size);
	~CObstacleObject(void);

	void Init();
	void Update(int delta_time);
	void Render();
	void Destroy();

	int size;
	Position position;
	LogicPosition logicposition;
	SObstacleData *data;
	irr::scene::ISceneNode* sceneNode;
	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//chua nghi ra
	//TODO------------------------------------------------------------------------------
};

#endif