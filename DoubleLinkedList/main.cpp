#include <iostream>
#include "DLL.hpp"

int main() {
	DLL<int> *myDLL = new DLL<int>();

	// insert some numbers at front
	for(int i = 0; i < 5; i++) {
		myDLL->insertAtFront(i);
	}

	// insert some numbers at back
	for(int i = 0; i < 5; i++) {
		myDLL->insertAtBack(i * 6);
	}

	// print list
	std::cout << "Original list: " << std::endl;
	myDLL->print();
	std::cout << std::endl << std::endl;

	// delete first and last node in list
	myDLL->deleteAtFront();
	myDLL->deleteAtBack();

	// reprint list with deleted nodes
	std::cout << "Reprinted list with front and back nodes deleted: " << std::endl;
	myDLL->print();

	return 0;
}
