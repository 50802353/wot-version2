
#include "CStateIngame.h"

CStateIngame::CStateIngame():CState()
{}

void CStateIngame::Init()
{
	Log("State Ingame: Init");

	//Temp Data
	SMapData MapData1("MAP_NAME_1", 10, 10, LogicPosition(0,0), LogicPosition(10,10), 100, 20, 0, 0);
	STowerData TowerData1("TOWER_NAME_1",10,3,ETowerType::E_TOWER_ATTACK, 1, 1);
	SEnemyData EnemyData1("ENEMY_NAME_1",30,10,2,2);
	SObstacleData ObstacleData1("OBSTACLE_NAME_1",3,3);
	SBulletData BulletData1("BULLET_NAME_1",20,10,NULL,4,4);

	//TempObject:	2 tower at (5,0) and (8,5), 
	//				1 enemy at (2,2)
	//				1 obstacle at (3,3)

	ObjectManager.SetMapObject(new CMapObject(&MapData1));
	ObjectManager.AddObject(new CTowerObject(&TowerData1, LogicPosition(5,0)));
	ObjectManager.AddObject(new CTowerObject(&TowerData1, LogicPosition(8,5)));
	ObjectManager.AddObject(new CEnemyObject(&EnemyData1, LogicPosition(2,2)));
	ObjectManager.AddObject(new CObstacleObject(&ObstacleData1, LogicPosition(3,3)));

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glScalef(1.0/20,1.0/20,1.0/20);
	glTranslatef(-5,-5,0);

	
}

void CStateIngame::Update()
{
	ObjectManager.Update();
}

void CStateIngame::Render()
{
	//Log("State Ingame: Fps = %d FrameDT = %d", CFpsController::GetInstance()->GetRuntimeFps(), CFpsController::GetInstance()->GetFrameDt());
	CGraphics2D::GetInstance()->Clear(SColor<float>(0,0,0,1));
	ObjectManager.Render();
	CGraphics2D::GetInstance()->Flush();
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
}
