#ifndef SuffixArray_H
#define SuffixArray_H

#include "LFTable.h"

class SuffixArray{
public:
	virtual unsigned getItem(unsigned i) = 0;
};
#endif