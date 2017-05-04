#ifndef BTNODE_HPP
#define BTNODE_HPP

// binary tree template class
template<class T>
class BTNode {
private:
	T data; // value of node
	BTNode<T> *parent;
	BTNode<T> *left;
	BTNode<T> *right;

public:
	// basic constructor where all pointers are initially set to nullptr
	BTNode() {
		parent = left = right = nullptr;
	}

	// get/set functions
	T getData();
	BTNode<T> *getParent();
	BTNode<T> *getLeft();
	BTNode<T> *getRight();
	void setData(T d);
	void setParent(BTNode<T> *p);
	void setLeft(BTNode<T> *l);
	void setRight(BTNode<T> *r);
};

template<class T>
T BTNode<T>::getData() {
	return data;
}

template<class T>
BTNode<T>* BTNode<T>::getParent() {
	return parent;
}

template<class T>
BTNode<T>* BTNode<T>::getLeft() {
	return left;
}

template<class T>
BTNode<T>* BTNode<T>::getRight() {
	return right;
}

template<class T>
void BTNode<T>::setData(T d) {
	data = d;
}

template<class T>
void BTNode<T>::setParent(BTNode<T> *p) {
	parent = p;
}

template<class T>
void BTNode<T>::setLeft(BTNode<T> *l) {
	left= l;
}

template<class T>
void BTNode<T>::setRight(BTNode<T> *r) {
	right = r;
}

#endif