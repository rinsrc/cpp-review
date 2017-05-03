#ifndef BTNODE_HPP
#define BTNODE_HPP

// binary tree template class
template<class T>
class BTNode {
private:
	T data; // value of node
	BTNode<T> *parent;
	BTNode<T> *leftChild;
	BTNode<T> *rightChild;

public:
	// basic constructor where all pointers are initially set to nullptr
	BTNode() {
		parent = leftChild = rightChild = nullptr;
	}

	// get/set functions
	T getData();
	BTNode<T> *getParent();
	BTNode<T> *getLeftChild();
	BTNode<T> *getRightChild();
	void setData(T d);
	void setParent(BTNode<T> *p);
	void setLeftChild(BTNode<T> *lc);
	void setRightChild(BTNode<T> *rc);
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
BTNode<T>* BTNode<T>::getLeftChild() {
	return leftChild;
}

template<class T>
BTNode<T>* BTNode<T>::getRightChild() {
	return rightChild;
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
void BTNode<T>::setLeftChild(BTNode<T> *lc) {
	leftChild = lc;
}

template<class T>
void BTNode<T>::setRightChild(BTNode<T> *rc) {
	rightChild = rc;
}

#endif