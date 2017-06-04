#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include <queue>
#include "RBTNode.hpp"

// root will always be black, null nodes are considered to be black
template<class T>
class RBTree {
private:
	RBTNode<T> *root;
	int blackHeight; // height of black nodes in tree

public:
	// constructor
	RBTree() {
		root = nullptr;
		blackHeight = 0;
	}

	RBTNode<T> *getRoot();
	void incBlackHeight();
	void decBlackHeight();
	RBTNode<T> *leftRotate(RBTNode<T> *p);
	RBTNode<T> *rightRotate(RBTNode<T> *p);
	void insert(RBTNode<T> *p, T d);
	void fixTree(RBTNode<T> *p);
	RBTNode<T> *minNode(RBTNode<T> *p);
	RBTNode<T>* getSucc(RBTNode<T> *p);
	void deleteNode(T d);
	void fixTreeDeletion(RBTNode<T> *p);
	void print(RBTNode<T> *p);
};

template<class T>
RBTNode<T>* RBTree<T>::getRoot() {
	return root;
}

// increases black height by 1
template<class T>
void RBTree<T>::incBlackHeight() {
	blackHeight++;
}

// decreases black height by 1
template<class T>
void RBTree<T>::decBlackHeight() {
	blackHeight--;
}

template<class T>
RBTNode<T>* RBTree<T>::leftRotate(RBTNode<T> *p) {
	RBTNode<T> *a = p->getRight();
	RBTNode<T> *b = a->getLeft();
	RBTNode<T> *parentOfP = p->getParent();

	// rotate nodes
	p->setRight(b);
	p->setParent(a);
	a->setParent(parentOfP);
	a->setLeft(p);

	if(b != nullptr) {
		b->setParent(p);
	}

	if(parentOfP != nullptr) {
		parentOfP->setRight(a);
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
RBTNode<T>* RBTree<T>::rightRotate(RBTNode<T> *p) {
	RBTNode<T> *a = p->getLeft();
	RBTNode<T> *b = a->getRight();
	RBTNode<T> *parentOfP = p->getParent();

	// rotate nodes
	p->setParent(a);
	p->setLeft(b);
	a->setRight(p);
	a->setParent(parentOfP);

	if(b != nullptr) {
		b->setParent(p);
	}

	if(parentOfP != nullptr) {
		parentOfP->setLeft(a);
	}

	// check to see if p is root
	if(p == root) {
		root = a;
	}

	return a;
}

template<class T>
void RBTree<T>::insert(RBTNode<T> *p, T d) {
	// new node
	RBTNode<T> *n = new RBTNode<T>();

	// if tree is empty
	if(root == nullptr) {
		RBTNode<T> *n = new RBTNode<T>();
		n->setData(d);
		n->setIsRed(false); // make root node black
		root = n;
		incBlackHeight(); // increase black height of tree by 1 (root is black)
	}

	else {
		RBTNode<T> *parentOfP = p->getParent();

		// binary search tree insertion
		while(p != nullptr) {
			// go right if data (d) is bigger than current
			if(d > p->getData()) {
				parentOfP = p;
				p = p->getRight();
			}

			// go left if data (d) is smaller than current node
			else if(d < p->getData()) {
				parentOfP = p;
				p = p->getLeft();
			}

			// data matches
			else {
				break;
			}
		}

		// create new pointer and fix parent, left, right nodes
		if(p == nullptr) {
			n->setParent(parentOfP);
			n->setData(d);
			n->setIsRed(true); // set newly inserted node as red

			if(parentOfP->getData() < n->getData()) {
				parentOfP->setRight(n);
			}

			else {
				parentOfP->setLeft(n);
			}
		}
	}

	// fix the newly inserted node
	fixTree(n);
}

// p is newly inserted node n from above BSTInsert function
// check aunt/uncle node to fix insertion
template<class T>
void RBTree<T>::fixTree(RBTNode<T> *p) {
	RBTNode<T> *parent;
	RBTNode<T> *grandParent;
	RBTNode<T> *aunt; // or uncle node

	// if first node inserted is root
	if(p->getParent() == nullptr) {
		return;
	}

	// while parent is red and p is not root
	while(p != root && p->getParent()->getIsRed() == true) {
		RBTNode<T> *parent = p->getParent();
		RBTNode<T> *grandParent = p->getParent()->getParent();

		// determine aunt node
		// if aunt node is on right of grandParent
		if(grandParent->getLeft() == parent) {
			aunt = grandParent->getRight();
			// if aunt is red, recolor nodes
			if(aunt != nullptr && aunt->getIsRed() == true) {
				// recolor grandParent red
				grandParent->setIsRed(true);

				// recolor parent and aunt black
				parent->setIsRed(false);
				aunt->setIsRed(false);

				// move p to grandparent to continue loop
				p = grandParent;
			}

			// aunt is black, so rotate
			else {
				// if p is to right of parent node 
				// perform left-right case rotation
				if(parent->getRight() == p) {
					leftRotate(parent);
				}

				// regular left-left case rotation if above statement not executed
				rightRotate(grandParent);
				grandParent->setIsRed(true); // make sure recolor grandParent to red
				parent->setIsRed(false); // and parent to black
				// move p to parent
				p = parent;
			}
		}

		// aunt node is left of grandParent
		else {
			aunt = grandParent->getLeft();
			// if aunt is red, recolor nodes
			if(aunt != nullptr && aunt->getIsRed() == true) {
				// recolor grandParent red
				grandParent->setIsRed(true);

				// recolor parent and aunt black
				parent->setIsRed(false);
				aunt->setIsRed(false);

				// move p to grandparent
				p = grandParent;
			}

			// aunt is black
			else {
				// if p is left of parent node
				// perform right-left case rotation
				if(parent->getLeft() == p) {
					rightRotate(p);
				}

				// regular right-right case rotation if above statement not executed
				leftRotate(grandParent);
				grandParent->setIsRed(true);
				parent->setIsRed(false);
				p = parent;
			}
		}
	}

	root->setIsRed(false); // make sure root is black
}

template<class T>
RBTNode<T> *RBTree<T>::minNode(RBTNode<T> *p) {
	RBTNode<T> *min = p;

	// find min key of left side recursively
	if(p->getLeft() != nullptr) {
		RBTNode<T> *leftMin = minNode(p->getLeft());

		if(min->getData() > leftMin->getData()) {
			min = leftMin;
		}
	}

	// find min key of right side recursively
	if(p->getRight() != nullptr) {
		RBTNode<T> *rightMin = minNode(p->getRight());

		if(min->getData() > rightMin->getData()) {
			min = rightMin;
		}
	}

	return min;
}

// returns successor (next key)
template<class T>
RBTNode<T>* RBTree<T>::getSucc(RBTNode<T> *p) {
	// if there are nodes directly to the right of tree
	if(p->getRight() != nullptr) {
		return minNode(p->getRight());
	}

	// else there are NO nodes to right of tree
	else {
		RBTNode<T> *n = p->getParent();
		if(n == nullptr) {
			return nullptr;
		}

		else {
			while(n != nullptr && p == n->getRight()) {
				p = n;
				n = p->getParent();
			}
			return n;
		}
	}
}

template<class T>
void RBTree<T>::deleteNode(T d) {
	RBTNode<T> *p = root;
	RBTNode<T> *targetChild, *target; // target is node to be deleted

	// use p to see if node to be deleted exists in tree
	while(p != nullptr) {
		if(d < p->getData()) {
			p = p->getLeft();
		}

		else if(d > p->getData()) {
			p = p->getRight();
		}

		else {
			break;
		}
	}

	// if data entered is not in tree, return
	if(p == nullptr) {
		std::cout << "Node to be deleted is not in tree." << std::endl;
		return;
	}

	// if p has 0 children
	if(p->getLeft() == nullptr || p->getRight() == nullptr) {
		target = p;
	}

	// if p has two children, target is successor
	else {
		std::cout << "GETTING THE SUCC" << std::endl;
		target = getSucc(p);
	}

	std::cout << "target = " << target->getData() << std::endl;

	if(target->getLeft() == nullptr && target->getRight() == nullptr) {
		std::cout << "trg has 2 null children" << std::endl;
		
		// if target and p is a leaf node
		if(p == target) {
			std::cout << "\ttarget = p\n";
			fixTreeDeletion(p);

			if(p->getParent()->getLeft() == p) {
				p->getParent()->setLeft(nullptr);
			}

			else {
				p->getParent()->setRight(nullptr);
			}

			// recoloring nodes
			if(p->getParent()->getLeft() != nullptr) {
				if(p->getParent()->getIsRed() == true && p->getParent()->getLeft()->getIsRed() == true) {
					p->getParent()->setIsRed(false);
				}
			}

			if(p->getParent()->getRight() != nullptr) {
				if(p->getParent()->getIsRed() == true && p->getParent()->getRight()->getIsRed() == true) {
					p->getParent()->setIsRed(false);
				}
			}
		}

		// target is a leaf and p has a child
		else {
			fixTreeDeletion(target);

			// copy data and set left/right pointers
			p->setData(target->getData());

			if(p->getLeft() == target) {
				p->setLeft(nullptr);
			}

			else {
				if(p->getRight() == target) {
					p->setRight(nullptr);
				}

				else {
					if(target->getParent()->getRight() == target) {
						target->getParent()->setRight(nullptr);
					}

					else {
						target->getParent()->setLeft(nullptr);
					}
				}
			}

			// recoloring nodes
			if(p->getLeft() != nullptr) {
				if(p->getIsRed() == true && p->getLeft()->getIsRed() == true) {
					p->setIsRed(false);
				}
			}

			if(p->getRight() != nullptr) {
				if(p->getIsRed() == true && p->getRight()->getIsRed() == true) {
					p->setIsRed(false);
				}
			}
		}
	}

	else {
		std::cout << "CHILD CASE\n";
		// set targetChild
		if(target->getLeft() != nullptr) {
			targetChild = target->getLeft();
		}

		else {
			targetChild = target->getRight();
		}
	

		// set targetChild's parent to target's parent
		targetChild->setParent(target->getParent());
	

		// repoint root if necessary
		if(target->getParent() == nullptr) {
			root = targetChild;
		}

		// fix p's left or right child to targetChild
		else {
			// if target is to left of parent, p
			if(target->getParent()->getLeft() == target) {
				target->getParent()->setLeft(targetChild);
			}

			// target is at right of parent, p
			else {
				target->getParent()->setRight(targetChild);
			}
		}

		// copy data
		if(target != p) {
			p->setData(target->getData());
		}

		// if target is black, fix tree
		if(target->getIsRed() == false) {
			fixTreeDeletion(targetChild);
		}
	}

	delete target;
}

template<class T>
void RBTree<T>::fixTreeDeletion(RBTNode<T> *p) {
	std::cout << "ENTERED FIX TREE DELETION" << std::endl;

	if(p->getIsRed() == true) {
		std::cout << "RECOLORED" << std::endl;
		p->setIsRed(false);
	}


	else {
		RBTNode<T> *sibling;
		// while p is not root and p is black
		while(p != root && p->getIsRed() == false) {
			// first determine sibling node of p
			// sibling is right of parent
			if(p->getParent()->getLeft() == p) {
				sibling = p->getParent()->getRight();
				std::cout << "SIBLING ON RIGHT" << std::endl;
				std::cout << "SIBLING 1xxx === IS: " << sibling->getData() << std::endl;

				// if sibling node is red
				if(sibling->getIsRed() == true) {
					std::cout << "\tSIBLING = RED" << std::endl;
					// recolor nodes (sibling becomes black and parent becomes red)
					sibling->setIsRed(false);
					p->getParent()->setIsRed(true);

					leftRotate(p->getParent());
					sibling = p->getParent()->getRight();
				}

				// if sibling is black and both children are black
				if(sibling->getIsRed() == false && (sibling->getLeft() == nullptr || sibling->getLeft()->getIsRed() == false) && (sibling->getRight() == nullptr || sibling->getRight()->getIsRed() == false)) {
					std::cout << "\nSIBLING + 2 CHILD = BLACK" << std::endl;
					// color sibling node red
					sibling->setIsRed(true);

					// recur up tree
					p = p->getParent();
				}

				// sibling is black
				else {
					std::cout << "\tSIBLING IS BLACK\n";
					// right-left case
					if(sibling->getRight() != nullptr && sibling->getRight()->getIsRed() == false) {
						std::cout << "\tRL CASE" << std::endl;
						rightRotate(sibling);

						sibling = p->getParent()->getRight();
					}

					// right-right case
					std::cout << "\tRR CASE" << std::endl;
					// color sibling to p's color
					sibling->setIsRed(p->getParent()->getIsRed());
					p->getParent()->setIsRed(false);

					// make sure sibling's nodes are recolored correctly
					if(sibling->getRight() != nullptr) {
						if(sibling->getRight()->getIsRed() == true) {
							sibling->getRight()->setIsRed(false);
						}
					}

					if(sibling->getLeft() != nullptr) {
						if(sibling->getLeft()->getIsRed() == true) {
							sibling->getLeft()->setIsRed(false);
						}
					}

					leftRotate(p->getParent());

					p = root;
				}
			}

			// sibling is left of parent
			else {
				sibling = p->getParent()->getLeft();
				std::cout << "SIBLING ON LEFT" << std::endl;
				std::cout << "SIBLING IS: " << sibling->getData() << std::endl;
				// if sibling node is red
				if(sibling->getIsRed() == true) {
					std::cout << "\tSIBLING = RED\n";
					// recolor nodes (sibling becomes black and parent becomes red)
					sibling->setIsRed(false);
					p->getParent()->setIsRed(true);

					rightRotate(p->getParent());

					sibling = p->getParent()->getLeft();
				}

				// if sibling is black and both children are black
				if(sibling->getIsRed() == false && (sibling->getLeft() == nullptr || sibling->getLeft()->getIsRed() == false) && (sibling->getRight() == nullptr || sibling->getRight()->getIsRed() == false)) {
					std::cout << "\tSIBLING + 2 CHILD = BLACK\n";
					// color sibling node red
					sibling->setIsRed(true);

					// recur up tree
					p = p->getParent();
				}

				// if sibling is black
				else {
					std::cout << "SIBLING IS BLACK\n";
					// left-right case
					if(sibling->getLeft() != nullptr && sibling->getLeft()->getIsRed() == false) {
						std::cout << "\tLR CASE\n";
						sibling->getRight()->setIsRed(false);
						sibling->setIsRed(true);
						leftRotate(sibling);

						sibling = p->getParent()->getLeft();
					}

					// left-left case if above code is not executed
					std::cout << "\tLL CASE\n";
					sibling->setIsRed(p->getParent()->getIsRed());
					p->getParent()->setIsRed(false);
					if(sibling->getLeft() != nullptr) {
						sibling->getLeft()->setIsRed(false);
					}
					rightRotate(p->getParent());
					p = root;
				}
			}
		}
	}
	
	root->setIsRed(false);
}

// prints binary tree (pass in root to print entire tree) in levelorder scan/travesal
template<class T>
void RBTree<T>::print(RBTNode<T> *p) {
	if(root == nullptr) {
		return;
	}

	std::queue<RBTNode<T>*> q; // this queue will store pointers of tree
	q.push(root); // push in root node first

	while(!q.empty()) {
		RBTNode<T>* currNode = q.front(); // store first pointer in currNode
		q.pop(); // remove first element in queue

		std::cout << currNode->getData() << " "; // print out data
		std::cout << "red?: " << currNode->getIsRed() << std::endl;

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

#endif