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
	typedef Distance DifferenceType;   //����������֮��ľ��룬ΪʲôҪ���������
	typedef Pointer Pointer; 
	typedef Reference Reference; 
};

//������ȡ��
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator:: IteratorCategory IteratorCategory ;
	typedef typename Iterator:: ValueType ValueType;
	typedef typename Iterator:: DifferenceType DifferenceType ;
	typedef typename Iterator:: Pointer Pointer;
	typedef typename Iterator:: Reference Reference;
};

// ƫ�ػ�ԭ��ָ������
template <class T>
struct IteratorTraits< T*>
{
	typedef RandomAccessIteratorTag IteratorCategory ;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType ;
	typedef T * Pointer;
	typedef T & Reference;
};

// ƫ�ػ�constԭ��ָ������
template <class T>
struct IteratorTraits<const T *>
{
	typedef RandomAccessIteratorTag IteratorCategory ;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType;
	typedef const T* Pointer;
	typedef const T& Reference;
};

//Distance��ʵ��
template <class InputIterator>
inline typename IteratorTraits <InputIterator>:: DifferenceType
Distance (InputIterator first, InputIterator last)
{
	return _Distance (first, last, IteratorTraits <InputIterator>:: IteratorCategory());
}

//����˫�������
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
//����������ʵ�����
template <class RandomAccessIterator>
inline typename IteratorTraits <RandomAccessIterator>:: DifferenceType 
	_Distance (RandomAccessIterator first, RandomAccessIterator last,RandomAccessIteratorTag)
{
	return last - first;
}

// Advance��ǰ���� ��ʵ��
template <class InputIterator, class Distance>
inline void Advance(InputIterator & i, Distance n)
{
	_Advance(i , n, IteratorTraits <InputIterator>:: IteratorCategory());
}

//����ǰ�������
template <class InputIterator, class Distance>
inline void _Advance(InputIterator & i, Distance n, InputIteratorTag )
{
	while(n --) 
		++i;
}
//����˫�������
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
//�������������
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