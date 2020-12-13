#include "cutwood.h"
#include <string>
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
int MinHeap<T>::elemNumber()
{
	return number;
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

void getNumber(int& temp)
{
	string checkIn;
	cin >> checkIn;
	if (checkIn.size() > 10)
	{
		temp = -1;
		return;
	}
	for (auto elem : checkIn)
	{
		if (!(elem >= '0'&&elem <= '9'))
		{
			temp = -1;
			return;
		}
	}
	if (atoi(checkIn.c_str()) < INT_MAX)
	{
		temp = stoi(checkIn);
	}
	else
	{
		temp = -1;
	}
}


int main()
{
	int size = -1;
	cout << "请输入需要的木头数量" << endl;
	getNumber(size);
	while (size == -1 || size > 10000)
	{
		cout << "请输入正确的木头数量，为0-10000的正整数" << endl;
		getNumber(size);
	}
	if (size == 0)
	{
		cout << "不需要木头，花费0元" << endl;
		system("pause");
		return 0;
	}
	int* arr = new int[size];
	cout << "请输入每块木头的长度" << endl;
	for (int i = 0; i < size; i++)
	{
		int temp = 0;
		getNumber(temp);
		if (temp <= 0)
		{
			cout << "输入错误，请输入大于0小于INT_MAX的整数" << endl;
			i--;
			continue;
		}
		arr[i] = temp;
	}
	MinHeap<int> heap(arr, size);
	long long ans = 0;
	int a = 0, b = 0;
	while (heap.elemNumber() != 1)
	{
		a = heap.pop();
		b = heap.pop();
		ans += a + b;
		heap.push(a + b);
	}
	cout << "需要" << size << "块木头，花费" << ans << "元" << endl;
	system("pause");
	return 0;
}