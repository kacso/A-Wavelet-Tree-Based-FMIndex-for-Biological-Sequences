#ifndef WaveletHeapSort_H
#define WaveletHeapSort_H

#include "Sort.h"
#include "WaveletTree.h"

class WaveletHeapSort : public Sort{
public:
	virtual void sort(WaveletTree **arr, int n);

private:
	void max_heapify(WaveletTree **arr, int i, int n);
	void build_maxheap(WaveletTree **arr, int n);
	void switchItmes(WaveletTree *&x, WaveletTree *&y);
	int waveletCmp(WaveletTree *x, WaveletTree *y);
};
#endif
