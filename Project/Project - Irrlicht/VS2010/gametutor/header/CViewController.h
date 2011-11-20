#ifndef __CVIEWCONTROLLER_H__
#define __CVIEWCONTROLLER_H__

#include "Header.h"
#include "CIrrlichtView.h"
#include "CSingleton.h"

namespace GameTutor
{
	class CViewController: public CSingleton<CViewController> 
	{
		friend CSingleton<CViewController>;
	public:
		static void CreateView(int width, int height, irr::IrrlichtDevice* &Irrlichtdevice, bool fullscreen = false, const char*name = 0)
		{
			GetInstance()->m_pView = new CIrrlichtView(width, height, Irrlichtdevice, fullscreen, name);
		}

		CIrrlichtView* GetView()
		{
			return m_pView;
		}

		virtual ~CViewController() 
		{
			if (m_pView) delete m_pView;
		}

		__INT32 GetWidth()
		{
			if (m_pView)
			{
				m_pView->GetWidth();
			}
			else
			{
				return 0;
			}
		}

		__INT32 GetHeight()
		{
			if (m_pView)
			{
				m_pView->GetHeight();
			}
			else
			{
				return 0;
			}
		}
	protected:
		
		CViewController(): m_pView(0) {}
		CIrrlichtView* m_pView;
		
	};
}

#endif