#include "CButton.h"

namespace GameTutor
{
	CButton::CButton(char *filename, char* filename_hover, float scale_up):button_image(NULL),button_image_hover(NULL),
		m_iOffsetX(0),m_iOffsetY(0), button_position(SRect<__INT32>()), button_region(SRect<__INT32>()),button_region_hover(SRect<__INT32>()), 
		m_bIsClicked(false), m_bIsHover(false), ActivateFunc(NULL),m_SelectedSound(NULL)
	{
		SetImage(filename);		
		SetImageHover(filename_hover);		
		this->scale_up = scale_up;
		m_bIsVisible = true;
	}

	bool CButton::OnControllerEvent(SControllerEvent Event)
	{
		if (m_bIsVisible)
		{
			if (Event.Type == ECE_POINTER)
			{
				if ((Event.PointerData.X>=button_position.X)&&
					(Event.PointerData.X<=button_position.X+button_position.W)&&
					(Event.PointerData.Y>=button_position.Y)&&
					(Event.PointerData.Y<=button_position.Y+button_position.H))
				{
					switch (Event.PointerData.Event)
					{	
					case EPE_PRESSED:
						m_SelectedSound->ForcePlay();
						m_bIsClicked = true;
						m_bIsHover = true;
						break;
					case EPE_DRAGGED:
						if (m_bIsClicked)
						{
							m_bIsHover = true;
						}

						break;
					case EPE_RELEASED:
						if (m_bIsClicked)
						{
							if (ActivateFunc)
								ActivateFunc();
							m_bIsClicked = false;
							m_bIsHover = false;
						}
						break;
					default:
						break;
					}
					return true;
				}
				else if (Event.PointerData.Event == EPE_DRAGGED)
				{
					if (m_bIsHover)	m_bIsHover = false;
				}
				else if (Event.PointerData.Event == EPE_RELEASED)
				{
					if (m_bIsClicked) m_bIsClicked = false;
					if (m_bIsHover) m_bIsHover = false;
				}
			}
			return false;
		}
	}

	void CButton::Draw()
	{
		if(m_bIsVisible)
		{
			SRect<__INT32> position = button_position;
			position.X += m_iOffsetX;
			position.Y += m_iOffsetY;
			if (m_bIsHover)
			{
				position.X -= position.W*(scale_up-1.0)/2;
				position.Y -= position.H*(scale_up-1.0)/2;
				position.W *= scale_up;
				position.H *= scale_up;

				CGraphics2D::GetInstance()->DrawImageRegion(position, button_image_hover, button_region_hover);
			}
			else
				CGraphics2D::GetInstance()->DrawImageRegion(position, button_image, button_region);
		}
	}

	void CButton::SetPosition(SRect<__INT32> pos)
	{
		button_position = pos;
	}

	void CButton::SetRegion(SRect<__INT32> reg)
	{
		button_region = reg;
		if ((button_region_hover.X==0) &&(button_region_hover.Y==0) &&(button_region_hover.W==0) &&(button_region_hover.H==0))
			button_region_hover = reg;
	}

	void CButton::SetRegionHover(SRect<__INT32> reg)
	{
		button_region_hover = reg;
	}

	void CButton::SetRegion(SRect<float> reg)
	{
		__INT32 W = button_image->GetWidth();
		__INT32 H = button_image->GetHeight();
		SRect<__INT32> reg_(reg.X * W, reg.Y * H, reg.W * W, reg.H * H);
		button_region = reg_;
		if ((button_region_hover.X==0) &&(button_region_hover.Y==0) &&(button_region_hover.W==0) &&(button_region_hover.H==0))
			button_region_hover = reg_;
	}

	void CButton::SetImage(char *filename)
	{
		button_image = CImageManager::GetInstance()->Get(filename);
		if (!button_image)
		{
			CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filename,true);
			button_image = CImageManager::GetInstance()->Get(filename);
			button_image->FreeBuffer();
		}
		if ((button_position.X==0) &&  (button_position.Y==0) && (button_position.W==0) && (button_position.H==0))
			button_position = SRect<__INT32>(0,0,button_image->GetWidth(),button_image->GetHeight());
		if ((button_region.X==0) &&  (button_region.Y==0) && (button_region.W==0) && (button_region.H==0))
			button_region = SRect<__INT32>(0,0,button_image->GetWidth(),button_image->GetHeight());
	}

	void CButton::SetImageHover(char *filename)
	{
		button_image_hover = CImageManager::GetInstance()->Get(filename);
		if (!button_image_hover)
		{
			CImageManager::GetInstance()->AddImage<CFileWin32Driver>(filename,true);
			button_image_hover = CImageManager::GetInstance()->Get(filename);
			button_image_hover->FreeBuffer();
		}
	}

	void CButton::SetOffset(SPosition2D<__INT32> pos)
	{
		m_iOffsetX = pos.X;
		m_iOffsetY = pos.Y;
	}

	void CButton::SetActiveFunction(void (*Func)())
	{
		ActivateFunc = Func;
	}
	void CButton::SetVisible(bool flag)
	{
		m_bIsVisible = flag;
	}
	bool CButton::Isvisible()
	{
		return m_bIsVisible;
	}
	void CButton::SetSelectedSound(GameSound* sound){
		m_SelectedSound = sound;
	}
}