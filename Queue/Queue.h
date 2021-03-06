#pragma once
#include <cstddef>

// Уровень абстракции
// клиентский код подключает именно этот хедер

// тип значений в стеке
using ValueType = double;

// на основе какого контейнера работает стек
enum class QueueContainer {
	Vector = 0,
	SinglyLinkedList,
	DoubleLinkedList,
	// можно дополнять другими контейнерами
};

// декларация класса с реализацией
class QueueImplementation;

class Queue
{
public:
	// Большая пятерка
	Queue(QueueContainer container = QueueContainer::SinglyLinkedList);
	// элементы массива последовательно подкладываются в стек
	Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container = QueueContainer::Vector);

	Queue(const Queue& copyStack);
	Queue& operator=(const Queue& copyStack);

	// Здесь как обычно
	Queue(Queue&& moveStack) noexcept;
	Queue& operator=(Queue&& moveStack) noexcept;

	~Queue();

	// добавление в хвост
	void enqueue(const ValueType& value);
	// удаление с хвоста
	//void realdequeue();
	void dequeue();
	// посмотреть элемент в хвосте
	const ValueType& front() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;

private:
	// указатель на имплементацию (уровень реализации)
	QueueImplementation* _pimpl = nullptr;
	// тип контейнера, наверняка понадобится
	QueueContainer _containerType;
};

