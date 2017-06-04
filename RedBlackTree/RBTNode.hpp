#ifndef RBT_NODE_HPP
#define RBT_NODE_HPP

template<class T>
class RBTNode {
private:
	bool isRed;
	T data;
	RBTNode<T> *parent;
	RBTNode<T> *left;
	RBTNode<T> *right;

public:
	// constructor
	RBTNode() {
		parent = left = right = nullptr;
		isRed = true;
	}

	// get/set functions
	bool getIsRed();
	T getData();
	RBTNode *getParent();
	RBTNode *getLeft();
	RBTNode *getRight();
	void setIsRed(bool r);
	void setData(T d);
	void setParent(RBTNode *p);
	void setLeft(RBTNode *p);
	void setRight(RBTNode *p);
};

template<class T>
bool RBTNode<T>::getIsRed() {
	return isRed;
}

template<class T>
T RBTNode<T>::getData() {
	return data;
}

template<class T>
RBTNode<T>* RBTNode<T>::getParent() {
	return parent;
}

template<class T>
RBTNode<T>* RBTNode<T>::getLeft() {
	return left;
}

template<class T>
RBTNode<T>* RBTNode<T>::getRight() {
	return right;
}

template<class T>
void RBTNode<T>::setIsRed(bool r) {
	isRed = r;
}

template<class T>
void RBTNode<T>::setData(T d) {
	data = d;
}

template<class T>
void RBTNode<T>::setParent(RBTNode *p) {
	parent = p;
}

template<class T>
void RBTNode<T>::setLeft(RBTNode *p) {
	left = p;
}

template<class T>
void RBTNode<T>::setRight(RBTNode *p) {
	right = p;
}

#endif