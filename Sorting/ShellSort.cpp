#include <iostream>
#include <ctime>
#include <cmath>

// shell sort works by comparing one value 
// with another value along in array (step, distance, gap)
// if the farther value is smaller, swap positions
// eventually the step will be one and linear
void shellSort(int a[], int arraySize) {
	// shell sort uses step called h to compare values of farther distances
	// using formula 2^x - 1 or (1, 3, 7, 15...)
	int h = 1;
	int x = 1;

	// calculate h
	while(h < arraySize) {
		h = pow(2, x) - 1;
		x++;
	}

	// correct h value since it enters the while loop one extra time
	x -= 2;
	h = pow(2, x) - 1;

	while(h >= 1) {
		// int i starts at h and compare with i-h in next for loop
		for(int i = h; i < arraySize; i++) {
			// compare by h step/distance
			for(int j = i; j >= h; j-=h) {
				// if current value is smaller than the h-step value, swap
				if(a[j] < a[j-h]) {
					int temp = a[j];
					a[j] = a[j-h];
					a[j-h] = temp;
				}
			}
		}

		// decrease h value by a power of 2 and subtract by 1
		h = (h+1)/2 - 1;
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

	std::cout << "Shell sort: " << std::endl;
	shellSort(a, size);
	printArray(a, size);
	std::cout << std::endl;

	return 0;
}