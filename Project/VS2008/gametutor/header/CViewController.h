#ifndef __CVIEWCONTROLLER_H__
#define __CVIEWCONTROLLER_H__

#include "Header.h"
#include "CVSView.h"
#include "CSingleton.h"

namespace GameTutor
{
	template <class View>
	class CViewController: public CSingleton<CViewController<View>> 
	{
		friend CSingleton<CViewController<View>>;
	public:
		static void CreateView(int width, int height,  bool fullscreen = false, const char*name = 0)
		{
			GetInstance()->m_pView = new View(width, height, fullscreen, name);
		}

		View* GetView()
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
		View* m_pView;
		
	};
}

#endif