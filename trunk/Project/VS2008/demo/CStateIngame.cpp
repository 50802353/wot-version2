
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

	CMapObject* map = new CMapObject(&MapData1);
	ObjectManager.SetMapObject(map);
	ObjectManager.AddObject(new CObstacleObject(&ObstacleData1, LogicPosition(3,3)));
	map->BuildTower(&TowerData1, LogicPosition(5,0));
	map->BuildTower(&TowerData1, LogicPosition(8,5));


	//Set camera
	glMatrixMode(GL_PROJECTION);
	glScalef(1.0/20,1.0/20,1.0/20);
	glTranslatef(-5,-5,0);
	glMatrixMode(GL_MODELVIEW);
	
}

void CStateIngame::Update()
{
	ObjectManager.Update(CFpsController::GetInstance()->GetFrameDt());
	if (CControllerPointerManager::GetInstance()->WasTouchedInside(0,0,VIEWCLASS::GetInstance()->GetWidth(),VIEWCLASS::GetInstance()->GetHeight()))
	{
		
		SPointerUserInfo* info = new SPointerUserInfo();
		int nPointer;
		CControllerPointerManager::GetInstance()->GetActivePointer(1, nPointer, info);
		Log("Clicked %d %d", info->CurrentPosition.X, info->CurrentPosition.Y);

		unsigned int selectBuf[512];
		int viewport[4];

		glSelectBuffer(512,selectBuf);
		glRenderMode(GL_SELECT);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glGetIntegerv(GL_VIEWPORT,viewport);
		gluPickMatrix(info->CurrentPosition.X,viewport[3]-info->CurrentPosition.Y,
				1,1,viewport);
		//gluPerspective(45,(float)viewport[2]/(float)viewport[3],0.1,1000);
		glScalef(1.0/20,1.0/20,1.0/20);
		glTranslatef(-5,-5,0);
		glMatrixMode(GL_MODELVIEW);
		glInitNames();




		//render in select mode
		CGraphics2D::GetInstance()->Clear(SColor<float>(0,0,0,1));
		ObjectManager.RenderInSelectMode();




		int hits;
	
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glFlush();

		hits = glRenderMode(GL_RENDER);	

		if (hits)
		{
			unsigned int i, j;
			GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

			Log ("hits = %d\n", hits);
			ptr = (GLuint *) selectBuf;
			minZ = 0xffffffff;
			for (i = 0; i < hits; i++) 
			{
				printf("Names(%u)\n\t",i+1);
				for (j=0; j<ptr[0];j++)
					printf("[%u]",ptr[3+j]);
				printf("\n");
				printf("MinZ %u\n", ptr[1]);
				printf("MaxZ %u\n", ptr[2]);

				if (ptr[0]>1)
				{
					CTowerObject* SelectedTower = (CTowerObject*)ptr[4];
					SelectedTower->isSelected = true;
				}

				ptr+=ptr[0]+3;
			}
		}


	}
}

void CStateIngame::Render()
{
	//Log("State Ingame: Fps = %d FrameDT = %d", CFpsController::GetInstance()->GetRuntimeFps(), CFpsController::GetInstance()->GetFrameDt());
	CGraphics2D::GetInstance()->Clear(SColor<float>(0,0,0,1));
	ObjectManager.Render();
}

void CStateIngame::Exit()
{
	Log("State Ingame: Exit");
}
