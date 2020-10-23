#include "testsystem.h"


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
		temp = hashnode + hash(key);
		temp->next = new Node<v>(key, v());
		return temp->next->value;
	}
}

template<class v>
void unordered_map<v> ::printValue()
{
	Node<v>*temp = hashnode;
	for (int i = 0; i < hashSize; i++)
	{
		if (temp->next)
		{
			Node<v>* print = temp->next;
			while (print)
			{
				cout << print->value;
				print = print->next;
			}
		}
		temp++;
	}
}



TestSystem::TestSystem() :dataSystem(10000)
{
	cout << "׼������������Ϣ����ϵͳ" << endl;
	cout << "�����뿼������:" << endl;
	cin >> studentNumber;
	cout << "�밴˳�����뿼�����š��������Ա����䡢��Ŀ" << endl;
	for (int i = 0; i < studentNumber; i++)
	{
		if (!insert())
		{
			i--;
		}
	}
	cout << "�����ɹ�" << endl;
}

bool TestSystem::getCommend()
{
	int order = 0;
	cout << "������Ҫִ�еĲ���:" << endl
		<< "1.�����¿��� 2.�޸Ŀ�����Ϣ 3.ɾ��������Ϣ 4.���ҿ��� 5.ͳ�� 0.��������" << endl;
	cin >> order;
	switch (order)
	{
	case 0:
		cout << "���뿪����ϵͳ" << endl;
		return false;
	case 1:
		cout << "�밴˳�����뿼�����š��������Ա����䡢��Ŀ" << endl;
		if (insert())
		{
			studentNumber++;
		}
		return true;
	case 2:
		cout << "��������Ҫ�޸���Ϣ�Ŀ�����" << endl;
		change(); 
		return true; 
	case 3:
		cout << "��������Ҫɾ����Ϣ�Ŀ�����" << endl;
		remove(); 
		return true; 
	case 4:
		cout << "��������Ҫ���ҵĿ�����" << endl; 
		find();
		return true;
	case 5:
		cout << "�Ѿ������ݿ��ڵĿ���Ϊ:" << endl; 
		printSystem();
		return true; 
	default:
		cout << "��������ȷ��ָ��!" << endl;	
		return true;	
		break;
	}
}

bool TestSystem::insert()
{
	string testnumber, name, sex, age, subject;
	cin >> testnumber >> name >> sex >> age >> subject;
	Student temp(testnumber, name, sex, age, subject);
	if (dataSystem.find(testnumber))
	{
		cout << "��������ͬ���ſ������ڣ�����ʧ��" << endl;
		return false;
	}
	else
	{
		dataSystem.insert(testnumber, temp);
		cout << "��������ɹ�,����Ŀ�����ϢΪ:" << temp;
		return true;
	}
}

bool TestSystem::find()
{
	string number;
	cin >> number;
	auto temp = dataSystem.find(number);
	if (temp)
	{
		cout << "���ҵ�����,������ϢΪ:" << temp->getValue();
		return true;
	}
	else
	{
		cout << "δ�ҵ�����,������һ��" << endl;
		return false;
	}
}

bool TestSystem::change()
{
	string number;
	cin >> number;
	if (dataSystem.find(number))
	{
		cout << "���ҵ�����,�������޸ĺ����Ϣ" << endl;
		string testnumber, name, sex, age, subject;
		cin >> testnumber >> name >> sex >> age >> subject;
		Student temp(testnumber, name, sex, age, subject);
		if (testnumber == number)
		{
			dataSystem[number] = temp;
			cout << "�޸ĳɹ�,�޸ĺ����ϢΪ:" << temp;
			return true;
		}
		else
		{
			if (dataSystem.find(testnumber))
			{
				cout << "�����������ͬ���ſ������޸�ʧ��" << endl;
				return false;
			}
			else
			{
				dataSystem.remove(number);
				dataSystem.insert(testnumber, temp);
				cout << "�޸ĳɹ�,�޸ĺ����ϢΪ:" << temp;
				return true;
			}
		}
	}
	else
	{
		cout << "δ�ҵ���Ӧ������������һ��" << endl;
		return false;
	}
}

bool TestSystem::remove()
{
	string number;
	cin >> number;
	if (auto temp = dataSystem.find(number))
	{
		cout << "ɾ���ɹ���ɾ������ϢΪ" << temp->getValue();
		studentNumber--;
		dataSystem.remove(number);
		return true;
	}
	else
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ���Ӧ����" << endl;
		return false;
	}
}

void TestSystem::printSystem()
{
	cout << "������	����	�Ա�	����	��Ŀ" << endl;
	dataSystem.printValue();
	cout << "��" << studentNumber << "����������ȫ����ʾ" << endl;
}

int main()
{
	TestSystem TS;
	while (TS.getCommend())
	{
		cout << "��ִ��һ������" << endl;
	}
	system("pause");
	return 0;
}