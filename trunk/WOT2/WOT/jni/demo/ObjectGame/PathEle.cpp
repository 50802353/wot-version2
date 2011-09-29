#include "PathEle.h"
#include "../CObjectManagement.h"
#include "../CStateIngame.h"


PathEle::PathEle(AStar* _AStar, MapPosition _start, MapPosition _end, __INT32 _id)
{
	ID = _id;
	startPos = new MapPosition(_start.mX,_start.mY);
	endPos = new MapPosition(_end.mX,_end.mY);
	icurPosIdx = 0;//for cur Position
	mAStarAlgorithm = _AStar;
	mChangeOriented = false;
	initPath();
}

__INT32 PathEle::getId()
{
	return ID;
}

void PathEle::initPath()
{
	path = getPath(startPos,endPos);
}

bool PathEle::wasFinish()
{
	return (icurPosIdx == path->GetCount()-1);
}

void PathEle::Next()
{
	//remove old position in Logic Map
	MapPosition* oldPosition = path->GetElement(icurPosIdx);
	__INT32* logicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
	logicMap[oldPosition->mX + oldPosition->mY*CObjectManagement::GetInstance()->GetMap()->GetWidth()] = OBJECT_NONE;

	if(!wasFinish())
	{
		icurPosIdx++;
		//set new Position in Logic Map
		MapPosition* newPosition = path->GetElement(icurPosIdx);
		__INT32* logicMap = CObjectManagement::GetInstance()->GetMap()->mLogicMap;
		__INT32 position = newPosition->mX + newPosition->mY*CObjectManagement::GetInstance()->GetMap()->GetWidth();
		logicMap[position] = OBJECT_ENEMY;
		//check xem trong o moi' cua enemy co dang vao` o dang duoc selected hay ko?
		__INT32 *selected = &(CObjectManagement::GetInstance()->GetMap()->selected);

		if(position == *selected || position == *selected + 1 ||
			position == *selected + CObjectManagement::GetInstance()->GetMap()->GetWidth() ||
			position == *selected + CObjectManagement::GetInstance()->GetMap()->GetWidth()+1)
		{
			__INT32 my_ = *selected / CObjectManagement::GetInstance()->GetMap()->GetWidth();
			__INT32 mx_ = *selected - CObjectManagement::GetInstance()->GetMap()->GetWidth() * my_;

			CStateIngame::currentBuildBar->sellButton->SetVisible(false);
			CObjectManagement::GetInstance()->GetMap()->CalculateBoundary(mx_, my_, SELECTED_UNBUILDABLE_CELL_COLOR,0);
			//an het cac button xay tru
			CStateIngame::currentBuildBar->Tower1->SetVisible(false);
			CStateIngame::currentBuildBar->Tower2->SetVisible(false);
			CStateIngame::currentBuildBar->Tower3->SetVisible(false);
			CStateIngame::currentBuildBar->Tower4->SetVisible(false);
		}
	}
}

MapPosition* PathEle::getNext()
{
	if(!wasFinish())
		return path->GetElement(icurPosIdx + 1);
	else return 0;
}

MapPosition* PathEle::getPre()
{
	if(icurPosIdx > 0)
		return path->GetElement(icurPosIdx - 1);
	else return 0;
}

MapPosition* PathEle::getCurrent()
{
	return path->GetElement(icurPosIdx);
}

CList<MapPosition*>* PathEle::getPath(MapPosition* _src, MapPosition* _dest)
{
	CList<MapPosition*>* result = 0;
	CList<cell>* temp = new CList<cell>;
	if(mAStarAlgorithm->pathFinder(false,temp, _src->mX, _src->mY, _dest->mX, _dest->mY))
	{
		//create new Path
		result = new CList<MapPosition*>;
		//add src to path
		result->AddItem(_src);
		//add temp to List
		temp->BeginBackTravel();
		cell t = temp->BackTravel();
		while(!temp->IsEndOfBackTravel()){
			t = temp->BackTravel();
			MapPosition* tMap = new MapPosition(t.i,t.j);
			result->AddItem(tMap);
		}
		result->AddItem(_dest);
	}
	//delete temp
	temp->Clear();
	delete temp;
	return result;
}

void PathEle::UpdatePath(MapPosition _begin, MapPosition _end)
{
	MapPosition* curPos = getCurrent();
	MapPosition* oldNext = getNext();
	CList<MapPosition*>* newAddPath = getPath(curPos, endPos);
	if(newAddPath)
	{
		//check New Next
		MapPosition* newNext = newAddPath->GetElement(1);
		if(oldNext && newNext && !(oldNext->mX == newNext->mX && oldNext->mY == newNext->mY)) mChangeOriented = true;

		//add newAddPath to cur Path
		//--remove path from curPos+1 -> end - 1
		__INT32 idx = 1;
		for(__INT32 i = icurPosIdx+1; i < path->GetCount()-1; i++)
		{
			MapPosition* temp = path->GetElement(i);
			delete temp;
		}
		//update path
		CList<MapPosition*>* result = new CList<MapPosition*>;
		for(int i = 0; i < icurPosIdx; i++)
		{
			result->AddItem(path->GetElement(i));
		}
		for(int i = 0; i < newAddPath->GetCount(); i++)
		{
			result->AddItem(newAddPath->GetElement(i));
		}
		//clean memory
		//path->DeallocateElementPointer();
		delete path;
		path = result;
		result = 0;

		//newAddPath->DeallocateElementPointer();
		delete newAddPath;
		newAddPath = 0;
	}
}

PathEle::~PathEle(void)
{
	for(int i = 0; i < path->GetCount(); i++)
	{
		MapPosition* temp = path->GetElement(i);
		delete temp;
	}
	path->DeallocateElementPointer();
	path = 0;
}