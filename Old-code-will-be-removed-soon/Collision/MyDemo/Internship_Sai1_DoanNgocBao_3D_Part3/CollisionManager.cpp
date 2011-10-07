#include "CollisionManager.h"

int occurCollision(PositionInfo* pos1, PositionInfo* pos2)
{
	return (pos1->xMin < pos2->xMax && pos1->xMax > pos2->xMin
		&& pos1->yMin < pos2->yMax && pos1->yMax > pos2->yMin
		&& pos1->zMin < pos2->zMax && pos1->zMax > pos2->zMin);
}