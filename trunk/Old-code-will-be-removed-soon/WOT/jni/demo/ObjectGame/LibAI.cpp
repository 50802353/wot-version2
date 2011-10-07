

#include "LibAI.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AStar::AStar()
{

}

AStar::~AStar()
{

}

void AStar::setMap(__INT32* map)
{
	m_matrix = map;
}

__INT32* AStar::getMap()
{
	return m_matrix;
}

__INT32 AStar::getWidth()
{
	return N_WIDTH;
}
__INT32 AStar::getHeight()
{
	return N_HEIGHT;
}

AStar::AStar(int width, int height, int* matrix)
{
	N_WIDTH = width;
	N_HEIGHT = height; 
	m_matrix = matrix;
}

bool AStar::getNextCell(const cell &current,const int &index,cell &next)
{
	/* index c?a � ti?p theo � X
		1	2	3
		0	x	4
		7	6	5
	*/
	if(index <0 || index > 7)
		return false;

	int iNext[] ={0,-1,-1,-1,0,1,1,1};
	int jNext[] = {-1,-1,0,1,1,1,0,-1};
	int i = current.i + iNext[index];
	int j = current.j + jNext[index];
	if( i < 0 || i>= N_WIDTH || j< 0 || j >= N_HEIGHT)
		return false;
	if( m_matrix[i + j*N_WIDTH] <= KET_THUC) 
	{
		if (iNext[index] * jNext[index] != 0)
			if (m_matrix[current.i + j*N_WIDTH] > KET_THUC || m_matrix[i+current.j*N_WIDTH] > KET_THUC)
				return false;
		next = cell(i,j);
		return true;
	}
	return false;
}

cell AStar::takeMinCost(deque<cell> &dMatrix)
{	
	
	bool isCostPority = true;
	if(isCostPority)
	{
		// uu ti�n v? gi� tr? Tr? l?i cell c� fValue nh? nh?t, n?u c� nhi?u fValue tr�ng nhau, th� l?y theo hValue
		int min = 0;
		int fMin = m_State[dMatrix[min]].gValue + getHeuristic(dMatrix[min]);

		for(int i =1;i < dMatrix.size();++i)
		{
			int fI = m_State[dMatrix[i]].gValue + getHeuristic(dMatrix[i]);
			if( fI < fMin)
			{
				fMin = fI;
				min = i;
			}
			if( fI == fMin && (getHeuristic(dMatrix[i]) < getHeuristic(dMatrix[min])))
			{
				fMin = fI;
				min = i;
			
			}
		}
		cell result = dMatrix[min];
		dMatrix.erase(dMatrix.begin() + min);
		return result;
	}
	else
	{
		// uu ti�n v? th?i gian 
		// Tr? l?i cell c� th?i gian ( hay chi ph� u?c lu?ng ) d? d?n d�ch l� nh? nh?t
		int min = 0;
		int hMin = getHeuristic(dMatrix[min]);

		for(int i =1;i < dMatrix.size();++i)
		{
			int hI = getHeuristic(dMatrix[i]);
			if( hI < hMin)
			{
				hMin = hI;
				min = i;
			}
			if( hI == hMin && (m_State[dMatrix[i]].gValue < m_State[dMatrix[min]].gValue))
			{
				hMin = hI;
				min = i;
			
			}
		}
		cell result = dMatrix[min];
		dMatrix.erase(dMatrix.begin() + min);
		return result;
	}
	
}
//============ T�nh chi ph� d? di t? i,j d?n iNext,jNext, 2 � n�y l� k? nhau ngang, ho?c ch�o
int AStar::getCost(const int &index) const
{
	/* index c?a � ti?p theo � X
		1	2	3
		0	x	4
		7	6	5
	*/

	if(index < 0 || index > 7)
		return -1 ;
	int cost[]={10,14,10,14,10,14,10,14};
	return cost[index];
}
//============= T�nh chi ph� u?c lu?ng d? di t? i,j d?n iEnd,jEnd
int AStar::getHeuristic(const cell &a) const
{
	// chi ph� u?c lu?ng t�nh theo kho?ng c�ch Mahatan: h(xi,yi,xe,ye) = |xi-xe| + |yi-ye|
	// Ho?c sqrt(sqr(xi-xe) + sqr(yi - ye))
	int xDistance = iEnd - a.i;
	int yDistance = jEnd - a.j;
	//abs(xDistance);
	//abs(yDistance);
	xDistance > 0 ? 0:xDistance = -xDistance;
	yDistance > 0 ? 0:yDistance = -yDistance;
	return (xDistance + yDistance)*10;
}

bool AStar::pathFinder(bool isStep, CList<cell> *lst, int Starti, int Startj, int Endi, int Endj)
{
	iStart = Starti;
	jStart = Startj;
	iEnd = Endi;
	jEnd = Endj;
	// ================Chuy?n qua bi?u tu?ng buzy c?a con tr?
	//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
		
	//================ C�c d? li?u s? d?ng cho A*
	// Luu tr? c�c � dang du?c x�t c?a matrix
	deque<cell> dMatrix;
	// X�a map;
	m_State.clear();
	// Kh?i t?o l?i matrix tr? c�c chu?ng ng?i v?t n?u matrix d� b? s? d?ng
	// kh?i d?ng l?i c�c gi� tr? ban d?u + v?t c?n:
	OnFileErase();

	// Ghi d?u � b?t d?u t�m ki?m v� � k?t th�c
	cell begin = cell(iStart,jStart);
	cell end = cell(iEnd,jEnd);
	// Th?i gian delay gi?a m?i bu?c
	int nTime = 0;
	if(isStep)
		nTime = 500;
	

	dMatrix.push_back(begin);
	m_State[begin] = status(begin,ENTERING,0,cell());
	
		
	// B?t d?u t�m t?t c? c�c � c� th? di trong deque
	while(dMatrix.empty() == false)
	{
		
		// L?y v� x�a � c� gi� tr? u?c lu?ng min
		cell currentCell = takeMinCost(dMatrix);
		// Luu tr? tr?ng th�i � trong ma tr?n
		m_matrix[currentCell.i + currentCell.j * N_WIDTH ] = ENTERED;
		// Hi?n th? cho ngu?i d�ng tr?ng th�i � ?
//		notify2User(currentCell,nTime);
		
		// Duy?t qua c�c � k? c� th? di d?n:
		for(int i = 0;i< 8 ; ++i)
		{
			cell nextCell;
			if ( getNextCell(currentCell,i,nextCell))
			{
				// t�nh to�n c�c chi ph� d? di d?n nextCell th�ng qua currentCell
				int gValue = m_State[currentCell].gValue + getCost(i);
				// Ki?m tra t�nh tr?ng � n�y :
				// N?u cell n�y chua c� trong map -> dua v�o.
				if(m_State.find(nextCell) == m_State.end())
				///if(m_State.find(nextCell) == --m_State.end())
				{
					// dua tr?ng th�i c?a cell m?i v�o map
					m_State[nextCell] = status(nextCell,ENTERING,gValue,currentCell);
					// dua cel m?i v�o deque d?i duy?t
					dMatrix.push_back(nextCell);
					// Luu tr? tr?ng th�i � trong ma tr?n
					m_matrix[nextCell.i + nextCell.j * N_WIDTH] = ENTERING;
					// hi?n th? cho ngu?i d�ng tr?ng th�i c?a �
					//notify2User(nextCell,0);
				}
				else
				{
					// Cell n�y d� t?n t?i, c?n ki?m tra xem d� t?i uu hay chua ?
					if(m_State[nextCell].gValue > gValue)
					{
						// c?p nh?t l?i
						m_State[nextCell].gValue = gValue;
						m_State[nextCell].prev = currentCell;
						// N?u d� x�t, th� x�t l?i d? lan truy?n d?n c�c d?nh con
						if(m_State[nextCell].isEnter == ENTERED)
						{
							m_State[nextCell].isEnter = ENTERING;
							dMatrix.push_back(nextCell);
							// hi?n th? cho ngu?i d�ng bi?t tr?ng th�i �
							// Luu tr? tr?ng th�i � trong ma tr?n
							m_matrix[nextCell.i  + nextCell.j* N_WIDTH] = ENTERING;
							//notify2User(nextCell,0);

						}
	
					}
				}
				
				// Ki?m tra xem cell hi?n t?i c� ph?i cell cu?i ko ?
				if(nextCell == end)
				{
					setPath(true, lst);
					//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
					this->Restore();
					return true;
				}
				
			}// end if
		}// end for
		
	}// end while
	
	// ================Tr? l?i con tr? th?ong
	//SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	this->Restore();
	return false;
}


void AStar::setPath(bool isSet, CList<cell> *lst)
{
 
	cell current = cell(iEnd,jEnd);
	cell start = cell(iStart,jStart);
	int value = EMPTY;
	if(isSet)
		value = PATH;

	m_matrix[current.i  + current.j* N_WIDTH] = KET_THUC;
	lst->AddItem(current);
	while(current != start)
	{
		current = m_State[current].prev;
		// set value cho current
		m_matrix[current.i + current.j * N_WIDTH] = value;

		lst->AddItem(current);
	}
	m_matrix[current.i + current.j * N_WIDTH] = BAT_DAU;

}

void AStar::OnFileErase()
{
	// TODO: Add your command handler code here
	// kh?i d?ng l?i c�c gi� tr? ban d?u + v?t c?n:
		for(int i=0;i<N_WIDTH;++i)
		{
			for(int j=0;j<N_HEIGHT;++j)
				if(m_matrix[i + j*N_WIDTH] < 0)
					m_matrix[i + j*N_WIDTH] = EMPTY;
		}
		// T?o l?i begin -	end
		backupStart = m_matrix[iStart + jStart*N_WIDTH];
		m_matrix[iStart + jStart*N_WIDTH] = BAT_DAU;
		backupEnd = m_matrix[iEnd + jEnd*N_WIDTH];
		m_matrix[iEnd + jEnd*N_WIDTH] = KET_THUC;
}

void AStar::Restore() {
	for (int i=0;i<N_WIDTH*N_HEIGHT;i++)
		if (m_matrix[i] < 0)
			m_matrix[i] = 0;

	m_matrix[iStart + jStart*N_WIDTH] = backupStart;
	m_matrix[iEnd + jEnd*N_WIDTH] = backupEnd;
}
