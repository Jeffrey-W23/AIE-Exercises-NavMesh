#pragma once
#include "DynamicArray.h"
#include "AStarNode.h"
#include <math.h>

// Isnt a template yet, change T to what ever it is gonna be used for.
//template <typename T>
class Heap
{
public:
	void Push(AStarNode* data)
	{
		// Add data to end of array.
		m_Data.PushBack(data);

		// Loop through and swap data with parent if data is smaller.
		int current = m_Data.Size() - 1;
		
		while (true)
		{
			if (current == 0)
				break;

			int parent = GetParentIndex(current);

				if (m_Data[current]->m_nFScore < m_Data[parent]->m_nFScore)
				{
					AStarNode* swap = m_Data[current];
					m_Data[current] = m_Data[parent];
					m_Data[parent] = swap;

					current = parent;
				}

				else
					break;
		}	
	}

	AStarNode* Pop()
	{
		AStarNode* result = m_Data[0];

		// Replace first element with last element.
		int last = m_Data.Size() - 1;
		m_Data[0] = m_Data[last];

		// Swap first element with smaller child if child is smaller.
		int current = 0;
		
		while (true)
		{
			int child0 = GetChildIndex(current, 1);

			if (child0 > last)
				break;

			int child1 = GetChildIndex(current, 2);
			int smallerChild = child0;

			if (child1 <= last && m_Data[child1]->m_nFScore < m_Data[smallerChild]->m_nFScore)
				smallerChild = child1;

			// Check if smaller than parent, if so swap.
			if (m_Data[smallerChild]->m_nFScore < m_Data[current]->m_nFScore)
			{
				AStarNode* swap = m_Data[current];
				m_Data[current] = m_Data[smallerChild];
				m_Data[smallerChild] = swap;

				current = smallerChild;
			}
			else
				break;
		}

		m_Data.PopBack();
		return result;
	}

	void Clear()
	{
		m_Data.Clear();
	}

	int GetSize() 
	{
		return (int)m_Data.Size();
	}

	int GetParentIndex(int child)
	{
		return (child - 1) / 2;
	}

	int GetChildIndex(int parent, int whichChild)
	{
		return (2 * parent) + whichChild;
	}

	int Contains(AStarNode* pData)
	{
		for (int i = 0; i < m_Data.Size(); ++i)
		{
			if (m_Data[i] == pData)
				return i;
		}

		return -1;
	}

	void Resort(int index)
	{
		if (index == 0)
			return;

		int nNodeIndex = index;
		int nParent = GetParentIndex(index);

		//Check if node has a lower F value than parent, if so then swap.
		while (nParent >= 0 && m_Data[nNodeIndex]->m_nFScore < m_Data[nParent]->m_nFScore)
		{
			//Swap
			AStarNode* temp = m_Data[nParent];
			m_Data[nParent] = m_Data[nNodeIndex];
			m_Data[nNodeIndex] = temp;

			nNodeIndex = nParent;
			nParent = GetParentIndex(nNodeIndex);
		}
	}

private:
	DynamicArray<AStarNode*> m_Data;

};