#ifndef _CPATHMANAGEMENT_H_
#define _CPATHMANAGEMENT_H_

#include "Header.h"
#include "CSingleton.h"
#include "PathEle.h"

using namespace GameTutor;

class CPathManagement: public CSingleton<CPathManagement>
{
	friend class  CSingleton<CPathManagement>;
protected:
	__INT32 numPaths;
	MapPosition mStart;
	MapPosition mEnd;
	AStar* mAStarAlgorithm;
	CList<PathEle*>* m_ListLookup;
	MapObject* mMap;
	__INT32* logicMap;
	CPathManagement() {
		numPaths = 0;
		m_ListLookup = new CList<PathEle*>;
		mStart.mX = 0;
		mStart.mY = 0;
		mEnd.mX = 10;
		mEnd.mY = 10;
	};
public:
	//use when load Map File
	void setPath(MapPosition _start, MapPosition _end, MapObject* _map)
	{
		mMap = _map;
		if(mMap)
		{
			//init logicMap for find path
			logicMap = new __INT32[mMap->GetWidth()*mMap->GetHeight()];
			for(__INT32 i = 0; i < mMap->GetWidth(); i++)
			{
				for(__INT32 j = 0; j < mMap->GetHeight(); j++)
				{
					__INT32 idx = i + j*mMap->GetWidth();
					if(mMap->mLogicMap[idx] == OBJECT_NONE || mMap->mLogicMap[idx] == OBJECT_ENEMY)
						logicMap[idx] = 0;
					else logicMap[idx] = 3;
				}
			}
			int s =sizeof(AStar);
			mAStarAlgorithm = new AStar(mMap->GetWidth(),mMap->GetHeight(),logicMap);
			//mAStarAlgorithm = new AStar(mMap->GetHeight(), mMap->GetWidth(),logicMap);
		}
		mStart.mX = _start.mX;
		mStart.mY = _start.mY;
		mEnd.mX = _end.mX;
		mEnd.mY = _end.mY;
	}
	bool IsStillExist(__INT32 position)
	{
		__INT32* backupMap = mAStarAlgorithm->getMap();
		__INT32 count = mAStarAlgorithm->getWidth()*mAStarAlgorithm->getHeight();
		__INT32* tempMap = new __INT32[count];
		for(int i = 0; i < count; i++)
		{
			tempMap[i] = backupMap[i];
		}
		//update tempMap
		tempMap[position] = 3;
		tempMap[position+1] = 3;
		tempMap[position + mAStarAlgorithm->getWidth()] = 3;
		tempMap[position + mAStarAlgorithm->getWidth() + 1] = 3;

		mAStarAlgorithm->setMap(tempMap);
		CList<cell>* list = new CList<cell>;
		bool result = mAStarAlgorithm->pathFinder(false,list,mStart.mX,mStart.mY, mEnd.mX, mEnd.mY);
		//restore map
		mAStarAlgorithm->setMap(backupMap);
		//clear list
		list->Clear();
		delete list;
		//delete temp Map
		delete[] tempMap;
		return result;
	}
	//the return value is the handle for path
	__INT32 addPath()
	{
		numPaths++;
		PathEle* ele = new PathEle(mAStarAlgorithm, mStart, mEnd, numPaths);
		m_ListLookup->AddItem(ele);
		return numPaths;
	}

	MapPosition* getCurPos(__INT32 _idPath)
	{
		MapPosition* result = 0;
		for(int i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				result = m_ListLookup->GetElement(i)->getCurrent();
				break;
			}
		}
		return result;
	}

	MapPosition* getNextPos(__INT32 _idPath)
	{
		MapPosition* result = 0;
		for(int i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				result = m_ListLookup->GetElement(i)->getNext();
				break;
			}
		}
		return result;
	}

	MapPosition* getPrePos(__INT32 _idPath)
	{
		MapPosition* result = 0;
		for(int i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				result = m_ListLookup->GetElement(i)->getPre();
				break;
			}
		}
		return result;
	}

	void next(__INT32 _idPath)
	{
		for(int i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				m_ListLookup->GetElement(i)->Next();
				break;
			}
		}
	}
	bool wasFinish(__INT32 _idPath)
	{
		int i;
		for(i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				break;
			}
		}
		return m_ListLookup->GetElement(i)->wasFinish();
	}
	void Update()
	{
		updateMap();
		for(int i = 0; i < m_ListLookup->GetCount(); i++)
		{
			PathEle* temp = m_ListLookup->GetElement(i);
			temp->UpdatePath(mStart,mEnd);
		}
	}

	void updateMap()
	{
		for(__INT32 i = 0; i < mMap->GetWidth(); i++)
		{
			for(__INT32 j = 0; j < mMap->GetHeight(); j++)
			{
				__INT32 idx = i + j*mMap->GetWidth();
				if(mMap->mLogicMap[idx] == OBJECT_NONE || mMap->mLogicMap[idx] == OBJECT_ENEMY)
					logicMap[idx] = 0;
				else logicMap[idx] = 3;
			}
		}
	}
	void ClearAll()
	{
		this->numPaths = 0;
		if(m_ListLookup)
		{
			PathEle* item = 0;
			m_ListLookup->BeginTravel();
			while(!m_ListLookup->IsEndOfTravel())
			{
				item = m_ListLookup->Travel();
				m_ListLookup->RemoveItem(item);
				//SAFE_DEL(item);
			}
		}
	}
	virtual ~CPathManagement() 
	{
		for(int i = 0; i < numPaths; i++)
		{
			PathEle* tEle = m_ListLookup->GetElement(i);
			delete tEle;
		}
		m_ListLookup->DeallocateElementPointer();
	}
	bool isChangeOriented(__INT32 _idPath)
	{
		int i;
		for(i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				break;
			}
		}
		return m_ListLookup->GetElement(i)->mChangeOriented;
	}
	void setNoChangeOriented(__INT32 _idPath)
	{
		int i;
		for(i = 0; i < m_ListLookup->GetCount(); i++)
		{
			if(m_ListLookup->GetElement(i)->getId() == _idPath)
			{
				break;
			}
		}
		m_ListLookup->GetElement(i)->mChangeOriented = false;
	}
};


#endif