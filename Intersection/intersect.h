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
	List();//���캯��
	~List();//��������
	void insert(const int &temp);//��˲���
	int size();//������
	void printList();//�������
	
protected:
	Node* head;
	Node* present;
	int length;
};

class intersection
{
public:
	intersection();//���캯��
	~intersection();//��������
	void printAnswer();//�����
	void getNumber(int& temp);//����������������
private:
	List* first;
	List* second;
	List* answer;
};

