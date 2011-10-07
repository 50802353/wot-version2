#include "CInfoPanel.h"




CInfoPanel::CInfoPanel(int posX, int posY, char* text, int row, int column)
{
	X = posX;
	Y = posY;
	strcpy(Text,text);
	Row = row;
	Col = column;

	maxlength = 0;
	
	char temptext[200];
	strcpy(temptext,Text);
	char* s = strtok(temptext,"|");;
	for (int i=0;i<Row;i++)
	{
		for (int j=0;j<Col;j++)
		{
			
			int len;
			if ((len = strlen(s))>maxlength)
				maxlength = len;

			s = strtok(NULL,"|");
		}
	}
	if (!CImageManager::GetInstance()->Get(BACKGROUND))
		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(BACKGROUND,true);
	background = CImageManager::GetInstance()->Get(BACKGROUND);
	if (!CImageManager::GetInstance()->Get(PANELFONT))
		CImageManager::GetInstance()->AddImage<CFileWin32Driver>(PANELFONT,true);
	font = CImageManager::GetInstance()->Get(PANELFONT);
}

void CInfoPanel::Draw()
{
	__INT32 size = 20;
	
	CGraphics2D::GetInstance()->DrawImageRegion(SRect<__INT32>(X,Y,maxlength*Col*size,Row*size+20), background, SRect<__INT32>(0,0,background->GetWidth(),background->GetHeight()));
	char temptext[200];
	strcpy(temptext,Text);
	char* s = strtok(temptext,"|");;
	for (int i =0; i<Row; i++)
	{
		for (int j = 0; j<Col; j++)
		{
			
			CGraphics2D::GetInstance()->DrawString(font,s,X+30+j*size*maxlength,Y-5+(Row-i)*size+size,h_left|v_top,0.06,0.9);
			s = strtok(NULL,"|");
		}
	}
	CGraphics2D::GetInstance()->Flush();

}