#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template<class v>
class unordered_map;
template<class T>
class queue;
class Course;
class Term;
class Schedule;

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
				auto temp = next;
				next = temp->next;
				temp->next = nullptr;
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
	T front();
	int getNumber();
	bool empty();
	bool full();
};

class Course
{
public:
	Course() = default;
	~Course();
	void addNext(Course* ptr);
	void delOut(queue<Course*>& q);
	string m_number;
	string m_name;
	int classHours;
	int openTerm;
	int in = 0;
	int out = 0;
	Course** next = nullptr;
};

class Term
{
public:
	Term();
	~Term();
	bool addCourse(Course* c);
	bool isFull();
	void arrange();
	int courseNum;
	int presentClass = 0;
	int classHour = 0;
	Course** buffer = nullptr;
	string termTable[5][10];
	bool isAvaiavle[5][4];

};

class Schedule
{
public:
	Schedule(int classnum) :courses(classnum), checkReady(classnum) {};
	Term singleTerm[8];
	unordered_map<Course> courses;
	queue<Course*> checkReady;
	void arrange();

};