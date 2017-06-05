#include <iostream>
#include "BSTree.hpp"

int main() {
	// create binary search tree (key and value both have int data type)
	BSTree<int, int> *tree = new BSTree<int, int>();
	/* 
		based on insertion, tree should look like this (key is shown):
			  20
		    /    \
		  15      25
		 /  \    /  \
		10	18	23	30
	*/
	tree->insert(tree->getRoot(), 20, 1); // this is root: key = 20, value = 1
	tree->insert(tree->getRoot(), 25, 2); // other nodes below
	tree->insert(tree->getRoot(), 15, 3);
	tree->insert(tree->getRoot(), 18, 4);
	tree->insert(tree->getRoot(), 10, 5);
	tree->insert(tree->getRoot(), 23, 6);
	tree->insert(tree->getRoot(), 30, 7);
	tree->insert(tree->getRoot(), 20, 1000);

	std::cout << "Printing tree in order:" << std::endl;
	tree->print();
	std::cout << std::endl;

	std::cout << std::endl << "Searching for key 23:" << std::endl;
	BSTNode<int, int> *p = tree->searchKey(23);
	std::cout << "The node with key 23 is: " << p << ". Key is: " << p->getKey() << std::endl;

	std::cout << std::endl << "Deleting max key and reprinting tree:" << std::endl;
	tree->deleteMax();
	tree->print();
	std::cout << std::endl;

	/* 
		with max deleted, tree should look like this:
			  20
		    /    \
		  15      25
		 /  \    /
		10	18	23
	*/

	std::cout << std::endl << "Min node is key: " << std::endl;
	BSTNode<int, int> *min = tree->minNode(tree->getRoot());
	std::cout << min->getKey() << std::endl;

	std::cout << std::endl << "Deleting node with key 20 and reprinting tree:" << std::endl;
	tree->deleteKey(tree->getRoot(), 20);
	tree->print();
	std::cout << std::endl;
	
	/* 
		with 20 deleted, tree should look like this:
			  23
		    /    \
		  15      25
		 /  \
		10	18	
	*/

	std::cout << std::endl << "Successor of root is:" << std::endl;
	std::cout << tree->getSucc(tree->getRoot())->getKey();
	std::cout << std::endl;

	std::cout << std::endl << "Predecessor of root is:" << std::endl;
	std::cout << tree->getPred(tree->getRoot())->getKey();
	std::cout << std::endl;

	std::cout << std::endl << "Is tree a binary search tree (T/F)?: ";
	std:: cout << tree->isBST(tree->getRoot()) << std::endl;

	return 0;
}