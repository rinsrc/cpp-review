#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include <queue>
#include "RBTNode.hpp"

// root will always be black, null nodes are considered to be black
template<class T>
class RBTree {
private:
	RBTNode<T> *root;

public:
	// constructor
	RBTree() {
		root = nullptr;
	}

	// destructor
	~RBTree() {
		deleteTree(root);
		root = nullptr;
	}

	RBTNode<T> *getRoot();
	RBTNode<T> *leftRotate(RBTNode<T> *p);
	RBTNode<T> *rightRotate(RBTNode<T> *p);
	void insert(RBTNode<T> *p, T d);
	void fixTreeInsertion(RBTNode<T> *p);
	RBTNode<T> *minNode(RBTNode<T> *p);
	RBTNode<T>* getSucc(RBTNode<T> *p);
	void deleteNode(T d);
	void fixTreeDeletion(RBTNode<T> *p);
	void print();
	void deleteTree(AVLNode<T> *p);
};

template<class T>
RBTNode<T>* RBTree<T>::getRoot() {
	return root;
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
RBTNode<T>* RBTree<T>::leftRotate(RBTNode<T> *p) {
	RBTNode<T> *a = p->getRight();
	RBTNode<T> *b = a->getLeft();
	RBTNode<T> *parentOfP = p->getParent();

	// rotate nodes by rearranging pointers
	p->setRight(b);
	p->setParent(a);
	a->setParent(parentOfP);
	a->setLeft(p);

	if(b != nullptr) {
		b->setParent(p);
	}

	if(parentOfP == nullptr) {
		root = a;
	}

	else if(parentOfP->getRight() == p) {
		parentOfP->setRight(a);
	}

	else {
		parentOfP->setLeft(a);
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

	// rotate nodes by rearranging pointers
	p->setParent(a);
	p->setLeft(b);
	a->setRight(p);
	a->setParent(parentOfP);

	if(b != nullptr) {
		b->setParent(p);
	}

	if(parentOfP == nullptr) {
		root = a;
	}

	else if(parentOfP->getRight() == p) {
		parentOfP->setRight(a);
	}

	else {
		parentOfP->setLeft(a);
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

	// fix the newly inserted node by recoloring/rotation
	fixTreeInsertion(n);
}

// pass newly inserted node n from above insert function
// check aunt/uncle node to fix insertion
template<class T>
void RBTree<T>::fixTreeInsertion(RBTNode<T> *p) {
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

	// find min of left side recursively
	if(p->getLeft() != nullptr) {
		RBTNode<T> *leftMin = minNode(p->getLeft());

		if(min->getData() > leftMin->getData()) {
			min = leftMin;
		}
	}

	// find min of right side recursively
	if(p->getRight() != nullptr) {
		RBTNode<T> *rightMin = minNode(p->getRight());

		if(min->getData() > rightMin->getData()) {
			min = rightMin;
		}
	}

	return min;
}

// returns successor (next node)
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
	RBTNode<T> *p = root; // p is used to find node that matches d
	RBTNode<T> *replace; // node that replaces target when deleted
	RBTNode<T> *target; // target is node to be deleted

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

	// if p has 1 or 0 children, target and p are the same
	if(p->getLeft() == nullptr || p->getRight() == nullptr) {
		target = p;
	}

	// if p has two children, target is successor
	else {
		target = getSucc(p);
	}

	// if target has two nullptr children, the replacing node will be marked double black
	if(target->getLeft() == nullptr && target->getRight() == nullptr) {
		// if target and p is a leaf node
		if(p == target) {
			fixTreeDeletion(p);

			// set the left or right of p to nullptr
			if(p->getParent()->getLeft() == p) {
				p->getParent()->setLeft(nullptr);
			}

			else {
				p->getParent()->setRight(nullptr);
			}
		}

		// target is a leaf but p is not the same as target
		else {
			fixTreeDeletion(target);

			// copy data
			p->setData(target->getData());

			// set left/right pointers of target's parent to nullptr
			if(target->getParent()->getLeft() == target) {
				target->getParent()->setLeft(nullptr);
			}

			else {
				target->getParent()->setRight(nullptr);
			}
		}
	}

	// target is successor
	else {
		// determine node that replaces target
		if(target->getLeft() != nullptr) {
			replace = target->getLeft();
		}

		else {
			replace = target->getRight();
		}
	
		// set replace's parent to target's parent
		replace->setParent(target->getParent());

		// repoint root if necessary
		if(target->getParent() == nullptr) {
			root = replace;
		}

		else {
			if(target->getParent()->getLeft() == target) {
				target->getParent()->setLeft(replace);
			}

			else {
				target->getParent()->setRight(replace);
			}
		}

		// copy data
		if(target != p) {
			p->setData(target->getData());
		}

		// if target is black, fix tree
		if(target->getIsRed() == false) {
			fixTreeDeletion(replace);
		}

		/*
		code below: 
		if target is red or replace is red, recolor replace to black,
		target is then deleted
				p 						p(target's data is copied to p)
			   / \					   / \
			  b  target(black)		  b  replace(black)
				  /	\                  \
				 r	replace(red)        r 
		*/
		if(target->getIsRed() == true || replace->getIsRed() == true) {
			replace->setIsRed(false);
		}
	}

	delete target;
}

template<class T>
void RBTree<T>::fixTreeDeletion(RBTNode<T> *p) {
	RBTNode<T> *sibling;

	// while p is not root and p is black
	while(p != root && p->getIsRed() == false) {
		// (1) determine wheter sibling node of p is right of left of parent

		// if sibling is right of parent
		if(p->getParent()->getLeft() == p) {
			sibling = p->getParent()->getRight();

			// if sibling node is red, simply recolor
			if(sibling->getIsRed() == true) {
				// recolor nodes (sibling becomes black and parent becomes red)
				sibling->setIsRed(false);
				p->getParent()->setIsRed(true);

				leftRotate(p->getParent());

				sibling = p->getParent()->getRight();
			}

			// if sibling is black and both children are black
			/*
			example case where s(b) = sibling(black):
					r            b
				   / \          / \
				s(b)  p       s(r) p
				 / \          / \
				b   b        b   b
			*/
			if(sibling->getIsRed() == false && (sibling->getLeft() == nullptr || sibling->getLeft()->getIsRed() == false) && (sibling->getRight() == nullptr || sibling->getRight()->getIsRed() == false)) {
				// color sibling node red
				sibling->setIsRed(true);

				// if sibling's parent is red, color it black and break out of loop
				if(sibling->getParent() != nullptr && sibling->getParent()->getIsRed() == true) {
					sibling->getParent()->setIsRed(false);
					break;
				}

				else {
					p = p->getParent(); // recur up tree
				}
			}

			// sibling is black and one of sibling's child is red
			else {
				// right-left case
				// if sibling's left child is red
				/*
				example of right-left case:
				right rotate sibling,
				sibling moves to p's parent's right
				recolor sibling to same color as p's parent
				left rotate p's parent
				delete p
					b          b             s(r)           s(b) (recolored sibling)
				   / \        / \            / \			/ \
				  p  s(b)    p   s(r)       b   b          b   b
				     /            \        /              /
				    r             b       p         (deleted p)
				*/
				if(sibling->getLeft() != nullptr && sibling->getLeft()->getIsRed() == true) {
					rightRotate(sibling);
					sibling = p->getParent()->getRight();
				}

				// if the above code is not executed
				// it becomes just a right-right case
				// color sibling to p's parent's color
				sibling->setIsRed(p->getParent()->getIsRed());

				// p's parent will become left child after rotation
				p->getParent()->setIsRed(false); // make p's parent black

				// check right child to make sure it is black also
				if(sibling->getRight() != nullptr && sibling->getRight()->getIsRed() == true) {
					sibling->getRight()->setIsRed(false);
				}

				leftRotate(p->getParent());
				p = root;
			}
		}

		// sibling is left of parent
		else {
			sibling = p->getParent()->getLeft();

			// if sibling node is red
			if(sibling->getIsRed() == true) {
				// recolor nodes (sibling becomes black and parent becomes red)
				sibling->setIsRed(false);
				p->getParent()->setIsRed(true);

				rightRotate(p->getParent());

				sibling = p->getParent()->getLeft();
			}

			// if sibling is black and both children are black
			if(sibling->getIsRed() == false && (sibling->getLeft() == nullptr || sibling->getLeft()->getIsRed() == false) && (sibling->getRight() == nullptr || sibling->getRight()->getIsRed() == false)) {
				// color sibling node red
				sibling->setIsRed(true);

				// if sibling's parent is red, color it black and break out of loop
				if(sibling->getParent() != nullptr && sibling->getParent()->getIsRed() == true) {
					sibling->getParent()->setIsRed(false);
					break;
				}

				else {
					p = p->getParent(); // recur up tree
				}
			}

			// sibling is black and sibling has one red child
			else {
				// left-right case
				// if sibling's right child is red
				/*
				example of left-right case:
				left rotate sibling
				sibling moves to p's parent's left 
				sibling's color becomes same color as p's parent and make left child black
				right rotate p's parent
				delete p
					b          b          s(r)         s(b) (recolored sibling)
				   / \        / \         / \          / \
				 s(b) p     s(r) p       b   b        b   b
				    \       /                 \             \
				     r     b                   p          (deleted p)
				*/
				if(sibling->getRight() != nullptr && sibling->getRight()->getIsRed() == true) {
					leftRotate(sibling);
					sibling = p->getParent()->getLeft();
				}

				// if above code is not executed
				// it becomes just a left-left case
				// color sibling node the same as p's parent and sibling's parent to black
				sibling->setIsRed(p->getParent()->getIsRed());

				// parent will become right child after rotation
				sibling->getParent()->setIsRed(false);

				// color left sibling children black
				if(sibling->getLeft() != nullptr && sibling->getLeft() != nullptr) {
					sibling->getLeft()->setIsRed(false);
				}

				rightRotate(p->getParent());
				p = root;
			}
		}
	}
	
	root->setIsRed(false); // make sure root is black
}

// prints binary tree in levelorder scan/travesal
template<class T>
void RBTree<T>::print() {
	if(root == nullptr) {
		return;
	}

	std::queue<RBTNode<T>*> q; // this queue will store pointers of tree
	q.push(root); // push in root node first

	while(!q.empty()) {
		RBTNode<T>* currNode = q.front(); // store first pointer in currNode
		q.pop(); // remove first element in queue

		std::cout << currNode->getData() << " "; // print out data
		std::cout << "isRed?: " << currNode->getIsRed() << std::endl;

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
void RBTree<T>::deleteTree(RBTNode<T> *p) {
	if(p != nullptr) {
		deleteTree(p->getLeft());
		deleteTree(p->getRight());
		delete p;
	}
}

#endif