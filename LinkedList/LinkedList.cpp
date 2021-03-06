﻿#pragma once
#include <iostream>
#include "LinkedList.h"
#include <cassert>
//#include <utility>
//#include <execution>
#include <stdexcept>
#include <cstddef>

using namespace std;

LinkedList::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LinkedList::Node::~Node()
{
	// íè÷åãî íå óäàëÿåì, ò.ê. àãðåãàöèÿ
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;

	this->next = newNext;
}

LinkedList::LinkedList():
_head(nullptr), _size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0)
    	{
		this->_head = nullptr;
		return;
	}
    this->_head = new Node(copyList._head->value);
	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head->next;
	while (currentCopyNode)
    {
		currentNode->next = new Node(currentCopyNode->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
	if(this == &copyList)
    {
		return *this;
	}
	LinkedList* bufList = new LinkedList(copyList);
	this->_size = bufList->_size;
	forceNodeDelete(_head);
	this->_head = bufList->_head;
	return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;
	moveList._size = 0;
	moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;
	moveList._size = 0;
	moveList._head = nullptr;
	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}
	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}
	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
	}
	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos-1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
	_size++;
}

void LinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos)
{
	if (_head)
	{
		if (pos != 0)
		{
			int counter = 0;
			Node* tmp = _head;
			while (counter <= pos)
			{
				tmp = tmp->next;
				counter++;
			}
			counter = 0;
			Node* nd = _head;
			while (counter < pos - 1)
			{
				nd = nd->next;
				counter++;
			}
			_size--;
			nd->next = tmp;
		}
		else
		{
			Node* tmp = _head;
			tmp = tmp->next;
			delete _head;
			_size--;
			_head = tmp;
		}
		}
		else
			throw out_of_range("List is empty");
}

void LinkedList::removeNextNode(Node* node)
{
    Node* removeNode = node->next;
    node->next = removeNode->next;
    delete removeNode;
    removeNode = nullptr;
    _size--;
}

void LinkedList::removeFront()
{
    if(_head)
        {
            Node *tmp = _head;
            tmp = tmp->next;
            delete _head;
            _size--;
            _head = tmp;
        }
    else
        cout << "The list is empty!" << endl;
}

void LinkedList::removeBack()
{
    if (_head)
	{
		if (_size >= 2)
		{
			/* Node *tmp = _head;
			 Node *nd = _head;
			 while(tmp->next!=nullptr)
				 {
					 nd = tmp;
					 tmp = tmp->next;

				 }
			 nd->next = nullptr;

			 delete tmp;
			 _size--;*/
			Node* tmp = getNode(_size - 2);
			delete tmp->next;
			tmp->next = nullptr;
			_size--;
		}

		else if (_size == 1)
		{
			delete _head;
			_head = nullptr;
			_size--;
		}
	}
}

long long int LinkedList::findIndex(const ValueType& value) const
{
    Node* tmp = _head;
    size_t i = 0;
    size_t j = 0;
    while(i<_size)
    {
        i++;
        if(tmp->value == value)
            {
                j = i;
                i = _size;
                return j-1;
            }
        tmp = tmp->next;
    }
    if(j==0)
    {
        return 0;
    }
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
    size_t i = 0;
    int j = 0;
    Node* tmp = _head;
    while(i < _size)
    {
        i++;
        if(tmp->value == value)
        {
            i=_size;
            j=1;
            return tmp;
        }
        tmp = tmp->next;
    }
    if(j==0)
        return nullptr;
}

void LinkedList::reverse()
{
    Node *tmp = _head;
    Node *next = nullptr;
    Node *last = nullptr;
    while(tmp)
    {
        next = tmp->next;
        tmp->next = last;
        last = tmp;
        tmp = next;
       }
    _head = last;
}

LinkedList LinkedList::reverse() const
{
    if(_size==0)
    {
        return LinkedList();
    }
    else
    {
        LinkedList buf(*this);
        buf.reverse();
        return buf;
    }
}

LinkedList LinkedList::getReverseList() const
{
    LinkedList buf(*this);
    buf.reverse();
    return buf;
	//return LinkedList();
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr)
    {
		return;
	}
	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}


/*int main() {

	LinkedList a;
	a.pushBack(2);
	a.pushBack(3);
	a.pushBack(4);
	a.pushBack(5);
	LinkedList b;
	b = a;
	a.removeBack();
	a.removeBack();
	a.removeBack();
	a.removeBack();
	cout << a[2];
	cout << b[2];
	
	a.remove(1);
}*/
