#ifndef TRIENODE_HPP
#define TRIENODE_HPP
#include <vector>

const int ALPHABET_SIZE = 26;

// trie node class will use english alphabet as example (hence 26 for array size)
class TrieNode {
private:
	char c;
	TrieNode *parent;
	TrieNode *children[ALPHABET_SIZE];
	bool isWord;

public:
	// constructor
	TrieNode() {
		c = ' ';
		isWord = false;
		parent = nullptr;

		// initially set all children to nullptrs
		for(int i = 0; i < ALPHABET_SIZE; i++) {
			children[i] = nullptr;
		}
	}

	char getChar();
	bool getIsWord();
	TrieNode *getParent();
	TrieNode *searchChildren(char c);
	int getChildrenLength();
	void getChildren(TrieNode *p, std::vector<TrieNode*> &v);
	void setChar(char letter);
	void setIsWord(bool b);
	void setParent(TrieNode *p);
	void addChild(TrieNode *p);
};

char TrieNode::getChar() {
	return c;
}

bool TrieNode::getIsWord() {
	return isWord;
}

TrieNode* TrieNode::getParent() {
	return parent;
}

// returns pointer to children that matches character
TrieNode* TrieNode::searchChildren(char c) {
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(children[i] != nullptr) {
			if(c == children[i]->getChar()) {
				return children[i]; // return children with matching char
			}
		}
	}

	// return nullptr if there is no children with matching char
	return nullptr;
}

// returns length of children pointers
int TrieNode::getChildrenLength() {
	int counter = 0;
	while(children[counter] != nullptr) {
		counter++;
	}
	return counter;
}

// returns children pointers in a vector
void TrieNode::getChildren(TrieNode *p, std::vector<TrieNode*> &v) {
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(children[i] != nullptr) {
			v.push_back(children[i]);
		}
	}
}

void TrieNode::setChar(char letter) {
	c = letter;
}

void TrieNode::setIsWord(bool b) {
	isWord = b;
}

void TrieNode::setParent(TrieNode *p) {
	parent = p;
}

// adds a pointer into the children array
void TrieNode::addChild(TrieNode *p) {
	// check for an empty spot in array and insert pointer
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		if(children[i] == nullptr) {
			children[i] = p;
			break;
		}
	}
}

#endif