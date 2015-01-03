#ifndef HeapSort_H
#define HeapSort_H

#include "Sort.h"

class HeapSort : public Sort{
public:
	virtual void sort(char **arr, int n);

private:
	void max_heapify(char **arr, int i, int n);
	void build_maxheap(char **arr, int n);
	void switchItmes(char *&x, char *&y);
};
#endif