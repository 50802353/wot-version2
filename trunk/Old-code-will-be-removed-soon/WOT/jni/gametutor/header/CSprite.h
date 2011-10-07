#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include "Header.h"
#include "CList.h"
#include "Utils.h"
#include "SGraphics.h"
#include "CImage.h"
#include "CStringBufferStream.h"
#include "Stream.h"
#include "CImageManager.h"
#include "CGraphics2D.h"
#include "SGameConfig.h"

namespace GameTutor
{
	extern SGameConfig Configuation;

	enum ESpriteDBFrameType
	{
		ESPRFRAME_TYPE_RECT_IMG,
		ESPRFRAME_TYPE_RECT_COLOR,
	};

	struct SSpriteDBHeader
	{
		__UINT16 Version;
		__UINT8 NumberOfImages;
		__UINT16 NumberFrames;
		__UINT16 NumberAnimations;
		__UINT8 Fps;
	};

	struct SSpriteDBBitmap
	{
		__UINT16 ID;
		char Name[128];
	};

	struct SSpriteDBFrameRectImg
	{
		__UINT16 ImgID;
		__UINT16 OffsetX;
		__UINT16 OffsetY;
		__UINT16 Width;
		__UINT16 Height;
		__UINT8 Reserved[30];
	};

	struct SSpriteDBFrameRectColor
	{
		__UINT16 Width;
		__UINT16 Height;
		__UINT8 Alpha;
		__UINT8 Red;
		__UINT8 Green;
		__UINT8 Blue;
		__UINT8 Reserved[32];
	};

	struct SSpriteDBFrame
	{
		__UINT16 ID;
		__UINT16 Type;
		union
		{
			SSpriteDBFrameRectImg RectImgFrame;
			SSpriteDBFrameRectColor RectColorFrame;
			__UINT8 Reserved[40];
		};
	};

	struct SSpriteDBAnimKeyFrame
	{
		__UINT16 FrameID;
		__UINT16 OffsetX;
		__UINT16 OffsetY;
		__UINT16 Loop;
	};

	struct SSpriteDBAnimation
	{
		__UINT16 ID;
		char Name[128];
		CList<SSpriteDBAnimKeyFrame*>* KeyFrameList;
	};

	class CSpriteDB
	{
		friend class CSprite;
	public:
		template <class IODriver> static CSpriteDB* ImportFromTextFile(const char *file)
		{
			CReaderStream<IODriver> F(file);
			if (F.GetStatus() == ESTREAM_ERROR)
			{
				return 0;
			}
			CStringBufferStream BStream(&F);
			CStringBufferStream *txtStream = &BStream;

			CSpriteDB* re = 0;

			int numLines = txtStream->GetNumOfLine();

			if (!numLines) 
			{
				return 0;
			}

			re = new CSpriteDB();
			CToken *tok;
			SSpriteDBAnimation *anim = 0;
			for (int i = 0; i < numLines; i++)
			{
				tok = txtStream->GetLineToken(i);
				int numOfToken = tok->GetTokenCount();


				if (numOfToken>0)
				{
					if (tok->IsTokenEqual(0, "VERSION"))
					{
						re->m_Header.Version = tok->GetTokenValueAsInt(1);
					}
					else if (tok->IsTokenEqual(0, "IMAGES"))
					{
						re->m_Header.NumberOfImages = tok->GetTokenValueAsInt(1);
					}
					else if (tok->IsTokenEqual(0, "FRAMES"))
					{
						re->m_Header.NumberFrames = tok->GetTokenValueAsInt(1);
					}
					else if (tok->IsTokenEqual(0, "ANIMS"))
					{
						re->m_Header.NumberAnimations = tok->GetTokenValueAsInt(1);
					}
					else if (tok->IsTokenEqual(0, "FPS"))
					{
						re->m_Header.Fps = tok->GetTokenValueAsInt(1);
					}
					else if (tok->IsTokenEqual(0, "IMG"))
					{
						SSpriteDBBitmap *bitmap = new SSpriteDBBitmap();
						bitmap->ID = tok->GetTokenValueAsInt(1);
						tok->GetToken(2, bitmap->Name);
						re->m_Bitmaps.AddItem(bitmap);
						CImageManager::GetInstance()->AddImage<IODriver>(bitmap->Name, true);
					}
					else if (tok->IsTokenEqual(0, "FRAME"))
					{
						SSpriteDBFrame *frame = new SSpriteDBFrame();
						frame->ID = tok->GetTokenValueAsInt(1);
						frame->Type = tok->GetTokenValueAsInt(2);
						if (frame->Type == ESPRFRAME_TYPE_RECT_IMG)
						{
							frame->RectImgFrame.ImgID = tok->GetTokenValueAsInt(3);
							frame->RectImgFrame.OffsetX = tok->GetTokenValueAsInt(4);
							frame->RectImgFrame.OffsetY = tok->GetTokenValueAsInt(5);
							frame->RectImgFrame.Width = tok->GetTokenValueAsInt(6);
							frame->RectImgFrame.Height = tok->GetTokenValueAsInt(7);
						}
						else if (frame->Type == ESPRFRAME_TYPE_RECT_COLOR)
						{
							frame->RectColorFrame.Width = tok->GetTokenValueAsInt(3);
							frame->RectColorFrame.Height = tok->GetTokenValueAsInt(4);
							frame->RectColorFrame.Alpha = tok->GetTokenValueAsInt(5);
							frame->RectColorFrame.Red = tok->GetTokenValueAsInt(6);
							frame->RectColorFrame.Green = tok->GetTokenValueAsInt(7);
							frame->RectColorFrame.Blue = tok->GetTokenValueAsInt(8);
						}
						re->m_Frames.AddItem(frame);
					}
					else if (tok->IsTokenEqual(0, "ANIM"))
					{
						SSpriteDBAnimation *a = new SSpriteDBAnimation;
						a->KeyFrameList = new CList<SSpriteDBAnimKeyFrame*>();
						tok->GetToken(1, a->Name);
						anim = a;
					}
					else if (tok->IsTokenEqual(0, "KEYFRAME"))
					{
						if (anim)
						{
							SSpriteDBAnimKeyFrame* kf = new SSpriteDBAnimKeyFrame;
							kf->FrameID = tok->GetTokenValueAsInt(1);
							kf->OffsetX = tok->GetTokenValueAsInt(2);
							kf->OffsetY = tok->GetTokenValueAsInt(3);
							kf->Loop = tok->GetTokenValueAsInt(4);
							anim->KeyFrameList->AddItem(kf);
						}
					}
					else if (tok->IsTokenEqual(0, "ENDANIM"))
					{
						if (anim)
						{
							re->m_Anims.AddItem(anim);
							anim = NULL;
						}
					}
				}
			}
			F.Close();
			return re;
		}
		virtual ~CSpriteDB() 
		{
			m_Anims.BeginTravel();
			while (!m_Anims.IsEndOfTravel())
			{
				SSpriteDBAnimation *anim = m_Anims.Travel();
				anim->KeyFrameList->DeallocateElementPointer();
				anim->KeyFrameList->Clear();
				SAFE_DEL(anim->KeyFrameList);
			}
			m_Anims.DeallocateElementPointer();
			m_Anims.Clear();

			m_Frames.DeallocateElementPointer();
			m_Frames.Clear();

			m_Bitmaps.DeallocateElementPointer();
			m_Bitmaps.Clear();
		}
	protected:
		CSpriteDB(){}
		SSpriteDBHeader m_Header;
		CList<SSpriteDBBitmap*> m_Bitmaps;
		CList<SSpriteDBFrame*> m_Frames;
		CList<SSpriteDBAnimation*> m_Anims;
	};

	class CSpriteDBManagement: public CSingleton<CSpriteDBManagement>, public CResourceLookupTable<CSpriteDB>
	{
		friend class CSingleton<CSpriteDBManagement>;
	protected:
		CSpriteDBManagement(){}
	public:
		template <class IODriver> void AddSpriteDBFromTextFile(const char* name)
		{
			if (!Get(name))
			{
				CReaderStream<IODriver> *F = new CReaderStream<IODriver>(name);
				if (F->GetStatus() == ESTREAM_OPEN)
				{
					CSpriteDB *re = CSpriteDB::ImportFromTextFile<IODriver>(name);
					this->Add(name, re);
				}
				F->Close();
				SAFE_DEL(F);
			}
		}
	};


	class CSprite
	{
	public:
		CSprite(CSpriteDB* spr);
		virtual ~CSprite();
		void SetAnimation(const char* anim, __INT32 loop = 0);
		void ResetAnimation();
		void UpdateAnimation(__UINT32 dt);
		void RenderAnimation(CGraphics2D *g);

		void SetFps(__UINT32 fps) {m_iFps = fps;}
		void SetPosition(SPosition2D<__INT32> pos) {m_Position.X = pos.X; m_Position.Y = pos.Y;}
	protected:
		CSpriteDB* m_SpriteData;
		SSpriteDBAnimation *m_pCurrentAnimation;
		SSpriteDBAnimKeyFrame *m_pCurrentKeyFrame;
		SSpriteDBFrame *m_pCurrentFrame;
		SSpriteDBBitmap *m_pCurrentBitmap;
		__INT32 m_iCurrentFrameNo;
		__UINT32 m_iFps;
		__UINT64 m_iElapsedTime;
		bool m_isEndOfAnimtion;
		SPosition2D<__INT32> m_Position;
		__INT32 m_iLoop;
		__INT32 m_iLoopCounter;
		__INT32 m_iCurrentAnimTotalFrame;
	};
}
#endif