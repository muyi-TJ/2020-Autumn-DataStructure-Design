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
	cout << "已析构" << endl;
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
			cout << "输入特殊符号，已截断";
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
	cout << "请输入一行升序排列的数字，以-1结尾"<<endl;
	getNumber(temp);
	while (temp != -1)
	{
		if (first->size() == 0 || (first->size() != 0 && first->present->value <= temp))
		{
			first->insert(temp);
		}
		else
		{
			cout << "请升序排列，已跳过非法输入" << endl;
		}
		getNumber(temp);
	}//完整读取第一个链表
	cout << "读取到的第一组链表为：";
	first->printList();
	Node* presentptr=first->head;
	presentptr = presentptr->next;//无论是否为空，都一定可以指向下一个
	cout << "请输入一行升序排列的数字，以-1结尾" << endl;
	getNumber(temp);
	while (temp != -1)
	{
		if (second->size() == 0 || (second->size() != 0 && second->present->value <= temp))
		{
			second->insert(temp);
			if (presentptr != nullptr)//只有不为空才能进行判断
			{
				if (presentptr->value == temp)
				{
					answer->insert(temp);//相等直接得到答案
					presentptr = presentptr->next;//当前值等于temp，指向下一个
				}
				else if (presentptr->value < temp)
				{
					while (presentptr != nullptr&&presentptr->value < temp)
					{
						presentptr = presentptr->next;//找到下一个大于等于temp的数字或读到尾端
					}
					if (presentptr != nullptr&&presentptr->value == temp)
					{
						answer->insert(temp);
						presentptr = presentptr->next;//如果相等，执行上方相同代码
					}
				}//此时只有大于temp的不执行任何操作，直接读取下一个temp
			}
		}
		else
		{
			cout << "请升序排列，已跳过非法输入" << endl;
		}
		getNumber(temp);
	}//此时所有链表均读取完毕
	cout << "读取到的第二组链表为：";
	second->printList();
}

void intersection::printAnswer()
{
	cout << "交集链表为：";
	if (answer->size() == 0)
	{
		cout << "NULL" << endl;
	}
	else
	{
		answer->printList();
	}
	cout << "已找到交集" << endl;
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