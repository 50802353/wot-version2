#ifndef __CLUTI_H__
#define __CLUTI_H__

#include "Header.h"
#include "map"
using namespace std;

namespace GameTutor
{
	template<typename element_type>
	class CLutI
	{
		struct ltstr
		{
			bool operator()(__INT32 s1, __INT32 s2) const
			{
				return s1 < s2;
			}
		};
	public:
		CLutI();
		virtual ~CLutI();
		void AddItem(__INT32 key, element_type ele);
		element_type RemoveItem(__INT32 key);
		bool GetElement(__INT32 key, element_type& out);
		int GetCount();			
		void DeallocateElementPointer();
		void Clear();

		void BeginTravel();
		element_type Travel();
		bool IsEndOfTravel();
	protected:
		map<__INT32, element_type, ltstr> m_List;
		typename map<__INT32, element_type, ltstr>::iterator m_CurrentIter;
	};

	template<typename element_type> GameTutor::CLutI<element_type>::CLutI()
	{
	}

	template<typename element_type> GameTutor::CLutI<element_type>::~CLutI()
	{
		m_List.clear();
	}


	template<typename element_type> void GameTutor::CLutI<element_type>::AddItem(__INT32 key, element_type ele)
	{
		m_List[key] = ele;
	}

	template<typename element_type> element_type GameTutor::CLutI<element_type>::RemoveItem(__INT32 key)
	{
		element_type re;
		if (GetElement(key, re))
		{
			map<__INT32, element_type, ltstr>::iterator cur  = m_List.find(key);	
			m_List.erase(key);
			return re;
		}
		else
		{
			return 0;
		}
	}

	template<typename element_type> bool GameTutor::CLutI<element_type>::GetElement(__INT32 key, element_type & out)
	{
		map<__INT32, element_type, ltstr>::iterator cur  = m_List.find(key);
		if (cur != m_List.end())
		{
			out = (*cur).second;
			return true;
		}
		else
		{
			return false;
		}
	}


	template<typename element_type> int GameTutor::CLutI<element_type>::GetCount()
	{
		return m_List.size();
	}

	template<typename element_type> void GameTutor::CLutI<element_type>::DeallocateElementPointer()
	{
		if (m_List.size() > 0)
		{
			map<__INT32, element_type, ltstr>::iterator cur  = m_List.begin();
			for (cur = m_List.begin(); cur != m_List.end(); cur++)
			{
				SAFE_DEL((*cur).second);
			}
		}
	}

	template<typename element_type> void GameTutor::CLutI<element_type>::Clear()
	{
		m_List.clear();
	}

	template<typename element_type> void GameTutor::CLutI<element_type>::BeginTravel()
	{
		m_CurrentIter = m_List.begin();
	}
	template<typename element_type> element_type GameTutor::CLutI<element_type>::Travel()
	{
		element_type re = (*m_CurrentIter).second;
		if (m_CurrentIter != m_List.end())
		{
			m_CurrentIter++;
		}
		return re;
	}
	template<typename element_type> bool GameTutor::CLutI<element_type>::IsEndOfTravel()
	{
		return ((GetCount()==0) || (m_CurrentIter == m_List.end()));
	}
}
#endif