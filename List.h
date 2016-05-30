#pragma once 
#include"Iterator.h"
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct _ListNode{
	T _data;
	_ListNode<T>* _prev;
	_ListNode<T>* _next;

	_ListNode()
		:_prev(NULL)
		,_next(NULL)
	{}

	_ListNode(const T &x)
		:_prev(NULL)
		,_next(NULL)
		,_data(x)
	{}
};

template<class T,class Ref,class Ptr>
struct _ListIterator
{
	typedef _ListNode<T> Node;
	typedef Node* LinkType;
	typedef _ListIterator<T,Ref,Ptr> Self;
	
	typedef T ValueType;
	typedef Ref Reference;
	typedef Ptr Pointer;
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef ptrdiff_t DifferenceType ;
	
	LinkType _node;
	
	_ListIterator()
	{}

	_ListIterator(LinkType node)
		:_node(node)
	{}

	Self operator ++()
	{
		_node = _node->_next;
		return *this;
	}
	
	Self operator ++(int)
	{
		LinkType tmp(_node);
		_node = _node->_next;
		return Self(tmp);
	}

	Self operator --()
	{
		_node = _node->_prev;
		return *this;
	}
	
	Self operator --(int)
	{
		LinkType tmp(_node);
		_node = _node->_prev;
		return Self(tmp);
	}

	Reference operator *()
	{
		return _node->_data;
	}

	Pointer operator ->()
	{
		return &(_node->_data);
	}

	bool operator == (Self &it)
	{
		return _node == it._node;
	}
	
	bool operator != (Self &it)
	{
		return _node != it._node;
	}
};

template<class T>
class _List
{
	typedef _ListNode<T> Node;
	typedef Node* LinkType;
	
public:
	typedef _ListIterator<T,T&,T*> Iterator;
	typedef _ListIterator<T,const T&,const T*> ConstIterator; 
	typedef ReverseIterator<Iterator> ReverseIterator;

	_List()
		:_head(new Node())
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		return Iterator(_head->_next);
	}

	Iterator End()
	{
		return Iterator(_head);
	}

	ConstIterator Begin() const
	{
		return ConstIterator(_head->_next);	
	}

	ConstIterator End() const
	{
		return ConstIterator(_head);
	}

	ReverseIterator RBegin() 
	{ 
		return ReverseIterator(End()); 
	}

	ReverseIterator REnd() 
	{ 
		return ReverseIterator(Begin()); 
	}

	Iterator Insert(Iterator pos,const T&x)   //在POS前插入x
	{
		LinkType cur = pos._node;
		LinkType prev = pos._node->_prev;

		LinkType tmp = new Node(x);

		tmp->_next = cur;
		cur->_prev = tmp;

		prev->_next = tmp;
		tmp->_prev = prev;

		return tmp;    //发生隐式转换
	}

	void PushBack(const T& x)
	{
		Insert(End(),x); 
	}

	void PushFront(const T& x)
	{
		Insert(Begin(),x);
	}

	Iterator Erase(Iterator pos)
	{
		assert(pos != End());

		LinkType next = pos._node->_next;
		LinkType prev = pos._node->_prev;
		LinkType del = pos._node;

		prev->_next = next;
		next->_prev = prev;

		delete del;

		return next;
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}
private:
	LinkType _head;
};

void PrintList(const _List<int> &l)
{
	_List<int>::ConstIterator it = l.Begin();
	while(it != l.End())
	{
		//*it = 10;
		cout<<*it<<endl;
		it++;
	}
	cout<<endl;

}
void testList()
{
	_List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	/*_List<int>::Iterator it = l.Begin();
	while(it != l.End())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;

	l.PopBack();
	l.PopFront();
	it = l.Begin();
	while(it != l.End())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;*/
	PrintList(l);
}
void testReverseIterator()
{
	_List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	_List<int>::ReverseIterator it = l.RBegin();
	while(it != l.REnd())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}
