#include <iostream>
#include <ctime>

// selection sort works by finding the smallest value in the array 
// and swapping it with a value near the front of the array
void selectionSort(int a[], int arraySize) {
	for(int i = 0; i < arraySize; i++) {
		// assume smallest value is at index i
		int minIndex = i;

		// find smallest index in for loop below (start at i + 1)
		for(int j = i+1; j < arraySize; j++) {
			// if j value is smaller than minIndex, j becomes the new minIndex
			if(a[j] < a[minIndex]) {
				minIndex = j;
			}
		}

		// swap values
		int temp = a[i];
		a[i] = a[minIndex];
		a[minIndex] = temp;
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

	std::cout << "Selection sort: " << std::endl;
	selectionSort(a, size);
	printArray(a, size);
	std::cout << std::endl;

	return 0;
}