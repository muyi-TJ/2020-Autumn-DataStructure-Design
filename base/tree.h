#pragma once
#include <iostream>
using namespace std;

template<class T>
class Tree
{
private:
	class Node
	{
	public:
		T value = 0;
		int childnum = 0;
		T* children;
		Node(T val)
		{
			value = val;
		}
		void setChildren(int size)
		{
			childnum = size;
			children = new T[size];
		}
		void addChildren(T newChild)
		{
			childnum++;
			T* temp = children;
			children = new T[childnum];
			memcpy(children, temp, childnum - 1);
			children[childnum - 1] = newChild;
			delete[] temp;
		}
	};
	T* root;
	void deleteNode();
public:
	Tree();
	void postOrder(Node* node, void(*func)(T));
	void postOrder(Node* node, void(*func)());
	void insert(T parent, T value);
	void removeChild(T parent);
	Node* find(T value);
	

};