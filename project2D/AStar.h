#pragma once
#include "AStarNode.h"
#include "Heap.h"

// Return/Type/Input
typedef int(*CalcHeuristic)(AStarNode*, AStarNode*);

class AStar
{
public:
	AStar(int nMaxNodes);
	~AStar();
	bool CalculatePath(AStarNode* pStart, AStarNode* pEnd, DynamicArray<AStarNode*>* finishedPath);
	
	// Pointer Function
	int Callfunction(AStarNode* pStart, AStarNode* pEnd);
	void SetFunction(CalcHeuristic func);

private:
	Heap m_OpenList;
	bool* m_ClosedList;
	int m_MaxNode;
	CalcHeuristic fn_CalcHeuristic = nullptr;
};