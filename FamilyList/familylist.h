#pragma once
#include <iostream>
#include <string>
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

class FamilyList
{
private:
	class Member
	{
	public:
		string name;
		int childnum = 0;
		Member** children = nullptr;

		Member(string val)
		{
			name = val;
		}

		Member() = default;

		~Member()
		{
			removeChildren();
			delete[] children;
		}

		void removeChildren()
		{
			for (int i = 0; i < childnum; i++)
			{
				delete children[i];
			}
			childnum = 0;
		}

		void setChildnum(int size)
		{
			children = new Member*[size];
		}

		void addChildren(string newChild)
		{
			childnum++;
			Member** temp = children;
			children = new Member*[childnum];
			memcpy(children, temp, (childnum - 1) * sizeof(Member*));
			children[childnum - 1] = new Member(newChild);
			delete[] temp;
		}

		friend ostream& operator <<(ostream& os, const Member& person)
		{
			cout << person.name;
			if (person.childnum == 0)
			{
				cout << "无子女" << endl;
			}
			else
			{
				cout << "有" << person.childnum << "个子女，分别为：";
				for (int i = 0; i < person.childnum; i++)
				{
					cout << person.children[i]->name << " ";
				}
				cout << endl;
			}
			return os;
		}
	};
	Member* root;
public:
	FamilyList();
	~FamilyList();
	void insert(string parent);
	void addChild(string parent, string child);
	void removeChildren(string parent);
	Member* find(const string& name);
	void changeName(string preName, string postName);
	bool getOrder();
	bool sameName(const string& name);
	void getNumber(int& temp);
};