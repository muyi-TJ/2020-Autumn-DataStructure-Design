#include <iostream>
using namespace std;
class Node
{
	friend class List;
	friend class intersection;
protected:
    int value;
	Node* next;
public:
	Node(int val);
	
};

class List
{
	friend class intersection;
public:
	List();//构造函数
	~List();//析构函数
	void insert(const int &temp);//后端插入
	int size();//链表长度
	void printList();//输出链表
	
protected:
	Node* head;
	Node* present;
	int length;
};

class intersection
{
public:
	intersection();//构造函数
	~intersection();//析构函数
	void printAnswer();//输出答案
	void getNumber(int& temp);//输入数据与输入检测
private:
	List* first;
	List* second;
	List* answer;
};

