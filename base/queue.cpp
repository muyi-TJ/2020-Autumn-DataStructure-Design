#include "queue.h"

template<class T>
queue<T>::queue(int num)
{
	size = num;
	number = 0;
	buffer = new T[size];
	head = 0;
	tail = 0;
}

template<class T>
queue<T>::~queue()
{
	delete[] buffer;
}

template<class T>
void queue<T>::push(const T& elem)
{
	if (full())
	{
		cout << "�����������޷�����" << endl;
		return;
	}
	else
	{
		buffer[tail++] = elem;
		number++;
		if (tail == size)
		{
			tail = 0;
		}
	}
}

template<class T>
T queue<T>::pop()
{
	if (empty())
	{
		cout << "����Ϊ�գ��޷�����" << endl;
		return;
	}
	else
	{
		T temp = buffer[head++];
		number--;
		if (head == size)
		{
			head = 0;
		}
		return temp;
	}
}

template<class T>
bool queue<T>::empty()
{
	return number == 0;
}

template<class T>
bool queue<T>::full()
{
	return number == size;
}

template<class T>
int queue<T>::getSize()
{
	return size;
}