//Vector.h
#pragma once
#include<iostream>
#include<new>

using namespace std;

/// целта е да изискам от темплейтния клас  да има подразбиращ се конструктор, деструктор и оператор = (не изисквам копиращ конструктор)
/// при копиране на вектора ако повече от 3/4 ще заделяме още памет за да го разширим 
/// при махане на елемент, при под 20% от общия размер свиваме вектора.
const double CAPACITY_BOUND = 0.8;
const double VECTOR_ALLOC_COEF = 2.0;
const double VECTOR_DEALOC_COEF = 0.20;

template <class T >
class Vector
{
private:
	T * _data;
	size_t _size;
	size_t _maxPositions;

public:

	void push_back(const T& obj);

	void operator delete[](void * ptr);

	void pop_back();

	Vector(int size = 4)
	{
		cout << "simple Vector Constructor" << endl;
		_data = static_cast<T*> (::operator new (sizeof(T[5]))); //заделяме памет без контруктор
		_size = 0;
		_maxPositions = size;
	}

	~Vector()
	{
		/// alp izcqlo e zapulneno da se izvika delete [] ako ne e zapulneno izcqlo da se izvika destr i posle operator delete 
		cout << "Vector destructor" << endl;
		for (int i = 0; i < _size; ++i)
			_data[i].~T();
		delete[] _data;
	}

	Vector(const Vector<T> & other)
	{
		cout << " Vector Copy Constructor" << endl;
		copy_helper(other);
	}

	void copy_helper(const Vector<T> & other)
	{
		this->_size = other._size;
		// Заделяме повече памет ако повече от 80% от възможните са запълнени
		if (_size > other._maxPositions * CAPACITY_BOUND)
		{
			_maxPositions = floor(sqrt(VECTOR_SHRINK_COEF) * _size);
			_data = new[_maxPositions];
		}
		else
		{
			_maxPositions = other._maxPositions;
			_data = new[_maxPositions];
		}

		for (int i = 0; i < _size; ++i)
			this->_data[i] = other._data[i];/// изисквам оператор =
	}

	void printData()
	{
		for (int i = 0; i < _size; ++i)
			cout << _data[_size] << endl;
	}
	/*template<class T> kak da go napravq
	T& operator T()
	{
	return _data[index];
	}*/


	template <class T>
	T& operator= (const Vector<T> & other)
	{
		cout << "Vector operator =" << endl;
		if (this != other)
		{
			copy_helper(other);
		}
		return *this;
	}


	T& operator[](unsigned int index)
	{
		cout << "vector operator []" << endl;
		return _data[index];
	}

	size_t size()
	{
		return _size;
	}
};

template<class T>
void Vector<T>::operator delete[](void * ptr)
//void operator delete[](void * ptr)
{
	cout << "operator delete[]" << endl;
	//delete ptr;
	free(ptr);
}

template<class T>
void Vector<T>::push_back(const T& obj)
{
	cout << "push operation ";
	if (_size + 1 < _maxPositions)
	{
		cout << "push single element" << endl;
		new (_data + _size)T(obj);// използвам подразбиращ се конструктор и оператор =
		//_data[_size].T();
		//_data[_size] = obj;
	}
	else
	{
		cout << "push single element with resize!" << endl;
		_maxPositions = floor(sqrt(VECTOR_ALLOC_COEF) * _maxPositions);
		T * newdata = (T*)operator new (_maxPositions * sizeof(T)); // samo zadelqme pametta
		for (unsigned int i = 0; i < _size; ++i)
		{
			newdata[i]= _data[i];
		}
		delete[] _data;
		_data = newdata;
		_data[_size] = obj;
	}
	
	++_size;
}


template<class T>
void Vector<T>::pop_back()
{
	cout << "pop operation ";
	if (_size == 0)
		return;
	if ((_size - 1) < VECTOR_DEALOC_COEF * _maxPositions)
	{
		cout << "with resize" << endl;
		T * newdata = new T[_maxPositions / 2]; // намаляме размера на половина
		for (int i = 0; i < _size - 1; ++i)
		{
			newdata[i] = _data[i];
			_data[i].~T();
		}

		delete[] _data;// ako ne e suvsem pulna ?! placement delete?
		_data = newdata;
	}
	else
	{
		cout << "normal" << endl;
		_data[_size - 1].~T();//само деструктор памметта си остава
	}
	--_size;
	++_maxPositions;
}


----///// main.cpp
#include "Vector.h"

int main()
{ 
	{
		Vector<int> a;
		int a1 = 0;
		a.push_back(a1);
		a.push_back(3);
		a.printData();
		

		

		a.pop_back();
		a.pop_back();
		a.pop_back(); 
		a.pop_back();
		
		for (unsigned int i = 0; i < a.size(); ++i)
		{
			a1 = a[i];

			cout << a1 << endl;
		}
		
				
	}

	cout << sizeof(double[12]);
	return 0;
}









