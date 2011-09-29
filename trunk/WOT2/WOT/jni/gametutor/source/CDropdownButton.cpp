#include "CDropdownButton.h"

namespace GameTutor
{
	void CDropdownButton::SetDropdownFunction(void (*Func)())
	{
		DropdownFunc = Func;
	}

	bool CDropdownButton::OnControllerEvent(SControllerEvent Event)
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
					if (m_bIsClicked) 
					{
						m_bIsClicked = false;
						if (DropdownFunc)
						DropdownFunc();
					}
					if (m_bIsHover) m_bIsHover = false;
					
				}
			}
			return false;
		}
	}

}