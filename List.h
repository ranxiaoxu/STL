#pragma once 
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

template<class T>
struct _ListIterator
{
	typedef _ListNode<T> Node;
	typedef Node* LinkType;
	typedef _ListIterator Self;
	
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

	T & operator *()
	{
		return _node->_data;
	}

	T *operator ->()
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
	typedef _ListIterator<T> Iterator;

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


void testList()
{
	_List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	_List<int>::Iterator it = l.Begin();
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
	cout<<endl;
}

