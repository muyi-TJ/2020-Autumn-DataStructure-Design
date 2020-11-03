#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>
using namespace std;
template<class T>
class Node
{
	friend class List;

protected:
	T value;
	Node<T>* prev;
	Node<T>* next;

public:
	Node (T val, Node<T>* p = nullptr, Node<T>* n = nullptr)
	{
		value = val;
		prev = p;
		next = n;
	}
	T getval()
	{
		return value;
	}
	friend ostream& operator <<(ostream & os, Node<T> node)
	{
		os << node.val;
		return os;
	}

};

template<class T>
class List
{
public:
	List()
	{
		head = new Node(T());
		head->next = new Node(T(), head);
		length = 0;
	}

	List(const List<T> &source)
	{
		head = new Node(T());
		head->next = new Node(T(), head);
		length = 0;
		Node<T>* temp = source.head;
		while (temp != source.tail)
		{
			temp = temp->next;
			insert(temp->value);
		}
	}

	~List()
	{
		Node<T>* temp = tail;
		while (temp != head)
		{
			temp = temp->prev;
			delete temp->next;
		}
		delete temp;
	}

	bool insert(const T &temp)
	{
		tail->prev->next = new Node(temp, tail->prev, tail);
		length++;
		return true;
	}

	bool insert(const T &temp, int index)
	{
		if (index <= 0)
		{
			cerr << "下标小于等于0，插入失败" << endl;
			return false;
		}
		if (index > length)
		{
			cerr << "下标大于链表长度，插入失败" << endl;
			return false;
		}
		Node<T>* checknode = head;
		for (int i = 0; i < index; i++)
		{
			checknode = checknode->next;
		}
		checknode->prev->next = new Node(temp, checknode->prev, checknode);
		checknode->prev = checknode->prev->next;
		return true;

	}

	T find(int index)
	{
		if (index <= 0)
		{
			cerr << "下标小于等于0，查找失败" << endl;
			return T();
		}
		if (index > length)
		{
			cerr << "下标大于链表长度，查找失败" << endl;
			return T();
		}
		Node<T>* temp = head;
		if (index < 0.5*length)
		{
			for (int i = 0; i < index; i++)
			{
				temp = temp->next;
			}
		}
		else
		{
			for (int i = length + 1; i > index; i--)
			{
				temp = temp->prev;
			}
		}
		return temp->value;
	}

	bool remove(int index)
	{
		if (index <= 0)
		{
			cerr << "下标小于等于0，删除失败" << endl;
			return false;
		}
		if (index > length)
		{
			cerr << "下标大于链表长度，删除失败" << endl;
			return false;
		}
		Node<T>* temp = head;
		if (index < 0.5*length)
		{
			for (int i = 0; i < index; i++)
			{
				temp = temp->next;
			}
		}
		else
		{
			for (int i = length + 1; i > index; i--)
			{
				temp = temp->prev;
			}
		}
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		delete temp;
		length--;
		return true;
	}

	int size()
	{
		return lenth;
	}

	bool isEmpty()
	{
		return lenth == 0;
	}

	void printList(bool reverse==false)
	{
		if (reverse)
		{
			Node<T>* temp = tail;
			while (temp->prev!=head)
			{
				temp = temp->prev;
				cout << *(temp);
			}
		}
		else
		{
			Node<T>* temp = head;
			while (temp->next != tail)
			{
				temp = temp->next;
				cout << *(temp);
			}
		}
	}
private:
	const Node<T>* head;
	const Node<T>* tail;
	int length;
};

#endif // !_LIST_H_

