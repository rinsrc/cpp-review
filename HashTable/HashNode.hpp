#ifndef HASH_NODE_HPP
#define HASH_NODE_HPP

template<class K, class V>
class HashNode {
private:
	K key;
	V value;
	HashNode<K, V> *next;

public:
	// constructor
	HashNode(K k, V v) {
		key = k;
		value = v;
		next = nullptr;
	}

	// set/get functions
	K getKey();
	V getValue();
	HashNode<K, V> *getNext();
	void setKey(K k);
	void setValue(V v);
	void setNext(HashNode<K, V> *n);
};

template<class K, class V>
K HashNode<K, V>::getKey() {
	return key;
}

template<class K, class V>
V HashNode<K, V>::getValue() {
	return value;
}

template<class K, class V>
HashNode<K, V>* HashNode<K, V>::getNext() {
	return next;
}

template<class K, class V>
void HashNode<K, V>::setKey(K k) {
	key = k;
}

template<class K, class V>
void HashNode<K, V>::setValue(V v) {
	value = v;
}

template<class K, class V>
void HashNode<K, V>::setNext(HashNode<K, V> *n) {
	next = n;
}

#endif