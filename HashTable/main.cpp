#include <iostream>
#include "HashTable.hpp"

// This hash table/map uses single linked list chaining method

int main() {
	HashTable<char, int> *ht = new HashTable<char, int>();

	// create a hash table that stores english alphabet letters
	char start = 'a';
	for(int i = 0; i < 26; i++) {
		ht->insert(start, i);
		start++;
	}

	ht->printKeys(); // print keys

	// get table to access specific keys
	HashNode<char, int> **t = ht->getTable();
	std::cout << std::endl;

	// get key a by hashing it and print its value
	int indexOfA = ht->hash('a');
	std::cout << "Value of key a: " << t[indexOfA]->getValue() << std::endl << std::endl;

	// delete key a and reprint entire hash table
	std::cout << "Deleting key a and reprinting hash table" << std::endl;
	ht->deleteKey('a');
	ht->printKeys();
	std::cout << std::endl;

	// reinsert key a and reprint entire hash table
	std::cout << "Reinserting key a with value 9000 and reprinting hash table:" << std::endl;
	ht->insert('a', 9000);
	ht->printKeys();
	std::cout << std::endl;

	// lookup a and print it's value
	HashNode<char, int> *pointerToA = ht->lookup('a');
	std::cout << "Using lookup function, the value of key a is now: " << pointerToA->getValue() << std::endl;

	return 0;
}
