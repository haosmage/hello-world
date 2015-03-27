#pragma once
#pragma once
#include<iostream>
#include<new>
#include<string>

using namespace std;

/// целта е да изискам от темплейтния клас  да има подразбиращ  конструктор, деструктор оператор =
/// при копиране на вектора ако повече от 3/4 ще заделяме още памет за да го разширим 
/// при махане на елемент, при под 20% от общия размер свиваме вектора.
const double CAPACITY_BOUND = 0.8;
const double VECTOR_ALLOC_COEF = 2.0;
const double VECTOR_DEALOC_COEF = 0.20;

template <class T >
class Vector2
{
private:
	T * _data;
	size_t _size;
	size_t _maxPositions;

public:

	void push_back(const T& obj);

	void operator delete[](void * ptr);

	void pop_back();

	Vector2(size_t size = 4)
	{
		cout << "simple Vector Constructor" << endl;
		//заделяме памет без контруктор
		_data = static_cast<T*> (operator new (sizeof(T)*size));
		_size = 0;
		_maxPositions = size;
	}

	~Vector2()
	{
		if (_data)
		{
			cout << "Vector destructor" << endl;
			///вектора може да е частично запълнен с елементи а останалата част да не някаква памет, затова извикваме деструкторите 
			for (int i = 0; i < _size; ++i)
				_data[i].~T();
			//освобождаваме паметта без да викаме деструктор
			if (_data)
				operator delete(_data);
		}
	}

	Vector2(const Vector2<T> & other)
	{
		cout << " Vector Copy Constructor" << endl;
		copy_helper(other, nullptr);
	}

	void copy_helper(const Vector2<T> & other, T * data)
	{
		this->_size = other._size;
		// Заделяме повече памет ако повече от CAPACITY_BOUND% от възможните са запълнени без да викаме конструктор
		if (_size > other._maxPositions * CAPACITY_BOUND)
		{
			if (data)//for operator =
				operator delete(_data);
			_maxPositions = floor(sqrt(VECTOR_ALLOC_COEF) * _size);
			//bug all data is at the same pointer breakpoint

			this->_data = static_cast<T*> (operator new (sizeof(T) * _maxPositions));
		}
		else
		{
			_maxPositions = other._maxPositions;
			if (data)
				_data = (T*)data;
			else
				_data = static_cast<T*> (operator new (sizeof(T)*_maxPositions));
		}
		/// инициализират се чрез конструктор за копие
		for (int i = 0; i < _size; ++i)
		{
			new (_data + i) T();
			_data[i] = other._data[i];
		}

	}

	void printData()
	{
		for (int i = 0; i < _size; ++i)
			cout << _data[i] << endl;
	}


	Vector2<T> & operator= ( const Vector2<T> & other)
	{
 		cout << "Vector operator =" << endl;
		if (this != &other)
		{
			for (int i = 0; i < _size; ++i)
				_data[i].~T();
			//operator delete(_data, );
			copy_helper(other, _data);
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

	//void operator delete(void * ptr);
};

//for debug
//template<class T>
//void Vector<T>::operator delete(void * ptr)
////void operator delete[](void * ptr)
//{
//	cout << "operator delete[]" << endl;
//	//leak ?!
//	free(ptr);
//}

template<class T>
void Vector2<T>::push_back(const T& obj)
{
	cout << "push operation ";
	if (_size + 1 <= _maxPositions)
	{
		cout << "push single element" << endl;
		// копиращ конструктор
		//new (_data + _size) T(obj);
		new (_data + _size) T();
		_data[_size] = obj;
	}
	else
	{
		cout << "push single element with resize!" << endl;
		_maxPositions = floor(sqrt(VECTOR_ALLOC_COEF) * _maxPositions);
		//заделяме паметта
		T * newdata = (T*)operator new (_maxPositions * sizeof(T));
		for (unsigned int i = 0; i < _size; ++i)
		{
			//използване на копиращ конструктор
			//new (newdata + i) T(_data[i]);
			new (newdata + _size) T();
			newdata[i] = obj;
		}
		operator delete(_data);
		_data = newdata;
		//new (_data + _size) T(obj);
		new (_data + _size) T();
		_data[_size] = obj;
	}
	++_size;
}


template<class T>
void Vector2<T>::pop_back()
{
	cout << "pop operation ";
	if (_size == 0)
		return;
	if ((_size - 1) < VECTOR_DEALOC_COEF * _maxPositions)
	{
		cout << "with resize" << endl;
		_maxPositions = _maxPositions / 2;
		// намаляме размера на половина
		T * newdata = (T*) operator new (_maxPositions * sizeof(T));;
		for (size_t i = 0; i < _size - 1; ++i)
		{
			//new (newdata + i) T(_data[i]);
			new (newdata + _size) T();
			newdata[i] = _data[i];
			_data[i].~T();
		}
		//освобождаваме паметта която сме заделили за старата дата
		operator delete(_data);
		_data = newdata;
	}
	else
	{
		cout << "normal" << endl;
		//само деструктор памметта си остава, иначе дупка!
		_data[_size - 1].~T();
	}
	--_size;
}
/*template<class T> семерджиев каза нещо такова за << а[]
T& operator T()
{
return _data[index];
}*/
