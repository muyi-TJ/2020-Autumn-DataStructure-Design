#pragma once
#include<iostream>
using namespace std;

template<class T>
class queue
{
private:
	int size;
	int number;
	T* buffer;
	int head;
	int tail;
	~queue();
public:
	queue(int num);
	void push(const T& elem);
	T pop();
	int getSize();
	bool empty();
	bool full();
};