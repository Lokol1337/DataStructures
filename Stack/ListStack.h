﻿#pragma once

#include "StackImplementation.h"
#include "LinkedList.h"
 // меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListStack : public StackImplementation, public LinkedList
{

	public:
		ListStack();
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
};

