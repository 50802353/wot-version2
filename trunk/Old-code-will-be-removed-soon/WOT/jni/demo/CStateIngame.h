#ifndef __CSTATEINGAME_H__
#define __CSTATEINGAME_H__

#include "gametutor.h"
#include "CSoundManagement.h"
#include "CModelManager.h"
#include "CObjectManagement.h"
#include "CStateMenu.h"
#include "CRandom.h"
#include "WOTMapfile.h"

using namespace GameTutor;

enum Ingame_status {INGAME_PLAY,
					INGAME_PAUSE_MENU,
					INGAME_CONFIRM,
					INGAME_BACK,
					INGAME_RESTART,
					INGAME_EXIT,
					INGAME_WIN,
					INGAME_LOSE,
};


class TowerBuildBar
{
public:
	TowerBuildBar();
	~TowerBuildBar();

	void Render();
	bool OnControllerEvent(SControllerEvent Event);
	void PrintMoney(CImage *font, __INT32 number);
	void PrintLives(CImage *font, __INT32 number);
	__INT32 towerID1;
	__INT32 towerID2;
	__INT32 towerID3;
	__INT32 towerID4;
	//4 nut' tower ben trai'
	CDropdownButton *Tower1;	
	CDropdownButton *Tower2;
	CDropdownButton *Tower3;
	CDropdownButton *Tower4;
	

	//nut' pause game
	CButton *but_HOME;	
	CButton *sellButton;
	CImage* font;

	//Add Bar
	CImage* InGameBar;
	CImage* CreepBar;
};

class IngameMenu
{
public:
	IngameMenu();
	void Render();
	bool OnControllerEvent(SControllerEvent Event);

	//4 nut' tower ben trai'
	CImage *fade_background;
	CButton *but_Continue;	
	CButton *but_Restart;
	CButton *but_mainMenu;
	CButton *but_Quit;

	//Ask when select a function
	CButton *but_Ask;
	CButton *but_Yes;
	CButton *but_No;

	//Ask When Lose or pass Game
	CButton *but_Lose;
	CButton *but_Win;
};

class CStateIngame: public CState, public CSingleton<CStateIngame>
{
public:
	CStateIngame();
	~CStateIngame() {}
	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
	void ResetState();
	static int Damage(int baseDamage, int amour, int probability);

public:
	////graphic and sound
	//MD2Model* treeModel;
	//MD2Model* towerModel;
	//GameSound* A_SoundJump;
	//GameSound* A_SoundFootStep;

	GameSound* A_Background;
	GameSound* A_Win;
	GameSound* A_Lose;



	////attributes

	

	TowerBuildBar* BuildBar;
	static TowerBuildBar* currentBuildBar;

	static Ingame_status status;

	float WaveTime;
	float introTime;

	IngameMenu *menu;

	static int creepCount;
	static int MaxCreep;
	static CRandom isCrit;
	static CWOTMapfile* currentfile;
//	static __INT32 ChooseAction;	//0: none	1:restart	2: Main Menu		3: Quit
};

#endif