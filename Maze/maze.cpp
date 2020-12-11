#include "maze.h"

template <class T>
stack<T>::stack(int size)
{
	m_size = size;
	m_buffer = new T[size];
	m_element = 0;
}

template <class T>
stack<T>::~stack()
{
	delete[] m_buffer;
}

template<class T>
bool stack<T>::empty()
{
	return m_element == 0;
}

template<class T>
T stack<T>::peek()
{
	return m_buffer[m_element - 1];
}

template<class T>
int stack<T>::size()
{
	return m_element;
}

template <class T>
bool stack<T>::push(T elem)
{
	expand();
	m_buffer[m_element++] = elem;
	return true;
}

template <class T>
T stack<T>::pop()
{
	return m_buffer[--m_element];

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

Maze::~Maze()
{
	for (int i = 0; i < m_column; i++)
	{
		delete[] isVisited[i];
	}
	delete[] isVisited;
	delete[] p_maze;
}

Maze::Maze(int column, int row) :m_column(column), m_row(row), m_way(1000), m_outPrint(1000)
{
	p_maze = new string[column];
	cout << "请按行输入迷宫内容，#表示墙壁，大写字母O表示通路，@表示入口，$表示出口" << endl;
	string buffer;
	bool isAllowed = true;
	bool haveEntry = false, haveExit = false;
	Position tempentry, tempexit;
	int i = 0, j = 0;
	while (i < m_column)
	{
		isAllowed = true;
		cin >> buffer;
		if (buffer.size() != m_row)
		{
			cout << "请检查输入元素数量是否与行长度相等并重新输入" << endl;
			continue;
		}
		else
		{
			for (j = 0; j < buffer.size(); j++)
			{
				if (buffer[j] == BLANK || buffer[j] == BLOCK)
				{
					continue;
				}
				else if (buffer[j] == ENTRY)
				{
					if (!haveEntry&&tempentry == m_nullposition)
					{
						tempentry = Position(i, j);
					}
					else
					{
						isAllowed = false;
						break;
					}
				}
				else if (buffer[j] == EXIT)
				{
					if (!haveExit&&tempexit == m_nullposition)
					{
						tempexit = Position(i, j);
					}
					else
					{
						isAllowed = false;
						break;
					}
				}
				else
				{
					isAllowed = false;
					break;
				}
			}
			if (isAllowed)
			{
				p_maze[i] = buffer;
				if (!haveEntry && !(tempentry == m_nullposition))
				{
					m_entry = tempentry;
					haveEntry = true;
				}
				if (!haveExit && !(tempexit == m_nullposition))
				{
					m_exit = tempexit;
					haveExit = true;
				}
				cout << "本行输入成功" << endl;
				i++;
			}
			else
			{
				tempentry = m_nullposition;
				tempexit = m_nullposition;
				cout << "输入不合法字符或出现多个出入口" << endl;
				continue;
			}
		}
	}
	printMaze();
}

bool Maze::isInBound(Position pos)
{
	return pos.x >= 0 && pos.y >= 0 && pos.x < m_column&&pos.y < m_row;
}

bool Maze::isAvaiable(Position pos)
{
	return isInBound(pos) && (!isVisited[pos.x][pos.y]) && (p_maze[pos.x][pos.y] == BLANK || p_maze[pos.x][pos.y] == EXIT);
}

void Maze::getWay()
{
	int size = m_way.size();
	for (int i = 0; i < size; i++)
	{
		m_outPrint.push(m_way.pop());
	}
}

void Maze::printMaze()
{
	cout << "       ";
	for (int i = 0; i < m_row; i++)
	{
		cout << "第" << i << "列" << "  ";
	}
	cout << endl;
	for (int i = 0; i < m_column; i++)
	{
		for (int j = -1; j < m_row; j++)
		{
			if (j == -1)
			{
				cout << "第" << i << "行" << "  ";
			}
			else
			{
				cout << "  " << p_maze[i][j] << "    ";
			}
		}
		cout << endl;
	}
}

void Maze::getOut()
{
	if (m_entry == m_nullposition || m_exit == m_nullposition)
	{
		cout << "没有出口/入口，无法给出路线" << endl;
		return;
	}
	m_position = m_entry;
	isVisited = new bool*[m_column];
	int row, column;
	Position temp;
	for (int i = 0; i < m_column; i++)
	{
		isVisited[i] = new bool[m_row];
		for (int j = 0; j < m_row; j++)
		{
			isVisited[i][j] = false;
		}
	}
	m_way.push(m_position);
	isVisited[m_position.x][m_position.y] = VISITED;
	while (!(m_position == m_exit))
	{
		row = m_position.y;
		column = m_position.x;
		temp = m_position;
		for (int i = 0; i < 4; i++)
		{
			if (isAvaiable(Position(column + DIRECTION[i][0], row + DIRECTION[i][1])))
			{
				temp = Position(column + DIRECTION[i][0], row + DIRECTION[i][1]);
				isVisited[temp.x][temp.y] = VISITED;
				m_way.push(temp);
				p_maze[temp.x][temp.y] = WAY;
				break;
			}
		}
		if (m_position == temp)
		{
			m_way.pop();//此路不通
			p_maze[m_position.x][m_position.y] = BLANK;
			if (m_way.empty())
			{
				cout << "无可通路径" << endl;
				return;
			}
			else
			{
				m_position = m_way.peek();//获取栈顶
			}
		}
		else
		{
			m_position = temp;
		}
	}//出循环，说明已经有一条通路
	getWay();
	p_maze[m_exit.x][m_exit.y] = EXIT;
	printMaze();
	cout << endl;
	cout << "迷宫路径：" << endl << endl;
	while (!m_outPrint.empty())
	{
		temp = m_outPrint.pop();
		cout << '<' << temp.x << ',' << temp.y << '>' << ' ';
		if (!m_outPrint.empty())
		{
			cout << "---> ";
		}
	}
	cout << endl;
}


int main()
{
	int column = 0, row = 0;
	cout << "先输入列长度，再输入行长度" << endl;
	cin >> column >> row;

	if (column <= 0 || row <= 0)
	{
		cout << "列长度/行长度不合法" << endl;
		system("pause");
		return 0;
	}
	Maze maze(column, row);
	maze.getOut();
	system("pause");
	return 0;
}