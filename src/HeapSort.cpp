#include "HeapSort.h"

#include <iostream>

/**Danijel
Implementation of heap sort
*/
// Heap sort - setting heap
void HeapSort::max_heapify(char **arr, int i, int n) {
	int j = 2 * i;
	char *item = arr[i];
	while (j <= n) {
		if ((j < n) && (_strcmpi(arr[j], arr[j + 1]) < 0)) j++;
		if (_strcmpi(item, arr[j]) >= 0) break;
		arr[j / 2] = arr[j];
		j *= 2;
	}
	arr[j / 2] = item;
}

// Heap sort - initial heap
void HeapSort::build_maxheap(char **arr, int n) {
	for (int i = n / 2; i >= 0; --i)
		max_heapify(arr, i, n);
}

// Heap sort 
void HeapSort::sort(char **arr, int n) {
	std::cout << "Sorting...\r";
	build_maxheap(arr, n - 1);
	for (int i = n - 1; i > 0;) {
		//std::cout << "Sorting: " << i << "\t\r";
		switchItmes(arr[0], arr[i]);
		max_heapify(arr, 0, --i);
	}
	std::cout << "Sorting: completed\n";
}

void HeapSort::switchItmes(char *&x, char *&y){
	char *tmp = x;
	x = y;
	y = tmp;
}