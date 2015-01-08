#ifndef SuffixArray_H
#define SuffixArray_H

#include "LFTable.h"

class SuffixArray{
public:
	virtual void generateArray(LFTable *lfTable, WaveletTree **arr) = 0;
	virtual unsigned getItem(unsigned i) = 0;
};
#endif