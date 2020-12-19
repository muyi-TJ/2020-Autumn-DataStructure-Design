#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class v>
class unordered_map
{
private:
	class Node
	{
	public:
		Node(string ikey, v ivalue)
		{
			key = ikey;
			value = ivalue;
			next = nullptr;
		}
		Node()
		{
			next = nullptr;
		}
		~Node()
		{
			while (next)
			{
				Node* temp = next;
				next = temp->next;
				delete temp;
			}
		}
		string key;
		v value;
		Node* next;
	};
	int hashSize;
	Node* hashnode;
	int hash(string key);
public:
	unordered_map(int size);
	~unordered_map();
	Node* find(string key);
	v& operator [] (string key);

};

class unordered_set
{
private:
	class Node
	{
	public:
		Node(string ivalue)
		{
			value = ivalue;
			next = nullptr;
		}
		Node()
		{
			next = nullptr;
		}
		string value;
		Node* next;
	};
	int hashSize;
	Node* hashnode;
	int hash(string value);
public:
	unordered_set(int size);
	~unordered_set();
	void insert(string value);
	Node* find(string value);

};

template<class T>
class UnionFindSet
{
private:
	class VW
	{
	public:
		T value;
		int weight;
		VW(T v, int w) :value(v), weight(w) {}
		VW() = default;
	};
	int num;
	unordered_map<VW> buffer;
public:
	UnionFindSet(int size, T* elements);
	void unionElement(T a, T b);
	T find(T a);
	bool isUnioned(T a, T b);
};

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
private:
	int size;
	int number;
	T* buffer;
	void down(int start, int end);
	void up(int start);
};

class Edge
{
public:
	string name1;
	string name2;
	int cost = 0;
	Edge(string a, string b, int number);
	Edge() = default;
	~Edge() = default;
	bool operator<(const Edge &right);
};

class electricity
{
private:
	int cityNumber = 0;
	int edgeNumber = 0;
	string* cities;
	unordered_set* check;
	Edge* edges;
	Edge* ans;
	UnionFindSet<string>* ufs;
	MinHeap<Edge>* heap;
	void getNumber(int& temp);
public:
	electricity();
	~electricity();
	void span();
	void printGraph();
};