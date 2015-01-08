#include "WaveletHeapSort.h"

#include <iostream>
#include <string.h>

/**Danijel
Implementation of heap sort
*/
// Heap sort - setting heap
void WaveletHeapSort::max_heapify(WaveletTree **arr, int i, int n) {
	int j = 2 * i;
	WaveletTree *item = arr[i];
	while (j <= n) {
	  //	  std::cout << "Maxheap..." << j << "\r" << std::flush;
		int x = waveletCmp(arr[j], arr[j + 1]);
		if ((j < n) && (waveletCmp(arr[j], arr[j + 1]) < 0)){
			++j;
		}
		if (waveletCmp(item, arr[j]) >= 0) {
			break;
		}
		arr[j / 2] = arr[j];
		j *= 2;
	}
	arr[j / 2] = item;
}

// Heap sort - initial heap
void WaveletHeapSort::build_maxheap(WaveletTree **arr, int n) {
        for (int i = n / 2; i >= 0; --i) {
	  //std::cout << "Building heap..." << i << "\r" << std::flush;
	        max_heapify(arr, i, n);
	}
}

// Heap sort 
void WaveletHeapSort::sort(WaveletTree **arr, int n) {
        std::cout << "Sorting...\r" << std::flush;
	
	build_maxheap(arr, n - 1);

	for (int i = n - 1; i > 0;) {
	  // std::cout << "Sorting: " << i << "\t\r";// << std::flush;
		switchItmes(arr[0], arr[i]);
		
		max_heapify(arr, 0, --i);
	}
	std::cout << "Sorting: completed\n" << std::flush;
}

void WaveletHeapSort::switchItmes(WaveletTree *&x, WaveletTree *&y){
	WaveletTree *tmp = x;
	x = y;
	y = tmp;
}

int WaveletHeapSort::waveletCmp(WaveletTree *x, WaveletTree *y){
	unsigned xLen = x->length();
	unsigned yLen = y->length();

	/**Check every character until first different*/
	for (unsigned i = 0; i < xLen && i < yLen; ++i){
	        char xChar = x->getChar(i);
		char yChar = y->getChar(i);
		if (xChar == yChar){
			continue;
		}
		else if (xChar > yChar){
			return 1;
		}
		else {
			return -1;
		}
	}

	return 0;
}
