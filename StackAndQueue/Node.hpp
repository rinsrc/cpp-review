#ifndef NODE_HPP
#define NODE_HPP

// template node class for singly linked list
template<class T>
class Node {
private:
	T data;
	Node<T> *next;

public:
	// empty node constructor
	Node() {
		next = nullptr;
	}

	// node constructor with two arguments
	Node(T d, Node<T>* n) {
		data = d;
		next = n;
	}

	// get/set functions for node class
	T getData();
	Node<T>* getNext();
	void setData(T d);
	void setNext(Node<T> *n);
};

template<typename T>
T Node<T>::getData() {
	return data;
}

template<typename T>
Node<T>* Node<T>::getNext() {
	return next;
}

template<typename T>
void Node<T>::setData(T d) {
	data = d;
}

template<typename T>
void Node<T>::setNext(Node<T> *n) {
	next = n;
}

#endif
