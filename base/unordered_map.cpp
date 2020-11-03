#include "unordered_map.h"

template<class v>
Node<v>::Node(string ikey, v ivalue)
{
	key = ikey;
	value = ivalue;
	next = nullptr;
}

template<class v>
Node<v>::Node()
{
	next = nullptr;
}

template<class v>
v Node<v>::getValue()
{
	return value;
}

template<class v>
void Node<v>::setValue(v newvalue)
{
	value = newvalue;
}

template<class v>
Node<v>::~Node()
{
	while (next)
	{
		Node<v>* temp = next;
		next = temp->next;
		delete temp;
	}
}

template<class v>
unordered_map<v>::unordered_map(int size)
{
	hashSize = size;
	hashnode = new Node<v>[hashSize];
}

template<class v>
unordered_map<v>::~unordered_map()
{
	delete[] hashnode;
}
//TODO:为啥会找不到成员
template<class v>
Node<v>* unordered_map<v>::find(string key)
{
	int index = hash(key);
	Node<v>* temp = hashnode + index;
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
	return hashvalue % hashSize;
}

template<class v>
void unordered_map<v>::insert(string key, v value)
{
	Node<v>* temp = find(key);
	if (temp)
	{
		temp->value = value;
	}
	else
	{
		int index = hash(key);
		temp = hashnode + index;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new Node<v>(key, value);
	}
}

template<class v>
v& unordered_map<v>:: operator [] (string key)
{
	Node<v>*temp = find(key);
	if (temp)
	{
		return temp->value;
	}
	else
	{
		return v();
	}
}

template<class v>
void unordered_map<v>::remove(string key)
{
	int index = hash(key);
	Node<v>* temp = hashnode + index;
	while (temp->next)
	{
		if (temp->next->key == key)
		{
			Node<v>* removeptr = temp->next;
			temp->next = removeptr->next;
			removeptr->next = nullptr;
			delete removeptr;
			return;
		}
		else
		{
			temp = temp->next;
		}
	}
}