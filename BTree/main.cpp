#include <iostream>
#include "BTree.hpp"

// the degree MUST be 3 or bigger
// otherwise, it would be a plain binary tree
int main() {
	BTree<int> *t = new BTree<int>(4);
	
	for(int i = 0; i < 13; i++) {
		t->insert(t->getRoot(), i);
	}
	/*
	tree looks like this where commas represent more than 1 key in an array:
	     3  , 7 [root]
	    / \    \
	   /   \    \
	  1     5    9
	  |     |    |
	 / \   / \  / \   
	0   2 4  6 8  10,11,12

	*/
	std::cout << "Printing keys in tree from left to right (inorder traversal): " << std::endl;
	t->print(t->getRoot());
	std::cout << std::endl;
	std::cout << t->getRoot()->getChild()[2]->getChild()[1]->getKeys()[2] << std::endl;
	int target = 4;
	BNode<int> *s = t->search(t->getRoot(), target);
	std::cout << "\n\nSearching B-Tree for key " << target << std::endl; 
	std::cout << "Potential node located at: " << s << std::endl;
	if(s != nullptr) {
		int i;
		for(i = 0; i < s->getNumOfKeys(); i++) {
			if(s->getKeys()[i] == target) {
				break;
			}
		}
		std::cout << "Node contains matching key (target) at index " << i << std::endl;
		std::cout << "Key is: " << s->getKeys()[i] << std::endl;
	}

	else {
		std::cout << "Key does not exist in B-Tree\n";
	}

	std::cout << "\n\n\nDeleted key 12 from B-Tree and reprinting:\n";
	t->deleteKey(t->getRoot(), 12);
	t->print(t->getRoot());
	/*
	after deleting 12, tree looks like this:
	        3
	      /   \
	     1     5 ,  7 , 9
	    / \   / \    \   \
	   0   2 4   6   8   10,11
	*/


	std::cout << "\n\nDeleted key 9 from B-Tree and reprinting:\n";
	t->deleteKey(t->getRoot(), 9);
	t->print(t->getRoot());
	/*
	after deleting 9, tree looks like this:
	        3
	      /   \
	     1     5 ,  7 , 10
	    / \   / \    \   \
	   0   2 4   6   8    11
	*/


	std::cout << "\n\nDeleted key 2 from B-Tree and reprinting:\n";
	t->deleteKey(t->getRoot(), 2);
	t->print(t->getRoot());
	/*
	after deleting 2, tree should look like this:
	        5
	     /     \
	    1       7, 10
	   / \     / \   \
	  0  3,4  6   8  11
	*/


	std::cout << "\n\nAttempting to delete key 47 (not in B-Tree):\n";
	t->deleteKey(t->getRoot(), 47);

	delete t;

	return 0;
}
