// #include, using, etc
#pragma once
#include <memory.h>

//--------------------------------------------------------------------------------------
// DynamicArray Templated object.
//--------------------------------------------------------------------------------------
template<typename T>
class DynamicArray
{
public:

	//--------------------------------------------------------------------------------------
	// Constructor taking in an Int.
	//
	// Param:
	//		initialSize: the starting size of the array.
	//--------------------------------------------------------------------------------------
	DynamicArray(int initialSize = 0)
	{
		int nCapacity = initialSize;

		if (nCapacity <= 0)
			nCapacity = 1;

		m_pData = new T[nCapacity];
		m_nCapacity = nCapacity;
		m_nUsed = 0;

		memset(&m_NullValue, 0, sizeof(T));
	}

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~DynamicArray()
	{
		delete m_pData;
	}

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	DynamicArray(const DynamicArray& other)
	{
		m_nCapacity = other.m_nCapacity;
		m_nUsed = other.m_nUsed;

		m_pData = new T[other.m_nCapacity];
		memcpy(m_pData, other.m_pData, sizeof(T) * other.m_nCapacity);
	}

	//--------------------------------------------------------------------------------------
	// PushBack: Push a value onto the back
	//
	// Param:
	//		value: the value you are pushing on.
	//--------------------------------------------------------------------------------------
	void PushBack(T value)
	{
		if (m_nUsed >= m_nCapacity)
			Resize();

		m_pData[m_nUsed] = value;
		++m_nUsed;
	}

	//--------------------------------------------------------------------------------------
	// PushFront: Push a value onto the front
	//
	// Param:
	//		value: the value you are pushing on.
	//--------------------------------------------------------------------------------------
	void PushFront(T value)
	{
		Insert(0, value);
	}

	//--------------------------------------------------------------------------------------
	// Insert: Insert a value at an index.
	//
	// Param:
	//		index: where you want to place the value.
	//		value: the value you want to place in the array.
	//--------------------------------------------------------------------------------------
	void Insert(int index, T value)
	{
		if (m_nUsed >= m_nCapacity)
			Resize();

		for (int i = m_nUsed - 1; i >= index; --i)
		{
			m_pData[i + 1] = m_pData[i];
		}

		m_pData[index] = value;
		++m_nUsed;
	}

	//--------------------------------------------------------------------------------------
	// PopBack: Pop a value off the array.
	//
	// Return:
	//		T: returns T
	//--------------------------------------------------------------------------------------
	T PopBack()
	{
		--m_nUsed;
		return m_pData[m_nUsed];
	}

	//--------------------------------------------------------------------------------------
	// Remove: Remove a value from an index.
	//
	// Param:
	//		index: where to remove the value from
	//
	// Return:
	//		T: return T.
	//--------------------------------------------------------------------------------------
	T Remove(int index)
	{
		// Backup value that we are removing from array
		T value = m_pData[index];

		// Shuffle all other values across to fill removed space
		for (int i = index; i < m_nUsed; ++i)
		{
			m_pData[i] = m_pData[i + 1];
		}

		--m_nUsed;

		// return removed value
		return value;
	}

	//--------------------------------------------------------------------------------------
	// PopFront: Pop a value off the front.
	//
	// Return:
	//		T: Returns T
	//--------------------------------------------------------------------------------------
	T PopFront()
	{
		return Remove(0);
	}

	//--------------------------------------------------------------------------------------
	// Clear: clear the array.
	//--------------------------------------------------------------------------------------
	void Clear()
	{
		m_nUsed = 0;
	}

	//--------------------------------------------------------------------------------------
	// Shrink: Shirk the array.
	//
	// return:
	//		T: returns T
	//--------------------------------------------------------------------------------------
	T Shrink()
	{
		int nCapacity = m_nUsed;

		if (nCapacity <= 0)
			nCapacity = 1;

		T* newData = new T[nCapacity];
		memcpy(newData, m_pData, sizeof(T) * nCapacity);
		delete m_pData;
		m_pData = newData;
		m_nCapacity = nCapacity;
	}

	//--------------------------------------------------------------------------------------
	// Sub-script operator returning a reference
	//
	// Param:
	//		index: takes in an int.
	//
	// Return:
	//		T: Returns a type T
	//--------------------------------------------------------------------------------------
	T& operator[](const int index)
	{
		return m_pData[index];
	}

	//--------------------------------------------------------------------------------------
	// Size: Return the size of the array.
	//
	// Return:
	//		int: returns an int of the array size.
	//--------------------------------------------------------------------------------------
	int Size()
	{
		return m_nUsed;
	}

	//--------------------------------------------------------------------------------------
	// Capacity: returns the capacity of the array.
	//
	// Return:
	//		int: returns an int of the array capacity.
	//--------------------------------------------------------------------------------------
	int Capacity()
	{
		return m_nCapacity;
	}

private:

	//--------------------------------------------------------------------------------------
	// Copy constructor etc
	//--------------------------------------------------------------------------------------
	DynamicArray& operator= (const DynamicArray& other) = default;
	DynamicArray(DynamicArray&& other) = default;
	DynamicArray& operator= (DynamicArray&& other) = default;

	//--------------------------------------------------------------------------------------
	// Resize: Resize the array.
	//--------------------------------------------------------------------------------------
	void Resize()
	{
		// Creates new array that is twice as big
		T* newData = new T[m_nCapacity * 2];

		// Copy old data across into new array
		memcpy(newData, m_pData, sizeof(T) * m_nCapacity);

		// delete old array
		delete m_pData;

		// Make sure our pointers still work
		m_pData = newData;

		// Increase capacity
		m_nCapacity = m_nCapacity * 2;
	}

	//--------------------------------------------------------------------------------------
	// a T pointer m_pData.
	//--------------------------------------------------------------------------------------
	T* m_pData;

	//--------------------------------------------------------------------------------------
	// An int m_nCapacity
	//--------------------------------------------------------------------------------------
	int m_nCapacity;

	//--------------------------------------------------------------------------------------
	// An int m_nUsed
	//--------------------------------------------------------------------------------------
	int m_nUsed;

	//--------------------------------------------------------------------------------------
	// a T m_NullValue
	//--------------------------------------------------------------------------------------
	T m_NullValue;
};