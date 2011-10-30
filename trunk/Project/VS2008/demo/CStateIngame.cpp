
#include "CStateIngame.h"



	
//--------------------------


CStateIngame::CStateIngame():CState()
{}

void CStateIngame::Init()
{
	Log("State Ingame: Init");

	

	//TempObject:	2 tower at (5,0) and (8,5), 
	//				1 enemy at (2,2)
	//				1 obstacle at (3,3)

	/*ObjectManager.SetMapObject(new CMapObject(&MapData1));
	ObjectManager.AddObject(new CTowerObject(&TowerData1, LogicPosition(5,0)));
	ObjectManager.AddObject(new CTowerObject(&TowerData1, LogicPosition(8,5)));
	ObjectManager.AddObject(new CEnemyObject(&EnemyData1, LogicPosition(2,2)));
	ObjectManager.AddObject(new CObstacleObject(&ObstacleData1, LogicPosition(3,3)));*/

	ObjectManager.SetMapObject(new CMapObject(&MapData1));
	ObjectManager.AddObject(new CObstacleObject(&ObstacleData1, LogicPosition(3,3)));

	//CTowerObject *t = ;	
	ObjectManager.AddObject(new CTowerObject(&TowerData1, LogicPosition(5,0)));


	//Set camera
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glScalef(1.0/20,1.0/20,1.0/20);
	glTranslatef(-5,-5,0);

	
}

void CStateIngame::Update()
{
	ObjectManager.Update(CFpsController::GetInstance()->GetFrameDt());
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
