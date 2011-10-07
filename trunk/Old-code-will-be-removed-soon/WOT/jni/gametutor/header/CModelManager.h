#ifndef __CMODELMANAGER_H__
#define __CMODELMANAGER_H__

#include "Header.h"
#include "CSingleton.h"
#include "CMD2Model.h"
#include "Stream.h"
#include "CResourceLookupTableI.h"
#include "Utils.h"

namespace GameTutor
{
	class CModelManager: public CSingleton<CModelManager>, public CResourceLookupTableI<MD2Model>
	{
		friend class  CSingleton<CModelManager>;
	protected:
		CModelManager() {}
	public:
		void AddModel(__INT32 id, const char* Md2FileName, const char* textureFileName);
		virtual ~CModelManager() {}
	};
}

#endif