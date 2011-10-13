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

	int RemainingLife;	//So' mang. con` lai.
	int Money;	//tien` de xay nha

	int* ObjectMap;	//array gom` width*height phan tu, moi phan tu cho biet tai o do' la` object gi
	// gia tri cua moi phan tu la` enum EGameObject
	int* DirectionMap; //array gom width*height phan tu, moi phan tu cho biet tai o hien tai thi` quai' vat se di chuyen den' o nao` tiep' theo
	// gia tri cua moi phan tu la enum EDirection



	//TODO++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	void CalculateEnemyPath();//viet ham tinh lai DirectionMap, thuat toan loan dau`, loan tu data->DestinationPosition, loan cho den khi het DirectionMap, moi lan qua o khac +1


	//vi' du map (5x10)
	//
	//X: destination (dich' den')
	//O: obstacle (chuong' ngai vat)
	//	
	//  . . . O . . . . . . 
	//  . . . O . . . . X .
	//  . O . O . . . . . .
	//  . . . O . . . O . . 
	//  . . . . . . . . . O
	//  Ket qua tinh' toan' duong di, 	
	//	U:up		D:down		L:left		R:right
	//  R R D O R R R R D L
	//  R R D O R R R R X L
	//  D O D O R R R R U L
	//  R R D O R R U O U L
	//  R R R R R R R R U O
	//  



	//TODO------------------------------------------------------------------------------

};
