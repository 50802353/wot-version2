#include "CStateIngame.h"
#include "CStateLoading.h"
#include "CSoundManagement.h"
#include "CExample.h"

__UINT16 numImg = 11;
CImage *_tmpImg;
char* ImageResource[] =		{	PATH_GRAPHIC("font_GillSanUltraBold2.tga"),
								PATH_GRAPHIC("Bullet/spos_mf0.tga"),
								PATH_GRAPHIC("Enemy/_Boss/boss.pcx"),
								PATH_GRAPHIC("Enemy/_Dragoon/dragoon.pcx"),
								PATH_GRAPHIC("InGameBar.tga"),
								PATH_GRAPHIC("terrain.tga"),
								PATH_GRAPHIC("HPBar.tga"),
								PATH_GRAPHIC("Blue_ground.tga"),
								PATH_GRAPHIC("tower_demo.tga"),
								PATH_GRAPHIC("terrain.tga"),
								PATH_GRAPHIC("terrain_heightmap.tga")
							};

__UINT16 numSound = 4;
char* SoundResource[] =		{	PATH_AUDIO("AButtonSelect.wav"),
								PATH_AUDIO("AIngameBackground.ogg"),
								PATH_AUDIO("ALose.wav"),
								PATH_AUDIO("AWin.wav"),

							};


char* SoundKey[4] =			{	(char*)"Button_Select",
								(char*)"InGame_Background",
								(char*)"LoseBG",
								(char*)"WinBG",
							};


__INT32 _modelKey;


ModelProperties *_tmpModel;

char* graphic_path = (char*)PATH_RESOURCE_GRAPHIC;
char _model[100];
char _texture[100];
char _preview[100];
char _temp[100];


__UINT16 ResCount;

CStateLoading::CStateLoading(): CState(), m_iPercent(0), FinishedLoadAllResources(false)
{
	memset(_model,0,sizeof(char)*100);
	memset(_texture,0,sizeof(char)*100);
	memset(_preview,0,sizeof(char)*100);
	memset(_temp,0,sizeof(char)*100);
	strcpy(_model,graphic_path);
	strcpy(_texture,graphic_path);
	strcpy(_preview,graphic_path);
	strcpy(_temp,graphic_path);
}

void CStateLoading::Init()
{
	Log("State Loading: Init");
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("WOT_Loading.tga"),true);
	Background = CImageManager::GetInstance()->Get(PATH_GRAPHIC("WOT_Loading.tga"));
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("loading1.tga"),true);
	loading_icon = CImageManager::GetInstance()->Get(PATH_GRAPHIC("loading1.tga"));
	CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PATH_GRAPHIC("loading3.tga"),true);
	loading_icon2 = CImageManager::GetInstance()->Get(PATH_GRAPHIC("loading3.tga"));

	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("ALoading.ogg"),(char*) "loading_bg");
	CSoundManagement::GetInstance()->AddSound(PATH_AUDIO("ALoadingMachine1.ogg"),(char*) "loading_sfx");

	A_Background = CSoundManagement::GetInstance()->GetSound((char*)"loading_bg");
	A_Background->SetLoop(true);
	A_Background->Play();
	A_Background2 = CSoundManagement::GetInstance()->GetSound((char*)"loading_sfx");
	A_Background2->Play();	

	m_iPercent = 0;
	m_iLoadState = 0;
	ResCount = 0;
}

void CStateLoading::Update()
{	
	char _map[100];
	memset(_map,0,sizeof(char)*100);
	strcpy(_map,graphic_path);
	bool isFinish = false;
	switch (m_iLoadState)
	{

	 ////////////////////////
	// Load Image
	case 0:
		if (ResCount < numImg)
		{
			CImageManager::GetInstance()->AddImage<CFileWin32Driver>(ImageResource[ResCount],true);
			Log ("Loading %d % \t %s", m_iPercent, ImageResource[ResCount]);
			CImageManager::GetInstance()->Get(ImageResource[ResCount])->FreeBuffer();
			ResCount++;

			m_iPercent = (float(ResCount) / numImg) * 15;
		}
		else {
			m_iLoadState++;
			ResCount = 0;
		}
		break;

	 ////////////////////////
	// Load Sound

	case 1:
		if (ResCount <numSound)
		{
			CSoundManagement::GetInstance()->AddSound(SoundResource[ResCount], SoundKey[ResCount]);
			Log ("Loading %d % \t %s", m_iPercent, SoundResource[ResCount]);
			ResCount++;
			m_iPercent = 15 + (float(ResCount) / numSound) * 5;
		}
		else {
			m_iLoadState++;
			ResCount = 0;
		}
		break;

	 ////////////////////////
	// Load Map
	case 2:
		memset(_temp,0,sizeof(char)*100);
		sprintf(_temp, "Level%d.wotmap", CExample::m_LevelChose);
		strcat (_map, _temp);
		CStateIngame::currentfile = new CWOTMapfile();
		CStateIngame::currentfile->loadfromFile(_map);
		Log ("Loading %d % \t %s", m_iPercent, _map);
		m_iLoadState++;
		m_iPercent++;
		ResCount = 0;
		break;

	 ////////////////////////
	// Load Model
	case 3:
		if (ResCount == 0)
		{
			CStateIngame::currentfile->m_lstModelProperties->BeginTravel();
			ResCount++;
		}
		else if (ResCount >0 && (ResCount%3) == 1 && !CStateIngame::currentfile->m_lstModelProperties->IsEndOfTravel()) {
			strcpy (_model, PATH_GRAPHIC());
			strcpy (_preview, PATH_GRAPHIC());
			strcpy (_texture, PATH_GRAPHIC());
			_tmpModel = CStateIngame::currentfile->m_lstModelProperties->Travel(_modelKey);
			strcat (_model, _tmpModel->fileModel);
			strcat (_texture, _tmpModel->fileTexture);
			strcat (_preview, _tmpModel->filePreview);
			CImageManager::GetInstance()->AddImage<CFileWin32Driver>(_texture,true);			

			ResCount++;
			m_iPercent += (1.0/(float(CStateIngame::currentfile->m_lstModelProperties->GetCount())*3))*80;
			Log ("Loading %d % \t %s", m_iPercent, _texture);
		}
		else if (ResCount >0 && (ResCount%3) == 2) {
			CImageManager::GetInstance()->AddImage<CFileWin32Driver>(_preview,true);			

			ResCount++;
			m_iPercent += (1.0/(float(CStateIngame::currentfile->m_lstModelProperties->GetCount())*3))*80;
			Log ("Loading %d % \t %s", m_iPercent, _preview);
		}
		else if (ResCount >0 && (ResCount%3) == 0) {
			CModelManager::GetInstance()->AddModel(_modelKey,_model,_texture);			

			ResCount++;
			m_iPercent += (1.0/(float(CStateIngame::currentfile->m_lstModelProperties->GetCount())*3))*80;
			Log ("Loading %d % \t %s", m_iPercent, _model);
		}
		else 
		{
			m_iLoadState++;
		}
				
		break;

	 ////////////////////////
	// Finished
	case 4:
		CStateManagement::GetInstance()->SwitchState(new CStateIngame());
		break;
	}
}

void CStateLoading::Render()
{
	__UINT32 w = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetWidth());
	__UINT32 h = (CViewController<VIEWCLASS>::GetInstance()->GetView()->GetHeight());
	CGraphics2D::GetInstance()->Clear(SColor<float>(0.0f,0.0f,0.0f,1.0f));
	float angle = atan(float(h)/w);
	float angle2 =  angle-5.0f*m_iPercent*PI/180.0f;
	float d = sqrt(pow(float(loading_icon->GetWidth()),2)+pow(float(loading_icon->GetHeight()),2));

	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(0, 0, w, h),Background,SRect<__INT32>(0,0,800,480));	

	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(w/2-256,h/2-256,512,512),loading_icon,SRect<__INT32>(0,0,loading_icon->GetWidth(),loading_icon->GetHeight()));
	CGraphics2D::GetInstance()->ObjectRotate(EG2D_LASTOBJ, m_iPercent%2, Z_AXIS);
	CGraphics2D::GetInstance()->ObjectTranslate(EG2D_LASTOBJ, float(m_iPercent%2)/200,0,0);
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(w/2-256,h/2-256,512,512),loading_icon2,SRect<__INT32>(0,0,loading_icon->GetWidth(),loading_icon->GetHeight()));
	CGraphics2D::GetInstance()->ObjectRotate(EG2D_LASTOBJ, 5.0f*m_iPercent, Z_AXIS);

	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(10, 7, m_iPercent*389/100, 26),Background,SRect<__INT32>(800,0,201,24));	

	CGraphics2D::GetInstance()->Flush();
}

void CStateLoading::Exit()
{
	CSoundManagement::GetInstance()->Free((char*)"loading_bg");
	CSoundManagement::GetInstance()->Free((char*)"loading_sfx");
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("WOT_Loading.tga"));
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("loading1.tga"));
	CImageManager::GetInstance()->Free(PATH_GRAPHIC("loading3.tga"));
	Log("State Loading: Exit");
}
