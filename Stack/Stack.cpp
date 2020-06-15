#pragma once
#include "Stack.h"
#include "StackImplementation.h"
#include "VectorStack.h"
#include "ListStack.h"
#include <iostream>
#include <stdexcept>

Stack::Stack(StackContainer container)
	: _containerType(container)
{
	switch (container) 

	{
	case StackContainer::List: {
		_pimpl = new ListStack();	// конкретизируйте под ваши конструкторы, если надо
		break;	
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)

    : _containerType(container)
    {
    switch (container)
    {
        case StackContainer::List: {
			_pimpl = new ListStack();// конкретизируйте под ваши конструкторы, если надо
        break;
       }

        case StackContainer::Vector: {
			_pimpl = new VectorStack(); // конкретизируйте под ваши конструкторы, если надо
        break;
        }
		
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
	for (size_t i = 0; i < arraySize; i++)
	{
		_pimpl->push(valueArray[i]);
	}
    }


Stack::Stack(const Stack& copyStack)
{
	_containerType = copyStack._containerType;
	switch (_containerType)
	{
	case StackContainer::List: {
		_pimpl = new ListStack(*(static_cast<ListStack*>(copyStack._pimpl)));	
		break;
	}
	case StackContainer::Vector: {
		_pimpl = new VectorStack(*(static_cast<VectorStack*>(copyStack._pimpl)));	
		break;
	}
	default:
		throw std::runtime_error("Unknown type");
	}// конкретизируйте под ваши конструкторы, если надо
}

Stack& Stack::operator=(const Stack& copyStack) {
	if (this->_pimpl == copyStack._pimpl)
	{
		return *this;
	}
	else
	{
		int copySize = copyStack.size();
		delete _pimpl;
		if (copyStack._containerType == StackContainer::List)
		{
			_pimpl = new ListStack();// конкретизируйте под ваши конструкторы, если надо
		}
		if (copyStack._containerType == StackContainer::Vector)
		{
			_pimpl = new VectorStack();    // конкретизируйте под ваши конструкторы, если надо
		}
		ValueType* array = new ValueType[copySize];
		for (int i = copySize - 1; i >= 0; i--) {
			array[i] = copyStack._pimpl->top();
			copyStack._pimpl->pop();
		}
		for (int i = 0; i < copySize; i++) {
			_pimpl->push(array[i]);
			copyStack._pimpl->push(array[i]);
		}
		delete[] array;
		return *this;
		// TODO: вставьте здесь оператор return
	}
}

Stack::~Stack()
{
	delete _pimpl;		// композиция!
}

void Stack::push(const ValueType& value)
{
	// можно, т.к. push определен в интерфейсе
	_pimpl->push(value);
}

void Stack::pop()
{
	_pimpl->pop();
}

const ValueType& Stack::top() const
{
	return _pimpl->top();
}

bool Stack::isEmpty() const
{
	return _pimpl->isEmpty();
}

size_t Stack::size() const
{
	return _pimpl->size();
}

/*int main() {
	Stack s1(StackContainer::List);
	s1.push(1);
	s1.push(2);
	s1.push(3);
	ValueType* a = new ValueType[5];
	for(int i = 0; i < 5; i++)
	{
		a[i] = i;
	}
	Stack s2;
	s2 = s1;
	size_t b = s2.size();
	size_t c = s1.size();
	for (int i = 0; i < b; i++)
	{
		std::cout << s2.top();
		s2.pop();
	}
	std::cout << std::endl;
	for (int i = 0; i < c; i++)
	{
		std::cout << s1.top();
		s1.pop();
	}
	return 0;
}*/