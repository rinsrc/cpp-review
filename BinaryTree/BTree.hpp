#ifndef BTREE_HPP
#define BTREE_HPP
#include "BTNode.hpp"
#include <queue>
#include <stack>

// binary tree class
template<class T>
class BTree {
private:
	BTNode<T> *root; // root of binary tree

public:
	// constructor creates a new BinaryTreeNode
	BTree() {
		root = nullptr;
	}

	// delete entire tree and then set root to nullptr
	~BTree() {
		deleteTree(root);
		root = nullptr;
	}

	BTNode<T> *getRoot();
	void setRoot(BTNode<T> *p);
	BTNode<T> *insert(T d);
	void print(BTNode<T> *p);
	void nodeCount(BTNode<T> *p, int &counter);
	int depth(BTNode<T> *p); 
	void countLeaves(BTNode<T> *p, int &counter);
	bool check(BTNode<T> *p, T target);
	void mirror(BTNode<T> *p);
	void printPathFromRoot(BTNode<T> *p);
	void swim(BTNode<T> *p);
	void sink(BTNode<T> *p);
	void copyTree(BTree<T> *t, BTNode<T> *p);
	void deleteTree(BTNode<T> *p);
};

// returns pointer to root of tree
template<class T>
BTNode<T>* BTree<T>::getRoot() {
	return root;
}

// set root of tree
template<class T>
void BTree<T>::setRoot(BTNode<T> *p) {
	root = p;
}

// insert new node into binary tree using level order traversal
template<class T>
BTNode<T>* BTree<T>::insert(T d) {
	// if tree is empty (or a new tree), create a new binary tree node
	if(root == nullptr) {
		BTNode<T> *nn = new BTNode<T>();
		nn->setData(d);
		root = nn; // point root to the new node
		return nn;
	}

	std::queue<BTNode<T>*> q; // create a queue
	q.push(root); // push in root first

	while(!q.empty()) {
		BTNode<T> *currNode = q.front(); // get first BTNode in tree
		q.pop(); // pop first node

		// if there is a left child node, push into queue
		if(currNode->getLeft() != nullptr) {
			q.push(currNode->getLeft());
		}

		// else, insert new node at the left b/c it is empty
		else {
			BTNode<T> *nn = new BTNode<T>(); // create a new node
			nn->setData(d); // change data
			nn->setParent(currNode); // make currNode the parent
			currNode->setLeft(nn); // make sure next node of parent is also connected
			return nn; // return pointer to newly created node
		}

		// if there is a right child node, push into queue
		if(currNode->getRight() != nullptr) {
			q.push(currNode->getRight());
		}

		// else, insert new node at the right b/c it is empty
		else {
			BTNode<T> *nn = new BTNode<T>(); // create a new node
			nn->setData(d); // change data
			nn->setParent(currNode); // make currNode the parent
			currNode->setRight(nn);
			return nn; // return pointer to newly created node
		}
	}
}

// prints binary tree (pass in root to print entire tree) using level order scan/travesal
template<class T>
void BTree<T>::print(BTNode<T> *p) {
	std::queue<BTNode<T>*> q; // this queue will store pointers of tree
	q.push(root); // push in root node first

	while(!q.empty()) {
		BTNode<T>* currNode = q.front(); // store first pointer in currNode
		q.pop(); // remove first element in queue
		std::cout << currNode->getData() << " "; // print out data

		// if there is a node left of p, push into queue
		if(currNode->getLeft() != nullptr) {
			q.push(currNode->getLeft());
		}

		// if there is a node right of p, push into queue
		if(currNode->getRight()!= nullptr) {
			q.push(currNode->getRight());
		}
	}
}

// counts how many nodes are in the tree
template<class T>
void BTree<T>::nodeCount(BTNode<T> *p, int &counter) {
	if(p == nullptr) {
		return;
	}

	nodeCount(p->getLeft(), counter);
	nodeCount(p->getRight(), counter);
	counter++;
}

// counts how many levels are in the tree
template<class T>
int BTree<T>::depth(BTNode<T> *p) {
	int depthLeft, depthRight, totalDepth;

	// if c is a nullptr, that means its an empty tree and totalDepth is -1
	if(p == nullptr) {
		totalDepth = -1;
	}

	else {
		// recursively calculate the depth of left and right subtrees
		depthLeft = depth(p->getLeft());
		depthRight = depth(p->getRight());

		// find max of left and right depths and add 1 to it for total depth
		if(depthLeft > depthRight) {
			totalDepth = 1 + depthLeft;
		}

		else {
			totalDepth = 1 + depthRight;
		}
	}

	return totalDepth;
}

// counts how many leaves are in tree (leaves have no children)
template<class T>
void BTree<T>::countLeaves(BTNode<T> *p, int &counter) {
	if(p != nullptr) {
		if(p->getLeft() == nullptr && p->getRight() == nullptr) {
			counter++;
		}

		countLeaves(p->getLeft(), counter);
		countLeaves(p->getRight(), counter);
	}
}

// returns true or false if target value is in tree
template<class T>
bool BTree<T>::check(BTNode<T> *p, T target) {
	if(p == nullptr) {
		return false;
	}

	// if current node matches target, return true
	if(p->getData() == target) {
		return true;
	}

	// recursively check left and right subtree to see if target exists and return true/false
	return check(p->getLeft(), target) || check(p->getRight(), target);
}

// creates a mirror of the tree
template<class T>
void BTree<T>::mirror(BTNode<T>* p) {
	if(p == nullptr) {
		return;
	}

	else {
		mirror(p->getLeft());
		mirror(p->getRight());

		// swap positions to mirror tree
		BTNode<T>* temp = p->getLeft(); // create a temp node that stores left child
		p->setLeft(p->getRight()); // set left child to c's right child
		p->setRight(temp); // change c's right child to temp
	}
}

// print path from root to a particular node in tree
template<class T>
void BTree<T>::printPathFromRoot(BTNode<T> *p) {
	std::stack<T> s; // create stack of data type

	// traverse up until you reach a parent will nullptr (the root)
	while(p != nullptr) {
		s.push(p->getData()); // push in each value of node
		p = p->getParent();
	}

	while(!s.empty()) {
		std::cout << s.top() << " "; // output value at top of stack
		s.pop(); // then pop it
	}	
}

// swaps data value of current node if  bigger than parent
template<class T>
void BTree<T>::swim(BTNode<T> *p) {
	// continue loop until it reaches root
	while(p->getParent() != nullptr) {
		// if parent data/value is smaller than current data, swap
		if(p->getParent()->getData() < p->getData()) {
			T temp = p->getData();
			p->setData(p->getParent()->getData());
			p->getParent()->setData(temp);
		}

		// move p up one parent
		p = p->getParent();
	}
}

// sinks a node down a tree if data value is smaller than left or right child
template<class T>
void BTree<T>::sink(BTNode<T> *p) {
	// swap values so long as p is smaller than left or right child
	while(p->getLeft() != nullptr || p->getRight() != nullptr) {
		// if left child value is bigger than p, swap and move left
		if(p->getLeft()->getData() >= p->getRight()->getData()) {
			T temp = p->getData();
			p->setData(p->getLeft()->getData());
			p->getLeft()->setData(temp);
			p = p->getLeft();
		}

		// if right child value is bigger than p, swap and move right
		else if(p->getLeft()->getData() <= p->getRight()->getData()) {
			T temp = p->getData();
			p->setData(p->getRight()->getData());
			p->getRight()->setData(temp);
			p = p->getRight();
		}

		else {
			break;
		}
	}
}

// copy a binary tree from bottom-up (creates new tree in memory)
// pass in an empty tree t and the root node p of tree you want to copy
template<class T>
void BTree<T>::copyTree(BTree<T> *t, BTNode<T> *p) {
	BTNode<T> *nn;

	if(p == nullptr) {
		return;
	}

	// recursively build left child and right child
	copyTree(t, p->getLeft());
	copyTree(t, p->getRight());

	nn = new BTNode<T>();
	t->setRoot(nn);
	nn->setData(p->getData());
	nn->setLeft(p->getLeft());
	nn->setRight(p->getRight());
}

// deletes tree from bottom up
template<class T>
void BTree<T>::deleteTree(BTNode<T> *p) {
	if(p != nullptr) {
		deleteTree(p->getLeft());
		deleteTree(p->getRight());
		delete p;
	}
}

#endif