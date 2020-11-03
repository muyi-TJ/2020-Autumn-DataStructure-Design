#include "priority_queue.h"

template<class T>
MinHeap<T>::MinHeap(int maxSize)
{
	size = maxSize;
	number = 0;
	buffer = new T[size];
}

template<class T>
MinHeap<T>::MinHeap(T arr[], int num)
{
	size = (num + 3)*1.25;
	number = num;
	buffer = new T[size];
	memcpy(buffer, arr, sizeof(T) * num);
	int now = (num - 2) / 2;
	while (now >= 0)
	{
		down(now--, num - 1);
	}
}

template<class T>
MinHeap<T>::~MinHeap()
{
	delete[] buffer;
}

template<class T>
void MinHeap<T>::push(const T & elem)
{
	if (isFull())
	{
		cout << "堆已满，无法添加新元素" << endl;
	}
	else
	{
		buffer[number] = elem;
		up(number);
		number++;
	}
}

template<class T>
T MinHeap<T>::pop()
{
	if (isEmpty())
	{
		cout << "堆为空，无法出堆" << endl;
		return T();
	}
	else
	{
		T temp = buffer[0];
		buffer[0] = buffer[number - 1];
		number--;
		down(0, number - 1);
		return temp;
	}
}


template<class T>
bool MinHeap<T>::isEmpty()
{
	return number == 0;
}

template<class T>
bool MinHeap<T>::isFull()
{
	return number == size;
}

template<class T>
void MinHeap<T>::down(int start, int end)
{
	int parent = start, child = 2 * parent + 1;
	T first = buffer[start];
	while (child <= end)
	{
		if (child < end && buffer[child] > buffer[child + 1])
		{
			child++;
		}
		if (first < buffer[child])
		{
			break;
		}
		else
		{
			buffer[parent] = buffer[child];
			parent = child;
			child = parent * 2 + 1;
		}
	}
	buffer[parent] = first;
}

template<class T>
void MinHeap<T>::up(int start)
{
	int child = start, parent = (child - 1) / 2;
	T last = buffer[start];
	while (child != parent)
	{
		if (last > buffer[parent])
		{
			break;
		}
		else
		{
			buffer[child] = buffer[parent];
			child = parent;
			parent = (child - 1) / 2;
		}
	}
	buffer[child] = last;
}
