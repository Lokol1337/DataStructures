#pragma once

#include "QueueImplementation.h"
#include "DoubleLinkedList.h"
#include <cstddef>
// ������� �� include ������ �����

// ������� � �������������� ����� ����������� ������ � �������������� ������������
// ���� �� ������ �� ��� ����������, �� ���� �� ������������ ������ �� ����������
// ������������� ������������ ����� �������� �� ����������
class DoubleListQueue : public QueueImplementation, public LinkedList2
{

public:
	DoubleListQueue();


	void enqueue(const ValueType& value);
	// �������� � ������
	void dequeue();
	// ���������� ������� � ������
	const ValueType& front() const;

	// �������� �� �������
	bool isEmpty() const;
	// ������ 
	size_t size() const;
};
