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

#define ENTERED  -6		// Ðã di qua ô này
#define ENTERING  -7		// Chua, nhung dang n?m trong t?p c?n xét

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
	int isEnter ;				// tình tr?ng ô hi?n t?i ( ENTERED ho?c ENTERING ) 
	int gValue;					// Chi phí t?i uu d? di t? b?t d?u d?n ô này
	cell prev;				// Là ô tru?c khi di qua 
	cell key;					// Khóa c?a ô là ch? s? i,j trong ma tr?n
	// Các hàm t?o ph?c v? cho vi?c luu tr?, tìm du?ng
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

	// nh?n v? ô th? index có th? di t? ô hi?n t?i:
	bool getNextCell(const cell &current,const int &index,cell &next); 
	// tính chi phí d? di t? cell a(i,j) d?n cell b(iNext,jNext) 2 ô này là k? nhau ngang, ho?c chéo
	int getCost(const int &index) const;
	// tính chi phí u?c lu?ng d? di t? cell a(i,j) d?n cell end (iEnd,jEnd)
	int getHeuristic(const cell &a)const;
	// L?y chi phí u?c lu?ng nh? nh?t d? di t? start - end thông qua các d?nh dang xét
	cell takeMinCost(deque<cell> &dMatrix);
	
	// Tìm du?ng di ng?n nh?t t? iStart,jStart, d?n iEnd,jEnd theo gi?i thu?t A*
	bool pathFinder(bool isStep,GameTutor::CList<cell> *lst, int Starti, int Startj, int Endi, int Endj);
	void setPath(bool isSet, GameTutor::CList<cell> *lst);
	void OnFileErase();
	void Restore();
	void setMap(__INT32* map);
	__INT32* getMap();
	__INT32 getWidth();
	__INT32 getHeight();
private:
	// ma tr?n  ô vuông
	int *m_matrix;
	int N_HEIGHT;
	int N_WIDTH;
	// T?a d? ô b?t d?u, k?t thúc trong ma tr?n
	int iStart,jStart;
	int iEnd, jEnd;
	int backupStart, backupEnd;
	// Map luu tr? các tr?ng thái trong quá trình tìm ki?m 
	map<cell,status> m_State;
};


#endif