#ifndef __CIMAGEMANAGER_H__
#define __CIMAGEMANAGER_H__

#include "Header.h"
#include "CSingleton.h"
#include "CImage.h"
#include "Stream.h"
#include "CResourceLookupTable.h"

using namespace std;

namespace GameTutor
{
	class CImageManager: public CSingleton<CImageManager>, public CResourceLookupTable<CImage>
	{
		friend class  CSingleton<CImageManager>;
	protected:
		CImageManager() {}
	public:
		template <class IODriver> void AddImage(const char* name, bool isForceBindGPU)
		{
			if (!Get(name))
			{
				CReaderStream<IODriver> *F = new CReaderStream<IODriver>(name);
				if (F->GetStatus() == ESTREAM_OPEN)
				{
					char ext[3];
					memcpy(ext, name + (strlen(name) - 3), 3);
					Str_ToLower(ext, 3);
					if (memcmp("tga", ext, 3) == 0)
					{
						CImage *re = CImage::LoadTGA(F);
						this->Add(name, re);
						if (isForceBindGPU)
						{
							re->BindGPU();
						}
					}
				}
				F->Close();
				SAFE_DEL(F);
			}
		}
		virtual ~CImageManager() {}
	};
}

#endif