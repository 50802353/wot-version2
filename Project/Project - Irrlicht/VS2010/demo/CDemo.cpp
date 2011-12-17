#include "CDemo.h"
#include "CStateIngame.h"
#include "CStateLogo.h"

void CDemo::Init()
{
	CStateManagement::GetInstance()->SwitchState(new CStateLogo());
	Log("Init");
}

void CDemo::Destroy()
{
	Log("Destroy");
}

