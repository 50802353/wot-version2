#ifndef __ENEMYOBJECT_H__
#define __ENEMYOBJECT_H__

#include "gameobject.h"
#include "MapObject.h"


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
	bool isSpawn;

	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	void Spawn(); // bat. co` isSpawn thanh` true, neu' true thi` moi' tuong tac' voi' tru.

	void Move(CMapObject* MapObject);//Tinh lai position hien tai cua quai vat dua vao cac thong so' sau
	// - movespeed cua enemy, cong thuc' tam. thoi` : 
	// - next position, lay tu MapObject->DirectionMap
	// - time_difference (delta time), lay tu ham` CFpsController::GetFrameDt()
	// - Cong thuc tam thoi: distance = movespeed*delta_time/10000
	// - new position = old position + distance neu' duong` di thang?, con` neu' be? cua thi` tinh' lai cho hop li'
	//		+ neu' newposition la destination thi goi ham ReachDestination
	//		+ nguoc lai , update ObjectMap

	void Damaged(int HP); // giam? mau' hien. tai. xuong' theo bien' HP, neu' <0 thi` die

	void Die(int* Money); //huy quai' vat, remove khoi map, tang money
	void ReachDestination(int* RemainingLife);  //den' dich', huy quai vat, remove khoi map, giam LIFE

	//TODO------------------------------------------------------------------------------


};

#endif