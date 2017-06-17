#include <iostream>
#include "SplayTree.hpp"

int main() {
	SplayTree<int> *st = new SplayTree<int>();

	for(int i = 0; i < 7; i++) {
		st->insert(st->getRoot(), i);
	}

	/* (degenerate) tree should look like this:
		            6
		           /
		          5
		         /
		        4
		       /
		      3
		     /
		    2
		   /
		  1
		 /
		0   
	*/
	std::cout << "Printing tree:\n";
	st->print();

	/* after searching for key 1, tree should look like this:
	           1
	          / \
	         0   5
	            / \
	           3   6
	          / \
	         2   4     
	*/ 
	std::cout << "\n\nSearching tree for key 1 and reprinting\n";
	st->search(1);
	st->print();

	/* after deleting node of key 5, tree should look like this:
	        4
	       / \
	      1   6
	     / \
	    0   3
	       /
	      2 
	*/
	std::cout << "\n\nDeleting node of key 5 from tree and reprinting\n";
	st->deleteNode(st->getRoot(), 5);
	st->print();

	return 0;
}