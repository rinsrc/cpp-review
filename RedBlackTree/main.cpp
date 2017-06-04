#include <iostream>
#include "RBTree.hpp"

int main() {
	RBTree<int> *t = new RBTree<int>();

	for(int i = 0; i < 8; i++) {
		t->insert(t->getRoot(), i);
	}

	t->insert(t->getRoot(), -1);

	std::cout << std::endl << "Printing tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 2:" << std::endl;
	t->deleteNode(2);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 1:" << std::endl;
	t->deleteNode(1);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 0:" << std::endl;
	t->deleteNode(0);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node -1:" << std::endl;
	t->deleteNode(-1);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 5:" << std::endl;
	t->deleteNode(5);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 6:" << std::endl;
	t->deleteNode(6);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 7:" << std::endl;
	t->deleteNode(7);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

/*
	std::cout << "\nDeleted node 4:" << std::endl;
	t->deleteNode(4);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 6:" << std::endl;
	t->deleteNode(6);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 5:" << std::endl;
	t->deleteNode(5);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());


	std::cout << "\nDeleted node 7:" << std::endl;
	t->deleteNode(7);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());

	std::cout << "\nDeleted node 1:" << std::endl;
	t->deleteNode(1);

	std::cout << "\nReprinting tree:" << std::endl;
	t->print(t->getRoot());
*/
	return 0;
}