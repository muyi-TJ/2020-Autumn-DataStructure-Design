#pragma once
#include <iostream>
using namespace std;

template<class T>
class MinHeap
{
public:
	MinHeap(int maxSize);
	MinHeap(T arr[], int num);
	~MinHeap();
	void push(const T& elem);
	T pop();
	bool isEmpty();
	bool isFull();
	int elemNumber();
private:
	int size;
	int number;
	T* buffer;
	void down(int start, int end);
	void up(int start);
};

