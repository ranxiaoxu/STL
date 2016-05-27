#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
class Vector{
public:
	typedef T ValueType;
	typedef ValueType* Iterator;

	Vector()
		:_start(NULL)
		,_finish(NULL)
		,_endofstorage(NULL)
	{}

	void PushBack(const ValueType &x)
	{
		_CheckCapacity();
		*_finish = x;
		++_finish;
	}

	void PopBack()
	{
		--_finish;
	}

	void Insert(Iterator pos,const ValueType &x) //‘⁄POS«∞≤Â»Î
	{
		assert(pos <= _finish+1);

		if(pos == _finish+1)
		{
			PushBack(x);
		}

		_CheckCapacity();
		Iterator cur = _finish;
		Iterator prev = _finish-1;
		while(cur != pos)
		{
			*cur-- = *prev--;
		}
		*cur = x;
		++_finish;
	}

	void Erase(Iterator pos)
	{
		assert(pos < _finish);

		if(pos == _finish - 1)
			PopBack();

		Iterator cur = _start;
		while(cur != pos)
		{
			cur++;
		}

		Iterator next = cur+1;
		while(next != _finish)
		{
			*cur++ = *next++;
		}
		--_finish;
	}
	Iterator Begin()
	{
		return _start;
	}
	
	Iterator End()
	{
		return _finish;
	}

	int Size()
	{
		return _finish - _start;
	}

	ValueType & operator [] (size_t index)
	{
		assert(index > -1 && index < Size())
		return _start[index];
	}


protected:
	void _CheckCapacity()
	{
		if(_finish == _endofstorage)
		{
			size_t oldstorage = _finish - _start;
			size_t storage =  oldstorage*2 + 3;

			ValueType *tmp = new ValueType[storage];

			for(int i = 0;i < oldstorage;i++)
			{
				tmp[i] = _start[i];
			}

			delete []_start;
			
			_start = tmp;
			_finish = tmp + oldstorage;
			_endofstorage = tmp + storage;
		}
	}



	Iterator _start;
	Iterator _finish;
	Iterator _endofstorage;
};


void testVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	Vector<int>::Iterator it = v.Begin();
	/*while(it != v.End())
	{	
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
	
	v.PopBack();
	v.PushBack(5);

	it = v.Begin();
	while(it != v.End())
	{	
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;*/

	v.Insert(v.Begin()+2,6);

	it = v.Begin();
	while(it != v.End())
	{	
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;

	v.Erase(v.Begin()+2);

	it = v.Begin();
	while(it != v.End())
	{	
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}