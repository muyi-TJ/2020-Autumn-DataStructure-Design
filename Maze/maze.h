#pragma once
#include <iostream>
#include<string>
using namespace std;

#define BLOCK '#'
#define BLANK 'O'
#define WAY '1'
#define EXIT '$'
#define ENTRY '@'
#define VISITED true
#define UNVISITED false

const int DIRECTION[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

template <class T>
class stack
{
public:
	stack(int size);
	~stack();
	bool push(T elem);
	void expand();
	int size();
	T pop();
	bool empty();
	T peek();
private:
	T* m_buffer;
	int m_size;
	int m_element;
};

class Maze
{
private:
	class Position
	{
	public:
		int x = -1;
		int y = -1;
		Position(int column, int row)//x表示纵坐标，y表示横坐标
		{
			x = column;
			y = row;
		}
		Position() = default;
		bool operator ==(Position pos)
		{
			return pos.x == this->x && pos.y == this->y;
		}
	};
	stack<Position> m_way;
	stack<Position> m_outPrint;
	Position m_position;
	Position m_exit;
	Position m_entry;
	Position m_nullposition;
	const int m_column;
	const int m_row;
	string* p_maze;
	bool** isVisited;

	bool isInBound(Position pos);//判断位置是否在迷宫内
	bool isAvaiable(Position pos);//判断位置是否可行走
	void printMaze();
	void getWay();
public:
	Maze(int column, int row);
	~Maze();
	void getOut();//出迷宫
};