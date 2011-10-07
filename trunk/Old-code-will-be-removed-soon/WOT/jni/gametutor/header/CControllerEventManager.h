#ifndef __CCONTROLLEREVENTMANAGER_H__
#define __CCONTROLLEREVENTMANAGER_H__
#include "Header.h"
#include "CLookupTableI.h"
#include "CSingleton.h"
#include "SGraphics.h"


namespace GameTutor
{
	class CControllerEventManager;
#include "CControllerEventManager_inc.h"
#include "CControllerPointerManager_inc.h"
#include "CControllerKeyManager_inc.h"

	class CControllerEventManager: public CSingleton<CControllerEventManager>
	{
		friend class CSingleton<CControllerEventManager>;
	protected:
		CControllerEventManager();
	public:
		virtual ~CControllerEventManager();
		void OnEvent(SControllerEvent Event);
		void Update();
	private:
		void OnPointerEvent(SControllerEventPointerData Event);
		void OnKeyEvent(SControllerEventKeyData Event);
		CControllerPointerManager *m_pPointerEventManager;
		CControllerKeyManager *m_pKeyEventManager;
	};
}

#endif