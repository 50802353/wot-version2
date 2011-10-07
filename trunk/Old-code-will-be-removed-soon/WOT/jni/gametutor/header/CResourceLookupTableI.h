#ifndef __CRESOURCELOOKUPTABLE_I_H__
#define __CRESOURCELOOKUPTABLE_I_H__

#include "Header.h"
#include "CLookupTableI.h"

namespace GameTutor
{
	template <class ResourceType>
	class CResourceLookupTableI
	{
	public:
		CResourceLookupTableI()
		{
			m_LookupTable = new CLutI<ResourceType*>();
		}

		virtual ResourceType* Get(__INT32 key)
		{
			ResourceType* re = 0;
			bool found = m_LookupTable->GetElement(key,re);
			if (found)
			{
				return re;
			}
			else
			{
				return 0;
			}
		}

		virtual void Add(__INT32 key, ResourceType* item)
		{
			m_LookupTable->AddItem(key,item);
		}

		virtual void Free(__INT32 key)
		{
			ResourceType *item = m_LookupTable->RemoveItem(key);
			SAFE_DEL(item);
		}

		virtual void Clean()
		{
			m_LookupTable->DeallocateElementPointer();
			m_LookupTable->Clear();
		}

		virtual ~CResourceLookupTableI()
		{
			m_LookupTable->DeallocateElementPointer();
			m_LookupTable->Clear();
			SAFE_DEL(m_LookupTable);
		}
	protected:
		CLutI<ResourceType*> *m_LookupTable;
	};
}
#endif