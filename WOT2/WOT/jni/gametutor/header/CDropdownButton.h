#ifndef __CDROPDOWNBUTTON_H__
#define __CDROPDOWNBUTTON_H__

#include "CButton.h"

namespace GameTutor
{
	class CDropdownButton:public CButton
	{
	public:
		CDropdownButton(char *filename, char* filename_hover, float scale_up):CButton(filename, filename_hover, scale_up),DropdownFunc(NULL){}

		bool OnControllerEvent(SControllerEvent Event);
		void SetDropdownFunction(void (*Func)());
	private:
		void (*DropdownFunc) ();
	};
}

#endif
