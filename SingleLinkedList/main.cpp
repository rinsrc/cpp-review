#include <iostream>
#include "SLL.hpp"

int main() {
	// create a single linked list
	SLL<int> *myList = new SLL<int>();
	
	// insert at front some values
	for(int i = 0; i < 5; i++) {
		myList->insertAtFront(i);
	}
	
	// insert at back some values
	for(int i = 0; i < 5; i++) {
		myList->insertAtBack(i*2);	
	}
	
	// print list
	std::cout << "Original list: " << std::endl;
	myList->print();
	std::cout << std::endl;
	
	// delete one value at front and back
	myList->deleteAtFront();
	myList->deleteAtBack();
	
	// reprint list with deleted values
	std::cout << std::endl << "Reprinted list with first and last nodes deleted:" << std::endl;
	myList->print();
	
	return 0;
}
