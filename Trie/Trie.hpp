#ifndef TRIE_HPP
#define TRIE_HPP
#include <vector>
#include "TrieNode.hpp"

using std::string;

class Trie {
private:
	TrieNode *root;

public:
	// constructor
	Trie() {
		root = new TrieNode();
	}

	// destructor
	~Trie() {
		deleteTrie(root);
	}

	TrieNode *getRoot();
	void insert(string s);
	void recurInsert(TrieNode *p, string s);
	void deleteString(string s);
	bool search(string s);
	void print(TrieNode *p);
	void suggest(string s);
	void deleteTrie(TrieNode *p);
};

TrieNode* Trie::getRoot() {
	return root;
}

// inserts string/word into the trie
void Trie::insert(string s) {
	TrieNode *curr = root;

	// if length of string is 0 (it is at root, so just set to ' ')
	if(s.length() == 0) {
		curr->setChar(' ');
		return;
	}

	for(int i = 0; i < s.length(); i++) {
		// search children in curr node for string
		TrieNode *child = curr->searchChildren(s[i]);

		// if there exists a child with a character from the string, move curr to child
		if(child != nullptr) {
			curr = child;
		}

		// else create a new node and insert at location (make sure set parent and char)
		else {
			TrieNode *n = new TrieNode();
			n->setChar(s[i]);
			n->setParent(curr);
			curr->addChild(n);
			curr = n;
		}

		// if you have traversed to the end of the word, setIsWord to true
		// this indicates that it is a word
		if(i == s.length() - 1) {
			curr->setIsWord(true);
		}
	}
}

// recursively insert string into trie
void Trie::recurInsert(TrieNode *p, string s) {
	if(s == "") {
		p->setIsWord(true);
		return;
	}

	TrieNode *child = p->searchChildren(s[0]);

	// if there already exists a child with specific character
	if(child != nullptr) {
		p = child; // move p to child
		s = s.substr(1, s.length()); // chop off index 0 in string
		recurInsert(p, s); // recursively insert
	}

	// else create a new node and recursively insert
	else {
		TrieNode *n = new TrieNode();
		n->setChar(s[0]);
		n->setParent(p);
		p->addChild(n);
		p = n;
		s = s.substr(1, s.length());
		recurInsert(p, s);
	}
}

// deletes a string/word from trie
// suppose good and goodness is in trie
// if I want to delete goodness, only -ness should be deleted
// good should still exist in trie
void Trie::deleteString(string s) {
	std::vector<TrieNode*> v;

	TrieNode *curr = root;

	// push all pointers with matching character into vector
	for(int i = 0; i < s.length(); i++) {
		TrieNode *child = curr->searchChildren(s[i]);

		if(child != nullptr) {
			v.push_back(child);
			curr = child;
		}
	}

	// delete last element in vector and pop last element
	// set to nullptr before deletion to prevent any problems when calling destructor
	v[v.size()-1] = nullptr; 
	delete v[v.size()-1];
	v.pop_back();
	v.resize(v.size());

	// counter (count backwards/subtract)
	int i = v.size()-1;

	// to save prefixes, just delete trie nodes in vector until isWord == true
	while(v[i]->getIsWord() == false && i > 0) {
		v[i] = nullptr;
		delete v[i];
		v.pop_back();
		i--;
	}
}

// returns true if string/word is in trie
bool Trie::search(string s) {
	TrieNode *curr = root;

	// if string is empty, return true
	if(s.length() == 0) {
		return true;
	}

	// search curr node for a char in string
	for(int i = 0; i < s.length(); i++) {
		TrieNode *child = curr->searchChildren(s[i]);

		// if child does not exist, then immediately return false
		if(child == nullptr) {
			return false;
		}

		// else continue traversing through string
		curr = child;
	}

	// after above loop, check to see if curr node ends at a word
	if(curr->getIsWord()) {
		return true;
	}

	else {
		return false;
	}
}

void Trie::print(TrieNode *p) {
	// get all children of p
	std::vector<TrieNode*> v;
	p->getChildren(p, v);

	// recursively get all the children to build word
	for(int i = 0; i < v.size(); i++) {
		print(v[i]);
	}

	// if p is a word, print it by building a string and moving up parent node
	if(p->getIsWord()) {
		string word = "";

		// nullptr is root's parent
		while(p->getParent() != nullptr) {
			word = p->getChar() + word;
			p = p->getParent();
		}

		std::cout << word << std::endl;
	}
}

void Trie::suggest(string s) {
	// cannot suggest any words if empty string
	if(s == "") {
		return;
	}

	TrieNode *curr = root;

	// curr will point to last word (pointer) in string
	for(int i = 0; i < s.size(); i++) {
		TrieNode *child = curr->searchChildren(s[i]);

		// if child is nullptr, that means character or word does not exist in trie
		if(child == nullptr) {
			return;
		}

		// continue traversing through trie
		else {
			curr = child;
		}
	}
	
	// recursively print starting from pointer of last character in string
	print(curr);
}

void Trie::deleteTrie(TrieNode *p) {
	// get all children of p
	std::vector<TrieNode*> v;
	p->getChildren(p, v);

	// loop through all children of p recursively
	for(int i = 0; i < v.size(); i++) {
		deleteTrie(v[i]);
	}

	delete p;
}

#endif