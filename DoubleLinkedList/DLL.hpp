#ifndef DLL_HPP
#define DLL_HPP
#include "Node.hpp"

// double linked list template class
template<typename T>
class DLL {
private:
	Node<T> *front; // points to start/front/head of list
	Node<T> *back; // points to end/back of list

public:
	// constructor
	DLL() {
		front = nullptr;
		back = nullptr;
	}

	// basic double linked list functions
	void insertAtFront(T d);
	void insertAtBack(T d);
	void deleteAtFront();
	void deleteAtBack();
	void print();
};

// insert node at front of list
template<typename T>
void DLL<T>::insertAtFront(T d) {
	// if list is empty
	if(front == nullptr) {
		Node<T> *temp= new Node<T>(d); // create a new node with data of value d
		front = temp; // set front and back to temp (only one node in list)
		back = temp;
	}

	else {
		Node<T> *temp = new Node<T>(d); // this will be inserted at front
		temp->setNext(front); // point temp's next to front
		front->setPrev(temp); // front's prev should point to temp (not nullptr anymore)
		front = temp; // reset front to point to temp
	}
}

// inserts node at the back of list
template<typename T>
void DLL<T>::insertAtBack(T d) {
	// if list is empty, just user insertAtFront() function
	if(front == nullptr) {
		insertAtFront(d);
	}

	else {
		Node<T> *temp = new Node<T>(d); // this node will be inserted at back
		temp->setPrev(back); // point temp's prev to back
		back->setNext(temp); // back's next should point to temp
		back = temp; // reset back to point to temp
	}
}

// delete node at front of list
template<typename T>
void DLL<T>::deleteAtFront() {
	if(front == nullptr) {
		return; // cannot delete empty list
	}

	Node<T> *temp = front; // make another pointer that also points to front
	temp->getNext()->setPrev(nullptr); // front's next node prev should point to nullptr
	front = temp->getNext(); // point front to its next node
	delete temp; // then delete temp
}

// delete node at back of list
template<typename T>
void DLL<T>::deleteAtBack() {
	if(front == nullptr) {
		return; // cannot delte empty list
	}

	Node<T> *temp = back; // make a pointer that points to back
	back->getPrev()->setNext(nullptr); // make second to last node point to nullptr instead of back
	back = temp->getPrev(); // point back to its prev node
	delete temp; // then delete temp
}

// prints out the data of each node
template<typename T>
void DLL<T>::print() {
	if(front == nullptr) {
		return; // cannot print empty list
	}

	Node<T> *ptr = front; // create a ptr to front
	while(ptr != nullptr) {
		std::cout << ptr->getData() << " "; // print out data
		ptr = ptr->getNext(); // move ptr to next node
	}
}

#endif