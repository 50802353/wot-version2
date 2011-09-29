#ifndef __CINFOPANEL_H__
#define __CINFOPANEL_H__


#define BACKGROUND PATH_GRAPHIC("Blue_ground.tga")
#define PANELFONT PATH_GRAPHIC("font_GillSanUltraBold2.tga")


#include "gametutor.h"

using namespace GameTutor;

class CInfoPanel
{
public:
	CInfoPanel();
	CInfoPanel(int posX, int posY, char* text, int row, int column);
	void Draw();
private:
	int X;
	int Y;
	char Text[200];
	int Row;
	int Col;
	int maxlength;
	CImage* background;
	CImage* font;
};


#endif