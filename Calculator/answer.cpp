#include"answerh.h"

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
		expand();
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

template<class T>
T stack<T>::peek()
{
	if (m_element > 0)
	{
		return m_buffer[m_element - 1];
	}
	return T();
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

template<class T>
void stack<T>::clear()
{
	m_element = 0;
}

char PriorityTable[9][9] = {
	//            |--------------- 当前运算符---------|
	//             (	)	+	-	*	/	%	^	=    
	/* --   (  */  '<','=','<','<','<','<','<','<',' ',
	/* |     ) */  ' ',' ',' ',' ',' ',' ',' ',' ',' ',
	/* 栈   +  */  '<','>','>','>','<','<','<','<','>',
	/* 顶   -  */  '<','>','>','>','<','<','<','<','>',
	/* 运   *  */  '<','>','>','>','>','>','>','<','>',
	/* 算   /  */  '<','>','>','>','>','>','>','<','>',
	/* 符   %  */  '<','>','>','>','>','>','>','<','>',
	/* |    ^  */  '<','>','>','>','>','>','>','<','>',
	/* --   =  */  '<',' ','<','<','<','<','<','<','='
};

bool answer::checkNumber(char elem)
{
	return elem >= '0'&&elem <= '9';
}

answer::answer()
{
	numbers = new stack<long long>(100);
	operators = new stack<char>(100);
	operators->push('=');//栈底放=号用于匹配=
}

answer::~answer()
{
	delete numbers;
	delete operators;
}

bool answer::calculation()
{
	cout << "请输入一行算式" << endl;
	getline(std::cin, calc);
	long long temp = 0;
	bool single = false;
	bool isNumber = false;
	char last = '=';
	for (auto elem : calc)
	{
		if (checkNumber(elem))
		{
			if (isNumber)
			{
				if (temp == 0)
				{
					isError = true;
					break;
				}
				if (temp * 10 + elem > temp)
				{
					temp = temp * 10 + elem - '0';
				}
				else
				{
					cout << "输入数溢出" << endl;
					isError = true;
				}
			}
			else//第一次得到数字直接进入else
			{
				temp = elem - '0';
				isNumber = true;
			}//得到数字
		}
		else
		{
			if (elem != '(' && (last == '=' || last == '('))//说明为单目运算符
			{
				if (single)
				{
					isError = true;
				}
				else
				{
					if (elem == '-')
					{
						numbers->push(0);
						operators->push('-');
						single = true;
					}
					else if (elem == '+')
					{
						single = true;
					}
					else
					{
						isError = true;
					}
				}
			}
			else
			{
				if (checkNumber(last))//除前括号以外，其他运算符前应为数字
				{
					single = false;
					numbers->push(temp);
					temp = 0;
					isNumber = false;
					checkOperator(elem);
				}
				else if (elem == '(' || last == ')')//前括号前可以是符号，后括号可以视为数字但不进行数字插入
				{
					checkOperator(elem);
				}
				else
				{
					isError = true;
				}
			}
		}
		last = elem;
		if (isError)
		{
			break;
		}
		if (operators->stacklength() == 0)
		{
			break;
		}
	}
	if (!isError && numbers->stacklength() == 1 && operators->isEmpty())
	{
		cout << "计算结果为：" << numbers->pop() << endl;
	}
	else
	{
		cout << "输入的表达式不合法，请重新输入" << endl;
	}
	cout << "如需继续计算请输入y\n";
	string get;
	getline(std::cin, get);
	return get == "y";
}

void answer::checkOperator(char elem)
{
	int val1 = 0, val2 = 0;
	val1 = getValue(elem);
	if (val1 == -1)
	{
		isError = true;
		return;
	}
	val2 = getValue(operators->peek());
	while (!isError)
	{
		if (PriorityTable[val2][val1] == '<')
		{
			operators->push(elem);
			return;
		}
		else if (PriorityTable[val2][val1] == '=')
		{
			operators->pop();
			return;
		}
		else if (PriorityTable[val2][val1] == '>')
		{
			useOperator(val2);
			operators->pop();
			val2 = getValue(operators->peek());//所有正确的输入中，等号都在栈底，一定能执行peek
		}
		else//空格说明为错误的输入
		{
			isError = true;
			return;
		}
	}
}

void answer::useOperator(int op)
{
	auto right = numbers->pop(), left = numbers->pop();
	long long ans = 0;
	switch (op)
	{
	case 2:
		ans = left + right;
		if (plusCheck(ans, left, right))
		{
			numbers->push(ans);
		}
		else
		{
			cout << "加法溢出" << endl;
			isError = true;
		}
		break;
	case 3:
		ans = left - right;
		if (minusCheck(ans, left, right))
		{
			numbers->push(ans);
		}
		else
		{
			cout << "减法溢出" << endl;
			isError = true;
		}
		break;
	case 4:
		ans = left * right;
		if (mulityCheck(ans, left, right))
		{
			numbers->push(ans);
		}
		else
		{
			cout << "乘法溢出" << endl;
			isError = true;
		}
		break;
	case 5:
		if (right == 0)
		{
			cout << "禁止除零" << endl;
			isError = true;
			break;
		}
		ans = left / right;
		if (ans == LLONG_MIN && right == -1)
		{
			cout << "除法溢出" << endl;
			isError = true;
			break;
		}
		numbers->push(ans);
		break;
	case 6:
		if (right == 0)
		{
			cout << "禁止除零" << endl;
			isError = true;
			break;
		}
		numbers->push(left%right);
		break;
	case 7:
		if (right < 0)
		{
			cout << "不支持负数幂" << endl;
			isError = true;
			break;
		}
		ans = pow(left, right);
		if (powerCheck(ans, left, right))
		{
			numbers->push(ans);
		}
		else
		{
			cout << "幂运算溢出" << endl;
			isError = true;
		}
		break;
	default:
		break;
	}
}

bool answer::plusCheck(const long long & ans, const long long & left, const long long & right)
{
	auto a = left ^ right;
	auto b = left ^ ans;
	return (a < 0) || (b >= 0);//异号时一定不溢出，同号时若结果也同号则不溢出
}//正+正=正，负+负=负

bool answer::minusCheck(const long long & ans, const long long & left, const long long & right)
{
	auto a = left ^ right;
	auto b = left ^ ans;
	return (a >= 0) || (b >= 0);//同号时一定不溢出，异号时若结果与左操作数同号也不溢出
}//负-正=负，正-负=正

bool answer::mulityCheck(const long long & ans, const long long & left, const long long & right)
{
	return left == 0 || right == 0 || (ans / right == left && (ans != LLONG_MIN || right != -1));
}

bool answer::powerCheck(const long long & ans, const long long & left, const long long & right)
{
	return ((left >= 0 || right % 2 == 0) && ans >= 0) || (left < 0 && right % 2 == 1 && ans < 0);
}//正数与负数偶次方为正，负数奇次方为负

int answer::getValue(char op)
{
	switch (op)
	{
	case '(':
		return 0;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 3;
	case '*':
		return 4;
	case '/':
		return 5;
	case '%':
		return 6;
	case '^':
		return 7;
	case '=':
		return 8;
	default:
		return -1;
	}
}

void answer::clear()
{
	numbers->clear();
	operators->clear();
	operators->push('=');
	isError = false;
	calc.clear();
}

int main()
{
	answer ans;
	while (ans.calculation())
	{
		cout << "进行下一次计算" << endl;
		ans.clear();
	}
	cout << "计算结束" << endl;
	system("pause");
	return 0;
}