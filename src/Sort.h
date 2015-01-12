#ifndef Sort_H
#define Sort_H

#include "WaveletTree.h"

class Sort{
public:
	virtual void sort(WaveletTree **arr, int n) = 0;

};
#endif