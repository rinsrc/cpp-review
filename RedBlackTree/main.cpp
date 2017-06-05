#include <iostream>
#include "RBTree.hpp"

int main() {
	RBTree<int> *t = new RBTree<int>();

	for(int i = 0; i < 8; i++) {
		t->insert(t->getRoot(), i);
	}
	t->insert(t->getRoot(), -1);

	std::cout << "Printing tree:" << std::endl;
	t->print();
	/*
	tree looks like this, where b = black and r = red:
				 3b
			   /   \
	          1r    5r
	         / \   / \
		    0b 2b 4b  6b
		   /           \   
		  -1r           7r
	*/

	std::cout << "\nDeleted node 2:" << std::endl;
	t->deleteNode(2);
	t->print();
	/*
	after deleting node 2 from tree:
				 3b
			   /   \
	          0r    5r
	         / \   / \
		   -1b 1b 4b  6b
		               \   
		               7r
	*/

	std::cout << "\nDeleted node 3:" << std::endl;
	t->deleteNode(3);
	t->print();
	/*
	after deleting node 3 from tree:
				 4b
			   /   \
	          0r    6r
	         / \   / \
		   -1b 1b 5b  7b
	*/

	std::cout << "\nDeleted node 7:" << std::endl;
	t->deleteNode(7);
	t->print();
	/*
	after deleting node 7 from tree:
				 4b
			   /   \
	          0r    6b
	         / \   /
		   -1b 1b 5r
	*/

	std::cout << "\nDeleted node 1:" << std::endl;
	t->deleteNode(1);
	t->print();
	/*
	after deleting node 1 from tree:
				 4b
			   /   \
	          0b    6b
	         /     /
		   -1r    5r
	*/

	std::cout << "\nDeleted node 6:" << std::endl;
	t->deleteNode(6);
	t->print();
	/*
	after deleting node 6 from tree:
				 4b
			   /   \
	          0b    5b
	         /
		   -1r
	*/


	std::cout << "\nDeleted node 5:" << std::endl;
	t->deleteNode(5);
	t->print();
	/*
	after deleting node 5 from tree:
				 0b
			   /   \
	         -1b    4b
	*/

	std::cout << "\nDeleted node -1:" << std::endl;
	t->deleteNode(-1);
	t->print();
	/*
	after deleting node -1 from tree:
				 0b
			      \
	               4r
	*/

	return 0;
}
