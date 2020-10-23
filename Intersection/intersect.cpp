#include "intersect.h"
#include <string>
Node::Node(int val)
{
	value = val;
}


List::List()
{
	head = new Node(0);
	present = head;
	length = 0;
}

List::~List()
{
	Node* temp = head;
	while (temp != present)
	{
		Node* ptr = temp;
		temp = temp->next;
		delete ptr;
	}
	delete temp;	
	cout << "������" << endl;
}

void List::insert(const int &temp)
{
	present->next = new Node(temp);
	present = present->next;
	length++;
}

int List::size()
{
	return length;
}

void intersection::getNumber(int& temp)
{
	string checkIn;
	cin >> checkIn;
	if (checkIn == "-1")
	{
		temp = -1;
		return;
	}
	for (auto elem : checkIn)
	{
		if (!(elem >= '0'&&elem <= '9'))
		{
			cout << "����������ţ��ѽض�";
			temp = -1;
			return;
		}
	}

	temp = stoi(checkIn);
}

void List::printList()
{
	Node* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		cout << temp->value << ' ';
	}
	cout << endl;
}

intersection::intersection()
{
	first = new List();
	second = new List();
	answer = new List();
	int temp = 0;
	cout << "������һ���������е����֣���-1��β"<<endl;
	getNumber(temp);
	while (temp != -1)
	{
		if (first->size() == 0 || (first->size() != 0 && first->present->value <= temp))
		{
			first->insert(temp);
		}
		else
		{
			cout << "���������У��������Ƿ�����" << endl;
		}
		getNumber(temp);
	}//������ȡ��һ������
	cout << "��ȡ���ĵ�һ������Ϊ��";
	first->printList();
	Node* presentptr=first->head;
	presentptr = presentptr->next;//�����Ƿ�Ϊ�գ���һ������ָ����һ��
	cout << "������һ���������е����֣���-1��β" << endl;
	getNumber(temp);
	while (temp != -1)
	{
		if (second->size() == 0 || (second->size() != 0 && second->present->value <= temp))
		{
			second->insert(temp);
			if (presentptr != nullptr)//ֻ�в�Ϊ�ղ��ܽ����ж�
			{
				if (presentptr->value == temp)
				{
					answer->insert(temp);//���ֱ�ӵõ���
					presentptr = presentptr->next;//��ǰֵ����temp��ָ����һ��
				}
				else if (presentptr->value < temp)
				{
					while (presentptr != nullptr&&presentptr->value < temp)
					{
						presentptr = presentptr->next;//�ҵ���һ�����ڵ���temp�����ֻ����β��
					}
					if (presentptr != nullptr&&presentptr->value == temp)
					{
						answer->insert(temp);
						presentptr = presentptr->next;//�����ȣ�ִ���Ϸ���ͬ����
					}
				}//��ʱֻ�д���temp�Ĳ�ִ���κβ�����ֱ�Ӷ�ȡ��һ��temp
			}
		}
		else
		{
			cout << "���������У��������Ƿ�����" << endl;
		}
		getNumber(temp);
	}//��ʱ�����������ȡ���
	cout << "��ȡ���ĵڶ�������Ϊ��";
	second->printList();
}

void intersection::printAnswer()
{
	cout << "��������Ϊ��";
	if (answer->size() == 0)
	{
		cout << "NULL" << endl;
	}
	else
	{
		answer->printList();
	}
	cout << "���ҵ�����" << endl;
}

intersection::~intersection()
{
	delete first;
	delete second;
	delete answer;
}

int main()
{
	intersection findIntersection;
	findIntersection.printAnswer();
	system("pause");
	return 0;
}