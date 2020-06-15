#pragma once
#include "ListStack.h"

ListStack::ListStack() {}

void ListStack::push(const ValueType& value) {
	pushFront(value);
}

void ListStack::pop() {
	this->removeFront();
}
const ValueType& ListStack::top() const{
	return getNode(0)->value;
}
bool ListStack::isEmpty() const {
	if (LinkedList::size() == 0)
		return true;
	return false;
}
size_t ListStack::size() const {
	return this->LinkedList::size();
}