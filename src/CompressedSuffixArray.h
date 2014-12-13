#ifndef CompressedSuffixArray_H
#define CompressedSuffixArray_H

#include "LFTable.h"
#include "SuffixArray.h"
#include <map>

class CompressedSuffixArray : public SuffixArray{
private:
	LFTable *lfTable;
	std::map<unsigned, unsigned> suffixArray;
public:
	CompressedSuffixArray(LFTable *lfTable);
	virtual unsigned getItem(unsigned i);

private:
	void generateArray();
};

#endif