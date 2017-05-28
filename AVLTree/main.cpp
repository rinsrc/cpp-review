#include <iostream>
#include "AVLTree.hpp"

int main() {
	AVLTree<int> *t = new AVLTree<int>();
	for(int i = 0; i < 10; i++) {
		t->insert(t->getRoot(), i);
	}
	/* tree looks like this:
		      3
		    /   \
		  1      7
		 / \    / \
		0   2  5   8
		      / \   \
	         4   6   9
    */
	std::cout << "Printing tree in level order scan:" << std::endl;
	t->print();

	/* after deleting node 7, tree looks like this:
		      3
		    /   \
		  1      8
		 / \    / \
		0   2  5   9
		      / \
	         4   6
	*/
	t->deleteNode(t->getRoot(), 7);
	std::cout << std::endl << std::endl << "Deleted node 7:" << std::endl;
	t->print();

	/* after deleting node 9, tree looks like this:
			  3
		    /   \
		  1      5
		 / \    / \
		0   2  4   8
		          / 
	             6
	*/
	std::cout << std::endl << std::endl << "Deleted node 9 (triggers left-left case):" << std::endl;
	t->deleteNode(t->getRoot(), 9);
	t->print();

	return 0;
}