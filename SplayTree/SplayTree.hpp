#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP
#include <iostream>
#include <queue>
#include "SplayNode.hpp"

template<class T>
class SplayTree {
private:
	SplayNode<T> *root;

public:
	// constructor
	SplayTree() {
		root = nullptr;
	}

	// destructor
	~SplayTree() {
		deleteTree(root);
		root = nullptr;
	}

	SplayNode<T> *getRoot();
	SplayNode<T> *leftRotate(SplayNode<T> *p);
	SplayNode<T> *rightRotate(SplayNode<T> *p);
	SplayNode<T> *splay(SplayNode<T>* p, T k);
	SplayNode<T> *search(T k);
	SplayNode<T> *insert(SplayNode<T> *p, T k);
	SplayNode<T> *maxNode(SplayNode<T> *p);
	SplayNode<T> *getPred(SplayNode<T> *p);
	SplayNode<T> *deleteNode(SplayNode<T> *p, T k);
	void deleteNode(T k);
	void print();
	void deleteTree(SplayNode<T> *p);
};

template<class T>
SplayNode<T>* SplayTree<T>::getRoot() {
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
SplayNode<T>* SplayTree<T>::leftRotate(SplayNode<T> *p) {
	SplayNode<T> *a = p->getRight();
	SplayNode<T> *b = a->getLeft();
	SplayNode<T> *parentOfP = p->getParent();

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
SplayNode<T>* SplayTree<T>::rightRotate(SplayNode<T> *p) {
	SplayNode<T> *a = p->getLeft();
	SplayNode<T> *b = a->getRight();
	SplayNode<T> *parentOfP = p->getParent();

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

// if node with matching key is found in tree, splay it to root, 
// otherwise last node reached is splayed to root
template<class T>
SplayNode<T>* SplayTree<T>::splay(SplayNode<T> *p, T k) {
	// if root is nullptr or root matches key, simply return root 
	if(p == nullptr || p->getKey() == k) {
		return p;
	}

	// key is in left subtree
	if(p->getKey() > k) {
		// if left of p is null, that means key is not in tree
		if(p->getLeft() == nullptr) {
			return p;
		}

		// zig-zig (left-left case), so rightRotate twice to fix
		/* example case: searching for 1
		     3(p)                                 2(p)
             /                                   /  \
            2      --> (after recursion) -->    1    3
           /                                   /
          1                                   0
         /   						(after 2nd rotation, 1 will be root)
		0
		*/
		if(p->getLeft()->getKey() > k) {
			// recursively bring key up to root
			p->getLeft()->setLeft(splay(p->getLeft()->getLeft(), k));

			// do first rotation after recursion
			p = rightRotate(p);
		}

		// zig-zag (left-right case)
		/* example case: searching for 4
		    5(p)                                   5(p)
		   /                                       /  
		  3     --> left rotate p->getLeft() -->  4  (after 2nd rotation, 4 will be root)
		 / \                                     / 
		t1  4                                   3
		                                       /
		                                      t1
		*/
		else if(p->getLeft()->getKey() < k) {
			// recursively bring matching key up to root
			p->getLeft()->setRight(splay(p->getRight()->getRight(), k));

			if(p->getLeft()->getRight() != nullptr) {
				p->setLeft(leftRotate(p->getLeft()));
			}
		}

		// do 2nd rotation (right rotate)
		if(p->getLeft() == nullptr) {
			return p;
		}

		else {
			return rightRotate(p);
		}
	}

	// else key is in right subtree (mirror case of left)
	else {
		if(p->getRight() == nullptr) {
			return p;
		}

		// zag-zag (right-right case), so leftRotate twice to fix
		if(p->getRight()->getKey() < k) {
			p->getRight()->setRight(splay(p->getRight()->getRight(), k));
			p = leftRotate(p);
		}

		// zag-zig (right-left case)
		else if(p->getRight()->getKey() > k) {
			p->getRight()->setLeft(splay(p->getRight()->getLeft(), k));

			if(p->getRight()->getLeft() != nullptr) {
				p->setRight(rightRotate(p->getRight()));
			}
		}

		// perform second rotation (left rotate)
		if(p->getRight() == nullptr) {
			return p;
		}

		else {
			return leftRotate(p);
		}
	}
}

// returns node with matching key (should be root after splay)
template<class T>
SplayNode<T>* SplayTree<T>::search(T k) {
	return splay(root, k);
}

template<class T>
SplayNode<T>* SplayTree<T>::insert(SplayNode<T> *p, T k) {
	if(root == nullptr) {
		SplayNode<T> *n = new SplayNode<T>();
		n->setKey(k);
		root = n;
		return n;
	}

	else {
		// bring node with closest value to key up to root
		// example: if inserting 3, it'll bring 2 up to root
		p = splay(p, k);
		
		// if inserted node already exists, return
		if(p != nullptr && p->getKey() == k) {
			return p;
		}

		// create new node
		SplayNode<T> *n = new SplayNode<T>();
		n->setKey(k);

		// if p (root) key is bigger, root will be right of new node
		if(p->getKey() > k) {
			n->setRight(p);
			n->setLeft(p->getLeft());
			p->setLeft(nullptr);
			p->setParent(n);
		}

		// else p (root) will be to left of new node
		else {
			n->setLeft(p);
			n->setRight(p->getRight());
			p->setRight(nullptr);
			p->setParent(n);
		}

		root = n;
		return n;
	}
}

template<class T>
SplayNode<T>* SplayTree<T>::maxNode(SplayNode<T> *p) {
	SplayNode<T> *max = p;

	// find max key of left side recursively
	if(p->getLeft() != NULL) {
		SplayNode<T> *leftMax = maxNode(p->getLeft());

		if(max->getKey() < leftMax->getKey()) {
			max = leftMax;
		}
	}

	// find max key of right side recursively
	if(p->getRight() != NULL) {
		SplayNode<T> *rightMax = maxNode(p->getRight());

		if(max->getKey() < rightMax->getKey()) {
			max = rightMax;
		}
	}

	return max;
}

template<class T>
SplayNode<T>* SplayTree<T>::getPred(SplayNode<T> *p) {
	// if there are nodes directly to left of p
	if(p->getLeft() != nullptr) {
		return maxNode(p->getLeft());
	}

	// else there are NO nodes directly to left of p, move up parent
	else {
		SplayNode<T> *n = p->getParent();
		while(n != nullptr && p == n->getLeft()) {
			p = n;
			n = p->getParent();
		}
	}
}

template<class T>
SplayNode<T>* SplayTree<T>::deleteNode(SplayNode<T> *p, T k) {
	// cannot delete empty tree, return
	if(p == nullptr) {
		return p;
	}

	else {
		// target node to delete is p
		p = splay(p, k);

		// if p's key actually matches key, then perform deletion
		if(p->getKey() == k) {
			SplayNode<T> *pred = getPred(p);

			// copy predecessor's key to p
			p->setKey(pred->getKey());

			// before deleting pred node, fix pointers for p
			if(pred->getParent()->getLeft() == pred) {
				pred->getParent()->setLeft(pred->getLeft());
			}

			else {
				pred->getParent()->setRight(pred->getRight());
			}

			delete pred;
		}

		return p;
	}
}

// prints tree (pass in root to print entire tree) using level order scan/travesal
template<class T>
void SplayTree<T>::print() {
	if(root == nullptr) {
		return;
	}

	std::queue<SplayNode<T>*> q; // this queue will store pointers of tree
	q.push(root); // push in root node first

	while(!q.empty()) {
		SplayNode<T>* currNode = q.front(); // store first pointer in currNode
		q.pop();
		std::cout << currNode->getKey() << " ";

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
void SplayTree<T>::deleteTree(SplayNode<T> *p) {
	if(p != nullptr) {
		deleteTree(p->getLeft());
		deleteTree(p->getRight());
		delete p;
	}
}

#endif