#include "CExample.h"
#include "CStateLogo.h"

void CExample::Init()
{
	CStateManagement::GetInstance()->SwitchState(new CStateLogo());
	Log("Init");
}

void CExample::Destroy()
{
	Log("Destroy");
}

