#pragma once
#include "gameobject.h"

class CEnemyObject :
	public CGameObject
{
public:
	CEnemyObject(SEnemyData* data, LogicPosition position);
	~CEnemyObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	Position position;
	SEnemyData *data;


};
