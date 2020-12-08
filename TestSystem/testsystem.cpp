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
	return abs(hashvalue % hashSize);
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



TestSystem::TestSystem() :dataSystem(10099)
{
	cout << "准备建立考生信息管理系统" << endl;
	cout << "请输入考生人数:" << endl;
	cin >> studentNumber;
	if (studentNumber < 0)
	{
		cout << "考生数目不得小于0，请重新建立" << endl;
		system("pause");
		exit(0);
	}
	if (studentNumber)
	{
		cout << "请按顺序输入考生考号、姓名、性别、年龄、科目" << endl;
		for (int i = 0; i < studentNumber; i++)
		{
			if (!insert())
			{
				i--;
			}
		}
	}
	cout << "建立成功" << endl;
}

bool TestSystem::getCommend()
{
	int order = 0;
	cout << "请输入要执行的操作:" << endl
		<< "1.插入新考生 2.修改考生信息 3.删除考生信息 4.查找考生 5.统计 0.结束访问" << endl;
	cin >> order;
	switch (order)
	{
	case 0:
		cout << "已离开考生系统" << endl;
		return false;
	case 1:
		cout << "请按顺序输入考生考号、姓名、性别、年龄、科目" << endl;
		if (insert())
		{
			studentNumber++;
		}
		return true;
	case 2:
		cout << "请输入想要修改信息的考生号" << endl;
		change(); 
		return true; 
	case 3:
		cout << "请输入想要删除信息的考生号" << endl;
		remove(); 
		return true; 
	case 4:
		cout << "请输入想要查找的考生号" << endl; 
		find();
		return true;
	case 5:
		cout << "已经在数据库内的考生为:" << endl; 
		printSystem();
		return true; 
	default:
		cout << "请输入正确的指令!" << endl;	
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
		cout << "不允许相同考号考生存在，插入失败" << endl;
		return false;
	}
	else
	{
		dataSystem.insert(testnumber, temp);
		cout << "考生插入成功,插入的考生信息为:" << temp;
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
		cout << "已找到考生,考生信息为:" << temp->getValue();
		return true;
	}
	else
	{
		cout << "未找到考生,返回上一级" << endl;
		return false;
	}
}

bool TestSystem::change()
{
	string number;
	cin >> number;
	if (dataSystem.find(number))
	{
		cout << "已找到考生,请输入修改后的信息" << endl;
		string testnumber, name, sex, age, subject;
		cin >> testnumber >> name >> sex >> age >> subject;
		Student temp(testnumber, name, sex, age, subject);
		if (testnumber == number)
		{
			dataSystem[number] = temp;
			cout << "修改成功,修改后的信息为:" << temp;
			return true;
		}
		else
		{
			if (dataSystem.find(testnumber))
			{
				cout << "不允许出现相同考号考生，修改失败" << endl;
				return false;
			}
			else
			{
				dataSystem.remove(number);
				dataSystem.insert(testnumber, temp);
				cout << "修改成功,修改后的信息为:" << temp;
				return true;
			}
		}
	}
	else
	{
		cout << "未找到相应考生，返回上一级" << endl;
		return false;
	}
}

bool TestSystem::remove()
{
	string number;
	cin >> number;
	if (auto temp = dataSystem.find(number))
	{
		cout << "删除成功，删除的信息为" << temp->getValue();
		studentNumber--;
		dataSystem.remove(number);
		return true;
	}
	else
	{
		cout << "删除失败，未找到对应考生" << endl;
		return false;
	}
}

void TestSystem::printSystem()
{
	cout << "考生号		姓名	性别	年龄	科目" << endl;
	dataSystem.printValue();
	cout << "共" << studentNumber << "名考生，已全部显示" << endl;
}

int main()
{
	TestSystem TS;
	while (TS.getCommend())
	{
		cout << "已执行一条命令" << endl;
	}
	system("pause");
	return 0;
}