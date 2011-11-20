#include "CDemo.h"
#include "CStateIngame.h"

void CDemo::Init()
{
	CStateManagement::GetInstance()->SwitchState(new CStateIngame());
	Log("Init");
}

void CDemo::Destroy()
{
	Log("Destroy");
}

