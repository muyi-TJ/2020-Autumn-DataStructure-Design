#include "electricity.h"

template<class v>
unordered_map<v>::unordered_map(int size)
{
	hashSize = size;
	hashnode = new Node[hashSize];
}

template<class v>
unordered_map<v>::~unordered_map()
{
	delete[] hashnode;
}

template<class v>
typename unordered_map<v>::Node* unordered_map<v>::find(string key)
{
	int index = hash(key);
	Node* temp = hashnode + index;
	while (temp)
	{
		if (temp->key == key)
		{
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}


template<class v>
int unordered_map<v>::hash(string key)
{
	int hashvalue = 0;
	for (auto elem : key)
	{
		hashvalue += (hashvalue << 5) + elem;
	}
	return abs(hashvalue % hashSize);
}

template<class v>
v& unordered_map<v>:: operator [] (string key)
{
	Node*temp = find(key);
	if (temp)
	{
		return temp->value;
	}
	else
	{
		temp = hashnode + hash(key);
		temp->next = new Node(key, v());
		return temp->next->value;
	}
}

unordered_set::unordered_set(int size)
{
	hashSize = size;
	hashnode = new Node[hashSize];
}

unordered_set::~unordered_set()
{
	delete[] hashnode;
}

void unordered_set::insert(string value)
{
	Node* temp = find(value);
	if (temp)
	{
		temp->value = value;
	}
	else
	{
		int index = hash(value);
		temp = hashnode + index;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new Node(value);
	}
}

unordered_set::Node* unordered_set::find(string value)
{
	int index = hash(value);
	Node* temp = hashnode + index;
	while (temp)
	{
		if (temp->value == value)
		{
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}

int unordered_set::hash(string value)
{
	int hashvalue = 0;
	for (auto elem : value)
	{
		hashvalue += (hashvalue << 5) + elem;
	}
	return abs(hashvalue % hashSize);
}


template<class T>
UnionFindSet<T>::UnionFindSet(int size, T* elements) :buffer(size)
{
	num = size;
	for (int i = 0; i < size; i++)
	{
		buffer[elements[i]] = VW(elements[i], 1);
	}
}

template<class T>
void UnionFindSet<T>::unionElement(T a, T b)
{
	T r1 = find(a), r2 = find(b);
	int temp;
	if (r1 != r2)
	{
		temp = buffer[r1].weight + buffer[r2].weight;
	}
	else
	{
		return;
	}
	if (buffer[r1].weight < buffer[r2].weight)
	{
		buffer[r1].value = r2;
		buffer[r2].weight = temp;
	}
	else
	{
		buffer[r2].value = r1;
		buffer[r1].weight = temp;
	}
}

template<class T>
T UnionFindSet<T>::find(T a)
{
	while (a != buffer[a].value)
	{
		a = buffer[a].value;
	}
	return a;
}

template<class T>
bool UnionFindSet<T>::isUnioned(T a, T b)
{
	return find(a) == find(b);
}

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
	for (int i = 0; i < num; i++)
	{
		buffer[i] = arr[i];
	}
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
		if (child < end && buffer[child + 1] < buffer[child])
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
		if (buffer[parent] < last)
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

Edge::Edge(string a, string b, int number)
{
	name1 = a;
	name2 = b;
	cost = number;
}

bool Edge::operator<(const Edge &right)
{
	return this->cost<right.cost;
}

void electricity::getNumber(int& temp)
{
	string checkIn;
	cin >> checkIn;
	if (checkIn.size() > 10)
	{
		temp = 0;
		return;
	}
	for (auto elem : checkIn)
	{
		if (!(elem >= '0'&&elem <= '9'))
		{
			temp = 0;
			return;
		}
	}
	if (atoi(checkIn.c_str()) < INT_MAX)
	{
		temp = stoi(checkIn);
	}
	else
	{
		temp = 0;
	}
}

electricity::electricity()
{
	cout << "请输入城市个数" << endl;
	getNumber(cityNumber);
	while (cityNumber <= 1)
	{
		cout << "发生错误，请输入大于1小于INT_MAX的正整数" << endl;
		getNumber(cityNumber);
	}
	cities = new string[cityNumber];
	check = new unordered_set(cityNumber);
	cout << "请输入各城市名称" << endl;
	for (int i = 0; i < cityNumber; i++)
	{
		cin >> cities[i];
		if (check->find(cities[i]))
		{
			cout << "请不要重名" << endl;
			i--;
			continue;
		}
		check->insert(cities[i]);
	}
	ufs = new UnionFindSet<string>(cityNumber, cities);
	cout << "请输入电网线路的个数" << endl;
	edgeNumber = 0;
	getNumber(edgeNumber);
	while (edgeNumber <= 0)
	{
		cout << "发生错误，请输入小于INT_MAX的正整数" << endl;
		getNumber(edgeNumber);
	}
	edges = new Edge[edgeNumber];
	string temps1, temps2;
	for (int i = 0; i < edgeNumber; i++)
	{
		int temp = 0;
		cout << "请输入两个城市名与线路价格：" ;
		cin >> temps1 >> temps2;
		getNumber(temp);
		if (check->find(temps1) && check->find(temps2) && temp > 0)
		{
			edges[i] = Edge(temps1, temps2, temp);
		}
		else
		{
			cout << "输入不合法，请重新输入" << endl;
			i--;
		}
	}
	heap = new MinHeap<Edge>(edges, edgeNumber);
	cout << "输入完毕" << endl;
}

electricity::~electricity()
{
	delete[] cities;
	delete check;
	delete[] edges;
	delete[] ans;
	delete ufs;
	delete heap;
}

void electricity::span()
{
	int num = 0;
	ans = new Edge[cityNumber - 1];
	Edge min;
	while (!heap->isEmpty() && num < cityNumber - 1)
	{
		min = heap->pop();
		if (ufs->isUnioned(min.name1, min.name2))
		{
			continue;
		}
		ufs->unionElement(min.name1, min.name2);
		ans[num++] = min;
	}
	if (num == cityNumber - 1)
	{
		cout << "已找到最佳线路" << endl;
		printGraph();
	}
	else
	{
		cout << "该地区电网不连通，无法找到最佳线路" << endl;
	}
}

void electricity::printGraph()
{
	cout << "最佳线路为：" << endl;
	for (int i = 0; i < cityNumber - 1; i++)
	{
		cout << ans[i].name1 << "-<" << ans[i].cost << ">->" << ans[i].name2 << endl;
	}
}


int main()
{
	electricity project;
	project.span();
	system("pause");
	return 0;
}