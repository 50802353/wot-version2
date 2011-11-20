#ifndef __CLUTSTR_H__
#define __CLUTSTR_H__

#include "Header.h"
#include "map"
using namespace std;

#define CLUT_Iterator(type) typename list<type>::iterator

namespace GameTutor
{
	template<typename element_type>
	class CLut
	{
		struct ltstr
		{
			bool operator()(const char* s1, const char* s2) const
			{
				return strcmp(s1, s2) < 0;
			}
		};
	public:
		CLut();
		virtual ~CLut();
		void AddItem(const char * name, element_type ele);
		element_type RemoveItem(const char * name);
		bool GetElement(const char * name, element_type& out);
		int GetCount();			
		void DeallocateElementPointer();
		void Clear();


		void BeginTravel();
		element_type Travel();
		bool IsEndOfTravel();
	protected:
		map<const char *, element_type, ltstr> m_List;
		typename map<const char *, element_type, ltstr>::iterator m_CurrentIter;
	};

	template<typename element_type> GameTutor::CLut<element_type>::CLut()
	{
	}

	template<typename element_type> GameTutor::CLut<element_type>::~CLut()
	{
		this->Clear();
		m_List.clear();
	}


	template<typename element_type> void GameTutor::CLut<element_type>::AddItem(const char *name, element_type ele)
	{
		char *namex = new char[strlen(name) + 1];
		memcpy(namex, name, strlen(name) + 1);
		m_List[namex] = ele;
	}

	template<typename element_type> element_type GameTutor::CLut<element_type>::RemoveItem(const char *name)
	{
		element_type re;
		if (GetElement(name, re))
		{
			map<const char*, element_type, ltstr>::iterator cur  = m_List.find(name);	
			char *key = (char*)((*cur).first);
			m_List.erase(name);
			delete key;
			return re;
		}
		else
		{
			return 0;
		}
	}

	template<typename element_type> bool GameTutor::CLut<element_type>::GetElement(const char *name, element_type & out)
	{
		map<const char*, element_type, ltstr>::iterator cur  = m_List.find(name);
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


	template<typename element_type> int GameTutor::CLut<element_type>::GetCount()
	{
		return m_List.size();
	}

	template<typename element_type> void GameTutor::CLut<element_type>::DeallocateElementPointer()
	{
		if (m_List.size() > 0)
		{
			map<const char*, element_type, ltstr>::iterator cur  = m_List.begin();
			for (cur = m_List.begin(); cur != m_List.end(); cur++)
			{
				/*char *key = (char*)((*cur).first);
				SAFE_DEL(key);*/
				SAFE_DEL((*cur).second);
			}
		}
	}

	template<typename element_type> void GameTutor::CLut<element_type>::Clear()
	{
		if (m_List.size() > 0)
		{
			map<const char*, element_type, ltstr>::iterator cur  = m_List.begin();
			for (cur = m_List.begin(); cur != m_List.end(); cur++)
			{
				char *key = (char*)((*cur).first);
				SAFE_DEL(key);
			}
		}
		m_List.clear();
	}

	template<typename element_type> void GameTutor::CLut<element_type>::BeginTravel()
	{
		m_CurrentIter = m_List.begin();
	}

	template<typename element_type> element_type GameTutor::CLut<element_type>::Travel()
	{
		element_type re = (*m_CurrentIter).second;
		if (m_CurrentIter != m_List.end())
		{
			m_CurrentIter++;
		}
		return re;
	}

	template<typename element_type> bool GameTutor::CLut<element_type>::IsEndOfTravel()
	{
		return ((GetCount()==0) || (m_CurrentIter == m_List.end()));
	}

}
#endif