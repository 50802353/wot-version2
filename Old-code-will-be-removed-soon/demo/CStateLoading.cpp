
#include "CStateLoading.h"
#include "CStatePoster.h"

CStateLoading::CStateLoading():m_iCount(0), CState()
{}

void CStateLoading::Init()
{
	Log("---");
	Log("State Loading: Init");
	Log("[Display something while loading]");
	//Display grogress bar/text

	m_iCount = 0;
}

void CStateLoading::Update()
{
	m_iCount+=10;
	if (m_iCount >= 100)
	{
		CStateManagement::GetInstance()->SwitchState(new CStatePoster());
	}
}

void CStateLoading::Render()
{
		Log("     Curent loading progess: %d%%", m_iCount);
}

void CStateLoading::Exit()
{
	Log("State Loading: Exit");
}
