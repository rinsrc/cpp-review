#ifndef NODE_HPP
#define NODE_HPP

// node template class for double linked list
template<typename T>
class Node {
private:
	T data;
	Node<T> *next;
	Node<T> *prev;

public:
	// empty node constructor
	Node() {
		next = nullptr;
		prev = nullptr;
	}

	// node constructor with just data argument, data "d"
	Node(T d) {
		data = d;
		next = nullptr;
		prev = nullptr;
	}

	// node constructor with all three arguments
	Node(T d, Node *n, Node *p) {
		data = d;
		next = n;
		prev = p;
	}

	// get/set functions
	T getData();
	Node<T>* getNext();
	Node<T>* getPrev();
	void setData(T d);
	void setNext(Node *n);
	void setPrev(Node *p);
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
Node<T>* Node<T>::getPrev() {
	return prev;
}

template<typename T>
void Node<T>::setData(T d) {
	data = d;
}

template<typename T>
void Node<T>::setNext(Node *n) {
	next = n;
}

template<typename T>
void Node<T>::setPrev(Node *p) {
	prev = p;
}

#endif