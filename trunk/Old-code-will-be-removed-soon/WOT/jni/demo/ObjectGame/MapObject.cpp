#include "MapObject.h"
#include "..\CStateIngame.h"
#include "CPathManagement.h"



//using namespace gametutor;

MapObject::MapObject(const char* filename,const char* heightmap_name, __INT32 _width, __INT32 _height, float scale, float scale_height, __INT32 detail):mVertices(NULL),mTextcoord(NULL),mIndices(NULL),mWidth(0),mHeight(0),
	mTextureID(0),mHeightMap(NULL),drawGrid(false),mIndices_grid(NULL),mGridColor(NULL),isPressed(false),scale(1),heightscale(1),selected(-1),mLogicMap(NULL),isDrag(false),MapCameraOffsetX(0),MapCameraOffsetY(0),detail_level(1),drawRange(false),boundarycolor(SColor<__UINT8>(255,255,255,255)),mCircleTextureID(0)
{
	mType = OBJECT_MAP;
	LoadTextureMap(filename);
	LoadHeightMap(heightmap_name);
	skybox = new SkyBox(PATH_GRAPHIC("HellSide5.tga"),PATH_GRAPHIC("HellSide3.tga"),PATH_GRAPHIC("HellSide6.tga"),PATH_GRAPHIC("HellSide1.tga"),PATH_GRAPHIC("HellSide2.tga"),PATH_GRAPHIC("HellSide4.tga"));
	SetMapProperties(_width,_height,scale,scale_height,detail);
	//initialize for mapLogic
	SAFE_DEL_ARRAY(mLogicMap);
	mLogicMap = new __INT32[mWidth*mHeight];
	for(int i = 0; i < mWidth*mHeight; i++)
	{
		mLogicMap[i] = OBJECT_NONE;	
	}
}
MapObject::~MapObject()
{
	delete skybox;
	delete mLogicMap;
}

void MapObject::EnableGrid(bool isEnable)
{
	drawGrid=isEnable;
}

void MapObject::LoadTextureMap(const char* filename)
{
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filename,true);
	mTextureID = (CImageManager::GetInstance()->Get(filename))->GetTextureID();
}

void MapObject::LoadHeightMap(const char* filename)
{
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filename,true);
	mCircleTextureID = (CImageManager::GetInstance()->Get(filename))->GetTextureID();
}

void MapObject::SetMapProperties(__INT32 W, __INT32 H, float scale_=1, float scale_height_=1, int detail)
{
	scale = scale_;
	heightscale = scale_height_;
	mWidth = W;
	mHeight = H;
	detail_level = detail;

	skybox->mWorldMatrix->LoadIdentity();
	
	skybox->mWorldMatrix->Translate(W*scale/2,H*scale/2,1);
	skybox->mWorldMatrix->Scale(20,20,20);
	skybox->mWorldMatrix->Translate(0,0,0.945);
	skybox->mWorldMatrix->Rotate(-90,1,0,0);
}
void MapObject::Render()
{
	skybox->Render();
	
	/*for (int i=0;i<mWidth*detail_level;i++)
	{

		GameTutor::CGraphics2D::GetInstance()->DrawMeshTriangleStrip(2*(mHeight*detail_level+1),&mWorldMatrix,mVertices,mTextcoord,mIndices+2*(mHeight*detail_level+1)*i,mTextureID);
	}*/

		float v[] = {0, 0, 0, 
					float(mWidth)*scale, 0, 0, 
					0, float(mHeight)*scale, 0, 
					float(mWidth)*scale, float(mHeight)*scale, 0};
		float t[] = {0, 0, 0, 
					float(mWidth), 0, 0, 
					0, float(mHeight), 0, 
					float(mWidth), float(mHeight), 0};
		__UINT32 i[] = {0,1,2,3};
		if (selected!=-1)
			GameTutor::CGraphics2D::GetInstance()->DrawMeshTriangleStrip(4,&mWorldMatrix,v,t,i,mTextureID);
		else
			GameTutor::CGraphics2D::GetInstance()->DrawMeshTriangleStrip(4,&mWorldMatrix,v,t,i,mTextureID,SColor<float>(1,1,1,0.3));



	if (selected!=-1)
	{
		__INT32 my_ = selected / CObjectManagement::GetInstance()->GetMap()->GetWidth();
		__INT32 mx_ = selected - CObjectManagement::GetInstance()->GetMap()->GetWidth() * my_;

		float mx = float(mx_)*scale;
		float my = float(my_)*scale;

		float v[] = {mx, my, 0.001, 
					mx+2*scale, my, 0.001, 
					mx, my+2*scale, 0.001, 
					mx+2*scale, my+2*scale, 0.001};
		float t[] = {0, 0, 0, 
					2, 0, 0, 
					0, 2, 0, 
					2, 2, 0};
		__UINT32 i[] = {0,1,2,3};
		SColor<float> color = SColor<float>(boundarycolor.Red/255.0, boundarycolor.Green/255.0, boundarycolor.Blue/255.0, boundarycolor.Alpha/255.0);
		GameTutor::CGraphics2D::GetInstance()->DrawMeshTriangleStrip(4,&mWorldMatrix,v,t,i,mTextureID,color);
	}


	if (drawRange>0)
	{
		__INT32 my_ = selected / CObjectManagement::GetInstance()->GetMap()->GetWidth();
		__INT32 mx_ = selected - CObjectManagement::GetInstance()->GetMap()->GetWidth() * my_;

		float mx = float(mx_+1)*scale;
		float my = float(my_+1)*scale;

		float v[] = {mx-drawRange*2*scale, my-drawRange*2*scale, 0.005, 
					mx+drawRange*2*scale, my-drawRange*2*scale, 0.005, 
					mx-drawRange*2*scale, my+drawRange*2*scale, 0.005, 
					mx+drawRange*2*scale, my+drawRange*2*scale, 0.005};
		float t[] = {0, 0, 0, 
					1, 0, 0, 
					0, 1, 0, 
					1, 1, 0};
		__UINT32 i[] = {0,1,2,3};
		SColor<float> color = SColor<float>(boundarycolor.Red/255.0, boundarycolor.Green/255.0, boundarycolor.Blue/255.0, boundarycolor.Alpha/255.0);
		GameTutor::CGraphics2D::GetInstance()->DrawMeshTriangleStrip(4,&mWorldMatrix,v,t,i,mCircleTextureID,SColor<float>(1,1,0,1));
	}
}

void MapObject::PushMap(ObjectType object, __INT32 x, __INT32 y)
{
	if(x < mWidth && y < mHeight){
		mLogicMap[x*mWidth + y] = object;
	}
}

void MapObject::ScreenPos2MapPos(int ScreenX, int ScreenY, Matrix MVP, float &MapX, float &MapY)
{
	__UINT32 W = VIEWCLASS::GetInstance()->GetWidth();
	__UINT32 H = VIEWCLASS::GetInstance()->GetHeight();
	SPosition2D<float> fpos;
	SPosition2D<float> fpos2;
	MVP.Inverse();

	fpos.X = (float(ScreenX)*2 - W)/W;
	fpos.Y = (float(ScreenY)*2 - H)/H;

	//Use ray to detect the point that cursor point to
	Vector v1(	fpos.X,
				fpos.Y,
				0,
				1);

	Vector v2(	fpos.X,
				fpos.Y,
				10,
				1);

	float* v1data = v1.GetData();
	float* v2data = v2.GetData();
	//Mult inverse matrix
	v1 = MVP.MultVector(v1);v1.Normalize();
	v2 = MVP.MultVector(v2);v2.Normalize();
	v1data = v1.GetData();
	v2data = v2.GetData();

	//Calculate position in object coordinate
	float t = (v1data[2])/(v1data[2]-v2data[2]);
	fpos2.X = v1data[0] + (v2data[0]-v1data[0])*t;
	fpos2.Y = v1data[1] + (v2data[1]-v1data[1])*t;


	MapX = fpos2.X;
	MapY = fpos2.Y;
}

void MapObject::ScreenPos2TowerPos(int ScreenX, int ScreenY, Matrix MVP, int &MapX, int &MapY)
{
	int rx, ry;
	float mx,my;
	ScreenPos2MapPos(ScreenX,ScreenY,MVP, mx, my);
	if ((mx<0) || (my<0))
	{
		MapX = -1;
		MapY = -1;
		return;
	}
	float checkx = fabs(mx/scale);
	float checky = fabs(my/scale);
	rx = 0;
	ry = 0;
	while (checkx>1)
	{
		checkx-=1.0f;
		rx +=1;
	}
	if (checkx<0.5f) rx -=1;
	if (mx<0) rx*=-1;
	while (checky>1)
	{
		checky-=1.0f;
		ry +=1;
	}
	if (checky<0.5f) ry -=1;
	if (my<0) ry*=-1;

	if (rx<0) rx=0;
	if (rx>mWidth-2) rx=mWidth-2;
	if (ry<0) ry=0;
	if (ry>mHeight-2) ry=mHeight-2;

	MapX = rx;
	MapY = ry;

}

void MapObject::UpdateTowerBuildBar(CList<__INT32> *list)
{
	CStateIngame::currentBuildBar->Tower1->SetVisible(false);
	CStateIngame::currentBuildBar->Tower2->SetVisible(false);
	CStateIngame::currentBuildBar->Tower3->SetVisible(false);
	CStateIngame::currentBuildBar->Tower4->SetVisible(false);

	
	list->BeginTravel();
	if (!list->IsEndOfTravel())
	{
		__INT32 towerID1 = list->Travel();
		CStateIngame::currentBuildBar->towerID1 = towerID1;
		TowerProperties *properties1;
		CStateIngame::GetInstance()->currentfile->m_lstTowerProperties->GetElement(towerID1,properties1);
		ModelProperties *mproperties1;
		CStateIngame::GetInstance()->currentfile->m_lstModelProperties->GetElement(properties1->mModelID,mproperties1);
		char *path = new char[100];
		strcpy(path,(char*)PATH_GRAPHIC());
		strcat(path,mproperties1->filePreview);
		CStateIngame::currentBuildBar->Tower1->SetImage(path);
		CStateIngame::currentBuildBar->Tower1->SetImageHover(path);
		CStateIngame::currentBuildBar->Tower1->SetVisible(true);
		if (!list->IsEndOfTravel())
		{
			__INT32 towerID2 = list->Travel();
			CStateIngame::currentBuildBar->towerID2 = towerID2;
			TowerProperties *properties2;
			CStateIngame::GetInstance()->currentfile->m_lstTowerProperties->GetElement(towerID2,properties2);
			ModelProperties *mproperties2;
			CStateIngame::GetInstance()->currentfile->m_lstModelProperties->GetElement(properties2->mModelID,mproperties2);
			strcpy(path,(char*)PATH_GRAPHIC());
			strcat(path,mproperties2->filePreview);
			CStateIngame::currentBuildBar->Tower2->SetImage(path);
			CStateIngame::currentBuildBar->Tower2->SetImageHover(path);
			CStateIngame::currentBuildBar->Tower2->SetVisible(true);
			if (!list->IsEndOfTravel())
			{
				__INT32 towerID3 = list->Travel();
				CStateIngame::currentBuildBar->towerID3 = towerID3;
				TowerProperties *properties3;
				CStateIngame::GetInstance()->currentfile->m_lstTowerProperties->GetElement(towerID3,properties3);
				ModelProperties *mproperties3;
				CStateIngame::GetInstance()->currentfile->m_lstModelProperties->GetElement(properties3->mModelID,mproperties3);
				strcpy(path,(char*)PATH_GRAPHIC());
				strcat(path,mproperties3->filePreview);
				CStateIngame::currentBuildBar->Tower3->SetImage(path);
				CStateIngame::currentBuildBar->Tower3->SetImageHover(path);
				CStateIngame::currentBuildBar->Tower3->SetVisible(true);
				if (!list->IsEndOfTravel())
				{
					__INT32 towerID4 = list->Travel();
					CStateIngame::currentBuildBar->towerID4 = towerID4;
					TowerProperties *properties4;
					CStateIngame::GetInstance()->currentfile->m_lstTowerProperties->GetElement(towerID4,properties4);
					ModelProperties *mproperties4;
					CStateIngame::GetInstance()->currentfile->m_lstModelProperties->GetElement(properties4->mModelID,mproperties4);
					strcpy(path,(char*)PATH_GRAPHIC());
					strcat(path,mproperties4->filePreview);
					CStateIngame::currentBuildBar->Tower4->SetImage(path);
					CStateIngame::currentBuildBar->Tower4->SetImageHover(path);
					CStateIngame::currentBuildBar->Tower4->SetVisible(true);

				}
			}
		}
	}

}

void MapObject::Update(float tpf)
{
	//skybox->mWorldMatrix->Rotate(1,0,1,0);
	if (isPressed)
	{
		SPointerUserInfo PInfo;
		int curP;
		if (CControllerPointerManager::GetInstance()->GetActivePointer(1,curP,&PInfo))
		{
			if (PInfo.DragDiffDistanceX==0 && PInfo.DragDiffDistanceY==0) return;
			__INT32 Cam_X = PInfo.DragDiffDistanceX;
			if (Cam_X+MapCameraOffsetX>100) 
			{
				Cam_X = 100-MapCameraOffsetX;
				if (Cam_X<0) Cam_X = 0;
			}
			if (Cam_X+MapCameraOffsetX<-100) 
			{
				Cam_X = -100-MapCameraOffsetX;
				if (Cam_X>0) Cam_X = 0;
			}
			__INT32 Cam_Y = PInfo.DragDiffDistanceY;
			if (Cam_Y+MapCameraOffsetY>25)
			{
				Cam_Y = 25-MapCameraOffsetY;
				if (Cam_Y<0) Cam_Y = 0;
			}
			if (Cam_Y+MapCameraOffsetY<-50) 
			{
				Cam_Y = -50-MapCameraOffsetY;
				if (Cam_Y>0) Cam_Y = 0;
			}


			//if ((abs(MapCameraOffsetX+PInfo.DragDiffDistanceX)<80) && (abs(MapCameraOffsetY+PInfo.DragDiffDistanceY)<60))
			//{
				CCamera3D::GetInstance()->CameraTranslate(float(Cam_X)/50,float(Cam_Y)/50,0);
				MapCameraOffsetX += Cam_X;
				MapCameraOffsetY += Cam_Y;
			//}
			Log("drag info %d %d ",PInfo.DragDiffDistanceX,PInfo.DragDiffDistanceY);
			dragDistanceX+=PInfo.DragDiffDistanceX;
			dragDistanceY+=PInfo.DragDiffDistanceY;
		}
	}
}


void MapObject::OnControllerEvent(SControllerEvent Event)
{
	float ax,ay,az,aw;
	Matrix MVP;
	int mx=0;
	int my=0;
	float fx=0;
	float fy=0;
	__INT32 distance=0;
	TowerObject* tower;
	if (Event.Type == ECE_POINTER)
	{
		switch (Event.PointerData.Event)
		{
		case EPE_PRESSED:
			isPressed = true;
			dragDistanceX = 0;
			dragDistanceY = 0;
			break;
		case EPE_DRAGGED:
			distance= dragDistanceX*dragDistanceX + dragDistanceY*dragDistanceY;
			if (distance>50) isDrag=true;
			break;
		case EPE_RELEASED:
			
			if (isPressed)
			{			
				MVP.LoadIdentity();
				MVP.Multiply(*(CCamera3D::GetInstance()->GetProjectMatrix()));
				MVP.Multiply(*(CCamera3D::GetInstance()->GetViewMatrix()));

				ScreenPos2MapPos(Event.PointerData.X,Event.PointerData.Y,MVP,fx,fy);
				mx = __INT32(fx/scale);
				my = __INT32(fy/scale);
				if ((!isDrag)/* && ((mLogicMap[my*mWidth+mx]==OBJECT_NONE) || (mLogicMap[my*mWidth+mx]==OBJECT_TOWER))*/)
				{
					if (mx>=0 && mx<mWidth &&my>=0 && my<mHeight)
					{

						if (mLogicMap[my*mWidth+mx]==OBJECT_NONE) //click len vung dat trong'
						{
							ScreenPos2TowerPos(Event.PointerData.X,Event.PointerData.Y,MVP,mx,my);

							Log("Logic map position: %d %d", mx, my);
							if ((mx<mWidth) && (my<mHeight) && (mx>=0) && (my>=0))
							{
								if (selected == my * mWidth + mx)
								{
									selected =-1;
									drawRange = 0;
									CList<__INT32> NullList;
									UpdateTowerBuildBar(&NullList);
									return;									
								}

								selected = my * mWidth + mx;
								if ((mLogicMap[selected]==OBJECT_NONE) && 
									(mLogicMap[selected+1]==OBJECT_NONE) && 
									(mLogicMap[selected+mWidth]==OBJECT_NONE) && 
									(mLogicMap[selected+mWidth+1]==OBJECT_NONE) &&
									CPathManagement::GetInstance()->IsStillExist(selected))	//Vung dat 2x2 trong'
								{
									CStateIngame::currentBuildBar->sellButton->SetVisible(false);
									//kiem tra so button xay tru can hien
									CStateIngame::currentBuildBar->Tower1->SetVisible(true);

									Log("Truoc calc boundary");
									CalculateBoundary(mx, my, SELECTED_BUILDABLE_CELL_COLOR,0);
									Log("Sau calc boundary");
									CList<__INT32> towerList;//sau nay de thong tin cac tower co the xay tu dat' trong vao day
									towerList.AddItem(TOWER_GUN);
									UpdateTowerBuildBar(&towerList);
								}
								else	//2x2 khong trong'
								{
									CStateIngame::currentBuildBar->sellButton->SetVisible(false);
									CalculateBoundary(mx, my, SELECTED_UNBUILDABLE_CELL_COLOR,0);
									//an het cac button xay tru
									CStateIngame::currentBuildBar->Tower1->SetVisible(false);
									CStateIngame::currentBuildBar->Tower2->SetVisible(false);
									CStateIngame::currentBuildBar->Tower3->SetVisible(false);
									CStateIngame::currentBuildBar->Tower4->SetVisible(false);
								}
							}
						}
						else if(mLogicMap[my*mWidth+mx]==OBJECT_TOWER)//click len TOWER
						{
							CStateIngame::currentBuildBar->sellButton->SetVisible(true);
							tower = (CObjectManagement::GetInstance()->GetTower(MapPosition(mx,my)));
							if (!tower) 
								tower = (CObjectManagement::GetInstance()->GetTower(MapPosition(mx-1,my)));
							if (!tower) 
								tower = (CObjectManagement::GetInstance()->GetTower(MapPosition(mx-1,my-1)));
							if (!tower) 
								tower = (CObjectManagement::GetInstance()->GetTower(MapPosition(mx,my-1)));


							if (selected == tower->mPosition.mY * mWidth + tower->mPosition.mX)
								{
									selected =-1;
									drawRange = 0;
									CList<__INT32> NullList;
									UpdateTowerBuildBar(&NullList);
									return;									
								}
							selected = tower->mPosition.mY * mWidth + tower->mPosition.mX;
							CalculateBoundary( tower->mPosition.mX, tower->mPosition.mY, SELECTED_TOWER_CELL_COLOR, tower->mProperties->mRange);
						
							UpdateTowerBuildBar(tower->mProperties->mLstChildren);
						}
						else //click len Enemy hoac tree
						{
							CStateIngame::currentBuildBar->sellButton->SetVisible(false);
							ScreenPos2TowerPos(Event.PointerData.X,Event.PointerData.Y,MVP,mx,my);
							CalculateBoundary(mx, my, SELECTED_UNBUILDABLE_CELL_COLOR,0);
							//an het cac button xay tru
							CStateIngame::currentBuildBar->Tower1->SetVisible(false);
							CStateIngame::currentBuildBar->Tower2->SetVisible(false);
							CStateIngame::currentBuildBar->Tower3->SetVisible(false);
							CStateIngame::currentBuildBar->Tower4->SetVisible(false);
						}
					}
					else
						selected = -1;
				}
				isPressed = false;

			}

			isDrag = false;
			break;
		}
	}

	

}

void MapObject::CalculateBoundary(int posX, int posY, SColor<__UINT8> color, __INT32 range)
{
	boundarycolor = color;
	drawRange = range;
}


__INT32 MapObject::GetWidth()
{
	return mWidth;
}

__INT32 MapObject::GetHeight()
{
	return mHeight;
}