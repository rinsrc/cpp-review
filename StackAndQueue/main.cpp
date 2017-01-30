#include "Stack.hpp"
#include <iostream>

#include "SLLStack.hpp"
#include "SLLQueue.hpp"

int  main() {
	// create a stack of integers
	SLLStack<int> *myStack = new SLLStack<int>();
	
	// push some integers into stack
	for(int i = 0; i < 10; i++) {
		myStack->push(i);
	}

	// print stack
	std::cout << "Original stack: " << std::endl;
	myStack->print();

	// pop two numbers from top of stack
	std::cout << std::endl << std::endl << "Pop twice from top of stack: " << std::endl;
	myStack->pop();
	myStack->pop();
	myStack->print();
	
	// create a queue of integers
	SLLQueue<int> *myQueue = new SLLQueue<int>();
	
	// enqueue integers into the queue
	for(int i = 0; i < 10; i++) {
		myQueue->enqueue(i);
	}

	// print queue
	std::cout << std::endl << std::endl << "Original queue: " << std::endl;
	myQueue->print();

	// dequeue two items from queue and print
	std::cout << std::endl << std::endl << "Dequeued two items from original queue: " << std::endl;
	myQueue->dequeue();
	myQueue->dequeue();
	myQueue->print();

	return 0;
}
