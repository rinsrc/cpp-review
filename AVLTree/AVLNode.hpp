#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

template<class T>
class AVLNode {
private:
	T data;
	AVLNode *parent;
	AVLNode *left;
	AVLNode *right;

public:
	// constructor
	AVLNode() {
		parent = left = right = nullptr;
	}

	// set get functions
	T getData();
	AVLNode<T> *getParent();
	AVLNode<T> *getLeft();
	AVLNode<T> *getRight();
	void setData(T d);
	void setParent(AVLNode *p);
	void setLeft(AVLNode *p);
	void setRight(AVLNode *p);
};

template<class T>
T AVLNode<T>::getData() {
	return data;
}

template<class T>
AVLNode<T>* AVLNode<T>::getParent() {
	return parent;
}

template<class T>
AVLNode<T>* AVLNode<T>::getLeft() {
	return left;
}

template<class T>
AVLNode<T>* AVLNode<T>::getRight() {
	return right;
}

template<class T>
void AVLNode<T>::setData(T d) {
	data = d;
}

template<class T>
void AVLNode<T>::setParent(AVLNode<T> *p) {
	parent = p;
}

template<class T>
void AVLNode<T>::setLeft(AVLNode<T> *p) {
	left = p;
}

template<class T>
void AVLNode<T>::setRight(AVLNode<T> *p) {
	right = p;
}

#endif
