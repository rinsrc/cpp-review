#ifndef SLL_HPP
#define SLL_HPP
#include "Node.hpp"
#include <iostream>

// template single linked list class
template<typename T>
class SLL {
private:
	Node<T> *front; // front or head of the list

public:
	// constructor
	SLL() {
		front = nullptr;
	}

	// destructor
	~SLL() {
		Node<T> *temp;
		Node<T> *frontPtr = front;
		
		// delete each node in list
		while(frontPtr != nullptr) {
			temp = frontPtr;
			frontPtr = frontPtr->getNext();
			delete temp;
		}

		std::cout << "List is deleted." << std::endl;
	}

	// some basic single linked list functions, implemented below
	void insertAtFront(T d);
	void deleteAtFront();
	void insertAtBack(T d);
	void deleteAtBack();
	void print();
};

// inserts data to front of list
template<typename T>
void SLL<T>::insertAtFront(T d) {
	// if list is initially empty
	if(front == nullptr) {
		// create a new node and assign its value and next pointer
		Node<T> *temp = new Node<T>(d, nullptr);
		front = temp; // point front to temp instead of nullptr
	}

	else {
		Node<T> *temp = new Node<T>(d, front);
		front = temp;
	}
}

// deletes node at front of list
template<typename T>
void SLL<T>::deleteAtFront() {
	if(front == nullptr) {
		return; // cannot delete empty list
	}

	Node<T> *temp = front; // create a node that points to front
	front = front->getNext(); // move front to front's next
	delete temp; // delete temp, which is the front
}

template<typename T>
void SLL<T>::insertAtBack(T d) {
	// if list is empty, just use insertAtFront function
	if(front == nullptr) {
		insertAtFront(d);
	}

	else {
		Node<T> *lastNode = front;
		// traverse list to the end
		while(lastNode->getNext() != nullptr) {
			lastNode = lastNode->getNext();
		}
		// make new node at end; assign d to data and nullptr to next
		Node<T> *temp = new Node<T>(d, nullptr);
		lastNode->setNext(temp); // change lastNode's next to the new node, temp
	}
}

// deletes the node at the back of the list
template<typename T>
void SLL<T>::deleteAtBack() {
	if(front == nullptr) {
		return; // cannot delete empty list
	}

	// create two pointers: one that points to last node
	// and one that points to second to last node
	Node<T> *lastNode = front;
	Node<T> *secondToLastNode = lastNode;
	// traverse list using loop to
	while(lastNode->getNext() != nullptr) {
		secondToLastNode = lastNode;
		lastNode = lastNode->getNext();
	}

	delete lastNode;
	secondToLastNode->setNext(nullptr);
}

// prints out the data of each node
template<typename T>
void SLL<T>::print() {
	if(front == nullptr) {
		return; // cannot print an empty list
	}

	Node<T> *ptr = front; // create a ptr to front
	while(ptr != nullptr) {
		std::cout << ptr->getData() << " "; // print out data
		ptr = ptr->getNext(); // move ptr to next node
	}
}

#endif
