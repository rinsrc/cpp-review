#ifndef B_NODE_HPP
#define B_NODE_HPP

template<class T>
class BNode {
private:
	T *keys; // array of keys
	int maxDegree; // maximum degree of each node
	BNode<T> **child; // array of child pointers
	int numOfKeys; // current number of keys in node (use to check if it is full)
	bool isLeaf;

public:
	// constructor
	BNode(int maxDeg) {
		maxDegree = maxDeg;

		// each key has maxDegree-1 amount of keys
		keys = new T[maxDegree-1];

		// each node can only have maxDegree amount of children nodes
		child = new BNode<T>*[maxDegree];

		// make each child node nullptr
		for(int i = 0; i < maxDegree; i++) {
			child[i] = nullptr;
		}

		// initialize number of keys at node to 0
		numOfKeys = 0;

		// assume new node is a leaf
		isLeaf = true;
	}

	// destructor
	~BNode() {
		delete [] keys;
		delete [] child;
	}

	T *getKeys();
	int getMaxDegree();
	BNode<T> **getChild();
	int getNumOfKeys();
	bool getIsLeaf();
	void setNumOfKeys(int k);
	void setIsLeaf(bool l);
};

template<class T>
T* BNode<T>::getKeys() {
	return keys;
}

template<class T>
int BNode<T>::getMaxDegree() {
	return maxDegree;
}

template<class T>
BNode<T>** BNode<T>::getChild() {
	return child;
}

template<class T>
int BNode<T>::getNumOfKeys() {
	return numOfKeys;
}

template<class T>
bool BNode<T>::getIsLeaf() {
	return isLeaf;
}

template<class T>
void BNode<T>::setNumOfKeys(int k) {
	numOfKeys = k;
}

template<class T>
void BNode<T>::setIsLeaf(bool l) {
	isLeaf = l;
}

#endif