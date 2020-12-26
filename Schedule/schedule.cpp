#include "schedule.h"

template<class v>
unordered_map<v>::unordered_map(int size)
{
	hashSize = size;
	hashnode = new Node[hashSize];
}

template<class v>
unordered_map<v>::~unordered_map()
{
	delete[] hashnode;
}

template<class v>
typename unordered_map<v>::Node* unordered_map<v>::find(string key)
{
	int index = hash(key);
	Node* temp = hashnode + index;
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
v& unordered_map<v>:: operator [] (string key)
{
	Node*temp = find(key);
	if (temp)
	{
		return temp->value;
	}
	else
	{
		temp = hashnode + hash(key);
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new Node(key, v());
		return temp->next->value;
	}
}

template<class T>
queue<T>::queue(int num)
{
	size = num;
	number = 0;
	buffer = new T[size];
	head = 0;
	tail = 0;
}

template<class T>
queue<T>::~queue()
{
	delete[] buffer;
}

template<class T>
void queue<T>::push(const T& elem)
{
	if (full())
	{
		cout << "队列已满，无法入列" << endl;
		return;
	}
	else
	{
		buffer[tail++] = elem;
		number++;
		if (tail == size)
		{
			tail = 0;
		}
	}
}

template<class T>
T queue<T>::pop()
{
	if (empty())
	{
		cout << "队列为空，无法出列" << endl;
		return T();
	}
	else
	{
		T temp = buffer[head++];
		number--;
		if (head == size)
		{
			head = 0;
		}
		return temp;
	}
}

template<class T>
T queue<T>::front()
{
	if (number > 0)
	{
		return buffer[head];
	}
	return T();
}

template<class T>
bool queue<T>::empty()
{
	return number == 0;
}

template<class T>
bool queue<T>::full()
{
	return number == size;
}

template<class T>
int queue<T>::getNumber()
{
	return number;
}

Course::~Course()
{
	delete[] next;
}

void Course::addNext(Course * ptr)
{
	auto temp = next;
	next = new Course*[out + 1];
	memcpy(next, temp, out * sizeof(Course*));
	next[out++] = ptr;
	delete[] temp;
}

void Course::delOut(queue<Course*>& q)
{
	for (int i = 0; i < out; i++)
	{
		if (--(next[i]->in) == 0)
		{
			q.push(next[i]);
		}
	}
}

Term::Term()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			isAvaiavle[i][j] = true;
			termTable[i][j] = "无";
		}
	}
}

Term::~Term()
{
	delete[] buffer;
}

bool Term::addCourse(Course * c)
{
	if (isFull() || classHour + c->classHours > 50)
	{
		return false;
	}
	else
	{
		buffer[presentClass++] = c;
		classHour += c->classHours;
		return true;
	}
}

bool Term::isFull()
{
	return presentClass == courseNum;
}

void Term::arrange()
{
	int i, j;
	for (i = 0; i < courseNum; i++)
	{
		auto course = buffer[i];
		int hours = course->classHours;
		int one = 0, two = 0, three = 0;
		bool isScheduled[5] = { false,false,false,false,false };
		while (hours > 0)
		{
			if (hours % 3 == 0)
			{
				three++;
				hours -= 3;
			}
			else if (hours % 2 == 1)
			{
				if (hours >= 3)
				{
					three++;
					hours -= 3;
				}
				else
				{
					one++;
					hours -= 1;
				}
			}
			else
			{
				two += hours / 2;
				hours = 0;
			}
		}
		if (one + two + three > 5)
		{
			cout << "某节课课时过多，排不开课" << endl;
			system("pause");
			exit(-1);
		}
		while (three || two || one)
		{
			bool isVisited[5] = { false,false,false,false,false };
			int count = 5;
			if (three)
			{
				for (j = 0; count > 0; j %= 5)
				{
					if (isScheduled[j])
					{
						isVisited[j] = true;
						j += 2;
						count--;
						continue;
					}
					if (isVisited[j])
					{
						j++;
						continue;
					}
					isVisited[j] = true;
					if (isAvaiavle[j][1])
					{
						isScheduled[j] = true;
						isAvaiavle[j][1] = false;
						termTable[j][2] = course->m_name;
						termTable[j][3] = course->m_name;
						termTable[j][4] = course->m_name;
						three--;
						break;
					}
					if (isAvaiavle[j][3])
					{
						isScheduled[j] = true;
						isAvaiavle[j][3] = false;
						termTable[j][7] = course->m_name;
						termTable[j][8] = course->m_name;
						termTable[j][9] = course->m_name;
						three--;
						break;
					}
					count--;
					j++;
				}
				if (count == 0)
				{
					three--;
					two++;
					one++;
					if (one == 2)
					{
						one = 0;
						two++;
					}
				}
			}
			else if (two)
			{
				for (j = 0; count > 0; j %= 5)
				{
					if (isScheduled[j])
					{
						isVisited[j] = true;
						j += 2;
						count--;
						continue;
					}
					if (isVisited[j])
					{
						j++;
						continue;
					}
					isVisited[j] = true;
					if (isAvaiavle[j][0])
					{
						isScheduled[j] = true;
						isAvaiavle[j][0] = false;
						termTable[j][0] = course->m_name;
						termTable[j][1] = course->m_name;
						two--;
						break;
					}
					if (isAvaiavle[j][1])
					{
						isScheduled[j] = true;
						isAvaiavle[j][1] = false;
						termTable[j][2] = course->m_name;
						termTable[j][3] = course->m_name;
						two--;
						break;
					}
					if (isAvaiavle[j][2])
					{
						isScheduled[j] = true;
						isAvaiavle[j][2] = false;
						termTable[j][5] = course->m_name;
						termTable[j][6] = course->m_name;
						two--;
						break;
					}
					if (isAvaiavle[j][3])
					{
						isScheduled[j] = true;
						isAvaiavle[j][3] = false;
						termTable[j][7] = course->m_name;
						termTable[j][8] = course->m_name;
						two--;
						break;
					}
					count--;
				}
				if (count == 0)
				{
					cout << "某节课课时过多，排不开课" << endl;
					system("pause");
					exit(-1);
				}
			}
			else
			{
				for (j = 0; count > 0; j %= 5)
				{
					if (isScheduled[j])
					{
						isVisited[j] = true;
						j += 2;
						count--;
						continue;
					}
					if (isVisited[j])
					{
						j++;
						continue;
					}
					isVisited[j] = true;
					if (isAvaiavle[j][0])
					{
						isScheduled[j] = true;
						isAvaiavle[j][0] = false;
						termTable[j][0] = course->m_name;
						one--;
						break;
					}
					if (isAvaiavle[j][1])
					{
						isScheduled[j] = true;
						isAvaiavle[j][1] = false;
						termTable[j][2] = course->m_name;
						one--;
						break;
					}
					if (isAvaiavle[j][2])
					{
						isScheduled[j] = true;
						isAvaiavle[j][2] = false;
						termTable[j][5] = course->m_name;
						one--;
						break;
					}
					if (isAvaiavle[j][3])
					{
						isScheduled[j] = true;
						isAvaiavle[j][3] = false;
						termTable[j][7] = course->m_name;
						one--;
						break;
					}
					count--;
				}
				if (count == 0)
				{
					cout << "某节课课时过多，排不开课" << endl;
					system("pause");
					exit(-1);
				}

			}
		}
	}
}

void Schedule::arrange()
{
	int term = 0;
	bool isError = false;
	while (term < 8)
	{
		if (checkReady.empty())
		{
			cout << "课程循环依赖！" << endl;
			isError = true;
			break;
		}
		auto course = checkReady.front();
		if (singleTerm[term].addCourse(course))
		{
			checkReady.pop();
		}
		else
		{
			int i = term + 1;
			while (i < 8)
			{
				if (singleTerm[i].addCourse(course))
				{
					checkReady.pop();
					break;
				}
				else
				{
					i++;
				}
			}
			if (i == 8)
			{
				cout << "无法排开课" << endl;
				isError = true;
				break;
			}
		}
		if (singleTerm[term].isFull())
		{
			singleTerm[term].arrange();
			for (int i = 0; i < singleTerm[term].courseNum; i++)
			{
				singleTerm[term].buffer[i]->delOut(checkReady);
			}
			term++;
		}
	}
	if (isError)
	{
		cout << "无法正常排课" << endl;
		system("pause");
		exit(-1);
	}
}

int main()
{
	fstream in, out;
	in.open("in.txt", ios_base::in | ios_base::binary);
	out.open("out.txt", ios_base::out | ios_base::binary);
	if (in.is_open() == false || out.is_open() == false)
	{
		cout << "文件打开失败，请检查文件是否正确命名！" << endl;
		system("pause");
		return 0;
	}

	int classnum, i, j, k;
	in >> classnum;
	Schedule scheduleTable(classnum);
	int sum = 0;
	for (i = 0; i < 8; i++)
	{
		in >> scheduleTable.singleTerm[i].courseNum;
		sum += scheduleTable.singleTerm[i].courseNum;
		scheduleTable.singleTerm[i].buffer = new Course*[scheduleTable.singleTerm[i].courseNum];

	}
	while (in.get() != '\n') continue;
	if (sum != classnum)
	{
		cout << "输入出错，请检查文件" << endl;
		system("pause");
		return 0;
	}



	for (i = 0; i < classnum; i++)
	{
		string s, courseNum, pre;
		getline(in, s);
		stringstream SS(s);
		SS >> courseNum;
		Course& c = scheduleTable.courses[courseNum];
		c.m_number = courseNum;
		SS >> c.m_name >> c.classHours >> c.openTerm;
		if (c.openTerm)
		{
			if (scheduleTable.singleTerm[c.openTerm - 1].addCourse(&c))
			{
				continue;
			}
			else
			{
				cout << "无法正常排课" << endl;
				system("pause");
				return 0;
			}
		}
		while (SS >> pre)
		{
			scheduleTable.courses[pre].addNext(&c);
			c.in++;
		}
		if (c.in == 0)
		{
			scheduleTable.checkReady.push(&c);
		}
	}
	in.close();

	scheduleTable.arrange();

	for (i = 0; i < 8; i++)
	{
		out << "第" << i + 1 << "学期课表为:" << endl;
		out << "           周一      周二      周三      周四      周五" << endl;
		for (j = 0; j < 10; j++)
		{
			out << "第" << j + 1 << "节" << "    ";
			for (k = 0; k < 5; k++)
			{
				out << scheduleTable.singleTerm[i].termTable[k][j] << "  ";
			}
			out << endl;
		}
	}
	out.close();
	cout << "课表已安排完毕" << endl;
	system("pause");
	return 0;
}
