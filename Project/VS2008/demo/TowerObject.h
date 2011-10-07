#pragma once
#include "gameobject.h"

class CTowerObject :
	public CGameObject
{
public:
	CTowerObject(void);
	~CTowerObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();

	Position position;
	STowerData *data;

	int damage;
	int range;



	

	


};
