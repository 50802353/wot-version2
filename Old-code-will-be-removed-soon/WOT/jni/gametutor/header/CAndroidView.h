#ifndef __CANDROIDVIEW_H__
#define __CANDROIDVIEW_H__



#include "Header.h"
#include "CSingleton.h"

#if (CONFIG_PLATFORM==PLATFORM_ANDROID)
namespace GameTutor
{
	class CAndroidView: public CAbsSingleton<CAndroidView>
	{
	public:
		CAndroidView(__INT32 w, __INT32 h, bool fullscreen = false, const char*name = 0);
		virtual ~CAndroidView();
		void Update();
		__INT32 GetWidth() {return m_iWidth;}
		__INT32 GetHeight() {return m_iHeight;}
		__INT32 IsFullScreen() {return m_isFullScreen;}
		
	private:
		__INT32 m_iWidth;
		__INT32 m_iHeight;
		bool m_isFullScreen;
		char *m_strTitle;
		__INT32 ConvertKeyCode(int keycode);

	public:
		void onKeyDown(int keycode);
		void onKeyUp(int keycode);
		void onKeyTyped(int keycode);
		void onTouchDown(int x, int y);
		void onTouchUp(int x, int y);
		void onTouchMove(int x, int y);

	private:
		bool m_isTouch;
		bool m_isKeyDown;
	};
}

#endif //(CONFIG_PLATFORM==PLATFORM_ANDROID)
#endif