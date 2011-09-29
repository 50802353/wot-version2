#include "CModelManager.h"

namespace GameTutor
{
	void CModelManager::AddModel(__INT32 id, const char* Md2FileName, const char* textureFileName)
	{
		if (!Get(id))
		{
			MD2Model* model = new MD2Model();
			model->Load(Md2FileName,textureFileName);
			this->Add(id,model);
		}
	}
}