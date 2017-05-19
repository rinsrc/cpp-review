#include <iostream>
#include "Trie.hpp"

using std::string;

// this trie is implemented in an unordered fashion
// trie node children is unordered array of the english alphabet

int main() {
	Trie *t = new Trie();

	t->insert("apple");
	t->insert("looking");
	t->insert("look");
	t->insert("loop");
	t->insert("apply");

	std::cout << "Is apple in trie? (T/F): " << t->search("apple") << std::endl;
	std::cout << "Is look in trie? (T/F): " << t->search("look") << std::endl;
	std::cout << "Is loop in trie? (T/F): " << t->search("loop") << std::endl;
	std::cout << "Is looking in trie? (T/F): " << t->search("looking") << std::endl;
	std::cout << "Is adfas in trie? (T/F): " << t->search("adfas") << std::endl << std::endl;

	t->deleteString("looking");
	std::cout << "Deleted looking from trie." << std::endl;
	std::cout << "Is looking in trie? (T/F): " << t->search("looking") << std::endl << std::endl;

	std::cout << "Is look in trie? (T/F): " << t->search("look") << std::endl << std::endl;

	std::cout << "Recursively inserting good and goodness." << std::endl;
	t->recurInsert(t->getRoot(), "good");
	t->recurInsert(t->getRoot(), "goodness");

	std::cout << "Is good in trie? (T/F): " << t->search("good") << std::endl;
	std::cout << "Is goodness in trie? (T/F): " << t->search("goodness") << std::endl << std::endl;

	t->deleteString("goodness");
	std::cout << "Deleted goodness" << std::endl;
	std::cout << "Is goodness in trie? (T/F): " << t->search("goodness") << std::endl;

	std::cout << "Is good in trie? (T/F): " << t->search("good") << std::endl << std::endl;

	std::cout << "Inserted words 'application', 'approval', 'approving', and 'approve' into Trie." << std::endl;
	t->insert("application");
	t->insert("approval");
	t->insert("approving");
	t->insert("approve");

	std::cout << "Printing all words in Trie:" << std::endl;
	t->print(t->getRoot());

	std::cout << std::endl << "Suggesting words for 'app' (auto-suggest) based on words in Trie:" << std::endl;
	t->suggest("app");

	delete t;

	return 0;
}