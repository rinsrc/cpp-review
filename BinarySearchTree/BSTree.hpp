#ifndef BSTREE_HPP
#define BSTREE_HPP
#include "BSTNode.hpp"
#include <queue>

template<class K, class V>
class BSTree {
private:
	BSTNode<K, V> *root;

public:
	// constructor makes root nullptr
	BSTree() {
		root = nullptr;
	}

	// destructor
	~BSTree() {
		deleteTree(root);
		root = nullptr;
	}

	BSTNode<K, V> *getRoot();
	void setRoot(BSTNode<K, V> *p);
	BSTNode<K, V> *insert(BSTNode<K, V> *p, K k, V v);
	BSTNode<K, V> *searchKey(K k);
	void deleteMax();
	void deleteMin();
	BSTNode<K, V> *minNode(BSTNode<K, V> *p);
	BSTNode<K, V> *maxNode(BSTNode<K, V> *p);
	BSTNode<K, V> *deleteKey(BSTNode<K, V> *p, K k);
	BSTNode<K, V> *getSucc(BSTNode<K, V> *p);
	BSTNode<K, V> *getPred(BSTNode<K, V> *p);
	bool isBST(BSTNode<K, V> *p);
	void print(BSTNode<K, V> *p);
	void deleteTree(BSTNode<K, V> *p);
};

template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::getRoot() {
	return root;
}

template<class K, class V>
void BSTree<K, V>::setRoot(BSTNode<K, V> *p) {
	root = p;
}

// insert node into binary search tree
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::insert(BSTNode<K, V> *p, K k, V v) {
	// if tree is initially empty, create a root wtih data value d
	if(root == nullptr) {
		BSTNode<K, V> *nn = new BSTNode<K, V>();
		nn->setKey(k);
		nn->setValue(v);
		root = nn;
	}

	else {
		// after traversing down to leaves, insert left or right
		if(p == nullptr) {
			BSTNode<K, V> *nn = new BSTNode<K, V>();
			nn->setKey(k);
			nn->setValue(v);
			return nn;
		}

		// if key is smaller than p's key, recursively insert left
		if(k < p->getKey()) {
			p->setLeft(insert(p->getLeft(), k, v));
			p->getLeft()->setParent(p);
		}

		// if key is bigger than p's key, recursively insert right
		else if(k > p->getKey()) {
			p->setRight(insert(p->getRight(), k, v));
			p->getRight()->setParent(p);
		}

		// if key already exists in tree, just modify value
		else {
			p->setValue(v);
		}

		return p;
	}
}

// returns node with correct key, pass in key
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::searchKey(K k) {
	// if list is empty, there are no matching keys, return nullptr
	if(root == nullptr) {
		return nullptr;
	}

	else {
		BSTNode<K, V> *currNode = root;
		while(currNode != nullptr) {
			// if k is smaller than current node key, go left
			if(k < currNode->getKey()) {
				currNode = currNode->getLeft();
			}

			// if k is bigger than current node key, go right
			else if(k > currNode->getKey()) {
				currNode = currNode->getRight();
			}

			// return node with matching key
			else {
				return currNode;
			}
		}

		return nullptr; // if no key exits in tree return nullptr
	}
}

// deletes the key with biggest value in tree (rightmost node)
template<class K, class V>
void BSTree<K, V>::deleteMax() {
	if(root == nullptr) {
		return;
	}

	else {
		BSTNode<K, V> *max = root; // will store node of max value
		BSTNode<K, V> *parentOfP; // this is rightmost (max key of binary tree)

		// max key is located at far right of tree
		while(max->getRight() != nullptr) {
			max = max->getRight();
		}

		// set max parent's right to nullptr before deletion
		max->getParent()->setRight(nullptr);
		delete max;
	}
}

// deletes min key in tree (leftmost node)
template<class K, class V>
void BSTree<K, V>::deleteMin() {
	if(root == nullptr) {
		return;
	}

	else {
		BSTNode<K, V> *min = root; // stores min node

		// min key is located at far left of tree
		while(min->getLeft() != nullptr) {
			min = min->getLeft();
		}

		// set min's parent left to nullptr before deletion
		min->getParent()->setLeft(nullptr);
		delete min;
	}
}

// returns node with smallest key
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::minNode(BSTNode<K, V> *p) {
	BSTNode<K, V> *min = p;

	// find min key of left side recursively
	if(p->getLeft() != NULL) {
		BSTNode<K, V> *leftMin = minNode(p->getLeft());

		if(min->getKey() > leftMin->getKey()) {
			min = leftMin;
		}
	}

	// find min key of right side recursively
	if(p->getRight() != NULL) {
		BSTNode<K, V> *rightMin = minNode(p->getRight());

		if(min->getKey() > rightMin->getKey()) {
			min = rightMin;
		}
	}

	return min;
}

// returns node with biggest key
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::maxNode(BSTNode<K, V> *p) {
	BSTNode<K, V> *max = p;

	// find max key of left side recursively
	if(p->getLeft() != NULL) {
		BSTNode<K, V> *leftMax = maxNode(p->getLeft());

		if(max->getKey() < leftMax->getKey()) {
			max = leftMax;
		}
	}

	// find max key of right side recursively
	if(p->getRight() != NULL) {
		BSTNode<K, V> *rightMax = maxNode(p->getRight());

		if(max->getKey() < rightMax->getKey()) {
			max = rightMax;
		}
	}

	return max;
}

// deletes key (or node) from tree
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::deleteKey(BSTNode<K, V> *p, K k) {
	if(p == nullptr) {
		return p;
	}

	// if key k is smaller than current node p, go left recursively
	if(k < p->getKey()) {
		p->setLeft(deleteKey(p->getLeft(), k));
	}

	// else if key k is bigger than p, go right recursively
	else if(k > p->getKey()) {
		p->setRight(deleteKey(p->getRight(), k));
	}

	// else keys match, so delete
	else {
		// case 1 (no children), simply delete
		if(p->getLeft() == nullptr && p->getRight() == nullptr) {
			delete p;
			p = nullptr;
		}

		// case 2 (one child on right)
		else if(p->getLeft() == nullptr) {
			BSTNode<K, V> *temp = p;
			p = p->getRight();
			p->setParent(temp->getParent());
			delete temp;
		}

		// case 3 (one child on left)
		else if(p->getRight() == nullptr) {
			BSTNode<K, V> *temp = p;
			p = p->getLeft();
			p->setParent(temp->getParent());
			delete temp;
		}

		// case 4 (two children)
		else {
			// find smallest key in right subtree (inorder successor)
			BSTNode<K, V> *temp = minNode(p->getRight());

			p->setKey(temp->getKey());
			p->setValue(temp->getValue());
			std::cout << "X: " << temp->getKey() << std::endl;

			// set p's right by recursively deleting node again (will either have one or no child)
			p->setRight(deleteKey(p->getRight(), temp->getKey()));
		}

		return p;
	}
}

// returns successor (next key)
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::getSucc(BSTNode<K, V> *p) {
	// if there are nodes directly to the right of tree
	if(p->getRight() != nullptr) {
		return minNode(p->getRight());
	}

	// else there are NO nodes to right of tree
	else {
		BSTNode<K, V> *n = p->getParent();
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

// returns predecessor
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::getPred(BSTNode<K, V> *p) {
	// if there are nodes directly to left of p
	if(p->getLeft() != nullptr) {
		return maxNode(p->getLeft());
	}

	// else there are NO nodes directly to left of p, move up parent
	else {
		BSTNode<K, V> *n = p->getParent();
		while(n != nullptr && p == n->getLeft()) {
			p = n;
			n = p->getParent();
		}
	}
}

// returns true if tree is a binary search tree
template<class K, class V>
bool BSTree<K, V>::isBST(BSTNode<K, V>* p) {
	if(p == nullptr) {
		return true; // empty tree is a binary search tree
	}

	// if there is a key with bigger value than p (left subtree) it is NOT BST (return false)
	else if(p->getLeft() != nullptr && maxNode(p->getLeft())->getKey() > p->getKey()) {
		return false;
	}

	// if there is a key with smaller value than p (right subtree) it is not BST (return false)
	else if(p->getRight() != nullptr && minNode(p->getRight())->getKey() < p->getKey()) {
		return false;
	}

	// recursively check left and right of tree (if left is not a BST or right is not a BST) return false
	if(!isBST(p->getLeft()) || !isBST(p->getRight())) {
		return false;
	}

	// if tree passes all the above statements, it is a BST
	return true;
}

// prints binary tree (pass in root to print entire tree) using level order scan/travesal
template<class K, class V>
void BSTree<K, V>::print(BSTNode<K, V> *p) {
	std::queue<BSTNode<K, V>*> q; // this queue will store pointers of tree
	q.push(root); // push in root node first

	while(!q.empty()) {
		BSTNode<K, V>* currNode = q.front(); // store first pointer in currNode
		q.pop();
		std::cout << currNode->getKey() << " "; // output key

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
template<class K, class V>
void BSTree<K, V>::deleteTree(BSTNode<K, V> *p) {
	if(p != nullptr) {
		deleteTree(p->getLeft());
		deleteTree(p->getRight());
		delete p;
	}
}

#endif