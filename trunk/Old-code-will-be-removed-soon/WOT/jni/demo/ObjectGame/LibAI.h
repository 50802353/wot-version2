#ifndef _LIB_AI_H
#define _LIB_AI_H

#include "stdio.h"
#include "iostream"
#include <functional>
#include <algorithm>
#include <deque>
#include <map>

#include "CList.h"
using namespace GameTutor;

using namespace std;

#define PATH -1
#define EMPTY 0
#define BAT_DAU 1
#define KET_THUC 2

#define ENTERED  -6		// �� di qua � n�y
#define ENTERING  -7		// Chua, nhung dang n?m trong t?p c?n x�t

struct cell
{
	int i; int j;
	cell(int _i = -1,int _j = -1)
	{
		i = _i; j = _j;
	}
	bool operator < (const cell &b)const
	{
		if( i < b.i) return true;
		if(i == b.i && j < b.j) return true;
		return false;
	}
	cell operator = (cell b)
	{
		this->i = b.i;
		this->j = b.j;
		return (*this);
	}
	bool operator == (cell &b)
	{
		if( this->i == b.i && this->j == b.j)
			return true;
		return false;
	}
	bool operator!=(cell &b)
	{
		if( this->i != b.i || this->j != b.j)
			return true;
		return false;
	}
};
struct status
{
	int isEnter ;				// t�nh tr?ng � hi?n t?i ( ENTERED ho?c ENTERING ) 
	int gValue;					// Chi ph� t?i uu d? di t? b?t d?u d?n � n�y
	cell prev;				// L� � tru?c khi di qua 
	cell key;					// Kh�a c?a � l� ch? s? i,j trong ma tr?n
	// C�c h�m t?o ph?c v? cho vi?c luu tr?, t�m du?ng
	status(cell _key = cell(-1,-1),int _isEnter = -1 ,int _gValue =  -1 ,cell _prev = cell(-1,-1))
		: key(_key),isEnter(_isEnter),gValue(_gValue),prev(_prev)
	{}
};



class AStar  
{
public:
	AStar();
	AStar(int width, int height, int* matrix);
	virtual ~AStar();

	// nh?n v? � th? index c� th? di t? � hi?n t?i:
	bool getNextCell(const cell &current,const int &index,cell &next); 
	// t�nh chi ph� d? di t? cell a(i,j) d?n cell b(iNext,jNext) 2 � n�y l� k? nhau ngang, ho?c ch�o
	int getCost(const int &index) const;
	// t�nh chi ph� u?c lu?ng d? di t? cell a(i,j) d?n cell end (iEnd,jEnd)
	int getHeuristic(const cell &a)const;
	// L?y chi ph� u?c lu?ng nh? nh?t d? di t? start - end th�ng qua c�c d?nh dang x�t
	cell takeMinCost(deque<cell> &dMatrix);
	
	// T�m du?ng di ng?n nh?t t? iStart,jStart, d?n iEnd,jEnd theo gi?i thu?t A*
	bool pathFinder(bool isStep,GameTutor::CList<cell> *lst, int Starti, int Startj, int Endi, int Endj);
	void setPath(bool isSet, GameTutor::CList<cell> *lst);
	void OnFileErase();
	void Restore();
	void setMap(__INT32* map);
	__INT32* getMap();
	__INT32 getWidth();
	__INT32 getHeight();
private:
	// ma tr?n  � vu�ng
	int *m_matrix;
	int N_HEIGHT;
	int N_WIDTH;
	// T?a d? � b?t d?u, k?t th�c trong ma tr?n
	int iStart,jStart;
	int iEnd, jEnd;
	int backupStart, backupEnd;
	// Map luu tr? c�c tr?ng th�i trong qu� tr�nh t�m ki?m 
	map<cell,status> m_State;
};


#endif