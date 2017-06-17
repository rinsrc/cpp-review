#ifndef SPLAY_NODE_HPP
#define SPLAY_NODE_HPP

template<class T>
class SplayNode {
private:
	SplayNode<T> *parent;
	SplayNode<T> *left;
	SplayNode<T> *right;
	T key;

public:
	// constructor
	SplayNode() {
		parent = left = right = nullptr;
	}

	// set/get functions
	SplayNode<T> *getParent();
	SplayNode<T> *getLeft();
	SplayNode<T> *getRight();
	T getKey();
	void setParent(SplayNode<T> *p);
	void setLeft(SplayNode<T> *p);
	void setRight(SplayNode<T> *p);
	void setKey(T k);
};

template<class T>
SplayNode<T>* SplayNode<T>::getParent() {
	return parent;
}

template<class T>
SplayNode<T>* SplayNode<T>::getLeft() {
	return left;
}

template<class T>
SplayNode<T>* SplayNode<T>::getRight() {
	return right;
}

template<class T>
T SplayNode<T>::getKey() {
	return key;
}

template<class T>
void SplayNode<T>::setParent(SplayNode<T> *p) {
	parent = p;
}

template<class T>
void SplayNode<T>::setLeft(SplayNode<T> *p) {
	left = p;
}

template<class T>
void SplayNode<T>::setRight(SplayNode<T> *p) {
	right = p;
}

template<class T>
void SplayNode<T>::setKey(T k) {
	key = k;
}

#endif