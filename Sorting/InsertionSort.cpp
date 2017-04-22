#include <iostream>
#include <ctime>

// insertion sort works by checking if left neighbor has smaller value
// if left is smaller than current value, it swaps
void insertionSort(int a[], int arraySize) {
	for(int i = 0; i < arraySize; i++) {
		for(int j = i; j >= 0; j--) {
			// if left neighbor is smaller, swap values
			if(a[j] < a[j-1]) {
				int temp = a[j-1];
				a[j-1] = a[j];
				a[j] = temp;
			}

			// break if left neighbor is already smaller than current
			else {
				break;
			}
		}
	}
}

void printArray(int a[], int arraySize) {
	for(int i = 0; i < arraySize; i++) {
		std::cout << a[i] << " ";
	}
}

int main() {
	int size = 50;
	int a[size];

	srand(time(nullptr));

	// populate array a[] with random values
	for(int i = 0; i < size; i++) {
		a[i] = rand();
	}

	std::cout << "Original array: " << std::endl;
	printArray(a, size);
	std::cout << std::endl << std::endl;

	std::cout << "Insertion sort: " << std::endl;
	insertionSort(a, size);
	printArray(a, size);
	std::cout << std::endl;

	return 0;
}