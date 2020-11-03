#include<iostream>
using namespace std;

template <class T>
class stack
{
public:
	stack(int size);
	stack(const stack<T>& source);
	~stack();
	bool isEmpty();
	bool isFull();
	int stacklength();
	bool push(T elem);
	void expand();
	T pop();
	T peek();
private:
	T* m_buffer;
	int m_size;
	int m_element;
};