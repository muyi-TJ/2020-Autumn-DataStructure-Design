#include "bankservice.h"

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
		cout << "队列已满，无法入列" << endl;
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
		cout << "队列为空，无法出列" << endl;
		return T();
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

bankService::bankService(int number) :odd(number), even(number), size(number)
{
	cout << "请输入排队的序号" << endl;
	int temp = 0;
	string temps;
	bool isNumber = true;
	for (int i = 0; i < number; i++)
	{
		cin >> temps;
		isNumber = true;
		for (auto elem : temps)
		{
			if (!(elem >= '0'&&elem <= '9'))
			{
				cout << "请输入正整数" << endl;
				i--;
				isNumber = false;
				break;
			}
		}
		if (!isNumber)
		{
			continue;
		}
		if (atoi(temps.c_str()) < INT_MAX)
		{
			temp = stoi(temps);
		}
		else
		{
			i--;
			cout << "请输入小于INT_MAX的整数" << endl;
			continue;
		}
		if (temp % 2 == 1)
		{
			odd.push(temp);
		}
		else
		{
			even.push(temp);
		}
	}
	cout << "输入完毕" << endl;
}

void bankService::serve()
{
	cout << "服务完毕的顺序为:" << endl;
	while (!odd.empty() || !even.empty())
	{
		pop(false);
		pop(false);
		pop(true);
	}
}

void bankService::pop(bool isEven)
{
	if (isEven)
	{
		if (!even.empty())
		{
			cout << even.pop();
			size--;
		}
		else
		{
			return;
		}
	}
	else
	{
		if (!odd.empty())
		{
			cout << odd.pop();
			size--;
		}
		else
		{
			return;
		}
	}
	if (size > 0)
	{
		cout << ' ';
	}
}

int main()
{
	cout << "请输入排队人数" << endl;
	int number = 0;
	cin >> number;
	if (number <= 0)
	{
		cout << "请输入合法的人数，使用服务失败" << endl;
		system("pause");
		return 0;
	}
	bankService bank(number);
	bank.serve();
	system("pause");
	return 0;
}