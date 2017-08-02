#pragma once
#include "AStarNode.h"
#include "GridNode.h"
#include "Defines.h"

// Did I put it in the right place, am I doing it right? ASK RICHARD
static int Heuristic(AStarNode* pNode, AStarNode* pEnd)
{
	// Make custom Heuristic for higher then credit mark

	// Manhattan Distance (Melbourne Method)
	/*int difX = ((GridNode*)pNode)->m_nIndexX - ((GridNode*)pEnd)->m_nIndexX;
	int difY = ((GridNode*)pNode)->m_nIndexY - ((GridNode*)pEnd)->m_nIndexY;

	return (abs(difX) + abs(difY)) * 10;*/

	// Digonal Shortcut Method
	int difX = ((GridNode*)pNode)->m_nIndexX - ((GridNode*)pEnd)->m_nIndexX;
	int difY = ((GridNode*)pNode)->m_nIndexY - ((GridNode*)pEnd)->m_nIndexY;

	difX = abs(difX);
	difY = abs(difY);

	if (difX > difY)
	{
		return (DIAGNAL_COST * difY) + ADJACENT_COST * (difX - difY);
	}
	else
	{
		return (DIAGNAL_COST * difX) + ADJACENT_COST * (difY - difX);
	}
}