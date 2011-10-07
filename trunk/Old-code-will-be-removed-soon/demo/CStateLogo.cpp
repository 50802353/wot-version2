
#include "CStateLogo.h"
#include "CStateLoading.h"

CStateLogo::CStateLogo():m_iCount(0), CState()
{}

void CStateLogo::Init()
{
	Log("---");
	Log("State Logo: Init");
	Log("[Do nothing in a short time]");
	//Display logo for a short time

	m_iCount = 0;
}

void CStateLogo::Update()
{
	m_iCount++;
	if (m_iCount >= 50)
	{
		CStateManagement::GetInstance()->SwitchState(new CStateLoading());
	}
}

void CStateLogo::Render()
{
	//Do nothing
}

void CStateLogo::Exit()
{
	Log("State Logo: Exit");
}
