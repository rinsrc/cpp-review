#ifndef BSTNODE_HPP
#define BSTNODE_HPP

template<class K, class V>
class BSTNode {
private:
	K key;
	V value;
	BSTNode<K, V> *parent;
	BSTNode<K, V> *left;
	BSTNode<K, V> *right;

public:
	// basic constructor
	BSTNode() {
		parent = left = right = nullptr;
	}

	// set/get functions
	K getKey();
	V getValue();
	BSTNode<K, V> *getParent();
	BSTNode<K, V> *getLeft();
	BSTNode<K, V> *getRight();
	void setKey(K k);
	void setValue(V v);
	void setParent(BSTNode<K, V> *p);
	void setLeft(BSTNode<K, V> *l);
	void setRight(BSTNode<K, V> *r);
};

template<class K, class V>
K BSTNode<K, V>::getKey() {
	return key;
}

template<class K, class V>
V BSTNode<K, V>::getValue() {
	return value;
}

template<class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getParent() {
	return parent;
}

template<class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getLeft() {
	return left;
}

template<class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getRight() {
	return right;
}

template<class K, class V>
void BSTNode<K, V>::setKey(K k) {
	key = k;
}

template<class K, class V>
void BSTNode<K, V>::setValue(V v) {
	value = v;
}

template<class K, class V>
void BSTNode<K, V>::setParent(BSTNode<K, V> *p) {
	parent = p;
}

template<class K, class V>
void BSTNode<K, V>::setLeft(BSTNode<K, V> *l) {
	left= l;
}

template<class K, class V>
void BSTNode<K, V>::setRight(BSTNode<K, V> *r) {
	right = r;
}

#endif