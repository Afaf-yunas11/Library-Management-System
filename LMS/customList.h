#pragma once
//#include<iostream>
#include <cassert>
using namespace std;

template <typename T>
class customList {
	T* m_ptrList;
	int m_size;
public:
	customList() {
		m_ptrList = nullptr;
		m_size = 0;
	}
	
	//make a destructor
	~customList(){
		if (m_ptrList != nullptr)
		{
		
			delete[] m_ptrList;
		}
		m_ptrList = nullptr;
	}
	
	void pushByRef(T& obj) {
		T* newList = new T[m_size + 1];

		for (int i = 0; i < m_size; i++) {
			newList[i] = m_ptrList[i];
		}

		newList[m_size] = obj;

		delete[] m_ptrList;
		m_ptrList = newList;
		newList = nullptr;
		m_size = m_size + 1;
	}
	
	
	void push(T obj) {
		T* newList = new T[m_size + 1];

		for (int i = 0; i < m_size; i++) {
			newList[i] = m_ptrList[i];
		}

		newList[m_size] = obj;

		delete[] m_ptrList;
		m_ptrList = newList;
		newList = nullptr;
		m_size = m_size + 1;
	}
	
	//pops the last element
	T pop() {
		T removedObj;

		T* newList = new T[m_size - 1];
		for (int i = 0; i < m_size - 1; i++) {
			newList[i] = m_ptrList[i];
		}

		removedObj = m_ptrList[m_size - 1];
		m_size = m_size - 1;

		delete[] m_ptrList;
		m_ptrList = newList;
		newList = nullptr;

		return removedObj;
	}

	int size() {
		return m_size;
	}

	T& operator [] (int index) {

		assert(index < m_size && index >= 0);
		return m_ptrList[index];
	}
	
	//returns the index of an object in the customList, if object not found then
	//returns -1
	int getIndex(T obj)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (m_ptrList[i] == obj)
			{
				return i;
			}
		}
		
		return -1;
	}
	
	//deletes the element at a certain index and resizes it accordingly
	void remove(int index) {
		//cout<<"in remove function"<<endl;
		T* newList = new T[m_size - 1];
		
		int tempCounter = 0;
		for (int i = 0; i < m_size ; i++) {
			if (i != index) {
				newList[tempCounter] = m_ptrList[i];
				//cout<<"newList[tempCounter]ISBN = "<<newList[tempCounter].GetISBN()<<endl;
				tempCounter = tempCounter + 1;
			}
		}

		delete[] m_ptrList;
		m_ptrList = newList;
		newList = nullptr;
		m_size = m_size - 1;
	}
	
	//clears the entire array
	void clear()
	{
		if (m_ptrList != nullptr)
		{
		
			delete[] m_ptrList;
		}
		m_ptrList = nullptr;
		
		m_size = 0;
	}
};
