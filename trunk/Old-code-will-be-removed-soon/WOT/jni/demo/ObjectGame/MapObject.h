#pragma once
#include "GameObject.h"

#define SELECTED_BUILDABLE_CELL_COLOR SColor<__UINT8>(0,255,0,255)
#define SELECTED_TOWER_CELL_COLOR SColor<__UINT8>(0,0,255,255)
#define SELECTED_UNBUILDABLE_CELL_COLOR SColor<__UINT8>(255,0,0,255)
//#include "gametutor.h"

#define SIZE_SQUARE 0.5
using namespace GameTutor;

class MapObject :
	public GameObject
{
private:
	__INT32 mWidth;
	__INT32 mHeight;
	GLuint mTextureID;
	GLuint mCircleTextureID;

	float* mVertices;
	float* mTextcoord;
	float* mGridColor;

	__UINT32* mIndices;
	__UINT32* mIndices_grid;
	CImage* mHeightMap;
	bool drawGrid;
	bool isPressed;
	float scale;
	float heightscale;
	

	float mBoundaryV[12+36*3];
	float mBoundaryC[12+36*3];
	
	bool isDrag;
	__INT32 detail_level;

public:
	Matrix mWorldMatrix;
	__INT32* mLogicMap;
	__INT32 selected;
	__INT32 drawRange;

public:
	MapObject(const char* filename,const char* heightmap_name, __INT32 _width, __INT32 _height, float scale, float scale_height, __INT32 detail);
	~MapObject(void);
	void LoadTextureMap(const char* filename);
	void LoadHeightMap(const char* filename);
	/*void SetMapProperties(__INT32 _width, __INT32 _height, __INT32 _squareSize);*/
	void SetMapProperties(__INT32 _width, __INT32 _height, float scale, float scale_height, int detail = 1);
	void Update(float tpf);
	void Render();
	void PushMap(ObjectType object, __INT32 x, __INT32 y);
	void EnableGrid(bool isEnable);
	void OnControllerEvent(SControllerEvent Event);
	void ScreenPos2MapPos(__INT32 ScreenX, __INT32 ScreenY, Matrix MVP, float &MapX, float &MapY);
	void ScreenPos2TowerPos(__INT32 ScreenX, __INT32 ScreenY, Matrix M, __INT32 &MapX, __INT32 &MapY);
	void CalculateBoundary(__INT32 posX, __INT32 posY, SColor<__UINT8> color, __INT32 range);
	void UpdateTowerBuildBar(CList<__INT32> *list);// update thong tin ben towerBar cua ingame_state
	__INT32 GetWidth();
	__INT32 GetHeight();

private:
	__INT32 dragDistanceX;
	__INT32 dragDistanceY;
	__INT32 MapCameraOffsetX;
	__INT32 MapCameraOffsetY;
	SColor<__UINT8> boundarycolor;
	SkyBox* skybox;
	float *skyVertex;
	float *skyTexture;

};
