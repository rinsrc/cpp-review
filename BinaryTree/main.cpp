#include <iostream>
#include "BTree.hpp"

// NOTE: This binary tree is NOT a Binary Search Tree
// It will insert nodes into tree starting from leftmost

int main() {
	BTree<int> *tree = new BTree<int>();
	int numOfNodes = 0;
	int numOfLeaves = 0;

	/* 
		tree should look like this:
			  0
		    /    \
		  1       2
		 /  \    /  \
		3	4	5	 6
	*/

	for(int i = 0; i < 7; i++) {
		tree->insert(i);
	}

	// print tree in order
	std::cout << "Printing tree: " << std::endl;
	tree->print(tree->getRoot());
	
	// calculate number of nodes in tree
	std::cout << std::endl;
	tree->nodeCount(tree->getRoot(), numOfNodes);
	std::cout << std::endl;
	std::cout << "Number of nodes in tree is: " << numOfNodes << std::endl;

	// calculate the depth of the tree
	std::cout << std::endl;
	std::cout << "Depth (number of levels) of tree is: " << tree->depth(tree->getRoot()) << std::endl;

	// calculate the number of leaves in the tree
	tree->countLeaves(tree->getRoot(), numOfLeaves);
	std::cout << std::endl;
	std::cout << "Number of leaves in tree is: " << numOfLeaves << std::endl;

	// checks to see if a value is in subtree
	std::cout << std::endl;
	std::cout << "Check if number 2 is in tree (T/F): " << tree->check(tree->getRoot(), 2) << std::endl;
	std::cout << "Check if number 89 is in tree (T/F): " << tree->check(tree->getRoot(), 89) << std::endl;

	// mirror tree
	std::cout << std::endl;
	std::cout << "Mirroring tree: "<< std::endl;
	tree->mirror(tree->getRoot());
	tree->print(tree->getRoot());
	
	/* 
		mirrored tree should now look like this:
			  0
		    /    \
		   2      1
		 /  \    /  \
		6	 5	4	 3
	*/

	// printing path from 2nd left child to root
	BTNode<int>* p = tree->getRoot()->getLeft()->getLeft();
	std::cout << std::endl << std::endl;
	std::cout << "The value/data of 2nd left child is " << p->getData() << "." << std::endl;
	std::cout << "Printing path from root to 2nd left child: " << std::endl;
	tree->printPathFromRoot(p);

	// swim a node up a tree
	std::cout << std::endl << std::endl;
	std::cout << "Swimming 2nd left child up tree: " << std::endl;
	tree->swim(p);
	tree->print(tree->getRoot());

	/* 
		after swimming 2nd left child, tree should look like this:
			  6
		    /    \
		   0      1
		 /  \    /  \
		2	 5	4	 3
	*/

	// sink node down tree
	std::cout << std::endl << std::endl;
	BTNode<int> *rightChild = tree->getRoot()->getRight();
	std::cout << "Sinking 1st right child (data value = " << rightChild->getData() << ") down tree:" << std::endl;
	tree->sink(rightChild);
	tree->print(tree->getRoot());

	/* 
		after sinking 1st right child of root, tree should look like this:
			  6
		    /    \
		   0      4
		 /  \    /  \
		2	 5	1	 3
	*/

	// copy tree
	std::cout << std::endl << std::endl;
	std::cout << "Copying tree and printing: " << std::endl;
	BTree<int> *treeTwo = new BTree<int>();
	treeTwo->copyTree(treeTwo, tree->getRoot()); // treeTwo copies tree
	treeTwo->print(treeTwo->getRoot()); // print treeTwo

	// delete tree
	std::cout << std::endl;
	delete tree;

	return 0;
}