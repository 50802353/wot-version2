#pragma once
#include "GameObject.h"

enum EDirection
{
	E_DIR_UP,
	E_DIR_DOWN,
	E_DIR_LEFT,
	E_DIR_RIGHT,
};

class CMapObject :
	public CGameObject
{
public:
	CMapObject(SMapData *data);
	~CMapObject(void);

	void Init();
	void Update();
	void Render();
	void Destroy();
	

	SMapData *data;
	CImage* MapGridTexture;

	int* ObjectMap;	//array gom` width*height phan tu, moi phan tu cho biet tai o do' la` object gi
	// gia tri cua moi phan tu la` enum EGameObject
	int* DirectionMap; //array gom width*height phan tu, moi phan tu cho biet tai o hien tai thi` quai' vat se di chuyen den' o nao` tiep' theo
	// gia tri cua moi phan tu la enum EDirection



	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	void CalculateEnemyPath();//viet ham tinh lai DirectionMap, thuat toan loan dau`, loan tu data->DestinationPosition, loan cho den khi het DirectionMap, moi lan qua o khac +1



	//TODO------------------------------------------------------------------------------

};
