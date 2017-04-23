#include <iostream>
#include <ctime>

// merge function, pass in original array, an auxiliary array, 
// and the low, high, and mid index
// this function sorts and merges the arrays
void merge(int a[], int aux[], int low, int high, int mid) {
	int i = low; // start position of left subarray
	int j = mid + 1; // start position of right subarray
	int k = low; // start position for aux array

	// sort array a and copy to aux
	while(i <= mid && j <= high) {
		// if left subarray's value is smaller, copy to aux
		if(a[i] < a[j]) {
			aux[k] = a[i];
			k++; // increment aux index
			i++; // increment i index
		}

		// else, right subarray's value is smaller, copy to aux
		else {
			aux[k] = a[j];
			k++; // increment aux index
			j++; // increment j index (not i)
		}
	}

	// after while loop above finishes, check to see if there are
	// any remaining values in left/right subarray
	while(i <= mid) {
		aux[k] = a[i];
		k++;
		i++;
	}

	while(j <= high) {
		aux[k] = a[j];
		k++;
		j++;
	}

	// aux array should now be sorted from smallest to largest
	// copy all elements of aux to a
	for(int i = low; i < k; i++) {
		a[i] = aux[i];
	}
}

// this function recursively breaks the array by calling merge
void mergeSort(int a[], int aux[], int low, int high) {
	// break out of recursion once you can't break array any further 
	if(high <= low) {
		return;
	}

	// calculate mid index
	int mid = low + (high - low) / 2;

	// recursively break and sort array
	mergeSort(a, aux, low, mid); // left subarray
	mergeSort(a, aux, mid+1, high); // right subarray

	merge(a, aux, low, high, mid); // merge and sort back together
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

	std::cout << "Merge sort: " << std::endl;
	mergeSort(a, aux, 0, size);
	printArray(a, size);
	std::cout << std::endl;

	return 0;
}