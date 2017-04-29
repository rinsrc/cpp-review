#include <iostream>
#include <ctime>

// pass in array, start index and end index (returns pivot index)
// partition returns index of the pivot (use start as pivot)
int partition(int a[], int start, int end) {
	int i = start + 1; 	// start is pivot, so i will be the next element in array
	int j = end; // j is at end of array
	int temp = 0; // used for swap

	while(true) {
		// i will store index with value bigger than pivot
		while(a[i] < a[start]) {
			// if i reaches end, break out of loop
			if(i == end) {
				break;
			}

			i++; // increment until i finds number smaller than pivot
		}

		// j will store index with value smaller than pivot
		while(a[j] > a[start]) {
			// if j reaches start, break out of loop
			if(j == start) {
				break;
			}

			j--; // decrement until j finds smaller number than pivot
		}

		// if i passes j break out of while loop 
		if(i >= j) {
			break;
		}

		// i should be at an index with value bigger than pivot
		// j should be at an index with value smaller than pivot
		// perform swap and increment/decrement
		temp = a[j];
		a[j] = a[i];
		a[i] = temp;
		i++;
		j--;
	}

	// lastly, swap pivot with j
	temp = a[start];
	a[start] = a[j];
	a[j] = temp;

	return j; // return j, because it will be the new pivot
}

// main recurisve quickSort algorithm
void quickSort(int a[], int start, int end) {
	// if start index passes end index, return (can't break array further)
	if(start >= end) {
		return;
	}

	// get pivot index from partition function
	int pivot = partition(a, start, end);

	// recursively call quickSort
	quickSort(a, start, pivot-1); // sort left half of array
	quickSort(a, pivot+1, end); // sort right half of array
}

void printArray(int a[], int arraySize) {
	for(int i = 0; i < arraySize; i++) {
		std::cout << a[i] << " ";
	}
}

int main() {
	int size = 50;
	int a[size]; // array that needs to be sorted
	int aux[size]; // auxiliary array

	srand(time(nullptr));

	// populate array a[] with random values
	for(int i = 0; i < size; i++) {
		a[i] = rand();
	}

	std::cout << "Original array: " << std::endl;
	printArray(a, size);
	std::cout << std::endl << std::endl;

	std::cout << "Quick sort: " << std::endl;
	quickSort(a, 0, size-1);
	printArray(a, size);
	std::cout << std::endl;

	return 0;
}