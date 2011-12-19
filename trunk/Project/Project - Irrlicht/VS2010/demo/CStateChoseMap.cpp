#include "CStateChoseMap.h"
#include "CStateMainMenu.h"
#include "CStateIngame.h"

#define CHOSEMAP_BACKGROUND_IMAGE "./resource/world-map.png"
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
					CStateManagement::GetInstance()->SwitchState(new CStateIngame(MapData,0));
				}
				else if (event.GUIEvent.Caller->getID()==E_GBCM_MAP2)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateIngame(MapData,1));
				}
				else if (event.GUIEvent.Caller->getID()==E_GBCM_MAP3)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateIngame(MapData,2));
				}
				else if (event.GUIEvent.Caller->getID()==E_GBCM_MAP4)
				{
					CStateManagement::GetInstance()->SwitchState(new CStateIngame(MapData,3));
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

	guienv->getSkin()->setColor(gui::EGUI_DEFAULT_COLOR::EGDC_WINDOW, video::SColor(0,0,0,0));
	
	bBack = guienv->addButton(core::recti(vp.LowerRightCorner-core::dimension2di(218,117),core::dimension2di(218,117)),screen, E_GBCM_BACK);
	bBack->setImage(driver->getTexture("./resource/back-arrow.png"));
	bBack->setUseAlphaChannel(true);
	

	bMap1 = guienv->addButton(core::recti(core::vector2di(150,180),core::dimension2di(50,50)),screen, E_GBCM_MAP1);
	bMap1->setImage(driver->getTexture("./resource/castle1.png"));

	bMap2 = guienv->addButton(core::recti(core::vector2di(230,380),core::dimension2di(50,50)),screen, E_GBCM_MAP2);
	bMap2->setImage(driver->getTexture("./resource/castle2.png"));

	bMap3 = guienv->addButton(core::recti(core::vector2di(530,150),core::dimension2di(50,50)),screen, E_GBCM_MAP3);
	bMap3->setImage(driver->getTexture("./resource/castle3.png"));

	bMap4 = guienv->addButton(core::recti(core::vector2di(420,270),core::dimension2di(50,50)),screen, E_GBCM_MAP4);
	bMap4->setImage(driver->getTexture("./resource/castle4.png"));

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
