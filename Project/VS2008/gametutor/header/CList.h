#ifndef __CLIST_H__
#define __CLIST_H__

#include "Header.h"
#include "list"
using namespace std;

#define ListIterator(type) typename list<type>::iterator

namespace GameTutor
{
	template<typename element_type> 
	class CList
	{
	public:
		CList();
		virtual ~CList();
		void AddItem(element_type ele);
		void RemoveItem(element_type ele);
		element_type GetElement(int index);
		element_type operator[](int index);
		int GetCount();			
		void DeallocateElementPointer();
		void Clear();

		void BeginTravel();
		element_type Travel();
		bool IsEndOfTravel();
		int GetTravelStepCounter() {return m_iTravelStepCounter;}
	protected:
		list<element_type>* m_List;
		typename list<element_type>::iterator m_CurrentIter;
	private:
		int m_iTravelStepCounter;
	};

	template<typename element_type> GameTutor::CList<element_type>::CList()
	{
		m_List = new list<element_type>();
	}

	template<typename element_type> GameTutor::CList<element_type>::~CList()
	{
		m_List->clear();
		SAFE_DEL(m_List);
	}


	template<typename element_type> void GameTutor::CList<element_type>::AddItem(element_type ele)
	{
		m_List->push_back(ele);
	}

	template<typename element_type> void GameTutor::CList<element_type>::RemoveItem(element_type ele)
	{
		m_List->remove(ele);
	}

	template<typename element_type> element_type GameTutor::CList<element_type>::GetElement(int index)
	{
		ListIterator(element_type) i = m_List->begin();
		int _i = 0;
		if ((unsigned)index < m_List->size())
		{
			for (i = m_List->begin(); _i < index; i++, _i++){}
			return (*i);
		}
		return (*i);
	}

	template<typename element_type> element_type GameTutor::CList<element_type>::operator[] (int index)
	{
		return GetElement(index);
	}

	template<typename element_type> int GameTutor::CList<element_type>::GetCount()
	{
		if (!m_List) return 0;
		return m_List->size();
	}

	template<typename element_type> void GameTutor::CList<element_type>::DeallocateElementPointer()
	{
		if (GetCount() > 0)
		{
			ListIterator(element_type) i;
			ListIterator(element_type) cur;
			for (i = m_List->begin(); i != m_List->end();)
			{
				cur = i;
				i++;
				if (*cur)
				{
					delete[] *cur;
				}
			}
		}
	}

	template<typename element_type> void GameTutor::CList<element_type>::Clear()
	{
		if (GetCount() > 0)
		{
			m_List->clear();
		}
	}



	template<typename element_type> void GameTutor::CList<element_type>::BeginTravel()
	{
		m_CurrentIter = m_List->begin();
		m_iTravelStepCounter = -1;
	}
	template<typename element_type> element_type GameTutor::CList<element_type>::Travel()
	{
		element_type re = (*m_CurrentIter);
		if (m_CurrentIter != m_List->end())
		{
			m_CurrentIter++;
			m_iTravelStepCounter++;
		}
		return re;
	}
	template<typename element_type> bool GameTutor::CList<element_type>::IsEndOfTravel()
	{
		return ((GetCount()==0) || (m_CurrentIter == m_List->end()));
	}
}

#endif