#ifndef B_TREE_HPP
#define B_TREE_HPP
#include <iostream>
#include "BNode.hpp"

// example: b tree of order 4 has max 3 keys and 4 children nodes

template<class T>
class BTree {
private:
	BNode<T> *root;
	int degree;

public:
	BTree(int d) {
		root = nullptr;
		degree = d;
	}

	// destructor
	~BTree() {
		deleteTree(root);
		delete root;
		root = nullptr;
	}

	BNode<T> *getRoot();
	BNode<T> *search(BNode<T> *p, T k);
	void split(BNode<T> *parent, BNode<T> *p, int index);
	void insert(BNode<T> *p, T k);
	void insertNotFull(BNode<T> *p, T k);
	int getIndexOfKey(BNode<T> *p, T k);
	T getPred(BNode<T> *p, int i);
	T getSucc(BNode<T> *p, int i);
	void fill(BNode<T> *p, int i);
	void getKeyFromPrevChild(BNode<T> *p, int i);
	void getKeyFromNextChild(BNode<T> *p, int i);
	void merge(BNode<T> *p, int i);
	void deleteKey(BNode<T> *p, T k);
	void deleteKeyLeaf(BNode<T> *p, int i);
	void deleteKeyNotLeaf(BNode<T> *p, int i);
	void print(BNode<T> *p);
	void deleteTree(BNode<T> *p);
};

template<class T>
BNode<T>* BTree<T>::getRoot() {
	return root;
}

template<class T>
BNode<T>* BTree<T>::search(BNode<T> *p, T k) {
	// determine which key or child potentially has key
	int i = 0;
	while(i < p->getNumOfKeys() && k > p->getKeys()[i]) {
		i++;
	}

	// if key matches k, return node
	if(p->getKeys()[i] == k) {
		return p;
	}

	// if this is leaf node and key is not there, simply return nullptr
	if(p->getIsLeaf() == true) {
		return nullptr;
	}

	// otherwise, recursively check children
	return search(p->getChild()[i], k);
}

// node p must be full when calling this function
// split creates a new node and copies half of keys and children to it
template<class T>
void BTree<T>::split(BNode<T> *parent, BNode<T> *p, int index) {
	// create a new node
	BNode<T> *n = new BNode<T>(degree);
	n->setIsLeaf(p->getIsLeaf());

	// copy right half of p's keys to n
	for(int i = 0; i < (degree-1)/2; i++) {
		// make sure (degree-1)/2+1+i does not go beyond keys[] array index upper bound
		// keys[] array index upper bound is degree-2
		if((degree-1)/2+1+i <= degree-2) {
			n->getKeys()[i] = p->getKeys()[(degree-1)/2+1+i];
			n->setNumOfKeys(n->getNumOfKeys()+1);
			p->setNumOfKeys(p->getNumOfKeys()-1);
		}
	}

	// if p is not a leaf, copy right half of p's children to n
	// make sure copied pointer of p becomes nullptr
	if(p->getIsLeaf() == false) {
		for(int i = 0; i <= degree/2; i++) {
			n->getChild()[i] = p->getChild()[(degree-1)/2+1+i];
			p->getChild()[(degree-1)/2+1+i] = nullptr;
		}
	}

	// update number of keys in p
	p->setNumOfKeys(p->getNumOfKeys()-1);

	// parent node will have new child, so create room for it
	// if necessary
	for(int i = parent->getNumOfKeys(); i >= index+1; i--) {
		parent->getChild()[i+1] = parent->getChild()[i];
	}

	// add n, new child, to parent's child
	parent->getChild()[index+1] = n;

	// move keys in parent to make room for middle key from p
	for(int i = parent->getNumOfKeys()-1; i >= index; i--) {
		parent->getKeys()[i+1] = parent->getKeys()[i];
	}

	// copy middle key of p to parent
	parent->getKeys()[index] = p->getKeys()[(degree-1)/2];

	// update number of keys in parent
	parent->setNumOfKeys(parent->getNumOfKeys()+1);
}

template<class T>
void BTree<T>::insert(BNode<T> *p, T k) {
	if(root == nullptr) {
		// create a new node based on degree
		BNode<T> *n = new BNode<T>(degree);

		// set index 0 key to k
		n->getKeys()[0] = k;

		// update number of keys
		n->setNumOfKeys(1);

		root = n;
	}

	else {
		// if root is full of keys (degree-1 means it is full)
		if(root->getNumOfKeys() == degree-1) {
			// create new root node and then split
			BNode<T> *n = new BNode<T>(degree);

			// n will be parent node, so it is NOT a leaf
			n->setIsLeaf(false);

			// set child of new node to p (old node)
			n->getChild()[0] = p;

			// split old node p, and move key to new node n
			split(n, p, 0);

			// after split, node n will have 2 child
			// determine where key k should go
			int i = 0;
			if(n->getKeys()[0] < k) {
				i++;
			}

			// then insertNotFull
			insertNotFull(n->getChild()[i], k);

			root = n;
		}
	
		// node is not full, insertNotFull
		else {
			insertNotFull(p, k);
		}
	}

	return;
}

// if a node has space to put more keys, insert into it
template<class T>
void BTree<T>::insertNotFull(BNode<T> *p, T k) {
	// if p is a leaf node, insert into key array
	if(p->getIsLeaf() == true) {
		// find where key should be placed in array
		// while k is smaller than p's key shift bigger values to right
		int i = p->getNumOfKeys()-1;
		while(i >= 0 && p->getKeys()[i] > k) {
			// shift larger elements to right
			p->getKeys()[i+1] = p->getKeys()[i];
			i--;
		}

		// after while loop above i+1 should be at correct location for k
		// add 1 to i, because of array index starting at 0
		// prevents index from being -1
		p->getKeys()[i+1] = k;

		// update/increment number of keys in node p
		p->setNumOfKeys(p->getNumOfKeys()+1);
	}

	// else p is not a leaf (internal node)
	else {
		int i = p->getNumOfKeys()-1;

		// find child to put key in
		while(i >= 0 && p->getKeys()[i] > k) {
			i--;
		}

		// after above while loop, check child array of p at index i+1
		// if child is full of keys, split
		if(p->getChild()[i+1]->getNumOfKeys() == degree-1) {
			split(p, p->getChild()[i+1], i+1);

			// after split, determine which children the key will be inserted into
			if(p->getKeys()[i+1] < k) {
				i++;
			}
		}

		insertNotFull(p->getChild()[i+1], k);
	}

	return;
}

// returns index of key that is greater or equal to the key
// used to check potential location of key in keys[] array or child[] array
template<class T>
int BTree<T>::getIndexOfKey(BNode<T> *p, T k) {
	int i = 0;
	while(i < p->getNumOfKeys() && k > p->getKeys()[i]) {
		i++;
	}

	return i;
}

// returns predecessor key (find rightmost node)
template<class T>
T BTree<T>::getPred(BNode<T> *p, int i) {
	// traverse to right until leaf node is found
	BNode<T> *curr = p->getChild()[i];
	while(curr->getIsLeaf() == false) {
		curr = curr->getChild()[curr->getNumOfKeys()];
	}

	// return predecessor key
	return curr->getKeys()[curr->getNumOfKeys()-1];
}

// returns successor key (find leftmost node)
template<class T>
T BTree<T>::getSucc(BNode<T> *p, int i) {
	// traverse to left until leaf node is found
	BNode<T> *curr = p->getChild()[i+1];
	while(curr->getIsLeaf() == false) {
		curr = curr->getChild()[0];
	}

	// return successor key
	return curr->getKeys()[0];
}

// gets a key from p's prev child[i-1]
template<class T>
void BTree<T>::getKeyFromPrevChild(BNode<T> *p, int i) {
	BNode<T> *c = p->getChild()[i];
	BNode<T> *sibling = p->getChild()[i-1];

	// shift c's keys to right
	for(int j = c->getNumOfKeys()-1; j >= 0; j--) {
		c->getKeys()[j+1] = c->getKeys()[j];
	}

	// also, shift c's child pointers to right
	for(int j = c->getNumOfKeys(); j >=0; j--) {
		c->getChild()[j+1] = c->getChild()[j];
	}

	// copy a value from p to c
	c->getKeys()[0] = p->getKeys()[i-1];

	// move sibling's last child to c's first child
	c->getChild()[0] = sibling->getChild()[sibling->getNumOfKeys()];

	// move sibling's last key to p
	p->getKeys()[i-1] = sibling->getKeys()[sibling->getNumOfKeys()-1];

	// update number of keys in c and sibling (p remains same)
	c->setNumOfKeys(c->getNumOfKeys()+1);
	sibling->setNumOfKeys(sibling->getNumOfKeys()-1);	

	return;
}

// gets a key from p's child[i+1]
template<class T>
void BTree<T>::getKeyFromNextChild(BNode<T> *p, int i) {
	BNode<T> *c = p->getChild()[i];
	BNode<T> *sibling = p->getChild()[i+1];

	// one of p's keys moves to c
	c->getKeys()[c->getNumOfKeys()] = p->getKeys()[i];

 	// if c is not a leaf, sibling's first child moves to last child of c
 	if(c->getIsLeaf() == false) {
 		c->getChild()[c->getNumOfKeys()+1] = sibling->getChild()[0];
 	}

 	// first key in sibling moves to p's keys
 	p->getKeys()[i] = sibling->getKeys()[0];

	// shift sibling's keys to left
	for(int j = 1; j < sibling->getNumOfKeys(); j++) {
		sibling->getKeys()[j-1] = sibling->getKeys()[j];
	}

	// shift sibling's child pointers to left also
	for(int j = 1; j <= sibling->getNumOfKeys(); j++) {
		if(sibling->getChild()[j] != nullptr)
		sibling->getChild()[j-1] = sibling->getChild()[j];
	}

	// set sibling's last child to nullptr after shifting from above
	sibling->getChild()[sibling->getNumOfKeys()+1] = nullptr;

	c->setNumOfKeys(c->getNumOfKeys()+1);
	sibling->setNumOfKeys(sibling->getNumOfKeys()-1);	

	return;
}

// merges child[i] with child[i+1] (or sibling)
// child[i+1] (or sibling) is deleted after merge
template<class T>
void BTree<T>::merge(BNode<T> *p, int i) {
	BNode<T> *c = p->getChild()[i];
	BNode<T> *sibling = p->getChild()[i+1];

	// copy one of p's keys to c
	if(i >= 0) {
    	c->getKeys()[degree/2-1] = p->getKeys()[i];
    }

 	// copy sibling's keys to c
 	for(int j = 0; j < sibling->getNumOfKeys(); j++) {
 		c->getKeys()[degree/2+j] = sibling->getKeys()[j];
 	}

 	if(c->getIsLeaf() == false) {
	 	// copy sibling's child to c
	 	for(int j = 0; j <= sibling->getNumOfKeys(); j++) {
	 		if(sibling->getChild()[j] != nullptr)
	 		c->getChild()[degree/2+j] = sibling->getChild()[j];
	 	}
	}
 	
 	// since one of p's keys were copied to c, shift p's keys[] to left
 	for(int j = i+1; j < p->getNumOfKeys(); j++) {
 		p->getKeys()[j-1] = p->getKeys()[j];
 	}

 	// also shift p's pointers to left starting from pointer after sibling (i+2)
 	for(int j = i+2; j <= p->getNumOfKeys(); j++) {
 		p->getChild()[j-1] = p->getChild()[j];
 	}

 	// check to see if p was root and reassign root to c if necessary
 	if(p == root && p->getNumOfKeys() == 0) {
 		delete p;
 		root = c;
 	}

 	// update num of keys in c and p
 	c->setNumOfKeys(c->getNumOfKeys()+sibling->getNumOfKeys()+1);
 	p->setNumOfKeys(p->getNumOfKeys()-1);
 
    delete sibling;
	
    return;
}

// fills child which has less than half the keys
template<class T>
void BTree<T>::fill(BNode<T> *p, int i) {
	// if previous child (child[i-1]) has more than 1/2 full of keys
	// get a key from prev child
	if(i != 0 && p->getChild()[i-1] != nullptr && p->getChild()[i-1]->getNumOfKeys() >= degree/2) {
		getKeyFromPrevChild(p, i);
	}

	// if next child (child[i+1]) has has more than 1/2 of its keys array full
	// get a key from next child
	else if(p->getChild()[i+1] != nullptr && p->getChild()[i+1]->getNumOfKeys() >= degree/2) {
		getKeyFromNextChild(p, i);
	}

	// else both prev and next child are less than 1/2 full of keys or nullptr
	// merge child[i] with next sibling node
	else {
		// if index i is not at end of child array, merge with next sibling
		if(i != p->getNumOfKeys()) {
			merge(p, i);
		}

		// else index i is at end of child array, merge with prev sibling
		else {
			merge(p, i-1);
		}
	}

	return;
}

template<class T>
void BTree<T>::deleteKey(BNode<T> *p, T k) {
	// get index of where key can potentially be found
	int i = getIndexOfKey(p, k);

	// if key is present in node p
	if(i < p->getNumOfKeys() && p->getKeys()[i] == k) {
		// call appropriate function if key is leaf or not
		if(p->getIsLeaf() == true) {
			deleteKeyLeaf(p, i);
		}

		else {
			deleteKeyNotLeaf(p, i);
		}
	}

	// key is not in node p
	else {
		// if p is a leaf node, that means key does not exist in B-Tree
		if(p->getIsLeaf() == true) {
			std::cout << "Key does not exist in B-Tree.\n";
			return;
		}

		// determine if i is last child in keys array
		bool isLastChild;
		if(i == p->getNumOfKeys()) {
			isLastChild = true;
		}

		else {
			isLastChild = false;
		}

		// if subtree where key exists is less than half full
		// fill it up by getting keys from prev or next child or merging
		if(p->getChild()[i]->getNumOfKeys() < degree/2) {
			fill(p, i);
		}

		if(isLastChild && i > p->getNumOfKeys()) {
			deleteKey(p->getChild()[i-1], k); 
		}

		else {
			deleteKey(p->getChild()[i], k);
		}
	}

	return;
}

// p is a leaf node and key to be deleted exists in p
template<class T>
void BTree<T>::deleteKeyLeaf(BNode<T> *p, int i) {
	// shift keys to left
	for(int j = i+1; j <= p->getNumOfKeys(); j++) {
		p->getKeys()[j-1] = p->getKeys()[j];
	}

	// decrease number of keys in p
	p->setNumOfKeys(p->getNumOfKeys()-1);
}

template<class T>
void BTree<T>::deleteKeyNotLeaf(BNode<T> *p, int i) {
	// key will be deleted
	T key = p->getKeys()[i];

	// if child that comes before key (the predecessor) is at least half full
	if(p->getChild()[i]->getNumOfKeys() >= degree/2) {
		// find predecessor
		T pred = getPred(p, i);

		// replace key with predecessor
		p->getKeys()[i] = pred;
		
		// remove predecessor from child node
		deleteKey(p->getChild()[i], pred);
	}

	// if child[i] is less than half full,
	// check child[i+1]
	else if(p->getChild()[i+1]->getNumOfKeys() >= degree/2) {
		// find successor
		T succ = getSucc(p, i);

		// replace key with successor
		p->getKeys()[i] = succ;

		// remove successor from child node
		deleteKey(p->getChild()[i+1], succ);
	}

	// if both child[i] and child[i+1] has less than half keys
	else {
		merge(p, i);
		deleteKey(p->getChild()[i], key);
	}

	return;
}

// prints all keys in B-Tree using inorder traversal
template<class T>
void BTree<T>::print(BNode<T> *p) {
	if(root == nullptr) {
		return;
	}

	else {
		int i;
		for(i = 0; i < p->getNumOfKeys(); i++) {
			// if p is not a leaf, check children nodes
			if(p->getIsLeaf() == false) {
				print(p->getChild()[i]);
			}

			// otherwise print key
			std::cout << p->getKeys()[i] << " ";
		}

		// check child one more time
		// because there is potentially 1 more child than
		// the number of keys in node
		if(p->getIsLeaf() == false) {
			print(p->getChild()[i]);
		}
	}

	return;
}

template<class T>
void BTree<T>::deleteTree(BNode<T> *p) {
	if(root == nullptr || p == nullptr) {
		return;
	}

	else {
		int i;
		for(i = 0; i <= p->getNumOfKeys(); i++) {
			// if not leaf, recurse down tree
			if(p->getIsLeaf() == false) {
				deleteTree(p->getChild()[i]);
			}

			// else delete that node
			delete p->getChild()[i];
		}

		// there is probably one more child that above loop did not check
		// check child[i+1] and delete
		if(p->getIsLeaf() == false) {
			deleteTree(p->getChild()[i+1]);
		}
	}

	return;
}

#endif