#ifndef __PATHELE_H__
#define __PATHELE_H__

#include "GameObject.h"
#include "LibAI.h"

class PathEle
{
private:
	AStar* mAStarAlgorithm;

	__INT32 ID;
	MapPosition* startPos;
	MapPosition* endPos;
	__INT32 icurPosIdx;

	CList<MapPosition*>* path;
	void initPath();
	CList<MapPosition*>* getPath(MapPosition* _src, MapPosition* _dest);
public:
	bool mChangeOriented;
	__INT32 getId();
	PathEle(AStar* _AStar, MapPosition _start, MapPosition _end, __INT32 _id);
	~PathEle(void);
	bool wasFinish();
	void Next();
	MapPosition* getCurrent();
	MapPosition* getNext();
	MapPosition* getPre();
	void UpdatePath(MapPosition _begin, MapPosition _end);
};

#endif