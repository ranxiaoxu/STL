#pragma once
#include"List.h"
#include"Vector.h"

struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template <class Category, class T, class Distance = ptrdiff_t ,class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category IteratorCategory;
	typedef T ValueType;
	typedef Distance DifferenceType;   //两个迭代器之间的距离，为什么要有这个？？
	typedef Pointer Pointer; 
	typedef Reference Reference; 
};

//特性萃取机
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator:: IteratorCategory IteratorCategory ;
	typedef typename Iterator:: ValueType ValueType;
	typedef typename Iterator:: DifferenceType DifferenceType ;
	typedef typename Iterator:: Pointer Pointer;
	typedef typename Iterator:: Reference Reference;
};

// 偏特化原生指针类型
template <class T>
struct IteratorTraits< T*>
{
	typedef RandomAccessIteratorTag IteratorCategory ;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType ;
	typedef T * Pointer;
	typedef T & Reference;
};

// 偏特化const原生指针类型
template <class T>
struct IteratorTraits<const T *>
{
	typedef RandomAccessIteratorTag IteratorCategory ;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType;
	typedef const T* Pointer;
	typedef const T& Reference;
};

//Distance的实现
template <class InputIterator>
inline typename IteratorTraits <InputIterator>:: DifferenceType
Distance (InputIterator first, InputIterator last)
{
	return _Distance (first, last, IteratorTraits <InputIterator>:: IteratorCategory());
}

//对于双向迭代器
template <class InputIterator>
inline typename IteratorTraits <InputIterator>:: DifferenceType 
	_Distance (InputIterator first, InputIterator last, InputIteratorTag )
{
	IteratorTraits<InputIterator >::DifferenceType count = 0;
	while (first != last) 
	{
		++ first; 
		++count;
	}
	return n ;
}
//对于随机访问迭代器
template <class RandomAccessIterator>
inline typename IteratorTraits <RandomAccessIterator>:: DifferenceType 
	_Distance (RandomAccessIterator first, RandomAccessIterator last,RandomAccessIteratorTag)
{
	return last - first;
}

// Advance（前进） 的实现
template <class InputIterator, class Distance>
inline void Advance(InputIterator & i, Distance n)
{
	_Advance(i , n, IteratorTraits <InputIterator>:: IteratorCategory());
}

//对于前向迭代器
template <class InputIterator, class Distance>
inline void _Advance(InputIterator & i, Distance n, InputIteratorTag )
{
	while(n --) 
		++i;
}
//对于双向迭代器
template <class BidirectionalIterator, class Distance>
inline void _Advance(BidirectionalIterator & i, Distance n ,BidirectionalIteratorTag )
{
	if (n >= 0)
	{
		while(n--) 
			++i;
	}else{
		while(n++) 
			--i;
	}
}
//对于随机迭代器
template <class RandomAccessIterator, class Distance>
inline void _Advance(RandomAccessIterator & i, Distance n ,RandomAccessIteratorTag)
{
	i += n ;
}

void test()
{
	//_List<int> l;
	//l.PushBack(1);
	//l.PushBack(2);
	//l.PushBack(3);
	//l.PushBack(4);
	//l.PushBack(5);
	//cout<<Distance(l.Begin(),l.End())<<endl;

	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	cout<<Distance(v.Begin(),v.End())<<endl;
}