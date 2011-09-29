#ifndef __CRESOURCELOOKUPTABLE_H__
#define __CRESOURCELOOKUPTABLE_H__

#include "Header.h"
#include "CLookupTableStr.h"

namespace GameTutor
{
	template <class ResourceType>
	class CResourceLookupTable
	{
	public:
		CResourceLookupTable()
		{
			m_LookupTable = new CLut<ResourceType*>();
		}

		virtual ResourceType* Get(const char* name)
		{
			ResourceType* re = 0;
			bool found = m_LookupTable->GetElement(name, re);
			if (found)
			{
				return re;
			}
			else
			{
				return 0;
			}
		}

		virtual void Add(const char* name, ResourceType* item)
		{
			m_LookupTable->AddItem(name, item);
		}

		virtual void Free(const char* name)
		{
			ResourceType *item = m_LookupTable->RemoveItem(name);
			SAFE_DEL(item);
		}

		virtual void Clean()
		{
			m_LookupTable->DeallocateElementPointer();
			m_LookupTable->Clear();
		}

		virtual ~CResourceLookupTable()
		{
			m_LookupTable->DeallocateElementPointer();
			m_LookupTable->Clear();
			SAFE_DEL(m_LookupTable);
		}
	protected:
		CLut<ResourceType*> *m_LookupTable;
	};
}
#endif