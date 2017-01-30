#ifndef SLL_QUEUE_HPP
#define SLL_QUEUE_HPP

#include "SLL.hpp" // include single linked list

// template queue implementation of queue using single linked list
// queue is FIFO (First In First Out), like a cafeteria line
template<typename T>
class SLLQueue {
private:
	SLL<T> *q;

public:
	// constructor
	SLLQueue() {
		q = new SLL<T>();
	}

	// destructor
	~SLLQueue() {
		delete q;
	}

	// basic functions
	void enqueue(T d);
	void dequeue();
	void print();

};

// enqueue is like pushing a node into the list
template<typename T>
void SLLQueue<T>::enqueue(T d) {
	q->insertAtBack(d);
}


// dequeue is like deleting the first node in list (first out)
template<typename T>
void SLLQueue<T>::dequeue() {
	q->deleteAtFront();
}

// print data of each node
template<typename T>
void SLLQueue<T>::print() {
	q->print();
}

#endif
