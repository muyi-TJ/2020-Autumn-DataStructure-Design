#pragma once
#include<iostream>
#include <string>
using namespace std;
template<class v>
class unordered_map;

template<class v>
class Node
{
public:
	friend class unordered_map<v>;
	Node<v>(string ikey, v ivalue);
	Node<v>();
	v getValue();
	void setValue(v newvalue);
	~Node<v>();
protected:
	string key;
	v value;
	Node<v>* next;
}; 

template<class v>
class unordered_map
{
public:
	unordered_map(int size);
	~unordered_map();
	Node<v>* find(string key);
	void remove(string key);
	void insert(string key, v value);
	v& operator [] (string key);
private:
	int hashSize;
	Node<v>* hashnode;
	int hash(string key);
};