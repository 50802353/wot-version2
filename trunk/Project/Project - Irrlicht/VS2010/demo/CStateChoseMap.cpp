#include "CStateChoseMap.h"
#include "CStateMainMenu.h"
#include "CStateIngame.h"

#define CHOSEMAP_BACKGROUND_IMAGE "./resource/backgroundChoseMap.jpg"
#define CHOSEMAP_BACKGROUND_MUSIC "./resource/backgroundChoseMap.wav"

class ChoseMapEventReceiver:public MyEventReceiver
{
public:
	ChoseMapEventReceiver(CStateChoseMap* state):MyEventReceiver()
	{
		this->state = state;
	}

	virtual bool ChoseMapEventReceiver::OnEvent(const SEvent& event)
	{
		bool inAction = false;
		if (MyEventReceiver::OnEvent(event)) inAction=true;
		if (event.EventType==EEVENT_TYPE::EET_GUI_EVENT)
		{
			switch (event.GUIEvent.EventType)
			{
			case gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED:
				if (event.GUIEvent.Caller->getID()==E_GBCM_BACK)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateMainMenu());
				}
				else if (event.GUIEvent.Caller->getID()==E_GBCM_MAP1)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateIngame());
				}
				else if (event.GUIEvent.Caller->getID()==E_GBCM_MAP2)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateIngame());
				}

				inAction=true;
				break;
			}
		}
		return inAction;
	}

private:
	CStateChoseMap* state;
};

CStateChoseMap::CStateChoseMap(): CState()
{}

void CStateChoseMap::Init()
{
	core::rect<s32> vp = driver->getViewPort();
	screen = guienv->addImage(vp, 0, -1, L"");
	screen->setImage(driver->getTexture(CHOSEMAP_BACKGROUND_IMAGE));
	screen->setScaleImage(true);

	bBack = guienv->addButton(core::recti(vp.LowerRightCorner-core::dimension2di(220,90),core::dimension2di(200,20)),screen, E_GBCM_BACK);
	bBack->setImage(driver->getTexture("./resource/button/back.png"));

	bMap1 = guienv->addButton(core::recti(vp.LowerRightCorner-core::dimension2di(220,60),core::dimension2di(200,20)),screen, E_GBCM_MAP1);
	bMap1->setImage(driver->getTexture("./resource/button/map1.png"));

	bMap2 = guienv->addButton(core::recti(vp.LowerRightCorner-core::dimension2di(220,30),core::dimension2di(200,20)),screen, E_GBCM_MAP2);
	bMap2->setImage(driver->getTexture("./resource/button/map2.png"));

	Log("State ChoseMap: Init");
	CAudioPlayer::GetInstance()->Load<CFileWin32Driver>(CHOSEMAP_BACKGROUND_MUSIC);
	CAudioPlayer::GetInstance()->Play(CHOSEMAP_BACKGROUND_MUSIC,true);

	receiver = new ChoseMapEventReceiver(this);
	CIrrlichtView::GetInstance()->device->setEventReceiver(receiver);

}

void CStateChoseMap::Update()
{	
}

void CStateChoseMap::Render()
{
}

void CStateChoseMap::Exit()
{
	Log("State Logo: Exit");	
	screen->remove();
	if (CAudioPlayer::GetInstance()->IsPlaying(CHOSEMAP_BACKGROUND_MUSIC))
		CAudioPlayer::GetInstance()->Stop(CHOSEMAP_BACKGROUND_MUSIC);
}
