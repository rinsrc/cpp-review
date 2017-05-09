#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include "HashNode.hpp"

const int TABLE_SIZE = 6; // size of hash table array

template<class K, class V>
class HashTable {
private:
	HashNode<K, V> **table;

public:
	// constructor sets all array values in table to nullptr
	HashTable() {
		// create an array of hash node pointers with table size
		table = new HashNode<K, V> *[TABLE_SIZE];
		for(int i = 0; i < TABLE_SIZE; i++) {
			table[i] = nullptr;
		}
	}

	// destructor, deletes entries in hash table like a singly linked list
	~HashTable() {
		for(int i = 0; i < TABLE_SIZE; i++) {
			if(table[i] != nullptr) {
				HashNode<K, V> *prev = nullptr;
				HashNode<K, V> *curr = table[i];

				while(curr != nullptr) {
					prev = curr;
					curr = curr->getNext();
					delete prev;
				}
			}
		}

		delete [] table; // delete array
	}

	int hash(K k);
	void insert(K k, V v);
	void deleteKey(K k);
	HashNode<K, V> *lookup(K k);
	HashNode<K, V> **getTable();
	void printKeys();
};

// very generic/basic hash function that returns an index
template<class K, class V>
int HashTable<K, V>::hash(K k) {
	return k % TABLE_SIZE;
}

// inserts a key value pair into the hash table
template<class K, class V>
void HashTable<K, V>::insert(K k, V v) {
	int h = hash(k); // get index from the hash function

	// if index is empty, create a new node and insert key/value there
	if(table[h] == nullptr) {
		table[h] = new HashNode<K, V>(k, v);
	}

	// else, there is already a hash node in that index
	else {
		// create a new hash node pointer that begins at index h
		HashNode<K, V> *p = table[h];

		// since this is a single linked list hash node, traverse list to end and insert
		while(p->getNext() != nullptr) {
			// break out of loop if p finds a matching key
			if(p->getKey() == k) {
				break;
			}

			// else, traverse through list
			p = p->getNext();
		}

		// if keys match, simply change value
		if(p->getKey() == k) {
			p->setValue(v);
		}

		// if n has no matching keys, create and insert a new node at end of linked list
		else {
			p->setNext(new HashNode<K, V>(k, v));
		}
	}
}

// deletes a key in the hash table
template<class K, class V>
void HashTable<K, V>::deleteKey(K k) {
	int h = hash(k); // get index by hashing the key

	// get first pointer from hash, will work as current node
	HashNode<K, V> *curr = table[h];

	// stores previous pointer to curr (used to maintain single linked list chaining structure after deletion)
	HashNode<K, V> *prev = nullptr;

	// find matching key in linked list
	while(curr != nullptr) {
		if(curr->getKey() == k) {
			break;
		}

		prev = curr; // prev moves to p
		curr = curr->getNext(); // p moves to next
	}

	// if key you want to delete is the first one in singly linked list
	if(prev == nullptr) {
		HashNode<K, V> *next = curr->getNext(); // store pointer to next node
		delete curr; // delete curr node
		table[h] = next; // make table[h] (first pointer) the next node
	}

	// else key is not first one, therefore delete like a regular singly linked list
	else {
		prev->setNext(curr->getNext()); // set prev's next to curr's next
		delete curr;
	}
}

// returns pointer of key that user wants to lookup
template<class K, class V>
HashNode<K, V>* HashTable<K, V>::lookup(K k) {
	int h = hash(k); // get index by hashing the key

	HashNode<K, V> *p = table[h]; // point to correct array index

	// if the keys match, break out of loop
	while(p != nullptr) {
		if(p->getKey() == k) {
			break;
		}

		p = p->getNext();
	}

	return p; // return pointer
}

// returns pointer to table to access like an array
template<class K, class V>
HashNode<K, V>** HashTable<K, V>::getTable() {
	return table;
}

// prints the keys in table
template<class K, class V>
void HashTable<K, V>::printKeys() {
	for(int i = 0; i < TABLE_SIZE; i++) {
		// if there is a node in table, print out entire linked list
		if(table[i] != nullptr) {
			HashNode<K, V> *curr = table[i];
			while(curr != nullptr) {
				std::cout << curr->getKey() << " ";
				curr = curr->getNext(); // go to next node to repeat and print
			}

			std::cout << std::endl;
		}

		// else, it is a nullptr and just print out nullptr
		else {
			std::cout << "nullptr" << std::endl;
		}
	}
}

#endif