#include "familylist.h"

template <class T>
stack<T>::stack(int size)
{
	m_size = size;
	m_buffer = new T[size];
	m_element = 0;
}

template <class T>
stack<T>::stack(const stack<T>& source)
{
	m_size = source.m_size;
	m_element = source.m_element;
	m_buffer = new T[m_size];
	memcpy(m_buffer, source.m_buffer, m_element);
}

template <class T>
stack<T>::~stack()
{
	delete[] m_buffer;
}

template <class T>
bool stack<T>::isEmpty()
{
	return m_element == 0;
}

template <class T>
bool stack<T>::isFull()
{
	return m_element == m_size;
}

template <class T>
int stack<T>::stacklength()
{
	return m_element;
}

template <class T>
bool stack<T>::push(T elem)
{
	if (isFull())
	{
		cout << "stack overflow" << endl;
		return false;
	}
	else
	{
		m_buffer[m_element++] = elem;
		return true;
	}
}

template <class T>
T stack<T>::pop()
{
	if (isEmpty())
	{
		cout << "stack underflow" << endl;
		return T();
	}
	else
	{
		return m_buffer[--m_element];
	}
}

template <class T>
T stack<T>::peek()
{
	if (isEmpty())
	{
		cout << "stack empty" << endl;
		return T();
	}
	else
	{
		return m_buffer[m_element - 1];
	}
}

template <class T>
void stack<T>::expand()
{
	if (static_cast<double>(m_element) / m_size >= 0.75)
	{
		T* temp = new T[(m_size + 2) * 4 / 3];
		memcpy(temp, m_buffer, m_element);
		delete[] m_buffer;
		m_buffer = temp;
		m_size = (m_size + 2) * 4 / 3;
	}
}

FamilyList::FamilyList()
{
	cout << "请输入祖先名称" << endl;
	string name;
	cin >> name;
	root = new Member(name);
	cout << "已建立家谱，继续操作" << endl;
	cout << "请输入操作\n" << "1.完善家谱 2.查找家庭\n"
		<< "3.添加子女 4.解散家庭\n" << "5.修改姓名 6.取消" << endl;
}

FamilyList::~FamilyList()
{
	delete root;
}

void FamilyList::getNumber(int& temp)
{
	string checkIn;
	cin >> checkIn;
	if (checkIn.size() > 10)
	{
		cout << "输入的数字不合法" << endl;
		temp = 0;
		return;
	}
	for (auto elem : checkIn)
	{
		if (!(elem >= '0'&&elem <= '9'))
		{
			cout << "输入的数字不合法" << endl;
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
		cout << "输入的数字过大" << endl;
		temp = 0;
	}
}

bool FamilyList::getOrder()
{
	int order = 0;
	getNumber(order);
	string parent, child, prename, postname;
	Member* p_parent;
	switch (order)
	{
	case 1:
		cout << "请输入要完善家庭的父母姓名" << endl;
		cin >> parent;
		insert(parent);
		break;
	case 2:
		cout << "请输入要所查找家庭父母姓名" << endl;
		cin >> parent;
		p_parent = find(parent);
		if (p_parent)
		{
			cout << *p_parent;
		}
		else
		{
			cout << "查无此人" << endl;
		}
		break;
	case 3:
		cout << "请输入要添加子女的父母姓名和子女姓名" << endl;
		cin >> parent >> child;
		addChild(parent, child);
		break;
	case 4:
		cout << "请输入要解散家庭的人的姓名" << endl;
		cin >> parent;
		removeChildren(parent);
		break;
	case 5:
		cout << "请输入改名前和改名后的名字" << endl;
		cin >> prename >> postname;
		changeName(prename, postname);
		break;
	case 6:
		cout << "访问家谱结束" << endl;
		return false;
	default:
		cout << "请输入正确的指令" << endl;
		break;
	}
	return true;
}

bool FamilyList::sameName(const string& name)
{
	return find(name) != nullptr;
}

void FamilyList::insert(string parent)
{
	Member* p_parent = find(parent);
	if (!p_parent)
	{
		cout << "未找到姓名为" << parent << "的成员" << endl;
		return;
	}
	if (p_parent->childnum > 0)
	{
		cout << "该成员的家庭已经完善，请使用添加子女功能" << endl;
		return;
	}
	cout << "请输入子女人数：" << endl;
	int childnum = 0;
	getNumber(childnum);
	if (childnum == 0)
	{
		cout << "完善家庭时子女数目必须合法" << endl;
		return;
	}
	p_parent->setChildnum(childnum);
	cout << "请输入子女姓名：" << endl;
	for (int i = 0; i < childnum; i++)
	{
		string child;
		cin >> child;
		if (sameName(child))
		{
			cout << "家谱内请不要重名，应添加标记区分重名者，请重新输入" << endl;
			i--;
			continue;
		}
		else
		{
			p_parent->children[i] = new Member(child);
			p_parent->childnum++;
		}
	}
	cout << *p_parent;
}

void FamilyList::addChild(string parent, string child)
{
	Member* p_parent = find(parent);
	if (p_parent)
	{
		if (sameName(child))
		{
			cout << "家谱内请不要重名，应添加标记区分重名者，添加失败" << endl;
			return;
		}
		p_parent->addChildren(child);
		cout << *p_parent;
	}
	else
	{
		cout << "未找到父母，添加子女失败" << endl;
	}
}

FamilyList::Member* FamilyList::find(const string& name)
{
	stack<Member*> order(1000);
	if (root->name == name)
	{
		return root;
	}
	order.push(root);
	while (!order.isEmpty())
	{
		Member* temp = order.pop();
		for (int i = 0; i < temp->childnum; i++)
		{
			if (temp->children[i]->name == name)
			{
				return temp->children[i];
			}
			else
			{
				order.push(temp->children[i]);
			}
		}
		
	}
	return nullptr;
}

void FamilyList::changeName(string preName, string postName)
{
	Member* person = find(preName);
	if (!person)
	{
		cout << "未找到姓名为" << preName << "的成员" << endl;
		return;
	}
	if (preName == postName)
	{
		cout << "更名前后名字相同，为" << preName << endl;
		return;
	}
	if (sameName(postName))
	{
		cout << "家谱内请不要重名，应添加标记区分重名者，更名失败" << endl;
		return;
	}
	cout << "成员更名前为" << preName << endl;
	cout << "成员更名后为" << postName << endl;
	person->name = postName;
}

void FamilyList::removeChildren(string parent)
{
	Member* p_parent = find(parent);
	if (!p_parent)
	{
		cout << "未找到姓名为" << parent << "的成员" << endl;
		return;
	}
	cout << *p_parent;
	p_parent->removeChildren();
	cout << "子女及其他后代已移除" << endl;
}



int main()
{
	FamilyList list;
	while (list.getOrder())
	{
		cout << "请再次输入指令" << endl;
	}
	system("pause");
	return 0;
}