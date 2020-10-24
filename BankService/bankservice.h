#pragma once
#include<iostream>
#include<string>
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
public:
	queue(int num);
	~queue();
	void push(const T& elem);
	T pop();
	int getSize();
	bool empty();
	bool full();
};

class bankService
{
private:
	queue<int> odd;
	queue<int> even;
	int size;
public:
	bankService(int number);
	void serve();
	void pop(bool isEven);
};
