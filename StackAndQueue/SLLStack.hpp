#ifndef SLL_STACK_HPP
#define SLL_STACK_HPP

#include "SLL.hpp" // include single linked list class

// template stack implementation using single linked list
// stack is FILO (First In Last Out)
template<typename T>
class SLLStack {
private:
	SLL<T> *s;
public:
	// constructor
	SLLStack() {
		s = new SLL<T>();	
	}

	// destructor
	~SLLStack() {
		delete s; // destroy the list
	}
	
	// basic stack functions
	void push(T d);
	void pop();
	void print();
};

// push inserts node at back of list
template<typename T>
void SLLStack<T>::push(T d) {
	s->insertAtBack(d);
}

// pop deletes node at back of list
template<typename T>
void SLLStack<T>::pop() {
	s->deleteAtBack();
}

// prints stack
template<typename T>
void SLLStack<T>::print() {
	s->print();
}

#endif
