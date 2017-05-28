#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <queue>
#include "AVLNode.hpp"

template<class T>
class AVLTree {
private:
	AVLNode<T> *root;

public:
	// constructor
	AVLTree() {
		root = nullptr;
	}

	// destructor
	~AVLTree() {
		deleteTree(root);
		root = nullptr;
	}

	AVLNode<T> *getRoot();
	int getHeight(AVLNode<T> *p);
	int getBalance(AVLNode<T> *p);
	AVLNode<T> *leftRotate(AVLNode<T> *p);
	AVLNode<T> *rightRotate(AVLNode<T> *p);
	AVLNode<T> *insert(AVLNode<T> *p, T d);
	AVLNode<T> *minNode(AVLNode<T> *p);
	AVLNode<T> *deleteNode(AVLNode<T> *p, T d);
	void print();
	void deleteTree(AVLNode<T> *p);
};

template<class T>
AVLNode<T>* AVLTree<T>::getRoot() {
	return root;
}

// returns height of tree
template<class T>
int AVLTree<T>::getHeight(AVLNode<T> *p) {
	int heightLeft, heightRight, totalHeight;

	// if p is a nullptr, that means its an empty tree and totalDepth is -1
	if(p == nullptr) {
		totalHeight = -1;
	}

	else {
		// recursively calculate height of left and right subtrees
		heightLeft = getHeight(p->getLeft());
		heightRight = getHeight(p->getRight());

		// find max of left and right depths and add 1 to it for total depth
		if(heightLeft > heightRight) {
			totalHeight = 1 + heightLeft;
		}

		else {
			totalHeight = 1 + heightRight;
		}
	}

	return totalHeight;
}

// determines which side of tree needs balancing
template<class T>
int AVLTree<T>::getBalance(AVLNode<T> *p) {
	// 0 means tree is balanced
	if(p == nullptr) {
		return 0;
	}

	// negative numbers means rotate left
	// positive numbers means rotate right
	return getHeight(p->getLeft()) - getHeight(p->getRight());
}

// rotates nodes to left subtree
/* example (t1, t2, and t3 are other subtrees):
		p 						a
	   / \					   / \	
	  t1  a 				  p  t2
		 / \				 / \   \	
		b   t2				t1  b   t3
			 \
			 t3
*/
template<class T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T> *p) {
	AVLNode<T> *a = p->getRight();
	AVLNode<T> *b = a->getLeft();
	AVLNode<T> *parentOfP = p->getParent();

	// rotate nodes
	p->setRight(b);
	p->setParent(a);
	a->setParent(parentOfP);
	a->setLeft(p);

	if(b != nullptr) {
		b->setParent(p);
	}

	// check to see if p is root
	if(p == root) {
		root = a;
	}

	return a;
}

// rotates nodes to right subtree
/* example (t1, t2, and t3 are other subtrees):
		p 						a
	   / \					   / \	
	  a   t1 				  t2  p
	 / \				 	 /   / \	
	t2	b					t3  b   t1
	/
   t3
*/
template<class T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T> *p) {
	AVLNode<T> *a = p->getLeft();
	AVLNode<T> *b = a->getRight();
	AVLNode<T> *parentOfP = p->getParent();

	// rotate nodes
	p->setParent(a);
	p->setLeft(b);
	a->setRight(p);
	a->setParent(parentOfP);

	if(b != nullptr) {
		b->setParent(p);
	}

	// check to see if p is root
	if(p == root) {
		root = a;
	}

	return a;
}

template<class T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T> *p, T d) {
	// if tree is initially empty, create a root wtih data value d
	if(root == nullptr) {
		AVLNode<T> *nn = new AVLNode<T>();
		nn->setData(d);
		root = nn;
	}

	else {
		// after traversing down to leaves, insert left or right
		if(p == nullptr) {
			AVLNode<T> *nn = new AVLNode<T>();
			nn->setData(d);
			return nn;
		}

		// if data (d) smaller than p's data, recursively insert left
		if(d < p->getData()) {
			p->setLeft(insert(p->getLeft(), d));
			p->getLeft()->setParent(p);
		}

		// if data (d) is bigger than p's data, recursively insert right
		else if(d > p->getData()) {
			p->setRight(insert(p->getRight(), d));
			p->getRight()->setParent(p);
		}

		// entry already exists in tree, return
		else {
			return p;
		}

		int balance = getBalance(p);
		
		// left-left case, rotate right to fix
		/*
				a
			   /
			  b
			 /
			c
		*/
		if(balance > 1 && d < p->getLeft()->getData()) {
			return rightRotate(p);
		}

		// right-right case, rotate left to fix
		/*
			a
			 \
			  b
			   \
			    c
		*/
		if(balance < -1 && d > p->getRight()->getData()) {
			return leftRotate(p);
		}

		// left-right case: left rotate b, then right rotate a
		/*
				a 			  a 			c
			   / \		  	 / \		  /   \
			  b  t4		  	c   t4		 b     a
			 / \		   / \			/ \	  / \	
			t1  c 		  b   t3	   t1 t2 t3 t4
			   / \    	 / \
			  t2  t3  	t1 t2
		*/
		if(balance > 1 && d > p->getLeft()->getData()) {
			p->setLeft(leftRotate(p));
			return rightRotate(p);
		}

		// right left case: right rotate b, then left rotate a
		/*
				a 			  a 			c
			   / \		  	 / \		  /   \
			 t1   b		  	t1  c		 a     b
			     / \		   / \   	/ \	  / \	
			   	c  t4  		  t2  b	   t1 t2 t3 t4
			   / \  			 / \
			  t2  t3			t3 t4
		*/
		if(balance < -1 && d < p->getRight()->getData()) {
			p->setRight(rightRotate(p));
			return leftRotate(p);
		}

		return p;
	}
}

// returns node with smallest data
template<class T>
AVLNode<T>* AVLTree<T>::minNode(AVLNode<T> *p) {
	AVLNode<T> *min = p;

	// find min key of left side recursively
	if(p->getLeft() != nullptr) {
		AVLNode<T> *leftMin = minNode(p->getLeft());

		if(min->getData() > leftMin->getData()) {
			min = leftMin;
		}
	}

	// find min key of right side recursively
	if(p->getRight() != nullptr) {
		AVLNode<T> *rightMin = minNode(p->getRight());

		if(min->getData() > rightMin->getData()) {
			min = rightMin;
		}
	}

	return min;
}

template<class T>
AVLNode<T>* AVLTree<T>::deleteNode(AVLNode<T> *p, T d) {
	AVLNode<T> *unbalNode;

	// delete node like a normal binary search tree
	if(p == nullptr) {
		return p;
	}

	// if data is smaller than curr node p
	if(d < p->getData()) {
		p->setLeft(deleteNode(p->getLeft(), d));
	}

	// if data is bigger than p
	else if (d > p->getData()) {
		p->setRight(deleteNode(p->getRight(), d));
	}

	// data matches p->getData(), then this is the node that needs to be deleted
	else {
		// case 1 (no children) delete
		if(p->getLeft() == nullptr && p->getRight() == nullptr) {
			delete p;
			p = nullptr;
			return p;
		}

		// case 2 (one child on right)
		else if(p->getLeft() == nullptr) {
			AVLNode<T> *temp = p;
			p = p->getRight();
			p->setParent(temp->getParent());
			delete temp;
		}

		// case 3 (one child on left)
		else if(p->getRight() == nullptr) {
			AVLNode<T> *temp = p;
			p = p->getLeft();
			p->setParent(temp->getParent());
			delete temp;
		}

		// case 4 (two children)
		else {
			// temp stores smallest data/key in right subtree (successor)
			AVLNode<T> *temp = minNode(p->getRight());
			p->setData(temp->getData());

			// set p's right by recursively deleting node again (will either have one or no child)
			p->setRight(deleteNode(p->getRight(), temp->getData()));
		}
	}
	
	// if tree had only one node that was deleted
	if(root == nullptr) {
		return root;
	}

	int balance = getBalance(p);

	// right-right case (more nodes on right, therefore rotate left)
	if(balance < -1 && getBalance(p->getRight()) <= 0) {
		return leftRotate(p);
	}

	// right-left case
	if(balance < -1 && getBalance(p->getRight()) > 0) {
		p->setRight(rightRotate(p->getRight()));
		return leftRotate(p);
	}

	// left-left case (more nodes on left, therefore shift to right)
	if(balance > 1 && getBalance(p->getLeft()) >= 0) {
		return rightRotate(p);
	}

	// left-right case
	if(balance > 1 && getBalance(p->getLeft()) < 0) {
		p->setLeft(leftRotate(p->getLeft()));
		return rightRotate(p);
	}

	return p;
}

// prints tree (pass in root to print entire tree) using level order scan/travesal
template<class T>
void AVLTree<T>::print() {
	if(root == nullptr) {
		return;
	}

	std::queue<AVLNode<T>*> q; // this queue will store pointers of tree
	q.push(root); // push in root node first

	while(!q.empty()) {
		AVLNode<T>* currNode = q.front(); // store first pointer in currNode
		q.pop();
		std::cout << currNode->getData() << " ";

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

// deletes tree from bottom up
template<class T>
void AVLTree<T>::deleteTree(AVLNode<T> *p) {
	if(p != nullptr) {
		deleteTree(p->getLeft());
		deleteTree(p->getRight());
		delete p;
	}
}

#endif