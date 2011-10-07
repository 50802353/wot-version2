#include "CControllerEventManager.h"
#include "CDevice.h"
#include "SGameConfig.h"

namespace GameTutor
{
	extern SGameConfig Configuation;
	CControllerEventManager::CControllerEventManager()
	{
		m_pPointerEventManager = CControllerPointerManager::GetInstance();
		m_pKeyEventManager = CControllerKeyManager::GetInstance();
	}
	CControllerEventManager::~CControllerEventManager()
	{
		delete m_pPointerEventManager;
		delete m_pKeyEventManager;
	}

	void CControllerEventManager::OnEvent(SControllerEvent Event)
	{
		switch (Event.Type)
		{
		case ECE_POINTER:
			OnPointerEvent(Event.PointerData);
			break;
		case ECE_KEY:
			OnKeyEvent(Event.KeyData);
			break;
		}
	}


	void CControllerEventManager::OnKeyEvent(SControllerEventKeyData Event)
	{
		switch (Event.Event)
		{
		case EKE_PRESSED:
			m_pKeyEventManager->OnKeyPressed(Event.KeyCode);
			break;
		case EKE_RELEASED:
			m_pKeyEventManager->OnKeyRelease(Event.KeyCode);
			break;
		case EKE_HOLD:
			m_pKeyEventManager->OnKeyHold(Event.KeyCode);
			break;
		}
	}

	void CControllerEventManager::OnPointerEvent(SControllerEventPointerData Event)
	{
		switch (Event.Event)
		{
		case EPE_PRESSED:
			m_pPointerEventManager->PointerPressed(Event.ID, Event.X, Event.Y);
			break;
		case EPE_RELEASED:
			m_pPointerEventManager->PointerReleased(Event.ID, Event.X, Event.Y);
			break;
		case EPE_DRAGGED:
			m_pPointerEventManager->PointerDragged(Event.ID, Event.X, Event.Y);
			break;
		}
	}

	void CControllerEventManager::Update()
	{
		m_pPointerEventManager->Update();
		m_pKeyEventManager->Update();
	}

	////////////////////////////////////////////////////////////////////////
	// CControllerPointerEvent
	////////////////////////////////////////////////////////////////////////
	CControllerPointerManager::CControllerPointerManager()
	{
		Reset();
		m_isEnable = true;
		m_isSleeping = false;
	}

	CControllerPointerManager::~CControllerPointerManager()
	{
		m_PointersInfo.DeallocateElementPointer();
		m_PointersInfo.Clear();
	}


	void CControllerPointerManager::PointerPressed(__INT32 ID, __INT32 x, __INT32 y)
	{
		if (!m_isEnable) return;

		SPointerStorageInfomation *info;
		if (!m_PointersInfo.GetElement(ID, info))
		{
			info = new SPointerStorageInfomation;
			m_PointersInfo.AddItem(ID, info);
			info->LastDraggedX = 0;
			info->LastDraggedY = 0;
			info->DraggedDiffX = 0;
			info->DraggedDiffY = 0;
			info->ID = ID;
		}
		info->PressedX = x;
		info->PressedY = y;
		info->DraggedX = x;
		info->DraggedY = y;
		info->Status = EPE_PRESSED;
		m_isSleeping = false;
	}

	void CControllerPointerManager::PointerReleased(__INT32 ID, __INT32 x, __INT32 y)
	{
		if (!m_isEnable || m_isSleeping) return;
		SPointerStorageInfomation *info;
		if (!m_PointersInfo.GetElement(ID, info))
		{
			info = new SPointerStorageInfomation;
			m_PointersInfo.AddItem(ID, info);
			info->LastDraggedX = 0;
			info->LastDraggedY = 0;
			info->DraggedDiffX = 0;
			info->DraggedDiffY = 0;
			info->ID = ID;
		}
		info->PressedX = x;
		info->PressedY = y;
		info->DraggedX = x;
		info->DraggedY = y;
		info->Status = EPE_RELEASED;
	}

	void CControllerPointerManager::PointerDragged(__INT32 ID, __INT32 x, __INT32 y)
	{
		if (!m_isEnable || m_isSleeping) return;
		SPointerStorageInfomation *info;
		if (!m_PointersInfo.GetElement(ID, info))
		{
			info = new SPointerStorageInfomation;
			m_PointersInfo.AddItem(ID, info);
			info->Status = EPE_NONE;
			info->LastDraggedX = 0;
			info->LastDraggedY = 0;
			info->DraggedDiffX = 0;
			info->DraggedDiffY = 0;
			info->ID = ID;
		}

		if (info->Status == EPE_RELEASED || info->Status == EPE_NONE)
		{
			info->PressedX = x;
			info->PressedY = y;
		}
		// * fixed bug: drag event raise althrough position is not changed
		if (info->Status == EPE_PRESSED)
		{
			if (info->PressedX == x && info->PressedY == y)
			{
				info->PressedX = x;
				info->PressedY = y;
				info->DraggedX = x;
				info->DraggedY = y;
				info->Status = EPE_PRESSED;
				return;
			}
		}
		info->DraggedX = x;
		info->DraggedY = y;
		info->Status = EPE_DRAGGED;
	}

	void CControllerPointerManager::Update()
	{
		if (!m_isEnable || m_isSleeping) return;
		m_PointersInfo.BeginTravel();
		while (!m_PointersInfo.IsEndOfTravel())
		{
			SPointerStorageInfomation *info = m_PointersInfo.Travel();
			if (info->Status == EPE_RELEASED)
			{
				info->Status = EPE_NONE;
			}
			else if (info->Status == EPE_DRAGGED)
			{
				info->DraggedDiffX = info->DraggedX - info->LastDraggedX;
				info->DraggedDiffY = info->DraggedY - info->LastDraggedY;

				info->LastDraggedX = info->DraggedX;
				info->LastDraggedY = info->DraggedY;
			}
			else if (info->Status == EPE_PRESSED)
			{
				info->LastDraggedX = info->DraggedX = info->DraggedDiffX = 0;
				info->LastDraggedY = info->DraggedY = info->DraggedDiffY = 0;
			}
		}
	}

	void CControllerPointerManager::Reset()
	{
		m_PointersInfo.BeginTravel();
		while (!m_PointersInfo.IsEndOfTravel())
		{
			SPointerStorageInfomation *info = m_PointersInfo.Travel();
			info->Status = EPE_NONE;
			info->PressedX = 0;
			info->PressedY = 0;
			info->DraggedX = 0;
			info->DraggedY = 0;
		}
	}

	bool CControllerPointerManager::WasTouchedInside(__INT32 x, __INT32 y, __INT32 w, __INT32 h)
	{
		m_PointersInfo.BeginTravel();
		while (!m_PointersInfo.IsEndOfTravel())
		{
			SPointerStorageInfomation *info = m_PointersInfo.Travel();
			if (info->Status == EPE_PRESSED)
			{
				return ( (info->PressedX > x) && (info->PressedX < (x + w)) && (info->PressedY > y) && (info->PressedY < (y + h)) );
			}
			else if (info->Status  == EPE_DRAGGED)
			{
				return ( (info->DraggedX > x) && (info->DraggedX < (x + w)) && (info->DraggedY > y) && (info->DraggedY < (y + h)) );
			}
		}
		return false;
	}

	bool CControllerPointerManager::WasReleaseInside(__INT32 x, __INT32 y, __INT32 w, __INT32 h)
	{
		m_PointersInfo.BeginTravel();
		while (!m_PointersInfo.IsEndOfTravel())
		{
			SPointerStorageInfomation *info = m_PointersInfo.Travel();
			if (info->Status == EPE_RELEASED)
			{
				return ( (info->PressedX > x) && (info->PressedX < (x + w)) && (info->PressedY > y) && (info->PressedY < (y + h)) );
			}
		}
		return false;
	}


	void CControllerPointerManager::SleepUntilPress()
	{
		Reset();
		m_isSleeping = true;
	}

	void CControllerPointerManager::GetActivePointer(__INT32 maxPointer, __INT32 &num, SPointerUserInfo* info)
	{
		int iNumberOfActiveTouch = 0;
		m_PointersInfo.BeginTravel();
		while ((!m_PointersInfo.IsEndOfTravel()) && (iNumberOfActiveTouch<=maxPointer))
		{
			SPointerStorageInfomation *pointer = m_PointersInfo.Travel();
			if (pointer->Status == EPE_DRAGGED)
			{
				info[iNumberOfActiveTouch].ID = pointer->ID;
				info[iNumberOfActiveTouch].OriginalPosition.X = pointer->PressedX;
				info[iNumberOfActiveTouch].OriginalPosition.Y = pointer->PressedY;
				info[iNumberOfActiveTouch].CurrentPosition.X = pointer->DraggedX;
				info[iNumberOfActiveTouch].CurrentPosition.Y = pointer->DraggedY;
				info[iNumberOfActiveTouch].DragDistanceX = pointer->DraggedX - pointer->PressedX;
				info[iNumberOfActiveTouch].DragDistanceY = pointer->DraggedY - pointer->PressedY;
				info[iNumberOfActiveTouch].DragDiffDistanceX = pointer->DraggedDiffX;
				info[iNumberOfActiveTouch].DragDiffDistanceY = pointer->DraggedDiffY;
				iNumberOfActiveTouch++;
			}
			else if (pointer->Status == EPE_PRESSED)
			{
				info[iNumberOfActiveTouch].ID = pointer->ID;
				info[iNumberOfActiveTouch].OriginalPosition.X = pointer->PressedX;
				info[iNumberOfActiveTouch].OriginalPosition.Y = pointer->PressedY;
				info[iNumberOfActiveTouch].CurrentPosition.X = pointer->PressedX;
				info[iNumberOfActiveTouch].CurrentPosition.Y = pointer->PressedY;
				info[iNumberOfActiveTouch].DragDistanceX = 0;
				info[iNumberOfActiveTouch].DragDistanceY = 0;
				info[iNumberOfActiveTouch].DragDiffDistanceX = 0;
				info[iNumberOfActiveTouch].DragDiffDistanceY = 0;
				iNumberOfActiveTouch++;
			}
		}
	}

	__INT32 CControllerPointerManager::GetNumberOfActivePointers()
	{
		int iNumberOfActiveTouch = 0;
		m_PointersInfo.BeginTravel();
		while (!m_PointersInfo.IsEndOfTravel())
		{
			SPointerStorageInfomation *pointer = m_PointersInfo.Travel();
			if (pointer->Status == EPE_DRAGGED || pointer->Status == EPE_PRESSED)
			{
				iNumberOfActiveTouch++;
			}
		}
		return iNumberOfActiveTouch;
	}

	////////////////////////////////////////////////////////////////////////
	// CControllerKeyManager
	////////////////////////////////////////////////////////////////////////

	CControllerKeyManager::CControllerKeyManager()
	{}
	CControllerKeyManager::~CControllerKeyManager()
	{
		m_KeysInfo.DeallocateElementPointer();
		m_KeysInfo.Clear();
	}

	void CControllerKeyManager::OnKeyPressed(__INT32 keycode)
	{
		if (!m_isEnable) return;

		SKeyStorageInfomation *info;
		if (!m_KeysInfo.GetElement(keycode, info))
		{
			info = new SKeyStorageInfomation;
			m_KeysInfo.AddItem(keycode, info);
			info->HoldDuration = 0;
			info->Keycode = keycode;
			info->Status = EKE_NONE;
		}
		if (info->Status == EKE_PRESSED || info->Status == EKE_HOLD)
		{
			OnKeyHold(keycode);
		}
		else
		{
			info->Status = EKE_PRESSED;
			info->PressedTimeStamp = CDevice::GetInstance()->GetTimer();
		}
	}

	void CControllerKeyManager::OnKeyRelease(__INT32 keycode)
	{
		if (!m_isEnable) return;

		SKeyStorageInfomation *info;
		if (!m_KeysInfo.GetElement(keycode, info))
		{
			info = new SKeyStorageInfomation;
			m_KeysInfo.AddItem(keycode, info);
			info->HoldDuration = 0;
			info->Keycode = keycode;
		}
		info->Status = EKE_RELEASED;
		info->PressedTimeStamp = 0;
	}

	void CControllerKeyManager::OnKeyHold(__INT32 keycode)
	{
		if (!m_isEnable) return;

		SKeyStorageInfomation *info;
		if (!m_KeysInfo.GetElement(keycode, info))
		{
			info = new SKeyStorageInfomation;
			m_KeysInfo.AddItem(keycode, info);
			info->Keycode = keycode;
		}

		if (info->Status == EKE_NONE || info->Status == EKE_RELEASED)
		{
			info->Status = EKE_PRESSED;
			info->PressedTimeStamp = CDevice::GetInstance()->GetTimer();
		}
		else
		{
			info->Status = EKE_HOLD;
			if (info->PressedTimeStamp > 0)
			{
				info->HoldDuration = CDevice::GetInstance()->GetTimer() - info->PressedTimeStamp;
			}
			else
			{
				info->HoldDuration = 0;
				info->PressedTimeStamp = CDevice::GetInstance()->GetTimer();
			}
		}
	}

	void CControllerKeyManager::Update()
	{
		if (!m_isEnable) return;
		m_KeysInfo.BeginTravel();
		while (!m_KeysInfo.IsEndOfTravel())
		{
			SKeyStorageInfomation *info = m_KeysInfo.Travel();
			if (info->Status == EKE_RELEASED)
			{
				info->Status = EKE_NONE;
				info->HoldDuration = 0;
			}
			else if(info->Status == EKE_HOLD)
			{
				if (info->PressedTimeStamp > 0)
				{
					info->HoldDuration = CDevice::GetInstance()->GetTimer() - info->PressedTimeStamp;
				}
				else
				{
					info->HoldDuration = 0;
					info->PressedTimeStamp = CDevice::GetInstance()->GetTimer();
				}
			}
			else if(info->Status == EKE_PRESSED)
			{
				info->HoldDuration = 0;
			}
		}
	}

	bool CControllerKeyManager::WasKeyPressed(int keycode)
	{
		if (!m_isEnable) return false;

		SKeyStorageInfomation *info;
		if (m_KeysInfo.GetElement(keycode, info))
		{
			return info->Status == EKE_PRESSED;
		}
		return false;
	}

	bool CControllerKeyManager::WasKeyHold(int keycode)
	{
		if (!m_isEnable) return false;

		SKeyStorageInfomation *info;
		if (m_KeysInfo.GetElement(keycode, info))
		{
			return info->Status == EKE_HOLD;
		}
		return false;
	}

	bool CControllerKeyManager::WasKeyRelease(int keycode)
	{
		if (!m_isEnable) return false;

		SKeyStorageInfomation *info;
		if (m_KeysInfo.GetElement(keycode, info))
		{
			return info->Status == EKE_RELEASED;
		}
		return false;
	}

	bool CControllerKeyManager::WasAnyKeyPressed()
	{
		if (!m_isEnable) return false;
		m_KeysInfo.BeginTravel();
		while (!m_KeysInfo.IsEndOfTravel())
		{
			SKeyStorageInfomation *info = m_KeysInfo.Travel();
			if (info->Status == EKE_PRESSED)
			{
				return true;
			}
		}
		return false;
	}

	bool CControllerKeyManager::WasAnyKeyHold()
	{
		if (!m_isEnable) return false;
		m_KeysInfo.BeginTravel();
		while (!m_KeysInfo.IsEndOfTravel())
		{
			SKeyStorageInfomation *info = m_KeysInfo.Travel();
			if (info->Status == EKE_HOLD)
			{
				return true;
			}
		}
		return false;
	}

	bool CControllerKeyManager::WasAnyKeyRelease()
	{
		if (!m_isEnable) return false;
		m_KeysInfo.BeginTravel();
		while (!m_KeysInfo.IsEndOfTravel())
		{
			SKeyStorageInfomation *info = m_KeysInfo.Travel();
			if (info->Status == EKE_RELEASED)
			{
				return true;
			}
		}
		return false;
	}

	__UINT64 CControllerKeyManager::GetKeyHoldDuration(int keycode)
	{
		if (WasKeyHold(keycode))
		{
			SKeyStorageInfomation *info;
			m_KeysInfo.GetElement(keycode, info);
			return info->HoldDuration;
		}
		else
		{
			return 0;
		}
	}

	void CControllerKeyManager::Reset()
	{
		m_KeysInfo.BeginTravel();
		while (!m_KeysInfo.IsEndOfTravel())
		{
			SKeyStorageInfomation *info = m_KeysInfo.Travel();
			info->HoldDuration = 0;
			info->PressedTimeStamp = 0;
			info->Status = EKE_NONE;
		}
	}
}