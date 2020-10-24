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
	void printValue();
private:
	int hashSize;
	Node<v>* hashnode;
	int hash(string key);
};


class TestSystem
{
private:
	class Student
	{
	public:
		string testnumber;
		string name;
		string sex;
		string age;
		string subject;
		Student(string inumber, string iname, string isex, string iage, string isubjext):
			testnumber(inumber), name(iname), sex(isex), age(iage), subject(isubjext) {}
		Student() = default;
		friend ostream& operator <<(ostream& os, Student stu)
		{
			os << stu.testnumber << ' ' << stu.name << ' ' << stu.sex << ' ' << stu.age << ' ' << stu.subject << endl;
			return os;
		}

	};
	int studentNumber;
	unordered_map<Student> dataSystem;
public:
	TestSystem();
	bool getCommend();
	bool find();
	bool change();
	bool insert();
	bool remove();
	void printSystem();
};
