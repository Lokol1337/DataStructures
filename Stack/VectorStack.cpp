#pragma once
#include "VectorStack.h"

VectorStack::VectorStack() {}

void VectorStack::push(const ValueType& value) {
	pushBack(value);
}

void VectorStack::pop() {
	popBack();
}

const ValueType& VectorStack::top() const {
	return (*this)[size() - 1];
}

bool VectorStack::isEmpty() const {
	if (this->MyVector::size() == 0)
		return true;
	return false;
}

size_t VectorStack::size() const {
	return MyVector::size();
}


