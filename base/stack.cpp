#include"stack.h"

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