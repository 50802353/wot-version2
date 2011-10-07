#ifndef __CPARTICLEMANAGER_H__
#define __CPARTICLEMANAGER_H__

#include "Header.h"
#include "CSingleton.h"
#include "MyParticleSystem.h"
#include "Stream.h"
#include "CResourceLookupTableI.h"
#include "Utils.h"

using namespace std;

namespace GameTutor
{
	class CParticleManager: public CSingleton<CParticleManager>, public CResourceLookupTableI<MyParticleSystem>
	{
		friend class  CSingleton<CParticleManager>;
	protected:
		CParticleManager() {}
	public:

		void AddParticle(__INT32 key, MyParticleSystem *particle)
		{
			while (Get(key))
				key++;
			this->Add(key, particle);
		}

		void Update()
		{
			m_LookupTable->BeginTravel();
			while (!(m_LookupTable->IsEndOfTravel()))
			{
				MyParticleSystem* particle = m_LookupTable->Travel();
				particle->Update();
				if (particle->isDied())
				{
					particle = m_LookupTable->RemoveCurrentTravel();
					SAFE_DEL(particle);
				}
			}
		}

		void Render()
		{
			m_LookupTable->BeginTravel();
			while (!(m_LookupTable->IsEndOfTravel()))
			{
				MyParticleSystem* particle = m_LookupTable->Travel();
				particle->Render(NULL);
			}
		}

		virtual ~CParticleManager() {}
	};
}

#endif