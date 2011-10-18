#include "MapObject.h"
#include "ObjectManager.h"

CMapObject::CMapObject(SMapData *data)
{
	this->ObjectType = EGameObject::E_OBJ_MAP;
	this->data = data;
	ObjectMap = new int[this->data->Height * this->data->Width];
	memset(ObjectMap, 0, sizeof(int) * this->data->Height * this->data->Width);
	RemainingLife = data->GivenLife;
	Money = data->GivenMoney;


	CImageManager::GetInstance()->AddImage<CFileWin32Driver>("..\\resource\\grid_cell.tga",true);
	MapGridTexture = CImageManager::GetInstance()->Get("..\\resource\\grid_cell.tga");
}

CMapObject::~CMapObject(void)
{
	SAFE_DEL_ARRAY(ObjectMap);
}

void CMapObject::Init()
{
}

void CMapObject::Update(int delta_time)
{
}

void CMapObject::Render()
{
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<float>(0,0,10,10),MapGridTexture,SRect<float>(0,0,MapGridTexture->GetWidth()*10,MapGridTexture->GetHeight()*10));
}

void CMapObject::Destroy()
{
	CObjectManager::CurrentObjectManager->SetMapObject(NULL);
	delete this;
}



