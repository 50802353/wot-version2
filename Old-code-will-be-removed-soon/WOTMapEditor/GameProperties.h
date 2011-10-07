#ifndef __GAME_PROPERTIES_H
#define __GAME_PROPERTIES_H

#include "CList.h"

#define TILE_GRASS 0
//do not use 1 2

#define TILE_BANANA		0x10000000
#define TILE_COCONUT	0x10000001

#define TILE_TREE		0x10000003
#define TILE_MOUTAIN	0x10000004
#define TILE_RIVER		0x10000005
#define TILE_BLACKHOLE	0x10000006

#define SOURCE			0x20000000
#define DESTINATION		0x30000000

#define TOWER_GUN		0x40000000

#define MAX_LENGTH_FILENAME 50
#define MAX_LENGTH_ALIASNAME 30

struct GameObjectType{
	int ID;	
	int i;
	int j;
	GameObjectType() {}	
	GameObjectType(int id, int i, int j) {
		ID = id;
		this->i = i;
		this->j = j;
	}
};

struct EnemyProperties
{
	__INT32 mHP;
	__INT32 mArmor;
	__INT32 mSpeed;
	__INT32 mCost;
	__INT32 mModelID;
	char mAlias[MAX_LENGTH_ALIASNAME];

	EnemyProperties()
	{}
	EnemyProperties(__INT32 HP, __INT32 Armor, __INT32 Speed, __INT32 Cost, __INT32 ModelID = 0, char alias[MAX_LENGTH_ALIASNAME] = (char*)"Zergling") {
		mHP = HP;
		mArmor = Armor;
		mSpeed =  Speed;
		mCost = Cost;
		mModelID = ModelID;
		strcpy(mAlias, alias);
	}
};

struct TowerProperties
{
	__INT32 mBaseDamage;
	__INT32 mSpeedAttack;
	__INT32 mValue;
	__INT32 mRange;
	__INT32 mCritical;

	__INT32 mPoison;

	__INT32 mBoostDamage;
	__INT32 mBoostSpeed;
	__INT32 mBoostCritical;

	__INT32 mModelID;
	__INT32 mParentID;
	__INT32 mSkillID;
	char mAlias[MAX_LENGTH_ALIASNAME];

	//AFTER THIS LINE IS NOT PRIMITIVE DATA
	GameTutor::CList<__INT32> *mLstChildren;
	TowerProperties() {
		mLstChildren = new GameTutor::CList<__INT32>;
	}
	TowerProperties(__INT32 BaseDamage, __INT32 SpeedAttack, __INT32 Value, __INT32 Range, __INT32 Critical, 
		__INT32 Poison = 0, __INT32 BoostDamage = 0,__INT32 BoostSpeed = 0, __INT32 BoostCritical = 0, 
	__INT32 ModelID = 0,__INT32 parentID=0x40000000, char alias[MAX_LENGTH_ALIASNAME] = "Gun Tower") {
		mBaseDamage = BaseDamage;
		mSpeedAttack = SpeedAttack;
		mValue = Value;
		mRange = Range;
		mCritical = Critical;

		mPoison = Poison;

		mBoostDamage = BoostDamage;
		mBoostSpeed = BoostSpeed;
		mBoostCritical = BoostCritical;

		mModelID = ModelID;
		mParentID = parentID;
		mLstChildren = new GameTutor::CList<__INT32>;
		strcpy(mAlias, alias);
	}
	~TowerProperties() {
		mLstChildren->Clear();
	}
};

struct Wave {
	__INT32 enemyType;
	__INT32 amount;
	__INT32 wayID;
	Wave() {
	}
	Wave(__INT32 enemyType, __INT32 amount, __INT32 wayID) {
		this->enemyType = enemyType;
		this->amount = amount;
		this->wayID = wayID;
	}
};

struct Way {
	int si, sj, di, dj;
	Way() {}
	Way(int i1, int j1, int i2, int j2) {
		sj = j1;
		si = i1;
		dj = j2;
		di = i2;
	}
};

struct ModelProperties {
	char fileModel[MAX_LENGTH_FILENAME];
	char fileTexture[MAX_LENGTH_FILENAME];
	char filePreview[MAX_LENGTH_FILENAME];
	ModelProperties(char model[MAX_LENGTH_FILENAME]=(char*)"model", char texture[MAX_LENGTH_FILENAME]=(char*)"texture", char preview[MAX_LENGTH_FILENAME]=(char*)"preview") {
		strcpy(fileModel, model);
		strcpy(fileTexture, texture);
		strcpy(filePreview, preview);
	}
};

#endif