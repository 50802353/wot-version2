#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "CControllerEventManager.h"
#include "CGraphics2D.h"
#include "Utils.h"
#include "CImageManager.h"
#include "SoundDriver.h"

namespace GameTutor
{
	class CButton
	{
	public:
		CButton(char* filename, char* filename_hover,float scale_up = 1.0);
		void SetPicture(char* filename, char* filename_hover);
		void SetActiveFunction(void (*Func)());
		bool OnControllerEvent(SControllerEvent Event);
		void Draw();
		void SetPosition(SRect<__INT32>);
		void SetPosition(SRect<float>);
		void SetRegion(SRect<__INT32>);
		void SetRegionHover(SRect<__INT32>);
		void SetRegion(SRect<float>);
		void SetImage(char *filename);
		void SetImageHover(char *filename);
		void SetOffset(SPosition2D<__INT32>);
		void SetVisible(bool flag);
		bool Isvisible();
		void SetSelectedSound(GameSound* sound);
	protected:
		void (*ActivateFunc) ();

		CImage *button_image;
		CImage *button_image_hover;
		__INT32 m_iOffsetX;
		__INT32 m_iOffsetY;
		bool m_bIsClicked;
		bool m_bIsHover;
		SRect<__INT32> button_position;
		SRect<__INT32> button_region;
		SRect<__INT32> button_region_hover;
		float scale_up;

		//Visible property
		bool m_bIsVisible;
		GameSound* m_SelectedSound;
	};
}

#endif